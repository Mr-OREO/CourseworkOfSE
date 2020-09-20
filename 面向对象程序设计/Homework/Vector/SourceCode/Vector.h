/**
 * FileName: Vector.h
 * Author: Ziteng Wang
 * Description: Class Definition
 *  1. Vector: template class
 *  2. test: used as a specified class for Vector
 * Date:2020-05-26
*/

#ifndef Vector__H
#define Vector__H

#include<string>
#include<iostream>
using namespace std;

// Temlate class
template <class T>
class Vector {
public:
  Vector();                      // creates an empty vector
  Vector(int size);              // creates a vector for holding 'size' elements
  Vector(const Vector& r);       // the copy ctor
  ~Vector();                     // destructs the vector 
  T& operator[](int index);      // accesses the specified element without bounds checking
  T& at(int index);              // accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
  int size() const;		           // return the size of the container
  void push_back(const T& x);    // adds an element to the end 
  void clear();                  // clears the contents
  bool empty() const;            // checks whether the container is empty 
  void Print();                  // Assitant Function to print out the size && content
private:
  void inflate();                // expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
  T *m_pElements;                // pointer to the dynamically allocated storage
  int m_nSize;                   // the number of elements in the container
  int m_nCapacity;               // the number of elements that can be held in currently allocated storage
};

// Test for constructed class in Vector
class test
{
public:
  string str;
  test():str(""){}
  test(const string s):str(s){}
  test(const test& t):str(t.str){}
};

//ostream& operator<<(ostream& os, const test& t);

#endif