#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include "robot.h"
#include <ncurses.h>

using namespace robot;

std::map<std::tuple<int,int>, std::string> grid; // Grid with {x,y} coordinates and contents of the cell
std::vector<string> contents = {"empty", "robot", "battery", "intruder"}; // Possible contents of a given cell

UserInterface::UserInterface(Robot& rob) : Process("user input"), _robot(rob) {
    initscr();
    keypad(stdscr, TRUE);
    timeout(1);  // Timeout for waiting for user input
    noecho();    // Do not echo user input to the screen
    curs_set(0); // Do not show the cursor
    refresh();
};

void UserInterface::create_window(){
    int rX = 1; //pos start x
    int rY = 1; //pos start y
    WINDOW *robotWin = newwin(19,40,rY,rX);
    box(robotWin,'|','-');
    wsyncup(robotWin);
    wrefresh(robotWin);
}

bool UserInterface::robotTimer(high_resolution_clock::duration d){
        mvprintw(20,1,"timerval = %d:%02d", 
        std::chrono::duration_cast<std::chrono::seconds>(d).count()%60,
        (std::chrono::duration_cast<std::chrono::milliseconds>(d).count()%1000)/10
    );
    if ( _robot.isCleaning()){
        _timerVal = true;
    }
    return _timerVal;
}

void UserInterface::addTrash(int x, int y){
    WINDOW *trashWin = newwin(1,1,y,x);

    waddch(trashWin,'*');
    wrefresh(trashWin);

        // wclear(trashWin);
        // wrefresh(trashWin);
}

void UserInterface::update() {

    // USER INPUT
    // get a character from the user, if one is ready.
    // If no character is ready, getch() returns ERR (which is
    // ignored below since there is no condition in the switch statement)
    int ch,total,rnd,cx,cy;
    int robX = 2;
    int robY = 2;
    int numCoords = 0, trashbin = 0;
    //int pairs[]={0,0};
    int coordinates[40*19][2];
    WINDOW *rob = newwin(1,1,2,2);
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
                wclear(rob);
                wrefresh(rob);
                waddch(rob,'R');
                mvwin(rob,robY,robX);
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
                waddch(rob,'R');
            }
            wrefresh(rob);
        }

        //take care of other stuff. 
        robotTimer(_robot.timeValue());
        mvprintw(23,1,"on(o), off(d), clean(c), add trash(t), quit(q)");
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