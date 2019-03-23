#ifndef _ELMA_ROBOT_RUN_H
#define _ELMA_ROBOT_RUN_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot;  // Declare containing class so it can be referred to here

    //! The Wander state of the robot
    class WanderState : public State {        

        public:
            WanderState() : State("wander") {};
            void entry(const Event& e) ;
            void during();
            void exit(const Event&);

            Robot& robot();
    };
}
#endif