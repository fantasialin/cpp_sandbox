#include <iostream>
#include <thread>
int main()
{
    // lambda
    auto fn = [](int i) {
        for (int ctr = i; ctr >= 0; ctr--)
            std::cout << ctr << " ";
        std::cout << "\n";
    };

    std::thread t1(fn, 10);
    t1.join(); 

    return 0;
}