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
  //fprintf(stdout,"1\n");
  fields = new Field[nblocks];
//fprintf(stdout,"2\n");
  // if (with_header)
  //   BIL_Set_io_header_size(12);

  if (var_type == kFloat) {
      float **data = new float *[nblocks];
      //fprintf(stdout,"3\n");
      MPI_Datatype bil_datatype;
      MPI_Type_contiguous(tuple_size, MPI_FLOAT, &bil_datatype);
      int block_min[4], block_size[4]; // block extents
      for (int i = 0; i < nblocks; i++)
      {
        DIY_Block_starts_sizes(did, i, block_min, block_size);
        data[i] = new float[block_size[0] * block_size[1] * block_size[2] * tuple_size]; 
        std::cout<<block_size[0] * block_size[1] * block_size[2]<<std::endl;
        Grid* grid = new CartesianGrid(block_size[0], block_size[1], block_size[2]);
        fields[i].set_grid(grid);
      }
      //fprintf(stdout,"4\n");
      DIY_Read_data_all(did, file_names, DIY_FLOAT, (void **)data, 0);
//fprintf(stdout,"5\n");
      for (int i = 0; i < nblocks; ++i) {
        AbstractArray* array = new FloatArray(block_size[0] * block_size[1] * block_size[2], tuple_size, data[i]);
        fields[i].attach_variable(array);
      }
//fprintf(stdout,"6\n");
      MPI_Barrier(MPI_COMM_WORLD);
      MPI_Type_free(&bil_datatype);
    } else if (var_type == kInt32) {
      int32_t **data = new int32_t *[nblocks];
      //fprintf(stdout,"3\n");
      MPI_Datatype bil_datatype;
      MPI_Type_contiguous(tuple_size, MPI_FLOAT, &bil_datatype);
      int block_min[4], block_size[4]; // block extents
      for (int i = 0; i < nblocks; i++)
      {
        DIY_Block_starts_sizes(did, i, block_min, block_size);
        data[i] = new int32_t[block_size[0] * block_size[1] * block_size[2] * tuple_size]; 
        std::cout<<block_size[0] * block_size[1] * block_size[2]<<std::endl;
        Grid* grid = new CartesianGrid(block_size[0], block_size[1], block_size[2]);
        fields[i].set_grid(grid);
      }
      //fprintf(stdout,"4\n");
      DIY_Read_data_all(did, file_names, DIY_INT, (void **)data, 0);
//fprintf(stdout,"5\n");
      for (int i = 0; i < nblocks; ++i) {
        AbstractArray* array = new Int32Array(block_size[0] * block_size[1] * block_size[2], tuple_size, data[i]);
        fields[i].attach_variable(array);
      }
//fprintf(stdout,"6\n");
      MPI_Barrier(MPI_COMM_WORLD);
      MPI_Type_free(&bil_datatype);
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

int Paritl_WriteHistogram()
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