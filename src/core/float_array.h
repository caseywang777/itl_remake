// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_FLOAT_ARRAY_H_
#define CORE_FLOAT_ARRAY_H_

#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT FloatArray : public internal::TypedArray<float> {};

}  // namespace itl

#endif  // CORE_FLOAT_ARRAY_H_
