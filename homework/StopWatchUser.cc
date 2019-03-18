#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace elma;

//double tolerance = 0.01;

/*
class stopwatchUser : public Process {
    public:
    stopwatchuser() : Process("stopwatchuser") {}

    void init() {}
    void start() {
        emit(Event("start"));
    }
    void update() { 
        //code about the stopwatch user using the stopwatch
    }
    void stop() {}
};

int main() {
    Manager m;
    stopwatchuser user("me");

    m.schedule(user, 1_ms)
     .schedule(q, 5_ms)
     .init()
     .run(11_ms);
}
*/