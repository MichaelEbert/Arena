//all code copyright(c) 2011 Michael Ebert -- all rights reserved
//LEVEL 0 FILE
#ifndef COLLISION_H
#define COLLISION_H

unsigned char grid[15][12];

//0=no collision, 1= collision
bool collisionCheck(char a, char b, char d)
{
	if ((a <= 0 && d=='l')||(b<= 0 && d=='u'))
		return 1;
	if ((a >= 14 && d=='r')||(b >= 11 && d=='d'))
		return 1;
	if (d=='r')
		a++;
	else if (d=='l')
		a--;
	else if (d=='u')
		b--;
	else if (d=='d')
		b++;
	if (grid[a][b] != 0)
		return 1;
	return 0;
}

bool oobCheck(char a, char b, char d)
//oob=Out Of Bounds(playable map area)
{
	if ((a <= 0 && d=='l')||(b<= 0 && d=='u'))
		return 1;
	if ((a >= 14 && d=='r')||(b >= 11 && d=='d'))
		return 1;
	return 0;
}
void updateCollisionGrid(char a, char b, char p)
//a=x position; b= y position; p = character ID; 
{
	grid[a][b]=p;
}
void clearCollisionGrid(void)
{
	for(char a=0;a<5;a++){}
}
#endif
