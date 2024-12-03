#include <iostream>
#include <thread>
#include <functional>


void functionOne(char symbol) {
    for (int i = 0; i < 200; i++) {
        std::cout << symbol;
    }
}

void functionTwo() {
    for (int i = 0; i < 200; i++) {
        std::cout << "-";
    }
}

int main() {
    char tempChar = 'o';

    std::thread workerOne(functionOne, tempChar);
    // std::thread workerOne(std::bind(functionOne, std::ref(tempChar))); // this works as well if using older version of compiler
    std::thread workerTwo(functionTwo);

    /*
        Will result runtime error if join() is not used, main/current thread will
        complete its execution and the other thread created will be still running

        In this case, workerOne and workerTwo will still be running when main thread 
        finishes executing, resulting in an error

        join(): blocks the current thread until the joined thread finishes its execution
    */
    workerOne.join();
    workerTwo.join();

    std::cout << std::endl;
    return 0;
}