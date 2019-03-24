#include <unistd.h>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include "robot.h"
#include "utilities.h"

using namespace robot;

std::map<std::tuple<int,int>, std::string> grid; // Grid with {x,y} coordinates and contents of the cell
std::vector<string> contents = {"empty", "robot", "battery", "intruder"}; // Possible contents of a given cell

// Grid variables
int now_occupied = 0;
static int x_max = 50; int y_max = 25;
static int total_coord = x_max * y_max;
int coordinates[1250][2]; // Two columns for x,y

RoboGrid::RoboGrid(Robot& robot) : Process("User-in-control"), _world("user"),_robot(robot) {
    
    //! The following will always run and be valid, regardless of what kind of world is chosen
    initscr();              // Start up curses
    keypad(stdscr, TRUE);   // Enables the keypad of the user's terminal.
                            // If enabled (TRUE), the user can press a function key (such as an arrow key),
                            // wgetch returns a single value representing the function key, as in KEY_LEFT.
    
    timeout(1);     // Timeout for waiting for user input
    noecho();       // Hide user input
    curs_set(0);    // Hide the cursor
    refresh();      // Must be called to get actual output to the terminal,
                    // as other routines merely manipulate data structures.
};

RoboGrid::RoboGrid(Robot& robot, std::string path) : Process("Simulation"), _world("sim"),_robot(robot) {
    _commands = read_simulation_csv(path);

    //! The following will always run and be valid, regardless of what kind of world is chosen
    initscr();              // Start up curses
    keypad(stdscr, TRUE);   // Enables the keypad of the user's terminal.
                            // If enabled (TRUE), the user can press a function key (such as an arrow key),
                            // wgetch returns a single value representing the function key, as in KEY_LEFT.
    
    timeout(1);     // Timeout for waiting for user input
    noecho();       // Hide user input
    curs_set(0);    // Hide the cursor
    refresh();      // Must be called to get actual output to the terminal,
                    // as other routines merely manipulate data structures.
};

void RoboGrid::create_window() {
    int rX = 0; //pos start x
    int rY = 0; //pos start y
    WINDOW *robotWin = newwin(y_max,x_max,rY,rX);
    box(robotWin,'|','-');
    wsyncup(robotWin);
    wrefresh(robotWin);
}

void RoboGrid::print_robotInfo() {
    mvprintw(robotInfoLine,1,"Robot Info:");

    if (_robot._battery >= lowBatteryThreshold) {
        mvprintw(robotInfoLine+1,5,"Battery:");
        
    } else {
        mvprintw(robotInfoLine+1,5,"LOW BATTERY:");
    }
    mvprintw(robotInfoLine+1,22,"%%");
    mvprintw(robotInfoLine+1,24,"%i", _robot._battery);
    
    mvprintw(robotInfoLine+2,5,"Activated:");
        if (_robot._activated) mvprintw(activatedLine,22,"TRUE!");
        else mvprintw(activatedLine,22,"FALSE");

    mvprintw(robotInfoLine+3,5,"Wandering:");
        if (_robot._wandering) mvprintw(wanderingLine,22,"TRUE!");
        else mvprintw(wanderingLine,22,"FALSE");

    mvprintw(robotInfoLine+4,5,"Making Noise:");
        if (_robot._makingnoise) mvprintw(makingnoiseLine,22,"TRUE!");
        else mvprintw(makingnoiseLine,22,"FALSE");

    mvprintw(robotInfoLine+5,5,"Evading:");
        if (_robot._evading) mvprintw(evadingLine,22,"TRUE!");
        else mvprintw(evadingLine,22,"FALSE");

    mvprintw(robotInfoLine+6,5,"Finding Station:");
        if (_robot._findingstation) mvprintw(findingstationLine,22,"TRUE!");
        else mvprintw(findingstationLine,22,"FALSE");

    mvprintw(robotInfoLine+7,5,"Recharging:");
        if (_robot._recharging) mvprintw(rechargingLine,22,"TRUE!");
        else mvprintw(rechargingLine,22,"FALSE");
    
    mvprintw(robotInfoLine+8,5,"Dead:");
        if (_robot._dead) mvprintw(deadLine,22,"TRUE!");
        else mvprintw(deadLine,22,"FALSE");
}

void RoboGrid::print_userOptions() {

    if (_robot._activated){
        if(_robot._wandering) {
            mvprintw(userOptionsLine,1,"User options available: find_station[f] off[x] quit[q]");
        } else {
            mvprintw(userOptionsLine,1,"User options available: wander[w] add_intruder[a] off[x] quit[q]");
        }
    } else {
        mvprintw(userOptionsLine,1,"User options available: on[o] quit[q]");
    }
}

void RoboGrid::print_events() {
    for ( int i=0; i<_robot.addEvents().size(); i++ ) {
        mvprintw(robotEventsLine+i, 1, "Event: %s", _robot.addEvents()[i].c_str());
    }
}

