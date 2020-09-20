/**************************************************************
 * File: Fraction.cpp
 * Author: Ziteng Wang
 * Date: 2020-05-11
 * Description: Function Implement
***************************************************************/

#include"Fraction.h"
#include<cmath>
using namespace std;

/**
 * Default Ctor
 * Initialise the fraction to 1/1
*/
Fraction::Fraction()
{
    numerator = 1;
    denominator = 1;
}


/**
 * Ctor with two integer parameters
 * Check & Initialise with values
 * @param[num]: used as numerator
 * @param[deno]: used as denominator
*/
Fraction::Fraction(int num, int deno)
{
    // check if illegal
	if (deno == 0)
	{
		cerr << "Denominator can't be zero!!" << endl;
		system("pause");
		exit(-1);
	}
    // flag process
	if (deno < 0)
		numerator = -num;
	else
		numerator = num;
    denominator = abs(deno);

    simplify();
}


/**
 * Copy Ctor
 * Copy the values passed by 'fra'
 * @param[fra]: a Fraction instance to be copied
*/
Fraction::Fraction(const Fraction& fra)
{
    numerator = fra.numerator;
    denominator = fra.denominator;
}


/**
 * Ctor with a string parameter
 * Initialise with 'str'
 * @param[str]: a finite decimal string
*/
Fraction::Fraction(const string& str)
{
    size_t i = str.size()-1;
    // check '.'
    for(;i >= 0; i--)
        if(str[i] == '.')
            break;

    // integer
    if(i == -1)
    {
        numerator = atoi(str.c_str());
        denominator = 1;
    }
    else // real number
    {
        // divide
        string num = str.substr(0, i);
        string deno = str.substr(i+1);
        int ofs = deno.length();
        ofs = (int)pow(10, ofs);
        // type transfer
        numerator = atoi(num.c_str()) *ofs;
        denominator = ofs;

        simplify();
    }
}


/**
 * simplify
 * Reduction of a Fraction instance
*/
void Fraction::simplify()
{
    int n = gcd(numerator);
    // reduction
    numerator /= n;
    denominator /= n;
}

/**
 * Find the Greatest-Common-Devisor
 * @return: integer answer
 * @para[y]: between denominator and y
*/
int Fraction::gcd(int y)
{
    int x = denominator;
    x = abs(x);
    y = abs(y);
	if (x == 0 || y == 0)	return 1;   // if one or both are '0'
    // until x == y
    while(x != y)
    {
        if(x>y) x-=y;
        else y -= x;
    }

    return x;
}

/**
 * Type cast to double
*/
Fraction::operator double() const
{
    return numerator *1.0 / denominator; // calculate
}

/**
 * Type cast to string
*/
Fraction::operator string() const
{
    return to_string(numerator) + "/" + to_string(denominator);
}

/**
 * String to Fraction
 * conversion from a finite decimal string
 * @para[str]: a finite decimal string
*/
void Fraction::StrtoFra(string str)
{
    int i = str.size()-1;
    // find '.'
    for(;i >= 0; i--)
        if(str[i] == '.')
            break;

    // integer
    if(i == -1)
    {
        numerator = atoi(str.c_str());
        denominator = 1;
    }
    else // real number
    {
        // divide
        string num = str.substr(0, i);
        string deno = str.substr(i+1);
        // off-set
        int ofs = deno.length();
        ofs = (int)pow(10, ofs);
        // assign values
        numerator = atof(str.c_str()) *ofs; // type transfer
        denominator = ofs;
        simplify();
    }
}

/**
 * Plus
 * @return: a Fraction instance
 * @para[a]: left fraction
 * @para[b]: right fraction
*/
Fraction operator +(Fraction& a, Fraction& b)
{
    int gcd = a.gcd(b.denominator);
    // adjust to same denominator
    int anum = a.numerator*b.denominator/gcd, bnum = b.numerator*a.denominator/gcd;
    int NewDenominator = a.denominator*b.denominator/gcd;
    // construction a new instance
    Fraction ret(anum+bnum, NewDenominator);

    ret.simplify();

    return ret;
}

/**
 * Opposite number
*/
Fraction operator -(Fraction& a)
{
    return Fraction(-a.numerator, a.denominator);
}

/**
 * Minus
*/
Fraction operator -(Fraction& a, Fraction& b)
{
    // similiar to '+'
    int gcd = a.gcd(b.denominator);
    int anum = a.numerator*b.denominator/gcd, bnum = b.numerator*a.denominator/gcd;
    int NewDenominator = a.denominator*b.denominator/gcd;
    Fraction ret(anum-bnum, NewDenominator);

    ret.simplify();
    
    return ret;
}

/**
 * Multiply
*/
Fraction operator *(Fraction& a, Fraction& b)
{
    Fraction ret(a.numerator*b.numerator, a.denominator*b.denominator);
    ret.simplify();
    return ret;
}

/**
 * Divide
*/
Fraction operator /(Fraction& a, Fraction& b)
{
    Fraction ret(a.numerator*b.denominator, a.denominator*b.numerator);
    ret.simplify();
    return ret;
}


/**
 * Less-than
 * @return: a boolean value
 * @para[a]: left fraction
 * @para[b]: right fraction
*/
bool operator <(Fraction& a, Fraction& b)
{
    int gcd = a.gcd(b.denominator);
    // adjust to same base
    int anum = a.numerator * b.denominator/gcd;
    int bnum = b.numerator * a.denominator/gcd;
    return anum < bnum;
}

/**
 * Less-than or Equal-to
*/
bool operator <=(Fraction& a, Fraction& b)
{
    return a<b || a==b;
}

/**
 * Equal
*/
bool operator ==(Fraction& a, Fraction& b)
{
    int gcd = a.gcd(b.denominator);
    // adjust to same base
    int anum = a.numerator * b.denominator / gcd;
    int bnum = b.numerator * a.denominator / gcd;
    return anum == bnum;
}

/**
 * Not Equal
*/
bool operator !=(Fraction& a, Fraction& b)
{
    return !(a==b);
}

/**
 * Greater-than or Equal-to
*/
bool operator >=(Fraction& a, Fraction& b)
{
    return !(a<b);
}

/**
 * Greater-than
*/
bool operator >(Fraction& a, Fraction& b)
{
    return b < a;
}

/**
 * Stream inserter
 * @return: istream reference
 * @para[in]: istream
 * @para[a]: right fraction instance
*/
istream& operator >>(istream& in, Fraction& a)
{
	int num, deno;
	in >> num >> deno;
	a.numerator = num;

    // check if illegal
	if (deno == 0)
	{
		cerr << "Denominator can't be zero!!" << endl;
		system("pause");
		exit(-1);
	}
	else
		a.denominator = abs(deno);

    // place flag in numerator
	if (deno < 0)
		a.numerator = -a.numerator;
	
    a.simplify();
    
    return in;
}

/**
 * Stream extractor
 * @return: ostream reference
 * @para[in]: ostream
 * @para[a]: right fraction instance
*/
ostream& operator <<(ostream& out, Fraction a)
{
    // format
    out << a.numerator << "/" << a.denominator;
    return out;
}
