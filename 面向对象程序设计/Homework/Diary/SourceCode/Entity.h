#ifndef ENTITY_H
#define ENTITY_H

#include<string>
#include<vector>
using namespace std;

class Entity
{
private:
    string date;
    vector<string> text;
public:
    ~Entity();

    void clear();
    void setdate(string);
    void addline(string);
    string getdate() const;
    string getline(unsigned int) const;
    int getsize() const;
    void show() const;
};

#endif