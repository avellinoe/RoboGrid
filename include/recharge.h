#ifndef _ELMA_ROBOT_RECHARGE_H
#define _ELMA_ROBOT_RECHARGE_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot;  // Declare containing class so it can be referred to here

    //! The Recharge state of the robot
    class RechargeState : public State {

        public:
            RechargeState() : State("findstation") {};
            void entry(const Event& e) ;
            void during();
            void exit(const Event&);

            Robot& robot();
    };
}
#endif