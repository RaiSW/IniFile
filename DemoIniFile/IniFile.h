//*********************************************************************************
// Die Klasse IniFile stellt die Funktionen der in den alten Windowsversionen
// üblichen Initialisierungsfiles zur Verfügung. Sie ist einfach aufgebaut und kann
// im Gegensatz zum Vorbild auch problemlos in 32- und 64-bit Programmen genutzt
// werden.
// Der Aufbau der Files erfolgt in Sektionen (in eckigen Klammern), Schlüsselwerte
// und Werte. Kommentare können mit einem ";" eingeleitet werden und bleiben auch
// nach dem Ändern von Werten erhalten.
// Bei allen Schlüsselwörten wird Groß- und Kleinschreibung berücksichtigt.
// Die Werte der Schlüsselwörter können Strings, Integer, Float und Boolean
// (false, true) sein. Hexadezimale Werte werden als Integer eingelesen und müssen
// mit "0x" beginnen. Zum Schreiben von Hex-Werten muss die Funktion WriteHex
// genommen werden.
//
// Funktionsweise:
// Beim Anlegen einer IniFile-Instanz wird das File geöffnet und Zeile für Zeile in
// eine Liste in den Speicher übernommen.
// Ob das File gefunden wurde, kann im Anschluss mit der Funktion FileExist()
// überprüft werden.
// Alle folgenden Read-Befehle holen die Werte aus dieser Liste. Werden Werte nicht
// gefunden, wird ein Defaultwert zurückgegeben, der beim Aufruf der Read-Funktion
// mit angegben wurde.
// Schreibbefehle erfolgen auch in diese Liste und sie wird ggf. erweitert.
// Dabei wird erst geprüft, ob die angegebene Sektion und das Schlüsslwort existiert.
// Fehlt eines, wird das Schlüsselwort und ggf. auch die Sektion neu angelegt.
// Wurde beides gefunden, dann wird der Wert neu geschrieben und ggf. ein
// vorhandener Kommentar übernommen.
// Nach einem Schreibbefehl wird die komplette Liste unter dem gleichen Namen
// abgespeichert, mit dem sie bei der Instanzierung geöffnet wurde. 
//
// Beispiel für eine Filestruktur:
//   ; Demofile
//   [Section_1]
//   String_1=value1  ; window header
//   height=14.5      ; window height
//   fill=true
//
//   [Section_2]
//   version=110
//
// Abhängigkeiten:
// Die Klasse benötigt folgende Stringfunktionen, die zur Vefügung gestellt werden
// müssen - hier in lib.cpp zur Verfügung gestellt
//  string ltrim(const string& s) - führende Leerzeichen eines String entfernen 
//  string rtrim(const string& s) - nachfolgende Leerzeichen eines String entfernen
//  string UCase(string s)        - String in Grossbuchstaben ändern
//
// Autor: Rainer Henkner, 07.03.2021
//*********************************************************************************

#pragma once
#include <fstream>
#include <list>

using namespace std;

// Der define stellt die Funktion printIniFile() zur Verfügung,
// der für Testzwecke die Liste auf die Console ausgibt
// #define INI_FILE_TEST

class IniFile
{
public:
	IniFile(string fileName);
	bool FileExist(void);
	int ReadInteger(string section, string key, int iDefaultValue);
	float ReadFloat(string section, string key, float fDefaultValue);
	bool ReadBoolean(string section, string key, bool bDefaultValue);
	string ReadString(string section, string key, string sDefaultValue);
	void WriteInteger(string section, string key, int iValue);
	void WriteHex(string section, string key, int iValue);
	void WriteFloat(string section, string key, float fValue);
	void WriteBoolean(string section, string key, bool bValue);
	void WriteString(string section, string key, string szValue);
#ifdef INI_FILE_TEST
	void printIniFile(void);
#endif
private:
	string fileName;
	fstream file;
	bool findFile;
	list<string> txtList;
	bool getKey(string sec, string key, string &value);
	bool findSection(list<string>::iterator &it, string section);
	bool findKey(list<string>::iterator &it, string key);
	void findEndOfSection(list<string>::iterator& it);
	void writeIniFile(void);
};
