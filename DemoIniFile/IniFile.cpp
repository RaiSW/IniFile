#include "IniFile.h"
#include <iostream>
#include <string>
#include "lib.h"

IniFile::IniFile(string fileName)
{
	string s;
	this->fileName = fileName;
	
	findFile = false;
	file.open(fileName, ios::in);
	if (!file.fail())
	{
		findFile = true;
		while (getline(file, s))
		{
			txtList.push_back(s);
		}
		file.close();
	}
}

int IniFile::ReadInteger(string szSection, string szKey, int iDefaultValue)
{
	string s;
	int i = iDefaultValue;

	if (this->getKey(szSection, szKey, s))
	{
		try
		{
			i = stoi(s);
		}
		catch (...) {}
	}
	return i;
}

float IniFile::ReadFloat(string szSection, string szKey, float fltDefaultValue)
{
	string s;
	float f= fltDefaultValue;

	if (this->getKey(szSection, szKey, s))
	{
		try
		{
			f = stof(s);
		}
		catch (...) {}
	}
	return f;
}

bool IniFile::ReadBoolean(string szSection, string szKey, bool bolDefaultValue)
{
	string s;
	bool b = bolDefaultValue;

	if (this->getKey(szSection, szKey, s))
	{
		try
		{
		if (UCase(s) == "TRUE")
			b = true;
		else
			b = false;
		}
		catch (...) {}
	}
	return b;
}

string IniFile::ReadString(string szSection, string szKey, string szDefaultValue)
{
	string s;
	
	return this->getKey(szSection, szKey, s) ? s : szDefaultValue;
}

void WriteInteger(string szSection, string szKey, int iValue)
{

}

void IniFile::WriteString(string szSection, string szKey, string szValue)
{
	string s;
	string comment = "";
	list<string>::iterator it;
	list<string>::iterator itSec;

	if (this->findSection(it, szSection))
	{
		// Section vorhanden
		it++;
		itSec = it;
		if (this->findKey(it, szKey))
		{
			// Key vorhanden
			s = ltrim(*it);
			int start = s.find_first_of(';');
			if (start > 0)
			{
				comment = " " + s.substr(start, s.length() - start);
			}
			start = s.find_first_of('=') + 1;
			s.erase(start, s.length());
			s = s + szValue + comment;
			txtList.insert(it, s);
			txtList.erase(it);
		}
		else
		{
			// neuer Key
			this->findEndofSection(itSec);
			s = szKey + "=" + szValue;
			txtList.insert(itSec, s);
		}
	}
	else
	{
		// neue Section
		txtList.insert(it, "");
		s = "[" + szSection + "]";
		txtList.insert(it, s);
		s = szKey + "=" + szValue;
		txtList.insert(it, s);
	}

	this->writeIniFile();

#ifdef INI_FILE_DEF
	this->printIniFile();
#endif
}

bool IniFile::FileExist()
{
	return findFile;
}

//**********************************************************
//******************* Private Functions ********************

bool IniFile::getKey(string sec, string key, string &value)
{
	string s = "";
	list<string>::iterator it;
	bool found = false;

	if (this->findSection(it, sec))
	{
		// Section wurde gefunden
		it++;
		if (this->findKey(it, key))
		{
			// Key gefunden
			found = true;
			s = *it;
			int start = s.find_first_of('=') + 1;
			s = s.substr(start, s.length() - start);
			start = s.find_first_of(';');
			if (start >= 0)
			{
				s.erase(start, s.length());
			}
			s = rtrim(s);
		}
	}
	value = s;
	return found;
}

bool IniFile::findSection(list<string>::iterator &it, string section)
{
	bool found = false;
	it = find(txtList.begin(), txtList.end(), "[" + section + "]");
	if (it != txtList.end()) found = true;
	return found;
}

void IniFile::findEndofSection(list<string>::iterator& it)
{
	string s;
	list<string>::iterator itEndSection = it;

	while(it != txtList.end())
	{
		s = ltrim(*it);
		if (s[0] == '[')
			// hier beginnt schon die nächste Section
			break;
		if (s.length() != 0)
			itEndSection = it;
		it++;
	}
	it = ++itEndSection;
}

bool IniFile::findKey(list<string>::iterator &it, string key)
{
	bool found = false;
	string s;

	while (it != txtList.end())
	{
		s = ltrim(*it);
		if (s[0] == '[')
			// Schleife abbrechen, wenn nächste Section gefunden wird
			break;
		int pos = s.find(key + "=");
		if (pos >= 0)
		{
			// Key gefunden
			found = true;
			break;
		}
		it++;
	}
	return found;
}

void IniFile::writeIniFile(void)
{
	file.open(fileName+"1", ios::out);
	if (!file.fail())
	{
		for (auto i : txtList)
		{
			file << i << endl;
		}
		file.close();
	}
}

//**********************************************************
//******************** Test Functions **********************

#ifdef INI_FILE_TEST
void IniFile::printIniFile(void)
{
	for (auto i : txtList)
	{
		cout << i << endl;
	}
	cout << endl;
}
#endif
