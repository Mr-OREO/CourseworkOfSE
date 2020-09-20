#pragma once
#include <typeinfo>

//Enum: XMLTypeID
//Usage: Used for indentifying the type in XMLParser
typedef enum {
	CHAR,
	CONST_CHAR,
	BOOL,
	INT,
	CONST_INT,
	FLOAT,
	CONST_FLOAT,
	DOUBLE,
	STRING,
	STLPAIR,
	STLVECT,
	STLLIST,
	STLSET,
	STLMAP,
	NONE
}XMLTypeID;

//Func: getXMLTypeID
//Usage: Gains the XMLTypeID from typeid(T)
template <typename T>
static XMLTypeID getXMLTypeID(T*)
{
	const type_info& tpif = typeid(T);
	if (tpif == typeid(char))
		return CHAR;
	//else if (tpif == typeid(const char))
	//	return CONST_CHAR;
	else if (tpif == typeid(bool))
		return BOOL;
	else if (tpif == typeid(int))
		return INT;
	//else if (tpif == typeid(const int))
	//	return CONST_INT;
	else if (tpif == typeid(float))
		return FLOAT;
	//else if (tpif == typeid(const float))
	//	return CONST_FLOAT;
	else if (tpif == typeid(double))
		return DOUBLE;
	else if (tpif == typeid(std::string))
		return STRING;
	else
		return NONE;
}

//Class: Member
//Usage: Represents a member variable in a struct
//	stores its member ptr and type info
template <typename Obj>
class Member
{
public:
	//Construction Function
	//basic type
	template <typename T>
	Member(T Obj::* ptr) {
		this->ptr = reinterpret_cast<void* Obj::*> (ptr);
		T* typePtr = nullptr;
		type = getXMLTypeID(typePtr);
	}
	//STL Container
	template <typename K, typename V>
	Member(std::pair<K, V> Obj::* ptr) {
		this->ptr = reinterpret_cast<void* Obj::*> (ptr);
		type = STLPAIR;
		K* p0TypePtr = nullptr; V* p1TypePtr = nullptr;
		p0type = getXMLTypeID(p0TypePtr); p1type = getXMLTypeID(p1TypePtr);
	}
	template <typename T>
	Member(std::vector<T> Obj::* ptr) {
		this->ptr = reinterpret_cast<void* Obj::*> (ptr);
		type = STLVECT;
		T* p0TypePtr = nullptr;
		p0type = getXMLTypeID(p0TypePtr);
	}
	template <typename T>
	Member(std::list<T> Obj::* ptr) {
		this->ptr = reinterpret_cast<void* Obj::*> (ptr);
		type = STLLIST;
		T* p0TypePtr = nullptr;
		p0type = getXMLTypeID(p0TypePtr);
	}
	template <typename T>
	Member(std::set<T> Obj::* ptr) {
		this->ptr = reinterpret_cast<void* Obj::*> (ptr);
		type = STLSET;
		T* p0TypePtr = nullptr;
		p0type = getXMLTypeID(p0TypePtr);
	}
	template <typename K, typename V>
	Member(std::map<K, V> Obj::* ptr) {
		this->ptr = reinterpret_cast<void* Obj::*> (ptr);
		type = STLMAP;
		K* p0TypePtr = nullptr; V* p1TypePtr = nullptr;
		p0type = getXMLTypeID(p0TypePtr); p1type = getXMLTypeID(p1TypePtr);
	}
	//return the member ptr
	void* Obj::* getPtr() {
		return ptr;
	}
	//get its type
	XMLTypeID getType() {
		return type;
	}
	//get the type of the first Template Parameter(if needed)
	//like the K in vector<K>
	XMLTypeID getP0Type() {
		return p0type;
	}
	//get the type of the second Template Parameter(if needed)
	//like the V in map<K,V>
	XMLTypeID getP1Type() {
		return p1type;
	}
private:
	void* Obj::* ptr;
	//typeID
	XMLTypeID type;
	//parameter typeID of Template Parameter
	//used for STL Container
	XMLTypeID p0type = NONE, p1type = NONE;
};

//Class: Reflection
//Usage: Binds a user defined type and builds a mapping
//	such as <member_name, (member_ptr, member_typeID)>
template <typename Obj>
class Reflection
{
public:
	Reflection() {
		structname = typeid(Obj).name();
	}
	//used for instance a Reflection obj with struct Obj
	static Reflection& instance() {
		static Reflection inst;
		return inst;
	}
	//regist one member variable in struct Obj
	template <typename T>
	Reflection& regist(T Obj::* ptr, std::string name) {
		members[name] = new Member<Obj>(ptr);
		return *this;
	}
	//get the struct name
	std::string& name() {
		return structname;
	}
	//get all Members of this struct
	std::map<std::string, Member<Obj>*>& getMems() {
		return members;
	}
	//get the Member named name
	Member<Obj>* getMem(std::string name) {
		if (members.find(name) == members.end())
			return nullptr;
		return members[name];
	}
private:
	//<member_name, (member_ptr, member_typeID)>
	std::map<std::string, Member<Obj>*> members;
	//the name of this struct
	std::string structname;
};