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
#define TIMER_BLINK500  1     /*500ms定时器事件标志号*/
#define TIMER_BLINK200  2     /*200ms定时器事件标志号*/
#define TIMER_BLINK100  3     /*200ms定时器事件标志号*/
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
 软件名：Artist 
 制作团队：董嘉华 陈颜烨 李宇
 最后版本 ：Artist 1.5
 运行平台：windows
 软件说明：
 本软件基于Office设计风格，制作了具有良好交互
 体验的2维绘图软件，希望您享受创作的过程！
*********************************************/

/********************************************
 1.5更新日志
 修复了文本光标右移bug
 修复了储存时文本若有空格、换行时读取错误的bug
 修复了四角星不封闭bug
 增加了对象切换的功能
 优化界面
********************************************/ 

/*文本链表结构体*/ 
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

/*图形链表结构体*/ 
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
基本的绘制函数集，包括图形、固定文本的绘制
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
选择状态相关函数
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
菜单操作函数
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
菜单元素绘制 
*******/ 
void DrawFace();
void DrawSign(int n, int pd);
void DrawMenu(int n, int pd);
void DrawButton(int n, int pd);
void DrawColorPan(int n, int pd);
void DrawPenSize(int n);
/////////////////////////////////////////// 
/*******
部分特殊绘制
*******/ 
void DrawColor();
void fillRectangle(double x, double y, double w, double h);
void fillEllipticalArc(double rx, double ry, double start, double sweep);
void fillIstriangle(double x, double y, double basis, double height);

/////////////////////////////////////////// 
/*******
左侧图标栏
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
左侧下方按钮 
*******/ 
void DrawMoveBotton(bool pd, double x, double y);
void DrawScaleBotton(bool pd, double x, double y);
void DrawSpinBotton(bool pd, double x, double y);
void DrawFillBotton(bool pd, double x, double y);
/////////////////////////////////////////// 
/*******
上方菜单 
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
