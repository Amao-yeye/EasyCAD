#include "lucky.h"

void MouseEventProcess(int x, int y, int button, int event);
void CharCall(char key);         //字符处理函数
void timecall(int timerID);      //定时器处理函数
void ButtonBack(int key, int event);

void Main() {
	SetWindowSize(15, 10);

	InitGraphics();
	InitColor();
	Background=0;
	SetBackColor();
	DrawFace();                 //界面绘制 
	Doing = Start;
	pTextWait = malloc(sizeof(TextString));
	pGraphWait = malloc(sizeof(Graph));
	NowColor = 11;
	Copying = 0;
	NowSize = 1;
	Describe = 0;
	Pasting = FALSE;
	Filling = FALSE;
	FillingClick = FALSE;
	pheadText = pheadGraph = NULL;
	GraphDoing = Moving;
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(ButtonBack); //设置输出位置
	registerCharEvent(CharCall);       //注册字符事件
	registerTimerEvent(timecall);      //注册定时器
}
