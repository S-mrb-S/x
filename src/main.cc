#include "core.hpp"

function hi() {
    $ errorCode = 404;
    $ errorMessage = "Not Found";

    console.error("Error {}: {}", errorCode, errorMessage);

    for (size_t i = 0; i < 30; i++) {
        go << []() {
            // task
            go << []() {
                // task
                std::this_thread::sleep_for(std::chrono::seconds(1));
            };
        };
    }

    // go.waitAll();

    $ result1 = async >> []() {
        std::cout << "Task 1\n";
        return 1;
    };

    $ result2 = async >> []() {
        std::cout << "Task 2\n";
        return 2;
    };

    async.await();

    std::cout << "Result 1: " << result1.get() << std::endl;
    std::cout << "Result 2: " << result2.get() << std::endl;
}

int main() {
    try {
        hi();
    } catch (const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
    return 0;
}
