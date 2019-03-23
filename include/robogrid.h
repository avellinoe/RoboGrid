#include <iostream>
#include <chrono>
#include <vector>
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

            //! Display the robot figure at the given x,y position on the screen
            void create_window();
            void addTrash(int x, int y);
            bool robotTimer(high_resolution_clock::duration d);

            //! Update the user interface by (a) reading keyboard input and (b) writing to the screen
            void update();
            void stop() {}

        private:

            Robot& _robot;
            std::string _world;
            bool _timerVal = false;
            bool _moveRobot = false;

            //! Simulation-only variables
            std::vector<std::tuple<int, std::string, int, int>> _commands;
    };

}