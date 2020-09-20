#include<iostream>
#include"Stu2.h"

//	Declaration
void Init();

int main()
{
    vector<Student> Stu;			//Student vector
    vector<Course2> cs2;			//Course vector (for summary)
    Student stu;
    Record Course;
    int  score, numstu = 0, numcs;
    string stname, csname;			//Input string

	//	Initialise the welcome table & course
    Init();
    Course.Init();

	cin >> numstu;
    while(numstu-- > 0)
    {
		stu = *new Student;

		//	Read in stu information
		cin >> numcs;
        cin >> stname;
        stu.AddStu(stname);     //	Initialise stu

        //	Read in Course information
		while (numcs-- > 0)
		{
			cin >> csname;
			cin >> score;
			stu.AddCourse(csname, score);//update stu
			Course.AddCourse(csname, score);
		}
        Stu.push_back(stu);
    }

	//	Initialise table
	cout << endl;
	cout << "---------------------------------------------------------" << endl;
	//	Headline
    Course.Display1();
	int j = 1;
    for(vector<Student>::iterator i = Stu.begin(); i != Stu.end(); i++, j++)
    {
        (*i).Display(Course, j);
    }
	//	Finishline
    Course.Display2();
	cout << "---------------------------------------------------------" << endl;

	//	Stop the program
	char a;
	cin >> a;
    return 0;
}

//	Initialise the welcome table
void Init()
{
    cout<<"\nWelcome to Mini_StuData !! May you have fun here (^_^)\n"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    cout<<" * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
    cout<<"              Designer: ZiTeng Wang"<<endl;
    cout<<"                    2020/03/22"<<endl;
    cout<<" * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
}
