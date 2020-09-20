//Protection
#ifndef Stu__H
#define Stu__H

#include<vector>
#include<string>
using namespace std;

//Student struct
struct Course1{
    string Cname;
    int Score;
};

//Record struct
struct Course2{
    string Cname;
    double Sumscore;		//sum of scores
    int Numstu;				//number of students in course
    int min;
    int max;
    double Avg;				//average score for this course
};

//Single is used
class Record
{
    private:
        vector<Course2> Courses;
        int Numcourse;

    public:
        void Init();
        void AddCourse(string cname, int score);
        void Duplicate(vector<Course2>& cs2);
        void Display1();
        void Display2();
};

//implemented by vector, including intern vector as 2-dimension
class Student
{
    private:
        string Name;
        vector<Course1> Courses;
        int Sumscore;		//sum of stu's scores
        int Numcourse;		//number of choosen courses
        double AvgScore;

    public:
        void AddStu(string name);
        void AddCourse(string cname, int score);
        void Display(Record CS, int no);
};

#endif