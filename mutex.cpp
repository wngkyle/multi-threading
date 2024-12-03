/* 
    Terminal Run Command: 
        $ g++ -std=c++14 mutex.cpp -o mutex
        $ ./mutex
*/
#include <iostream>
#include <thread> 
#include <mutex>
using namespace std;

mutex carMutex;

/*
    unique_lock()
        - An object that manages a mutex object with unique ownership in both states: locked and unlocked
        - Need to unlock manually
        - Can be used to defer locking and unlock anytime you want


    lock_gaurd():
        - An object that manages a mutex object by keeping it always locked
        - Lock the critical section at the line it is placed, automatically unlocked when the lock_guard object goes out of scope 
        - Cannot be unlocked manually
        - Use lock_guard when you have a small and well-defined block of code
*/

void driveCar(string driverName) {
    // unique_lock<mutex> carLock(carMutex);
    lock_guard<mutex> carLock(carMutex);
    cout << driverName << " is driving" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << driverName << " is done driving" << endl;
    // carLock.unlock();
}

int main() {
    thread t1(driveCar, "Elon");
    thread t2(driveCar, "Jeff");

    t1.join();
    t2.join();
}