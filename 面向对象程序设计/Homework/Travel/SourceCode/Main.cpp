/*
    FileName: Main.cpp
    Author: Ziteng Wang
    Date: 2020.04.05
*/

#include<iostream>
#include"Castle.h"
using namespace std;

/*
    Extern Variables
    Index: number of Visited Room
    Princess: Princess found or not
    Monster: Monster encountered or not
*/
int Index = 0;
bool Princess = false;
bool Monster = false;

                                     // Main Function
int main()
{
    cout << "Welcome to the Castle, brave Prince!!" <<endl;
    Room lobby(Index++, 'A', true);
    Room* current = &lobby;
    string direction;                //Record the input direction

    //Keep travling until player succeed or fail
    while(1)
    {
                                     //OUTPUT & INPUT
        (*current).displayinfo();    //Display the current Room information
        cin >> direction;            //Read in the target dir

                                     //Go to next room
        current = (*current).findexit(direction, current);

                                     //Judge if succeed or fail
        if(Monster)                  //Meet the monster
        {
            cout << "\nOh No, you encounter the Monster !!\n" << "Game Over." <<endl;
            break;
        }
        if(Princess && current == &lobby)   //Go back to the lobby
        {
            cout << "\nYou win! What a brave Prince!!" << endl;
            break;
        }
    }
    return 0;
}