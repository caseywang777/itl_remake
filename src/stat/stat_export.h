// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef STAT_STAT_EXPORT_H_
#define STAT_STAT_EXPORT_H_

#include "config.h"

/// Defines STAT_EXPORT so that functionality implemented by
/// the stat module can be exported to consumers.

#if defined(OS_WIN)
#define STAT_EXPORT __declspec(dllexport)

#else  // defined(OS_WIN)
#define STAT_EXPORT __attribute__((visibility("default")))
#endif

#endif  // STAT_STAT_EXPORT_H_
