//all code copyright(c) 2011 Michael Ebert -- all rights reserved
//LEVEL 0 FILE
#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctime>
#include <sstream>


using namespace std;

////////////////
//'dice' (random numbers)
////////////////
void seedRand(void)
{
	srand((unsigned)time(0));
}

int roll(int n, int s)
{
	int val=0;
	int i;
	for(i=0;i<n;i++)
	{
		val+= (rand()%s)+1;
	}
	return val;
}

////////////////
//integer->string
////////////////

string itos(int num)
{
	int i = num;
	std::string s;
	std::stringstream out;
	out << i;
	s = out.str();
	return s;
}

////////////////
//c++ string to c string
////////////////


////////////////
//Is a number in specified range?
////////////////
bool inRange_C(char x,char y, char boundX, char boundY, char XRange, char YRange, bool inside)
{
	if(inside)
	{
		if (x>=boundX && y>=boundY && x<=(boundX+XRange) && y<=(boundY+YRange)){
			return true;
		}
		else
		{
			return false;
		}
	}
	if(!inside)
	{
		if((x<boundX)&&(y<boundY)&& x>(boundX+XRange)&& y>(boundY+YRange)){
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}





////////////////
//unarmed weapon stats(default)
////////////////

//struct damageM
//{
//	char n;
//	char s;
//}
//
//
//struct weapon
//{
//	string name;
//	int cost;
//	int range;
//	int weight;
//	char damageMN;
//	char damageMS;
//	string type;
//
//	/*struct damageS
//	{
//		char n;
//		char s;
//	}
//	struct damageM
//	{
//		char n;
//		char s;
//	}*/
//}

//
//
//void initiateWeaponUnarmed(void)
//{
//	weapon unarmed

//hmmm... I guess that currently this is the best place to put this.
/*
XP TABLE STUFF
*/
//currently only doing character levels 1-3 and CR 1-3. 
int xptable[3][3];
int levelxptable[3];
bool initXP(void)
{
	xptable[0][0]=300;xptable[0][1]=600;xptable[0][2]=900;
	xptable[1][0]=300;xptable[1][1]=600;xptable[1][2]=900;
	xptable[2][0]=300;xptable[2][1]=600;xptable[2][2]=900;
	
	levelxptable[0]=1000;levelxptable[1]=3000;levelxptable[2]=6000;
	return 1;
}


#endif
