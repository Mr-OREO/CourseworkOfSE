#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

/*
    Define the data structure
    Store the input data with key information
    Using array
*/
typedef struct Student* PtrtoStu;
struct Student{
    string name;
    int score[3];
    double average;
};
Student Stu[10];                

/*  Function declaration
    
    InitData(): initialize the ".txt" file and UI
    Append(): output the new data set to ".txt" file
    Display(): show stored data in specific form
    Input(): read in new information

*/
bool InitData();
bool Append();
bool Display();
void Input();

/*
    Current amount of stored data
*/
int Count;


int main()
{
    int op;                 // operation index

    if(!InitData())
        return 0;

    /*
        Give the operations and call functions by order
        Keep working until enter '3'
    */
    while(1)
    {
        //Input
        cout << "Please choose an operation:\n" << endl;
        cout << "1: Display current data sets (current: "<< Count<< ")\n" << endl;
        cout << "2: Append a new data set\n" << endl;
        cout << "3: Terminate the program\n" << endl;
        cout << "Enter the index:";

        cin>>op;
        cout << endl;

        //switch to different functions
        switch(op)
        {
            case 1: 
                if(!Display())          //Error with Display
                    cout << "I meet some troubles...T_T" << endl;
                break;
            case 2:
                Input();
                break;
            case 3:
                cout << "Nice to meet you. ^_^\n Bye bye~" << endl;
                return 0;
            default:                    //Invalid input
                cout << "I can't recognize your input. T_T\nPlease try again." << endl;
                continue;
        }
    }
    return 0;
}

/*
    Initialize ".txt" file & UI
    Prepare the title of StuData
*/
bool InitData()
{
    ofstream File("StuData.txt");
    cout<<"\nWelcome to Mini_StuData !! May you have fun here (^_^)\n"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    cout<<" * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
    cout<<"              Designer: ZiTeng Wang"<<endl;
    cout<<"                    2020/03/05"<<endl;
    cout<<" * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
    cout<<"---------------------------------------------------------"<<endl;

    if(!File.is_open())             
    {                                   //File open error
        cout << "\"StuData.txt\" can't be opened. T_T" << endl;
        return 0;
    }
    else cout << "The program is now in great condition ! ^_^\n" << endl;
    
    File << "no\tname\tscore1\tscore2\tscore3\taverage" << endl;
    
    File.close();

    return 1;
}

/*
    Print the stored content in screen
    Calculate the average/min/max value in each column
*/
bool Display()
{
    string read;
    double sum, aver[3];
    int min[3], max[3];
    if(Count == 0)
        min[0] = min[1] = min[2] = 0;
    else min[0] = min[1] = min[2] = 10;
    memset(max, 0, 3*sizeof(int));
    ifstream File("StuData.txt");

    if(!File.is_open())                 //File open error
    {
        cout << "\"StuData.txt\" can't be opened. T_T\n" << endl;
        return 0;
    }

    while(getline(File, read))          //Read in every line and print it
    {
        cout << read << endl;
    }

    for(int i = 0; i < 3; i++)          //Calculate
    {
        sum = 0;
        for(int j = 0; j < Count; j++)
        {
            sum += Stu[j].score[i];
            if(Stu[j].score[i] > max[i])
                max[i] = Stu[j].score[i];
            if(Stu[j].score[i] < min[i])
                min[i] = Stu[j].score[i];
        }
        aver[i] = sum / (Count * 1.0);
    }

    cout << "\taverage\t" << aver[0] <<"\t"<<aver[1]<<"\t"<<aver[2] <<"\t"<<endl;
    cout << "\tmin\t" << min[0] <<"\t"<<min[1]<<"\t"<<min[2] <<"\t"<<endl;
    cout << "\tmax\t" << max[0] <<"\t"<<max[1]<<"\t"<<max[2] <<"\t"<<endl;
    cout<<endl;

    return 1;
}

/*
    Read in one student's information a time
    Judge if full data sets
    Stored the input in 'Stu' array
    Call the 'Append()' function to save the data
    Go on inputting for convenience
*/
void Input()
{
    char con = 'Y';
    while(con == 'Y')
    {
        if(Count == 10)
        {
            cout<<"There's already 10 students.T_T\n" << endl;
            cout << "( Typing any letter to continue... )" << endl;
            char c;
            cin >> c;
            cout << "\n" <<endl;
            return;
        }
        
        //Read input
        cout << "Please input a student's information" <<endl;
        cout << "name:";
        cin >> Stu[Count].name;
        cout << "score1:";
        cin >> Stu[Count].score[0];
        cout << "score2:";
        cin >> Stu[Count].score[1];
        cout << "score3:";
        cin >> Stu[Count].score[2];
        cout << endl;
        
        //Calculate the average value
        Stu[Count].average = (Stu[Count].score[0]+Stu[Count].score[1]+Stu[Count].score[2])/3.0;

        if(Append())
            cout<<"Success! ^_^\n"<<endl;
        else
            cout<<"Input unsuccessfully...T_T\n"<<endl;
        
        cout<<"Want to append another one ??"<<endl;
        cout<<"If Yes, input 'Y', otherwise 'N':"<<endl;
        cin>>con;
        cout<< endl;
    }
}

/*
    Write the new input into ".txt" file
    Keep the string format
*/
bool Append()
{
    ofstream File("Studata.txt",ios::app);

    if(!File.is_open())                     //File open error
    {
        return 0;
    }
    else
    {
        File << Count+1<<"\t" <<Stu[Count].name<<"\t" <<Stu[Count].score[0] <<"\t"<<Stu[Count].score[1] <<"\t"<<Stu[Count].score[2] <<"\t"<<setprecision(6)<<Stu[Count].average << endl;
        Count++;
    }
    
    File.close();
    return 1;
}
