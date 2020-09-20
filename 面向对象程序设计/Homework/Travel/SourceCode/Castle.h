/*
    FileName: Castle.h
    Author: Ziteng Wang
    Date: 2020.04.05
*/

#ifndef CASTLE_H            //Protection
#define CASTLE_H

#include<string>
#include<map>
using namespace std;

// Class declaration
class Room{
    public:
        Room(int index1, char type1, bool lobby);   // Ctor
        ~Room();                                    // Dtor
    
    private:
        int index;          // room number
        char type;          // room type
        map<string,Room*> exits;    // mapping dir_ with exit
        bool princess;      // princess inside or not
        bool monster;       // monster inside or not
    
    public:
        Room* findexit(string dir, Room* cur);      // move to next room
        void displayinfo();                         // show room information
        Room* crtroom(string bkdir, Room* bkrm);    // create new room
};

#endif