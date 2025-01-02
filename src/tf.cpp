
// Silent async execution
class Go{
public:
    // Go() : TaskExecutor(200) {}

    // Shift left operator for silent async
    template<typename Func>
    $ &operator<<(Func &&func) {
        // executor.silent_async(std::forward<Func>(func));
        return *this;
    }

    $ waitAll() {
        // executor.wait_for_all();
    }
};

// Async execution with future
class Async{
public:
    // Async() : TaskExecutor(100) {}

    // Shift right operator for async
    template<typename Func>
    $ operator>>(Func &&func) {
        // return executor.async(std::forward<Func>(func));
    }
};

// Global instances
Async async;
Go go;
