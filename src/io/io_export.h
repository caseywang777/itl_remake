// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef IO_IO_EXPORT_H_
#define IO_IO_EXPORT_H_

#include "config.h"

/// Defines IO_EXPORT so that functionality implemented by
/// the io module can be exported to consumers.

#if defined(OS_WIN)
#define IO_EXPORT __declspec(dllexport)

#else  // defined(OS_WIN)
#define IO_EXPORT __attribute__((visibility("default")))
#endif

#endif  // IO_IO_EXPORT_H_
