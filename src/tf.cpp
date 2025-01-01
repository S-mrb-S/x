// Base class for task execution
template<typename ExecutorType>
class TaskExecutor {
public:
    explicit TaskExecutor(size_t thread_count) : executor(thread_count) {}

    TaskExecutor(const TaskExecutor &) = delete;
    $ &operator=(const TaskExecutor &) = delete;

protected:
    ExecutorType executor;
};

// Silent async execution
class Go : public TaskExecutor<tf::Executor> {
public:
    Go() : TaskExecutor(200) {}

    // Shift left operator for silent async
    template<typename Func>
    $ &operator<<(Func &&func) {
        executor.silent_async(std::forward<Func>(func));
        return *this;
    }

    $ waitAll() {
        executor.wait_for_all();
    }
};

// Async execution with future
class Async : public TaskExecutor<tf::Executor> {
public:
    Async() : TaskExecutor(100) {}

    // Shift right operator for async
    template<typename Func>
    $ operator>>(Func &&func) {
        return executor.async(std::forward<Func>(func));
    }
};

// Global instances
Async async;
Go go;
