#ifndef _lucky_H_
#define _lucky_H_

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <string.h>
#include <math.h>


#define Pi 3.1415926535
#define GraphStart 0
#define TextStart 1
#define Start -1
#define TIMER_BLINK500  1     /*500ms��ʱ���¼���־��*/
#define TIMER_BLINK200  2     /*200ms��ʱ���¼���־��*/
#define TIMER_BLINK100  3     /*200ms��ʱ���¼���־��*/
///////////////////////
#define Moving 0
#define magnifing 1
#define Spining 2
///////////////////////
#define Choosing 0
#define StraightLine 1
#define Rectangle 2
#define Ellipse 3
#define Texting 4
#define Hexagon 5
#define Diamond 6
#define Triangle 7
#define Star 8
#define Circle 9
///////////////////////
#define SignSize 0.6
#define Menu 1
#define ClearAll 2
#define PenType 3
#define ColorPen 4
#define SetSize 5
#define MoveStyle 6
#define FillType 7
/*********************************************
 �������Artist 
 �����Ŷӣ����λ� ������ ����
 ���汾 ��Artist 1.5
 ����ƽ̨��windows
 ���˵����
 ���������Office��Ʒ�������˾������ý���
 �����2ά��ͼ�����ϣ�������ܴ����Ĺ��̣�
*********************************************/

/********************************************
 1.5������־
 �޸����ı��������bug
 �޸��˴���ʱ�ı����пո񡢻���ʱ��ȡ�����bug
 �޸����Ľ��ǲ����bug
 �����˶����л��Ĺ���
 �Ż�����
********************************************/ 

/*�ı�����ṹ��*/ 
typedef struct t1 {    
	char text[200];
	double x0, y0, x1, y1, ygraph, cx,cy;
	int color;
	int size;
	int wordtype;
	bool ischoosed;
	struct t1* next;
	struct t1* fore;
	bool move;
}TextString;

/*ͼ������ṹ��*/ 
typedef struct t2{
	double x1,y1,x2,y2,xmid,ymid;
	int type;
	int color;
	bool fill;
	double angle;
	int size;
	struct t2* next;
	struct t2* fore;
	bool ischoosed;
	bool drawing;
	bool move;
}Graph;

int Describe;
int NowColor;
int GraphDoing;
int Doing;
int MoveText;
int Copying;
int Choice;
int NowSize;
int Background;

char* AllColor[12];

bool Filling;
bool FillingClick;
bool Pasting;
bool PastClick;

TextString* pheadText;  
Graph* pheadGraph;
TextString* pTextWait;
Graph* pGraphWait;

///////////////////////////////////////////  

/////////////////////////////////////////////////////////// 
/********
�����Ļ��ƺ�����������ͼ�Ρ��̶��ı��Ļ���
********/ 
void DrawEllipse(double xc, double yc, double l, double s, double angle);
void DrawRectangle(double xc, double yc, double l, double s, double angle);
void DrawTriangle(double xc, double yc, double l, double s, double angle);
void DrawDiamond(double xc, double yc, double l, double s, double angle);
void DrawGraph(Graph* p, bool flag);
void DrawStraightLine(double xc, double yc, double l, double s, double angle);
void DrawA(double xc, double yc, double l, double s, double angle);
void DrawStar(double xc, double yc, double l, double s, double angle);
void DrawHexagon(double xc, double yc, double l, double angle);
void DrawCircle(double  xc, double  yc, double l);
void drawLabel(double x, double y, char* label);
/////////////////////////////////////////// 
/*******
ѡ��״̬��غ���
*******/ 
void choose(double x1, double x2, double y1, double y2, bool flag);
void PlaceGraph(Graph* pg, double mx, double my, double mx0, double my0);
void chooseGraph(Graph* q, bool flag);
TextString* creatText(double mx, double my);
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2, double angle);
double four(double x1, double x2, double x3, double x4, int flag);
Graph* creatGraph(double mx, double my, int itstype);
///////////////////////////////////////////
/******* 
�˵���������
*******/ 
void InitColor();
void clear();
void DisplayClear();
void paste(double mx, double my);
void NewBuild();
void copy();
void DeleteElement();
void SetBackColor(); 
/////////////////////////////////////////// 
/*******
�˵�Ԫ�ػ��� 
*******/ 
void DrawFace();
void DrawSign(int n, int pd);
void DrawMenu(int n, int pd);
void DrawButton(int n, int pd);
void DrawColorPan(int n, int pd);
void DrawPenSize(int n);
/////////////////////////////////////////// 
/*******
�����������
*******/ 
void DrawColor();
void fillRectangle(double x, double y, double w, double h);
void fillEllipticalArc(double rx, double ry, double start, double sweep);
void fillIstriangle(double x, double y, double basis, double height);

/////////////////////////////////////////// 
/*******
���ͼ����
*******/ 
void DrawMouseSign(bool pd, double x, double y);
void DrawLineSign(bool pd, double x, double y);
void DrawRectangleSign(bool pd, double x, double y);
void DrawEllipsesign(bool pd, double x, double y);
void DrawStringSign(bool pd, double x, double y);
void DrawSuiBiHuaSign(bool pd, double x, double y);
void DrawTriangleSign(bool pd, double x, double y);
void DrawDiamondSign(bool pd, double x, double y);
void DrawFourPointStarSign(bool pd, double x, double y);
void DrawCircularSign(bool pd, double x, double y);
/////////////////////////////////////////// 
/*******
����·���ť 
*******/ 
void DrawMoveBotton(bool pd, double x, double y);
void DrawScaleBotton(bool pd, double x, double y);
void DrawSpinBotton(bool pd, double x, double y);
void DrawFillBotton(bool pd, double x, double y);
/////////////////////////////////////////// 
/*******
�Ϸ��˵� 
*******/ 
void  DrawNewBuildMenu(bool pd, double x, double y);
void  DrawKeepMenu(bool pd, double x, double y);
void  DrawCopyMenu(bool pd, double x, double y);
void  DrawStickMenu(bool pd, double x, double y);
void  DrawDeleteMenu(bool pd, double x, double y);
void  DrawImportMenu(bool pd, double x, double y);
void  DrawHelpMenu(bool pd, double x, double y);
void  DrawQuitMenu(bool pd, double x, double y);
/////////////////////////////////////////// 
# endif