bool RoboGrid::robotTimer(high_resolution_clock::duration d) {
    if( _robot.wandering()) {
        _saved = d;
        mvprintw(timerLine,1,"Time elapsed = %d:%02d", 
            std::chrono::duration_cast<std::chrono::seconds>(d).count() % 60,
            (std::chrono::duration_cast<std::chrono::milliseconds>(d).count() % 1000)/10
        );
        _timerVal = true;

    } else {
        mvprintw(timerLine,1,"Time elapsed = %d:%02d", 
        std::chrono::duration_cast<std::chrono::seconds>(_saved).count()%60,
        (std::chrono::duration_cast<std::chrono::milliseconds>(_saved).count()%1000)/10
        );
    }
    return _timerVal;
}

void RoboGrid::addStations() {
    int i = 0, rnd, cx, cy;;
    std::tuple<int,int> xy;
    while (i < stations) {
        rnd = rand() % (total_coord);
        cx = rnd % x_max;
        cy = rnd / x_max;
        while (cx < 2 || cy < 2) { // Repeat if coordinates are out of bounds
            rnd = rand() % (total_coord);
            cx = rnd % x_max;
            cy = rnd / x_max;
        }
        coordinates[now_occupied][0] = cx;
        coordinates[now_occupied][1] = cy;
        get<0>(xy) = cx;
        get<1>(xy) = cy;
        chargeStations.push_back(xy);
        now_occupied++;
        i++;
    }
    allStationsAdded = true;
}

void RoboGrid::displayStations() {
    int x, y;
    for (auto const& coordpairs: chargeStations) {
        x = get<0>(coordpairs);
        y = get<1>(coordpairs);
        WINDOW *stationsWindow = newwin(1,1,y,x);
        waddch(stationsWindow,'%');
        wrefresh(stationsWindow);
    }
    stationsDisplayed = true;
}

void RoboGrid::addIntruder() {}
//     int i = 0, rnd, cx, cy;
//     bool already_occupied = true;
//     std::tuple<int,int> xy;
//     rnd = rand() % (y_max * x_max);
//     cx = rnd % x_max;
//     cy = rnd / x_max;
    
//     while (already_occupied) { // Repeat if cell is already occupied
//         already_occupied = false;
//         for (auto const& coordpairs: chargeStations) {
//             if (cx == get<0>(coordpairs) && cy == get<1>(coordpairs)) {
//                 already_occupied = true;
//             }
//         }
//         rnd = rand() % (total_coord);
//         cx = rnd % x_max;
//         cy = rnd / x_max;
//     }
//     coordinates[now_occupied][0] = cx;
//     coordinates[now_occupied][1] = cy;
//     get<0>(xy) = cx;
//     get<1>(xy) = cy;
//     intruders.push_back(xy);
//     now_occupied++;
// }

void RoboGrid::displayIntruders() {}
//     int x, y;
//     for (auto const& coordpairs: intruders) {
//         x = get<0>(coordpairs);
//         y = get<1>(coordpairs);
//         WINDOW *intrudersWindow = newwin(1,1,y,x);
//         waddch(intrudersWindow,'@');
//         wrefresh(intrudersWindow);
//     }
// }

void RoboGrid::update() {

    int ch,total;
    int robX = 1,robY = 1;
    WINDOW *robotWindow = newwin(1,1,2,2);
    create_window();

    while((ch=getch())!='q') {
        switch ( ch ) {            
            case 'o':
                if (_robot._activated) break;
                else {
                    emit(Event("on"));
                    create_window();
                    robotWindow = newwin(1,1,2,2);
                    if (!allStationsAdded) addStations();
                    if (!stationsDisplayed) displayStations();
                    break;
                }

            case 'x':
                emit(Event("off"));
                clear(); // Clear screen
                break;

            case 'w':
                emit(Event("wander"));
                mvprintw(robotEventsLine+1,1,"Robot will wander for %i steps", wanderSteps);
                for (int j = 0; j < wanderSteps; j++) {

                    int rndx = rand() % 2;
                    if (rndx == 0) {
                        robX = robX;
                    } else if (rndx == 1) {
                        robX++;
                    } else {
                        robX--;
                    }

                    int rndy = rand() % 2;
                    if (rndy == 0) {
                        robY = robY;
                    } else if (rndy == 1) {
                        robY++;
                    } else {
                        robY--;
                    }

                    _robot._battery--;
                    wclear(robotWindow);
                    wrefresh(robotWindow);
                    waddch(robotWindow,'R');
                    mvwin(robotWindow,robY,robX);
                    wrefresh(robotWindow);
                }
                break;

            case 'f':
                emit(Event("findstation"));
                break;

            case 'a':
                addIntruder();
                displayIntruders();
                break;
        }

        // Printing info
        robotTimer(_robot.timeValue());
        print_robotInfo();
        print_userOptions();
        print_events();
    } // End of while loop
    
    // Clear all and exit when user enters 'q'
    if (ch=='q'){
        std::cout << "halting\n";
        halt();
    }
}