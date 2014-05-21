#include "ParItl.h"

#include "core/abstract_array.h"
#include "core/basic_types.h"
#include "core/field.h"
#include "core/float_array.h"
#include "io/console.h"
#include <stdio.h>

namespace {

int paritl_initialized = 0; // whether initialized already
int rank; // MPI rank of this process
int nprocs; // MPI groupsize
int dim; // number of dimensions
MPI_Comm comm; // MPI communicator
int num_threads = 1; // number of threads PatItl can use
int did; // domain id for diy
int nblocks; // my local number of blocks
itl::Field* fields;

}

namespace itl {

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
  fprintf(stdout,"1\n");
  fields = new Field[nblocks];
fprintf(stdout,"2\n");
  // if (with_header)
  //   BIL_Set_io_header_size(12);

  if (var_type == kFloat) {
      float **data = new float *[nblocks];
      fprintf(stdout,"3\n");
      MPI_Datatype bil_datatype;
      MPI_Type_contiguous(tuple_size, MPI_FLOAT, &bil_datatype);
      int block_min[4], block_size[4]; // block extents
      for (int i = 0; i < nblocks; i++)
      {
        DIY_Block_starts_sizes(did, i, block_min, block_size);
        data[i] = new float[block_size[0] * block_size[1] * block_size[2] * tuple_size]; 
        std::cout<<block_size[0] * block_size[1] * block_size[2]<<std::endl;
      }
      fprintf(stdout,"4\n");
      DIY_Read_data_all(did, file_names, DIY_INT, (void **)data, 0);
fprintf(stdout,"5\n");
      for (int i = 0; i < nblocks; ++i) {
        AbstractArray* array = new FloatArray(block_size[0] * block_size[1] * block_size[2], tuple_size, data[i]);
        fields[i].attach_variable(array);
      }
fprintf(stdout,"6\n");
      MPI_Barrier(MPI_COMM_WORLD);
      MPI_Type_free(&bil_datatype);
    } else {
      Console::Warn("RawReader::LoadData() given unsupported data type.");
    }
}

}  // namespace itl