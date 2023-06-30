#include <iostream>
#include <thread>
#include <mutex>
std::mutex m1, m2; // our mutex objects 
int balance = 500; // this is our shared resource
void deposit(int amount) 
{
    int ret = std::try_lock(m1, m2);
    if (ret == 0) {
        std::cout << "resource m1 is locked\n";
    } 
    else if (ret == 1) {
        std::cout << "resource m2 is locked\n";
    }
    else {
        std::cout << "resource m1 and m2 not locked\n";
        // this is the critical code section
        balance += amount;
        std::cout << "critical section processed" << std::endl;
        m1.unlock();
        m2.unlock();
    } 
} 

int main()
{
    std::cout << "balance: " << balance << std::endl;
    m2.lock();
    m1.lock();
    std::thread t1(deposit, 100);
    std::thread t2(deposit, 200);
    t1.join();
    t2.join();
    m1.unlock();
    m2.unlock();
    std::thread t3(deposit, 100);
    t3.join();
    std::thread t4(deposit, 200);
    t4.join();
    std::cout << "balance: " << balance << std::endl;
}
