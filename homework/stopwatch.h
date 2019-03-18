#include <iostream>
#include <chrono>
#include "elma.h"
#include <chrono>

using namespace elma;
using namespace std::chrono;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

class Stopwatch : public Process {

    public:
        Stopwatch() : Process("Stopwatch") {}
        // Stopwatch() : Process("Stopwatch") {
        //     t1 = std::chrono::high_resolution_clock::now();
        // }

        void init();

        void start();
        void update();
        void stop();
        void reset();

        double seconds();

    private:
        bool isRunning = false;
        bool stopped = false;
        bool resetTriggered = false;
        
        seconds_type time_duration;
        std::chrono::high_resolution_clock::time_point t1 = high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point t2;
};