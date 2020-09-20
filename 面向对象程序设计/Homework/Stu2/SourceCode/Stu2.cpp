#include<iostream>
//	#include<vector>
#include"Stu2.h"

//	Add a new stu's account
//	Initialise
void Student::AddStu(string name)
{
    Name = name;
    Numcourse = 0;
    AvgScore = 0;
    Sumscore = 0;
}

//	Update the stu's course information
void Student::AddCourse(string cname, int score)
{
    Course1 a;
    a.Cname = cname;
    a.Score = score;
    Courses.push_back(a);

    Sumscore += score;
    Numcourse++;
    AvgScore = Sumscore/(Numcourse*1.0);
}

//	Display students' information
//	Compare with headline
void Student::Display(Record CS, int no)
{
    vector<Course2> cs;
    int find = 0;
    //	Form
    cout << no << '\t' << Name << '\t';
    CS.Duplicate(cs);
	//	Traversal
    for(vector<Course2>::iterator j = cs.begin(); j != cs.end(); j++)
    {
        find = 0;
        for(vector<Course1>::iterator i = Courses.begin(); i != Courses.end(); i++)
        {
            if((*i).Cname == (*j).Cname)
            {
                cout << (*i).Score << '\t';
                find = 1;
                break;
            }
        }
        if(find)
            continue;
        else cout << "\t";
    }
    cout << endl;
}

//	Display the headline
//	Initialise table
void Record::Display1()
{
    cout << "no\t" << "Name\t";
    for(vector<Course2>::iterator i = Courses.begin(); i != Courses.end(); i++)
    {
        cout << (*i).Cname << '\t';
    }
    cout << endl;
}


//	Display the target value
//	Avg, Min, Max
void Record::Display2()
{
    cout << "\taverage\t";
    for(vector<Course2>::iterator i = Courses.begin(); i != Courses.end(); i++)
    {
        cout << (*i).Avg << '\t';
    }
    cout << endl;
    cout << "\tmin\t";
    for(vector<Course2>::iterator i = Courses.begin(); i != Courses.end(); i++)
    {
        cout << (*i).min << '\t';
    }
    cout << endl;
    cout << "\tmax\t";
    for(vector<Course2>::iterator i = Courses.begin(); i != Courses.end(); i++)
    {
        cout << (*i).max << '\t';
    }
    cout << endl;
}

//	Add course in summary
void Record::AddCourse(string cname, int score)
{
    //	Search for duplication
	for(vector<Course2>::iterator i = Courses.begin(); i != Courses.end(); i++)
    {
        if((*i).Cname == cname)
        {
            (*i).Numstu++;
            (*i).Sumscore += score;
            (*i).Avg = (*i).Sumscore / (*i).Numstu;
            if((*i).max<score)
                (*i).max = score;
            if((*i).min>score)
                (*i).min = score;
			//cout << (*i).max << '\t' << (*i).min;
            return;
        }
    }

	//	No duplication
    Numcourse++;
    Course2 a = *new Course2;
    a.max = score;
    a.min = score;
    a.Cname = cname;
    a.Numstu = 1;
    a.Avg = score;
    a.Sumscore = score;
    Courses.push_back(a);
}

//	Initialise
void Record::Init()
{
    Numcourse = 0;
}

//	Copy a sample to do the search work
void Record::Duplicate(vector<Course2>& cs2)
{
    cs2.assign(Courses.begin(), Courses.end());
}