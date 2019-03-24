#include <iostream>
#include <chrono>
#include <vector>
#include <tuple>
#include <string>
#include <ncurses.h>

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;
    using namespace robot;

    //! The RoboGrid class implements the User-Defined (Real vs. Simulated) RoboGrid behavior
    class RoboGrid : public Process {

        public:
    
            //! Default Constructor: New RoboGrid controlled by User via curses
            //! \param robot A reference to a robot object
            RoboGrid(Robot& robot);

            //! Secondary Constructor: New RoboGrid controlled by Simulation
            //! \param robot A reference to a robot object
            //! \param path Path to .csv file with commands for RoboGrid
            RoboGrid(Robot& robot, std::string path);

            void init() {}
            void start() {}

            //! Display the time at the given x,y position on the screen
            //void show_event(int x, int y, high_resolution_clock::duration d);

            //! Display functions
            void create_window();
            void displayStations();
            void print_robotInfo();
            void print_events();
            void print_userOptions();
            void displayIntruders();

            void addStations();
            void addIntruder();
            bool robotTimer(high_resolution_clock::duration d);
            
            //! Update the user interface by (a) reading keyboard input and (b) writing to the screen
            void update();
            void stop() {}

        private:

            Robot& _robot;
            std::string _world;
            bool _timerVal = false;
            high_resolution_clock::duration _saved;
            int lowBatteryThreshold = 35;
            int stations = 5;
            int wanderSteps = 5;

            //! Simulation-only variables
            std::vector<std::tuple<int, std::string, int, int>> _commands;

            // Variable for formatting
            int timerLine = 26;             // This is where the TimeElapsed Line starts in the window
            int robotInfoLine = 28;         // This is where the RobotInfo Line starts in the window
            int activatedLine = 30;         // "Activated"
            int wanderingLine = 31;         // "Activated"
            int makingnoiseLine = 32;       // "Activated"
            int evadingLine = 33;           // "Activated"
            int findingstationLine = 34;    // "Activated"
            int rechargingLine = 35;        // "Activated"
            int deadLine = 36;              // "Activated"
            int userOptionsLine = 38;       // This is where the UserOptions Line starts in the window
            int robotEventsLine = 41;       // This is where the RobotEvents Line starts in the window
            std::vector<std::tuple<int,int>> chargeStations;    // This is where the chargeStations are located
            std::vector<std::tuple<int,int>> intruders;         // This is where the intruders are located
            bool allStationsAdded = false;
            bool stationsDisplayed = false;
    };
}