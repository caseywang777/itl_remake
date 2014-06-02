// Copyright (c) 2014 Kewei Lu. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "parallel/ParItl.h"
#include "core/basic_types.h"

using namespace itl;

int main(int argc, char **argv)
{
  int dim = 3;
  int tot_blocks = 8;
  int data_size[3] = {10, 10, 10}; // {x_size, y_size, z_size}
  int given[3] = {0, 0, 0}; // no constraints on decomposition in {x, y, z}
  int ghost[6] = {0, 0, 0, 0, 0, 0}; // -x, +x, -y, +y, -z, +z ghost
  int min[3], max[3], size[3]; // block extents
  char *infiles[] = { (char *)"test.dat" }; // pre-made 10x10x10 ints
  char outfile[] = "test.out"; // analysis output file
  int num_threads = 1; // number of threads DIY can use
  int nblocks; // my local number of blocks
  int rank; // MPI process
  int did; // domain id

  if (num_threads > 1) {
    int thread_level; // threading level that MPI implementation provides
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &thread_level);
    assert(thread_level == MPI_THREAD_FUNNELED);
  } else
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Paritl_Init(dim,num_threads,MPI_COMM_WORLD);
  did = Paritl_Decompose(ROUND_ROBIN_ORDER, data_size, tot_blocks, &nblocks, 1, ghost, given, 0);
  Paritl_Read_data_all(did,infiles,kInt32,1,false);
  Paritl_ComputeHistogram(0,1000);
  Paritl_WriteHistogram("test");
  Paritl_Finalize();
  MPI_Finalize();
  return 0;
}