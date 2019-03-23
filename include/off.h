#ifndef _ELMA_ROBOT_OFF_H
#define _ELMA_ROBOT_OFF_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot; // Declare containing class so it can be referred to here

    //! The Off state of the robot
    class OffState : public State {

        public:
            OffState() : State("off") {};
            void entry(const Event& e) {};
            void during() {};
            void exit(const Event& e);

            Robot& robot();
    };
}
#endif