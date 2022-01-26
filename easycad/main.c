#include "lucky.h"

void MouseEventProcess(int x, int y, int button, int event);
void CharCall(char key);         //�ַ�������
void timecall(int timerID);      //��ʱ��������
void ButtonBack(int key, int event);

void Main() {
	SetWindowSize(15, 10);

	InitGraphics();
	InitColor();
	Background=0;
	SetBackColor();
	DrawFace();                 //������� 
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
	registerKeyboardEvent(ButtonBack); //�������λ��
	registerCharEvent(CharCall);       //ע���ַ��¼�
	registerTimerEvent(timecall);      //ע�ᶨʱ��
}
