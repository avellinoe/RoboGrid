#include <iostream>
#include <chrono>
#include "elma.h"
#include "stopwatch.h"

using namespace std::chrono;
using namespace elma;

    void Stopwatch::init() {
        watch("start", [this](Event& e) {
            start();
            isRunning = true;
        });
        watch("stop", [this](Event &e) {
            isRunning = false;
            stop();
        });
        watch("reset", [this](Event& e) {
            std::cout << "DEFAULT: 0\n";
            isRunning = false;
            reset();
        });
        // watch("reset", [this](Event& e) {
        //     std::cout << "PRIORITY: 2\n";
        // }, 2);
        // watch("reset", [this](Event& e) {
        //     std::cout << "PRIORITY: 55\n";
        // }, 55);
    }

    void Stopwatch::start() {
        if (isRunning) throw std::range_error("Stopwatch already running.\n");
        else {
            t1 = high_resolution_clock::now();
            resetTriggered = false;
            stopped = false;
        }
    }

    void Stopwatch::update() {
        t2 = high_resolution_clock::now();
        time_duration = t2 - t1;
    }

    void Stopwatch::stop() {
        if (stopped) throw std::range_error("Stopwatch already stopped.\n");
        else {
            // std::cout << "Stopped.\n";
            stopped = true;
            update();
        }
    }

    void Stopwatch::reset() {
        // std::cout << "Reset pressed.\n";
        resetTriggered = true;
    }

    double Stopwatch::seconds() {
        if (resetTriggered) {
            // std::cout << "Calling seconds() while reset is triggered.\n";
            time_duration = std::chrono::duration<double>::zero();
            auto value = std::chrono::duration_cast<std::chrono::nanoseconds> (time_duration);
            return value.count()/1000000000.0;

        } else if (stopped) {
            // std::cout << "Calling seconds() while stop is triggered.\n";
            auto value = std::chrono::duration_cast<std::chrono::nanoseconds> (time_duration);
            return value.count()/1000000000.0;

        } else {
            update();
            auto value = std::chrono::duration_cast<std::chrono::nanoseconds> (time_duration);
            return value.count()/1000000000.0;
        }
    }