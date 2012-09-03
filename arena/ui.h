#ifndef UI_H
#define UI_H

#include <string>
#include "menu.h"

//(theoretically) creating windows.   //f*k it, doing specific window for shop. Can generalize later.
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
	//menu* shopMenu; //<------ remove to generalize
	//string windowType; //window types: "MENU"  -only one so far.  ----for later.
	string borderImagePath;
	int borderImageHeight; //width==1. always.
	LPDIRECT3DTEXTURE9 d3dBorderTex;
	LPDIRECT3DTEXTURE9 d3dBorderCornerTex;
	char* borderCstr;
	char* cornerCstr;

	void initTextures(void);
	void initMenu(void);

};

ArenaWindow::ArenaWindow(int windowPosX, int windowPosY,
						 int width,      int height, 
						 string borderImageFile, int borderImageHeight)
{
	d3dBorderTex=NULL;
	d3dBorderCornerTex=NULL;
	isShowing=0;
	windowX=windowPosX;
	windowY=windowPosY;
	windowWidth=width;
	windowHeight=height;
	borderImagePath=borderImageFile;
	borderImageHeight=borderImageHeight;
	initTextures();
	//initMenu();
}

ArenaWindow::~ArenaWindow(){d3dBorderTex->Release();d3dBorderCornerTex->Release();/*delete shopMenu*/;} //<------put window thing into an if to generalize

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

/*void ArenaWindow::initMenu(void)
{
	shopMenu = new menu(3, {"testheal","item2","item3"},{1,4,8})
}
*/
void ArenaWindow::draw(void)
{
	//ohgodohgodohgod
	return;
}
//ArenaWindow shopWindow (width, height, borderimagefile, borderimageheight)?? I guess good for now...






























#endif