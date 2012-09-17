//LEVEL 3
//need to find way to re-render only part of the scene
//
//also – camera movement. I’m thinking grid size of 15x12 
//(3x4 more than current) to test on.
//11-30-11- library- edited collision.h to reflect new grid.
//Thanks to Keith Ditchburn (www.toymaker.info), Chris (www.directxtutorial.com),
//and Forest J. Handford (www.eastcoastgames.com) for the windows initialization 
//and DirectX stuff.
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include <windows.h>
#include <winuser.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windef.h>
#include <string>
#include "utilities.h" //LEVEL 0
#include "import.h"
#include "camera.h"

using namespace std;
LPSTR lpcharname;
LPSTR cTxtStrA;
LPSTR cTxtStrB;
LPSTR cTxtStrC;
LPDIRECT3D9 d3dObject=NULL;
LPDIRECT3DDEVICE9 d3dDevice=NULL;
LPDIRECT3DTEXTURE9 d3dGrassTex=NULL;
LPDIRECT3DTEXTURE9 d3dDirtTex=NULL;
LPDIRECT3DTEXTURE9 d3dPortalTex=NULL;
LPDIRECT3DTEXTURE9 d3dFtrTex=NULL;
LPD3DXSPRITE d3dSprite=NULL;
LPD3DXFONT d3dFont=NULL;

camera theCamera;
#include "person.h" //LEVEL 2
#include "ui.h"
person test[5];
person fighter (1,1,1);
person dummy (8,4,5);
//base
void initD3D(HWND hWnd);// sets up and initializes Direct3D
void initBaseGround(void);
void renderFrame(void);    // renders a single frame
void cleanD3D(void);      // closes Direct3D and releases memory (theoretically)
//drawings
void createBaseGrass(void); //loads sprite
void drawFtr(void);

void drawChar(string charname);
//texts
void displayTextA(void);
void displayTextB(void);
void displayTextC(string text);
void displayText(string text);
void renderText(void);

void sdisplayTextA(void);
void sdisplayTextB(void);
void sdisplayTextC(void);
void sdisplayText(void);
//turn
void playerTurn(void);
void turnmenu(void);
void playerMove(void);
void playerAttack(void);
void playerEnd(void);
//turn actions
void ftrtestmove(char d);
void ftrtestattack(char d);
//void dummeykey(void);

void killed(char index);

void spawnMonster(void);

D3DXVECTOR3 sprPos(0.0f,0.0f,0.0f);
D3DXVECTOR3 ftrPos3D(0.0f,0.0f,0.0f);

HWND hWnd;

int blu=100;
int red=100;
int grn=100;
int idmax=1;
bool up=1;
int turnID=0;
int turnPhase=0;
bool collision;
char portalturn=0;

//error variables
bool spriteErr=0;
bool drawErr=0;

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


    WNDCLASSEX wcex;

    wcex.cbSize = sizeof (WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)WndProc;
    wcex.cbClsExtra = 0;

    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "MyWindowClass";
    wcex.hIconSm = 0;

