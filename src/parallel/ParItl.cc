#include "ParItl.h"

static int paritl_initialized = 0; // whether initialized already
static int rank; // MPI rank of this process
static int nprocs; // MPI groupsize
static int dim; // number of dimensions
static MPI_Comm comm; // MPI communicator
static int num_threads = 1; // number of threads PatItl can use
static int did; // domain id for diy
static int nblocks; // my local number of blocks
static Field* fields;

int Paritl_Init(int dim, int num_threads, MPI_Comm comm) {

  if (paritl_initialized) // prevent multiple initialiations
    return 0;

  ::dim = dim;
  ::comm = comm;
  ::num_threads = num_threads;
  MPI_Comm_rank(comm, &::rank);
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
  ::did = DIY_Decompose(block_order, data_size, glo_num_blocks, loc_num_blocks, share_face, ghost, given, wrap);
  ::nblocks = loc_num_blocks;
  return did;
}


int Patitl_Read_data_all(int did, char **file_names, int var_type, int tuple_size, void** buffer, bool with_header)
{
  fields = new Field[nblocks];

  if (with_header)
    BIL_Set_io_header_size(12);

  switch (var_type) {
    case kFloat:
      float **data = new float *[nblocks];
      MPI_Datatype bil_datatype;
      MPI_Type_contiguous(tuple_size, MPI_FLOAT, &bil_datatype);
      int block_min[4], block_size[4]; // block extents
      for (int i = 0; i < nblocks; i++)
      {
        DIY_Block_starts_sizes(did, i, block_min, block_size);
        data[i] = new float[block_size[0] * block_size[1] * block_size[2] * block_size[3] * tuple_size]; 
        //  cout<<block_size[0] * block_size[1] * block_size[2] * block_size[3] * 3<<endl;
      }
      DIY_Read_data_all(did, file_names, bil_datatype, (void **)data, 0);

      for (int i = 0; i < nblocks; ++i) {
        AbstractArray* array = new FloatArray(block_size[0] * block_size[1] * block_size[2] * block_size[3], tuple_size, data[i]);
        fields[i].attach_variable(array);
      }

      MPI_Barrier(MPI_COMM_WORLD);
      MPI_Type_free(&bil_datatype);
      break;
    default:
      Console::Warn("RawReader::LoadData() given unsupported data type.");
  }
}
