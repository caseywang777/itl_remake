#ifndef _PARITL
#define _PARITL

#include "mpi.h"
#include "diy.h"

namespace itl {

int Paritl_Init(int dim, int num_threads, MPI_Comm comm);

/*
  Decomposes a discrete domain

  block_order: ROUND_ROBIN_ORDER or CONTIGUOUS_ORDER numbering of
  global block ids to processes (input)
  data_size: global data size (grid pts) in each dimension
  glo_num__blocks: total number of blocks in the global domain (input)
    pass 0 or anything for CONTIGUOUS_ORDER (unused)
  loc_num_blocks: local number of blocks on this process (output)
  share_face: whether neighboring blocks share a common face or are
  separated by a gap of one unit
  ghost: ghost layer for each dimension and side (min, max)
   each entry can be 0 (no ghost) or > 0 (this many ghost cells per side)
   {x min side ghost, x max side ghost, y min side ghost, y max side ghost...}
  given: constraints on the blocking entered as an array where
  0 implies no constraint in that direction and some value n > 0 is a given
  number of blocks in a given direction
  eg., {0, 0, 0, t} would result in t blocks in the 4th dimension
  wrap: whether wraparound neighbors are used

  returns: id of domain (< 0 if error)
*/
int Paritl_Decompose(int block_order, int *data_size, int glo_num_blocks, 
		  int *loc_num_blocks, int share_face, int *ghost, 
		  int *given, int wrap);


int Paritl_Read_data_all(int did, char **file_names, int var_type, int tuple_size, bool with_header);

int Paritl_ComputeHistogram(double min, double max);

int Paritl_WriteHistogram();

int Paritl_Finalize();

}  // namespace itl

#endif