// Now we can go ahead and register our new window class
     if (!RegisterClassEx (&wcex))
        return 0;

    HWND hWnd = CreateWindow( 
          "MyWindowClass",        /*Class Name*/
          "Arena v1.3",          /*Window Title*/
          WS_OVERLAPPEDWINDOW,    /*Window Style       =default*/
          0,					  /*Initial X Position =0*/
          0,				      /*Initial Y Position =0*/
          800,                    /*Initial Width      =400*/
          600,                    /*Initial Hight      =300*/
          NULL,                   /*Parent window handle=NONE*/
          NULL,                   /*menu used          =NONE*/
          hInstance,
          NULL                    /*Window creation data=none(default)*/
          );
    
    /* Make the window visible on the screen */
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    //do one-time stuff here
	seedRand();
	initXP();
    dummy.icon="dummy";
	test[0]=fighter;
	test[0].level=1;
	test[4]=dummy;
	currentMapFile="map0.arm";
	readMap(currentMapFile);
	//Set up and initialize Direct3D, render first frame
    initD3D(hWnd);
	ArenaWindow shopMenuWindow(300,200,60,60,"border1.bmp",3);
	initBaseGround();
	renderFrame();
	
	//textout--/????
	//border- side=~8px, top=~30px
	//TCHAR testing[]=(blu);
	//PAINTSTRUCT ps;
	//HDC hdc;
	//extOut(hdc,8,30,lpCmdLine,20);
    //Enter main loop
    MSG msg;
	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//while (msg.message != WM_QUIT)
 //   {
 //       while (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
 //       {
 //               TranslateMessage(&msg);
 //               DispatchMessage(&msg);
 //       }
 //   //run game code here (update game, render, etc. here) 
 //       if (WM_SIZE == SIZE_MINIMIZED)
 //       {
 //               Sleep(10);
 //       }
 //       else
 //       {
 //               Sleep (5);
	//			renderFrame();
 //       }
 //   }
    cleanD3D();
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //PAINTSTRUCT ps;
	//HDC hdc;
	switch (message)                  /* handle the messages */
    {
		case WM_KEYDOWN:
		{
			//turn phases pt.1
			/*switch(turnPhase)
			{
			case 0:
				playerTurn();
				break;
			case 1:
				switch (wParam)
				{
				case 'A':
					playerAttack();
					break;
				case 'M':
					playerMove();
					break;
				case 'E':
					playerEnd();
					break;
				case VK_ESCAPE:
					renderFrame();
					break;
				default:
					break;
				}
				break;
			case 2:
				switch(wParam)
				{
				case VK_RIGHT:
					ftrtestmove ('r');
					break;
				case VK_UP:
					ftrtestmove ('u');
					break;
				case VK_LEFT:
					ftrtestmove ('l');
					break;
				case VK_DOWN:
					ftrtestmove ('d');
					break;
				case 'A':
					playerAttack();
				case VK_ESCAPE:
					renderFrame();
					break;
				default:
					break;
				}
				break;
			case 3:
				switch(wParam)
				{
				case VK_RIGHT:
					ftrtestattack ('r');
					break;
				case VK_UP:
					ftrtestattack ('u');
					break;
				case VK_LEFT:
					ftrtestattack ('l');
					break;
				case VK_DOWN:
					ftrtestattack ('d');
					break;
				case 'M':
					playerMove();
				case VK_ESCAPE:
					renderFrame();
					break;
				default:
					break;
				}
				break;
				default:
					break;
			}*/
			
			switch (wParam) //old stuff
			{
			case VK_ESCAPE:
					renderFrame();
					break;
		        //character movement
				case VK_RIGHT:
					ftrtestmove ('r');
					break;
				case VK_UP:
					ftrtestmove ('u');
					break;
				case VK_LEFT:
					ftrtestmove ('l');
				break;
				case VK_DOWN:
					ftrtestmove ('d');
				break;
				//camera movement
				case 'W':
                     theCamera.move('u');
					 renderFrame();
                break;
                case 'S':
                     theCamera.move('d');
					 renderFrame();
                break;
                case 'A':
                     theCamera.move('l');
					 renderFrame();
                break;
                case 'D':
                     theCamera.move('r');
					 renderFrame();
                break;       
				default:
				break;
			}
			break;
		}
		//case WM_PAINT:
		//	hdc = BeginPaint(hWnd, &ps);
		//	//renderFrame();
		//	EndPaint(hWnd, &ps);
		//	break;		
		case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hWnd, message, wParam, lParam);
    }

    return 0;
}
//This function initialized and prepared Direct3D for use
void initD3D(HWND hWnd)
{
    d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
        
    D3DPRESENT_PARAMETERS presParams;
    ZeroMemory(&presParams,sizeof(presParams));
    
    presParams.Windowed=TRUE;
    presParams.SwapEffect=D3DSWAPEFFECT_DISCARD;
    presParams.hDeviceWindow=hWnd;
    presParams.BackBufferFormat=D3DFMT_UNKNOWN;
    presParams.BackBufferCount=1;
    presParams.PresentationInterval=D3DPRESENT_INTERVAL_ONE;
    //Create device class using this information  /*Obtain device pointer/create Direct3D Device*/
    d3dObject->CreateDevice(D3DADAPTER_DEFAULT,
                            D3DDEVTYPE_HAL,
                            hWnd,
                            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                            &presParams,
                            &d3dDevice
                            );
	//Create font
	D3DXCreateFont(d3dDevice, 20, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"), &d3dFont);
}

void initBaseGround(void)
{
	D3DXCreateTextureFromFile(d3dDevice, "grass64x.bmp", &d3dGrassTex);
	if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "grass64x.bmp", &d3dGrassTex)) && drawErr==0)
	{
		MessageBox(NULL, "Error: Could not find texture.", "Grats. You broke it.",MB_ICONEXCLAMATION | MB_OK);
		drawErr=1;
	}
	D3DXCreateTextureFromFile(d3dDevice, "dirt64x.bmp", &d3dDirtTex);
	if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "dirt64x.bmp", &d3dDirtTex)) && drawErr==0)
	{
		MessageBox(NULL, "Error: Could not find texture 'dirt64x.bmp'.", "Grats. You broke it.",MB_ICONEXCLAMATION | MB_OK);
		drawErr=1;
	}
	D3DXCreateTextureFromFile(d3dDevice, "portal64x.bmp", &d3dPortalTex);
	if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "portal64x.bmp", &d3dPortalTex)) && drawErr==0)
	{
		MessageBox(NULL, "Error: Could not find texture 'portal64x.bmp'.", "Grats. You broke it.",MB_ICONEXCLAMATION | MB_OK);
		drawErr=1;
	}
    D3DXCreateSprite(d3dDevice, &d3dSprite);
	if (FAILED(D3DXCreateSprite(d3dDevice,&d3dSprite)) && spriteErr==0)
	{
		MessageBox(NULL, "Error: Sprite draw failed.", "SPRITE ERROR",MB_ICONEXCLAMATION | MB_OK);
		spriteErr=1;
	}
}
//This is the function used to render a single frame
void renderFrame(void)
{
    /*"clear" function*/           
    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red,grn,blu), 1.0f, 0);
    /*Begins the scene*/
    d3dDevice->BeginScene();
    //do 3D rendering on the back buffer here (?)
    createBaseGrass();
	for (char i=0;i<5;i++)
	{
		if (theCamera.inView(test[i].posx,test[i].posy)) //#new
			test[i].drawspr();
	}
	sdisplayText();
	/*displayTextA();
	displayTextB();*/
	//displayText(itos(test[0].posx));
	/*Ends the scene*/
    d3dDevice->EndScene();
    /*"Present"*/
    d3dDevice->Present(NULL, NULL, NULL, NULL);
    
}

