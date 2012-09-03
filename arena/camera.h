#ifndef CAMERA_H
#define CAMERA_H
#include "utilities.h"
using namespace std;

class camera {
public:
	camera();
	char getX();
	char getY();
	void snapCamera(char x, char y);
	bool inView(char x, char y);
	bool move(char direction);
private:
	char cameraX;
	char cameraY;
	char width;//width and height are measured in GAME SQUARES.default zoom is 12x8
	char height; 
};

camera::camera()
{
	cameraX=0;
	cameraY=0;
	width=12;
	height=8;
}

char camera::getX(){return cameraX;}
char camera::getY(){return cameraY;}

void camera::snapCamera(char x, char y)
{
	cameraX=x;
	cameraY=y;
}

bool camera::inView(char x, char y)
{
     if(inRange_C(x,y,cameraX,cameraY,width-1,height-1,1))
     {return true;}
     else
     {return false;}
}

bool camera::move(char direction)
{
    if ((cameraX <= 0 && direction=='l')||(cameraY<= 0 && direction=='u'))
		return 1;
	if ((cameraX >= 14 && direction=='r')||(cameraY >= 11 && direction=='d'))
		return 1;
	if (direction=='r')
		cameraX++;
	else if (direction=='l')
		cameraX--;
	else if (direction=='u')
		cameraY--;
	else if (direction=='d')
		cameraY++;
	return 0;
}
#endif
