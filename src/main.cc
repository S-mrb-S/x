#include <iostream>
#include <stdexcept>
#include <string>
// #include <math.h>
// #include <memory>
// #include <any>
// #include <future>
// #include <thread>
// #include <utility>
// #include <vector>
// #include <map>
// #include <set>
// #include <type_traits>
// #include <functional>
// #include <chrono>
// #include <exception>
#include <fmt/core.h>
// #include <fmt/ostream.h>
#include <sstream>
// #include <taskflow/taskflow.hpp>

#define function inline __attribute__((always_inline)) auto
#define var auto
#define elif else if

// print
#define echo(x) std::cout << x << std::endl // printing to console

// int main()
// {
// tf::Executor executor;

//     for (size_t i = 0; i < 30000000; i++)
//     {
//         executor.silent_async([]() { executor.silent_async([]() { executor.silent_async([]() { executor.silent_async([]() { executor.silent_async([]() { executor.silent_async([](){}); }); }); }); }); });
//     }

//     executor.wait_for_all();
//     return 0;
// }

class Console
{
public:
    template <typename... Args>
    static void log(const std::string &format, Args &&...args)
    {
        fmt::print("{}\n", fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
    }

    template <typename... Args>
    static void error(const std::string &format, Args &&...args)
    {
        fmt::print(stderr, "{}\n", fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
    }
};

Console console;

function hi()
{
    var errorCode = 404;
    var errorMessage = "Not Found";

    console.error("Error {}: {}", errorCode, errorMessage);
}

int main()
{
    try
    {
        hi();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred." << std::endl;
    }
    return 0;
}
