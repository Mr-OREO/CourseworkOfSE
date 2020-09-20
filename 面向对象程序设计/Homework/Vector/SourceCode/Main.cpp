/**
 * FileName: Main.cpp
 * Author: Ziteng Wang
 * Description: Main & Test Part
 * Date:2020-05-26
*/

#include"Vector.h"
#include"Vector.cpp"
using namespace std;

/**
 * Main Integration & Testing part
 * @exception [Input 2][Test4's input 'index1' are supposed to be non-negative and within size]
 * @return [int][0: Success]
*/
int main()
{
    Vector<int> v0(10), v1;     // Vector of class int: v0: Ctor(int), v1: Ctor()
    Vector<test> vt;            // Vector of class test: vt: Ctor();
    
    int index0, index1;         // Query index (input)
    test t0("class type");      // Construct an instance of class test

    cout << "Test0: Vector of type test\nvt.push_back(): t0" << endl;
    vt.push_back(t0);           // Vector<test>: push_back 'test' instance
    vt.Print();

    cout << "Test1: v1.push_back(): 1~10" << endl;
    for (int i = 0; i < 10; i++)
        v1.push_back(i);        // Vector<int>: push_back 1~10
    v1.Print();
    
    cout << "Test2: copy ctor\nv2 <- v1" << endl;
    Vector<int> v2 = v1;        // Copy Ctor
    v2.Print();

    cout << "Test3: operate[]\nPlease Input an Integer:" << endl;
    cin >> index0;
    cout << v1[index0] << "\n" << endl;     // operator[]

    cout << "Test4: v1.at()\nPlease Input an Integer:" << endl;
    cin >> index1;
    cout << v1.at(index1) << "\n" << endl;  // at()

    cout << "Test5: v1.empty()" << endl;
    if(v1.empty())
        cout << "True" << endl;             // empty
    else cout << "False" << endl;           // non-empty
	cout << endl;

    cout << "Test6: v1.clear()" << endl;
    v1.clear();
    v1.Print();

    cout << "Test7: v1.empty()" << endl;
    if(v1.empty())
        cout << "True" << endl;             // similiar
    else cout << "False" << endl;

    system("pause");
    return 0;
}