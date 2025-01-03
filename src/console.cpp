#pragma once
#include "core.hpp"

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
