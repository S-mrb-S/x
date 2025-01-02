#include "core.hpp"

// function hi() {
//     $ errorCode = 404;
//     $ errorMessage = "Not Found";
//
//     console.log("Error {}: {}", errorCode, errorMessage);
//
//     for (size_t i = 0; i < 30; i++) {
//         go << lm {
//             // task
//             // go << lm {
//             //     // task
//             //     // std::this_thread::sleep_for(std::chrono::seconds(1));
//             // };
//         };
//     }
//
//     go.waitAll();
//
//     $ result1 = async >> lm {
//         console.log("Task 1");
//         return 1;
//     };
//
//     $ result2 = async >> lm {
//         console.log("Task 2");
//         return 2;
//     };
//
//     result2.wait();
//
//     console.log("Result 1: {}", result1.get());
//     console.log("Result 2: {}", result2.get());
// }

function hi() {

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
