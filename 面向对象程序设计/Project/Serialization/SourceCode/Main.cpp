/**
 * FileName: Main.cpp
 * Description: User-interface of the project "Serialization"
 * Author: Ziteng Wang, Keyue Xu
 * Date: 2020/07/05
*/

#include"BinParser.h"
#include"XMLParser.h"
#include"base64Coder.h"
using namespace binparser;
using namespace xmlparser;

/**
 * BinaryTest()
 * 	Test for binary version
 * 1. Basic User-defined struct
 * 		all basic types
 * 		all basic STL containers
 * 2. Advance User-defined struct
 * 		smart pointers
 * 		nest STLs, such as list<vector<int>>, vector<list<string>>
 * 3. Any Single Variables
*/
void BinaryTest() {
	Basic b1, b2;
	Advance a1, a2;
	string path1 = "Basic.txt", path2 = "Advance.txt";

// INIT & DISPLAY(before)
	Initialise(b1);
	Initialise(a1);

	cout << "Before Binary Serialization" << endl;
	ShowContent(b1);
	ShowContent(a1);

// (DE)SERIALIZE
	serialize(b1, path1);
	serialize(a1, path2);

	deserialize(b2, path1);
	deserialize(a2, path2);

// DISPLAY(after)
	cout << "\nAfter Binary Deserialization" << endl;
	ShowContent(b2);
	ShowContent(a2);
}


/**
 * XMLTest()
 * 	Test for XML version
 * 1. Basic User-defined struct
 * 		all basic types
 * 		all basic STL containers
 * 2. Any Nest STLs
 * 		such as list<vector<int>>, vector<list<string>>
 * 3. Any Single Variable
*/
void XMLTest() {
	
	cout << "\nXML serilization and deserilization" << endl;
	//test struct Basic
	//1. bind a file
	XMLParser parser1 = XMLParser("testStruct.xml");
	//2. initialize
	Basic bs, bs2;
	Initialise(bs);
	Reflection<Basic>::instance()
		.regist(&Basic::b, "b")
		.regist(&Basic::ch, "ch")
		.regist(&Basic::d_float, "d_float")
		.regist(&Basic::f, "f")
		.regist(&Basic::i, "i")
		.regist(&Basic::l, "l")
		.regist(&Basic::mp, "mp")
		.regist(&Basic::p, "p")
		.regist(&Basic::s, "s")
		.regist(&Basic::str, "str")
		.regist(&Basic::v, "v");
	//3. serilize
	parser1.parse2XML(bs);
	//4. deserilize
	parser1.parseFromXML(&bs2);
	//5. display result
	ShowContent(bs2);

	//test map<string, ste<string>>
	//1. bind a file
	XMLParser parser2 = XMLParser("testMap(Set).xml");
	//2. initialize
	map<string, set<string>> mp, mp2;
	set<string> st1; st1.insert("Apple"); st1.insert("Banana");
	set<string> st2; st2.insert("Pork"); st2.insert("Beaf");
	mp["fruit"] = st1; mp["meat"] = st2;
	//3. serilize
	parser2.parse2XML(mp);
	//4. deserilize
	parser2.parseFromXML(&mp2);
	//5. display result
	cout << "\nmap<string,set<string>> test:" << endl;
	set<string>::iterator itr2;
	cout << "fruit" << endl;
	for (itr2 = mp2["fruit"].begin(); itr2 != mp2["fruit"].end(); itr2++)
		cout << "\tval: " << *itr2 << endl;
	cout << "meat" << endl;
	for (itr2 = mp2["meat"].begin(); itr2 != mp2["meat"].end(); itr2++)
		cout << "\tval: " << *itr2 << endl;

	//test list<vector<int>>
	//1. bind a file
	XMLParser parser3 = XMLParser("testList(Vect).xml");
	//2. initialize
	list<vector<int>> lst, lst2;
	vector<int> vct1; vct1.push_back(1); vct1.push_back(2);
	vector<int> vct2; vct2.push_back(3); vct2.push_back(4);
	lst.push_back(vct1); lst.push_back(vct2);
	//3. serilize
	parser3.parse2XML(lst);
	//4. deserilize
	parser3.parseFromXML(&lst2);
	//5. display result
	cout << "\nlist<vector<int>> test:" << endl;
	list<vector<int>>::iterator itr3;
	for (itr3 = lst2.begin(); itr3 != lst2.end(); itr3++)
		for (unsigned int i = 0; i < itr3->size(); i++)
			cout << "val: " << (*itr3)[i] << endl;
	base64Coder coder;
	coder.parseBinary2Zijie("testList(Vect).xml", "base64");
	coder.parseZijie2Binary("base64", "newTestList(Vect).xml");
}

int main() {
	cout << "---------------------------------------------------------------" << endl;
	cout <<	"                _       _ _          _   _             		" << endl;
	cout <<	"               (_)     | (_)        | | (_)            		" << endl;
	cout <<	"  ___  ___ _ __ _  __ _| |_ ______ _| |_ _  ___  _ __  		" << endl;
	cout <<	" / __|/ _ \\ '__| |/ _` | | |_  / _` | __| |/ _ \\| '_ \\ 		" << endl;
	cout <<	" \\__ \\  __/ |  | | (_| | | |/ / (_| | |_| | (_) | | | |		" << endl;
	cout <<	" |___/\\___|_|  |_|\\__,_|_|_/___\\__,_|\\__|_|\\___/|_| |_|	" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "Team Member: Ziteng Wang, Keyue Xu" << endl;
	cout << "Date: 2020/07/05" << endl;
	cout << "---------------------------------------------------------------" << endl;

	cout << "Binary Version : \n" << endl;
	BinaryTest();

	cout << "\nXML Version : \n" << endl;
	XMLTest();

	system("pause");
	return 0;
}