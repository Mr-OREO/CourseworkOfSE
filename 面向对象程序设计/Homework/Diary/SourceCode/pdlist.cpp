#include"Entity.h"
#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

vector<Entity> diary;   // Constituted by entities

// Declaration: File operation
// True: successful done
// False: ERROR
bool ReadinFile();      // Read
bool WritetoFile();     // Write

/*
Comparison function called by "sort"
e1: former
e2: latter
*/
int cmp(const Entity e1, const Entity e2)
{
    return e1.getdate()<e2.getdate();
}

/*
Processing function to list entities in order
d1: floor date
d2: ceiling date
*/
void ListDiary(string d1, string d2)
{
    unsigned int i, j, d_size;      // vector index

    // Tempary container
    vector<Entity> temp;
    temp.assign(diary.begin(), diary.end());    // Initialise
    d_size = temp.size();
    string date;

    // Select entities with date-limits
    for(i = 0; i < d_size; i++)
    {
        date = temp[i].getdate();
        if(date.compare(d1)==-1 || date.compare(d2)==1)
        {
            temp.erase(temp.begin()+i);     // Remove the entity 
			i--;        // Move left for changed orders
        }
        d_size = temp.size();               // Resize
    }

    // Sort left entities
    sort(temp.begin(), temp.end(), cmp);

    // Show contents
    d_size = temp.size();
    for(i = 0; i < d_size; i++)
    {
        temp[i].show();
    }
}

// __Main__
int main(int argc, char* argv[])
{
    // File Preparation
    bool in = ReadinFile();
    if(!in)
    {
        cout << "Read in ERROR" << endl;
        return 1;
    }

    // Initialise date-limits
    string dlow, dhigh;
    if(argc == 3)       // floor&ceiling given
    {
        dlow = argv[1];
        dhigh = argv[2];
    }
    else                // No limits
    {
        dlow = "0";
        dhigh = "9";
    }
    
    // Processing data
    ListDiary(dlow, dhigh);

    // Rewrite
    bool out = WritetoFile();
    if(!out)
    {
        cout << "Write out ERROR" << endl;
        return 1;
    }

    // Success
    return 0;
}

// Read in File "diary.txt" and store in diary(vector)
bool ReadinFile()
{
    // Temporary container
    Entity entity;
    string line;
    string date;
    entity.clear();

    // Open File
    ifstream infile("diary.txt");
    if(!infile.is_open())   // ERROR during file opening
    {
        return false;
    }

    while(!infile.eof())    // Check EOF(end of file) when reading content
    {
        // Read-in date
        getline(infile, date);
        entity.setdate(date);

        // Read-in a line
        getline(infile, line);
        while(line != ".")  // Verify if meet stop-sign "."
        {
            entity.addline(line);
            getline(infile, line);
        }
        diary.push_back(entity);    // Push in an entity
    }

    infile.close();         // Close file
    return true;            // Read-in successfully
}

// Rewrite the diary's content
bool WritetoFile()
{
    unsigned int i, j, d_size=diary.size(), e_size;     // Representing index of vectors
    
    // Open file && Check ERROR
    ofstream outfile("diary.txt");
    if(!outfile.is_open())
        return false;

    // Store diary(vector) into "diary.txt"
    for(i = 0; i < d_size; i++)     // For each entity
    {
        outfile << diary[i].getdate() << endl;      // 1.date
        e_size = diary[i].getsize();
        for(j = 0; j < e_size; j++)                 // 2.text
            outfile << diary[i].getline(j) << endl;
        if(i == d_size-1)                           // 3.stop-sign "."
            outfile << '.';
        else outfile << '.' << endl;
    }

    outfile.close();        // Close file
    return true;            // Reweite successfully
}