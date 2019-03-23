#ifndef _ELMA_ROBOT_ON_H
#define _ELMA_ROBOT_ON_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot;    // Declare containing class so it can be referred to here

    //! The On state of the Robot
    class OnState : public State {

        public:
            OnState() : State("on") {};
            void entry(const Event& e) {};
            void during() {};
            void exit(const Event&);

            Robot& robot();
    };
}
#endif