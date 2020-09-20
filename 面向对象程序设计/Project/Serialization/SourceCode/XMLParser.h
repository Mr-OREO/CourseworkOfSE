#pragma once
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <map>
#include "tinyxml2.h"
#include "Reflection.h"
#include <sstream>
#include <iostream>

namespace xmlparser
{
	//Class: XMLParser
	//Usage: Binds a filename and parses a specified type:
	//	basic type, STL container type,
	//	or a user defined type (Without complex structure) to XML doc in file
	//	or parse from a XML doc to deserilize
	class XMLParser
	{
	public:
		XMLParser(std::string filename)
		{
			this->filename = filename;
			doc = nullptr;
		}
		//Parses T to XML doc
		template <typename T>
		void parse2XML(T val);
		//Parses XML doc to T
		template <typename T>
		void parseFromXML(T* tar);
	private:
		//User defiend type
		//T to XML
		template <typename T>
		void parseElement2XML(T val, std::string name = "a");
		//XML to T
		template <typename T>
		void parseElementFromXML(T* val);
		//Basic type
		//basic type to XML
		void parseElement2XML(char val, std::string name = "a");
		void parseElement2XML(bool val, std::string name = "a");
		void parseElement2XML(int val, std::string name = "a");
		void parseElement2XML(float val, std::string name = "a");
		void parseElement2XML(double val, std::string name = "a");
		void parseElement2XML(std::string val, std::string name = "a");
		//XML to basic type
		void parseElementFromXML(char* val);
		void parseElementFromXML(bool* val);
		void parseElementFromXML(int* val);
		void parseElementFromXML(float* val);
		void parseElementFromXML(double* val);
		void parseElementFromXML(std::string* val);
		//std::container to XML
		template <typename K, typename V>
		void parseElement2XML(std::pair<K, V> val, std::string name = "a");
		template <typename T>
		void parseElement2XML(std::vector<T> val, std::string name = "a");
		template <typename T>
		void parseElement2XML(std::list<T> val, std::string name = "a");
		template <typename T>
		void parseElement2XML(std::set<T> val, std::string name = "a");
		template <typename K, typename V>
		void parseElement2XML(std::map<K, V> val, std::string name = "a");
		//XML to std::container
		template <typename K, typename V>
		void parseElementFromXML(std::pair<K, V>* val);
		template <typename T>
		void parseElementFromXML(std::vector<T>* val);
		template <typename T>
		void parseElementFromXML(std::list<T>* val);
		template <typename T>
		void parseElementFromXML(std::set<T>* val);
		template <typename K, typename V>
		void parseElementFromXML(std::map<K, V>* val);
	private:
		//The file name used for IO
		std::string filename;
		//The XML document used across functions
		tinyxml2::XMLDocument* doc;
		//The top node is used for recursive step
		std::stack<tinyxml2::XMLElement*> nodeStk;
	};

	//Implementation of Function with template T
	//
	//Entrance of serialization
	template<typename T>
	inline void XMLParser::parse2XML(T val)
	{
		doc = new tinyxml2::XMLDocument();
		//header
		tinyxml2::XMLElement* rootnode = doc->NewElement("serialization");
		//The top node is the root element in serilization
		doc->InsertEndChild(rootnode);
		{
			nodeStk.push(rootnode);
			parseElement2XML(val);
			nodeStk.pop();
		}
		doc->SaveFile(filename.c_str());
		doc->Clear();
		doc = nullptr;
	}

