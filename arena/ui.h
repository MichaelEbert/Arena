#ifndef UI_H
#define UI_H

#include <string>
#include "menu.h"

//(theoretically) creating windows.   //f*k it, doing specific window for shop. Can generalize later.

//I don't get sprites. So I'm just going to use one for the entire application. 
class ArenaWindow{
public:
	ArenaWindow(int windowPosX, int windowPosY, int width, int height, string borderImageFile, int borderImageHeight);
	~ArenaWindow();
	void hide(void);
	void show(void);
	void draw(void);

private:
	bool isShowing;
	int windowX;
	int windowY;
	int windowWidth;
	int windowHeight;
	menu* shopMenu; //<------ remove to generalize //pointer- so I can new() it.
	//string windowType; //window types: "MENU"  -only one so far.  ----for later.
	string borderImagePath;
	int borderImageHeight; //width==1. always.
	LPDIRECT3DTEXTURE9 d3dBorderTex;
	LPDIRECT3DTEXTURE9 d3dBorderCornerTex;
	D3DXVECTOR3 windowSpritePosition;
	char* borderCstr;
	char* cornerCstr;

	void initTextures(void);
	void initMenu(void);
	void drawFrame(void);

};

ArenaWindow::ArenaWindow(int windowPosX, int windowPosY,
						 int width,      int height, 
						 string borderImageFile, int borderImageHeight)
{
	d3dBorderTex=NULL;
	d3dBorderCornerTex=NULL;
	isShowing=false;
	windowX=windowPosX;
	windowY=windowPosY;
	windowWidth=width;
	windowHeight=height;
	borderImagePath=borderImageFile;
	borderImageHeight=borderImageHeight;
	initTextures();
	initMenu();
}

ArenaWindow::~ArenaWindow(){d3dBorderTex->Release();d3dBorderCornerTex->Release();delete shopMenu;} //<------put window thing into an if to generalize

void ArenaWindow::initTextures(void)
{	
	D3DXCreateTextureFromFile(d3dDevice, borderImagePath.c_str(), &d3dBorderTex);
	if (FAILED(D3DXCreateTextureFromFile(d3dDevice, borderImagePath.c_str(), &d3dBorderTex)))
	{
		MessageBox(NULL, "Error: Could not find texture <border image>", "Grats. You broke it.",MB_ICONEXCLAMATION | MB_OK);
	}
	D3DXCreateTextureFromFile(d3dDevice, borderImagePath.c_str(), &d3dBorderCornerTex);
	if (FAILED(D3DXCreateTextureFromFile(d3dDevice, borderImagePath.c_str(), &d3dBorderCornerTex)))
	{
		MessageBox(NULL, "Error: Could not find texture <corner image>", "Grats. You broke it.",MB_ICONEXCLAMATION | MB_OK);
	}
}

void ArenaWindow::initMenu(void)
{
	std::string menuitems[]={"testheal","item2","item3"};
	int menuitemcosts[]={1,4,8};
	shopMenu = new menu(3, menuitems,menuitemcosts);
}

void ArenaWindow::show(void)
{
	isShowing=true;
}

void ArenaWindow::hide(void)
{
	isShowing=false;
	//giveUpFocus(); //TODO: implement that.
}
void ArenaWindow::draw(void)
{
	if(isShowing)
	{
		d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
		windowSpritePosition.x=windowX;
		windowSpritePosition.y=windowY;

		drawFrame();

		d3dSprite->End();
		return;
	}
	else
	{
		return;
	}
}

void ArenaWindow::drawFrame(void)
{
	for(int currentX=windowX;currentX<(windowX+windowWidth);currentX++)
	{
		windowSpritePosition.x=currentX;
		d3dSprite->Draw(d3dBorderTex,NULL,NULL,&windowSpritePosition,0xFFFFFFFF);
	}
	windowSpritePosition.x=windowX;//reset X position
	for(int currentY=windowY;currentY<(windowY+windowHeight);currentY++)//this should be rotated, but ill do that later.
	{
		windowSpritePosition.y=currentY;
		d3dSprite->Draw(d3dBorderTex,NULL,NULL,&windowSpritePosition,0xFFFFFFFF);
	}



}
//ArenaWindow shopWindow (width, height, borderimagefile, borderimageheight)?? I guess good for now...

/*
when player position==(3,3)&&map==1
{
	shopMenuWindow.show();
	focus=shopMenuWindow;//now when the user moves, it moves the menu instead of the character.
	

	shopmenuwindow- relinquishFocus();




*/





















#endif