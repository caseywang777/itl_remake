// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include <sstream>

#include "extras/pyplot.h"

namespace itl {

void PyPlot(const Histogram& hist) {
  Py_Initialize();

  std::stringstream command;
  command << "pylab.plot([";
  size_t bn = hist.bins()->get_bin_number() - 1;
  for (size_t i = 0; i != bn; ++i) {
    command << hist.get_frequency(i);
    command << ", ";
  }
  command << hist.get_frequency(bn);
  command << "])";

  PyRun_SimpleString("import pylab");
  PyRun_SimpleString(command.str().c_str());
  PyRun_SimpleString("pylab.show()");

  Py_Finalize();
}

void PyPlot(const double* data, size_t size) {
  Py_Initialize();

  std::stringstream command;
  command << "pylab.plot([";
  size--;
  for (size_t i = 0; i != size; ++i) {
    command << data[i];
    command << ", ";
  }
  command << data[size];
  command << "])";

  PyRun_SimpleString("import pylab");
  PyRun_SimpleString(command.str().c_str());
  PyRun_SimpleString("pylab.show()");

  Py_Finalize();
}

}  // namespace itl