//This function used to clean up Direct3D and COM
void cleanD3D(void)
{
    d3dDevice->Release();
    d3dObject->Release();
    d3dGrassTex->Release();
	d3dDirtTex->Release();
	d3dPortalTex->Release();
	d3dSprite->Release();
	d3dFont->Release();
	//d3dFtrTex->Release();
	delete[] lpcharname;
	delete[] cTxtStrB;
	delete[] cTxtStrC;
}

void createBaseGrass(void)
{
	//drawing a sprite
	d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprPos.x = 0.0f;
	sprPos.y = 0.0f;
	int modifiedSprPosX=(int)sprPos.x/64+theCamera.getX();
	int modifiedSprPosY=(int)sprPos.y/64+theCamera.getY();
	int tileName;
    while (sprPos.y < 512 )
    {
		int modifiedSprPosX=(int)(sprPos.x/64)+theCamera.getX();
		int modifiedSprPosY=(int)(sprPos.y/64)+theCamera.getY();

		if((char)modifiedSprPosX<mapDataWidth)
		{
			if((char)modifiedSprPosY<mapDataHeight)
			{
				tileName=pMapDatax[(modifiedSprPosY*mapDataWidth)+modifiedSprPosX];
				switch(pMapDatax[(modifiedSprPosY*mapDataWidth)+modifiedSprPosX])//mapData[y*mapwidth+x]
				{
					/*case 1:
					d3dSprite->Draw(d3dGrassTex, NULL, NULL, &sprPos, 0xFFFFFFFF);
					break;*/ //don't need because grass is default.
					case 2:
					d3dSprite->Draw(d3dDirtTex, NULL, NULL, &sprPos, 0xFFFFFFFF);
					break;
					case 3:
					d3dSprite->Draw(d3dPortalTex, NULL, NULL, &sprPos, 0xFFFFFFFF);
					break;
					default:
					d3dSprite->Draw(d3dGrassTex, NULL, NULL, &sprPos, 0xFFFFFFFF);
					break;
				}

			}
		}
		sprPos.x += 64;
		if (sprPos.x >=768)
		{
			sprPos.y += 64;
			sprPos.x = 0;
		}
	}
	d3dSprite->End();
}

