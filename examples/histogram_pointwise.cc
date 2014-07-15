#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

#include "core/basic_types.h"
#include "core/field.h"
#include "stat/histogram.h"
#include "stat/sampler.h"
#include "io/raw_reader.h"
#include "algorithm/hist.h"
#include "extras/pyplot.h"

using namespace std;
using namespace itl;

int main(int argc, char* argv[]) {
  RawReader* reader = new RawReader();
  reader->set_dimensions(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
  unique_ptr<Field> field(reader->LoadData({{argv[1], kDouble}}));

  shared_ptr<Bins> bins(new RegularBins(field->variable(0)->MinValue(),
                                        field->variable(0)->MaxValue(),
                                        256));

  int from[3] = {0, 0, 0}, to[3] = {10, 10, 10};
  Histogram hist = ComputeHistogram(field.get(), bins, from, to);
  hist.Normalize();

  cout << "Entropy is: " << hist.Entropy() << endl;

  double* sample = new double[1000];
  Sampler::Rejection(hist, 1.0, sample, sample + 1000);

  PyPlot(hist);

  return 0;
}
