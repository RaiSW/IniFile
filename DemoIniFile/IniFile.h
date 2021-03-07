#pragma once
#include <fstream>
#include <list>

 #define INI_FILE_TEST

using namespace std;

class IniFile
{
public:
	IniFile(string fileName);
	bool FileExist(void);
	int ReadInteger(string szSection, string szKey, int iDefaultValue);
	float ReadFloat(string szSection, string szKey, float fltDefaultValue);
	bool ReadBoolean(string szSection, string szKey, bool bolDefaultValue);
	string ReadString(string szSection, string szKey, string szDefaultValue);
	void WriteInteger(string szSection, string szKey, int iValue);
	void WriteString(string szSection, string szKey, string szValue);
private:
	string fileName;
	fstream file;
	bool findFile;
	list<string> txtList;
	bool getKey(string sec, string key, string &value);
	bool findSection(list<string>::iterator &it, string section);
	bool findKey(list<string>::iterator &it, string key);
	void findEndofSection(list<string>::iterator& it);
	void writeIniFile(void);
	void printIniFile(void);
};


