#ifndef _ELMA_ROBOT_EVADE_H
#define _ELMA_ROBOT_EVADE_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot;  // Declare containing class so it can be referred to here

    //! The Evade state of the robot
    class EvadeState : public State {        

        public:
            EvadeState() : State("evade") {};
            void entry(const Event& e) ;
            void during();
            void exit(const Event&);

            Robot& robot();
    };
}
#endif