	//Entrance of deserialization
	template<typename T>
	inline void XMLParser::parseFromXML(T* val)
	{
		doc = new tinyxml2::XMLDocument();
		tinyxml2::XMLError err = doc->LoadFile(filename.c_str());
		if (err != tinyxml2::XMLError::XML_SUCCESS) {
			std::cout << doc->ErrorName() << std::endl; delete doc;
			doc = nullptr;
			return;
		}
		tinyxml2::XMLElement* rootnode = doc->FirstChildElement();
		//skip header
		rootnode = rootnode->FirstChildElement();
		//The top node is the first element in deserilization
		nodeStk.push(rootnode);
		{
			parseElementFromXML(val);
		}
		nodeStk.pop();
		delete doc;
		doc = nullptr;
		return;
	}

//Macro for reducing coding
#define SWITCH_SER_CONT_ONE_PARAMETER(Cont) \
switch(p0type)\
{\
case CHAR:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<char> T::*>(ptr), itr->first);break;\
case BOOL:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<bool> T::*>(ptr), itr->first);break;\
case INT:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<int> T::*>(ptr), itr->first);break;\
case FLOAT:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<float> T::*>(ptr), itr->first);break;\
case DOUBLE:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<double> T::*>(ptr), itr->first);break;\
case STRING:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<std::string> T::*>(ptr), itr->first);break;\
default:\
	break;\
}

#define SWITCH_SER_CONT_TWO_PARAMETER_0(Cont, K) \
switch(p1type)\
{\
case CHAR:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<K,char> T::*>(ptr), itr->first);break;\
case BOOL:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<K,bool> T::*>(ptr), itr->first);break;\
case INT:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<K,int> T::*>(ptr), itr->first);break;\
case FLOAT:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<K,float> T::*>(ptr), itr->first);break;\
case DOUBLE:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<K,double> T::*>(ptr), itr->first);break;\
case STRING:\
	parseElement2XML(val.*reinterpret_cast<std::##Cont##<K,std::string> T::*>(ptr), itr->first);break;\
default:\
	break;\
}
#define SWITCH_SER_CONT_TWO_PARAMETER(Cont) \
switch(p0type)\
{\
case CHAR:\
	SWITCH_SER_CONT_TWO_PARAMETER_0(Cont, char);break;\
case BOOL:\
	SWITCH_SER_CONT_TWO_PARAMETER_0(Cont, bool);break;\
case INT:\
	SWITCH_SER_CONT_TWO_PARAMETER_0(Cont, int);break;\
case FLOAT:\
	SWITCH_SER_CONT_TWO_PARAMETER_0(Cont, float);break;\
case DOUBLE:\
	SWITCH_SER_CONT_TWO_PARAMETER_0(Cont, double);break;\
case STRING:\
	SWITCH_SER_CONT_TWO_PARAMETER_0(Cont, std::string);break;\
default:\
	break;\
}

	//Recursive body with user defined type T in serilization
	template<typename T>
	void XMLParser::parseElement2XML(T val, std::string name)
	{
		tinyxml2::XMLElement* Tnode = doc->NewElement(name.c_str());
		Tnode->SetAttribute("type", Reflection<T>::instance().name().c_str());
		tinyxml2::XMLElement* rootnode = nodeStk.top();
		rootnode->InsertEndChild(Tnode);
		{
			nodeStk.push(Tnode);
			typename std::map<std::string, Member<T>*>::iterator itr;
			std::map<std::string, Member<T>*>& mems = Reflection<T>::instance().getMems();
			for (itr = mems.begin(); itr != mems.end(); itr++)
			{
				XMLTypeID type = itr->second->getType();
				XMLTypeID p0type = itr->second->getP0Type();
				XMLTypeID p1type = itr->second->getP1Type();
				void* T::* ptr = itr->second->getPtr();
				switch (type)
				{
				case CHAR:
					parseElement2XML(val.*reinterpret_cast<char T::*>(ptr), itr->first); break;
				case BOOL:
					parseElement2XML(val.*reinterpret_cast<bool T::*>(ptr), itr->first); break;
				case INT:
					parseElement2XML(val.*reinterpret_cast<int T::*>(ptr), itr->first); break;
				case FLOAT:
					parseElement2XML(val.*reinterpret_cast<float T::*>(ptr), itr->first); break;
				case DOUBLE:
					parseElement2XML(val.*reinterpret_cast<double T::*>(ptr), itr->first); break;
				case STRING:
					parseElement2XML(val.*reinterpret_cast<std::string T::*>(ptr), itr->first); break;
				case STLPAIR:
					SWITCH_SER_CONT_TWO_PARAMETER(pair); break;
				case STLVECT:
					SWITCH_SER_CONT_ONE_PARAMETER(vector); break;
				case STLLIST:
					SWITCH_SER_CONT_ONE_PARAMETER(list); break;
				case STLSET:
					SWITCH_SER_CONT_ONE_PARAMETER(set); break;
				case STLMAP:
					SWITCH_SER_CONT_TWO_PARAMETER(map); break;
				default:
					break;
				}
			}
			nodeStk.pop();
		}
	}

