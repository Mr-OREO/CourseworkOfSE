/*
    FileName: Castle.cpp
    Author: Ziteng Wang
    Date: 2020.04.05
*/

#include"Castle.h"
#include<iostream>
#include<time.h>
#include<stdlib.h> 
using namespace std;

extern int Index;
extern bool Princess;
extern bool Monster;

/*
    Constructor Func
    index1: room index
    type1: room type
    lobby: lobby or not
*/
Room::Room(int index1, char type1, bool lobby)
{
    index = index1;
    type = type1;
    if(lobby)
    {
        princess = false;
        monster = false;
    }
}

/*
    Destructor Func
    Called when the game end
*/
Room::~Room()
{
    if(Monster)
        cout << "\nYou can try again!" << endl;
    else
        cout << "\nYou Have Left the Castle!"<<endl;
}

/*
    Locate and return the next Room pointer
    dir: the direction player chose
    cur: current Room pointer
*/
Room* Room::findexit(string dir, Room* cur)
{
    //case 1: exist exit
    map<string, Room*>::iterator iter = exits.find(dir);
    if(iter!=exits.end())
        return iter->second;

    //case 2: allocate a new Room
    string backdir;
    if(dir == "left")   backdir="right";    //choose the  opposite dir
    else if(dir=="right")   backdir="left";
    else if(dir=="up")  backdir="down";
    else    backdir="up";

    Room* nroom = crtroom(backdir, cur);
    exits.insert(pair<string, Room*>(dir, nroom));
    if((*nroom).princess == 1)
        cout << "\n\nYou Find the Princess!!\n" << "Let's get out of here." << endl;
    return nroom;
}


/*
    Create an adjancent room
    bkdir: direction back to previous room
    bkrm: pointer to previous room
*/
Room* Room::crtroom(string bkdir, Room* bkrm)
{
    srand((unsigned)time(NULL));
    int num = rand()%4;
    int mst = rand()%10;     //Monster or none
    int prcs = rand()%4;    //Princess or none
    char type1;

    // make sure the back path available
    while(bkdir == "down" && num == 0)  num = rand()%4;
    while(bkdir == "left" && num == 1)   num = rand()%4;
    while(bkdir=="right" && num == 2)   num = rand()%4;
    while(bkdir=="up" && num == 3)  num = rand()%4;

    // initialise the roominfo
    switch(num)
    {
        case 0: type1 = 'A';break;  //up, l, r
        case 1: type1 = 'B';break;  //up, r, d
        case 2: type1 = 'C';break;  //up, l, d
        default: type1 = 'D';       //l, r, d
    }
    Room* nroom = new Room(Index++, type1, false);
    nroom->exits.insert(pair<string, Room*>(bkdir, bkrm));
    if(prcs == 0)
    {
        (*nroom).princess = 1;
        Princess = true;
    }
    if(mst == 0)
    {  
        (*nroom).monster = 1;
        Monster = 1;
    }
	return nroom;
}

/*
    Display the Room information and give the choices
*/
void Room::displayinfo()
{
    cout<<"\nWelcome to the "<<type<<index<<". There are "<<3<<" exits: ";

    // Gave the available dir_ choice
    switch(type)
    {
        case 'A':
            cout << "up, left and right.";
            break;
        case 'B':
            cout << "up, right and down.";
            break;
        case 'C':
            cout << "up, left and down.";
            break;
        default:
            cout << "left, right and down.";
    }
    cout << endl;
    cout << "Enter your command:";
}
