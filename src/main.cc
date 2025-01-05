#include "core.hpp"

function hi() {
    // $ errorCode = 404;
    // $ errorMessage = "Not Found";

    // console.log("Error {}: {}", errorCode, errorMessage);
    const int N = 10000000; // 10000000
    int sum = 0;
    std::mutex mu; // قفل برای دسترسی ایمن به sum

    #pragma omp parallel
    {
        #pragma omp single
        {
        // هر رشته یک متغیر محلی برای شمارش ایجاد می‌کند
        int local_sum = 0;

        // حلقه برای افزایش شمارش محلی
        for (int i = 0; i < N; i++) {
            local_sum++; // افزایش شمارش محلی
        }

        // قفل کردن برای دسترسی ایمن به sum
        mu.lock();
        sum += local_sum; // جمع کردن نتایج محلی به متغیر مشترک
        mu.unlock(); // آزاد کردن قفل
        }
    }

    std::cout << "مقدار نهایی: " << sum << std::endl;

}

int main() {
    try {
      hi();
    // const int N = 10000000;
    // int sum = 0;

    // #pragma omp parallel
    // {
    //     // فقط یک ترد کار جمع را انجام می‌دهد
    //     #pragma omp single
    //     {
    //         for (int i = 0; i < N; ++i) {
    //             // هر ترد یک تسک برای اضافه کردن 1 به sum ایجاد می‌کند
    //             #pragma omp task
    //             {
    //                 #pragma omp atomic
    //                 sum += 1; // اطمینان از ایمنی در دسترسی به sum
    //             }
    //         }
    //     }
    // }

    // #pragma omp taskwait

    // std::cout << "مقدار نهایی: " << sum << std::endl;

    // const int N = 1000000000;
    // int sum = 0;

    // #pragma omp parallel for reduction(+:sum)
    // for (int i = 0; i < N; ++i) {
    //     sum += 1;
    //     // std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    // #pragma omp taskwait
    
    // std::cout << "مقدار نهایی: " << sum << std::endl;
    
    } catch (const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
    return 0;
}
