#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <random>

constexpr auto MAX_NUM_ITS = 1000000;

// using random values to try to cut down on massive compiler optimizations
static std::random_device RAND_DEV;
static std::mt19937 RNG(RAND_DEV());
static std::uniform_int_distribution<std::mt19937::result_type> DIST11(0,10);

void CopyPtr(std::shared_ptr<int> myInt)
{
    // demonstrates that use_count increases with each copy
    std::cout << "In CopyPtr: ref count = " << myInt.use_count() << std::endl;
    std::shared_ptr<int> myCopyInt(myInt);
    std::cout << "In CopyPtr: ref count = " << myCopyInt.use_count() << std::endl;
}

void ReferencePtr(std::shared_ptr<int>& myInt)
{
    // reference count stays the same until a copy is made
    std::cout << "In ReferencePtr: ref count = " << myInt.use_count() << std::endl;
    std::shared_ptr<int> myCopyInt(myInt);
    std::cout << "In ReferencePtr: ref count = " << myCopyInt.use_count() << std::endl;
}

void MovePtr(std::shared_ptr<int>&& myInt)
{
    // demonstrates that use_count remains constant with each move
    std::cout << "In MovePtr: ref count = " << myInt.use_count() << std::endl;
    std::shared_ptr<int> myMovedInt(std::move(myInt));
    std::cout << "In MovePtr: ref count = " << myMovedInt.use_count() << std::endl;
}

int CopyPtrFastConst(std::shared_ptr<int> myInt)
{
    return 5 + *myInt;
}

int ReferencePtrFastConst(std::shared_ptr<int>& myInt)
{
    return 5 + *myInt;
}

int MovePtrFastConst(std::shared_ptr<int>&& myInt)
{
    return 5 + *myInt;
}

int CopyPtrFastRand(std::shared_ptr<int> myInt)
{
    return DIST11(RNG) + *myInt;
}

int ReferencePtrFastRand(std::shared_ptr<int>& myInt)
{
    return DIST11(RNG) + *myInt;
}

int MovePtrFastRand(std::shared_ptr<int>&& myInt)
{
    return DIST11(RNG) + *myInt;
}

void RunConstantFunctions(std::shared_ptr<int> myInt)
{
    std::cout << "\nIn constant funcs, ref count = " << myInt.use_count() << std::endl;
    // demonstrates speed of each function
    int sum = 0;

    // Copy pointer
    auto start = std::chrono::steady_clock::now();
    for (auto i=0; i<MAX_NUM_ITS; i++)
    {
        sum += CopyPtrFastConst(myInt);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> copyElapsed = end - start;
    std::cout << "CopyPtrConst sum = " << sum << ", took " << copyElapsed.count() << " seconds.\n";

    // pass pointer by reference
    sum = 0;
    start = std::chrono::steady_clock::now();
    for (auto i=0; i<MAX_NUM_ITS; i++)
    {
        sum += ReferencePtrFastConst(myInt);
    }
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> refElapsed = end - start;
    std::cout << "ReferencePtrConst sum = " << sum << ", took " << refElapsed.count() << " seconds.\n";

    // pass pointer using std::move
    sum = 0;
    start = std::chrono::steady_clock::now();
    for (auto i=0; i<MAX_NUM_ITS; i++)
    {
        sum += MovePtrFastConst(std::move(myInt));
    }
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> moveElapsed = end - start;
    std::cout << "MovePtrConst sum = " << sum << ", took " << moveElapsed.count() <<
        " seconds.\n";

    std::cout << "std::move vs pass by value: " << copyElapsed / moveElapsed << " times faster.\n";
    std::cout << "std::move vs pass by ref:   " << refElapsed / moveElapsed << " times faster.\n";
}

void RunRandomFunctions(std::shared_ptr<int> myInt)
{
    std::cout << "\nIn random funcs, ref count = " << myInt.use_count() << std::endl;
    // demonstrates speed of each function
    int sum = 0;

    // Copy pointer
    auto start = std::chrono::steady_clock::now();
    for (auto i=0; i<MAX_NUM_ITS; i++)
    {
        sum += CopyPtrFastRand(myInt);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> copyElapsed = end - start;
    std::cout << "CopyPtrRand sum = " << sum << ", took " << copyElapsed.count() << " seconds.\n";

    // pass pointer by reference
    sum = 0;
    start = std::chrono::steady_clock::now();
    for (auto i=0; i<MAX_NUM_ITS; i++)
    {
        sum += ReferencePtrFastRand(myInt);
    }
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> refElapsed = end - start;
    std::cout << "ReferencePtrRand sum = " << sum << ", took " << refElapsed.count() << " seconds.\n";

    // pass pointer using std::move
    sum = 0;
    start = std::chrono::steady_clock::now();
    for (auto i=0; i<MAX_NUM_ITS; i++)
    {
        sum += MovePtrFastRand(std::move(myInt));
    }
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> moveElapsed = end - start;
    std::cout << "MovePtrRand sum = " << sum << ", took " << moveElapsed.count() <<
        " seconds.\n";

    std::cout << "std::move vs pass by value: " << copyElapsed / moveElapsed << " times faster.\n";
    std::cout << "std::move vs pass by ref:   " << refElapsed / moveElapsed << " times faster.\n";
}

int main()
{
    // demonstrates how use counts are effected between copy and move
    std::shared_ptr<int> myInt = std::make_shared<int>(5);
    std::cout << "In main: ref count = " << myInt.use_count() << std::endl;
    CopyPtr(myInt);
    std::cout << "In main: ref count = " << myInt.use_count() << std::endl;
    ReferencePtr(myInt);
    std::cout << "In main: ref count = " << myInt.use_count() << std::endl;
    MovePtr(std::move(myInt));
    std::cout << "In main: ref count = " << myInt.use_count() << std::endl;

    // since myInt was moved to MovePtr and fell out of scope on return (was destroyed),
    // we have to reinitialize myInt
    myInt.reset();
    myInt = std::make_shared<int>(5);

    RunConstantFunctions(myInt);
    RunRandomFunctions(myInt);

    return 0;
}