#pragma once
#include <iostream>
#include <string>
#include <map>

class base64Coder
{
public:
	//Construction Function
	base64Coder() {
		//initialize table
		char start = 'A';
		for (int i = 0; i < 26; i++)
			table[i] = start + (char)i;
		start = 'a';
		for (int i = 0; i < 26; i++)
			table[i + 26] = start + (char)i;
		start = '0';
		for (int i = 0; i < 10; i++)
			table[i + 52] = start + (char)i;
		table[62] = '+'; table[63] = '/';

		for (int i = 0; i < 63; i++)
			revtable[table[i]] = (unsigned char)i;
	}
	//encoder: binary to zijie
	void parseBinary2Zijie(std::string in, std::string out);
	//decoder: zijie to binary
	void parseZijie2Binary(std::string in, std::string out);
private:
	char table[64];
	std::map<char, unsigned char>revtable;
};

