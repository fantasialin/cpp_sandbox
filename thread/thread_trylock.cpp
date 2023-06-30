#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
using namespace std;
mutex mu;
void print(void) {
    if (mu.try_lock() == false) {
        cout << "mutex is locked\n";
    }
    // critical code section
    else {
        cout << "mutex is unlocked\n";
        cout << "hello world\n";
        mu.unlock();
    }
}

int main() {
    mu.lock();

    thread t1(print);
    t1.detach();
    this_thread::sleep_for(std::chrono::seconds(3)); 
    mu.unlock();

    thread t2(print);
    t2.detach();
    this_thread::sleep_for(std::chrono::seconds(2));

}

