#ifndef _ELMA_ROBOT_MAKENOISE_H
#define _ELMA_ROBOT_MAKENOISE_H

#include "robot.h"

namespace robot {

    using namespace std::chrono;
    using namespace elma;

    class Robot;  // Declare containing class so it can be referred to here

    //! The Makenoise state of the robot
    class MakeNoiseState : public State {

        public:
            MakeNoiseState() : State("makenoise") {};
            void entry(const Event& e) ;
            void during();
            void exit(const Event&);

            Robot& robot();
    };
}
#endif