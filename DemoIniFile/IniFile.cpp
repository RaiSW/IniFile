#include "IniFile.h"
#include "lib.h"
#include <iostream>
#include <string>
#include <sstream>

//*********************************************************************************
// Konstruktor für die Klasse IniFile mit Übergabe es zu öffnen Files
//*********************************************************************************
IniFile::IniFile(string fileName)
{
	string s;
	this->fileName = fileName;
	
	findFile = false;
	file.open(fileName, ios::in);
	if (!file.fail())
	{
		findFile = true;
		// File zeilenweise einlesen und der Stringliste anhängen
		while (getline(file, s))
		{
			txtList.push_back(s);
		}
		file.close();
	}
}

//*********************************************************************************
// Lesen eines Integerwertes aus der Liste
//*********************************************************************************
int IniFile::ReadInteger(string szSection, string szKey, int iDefaultValue)
{
	string s;
	int i = iDefaultValue;

	// Holen des Wertes eines Keys als Teilstring
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

//*********************************************************************************
// Lesen eines Floatwertes aus der Liste
//*********************************************************************************
float IniFile::ReadFloat(string szSection, string szKey, float fDefaultValue)
{
	string s;
	float f= fDefaultValue;

	// Holen des Wertes eines Keys als Teilstring
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

//*********************************************************************************
// Lesen eines Boolwertes aus der Liste
//*********************************************************************************
bool IniFile::ReadBoolean(string szSection, string szKey, bool bDefaultValue)
{
	string s;
	bool b = bDefaultValue;

	// Holen des Wertes eines Keys als Teilstring
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

//*********************************************************************************
// Lesen eines Strings aus der Liste
//*********************************************************************************
string IniFile::ReadString(string szSection, string szKey, string szDefaultValue)
{
	string s;
	
	return this->getKey(szSection, szKey, s) ? s : szDefaultValue;
}

//*********************************************************************************
// Schreiben eines Integerwertes in die Liste
//*********************************************************************************
void IniFile::WriteInteger(string szSection, string szKey, int iValue)
{
	stringstream ss;
	ss << iValue;
	// Wert als String in die Liste schreiben
	this->WriteString(szSection, szKey, ss.str());
}

//*********************************************************************************
// Schreiben eines Floatwertes in die Liste
//*********************************************************************************
void IniFile::WriteFloat(string szSection, string szKey, float fValue)
{
	stringstream ss;
	ss << fValue;
	this->WriteString(szSection, szKey, ss.str());
}

//*********************************************************************************
// Schreiben eines Boolwertes in die Liste
//*********************************************************************************
void IniFile::WriteBoolean(string szSection, string szKey, bool bValue)
{
	string s = "false";
	if (bValue)
		s = "true";
	// Wert als String in die Liste schreiben
	this->WriteString(szSection, szKey, s);
}

//*********************************************************************************
// Schreiben eines Strings in die Liste
//*********************************************************************************
void IniFile::WriteString(string szSection, string szKey, string szValue)
{
	string s;
	string comment = "";          // Platzhalter für Kommentar
	list<string>::iterator it;    // Zeiger auf einen Listeintrag
	list<string>::iterator itSec; // Zeiger auf den Beginn einer Section

	// Section suchen
	if (this->findSection(it, szSection))
	{
		// Section vorhanden
		//todo it++;
		itSec = it; // Zeiger auf 1. Eintrag in der Section merken
		// Key suchen
		if (this->findKey(it, szKey))
		{
			// Key vorhanden
			s = ltrim(*it); // Leerzeichen links abschneiden
			
			// Falls am Ende d
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
			this->findEndOfSection(itSec);
			s = szKey + "=" + szValue;
			if (++itSec == txtList.end())
				txtList.push_back(s);
			else
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

void IniFile::findEndOfSection(list<string>::iterator& it)
{
	int noOfSearchSections = 1;
	string s;
	list<string>::iterator itEndSection = it;
	
	// Wenn das erste Element eine Section ist, dann muss die 2. Section gefunden werden
	s = ltrim(*it);
	if (s[0] == '[')
		noOfSearchSections = 2;
	
	while (it != txtList.end())
	{
		s = ltrim(*it);
		if (s[0] == '[')
		{
			if (--noOfSearchSections == 0)
			{
				// hier beginnt die nächste Section
				break;
			}
		}
		else if (s.length() != 0)
			itEndSection = it;
		it++;
	}
	it = itEndSection;
}

bool IniFile::findKey(list<string>::iterator &it, string key)
{
	int noOfSearchSections = 1;
	bool found = false;
	string s;

	// Wenn das erste Element eine Section ist, dann muss die 2. Section gefunden werden
	s = ltrim(*it);
	if (s[0] == '[')
		noOfSearchSections = 2;

	while (it != txtList.end())
	{
		s = ltrim(*it);
		if (s[0] == '[')
		{
			if (--noOfSearchSections == 0)
			{
				// hier beginnt die nächste Section
				break;
			}
		}
		else
		{
			int pos = s.find(key + "=");
			if (pos >= 0)
			{
				// Key gefunden
				found = true;
				break;
			}
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
	cout << "***** Ausgabe des Files *****" << endl;
	for (auto i : txtList)
	{
		cout << i << endl;
	}
	cout << endl;
}
#endif
