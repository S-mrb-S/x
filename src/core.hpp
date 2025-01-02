#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <memory> // C++11
#include <any> // C++17
#include <future> // C++11
#include <utility>
#include <functional>
#include <chrono> // C++11
#include <exception>
#include <sstream>

#ifdef USE_FMT
#include <fmt/core.h>
#endif

#ifdef USE_OPENMP
#include <omp.h>
#endif

#include <string_view> // C++17
#include <optional> // C++17
#include <vector>
#include <atomic>
#include <unistd.h>

// local modules
#include "core.cpp"
#include "console.cpp"
#include "tf.cpp"
