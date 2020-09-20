/**
 * FileName: BinParser.h
 * Description: Declarations of C++ <-> Binary (de)serialization function
 * Author: Ziteng Wang
 * Date: 2020/07/05
*/

#include <iostream>
#include <type_traits>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
using namespace std;


/**
 * Basic
 * Support Types:
 *  1. Arithmetic Types
 * 	2. String Type
 *  2. Basic STL Containers
*/
typedef struct basic {
	int i;
    float f;
	double d_float;
    char ch;
    bool b;

    string str;

	vector<int> v;
	set<int> s;
	list<float> l;
	map<int, string> mp;
	pair<int, double> p;
}Basic;


/**
 * Advance
 * Support Types:
 *  1. Smart Pointer
 *  2. Advanced STL Container
*/
typedef struct advance {
	shared_ptr<vector<int>> sp;		// Constructructed by STL-vector
	weak_ptr<vector<int>> wp;

// Can support ANY FINITE layers of nesting
	vector<vector<string>> advv;
    list<list<char>> advl;
}Advance;



// namespace for Binary (de)serialization
namespace binparser{
	/**
	 * Inner Interface
	 * @param stream out/in stream for File write/read
	 * @param T Specified type filtered by template
	*/
	//  Arithmetic Type
	template <class T, typename enable_if_t<is_trivially_copyable_v<T>, int> N = 0>
	void Serialize(ostream & os, const T & val);

	template <class T, typename enable_if_t<is_trivially_copyable_v<T>, int> N = 0>
	void Deserialize(istream & is, T & val);
	//  STL Type
	template <class T, typename enable_if_t<is_same_v<typename T::iterator, decltype(declval<T>().begin())> && is_same_v<typename T::iterator, decltype(declval<T>().end())>, int> N = 0>
	void Serialize(ostream & os, const T & val);

	template <class T, typename enable_if_t<is_same_v<typename T::iterator, decltype(declval<T>().begin())> && is_same_v<typename T::iterator, decltype(declval<T>().end())>, int> N = 0>
	void Deserialize(istream & is, T & val);


	/**
	 * Outer Interface
	 * 	Direct interaction with user-interface
	*/
	//	Major Interface of Serialization for different types
	void serialize(Basic& b, string path);
	void serialize(Advance& a, string path);
	template <class T>
	void serialize(T& t, string path);

	//	Major Interface of Deserialization for different types
	void deserialize(Basic& b, string path);
	void deserialize(Advance& a, string path);
	template <class T>
	void deserialize(T& t, string path);

	//	Major Interface of Initialization and Visualization
	void Initialise(Basic &b);
	void Initialise(Advance &a);
	void ShowContent(Basic &b);
	void ShowContent(Advance &a);
}