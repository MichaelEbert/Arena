#ifndef IMPORT_H
#define IMPORT_H
//split off of main.cpp
#include <string>
#include <fstream>

char bytevalue,mapDataWidth,mapDataHeight;
char* pMapDatax;
fstream mapfile;
string currentMapFile;


bool readMap(string title)
{
	mapfile.open(title,fstream::in | fstream::out | fstream::binary);
	if (!mapfile.is_open())
	{
		return 1;
	}
	mapfile.get(mapDataWidth);
	mapfile.get(mapDataHeight);
	/*char* */pMapDatax = new char[mapDataWidth*mapDataHeight];
	for( unsigned char readY=0;readY<mapDataHeight;readY++)
	{
		for (unsigned char readX=0;readX<mapDataWidth;readX++)
		{
			if(!mapfile.eof())
			{
				mapfile.get(pMapDatax[readY*mapDataWidth+readX]);
			}
		}
	}
	return 0;

}

void delMap(void)
{
	mapfile.close();
	delete[] pMapDatax;
}

void changeMap(void)
{
	if (currentMapFile=="map1.arm")
	{currentMapFile="map0.arm";}
	else
	{currentMapFile="map1.arm";}
	delMap();
	readMap(currentMapFile);
}













#endif IMPORT_H