#include"Entity.h"
#include<iostream>
using namespace std;

// Dtor release memory
Entity::~Entity()
{
    text.clear();
    text.shrink_to_fit();
}

// Initialise
void Entity::clear()
{
    date.clear();
    text.clear();
}

// Set entity's date
// d: date information
void Entity::setdate(string d)
{
    date = d;
}

// Add a string to vector of the entity
// line: content to be pushed
void Entity::addline(string line)
{
    text.push_back(line);
}

// Get current date
string Entity::getdate() const
{
    return date;
}

// Get the size of storied text
int Entity::getsize() const
{
    return text.size();
}

// Return i_th line of thes text
// index: index of text(vector)
string Entity::getline(unsigned int index) const
{
    string str = text[index];
    return str;
}

// Show the content of entity
void Entity::show() const
{
    cout << date << endl;               // 1. date

    int textsize = text.size(); // Each line
    for(int i = 0; i < textsize; i++)   // 2. line(s)
    {
        cout << text[i] << endl;
    }
    cout << endl;                       // 3. end
}