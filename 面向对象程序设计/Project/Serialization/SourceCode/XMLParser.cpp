#include "XMLParser.h"

using namespace std;
using namespace tinyxml2;
using namespace xmlparser;

//Recursive body with char in serilization
void XMLParser::parseElement2XML(char val, string name)
{
	XMLElement* intnode = doc->NewElement(name.c_str());
	intnode->SetAttribute("type", "char");
	//intnode->SetAttribute("isConst", "false");
	intnode->SetAttribute("val", val);
	XMLElement* rootnode = nodeStk.top();
	rootnode->InsertEndChild(intnode);
}

//Recursive body with bool in serilization
void XMLParser::parseElement2XML(bool val, string name)
{
	XMLElement* intnode = doc->NewElement(name.c_str());
	intnode->SetAttribute("type", "bool");
	intnode->SetAttribute("val", val ? "true" : "flase");
	XMLElement* rootnode = nodeStk.top();
	rootnode->InsertEndChild(intnode);
}

//Recursive body with int in serilization
void XMLParser::parseElement2XML(int val, string name)
{
	XMLElement* intnode = doc->NewElement(name.c_str());
	intnode->SetAttribute("type", "int32");
	//intnode->SetAttribute("isConst", "false");
	intnode->SetAttribute("val", val);
	XMLElement* rootnode = nodeStk.top();
	rootnode->InsertEndChild(intnode);
}

//Recursive body with float in serilization
void XMLParser::parseElement2XML(float val, string name)
{
	XMLElement* intnode = doc->NewElement(name.c_str());
	intnode->SetAttribute("type", "float");
	//intnode->SetAttribute("isConst", "false");
	intnode->SetAttribute("val", val);
	XMLElement* rootnode = nodeStk.top();
	rootnode->InsertEndChild(intnode);
}

//Recursive body with double in serilization
void XMLParser::parseElement2XML(double val, string name)
{
	XMLElement* intnode = doc->NewElement(name.c_str());
	intnode->SetAttribute("type", "double");
	intnode->SetAttribute("val", val);
	XMLElement* rootnode = nodeStk.top();
	rootnode->InsertEndChild(intnode);
}

//Recursive body with std::string in serilization
void XMLParser::parseElement2XML(std::string val, string name)
{
	XMLElement* intnode = doc->NewElement(name.c_str());
	intnode->SetAttribute("type", "std_string");
	//intnode->SetAttribute("len", val.length());
	intnode->SetAttribute("val", val.c_str());
	XMLElement* rootnode = nodeStk.top();
	rootnode->InsertEndChild(intnode);
}


//Recursive body with char in deserilization
void XMLParser::parseElementFromXML(char* val)
{
	XMLElement* node = nodeStk.top();
	if (string(node->FindAttribute("type")->Value()) != "char") {
		cout << "type is NOT char" << endl;
		return;
	}
	*val = (char)node->FindAttribute("val")->IntValue();
}

//Recursive body with bool in deserilization
void XMLParser::parseElementFromXML(bool* val)
{
	XMLElement* node = nodeStk.top();
	if (string(node->FindAttribute("type")->Value()) != "bool") {
		cout << "type is NOT bool" << endl;
		return;
	}
	*val = string(node->FindAttribute("val")->Value()) == "true" ? true : false;
}

//Recursive body with int in deserilization
void XMLParser::parseElementFromXML(int* val)
{
	XMLElement* node = nodeStk.top();
	if (string(node->FindAttribute("type")->Value()) != "int32") {
		cout << "type is NOT int32" << endl;
		return;
	}
	*val = node->FindAttribute("val")->IntValue();
}

//Recursive body with float in deserilization
void XMLParser::parseElementFromXML(float* val)
{
	XMLElement* node = nodeStk.top();
	if (string(node->FindAttribute("type")->Value()) != "float") {
		cout << "type is NOT float" << endl;
		return;
	}
	*val = node->FindAttribute("val")->FloatValue();
}

//Recursive body with double in deserilization
void XMLParser::parseElementFromXML(double* val)
{
	XMLElement* node = nodeStk.top();
	if (string(node->FindAttribute("type")->Value()) != "double") {
		cout << "type is NOT double" << endl;
		return;
	}
	*val = node->FindAttribute("val")->DoubleValue();
}

//Recursive body with std::string in deserilization
void XMLParser::parseElementFromXML(std::string* val)
{
	XMLElement* node = nodeStk.top();
	if (string(node->FindAttribute("type")->Value()) != "std_string") {
		cout << "type is NOT std_string" << endl;
		return;
	}
	*val = node->FindAttribute("val")->Value();
}