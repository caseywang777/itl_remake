#include <iostream>
#include <sstream>
#include <memory>

#include "core/basic_types.h"
#include "core/field.h"
#include "stat/histogram.h"
#include "io/raw_reader.h"
#include "algorithm/hist.h"
#include "algorithm/entropy.h"

using namespace std;
using namespace itl;

int main(int argc, char* argv[]) {
  RawReader* reader = new RawReader(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
  unique_ptr<Field> field(reader->LoadData({{argv[1], kFloat}}));

  int from[3], to[3];
  from[0] = atoi(argv[5]);
  from[1] = atoi(argv[6]);
  from[2] = atoi(argv[7]);
  to[0] = atoi(argv[8]);
  to[1] = atoi(argv[9]);
  to[2] = atoi(argv[10]);

  shared_ptr<Bins> bins(new RegularBins(field->variable(0)->MinValue(),
                                        field->variable(0)->MaxValue(),
                                        128));

  Histogram hist = ComputeHistogram(field.get(), bins, from, to);
  hist.Normalize();

  stringstream ss;

  for (size_t i = 0; i < 128; i++) {
    ss.str("");
    ss << hist.bins()->get_bin_center(i);
    cout << ss.str() << "\t" << hist.get_frequency(i) << endl;
  }

  return 0;
}