void ftrtestmove (char d)
{
	if (test[0].posx==0 && test[0].posy==0) //triggers when you stay on the portal for a turn (also allows you to get off the portal)
	{
		portalturn++;
	}
	if (portalturn==2) //if has been standing on the portal for a turn
	{
		for(int i=1;i<5;i++)//for everyone EXCEPT the player
		{
			if (test[i].alive!=0)
			{test[i].hitcalc(20,20);} //if they're alive, kill them so they don't "teleport with you"
		}
		changeMap();
		portalturn=0;
		renderFrame();
		return;
	}
	collision = test[0].move(d);
	if (collision==1)
		ftrtestattack(d);
	renderFrame();
	//number of people currently hardcoded to one
	if (currentMapFile=="map1.arm")
	{
		for (int i=4;i<5;i++)
		{
			if (test[i].alive!=0)
			{
				Sleep(200);
				test[i].aiMove();
				renderFrame();
			}
		}
		Sleep(200);
		spawnMonster();
	}
	//displayText("(Arrow keys) Continue moving (A)ttack");
}

void displayTextA(void)
{
	/*string TxtStrA;
	TxtStrA=text;
	cTxtStrA = new char [text.size()+1];
	strcpy (cTxtStrA, TxtStrA.c_str());*/
	cTxtStrA=cTxtStrB;

	RECT fontRectA;
	fontRectA.left=8;
	fontRectA.right=200;
	fontRectA.top=512;
	fontRectA.bottom=fontRectA.top+16;

	d3dFont->DrawTextA(NULL, cTxtStrB, -1, &fontRectA, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);
}

void displayTextB(void)
{
	/*string TxtStrB;
	TxtStrB=text;
	cTxtStrB = new char [text.size()+1];
	strcpy (cTxtStrB, TxtStrB.c_str());*/
	cTxtStrB=cTxtStrC;

	RECT fontRectB;
	fontRectB.left=8;
	fontRectB.right=200;
	fontRectB.top=528;
	fontRectB.bottom=fontRectB.top+16;

	d3dFont->DrawTextA(NULL, cTxtStrC, -1, &fontRectB, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);
}

void displayTextC(string text)
{
	string TxtStrC;
	TxtStrC=text;
	cTxtStrC = new char [text.size()+1];
	strcpy (cTxtStrC, TxtStrC.c_str());
	
	RECT fontRectC;
	fontRectC.left=8;
	fontRectC.right=200;
	fontRectC.top=544;
	fontRectC.bottom=fontRectC.top+16;

	d3dFont->DrawTextA(NULL, cTxtStrC, -1, &fontRectC, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);
}

void displayText(string text)
{
    D3DRECT txtRct;
	txtRct.x1=1;
	txtRct.y1=512;
	txtRct.x2=700;
	txtRct.y2=590;
	
	/*"clear" function*/           
    d3dDevice->Clear(1, &txtRct, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red,grn,blu), 1.0f, 0);
    /*Begins the scene*/
    d3dDevice->BeginScene();
    //do 3D rendering on the back buffer here
	displayTextA();
	displayTextB();
	displayTextC(text);
	/*Ends the scene*/
    d3dDevice->EndScene();
    /*"Present"*/
    d3dDevice->Present(NULL, NULL, NULL, NULL);
    
}

//static versions of displaytext() - text doesn't advance a line.
void sdisplayTextA(void)
{
	RECT fontRectA;
	fontRectA.left=8;
	fontRectA.right=200;
	fontRectA.top=512;
	fontRectA.bottom=fontRectA.top+16;

	d3dFont->DrawTextA(NULL, cTxtStrA, -1, &fontRectA, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);
}

void sdisplayTextB(void)
{
	RECT fontRectB;
	fontRectB.left=8;
	fontRectB.right=200;
	fontRectB.top=528;
	fontRectB.bottom=fontRectB.top+16;

	d3dFont->DrawTextA(NULL, cTxtStrB, -1, &fontRectB, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);
}

void sdisplayTextC(void)
{
	RECT fontRectC;
	fontRectC.left=8;
	fontRectC.right=200;
	fontRectC.top=544;
	fontRectC.bottom=fontRectC.top+16;

	d3dFont->DrawTextA(NULL, cTxtStrC, -1, &fontRectC, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);
}

