// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "extras/pyplot.h"

namespace itl {

void plot(const Histogram& hist) {
  PyObject *pName, *pModule, *pFunc, *pArgs;
  PyObject *pList, *pValue;

  Py_Initialize();

  pName = PyString_FromString("matplotlib.pyplot");
  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  size_t bn = hist.bins()->get_bin_number();
  pList = PyTuple_New(bn);
  for (size_t i = 0; i != bn; ++i) {
    pValue = PyInt_FromLong(hist.get_frequency(i));
    PyTuple_SetItem(pList, i, pValue);
    Py_DECREF(pValue);
  }

  pArgs = PyTuple_New(1);
  PyTuple_SetItem(pArgs, 0, pList);
  pFunc = PyObject_GetAttrString(pModule, "plot");
  PyObject_CallObject(pFunc, pArgs);
  Py_DECREF(pFunc);

  pFunc = PyObject_GetAttrString(pModule, "show");
  PyObject_CallObject(pFunc, pArgs);
  Py_DECREF(pFunc);

  Py_DECREF(pArgs);
  Py_DECREF(pList);
  Py_DECREF(pModule);

  Py_Finalize();
}

}  // namespace itl
