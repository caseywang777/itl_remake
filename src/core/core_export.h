// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_CORE_EXPORT_H_
#define CORE_CORE_EXPORT_H_

#include "config.h"

/// Defines CORE_EXPORT so that functionality implemented by
/// the core module can be exported to consumers.

#if defined(OS_WIN)
#define CORE_EXPORT __declspec(dllexport)

#else  // defined(OS_WIN)
#define CORE_EXPORT __attribute__((visibility("default")))
#endif

#endif  // CORE_CORE_EXPORT_H_
