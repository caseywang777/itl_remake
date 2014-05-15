// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef IO_CONSOLE_H_
#define IO_CONSOLE_H_

#include <iostream>

#include "io/io_export.h"

namespace itl {

class IO_EXPORT Console {
 public:
  template <typename Type>
  static void Log(const Type& msg) {
    std::cout << msg << std::endl;
  }

  template <typename Type, typename... Args>
  static void Log(const Type& msg, const Args&... rest);

  static void CLog(const char* format, ...);

  template <typename Type>
  static void Warn(const Type& msg) {
    std::cout << msg << std::endl;
  }

  template <typename Type, typename... Args>
  static void Warn(const Type& msg, const Args&... rest);

  static void CWarn(const char* format, ...);

  template <typename Type>
  static void Error(const Type& msg) {
    std::cerr << msg << std::endl;
    abort();
  }

  template <typename Type, typename... Args>
  static void Error(const Type& msg, const Args&... rest);

  static void CError(const char* format, ...);

 private:
  Console() = delete;
  ~Console() = delete;
  Console(const Console& rhs) = delete;
  Console& operator=(const Console& rhs) = delete;
};

template <typename Type, typename... Args>
void Console::Log(const Type& msg, const Args&... rest) {
  std::cout << msg << " ";
  Log(rest...);
}

template <typename Type, typename... Args>
void Console::Warn(const Type& msg, const Args&... rest) {
  std::cout << msg << " ";
  Warn(rest...);
}

template <typename Type, typename... Args>
void Console::Error(const Type& msg, const Args&... rest) {
  std::cerr << msg << " ";
  Error(rest...);
}

}  // namespace itl

#endif  // IO_CONSOLE_H_
