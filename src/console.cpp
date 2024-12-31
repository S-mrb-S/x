// console class for log and save
class Console {
public:
    template<typename... Args>
    $ log(const std::string &format, Args &&... args) {
        fmt::print("{}\n", fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
    }

    template<typename... Args>
    $ error(const std::string &format, Args &&... args) {
        fmt::print(stderr, "{}\n", fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
    }
};

Console console;
