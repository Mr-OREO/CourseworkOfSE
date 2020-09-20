/**
 * FileName: BinParser.cpp
 * Description: Implement of C++ <-> Binary (de)serialization
 * Author: Ziteng Wang
 * Date: 2020/07/05
*/

#include"BinParser.h"

/**
 * Serialize()
 * 	Inner interface equipted with type filters
 * @param os	out-stream for writing
 * @param val	template type reference acts as content
*/

//  Arithmetic Type
template <class T, typename enable_if_t<is_trivially_copyable_v<T>, int> N = 0>
void binparser::Serialize(ostream & os, const T & val) {
	os.write((const char *)&val, sizeof(T));
}

//  STL Type
template <class T, typename enable_if_t<is_same_v<typename T::iterator, decltype(declval<T>().begin())> && is_same_v<typename T::iterator, decltype(declval<T>().end())>, int> N = 0>
void binparser::Serialize(ostream & os, const T & val) {
	unsigned int size = val.size();
	os.write((const char *)&size, sizeof(size));
	for (auto iter = val.begin(); iter != val.end(); iter++)
		Serialize(os, *iter);
}



/**
 * Deserialize()
 * 	Inner interface equipted with type filters
 * @param is	in-stream for reading
 * @param val	template type reference acts as content
*/

template <class T, typename enable_if_t<is_trivially_copyable_v<T>, int> N = 0>
void binparser::Deserialize(istream & is, T & val)
{
	is.read((char *)&val, sizeof(T));
}

template <class T, typename enable_if_t<is_same_v<typename T::iterator, decltype(declval<T>().begin())> && is_same_v<typename T::iterator, decltype(declval<T>().end())>, int> N = 0>
void binparser::Deserialize(istream & is, T & val)
{
	unsigned int size = 0;
	is.read((char *)&size, sizeof(unsigned int));
	val.resize(size);
	for (auto & v : val) { Deserialize(is, v); }
}



/**
 * serialize()
 * 	Outer serialize interface called in Main function
 * @param b/a/t		content reference
 * @param path		file path
*/

// Basic Type
void binparser::serialize(Basic& b, string path) {
	ofstream out(path, ios::out | ios::binary);
	Serialize(out, b.i);
	Serialize(out, b.f);
	Serialize(out, b.d_float);
	Serialize(out, b.ch);
	Serialize(out, b.b);
	Serialize(out, b.str);
	Serialize(out, b.v);
	Serialize(out, b.s);
	Serialize(out, b.l);
	Serialize(out, b.mp.size());
	for (auto & m : b.mp) {		// Map: The iterator works differently
		Serialize(out, m.first);
		Serialize(out, m.second);
	}
	Serialize(out, b.p.first);
	Serialize(out, b.p.second);
	out.close();
}

// Advance Type
void binparser::serialize(Advance& a, string path) {
	ofstream out(path, ios::out | ios::binary);
	out.write((char*)(&a.sp), sizeof(a.sp));
	out.write((char*)(&a.wp), sizeof(a.wp));
	Serialize(out, a.advv);
	Serialize(out, a.advl);
	out.close();
}

// Single Template Type
template <class T>
void binparser::serialize(T& t, string path){
	ofstream out(path, ios::out | ios::binary);
	Serialize(out, t);
	out.close;
}



/**
 * deserialize()
 * 	Outer deserialize interface called in Main function
 * @param b/a/t		content reference
 * @param path		file path
*/

// Basic Type
void binparser::deserialize(Basic& b, string path) {
	unsigned int mapsize, setsize;
	int first, element;
	string second;
	ifstream in(path, ios::in | ios::binary);
	Deserialize(in, b.i);
	Deserialize(in, b.f);
	Deserialize(in, b.d_float);
	Deserialize(in, b.ch);
	Deserialize(in, b.b);
	Deserialize(in, b.str);
	Deserialize(in, b.v);
	Deserialize(in, setsize);
	for (int i = 0; i < setsize; i++) {	// Set: No resize() function inside
		Deserialize(in, element);
		b.s.insert(element);
	}
	Deserialize(in, b.l);
	Deserialize(in, mapsize);
	for (int i = 0; i < mapsize; i++) {	// Map: No resize() function inside
		Deserialize(in, first);
		Deserialize(in, second);
		b.mp[first] = second;
	}
	Deserialize(in, b.p.first);
	Deserialize(in, b.p.second);
	in.close();
}

// Advance Type
void binparser::deserialize(Advance& a, string path) {
	ifstream in(path, ios::in | ios::binary);
	in.read((char*)(&a.sp), sizeof(a.sp));
	in.read((char*)(&a.wp), sizeof(a.wp));
	Deserialize(in, a.advv);
	Deserialize(in, a.advl);
	in.close();
}

// Single Template Type
template <class T>
void binparser::deserialize(T& t, string path){
	ifstream in(path, ios::in | ios::binary);
	Serialize(in, t);
	in.close;
}



/**
 * Initialise()
 * Description:
 *  Initialise two struct instances
 * 	You can change it to whatever values, but keep types' consistence
 * @param b: basic struct (reference)
 * @param a: advance struct (reference)
*/
void binparser::Initialise(Basic &b) {
	// BASIC
	b.i = 1; b.f = 1.41; b.d_float = 3.14159; b.ch = 'b'; b.b = true;
	b.str = "Basic Struct";
	b.l.push_back(1.73); b.v.push_back(13); b.s.insert(27); b.p = make_pair(7, 2.718); b.mp[10] = "STL::MAP";
}

void binparser::Initialise(Advance &a) {
	// ADVANCE
	vector<int> veci;
	vector<string> vecs;
	list<char> listc;
	veci.push_back(1); veci.push_back(2); veci.push_back(3);
	vecs.push_back("no.1"); vecs.push_back("no.2"); vecs.push_back("no.3");
	listc.push_back('a'); listc.push_back('b'); listc.push_back('c');
	a.sp = make_shared<vector<int>>(veci);
	a.wp = a.sp;

	a.advv.push_back(vecs);
	a.advl.push_back(listc);
}



/**
 * ShowContent()
 * Description:
 *  Visualization of Basic&Advance structs' content
 * @param b: basic struct (reference)
 * @param a: advance struct (reference)
*/
void binparser::ShowContent(Basic &b) {
	// BASIC
	cout << "Basic: " << endl;
	cout << "INT: " << b.i << "\nFLOAT: " << b.f << "\nDOUBLE: " << b.d_float << "\nCHAR: " << b.ch << "\nBOOL: " << b.b << "\nSTRING: " << b.str << endl;
	cout << "Vector: " << b.v[0] << "\nList: " << (b.l.front()) << "\nMap: ";
	for (auto & m : b.mp)
		cout << m.second << " ";
	cout << "\nSet: ";
	for (auto & st : b.s)
		cout << st << " ";
	cout << "\nPair: " << b.p.first << " " << b.p.second << endl;
	cout << endl;
}


void binparser::ShowContent(Advance &a) {
	// ADVANCE
	cout << "Advance: " << endl;
	cout << "Shared_Ptr: " << (*a.sp)[0] << " " << (*a.sp)[1] << " " << (*a.sp)[2] << endl;
	cout << "Weak_Ptr: " << (a.wp.use_count() ? "There exist weak_ptr" : "Not exist weak_ptr") << endl;
	cout << "Adv_Vector: { ";
	for (auto & av : a.advv.front())
		cout << av << " ";
	cout << " }\nAdv_List: { ";
	for (auto iter = a.advl.front().begin(); iter != a.advl.front().end(); iter++)
		cout << *iter << " ";
	cout << "}" << endl;
	cout << endl;
}