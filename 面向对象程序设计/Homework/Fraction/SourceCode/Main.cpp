/**************************************************************
 * File: Main.cpp
 * Author: Ziteng Wang
 * Date: 2020-05-11
 * Description: Main && Test-part
***************************************************************/

#include"Fraction.h"
using namespace std;

/**
 * Test function declaration
*/
void test();

/**
 * Main
*/
int main()
{
    test();

	system("pause");
    return 0;
}

/**
 * Test
 * Interface && Test
 * @Input[i1, i2, i3, i4]: 4 integers
 * @Input[int int]: test for stream inserter
*/
void test()
{
    int i1, i2, i3, i4;

    // Test default constructor
    cout << "==> Fn1: Default Ctor" << endl;
    Fraction f1;
    cout << "   Result: f1 = " << f1 << "\n" << endl;

    // Test constructor that takes 2 integers as parameters
    cout << "==> Fn2: Ctor takes 2 integers" << endl;
    cout << "   Type in 2 integers: ";
    cin >> i1 >> i2;
    Fraction f2(i1,i2);
    cout << "   Result: f2 = " << f2 << "\n" <<endl;

    // Another one
    cout << "   Type in Another 2 integers: ";
    cin >> i3 >> i4;
    Fraction f3(i3,i4);
    cout << "   Result: f3 = " << f3 << "\n" <<endl;

    // Test copy constructor
    cout << "==> Fn3: Copy Ctor" << endl;
    Fraction f4=f2;
    cout << "   Result(copy from f2): f4 = " << f4 << "\n" << endl;
    
    // Test 4 arithmetical operators
    cout << "==> Fn4: Arithmetical Operators" << endl;
    cout << "   For f2 and f3:" << endl;
    Fraction f5 = f2+f3;
    cout << "   " << f2 << " + "<< f3 <<" = " << f5 << endl;
    Fraction f6 = f2-f3;
    cout << "   " << f2 << " - "<< f3 <<" = " << f6 << endl;
    Fraction f7 = f2*f3;
    cout << "   " << f2 << " * "<< f3 <<" = " << f7 << endl;
    Fraction f8 = f2/f3;
    cout << "   " << f2 << " / "<< f3 <<" = " << f8 << "\n" << endl;

    // Test 6 relation operators
    cout << "==> Fn5: Relational Operators" << endl;
    cout << "   For f2 and f3:" << endl;
    // Fronter
    cout << "   " << f2 << " < " << f3 << ": ";
    // Result
    if(f2<f3)
        cout<< "True" << endl;
    else cout<< "False" << endl;

    cout << "   " << f2 << "<=" << f3 << ": ";
    if(f2<=f3)
        cout << "True" << endl;
    else cout << "False" << endl;

    cout << "   " << f2 << " == " << f3 << ": ";
    if(f2==f3)
        cout << "True" << endl;
    else cout << "False" << endl;

    cout << "   " << f2 << " != " << f3 << ": ";
    if(f2!=f3)
        cout << "True" << endl;
    else cout << "False" << endl;

    cout << "   " << f2 << " >= " << f3 << ": ";
    if(f2>=f3)
        cout << "True" << endl;
    else cout << "False" << endl;

    cout << "   " << f2 << " > " << f3 << ": ";
    if(f2>f3)
        cout << "True" << endl;
    else cout << "False" << endl;
    cout << endl;

    // Type cast
    // from Fraction to Double
    cout << "==> Fn6: Type Cast to Double" << endl;
    double fra_d2 = f2, fra_d3 = f3;
    cout << "   f2(double): "<< fra_d2<<endl;
    cout << "   f3(double): "<< fra_d3<< "\n" << endl;

    // from Fraction to string
    cout << "==> Fn7: Type Cast to String" << endl;
    string fra_str2 = f2, fra_str3 = f3;
    cout << "   f2(string): "<< fra_str2 << endl;
    cout << "   f3(string): "<< fra_str3 << "\n" << endl;

    // Test stream process
    // Extractor
    cout << "==> Fn8: Stream Extractor: " << endl;
    cout << "   cout: f2 = "<< f2 << "\n" << endl;

    // Insertor
	cout << "==> Fn9: Stream Inserter(form:a b): ";
    cin >> f4;
    cout << "   cin: f4 = " << f4 << "\n" << endl;

    // Test conversion from a finite decimal string
    string str;
	cout << "==> Fn10: Input a finite-decimal-string: ";
    cin >> str;
    f4.StrtoFra(str);
    cout << "   Conversion Result: f4 = " << f4 << "\n" << endl;

    cout << "Thanks for your testing" << endl;
}