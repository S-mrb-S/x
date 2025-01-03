#include "core.hpp"

function hi() {
    // $ errorCode = 404;
    // $ errorMessage = "Not Found";

    // console.log("Error {}: {}", errorCode, errorMessage);

    // for (size_t i = 0; i < 30; i++) {
    //     go >> lm {
    //         // task
    //         go >> lm {
    //             // task
    //             std::this_thread::sleep_for(std::chrono::seconds(1));
    //         };
    //     };
    // }

    // go.wait();
    const int N = 1000;
    #pragma omp parallel
    {
        // ایجاد تسک‌ها درون منطقه موازی
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            #pragma omp task
            {
                // هر تسک به مدت 1 ثانیه خواب می‌کند
                // std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }

    // منتظر ماندن برای اتمام همه تسک‌ها
    #pragma omp taskwait

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
