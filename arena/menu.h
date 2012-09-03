#ifndef MENU_H
#define MENU_H

//#include <string>

class menu{
public:
	menu(int numberOfEntries, string entryNames[], int entryValues[]);
	~menu();
	string getEntryText(int entry);
	int getEntryValue(int entry);
	int getNumEntries();
private:
	int numEntries;
	string* entryList;
	int* entryVals;
};

menu::menu(int numberOfEntries, string entryNames[], int entryValues[])
{
	entryList=new string[numberOfEntries];
	entryList=entryNames;
	entryVals=new int[numberOfEntries];
	entryVals=entryValues;
}

menu::~menu(){delete[] entryList;delete[] entryVals;}

string menu::getEntryText(int entry){return entryList[entry];}

int menu::getEntryValue(int entry){return entryVals[entry];}

int menu::getNumEntries(){return numEntries;}

#endif