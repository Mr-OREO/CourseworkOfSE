#include "base64Coder.h"
#include<fstream>

using namespace std;
void base64Coder::parseBinary2Zijie(std::string in, std::string out)
{
	ifstream is;
	ofstream os;
	is.open(in, ios::binary);
	os.open(out, ios::out);
	unsigned char three[3];
	int rest = 0;

	while (!is.eof())
	{
		three[0] = three[1] = three[2] = 0;
		is.read((char*)&three[0], sizeof(char));
		if (!is.eof())
		{
			is.read((char*)&three[1], sizeof(char));
			if (!is.eof())
				is.read((char*)&three[2], sizeof(char));
			else
				rest = 1;
		}
		else
			rest = 2;
		unsigned char tmp;
		tmp = three[0] >> 2; tmp = tmp & 0x3f;
		os << table[tmp];
		tmp = (three[0] << 6 >> 2) | (three[1] >> 4); tmp = tmp & 0x3f;
		os << table[tmp];
		tmp = (three[1] << 4 >> 2) | (three[2] >> 6); tmp = tmp & 0x3f;
		os << table[tmp];
		tmp = three[2] << 2 >> 2; tmp = tmp & 0x3f;
		os << table[tmp];
	}
	char eq = '=';
	for (int i = 0; i < rest; i++)
		os.write(&eq, sizeof(char));
	is.close();
	os.close();
}

void base64Coder::parseZijie2Binary(std::string in, std::string out)
{
	ifstream is;
	ofstream os;
	is.open(in, ios::in);
	os.open(out, ios::binary);
	unsigned char three[3];
	int rest = 0;
	long stoppos = 0;

	while (!is.eof())
	{
		char ch;
		is >> ch;
		if (ch == '=')rest++;
		if (stoppos == 0 && ch == '=')
			stoppos = is.tellg();
	}
	is.close();
	is.open(in, ios::in);

	while (!is.eof() && is.tellg() < stoppos - 1)
	{
		three[0] = three[1] = three[2] = 0;
		unsigned char tmp, tmp2;
		is >> tmp;
		tmp = revtable[(char)tmp];
		if (is.eof())
		{
			cout << "base64 error: zijie file NOT complete" << endl;
			break;
		}
		is >> tmp2;
		tmp2 = revtable[(char)tmp2];
		if (is.eof())
		{
			cout << "base64 error: zijie file NOT complete" << endl;
			break;
		}
		three[0] = (tmp << 2) | (tmp2 >> 4);
		is >> tmp;
		tmp = revtable[(char)tmp];
		if (is.eof())
		{
			cout << "base64 error: zijie file NOT complete" << endl;
			break;
		}
		three[1] = (tmp2 << 4) | (tmp >> 2);
		is >> tmp2;
		tmp2 = revtable[(char)tmp2];
		if (is.eof())
		{
			cout << "base64 error: zijie file NOT complete" << endl;
			break;
		}
		three[2] = (tmp << 6) | tmp2;
		if (is.eof())
			for (int i = 0; i < 3 - rest; i++)
				os.write((char*)&three[i], sizeof(char));
		else
			for (int i = 0; i < 3; i++)
				os.write((char*)&three[i], sizeof(char));
	}
	is.close();
	os.close();
}
