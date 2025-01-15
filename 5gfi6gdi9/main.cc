// #include "core.cxx"
//
// #define $run int main() {run(); return 0;}
//
// $ run() {
//     int num_threads = 40000;
//
// #pragma omp parallel
//     {
// #pragma omp for
//         for (int i = 0; i < num_threads; i++) {
// #pragma omp task
//             {
//                 // کار مورد نظر
//             }
//         }
//     }
//
//
//     // try {
//         // for (int i = 0; i < 100000; ++i) {
//         //
//         // }
//     // } catch (const std::runtime_error &e) {
//     //     std::cerr << "Runtime error: " << e.what() << std::endl;
//     //     return 0;
//     // }
//     // catch (...) {
//     //     std::cerr << "An unknown error occurred." << std::endl;
//     //     return 0;
//     // }
// }
//
// $run
// #include <taskflow/taskflow.hpp> // شامل کتابخانه Taskflow
#include <omp.h>
#include <iostream>

int main() {
    int num_threads = 1000000;
    int task_count = 0;

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < num_threads; i++) {
#pragma omp task
            {
                // کار واقعی
#pragma omp atomic
                task_count++;
            }
        }
    }

    std::cout << "Total tasks executed: " << task_count << std::endl;

    return 0;
}