//Macro for reducing coding
#define SWITCH_DESER_CONT_ONE_PARAMETER(Cont) \
switch(p0type)\
{\
case CHAR:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<char> T::*>(ptr)));break;\
case BOOL:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<bool> T::*>(ptr)));break;\
case INT:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<int> T::*>(ptr)));break;\
case FLOAT:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<float> T::*>(ptr)));break;\
case DOUBLE:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<double> T::*>(ptr)));break;\
case STRING:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<std::string> T::*>(ptr)));break;\
default:\
	break;\
}\

#define SWITCH_DESER_CONT_TWO_PARAMETER_0(Cont, K) \
switch(p1type)\
{\
case CHAR:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<K,char> T::*>(ptr)));break;\
case BOOL:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<K,bool> T::*>(ptr)));break;\
case INT:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<K,int> T::*>(ptr)));break;\
case FLOAT:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<K,float> T::*>(ptr)));break;\
case DOUBLE:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<K,double> T::*>(ptr)));break;\
case STRING:\
	parseElementFromXML(&(val->*reinterpret_cast<std::##Cont##<K,std::string> T::*>(ptr)));break;\
default:\
	break;\
}

#define SWITCH_DESER_CONT_TWO_PARAMETER(Cont) \
switch(p0type)\
{\
case CHAR:\
	SWITCH_DESER_CONT_TWO_PARAMETER_0(Cont, char);break;\
case BOOL:\
	SWITCH_DESER_CONT_TWO_PARAMETER_0(Cont, bool);break;\
case INT:\
	SWITCH_DESER_CONT_TWO_PARAMETER_0(Cont, int);break;\
case FLOAT:\
	SWITCH_DESER_CONT_TWO_PARAMETER_0(Cont, float);break;\
case DOUBLE:\
	SWITCH_DESER_CONT_TWO_PARAMETER_0(Cont, double);break;\
case STRING:\
	SWITCH_DESER_CONT_TWO_PARAMETER_0(Cont, std::string);break;\
default:\
	break;\
}

	//Recursive body with user defined type T in deserilization
	template<typename T>
	void XMLParser::parseElementFromXML(T* val)
	{
		tinyxml2::XMLElement* node = nodeStk.top();
		if (std::string(node->FindAttribute("type")->Value()) != Reflection<T>::instance().name()) {
			std::cout << "type is NOT " << Reflection<T>::instance().name() << std::endl;
			return;
		}
		node = node->FirstChildElement();
		for (; node != nullptr; node = node->NextSiblingElement())
		{
			Member<T>* mem = Reflection<T>::instance().getMem(node->Name());
			if (mem == nullptr) {
				std::cout << node->Name() << "doesn't exist in " << Reflection<T>::instance().name() << std::endl;
				return;
			}
			XMLTypeID type = mem->getType();
			XMLTypeID p0type = mem->getP0Type();
			XMLTypeID p1type = mem->getP1Type();
			void* T::* ptr = mem->getPtr();
			nodeStk.push(node);
			switch (type)
			{
			case CHAR:
				parseElementFromXML(&(val->*reinterpret_cast<char T::*>(ptr))); break;
			case BOOL:
				parseElementFromXML(&(val->*reinterpret_cast<bool T::*>(ptr))); break;
			case INT:
				parseElementFromXML(&(val->*reinterpret_cast<int T::*>(ptr))); break;
			case FLOAT:
				parseElementFromXML(&(val->*reinterpret_cast<float T::*>(ptr))); break;
			case DOUBLE:
				parseElementFromXML(&(val->*reinterpret_cast<double T::*>(ptr))); break;
			case STRING:
				parseElementFromXML(&(val->*reinterpret_cast<std::string T::*>(ptr))); break;
			case STLPAIR:
				SWITCH_DESER_CONT_TWO_PARAMETER(pair); break;
			case STLVECT:
				SWITCH_DESER_CONT_ONE_PARAMETER(vector); break;
			case STLLIST:
				SWITCH_DESER_CONT_ONE_PARAMETER(list); break;
			case STLSET:
				SWITCH_DESER_CONT_ONE_PARAMETER(set); break;
			case STLMAP:
				SWITCH_DESER_CONT_TWO_PARAMETER(map); break;
			default:
				break;
			}
			nodeStk.pop();
		}
	}

	//Recursive body with std::pair in serilization
	template<typename K, typename V>
	inline void XMLParser::parseElement2XML(std::pair<K, V> val, std::string name)
	{
		tinyxml2::XMLElement* pairnode = doc->NewElement(name.c_str());
		pairnode->SetAttribute("type", "std_pair");
		tinyxml2::XMLElement* rootnode = nodeStk.top();
		rootnode->InsertEndChild(pairnode);
		{
			nodeStk.push(pairnode);
			parseElement2XML(val.first, "first");
			parseElement2XML(val.second, "second");
			nodeStk.pop();
		}
	}

	//Recursive body with std::vector in serilization
	template<typename T>
	inline void XMLParser::parseElement2XML(std::vector<T> val, std::string name)
	{
		tinyxml2::XMLElement* vectnode = doc->NewElement(name.c_str());
		vectnode->SetAttribute("type", "std_vector");
		std::stringstream ss;
		ss << val.capacity();
		vectnode->SetAttribute("capacity", ss.str().c_str());
		tinyxml2::XMLElement* rootnode = nodeStk.top();
		rootnode->InsertEndChild(vectnode);
		{
			nodeStk.push(vectnode);
			for (int i = 0; i < val.size(); i++)
				parseElement2XML(val[i], "element");
			nodeStk.pop();
		}
	}

	//Recursive body with std::list in serilization
	template<typename T>
	inline void XMLParser::parseElement2XML(std::list<T> val, std::string name)
	{
		tinyxml2::XMLElement* listnode = doc->NewElement(name.c_str());
		listnode->SetAttribute("type", "std_list");
		tinyxml2::XMLElement* rootnode = nodeStk.top();
		rootnode->InsertEndChild(listnode);
		{
			nodeStk.push(listnode);
			typename std::list<T>::iterator itr;
			for (itr = val.begin(); itr != val.end(); itr++)
				parseElement2XML(*itr, "element");
			nodeStk.pop();
		}
	}

	//Recursive body with std::set in serilization
	template<typename T>
	inline void XMLParser::parseElement2XML(std::set<T> val, std::string name)
	{
		tinyxml2::XMLElement* setnode = doc->NewElement(name.c_str());
		setnode->SetAttribute("type", "std_set");
		tinyxml2::XMLElement* rootnode = nodeStk.top();
		rootnode->InsertEndChild(setnode);
		{
			nodeStk.push(setnode);
			typename std::set<T>::iterator itr;
			for (itr = val.begin(); itr != val.end(); itr++)
				parseElement2XML(*itr, "element");
			nodeStk.pop();
		}
	}

	//Recursive body with std::map in serilization
	template<typename K, typename V>
	inline void XMLParser::parseElement2XML(std::map<K, V> val, std::string name)
	{
		tinyxml2::XMLElement* mapnode = doc->NewElement(name.c_str());
		mapnode->SetAttribute("type", "std_map");
		tinyxml2::XMLElement* rootnode = nodeStk.top();
		rootnode->InsertEndChild(mapnode);
		{
			nodeStk.push(mapnode);
			typename std::map<K, V>::iterator itr;
			std::pair<K, V> par;
			for (itr = val.begin(); itr != val.end(); itr++)
			{
				parseElement2XML(itr->first, "first");
				parseElement2XML(itr->second, "second");
			}
			nodeStk.pop();
		}
	}


	//Recursive body with std::pair in deserilization
	template <typename K, typename V>
	void XMLParser::parseElementFromXML(std::pair<K, V>* val)
	{
		tinyxml2::XMLElement* node = nodeStk.top();
		if (std::string(node->FindAttribute("type")->Value()) != "std_pair") {
			std::cout << "type is NOT std_pair" << std::endl;
			return;
		}
		node = node->FirstChildElement();
		nodeStk.push(node);
		{
			parseElementFromXML(&(val->first));
		}
		nodeStk.pop();
		nodeStk.push(node->NextSiblingElement());
		{
			parseElementFromXML(&(val->second));
		}
		nodeStk.pop();
	}

	//Recursive body with std::vector in deserilization
	template <typename T>
	void XMLParser::parseElementFromXML(std::vector<T>* val)
	{
		tinyxml2::XMLElement* node = nodeStk.top();
		if (std::string(node->FindAttribute("type")->Value()) != "std_vector") {
			std::cout << "type is NOT std_vector" << std::endl;
			return;
		}
		val->resize(node->FindAttribute("capacity")->IntValue());
		node = node->FirstChildElement();
		for (int i = 0; node != nullptr; i++, node = node->NextSiblingElement())
		{
			nodeStk.push(node);
			{ parseElementFromXML(&((*val)[i])); }
			nodeStk.pop();
		}
	}

	//Recursive body with std::list in deserilization
	template <typename T>
	void XMLParser::parseElementFromXML(std::list<T>* val)
	{
		tinyxml2::XMLElement* node = nodeStk.top();
		if (std::string(node->FindAttribute("type")->Value()) != "std_list") {
			std::cout << "type is NOT std_list" << std::endl;
			return;
		}
		node = node->FirstChildElement();
		for (; node != nullptr; node = node->NextSiblingElement())
		{
			T* tmp = new T;
			nodeStk.push(node);
			{ parseElementFromXML(tmp); }
			nodeStk.pop();
			val->push_back(*tmp);
			delete tmp;
		}
	}

	//Recursive body with std::set in deserilization
	template <typename T>
	void XMLParser::parseElementFromXML(std::set<T>* val)
	{
		tinyxml2::XMLElement* node = nodeStk.top();
		if (std::string(node->FindAttribute("type")->Value()) != "std_set") {
			std::cout << "type is NOT std_set" << std::endl;
			return;
		}
		node = node->FirstChildElement();
		for (; node != nullptr; node = node->NextSiblingElement())
		{
			T* tmp = new T;
			nodeStk.push(node);
			{ parseElementFromXML(tmp); }
			nodeStk.pop();
			val->insert(*tmp);
			delete tmp;
		}
	}

	//Recursive body with std::map in deserilization
	template <typename K, typename V>
	void XMLParser::parseElementFromXML(std::map<K, V>* val)
	{
		tinyxml2::XMLElement* node = nodeStk.top();
		if (std::string(node->FindAttribute("type")->Value()) != "std_map") {
			std::cout << "type is NOT std_map" << std::endl;
			return;
		}
		node = node->FirstChildElement();
		for (; node != nullptr; node = node->NextSiblingElement())
		{
			K* tmpK = new K;
			V* tmpV = new V;
			nodeStk.push(node);
			{ parseElementFromXML(tmpK); }
			nodeStk.pop();
			node = node->NextSiblingElement();
			if (node == nullptr) {
				std::cout << "type is NOT std_map" << std::endl;
				delete tmpK; delete tmpV;
				return;
			}
			nodeStk.push(node);
			{ parseElementFromXML(tmpV); }
			nodeStk.pop();
			(*val)[*tmpK] = *tmpV;
			delete tmpK; delete tmpV;
		}
	}
}