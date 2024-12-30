# XCore
## Example
```C++
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

    $ result1 = async << []() {
        std::cout << "Task 1\n";
        return 1;
    };

    $ result2 = async << []() {
        std::cout << "Task 2\n";
        return 2;
    };

    async.waitAll();

    echo("Result 1: " << result1.get());
    echo("Result 2: " << result2.get());
}
```
### New Features

We're excited to introduce some fantastic new features to enhance your coding experience! These include `function`, `echo`, `go`, `async`, `console.log`, `console.error`, and variable support with `$`. Each of these features has been carefully optimized and thoroughly tested to ensure they work seamlessly for you.

#### Feature Explanations

- **`function`**: Functions are essential in programming, allowing you to encapsulate reusable blocks of code. They help organize your code, making it more modular and easier to maintain. You can define functions to perform specific tasks, which can be called multiple times throughout your code.

- **`echo`**: This is a popular language construct in PHP that outputs strings or variables directly to the screen. It's a simple yet powerful way to display information to users, making it a staple in PHP development.

- **`console.log`**: A widely used method in Node.js, `console.log` is invaluable for debugging. It allows you to print messages to the console, helping you track the flow of your application and identify issues quickly.

- **`console.error`**: Similar to `console.log`, this method is specifically designed for logging error messages. It helps you differentiate between regular log messages and errors, making it easier to spot problems in your code.

- **`go`**: In Go (Golang), the `go` keyword is used to initiate a goroutine, which is a lightweight thread managed by the Go runtime. This feature allows you to run functions concurrently, making your applications more efficient and responsive.

- **`async`**: This keyword in Node.js enables you to write asynchronous code, which is crucial for handling operations that take time, such as network requests. By using `async`, you can work with promises more easily, allowing your code to run smoothly without blocking the main thread.

- **`$`**: In PHP, the `$` symbol is used to denote variables. This syntax allows you to create dynamic data handling within your scripts, making it easy to store and manipulate information as needed.

#### Additional Notes

> **Important**: Please keep in mind that this source code is not standardized and may not be easily readable or understandable by others.
>
> **Friendly Reminder**: We encourage you not to attempt to standardize it. Embrace the uniqueness! :(
