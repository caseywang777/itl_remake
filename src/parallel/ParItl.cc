#include "ParItl.h"

static int paritl_initialized = 0; // whether initialized already
static int rank; // MPI rank of this process
static int nprocs; // MPI groupsize
static int dim; // number of dimensions
static MPI_Comm comm; // MPI communicator
static int num_threads = 1; // number of threads PatItl can use
static int did; // domain id for diy
static int nblocks; // my local number of blocks

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


int Patitl_Read_data_all(int did, char **file_names, DIY_Datatype var_type, void** buffer)
{
  buffer = malloc(sizeof(void *) * nblocks);
  buffer = new void *[nblocks];
}
