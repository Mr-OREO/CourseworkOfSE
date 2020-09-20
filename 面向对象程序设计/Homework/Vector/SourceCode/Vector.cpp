/**
 * FileName: Vector.cpp
 * Author: Ziteng Wang
 * Description: Functions Implement
 * Date:2020-05-26
*/

#include"Vector.h"

// creates an empty vector
template <class T>
Vector<T>::Vector():m_pElements(NULL), m_nSize(0), m_nCapacity(0){}

// creates a vector for holding 'size' elements
template <class T>
Vector<T>::Vector(int size):m_pElements(new T[size]), m_nSize(0), m_nCapacity(size){}

// the copy ctor
template <class T>
Vector<T>::Vector(const Vector& r)       
{
    if(this->m_nCapacity < r.m_nCapacity)       // When Capacity need to be expanded
    {
        m_pElements = new T[r.m_nCapacity];     //  Allocate larger space FIRST
        m_nCapacity = r.m_nCapacity;            //  Capacity equation THEN
    }
    m_nSize = r.m_nSize;                        // Always Size equation

    for (int i = 0; i < r.m_nSize; i++)
    {
        m_pElements[i] = r.m_pElements[i];      // Elements copy
    }
}

// destructs the vector 
template <class T>
Vector<T>::~Vector()                     
{
    delete[] m_pElements;               // Array Deletion
}

/**
 * accesses the specified element without bounds checking
 * @param [int]{Query at position 'index'}
 * @return [T&]{Reference of Element of class T}
*/
template <class T>
T& Vector<T>::operator[](int index)
{
    return m_pElements[index];          // Return straightly
}

/**
 * accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
 * @param [int]{Query at position 'index'}
 * @return [T&]{Reference of Element of class T}
*/
template <class T>
T& Vector<T>::at(int index)
{
	if ((index >= m_nSize) || (index < 0))    // ERROR throw out: 1. Beyond size  2. Negative
	{
		cerr << "std::out_of_range";     // Throw 'std::out_of_range'
		exit(0);
	}
    return m_pElements[index];
}


/**
 * return the size of the container
 * @return [int]{Current Size of the Vector}
*/
template <class T>
int Vector<T>::size() const
{
    return m_nSize;
}

/**
 * adds an element to the end 
 * @param [const T&]{Reference of Inserted Element in class T}
*/
template <class T>
void Vector<T>::push_back(const T& x)
{
    if(m_nCapacity == m_nSize)          // Full now
        inflate();                      // Memory expand

    m_pElements[m_nSize++] = x;         // push back x
}

// clears the contents
template <class T>
void Vector<T>::clear()
{
    m_nSize = 0;            // Similiar to STL(vector)
}

/**
 * checks whether the container is empty 
 * @return [bool]{True: empty; False: non-empty}
*/
template <class T>
bool Vector<T>::empty() const
{
    if(m_nSize)
        return false;
    else
        return true;
}


// expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
template <class T>
void Vector<T>::inflate()
{
    if (m_nCapacity==0)                 // No space to be inflated
    {
        m_pElements = new T[1];         // 2^0
        m_nCapacity = 1;
        return;
    }
    T* temp = new T[2*m_nCapacity];     // Allocate Memory
    for (size_t i = 0; i < m_nSize; i++)
    {
        temp[i] = m_pElements[i];       // Content transfer
    }
    m_pElements = temp;                 // Pointer Equation FIRST
    m_nCapacity *= 2;                   // Capacity Equation THEN
}

// Assitant Function to print out the size && content
template<class T>
void Vector<T>::Print()
{
	cout << "Size: " << m_nSize << endl;
	for (size_t i = 0; i < m_nSize; i++)
	{
		cout << m_pElements[i] << " ";
	}
	if (m_nSize != 0)
		cout << "\n";

	cout << "\n";
}

/**
 * Inline Function
 * Overrided stream operator '<<' for class test
 * @param [ostream&]{Reference of Out Stream}
 * @param [const test&]{t of test class to be operated}
 * @return [ostream&]{Reference of Out Stream}
*/
inline ostream& operator<<(ostream& os, const test& t)
{
	os << t.str;
	return os;
}