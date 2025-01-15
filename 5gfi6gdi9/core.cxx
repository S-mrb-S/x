#pragma once

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <iostream>
// #include <stdexcept>
// #include <string>
// #include <cmath>
// #include <memory> // C++11
// #include <any> // C++17
// #include <future> // C++11
// #include <utility>
// #include <functional>
// #include <chrono> // C++11
// #include <exception>
// #include <sstream>
// #include <format>
// #include <mutex>

#ifdef USE_FMT
#include <fmt/core.h>
#endif

// #ifdef USE_OPENMP
//#include <omp.h>
// #endif

#include <curl/curl.h>

// #include <string_view> // C++17
// #include <optional> // C++17
// #include <vector>
// #include <atomic>
// #include <unistd.h>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// auto macros

#define function inline __attribute__((always_inline)) auto
#define $ auto

#define elif else if
#define echo(x) std::cout << x << std::endl // printing to console
#define echo_err(x) std::cerr << x << std::endl // print error to console

#define lm []()
#define lma [&]()

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

template <typename... Args>
function rformat(const std::string_view content, Args &&...args)
{
#ifdef USE_FMT
    return fmt::format(fmt::runtime(content), std::forward<Args>(args)...);
#else
    return std::vformat(content, std::make_format_args(std::forward<Args>(args)...));
#endif
}

class Console
{
public:
    template <typename... Args>
    function error(const std::string_view format, Args &&...args) const -> $
    {
        $ fmt_res = rformat(format, std::forward<Args>(args)...);
#ifdef USE_FMT
        fmt::print(std::cerr, "{}\n", fmt_res);
#else
        echo_err(fmt_res);
#endif
    }

    template <typename... Args>
    function log(const std::string_view format, Args &&...args) const -> $
    {
        $ fmt_res = rformat(format, std::forward<Args>(args)...);
#ifdef USE_FMT
        fmt::print("{}\n", fmt_res);
#else
        echo(fmt_res);
#endif
    }
};

Console console;

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

