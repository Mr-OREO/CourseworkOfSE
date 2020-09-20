/**************************************************************
 * File: Fraction.h
 * Author: Ziteng Wang
 * Date: 2020-05-11
 * Description: Fraction Class & Function declaration
***************************************************************/

#ifndef Fraction__h
#define Fraction__h

#include<string>
#include<iostream>
using namespace std;

/*
 * Description: Represent a Fraction like 2/3
*/
class Fraction
{
private:
    // numerator: eg. '2' in '2/3'
    int numerator;
    // denominator: eg. '3' in '2/3'
    int denominator;

public:
/*
* Constructor Declaration
*/
    // Default
    Fraction();

    // Ctor takes two integers as parameters
    Fraction(int, int);

    // Copy Ctor
    Fraction(const Fraction& fra);

    // Ctor takes a decimal-string as parameter
    Fraction(const string& str);

/*
* Function Declaration
*/
    // Reduction of a Fraction instance
    void simplify();

    // Find the Greatest-Common-Devisor between denominator and int(para)
    int gcd(int);

    // Conversion from a finite decimal string
    void StrtoFra(string);

    // Type Conversion
    operator double() const;
    operator string() const;

/*
* Friend Declaration
*/
    // Arithmetical Operator
    friend Fraction operator +(Fraction&, Fraction&);
    friend Fraction operator -(Fraction&);
    friend Fraction operator -(Fraction&, Fraction&);
    friend Fraction operator *(Fraction&, Fraction&);
    friend Fraction operator /(Fraction&, Fraction&);

    // Relation Operator
    friend bool operator <(Fraction&, Fraction&);
    friend bool operator <=(Fraction&, Fraction&);
    friend bool operator ==(Fraction&, Fraction&);
    friend bool operator !=(Fraction&, Fraction&);
    friend bool operator >=(Fraction&, Fraction&);
    friend bool operator >(Fraction&, Fraction&);

    // Stream
    friend istream& operator >>(istream&, Fraction&);
    friend ostream& operator <<(ostream&, Fraction);
};

// inserter and extractor for streams
istream& operator >>(istream&, Fraction&);
ostream& operator <<(ostream&, Fraction);

// arithmetical operators: + - * /
Fraction operator +(Fraction&, Fraction&);
Fraction operator -(Fraction&);
Fraction operator -(Fraction&, Fraction&);
Fraction operator *(Fraction&, Fraction&);
Fraction operator /(Fraction&, Fraction&);

// relational operators: < <= == != >= >
bool operator <(Fraction&, Fraction&);
bool operator <=(Fraction&, Fraction&);
bool operator ==(Fraction&, Fraction&);
bool operator !=(Fraction&, Fraction&);
bool operator >=(Fraction&, Fraction&);
bool operator >(Fraction&, Fraction&);

#endif