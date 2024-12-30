// taskflow threads managers

// Go (silent async)
class Go {
public:
    Go() : executor(100) {}

    Go(const Go &) = delete;
    Go &operator=(const Go &) = delete;

    template<typename Func>
    Go &operator<<(Func &&func) {
        this->executor.silent_async(std::forward<Func>(func));
        return *this;
    }

    function waitAll() {
        this->executor.wait_for_all();
    }

private:
    tf::Executor executor;
};

// Async (future)
class Async {
public:
    Async() : executor(100) {}

    Async(const Async &) = delete;
    Async &operator=(const Async &) = delete;

    template<typename Func>
    auto operator<<(Func &&func) {
        auto future = this->executor.async(std::forward<Func>(func));
        return future;
    }

    function waitAll() {
        this->executor.wait_for_all();
    }

private:
    tf::Executor executor;
};

Async async;
Go go;
