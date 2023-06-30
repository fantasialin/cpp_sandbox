#include <iostream>
#include <thread>
#include <mutex>
std::mutex mu; // our mutex object 
int balance = 0; // this is our shared resource
void deposit(int amount) 
{
    mu.lock(); // obtain a lock on the shared resource
        balance += amount; // this is the critical section
    mu.unlock(); // unlock the mutex
} 

int main()
{
    std::thread t1(deposit, 100);
    std::thread t2(deposit, 200);
    t1.join();
    t2.join();
    std::cout << balance << std::endl;
}
