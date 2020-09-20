#include"Entity.h"
#include<iostream>
#include<fstream>

using namespace std;

vector<Entity> diary;   // Constituted by entities

// Declaration: File operation
// True: successful done
// False: ERROR
bool ReadinFile();      // Read
bool WritetoFile();     // Write

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

    unsigned int size = diary.size(), i=0;  // Act as vector's index
    string date = argv[1], line;            // Temprary container
    Entity entity;

    entity.clear();         // Initialise
    entity.setdate(date);

    // Read in from CMD
    for(int j = 2; j < argc-1; j++)
    {
        line = argv[j];
        entity.addline(line);
    }

    // Check duplication
    for(i = 0; i < size; i++)
        if(diary[i].getdate()==date)
            break;

    // Break --> find duplication
    if(i!=size) // Replace
    {
        diary[i] = entity;
        cout << "Successful Replacement" << endl;
    }
    else        // Append
    {
        diary.push_back(entity);
        cout << "Successful Addition" << endl;
    }
    
    // Rewrite after processing
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