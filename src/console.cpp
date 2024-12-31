// console class for log and save
class Console {
public:
    template<typename... Args>
    void out(std::ostream& out, const std::string_view format, Args&&... args) {
        fmt::print(out, "{}\n", fmt::vformat(format, fmt::make_format_args(std::forward<Args>(args)...)));
    }

    template<typename... Args>
    void error(std::string_view format, Args&&... args) {
        out(std::cerr, format, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void log(std::string_view format, Args&&... args) {
        out(std::cout, format, std::forward<Args>(args)...);
    }
};

Console console;
