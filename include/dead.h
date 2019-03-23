#ifndef _ELMA_ROBOT_DEAD_H
#define _ELMA_ROBOT_DEAD_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot;  // Declare containing class so it can be referred to here

    //! The Dead state of the robot
    class DeadState : public State {

        public:
            DeadState() : State("dead") {};
            void entry(const Event& e) ;
            void during();
            void exit(const Event&);

            Robot& robot();
    };
}
#endif