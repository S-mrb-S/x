// console class for log and save

/**
 * Run time format in fmt
 * @tparam Args
 * @param content
 * @param args
 * @return
 */
template<typename... Args>
function rformat(const std::string_view content, Args &&... args) {
    return fmt::format(fmt::runtime(content), std::forward<Args>(args)...);
}

/**
 * Console class
 */
class Console {
public:
    /**
     * Error log in fmt (unbuffered)
     * @tparam Args
     * @param format
     * @param args
     * @return
     */
    template<typename... Args>
    function error(const std::string_view format, Args &&... args) const -> $ {
        fmt::print(std::cerr, "{}\n", rformat(format, std::forward<Args>(args)...));
    }

    /**
     * normal log in fmt
     * @tparam Args
     * @param format
     * @param args
     * @return
     */
    template<typename... Args>
    function log(const std::string_view format, Args &&... args) const -> $ {
        fmt::print("{}\n", rformat(format, std::forward<Args>(args)...));
    }
};

Console console;
