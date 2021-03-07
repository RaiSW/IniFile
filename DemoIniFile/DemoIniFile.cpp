// DemoIniFile.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "IniFile.h"

int main()
{
    string s,sec;
    int i;
    float f;
    bool b;
    IniFile ini("data.txt");
    if (!ini.FileExist()) {
        cout << "File not Exist" << endl;
        exit(1);
    }
    sec = "Section1";
    s = ini.ReadString(sec, "ZEile_1", "default");
    cout << s << endl;
    s = ini.ReadString(sec, "Zeile_2", "default");
    cout << s << endl;
    s = ini.ReadString(sec, "Zeile_3", "default");
    cout << s << endl;
    i = ini.ReadInteger(sec, "Zeile_4", 222);
    cout << i << endl;
    f = ini.ReadFloat(sec, "Zeile_5", 1.11f);
    cout << f << endl;
    b = ini.ReadBoolean(sec, "Zeile_6", 0);
    cout << (b?"true":"false") << endl;
    s = ini.ReadString("Section2", "Gap1", "default");
    cout << s << endl;
    i = ini.ReadInteger(sec, "Int2", 1234567);
    cout << i << endl;
    f = ini.ReadFloat(sec, "Float1", 1.00001f);
    cout << f << endl;
    b = ini.ReadBoolean(sec, "Bool1", 0);
    cout << (b ? "true" : "false") << endl;

    cout << endl;

    ini.WriteString(sec, "Zeile_1", "write 1");
   // ini.WriteString(sec, "Zeile_2", "write 22");
   // ini.WriteString(sec, "neue Zeile", "Hallo");
   // ini.WriteString("Section2", "neue Zeile", "Fenster");
   // ini.WriteString("Section3", "Sektionskey3", "Wert");
   // ini.WriteString("Neue Sektion", "newSecKey", "wert");
    ini.WriteInteger("Section3", "Int1", 111);
    ini.WriteInteger(sec, "Int2", 4444);
    ini.WriteFloat(sec, "Float1", 2.1234e3);
    ini.WriteBoolean(sec, "Bool1", true);
    ini.WriteString("Section4", "Zeile10", "Hallo");
    ini.WriteInteger("Section5", "NeuerWert", 258);
   
    ini.printIniFile();
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
