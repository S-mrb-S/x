#include "core.cxx"

#define $run int main() {run(); return 0;}

$ run() {
    try {

    } catch (const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 0;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 0;
    }
}

$run
