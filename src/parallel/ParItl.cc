// Copyright (c) 2014 Kewei Lu. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "ParItl.h"
#include "algorithm/hist.h"
#include "core/abstract_array.h"
#include "core/basic_types.h"
#include "core/field.h"
#include "core/float_array.h"
#include "core/int32_array.h"
#include "core/cartesian_grid.h"
#include "io/console.h"
#include "stat/bins.h"
#include "stat/histogram.h"
#include <stdio.h>
#include <memory>
#include <vector>

namespace itl {

namespace {

int paritl_initialized = 0; // whether initialized already
int rank; // MPI rank of this process
int nprocs; // MPI groupsize
int dim; // number of dimensions
MPI_Comm comm; // MPI communicator
int num_threads = 1; // number of threads PatItl can use
int did; // domain id for diy
int nblocks; // my local number of blocks
Field* fields;
std::vector<Histogram> hists;

}

int Paritl_Init(int dim, int num_threads, MPI_Comm comm) {

  if (paritl_initialized) // prevent multiple initialiations
    return 0;

  dim = dim;
  comm = comm;
  num_threads = num_threads;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &nprocs);

  DIY_Init(dim, num_threads, comm);

  paritl_initialized = 1;

  return 0;
}


int Paritl_Finalize() {
	if (!paritl_initialized) // prevent finalizing without initializing
		return 0;
	DIY_Finalize();
	paritl_initialized = 0;
	return 0;
}

int Paritl_Decompose(int block_order, int *data_size, int glo_num_blocks, 
      int *loc_num_blocks, int share_face, int *ghost, 
      int *given, int wrap) {
  did = DIY_Decompose(block_order, data_size, glo_num_blocks, loc_num_blocks, share_face, ghost, given, wrap);
  nblocks = *loc_num_blocks;
  return did;
}


int Paritl_Read_data_all(int did, char **file_names, int var_type, int tuple_size, bool with_header)
{
  fields = new Field[nblocks];
  //if (with_header)
  //  BIL_Set_io_header_size(12);

  if (var_type == kFloat) {
      float **data = new float *[nblocks];
      int block_min[4], block_size[4]; // block extents
      for (int i = 0; i < nblocks; i++)
      {
        DIY_Block_starts_sizes(did, i, block_min, block_size);
        data[i] = new float[block_size[0] * block_size[1] * block_size[2] * tuple_size]; 
        std::cout<<block_size[0] * block_size[1] * block_size[2]<<std::endl;
        Grid* grid = new CartesianGrid(block_size[0], block_size[1], block_size[2]);
        fields[i].set_grid(grid);
      }
      DIY_Read_data_all(did, file_names, DIY_FLOAT, (void **)data, 0);
      for (int i = 0; i < nblocks; ++i) {
        AbstractArray* array = new FloatArray(block_size[0] * block_size[1] * block_size[2], tuple_size, data[i]);
        fields[i].attach_variable(array);
      }
      MPI_Barrier(MPI_COMM_WORLD);
    } else if (var_type == kInt32) {
      int32_t **data = new int32_t *[nblocks];
      int block_min[4], block_size[4]; // block extents
      for (int i = 0; i < nblocks; i++)
      {
        DIY_Block_starts_sizes(did, i, block_min, block_size);
        data[i] = new int32_t[block_size[0] * block_size[1] * block_size[2] * tuple_size]; 
        std::cout<<block_size[0] * block_size[1] * block_size[2]<<std::endl;
        Grid* grid = new CartesianGrid(block_size[0], block_size[1], block_size[2]);
        fields[i].set_grid(grid);
      }
      DIY_Read_data_all(did, file_names, DIY_INT, (void **)data, 0);

      for (int i = 0; i < nblocks; ++i) {
        AbstractArray* array = new Int32Array(block_size[0] * block_size[1] * block_size[2], tuple_size, data[i]);
        fields[i].attach_variable(array);
      }
      MPI_Barrier(MPI_COMM_WORLD);
    } else {
      Console::Warn("RawReader::LoadData() given unsupported data type.");
    }
}

int Paritl_ComputeHistogram(double min, double max)
{
  int from[3] = {0, 0, 0};
  int block_min[4], block_size[4]; // block extents
  std::shared_ptr<Bins> bins(new RegularBins(min, max, 32));
  for (int i = 0; i < nblocks; i++)
  {
    DIY_Block_starts_sizes(did, i, block_min, block_size);
    hists.push_back(ComputeHistogram(&fields[i], bins, from, block_size));
  }
}

int Paritl_WriteHistogram(char* filename)
{
  MPI_File fd;
  MPI_Status status;
  int* allNumBlocks = new int[nprocs];
  int myNumValues;
  int offset;
  int numBins=32;
  MPI_Allgather(&nblocks, 1, MPI_INT, allNumBlocks, 1, MPI_INT, MPI_COMM_WORLD);
  if(rank==0)
  {
    for(int i=0;i<nprocs;i++)
      fprintf(stdout,"%d ",allNumBlocks[i]);
  }
  //first integer indicates the number of bins for each histogram
  offset=1;  
  myNumValues=0;
  myNumValues=allNumBlocks[rank]*(numBins+1);
  for(int j=1;j<rank;j++)
  {
    offset=offset+allNumBlocks[j-1]*(numBins+1);
  }
  assert(MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fd) == MPI_SUCCESS);
  float* values = new float[nblocks*(numBins+1)];
  for (int i = 0; i < nblocks; i++)
  {
    //first value record the block id
    values[i*(numBins+1)]=(float)(DIY_Gid(0,i)); 
    for (size_t j = 1; j < numBins+1; j++) {
      values[i*(numBins+1)+j]=hists[i].get_frequency(j);
    }
  }
  if(rank==0)
    assert(MPI_File_write(fd, &numBins, 1, MPI_INT, &status) == MPI_SUCCESS);
  MPI_File_set_view(fd,offset,MPI_FLOAT,MPI_FLOAT,"native",MPI_INFO_NULL);
  MPI_File_write(fd,values,myNumValues,MPI_FLOAT, &status);
  MPI_File_close(&fd);
}

int Paritl_DistributedWriteHistogram()
{
  char buffer[50];
  sprintf(buffer, "./%d.off", rank);
  FILE * pFile;
  pFile = fopen (buffer, "w");
  for (int i = 0; i < nblocks; i++)
  {
    for (size_t j = 0; j < 32; j++) {
      fprintf (pFile, "%f ",hists[i].get_frequency(j));
    }
    fprintf (pFile, "\n");
  }
  
}

}  // namespace itl