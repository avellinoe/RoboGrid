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

std::string path = "simulation.csv"; 
std::map<std::tuple<int,int>, std::string> grid; // Grid with {x,y} coordinates and contents of the cell
std::vector<string> contents = {"empty", "robot", "battery", "intruder"}; // Possible contents of a given cell

RoboGrid::RoboGrid(Robot& robot, std::string world) : Process(world), _world(world),_robot(robot) {
    
    //! The following will always run and be valid, regardless of what kind of world is chosen
    initscr();
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
    int rX = 1; //pos start x
    int rY = 1; //pos start y
    WINDOW *robotWin = newwin(25,50,rY,rX);
    box(robotWin,'|','-');
    wsyncup(robotWin);
    wrefresh(robotWin);
}

bool RoboGrid::robotTimer(high_resolution_clock::duration d){
        mvprintw(26,1,"timerval = %d:%02d", 
        std::chrono::duration_cast<std::chrono::seconds>(d).count()%60,
        (std::chrono::duration_cast<std::chrono::milliseconds>(d).count()%1000)/10
    );
    if ( _robot.isCleaning()){
        _timerVal = true;
    }
    return _timerVal;
}

void RoboGrid::addTrash(int x, int y){
    WINDOW *trashWin = newwin(1,1,y,x);

    waddch(trashWin,'*');
    wrefresh(trashWin);

        // wclear(trashWin);
        // wrefresh(trashWin);
}

void RoboGrid::update() {

    // USER INPUT
    // get a character from the user, if one is ready.
    // If no character is ready, getch() returns ERR (which is
    // ignored below since there is no condition in the switch statement)
    int ch,total,rnd,cx,cy;
    int robX = 2;
    int robY = 2;
    int numCoords = 0, trashbin = 0;
    //int pairs[]={0,0};
    int coordinates[25*50][2];
    WINDOW *robot = newwin(1,1,2,2);
    create_window();

    while((ch=getch())!='q'){
        switch ( ch ) {            
            case 'o':
                emit(Event("on"));
                break;
            case 'd':
                emit(Event("off"));
                
                clear(); // Clear the screen of old stuff
                break;
            case 'r':
                emit(Event("run"));
                break;
            case 's':
                emit(Event("stop"));
                break;
            case 'c':
                emit(Event("clean"));
                //timer start
                _moveRobot = true;
                break;
            case 't':
                //for(int i = 0; i < 2; i++){
                     rnd = rand() % (40*19);
                     cx = rnd % 40;
                     cy = rnd / 40;
                    while (cx<2 || cy < 2){
                        rnd = rand() % (40*19);
                        cx = rnd % 40;
                        cy = rnd / 40;
                    }
                    coordinates[numCoords][0] = cx;
                    coordinates[numCoords][1] = cy;
                    addTrash(cx,cy);
                    ++numCoords;
                //}
                break;
            //KEYBOARD, only move within window
            case KEY_LEFT: 
                if(robX > 2)  --robX;
                break;
            case KEY_RIGHT: 
                if(robX < 39) ++robX;
                break;
            case KEY_UP: 
                if(robY > 2)    --robY;
                break;
            case KEY_DOWN: 
                if(robY < 18)  ++robY;
                break;
        }

        if (_robot.isOn()){
            if(_moveRobot){
                wclear(robot);
                wrefresh(robot);
                waddch(robot,'R');
                mvwin(robot,robY,robX);
                for(int j = 0; j < sizeof(coordinates[0]); j++){
                    if(coordinates[j][0] == robX && coordinates[j][1] == robY){
                        mvprintw(21,1,"FOUND TRASH");
                        coordinates[j][0] = 0;// set to 0 so trashbin doesnt double count
                        coordinates[j][1] = 0;// set to 0 so trashbin doesnt double count
                        trashbin++;
                    }
                }
                if(numCoords == trashbin){
                    mvprintw(22,1,"DONE COLLECTING TRASH");
                    emit(Event("off"));
                }else{
                    mvprintw(22,1,"");
                }
            }else{
                waddch(robot,'R');
            }
            wrefresh(robot);
        }

        //take care of other stuff. 
        robotTimer(_robot.timeValue());
        mvprintw(30,1,"on(o), off(d), clean(c), add trash(t), quit(q)");
        for ( int i=0; i<_robot.addEvents().size(); i++ ) {
            mvprintw(24+i, 1, "Event: %s", _robot.addEvents()[i].c_str());
        }
    }
    //clear everything and return once q is hit
    if (ch=='q'){
        std::cout << "halting\n";
        halt();
    }
}