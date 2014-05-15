// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef GRAPHICS_GRAPHICS_EXPORT_H_
#define GRAPHICS_GRAPHICS_EXPORT_H_

#include "config.h"

/// Defines GRAPHICS_EXPORT so that functionality implemented by
/// the graphics module can be exported to consumers.

#if defined(OS_WIN)
#define GRAPHICS_EXPORT __declspec(dllexport)

#else  // defined(OS_WIN)
#define GRAPHICS_EXPORT __attribute__((visibility("default")))
#endif

#endif  // GRAPHICS_GRAPHICS_EXPORT_H_
