//all code copyright(c) 2011 Michael Ebert -- all rights reserved
//LEVEL 2 FILE

//in PrOgReSs =)
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h" //LEVEL 0
#include "utilities.h" //LEVEL 0
#include "camera.h"
int numberofUnits=0;
using namespace std;

class person {
public:
	int posy;
	int posx;
	string name;
	string icon;
	bool alive;
	string weapon;
	float CR;
	int level; //total class level.

	person();
	person(int x, int y);
	person(int x, int y, int idnumber);
	void SetPos(int a, int b);
	void SetPosX(int a);
	void SetPosY(int b);
	bool move(char d);
	void drawspr(void);
	void update(void);
	void aiMove(void);
	float attack(void);
	float damage(void);
	char hitcalc(int attack, int damage);//hit calculation: does an attack hit? also does damage, etc.
	int addxp(float ChallengeRating); //can't use abbreviation CR because that's used in the character class already.
	bool levelup(void); //checks for levelup. also does levelup functions.


private:
	LPDIRECT3DTEXTURE9 d3dTex;
	LPSTR lpcharname;
	LPD3DXSPRITE d3dIco;
	D3DXVECTOR3 pos3D;
	bool init;
	int hp;
	int id;
	int AB; //Attack Bonus
	int AC; //...    Armor Class. You should know this one.
	int xp;
	char faction;
	
	bool damageNdead(int damage);	
};

person::person() {
	//this is for the array of people. DO NOT USE OTHERWISE. special modifications made.
	posx = 0;
	posy = 0;
	name = "Default name";
	alive=0;
	icon="ftr";
	init=0;
	hp=6;
	AB=0;
	AC=0;
	CR=0.5;
	pos3D.z=0;
	id=5;
	weapon="unarmed";
}

person::person(int x, int y) {
	posx=x;
	posy=y;
	name = "Default";
	alive=1;
	numberofUnits++;
	icon="ftr";
	init=0;
	hp=6;
	AB=0;
	AC=10;
	CR=0.5;
	id=5;
	weapon="unarmed";
	pos3D.x=(float)(posx-theCamera.getX())*64;
	pos3D.y=(float)(posy-theCamera.getY())*64;
	pos3D.z=0;
	updateCollisionGrid(posx,posy,id);
}

person::person(int x, int y,int idnumber) {
	posx=x;
	posy=y;
	name = "Default";
	alive=1;
	numberofUnits++;
	icon="ftr";
	init=0;
	hp=6;
	AB=0;
	AC=10;
	CR=0.5;
	id=idnumber;
	weapon="unarmed";
	pos3D.x=(float)(posx-theCamera.getX())*64;
	pos3D.y=(float)(posy-theCamera.getY())*64;
	pos3D.z=0;
	updateCollisionGrid(posx,posy,id);
}


void person::SetPos(int a, int b) {
	updateCollisionGrid(posx, posy, 0);
	posx=a;
	posy=b;
	pos3D.x=(float)(posx-theCamera.getX())*64;
	pos3D.y=(float)(posy-theCamera.getY())*64;
	updateCollisionGrid(posx,posy,id);
}

bool person::move(char d)
{
	if (collisionCheck(posx,posy,d)==0)
	{
		updateCollisionGrid(posx,posy,0);
		if (d=='r' && posx<11)
			posx++;
		else if (d=='l' && posx>0)
			posx--;
		else if (d=='u' && posy>0)
			posy--;
		else if (d=='d' && posy<7)
			posy++;
		pos3D.x=(float)(posx-theCamera.getX())*64;
		pos3D.y=(float)(posy-theCamera.getY())*64;
		updateCollisionGrid(posx,posy,id);
		return 0;
	}
	//if there is a collision...
	else return 1;
}

void person::drawspr(void)
{
	if (init==0)
	{
		icon+="ico64x.bmp";
		init=1;
	}
	if (alive==0)
		return;
	update();
	lpcharname=new char [icon.size()+1];
	strcpy(lpcharname, icon.c_str());
	D3DXCreateTextureFromFile(d3dDevice, lpcharname, &d3dTex);
	if (FAILED(D3DXCreateTextureFromFile(d3dDevice, lpcharname, &d3dTex)))
	{
		MessageBox(NULL, "Error: Could not find texture.", "Grats! You broke it.",MB_ICONEXCLAMATION | MB_OK);
	}
    //drawing a sprite
	d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
    d3dSprite->Draw(d3dTex, NULL, NULL, &pos3D, 0xFFFFFFFF);
	d3dSprite->End();
}

void person::update(void)
{
     pos3D.x=(float)(posx-theCamera.getX())*64;
     pos3D.y=(float)(posy-theCamera.getY())*64;
     return;
}

void person::aiMove(void)
{
	char a=0;
	char b=0;
	for (a=0;a<12;a++)
	{
		for (b=0;b<8;b++)
		{
			if (grid[a][b]<5&&grid[a][b]>0)
			{
				if (abs(a-posx)+abs(b-posy)<=5)
				{
					//start movement here
					//both offset
					if (a!=posx && b!=posy)
					{
						if (roll(1,2)>1)
						{
							if (a>posx)
								move('r');
							else if (a<posx)
								move('l');
						}
						else
						{
							if (b>posy)
								move('d');
							else if (b<posy)
								move('u');
						}
					}
					
					//only y difference
					else if (a == posx && b!= posy)
					{
						if (b>posy)
							move('d');
						else if (b<posy)
							move('u');
					}
					
					//only x difference
					else if (a != posx && b== posy)
					{
						if (a>posx)
							move('r');
						else if (a<posx)
							move('l');
					}
				}
				else
				{
					int r=roll(1,4);
					if (r==1)
						move('u');
					else if (r==2)
						move('l');
					else if (r==3)
						move('r');
					else if (r==4)
						move('d');
				}
			}
		}
	}
}

float person::attack(void)
		/*This function returns attack and damage results (whole number=attack, decimal portion= damage).
		max damage=99. no max attack roll.
		TODO:
		currently 1d4 damage hard coded.
		add in STR bonus (once I get around to adding stats, that is.)
		Add in critical hits*/
{
	return (float)(roll(1,20)+AB);
}

float person::damage(void)
{
	return (float)roll(1,4);
}

bool person::damageNdead(int damage)
//return values: 0=not dead 1=dead.
{
	hp=hp-damage;
	if (hp<0)
	{
		alive=0;
		numberofUnits--;
		updateCollisionGrid(posx,posy,0);
		return 1;
	}
	return 0;
}


char person::hitcalc(int attack, int damage)
//returns- 1=hit(?) 0=miss
{
	if (attack<AC)
		return 0;
	//[next line]:the +1 is there so functions can tell the difference between hitcalc returning 0 (attack didnt hit)
	//and damaged returning 0(still alive).
	return person::damageNdead(damage)+1;
}

int person::addxp(float ChallengeRating)
{
	float tempxp;
	if (ChallengeRating<=1)
		tempxp=(xptable[level-1][0]*ChallengeRating);
	else
	{
		int tempcr=(int)floor(ChallengeRating);
		tempxp=(float)xptable[level-1][tempcr-1];
	}
	xp+=(int)tempxp;
	return (int)floor(tempxp);
}

bool person::levelup(void)
{
	if (xp>=levelxptable[level-1])
	{
		level++;
		CR=(float)level;
		return 1; //used to be return level. not sure why...
	}
	else
		return 0;
}

////////////////////////////////
//
//non-(person(class)) functions
//
////////////////////////////////

#endif
