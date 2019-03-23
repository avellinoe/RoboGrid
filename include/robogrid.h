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

            //! Create a new robot user interface using curses
            //! \param rob A reference to a robot object
            //! \param world A choice between a Real-time/User-Interacted or Simulated World
            RoboGrid(Robot& robot, std::string world);

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
    };

}