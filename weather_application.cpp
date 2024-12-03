/* 
    Terminal Run Command: 
        $ g++ -std=c++14 weather_application.cpp -o weather_application
        $ ./weather_application
*/
#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <chrono>
using namespace std::chrono_literals; // Requires C++14 or newer compiler

void RefreshForcast(std::map<std::string, int> forcastMap) {
    while (true) {
        for (auto& item : forcastMap) {
            item.second++;
            std::cout << item.first << " - " << item.second << std::endl;
        }
        std::this_thread::sleep_for(2000ms);
    }
}

int main() {
    std::map<std::string, int> weatherForcastMap = {
        { "New York", 15 },
        { "Tokyo", 13 },
        { "Taipei", 20 },
        { "Seoul", 14 },
        { "Brisbane", 15 },
    };

    std::thread bgWorker(RefreshForcast, weatherForcastMap);

    bgWorker.join();
}