void sdisplayText(void)
{
    D3DRECT txtRct;
	txtRct.x1=1;
	txtRct.y1=512;
	txtRct.x2=700;
	txtRct.y2=590;
	
	/*"clear" function*/           
    d3dDevice->Clear(1, &txtRct, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red,grn,blu), 1.0f, 0);
    /*Begins the scene*/
    d3dDevice->BeginScene();
    //do 3D rendering on the back buffer here
	sdisplayTextA();
	sdisplayTextB();
	sdisplayTextC();
	/*Ends the scene*/
    d3dDevice->EndScene();
    /*"Present"*/
    d3dDevice->Present(NULL, NULL, NULL, NULL);
    
}


void playerTurn(void)
{
	turnmenu();
	turnPhase=1;
}



void turnmenu(void)
{
	displayText("Your turn. What would you like to do?");
	displayText("(A)ttack  (M)ove  (E)nd turn");
}

void playerMove(void)
{
	displayText("Move phase: (arrow keys)move  (A)ttack");
	turnPhase=2;
}

void playerAttack(void)
{
	displayText("Attack: (M)ove  (arrow keys)choose target");
	turnPhase=3;

}

void playerEnd(void)
{
	displayText("You have ended your turn.");

}
//void dummykey(void)
//{
//switch(turnPhase)
//{
//	case 1:
//		switch (wparam)
//		{
//			case a:
//				playerAttack();
//				break;
//			case m:
//				playerMove();
//				break;
//			case e:
//				playerEnd();
//				break;
//			default:
//				break;
//		}
//	case 2:
//		switch(wparam)
//		{
//			case VK_RIGHT:
//				ftrtestmove ('r');
//				break;
//			case VK_UP:
//				ftrtestmove ('u');
//				break;
//			case VK_LEFT:
//				ftrtestmove ('l');
//				break;
//			case VK_DOWN:
//				ftrtestmove ('d');
//				break;
//			case a:
//				playerAttack();
//			default:
//				break;
//		}
//	case 3:
//		switch(wparam)
//		{
//			case VK_RIGHT:
//				attack ('r');
//				break;
//			case VK_UP:
//				attack ('u');
//				break;
//			case VK_LEFT:
//				attack ('l');
//				break;
//			case VK_DOWN:
//				attack ('d');
//				break;
//			case m:
//				playerMove();
//			default:
//				break;
//		}	
//	default:
//		break;
//}
//}
//
void ftrtestattack(char d)
//steps: (0).range of weapon 1.Target 2.attack roll 3.damage roll 4.(...  . . follow through?    (:I have no clue))
//DR not implemented.
//add in cleanup on death
{
	//v=x of enemy, w= y of enemy, targ=targetID, ares=attack result
	if (oobCheck(test[turnID].posx,test[turnID].posy,d)==1)
		return;
	char v,w,targ,result;
	float ares,damageresult;
	v=test[turnID].posx;
	w=test[turnID].posy;
	if (d=='r')
		v++;
	else if (d=='l')
		v--;
	else if (d=='u')
		w--;
	else if (d=='d')
		w++;
	targ=grid[v][w]-1;//get target ID- the -1 is beacuse grid IDs start at 1 (0=blank tile), but person array starts at 0.
	ares=test[turnID].attack();
	damageresult=test[turnID].damage();
	result=test[targ].hitcalc((int)floor(ares),(int)floor(damageresult));
	if (result == 1)
		displayText("You hit the monster for "+itos((int)floor(damageresult))+" damage!");
	else if (result == 0)
		displayText("miss");
	else if (result == 2)
		{
			displayText("You hit the monster for "+itos((int)floor(damageresult))+" damage!");
			displayText("A monster dies.");
			displayText("You gained "+itos(test[turnID].addxp(test[targ].CR))+" xp!");
			if (test[turnID].levelup()!=0)
				displayText("You gained a level!");
		}
}

void spawnMonster(void)
{
	//chance to spawn monster based upon number of current monsters- at least, it will be. chance = 1/#ofmonsters+1 ?
	//so: only PC: 1/2 chance; PC+1 monster: 1/3 chance, etc.
	//if roll(1,10)>4+numberOfUnits  <- implement later
	if (numberofUnits==1 && roll(1,2)==2)
	{
		//search for empty spot in array
		for (int i=4; i<5; i++)
		{
			if (test[i].alive==0) //need to find way of making monster spawn location random- but only on free spaces. 
				//currently all spawn at (1,1).
			{
				person spawned (1,1,i+1);
				test[i]=spawned;
				//initialize the poor thing before it gets into the world.
				test[i].icon="dummy";
			}
		}
	}
}
//all code copyright(c) 2012 Michael Ebert -- all rights reserved
