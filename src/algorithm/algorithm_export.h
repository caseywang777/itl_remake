// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef ALGORITHM_ALGORITHM_EXPORT_H_
#define ALGORITHM_ALGORITHM_EXPORT_H_

#include "config.h"

/// Defines ALGORITHM_EXPORT so that functionality implemented by
/// the algorithm module can be exported to consumers.

#if defined(OS_WIN)
#define ALGORITHM_EXPORT __declspec(dllexport)

#else  // defined(OS_WIN)
#define ALGORITHM_EXPORT __attribute__((visibility("default")))
#endif

#endif  // ALGORITHM_ALGORITHM_EXPORT_H_
