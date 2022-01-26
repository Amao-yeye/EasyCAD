#include "lucky.h"


static int point = 0, iswrite = 0;
static TextString* s;
void CharCall(char key);         //�ַ�������
void timecall(int timerID);      //��ʱ��������
void DrawCursor(bool flag);               //�����
void ButtonBack(int key, int event);
void  printtext(bool flag);
void cat(char key);
void delete();

void TextChoice(TextString* Text, int flag)
{
	s = Text;
	SetPointSize(s->size);
	if (s->color >= 0 && s->color <= 11)
		SetPenColor(AllColor[s->color]);
	s->ygraph = s->y0 + ScaleXInches(30);
	switch (flag)
	{
	case 0:
		iswrite = 1;

		s->text[0] = '\0';
		point = 0;
		MovePen(s->x0, s->y0);
		break;
	case 1:
		printtext(TRUE);
		DrawCursor(FALSE);
		break;
	case 2:
		printtext(FALSE);
		DrawCursor(FALSE);
		break;
	case 3:
		iswrite = 0;
	}
}
void CharCall(char key)
{
	if (key == '\b' || !iswrite || !Texting)
		return;
	DrawCursor(FALSE);
	printtext(FALSE);   //д�ַ�
	cat(key);
	printtext(TRUE);
	DrawCursor(TRUE);                  //�����
}
void DrawCursor(bool flag)
{
	MovePen(s->cx, s->cy);
	if (!flag)
	{
		SetEraseMode(TRUE);            //����֮ǰ���
		DrawTextString("|");
	}
	else {                     //������궨ʱ��
		SetEraseMode(FALSE);
		startTimer(TIMER_BLINK500, 500);
	}
}
void timecall(int timerID)
{

	double x, y;
	x = GetCurrentX();
	y = GetCurrentY();
	bool charge;
	switch (timerID)
	{
	case TIMER_BLINK500:
		charge = GetEraseMode();   //ʵ�ֹ����˸
		DrawTextString("|");
		charge = !charge;
		SetEraseMode(charge);
		MovePen(x, y);
		break;
	case TIMER_BLINK100:
		ReDraw();
	}
}
void ButtonBack(int key, int event)
{
	int length;
	if (s)
		length = strlen(s->text);
	Graph* pg = pheadGraph,*pchooseG;
	TextString* pt = pheadText,*pchooseT;
	switch (event)
	{
	case KEY_DOWN:
		switch (key) //�˵���ȡ��ݼ���ִ�� 
		{   
		case VK_F1:
			NewBuild();   
			break;
		case VK_F2:
			output();
			break;
		case VK_F3:
			input();
			break;
		case VK_F4:
			copy();
			break;
		case VK_F5:
			paste(6, 4);
			break;
		case VK_F8:
			exit(0);
			break;
		}
		switch (Doing)
		{
		case Texting:  //�ı�����ز��� 
			switch (key)
			{
				
			case VK_BACK:  //��ɾ�� 
				if (point < 0)
					break;
				printtext(FALSE);
				DrawCursor(FALSE);
				point--;
				delete();
				printtext(TRUE);
				DrawCursor(TRUE);
				break;
			case VK_DELETE:  //��ɾ�� 
				if (point > length)
					break;
				printtext(FALSE);
				DrawCursor(FALSE);
				delete();
				printtext(TRUE);
				DrawCursor(TRUE);
				break;
			case VK_LEFT:  //������� 
				if (point <= 0)
					break;
				DrawCursor(FALSE);
				point--;
				printtext(TRUE);
				DrawCursor(TRUE);
				printf("%d", point);
				break; 
			case VK_RIGHT:  //������� 
				printf("#%d#,#%d#", point, length);
				if (point >= length)
					break;
				DrawCursor(FALSE);
				point++;
				printtext(TRUE);
				DrawCursor(TRUE);
				printf("%d,%d", point,length);
				break;
			}
			break;
		case Choosing:  //ѡ��״̬�µĲ��� 
			pchooseT = pheadText;
			pchooseG = pheadGraph;
			while (pchooseG)  //ѡȡѡ��Ķ��� 
			{
				if (pchooseG->ischoosed)
				{
					break;
				}
				pchooseG = pchooseG->next;
			}
			while (pchooseT)
			{
				if (pchooseT->ischoosed)
				{
					break;
				}
				pchooseT = pchooseT->next;
			}
			switch (key)
			{

			case VK_BACK:  //ɾ������ 
			case VK_DELETE:
				DeleteElement();
				break;
			case VK_DOWN:  //������һ������ 
				if (pchooseT&&pchooseT->next)
				{
					pchooseT->ischoosed = FALSE;
					pchooseT->move = FALSE;
					choose(pchooseT->x0 - 0.1, pchooseT->x1 + 0.1, pchooseT->ygraph + 0.03, pchooseT->y1 - 0.1, FALSE);
					pchooseT = pchooseT->next;
					choose(pchooseT->x0 - 0.1, pchooseT->x1 + 0.1, pchooseT->ygraph + 0.03, pchooseT->y1 - 0.1, TRUE);
					pchooseT->ischoosed = TRUE;
				}
				if (pchooseG&&pchooseG->next)   
				{
					pchooseG->ischoosed = FALSE;
					pchooseG->move = FALSE;
					chooseGraph(pchooseG, FALSE);
					pchooseG = pchooseG->next;
					chooseGraph(pchooseG, TRUE);
					pchooseG->ischoosed = TRUE;
				}
				break;
			case VK_UP:  //������һ������ 
				if (pchooseT&&pchooseT->fore)
				{
					pchooseT->ischoosed = FALSE;
					pchooseT->move = FALSE;
					choose(pchooseT->x0 - 0.1, pchooseT->x1 + 0.1, pchooseT->ygraph + 0.03, pchooseT->y1 - 0.1, FALSE);
					pchooseT = pchooseT->fore;
					choose(pchooseT->x0 - 0.1, pchooseT->x1 + 0.1, pchooseT->ygraph + 0.03, pchooseT->y1 - 0.1, TRUE);
					pchooseT->ischoosed = TRUE;
				}
				if (pchooseG&&pchooseG->fore)
				{
					pchooseG->move = FALSE;
					pchooseG->ischoosed = FALSE;
					chooseGraph(pchooseG, FALSE);
					pchooseG = pchooseG->fore;
					chooseGraph(pchooseG, TRUE);
					pchooseG->ischoosed = TRUE;
				}
			}
		}
	}
}

void printtext(bool flag)  //����ı� 
{
	char cc[2] = { 0,0 };
	double MaxX = s->x0, MaxY = s->y0;
	MovePen(s->x0, s->y0);
	int i = 0, j = 1, n;
	int sum = 0;
	SetEraseMode(!flag);
	n = strlen(s->text);
	s->cx = GetCurrentX();
	s->cy = GetCurrentY();
	for (i = 0; i < n; i++)  //���ı��ָ����� 
	{
		if (s->text[i] == '\r')
		{
			if (GetCurrentX() > MaxX)
				MaxX = GetCurrentX();
			MovePen(s->x0, s->y0 - 0.25 * j);
			j++;
		}
		else
		{
			cc[0] = s->text[i];
			DrawTextString(cc);
		}
		if (i < point)
		{
			s->cx = GetCurrentX();
			s->cy = GetCurrentY();
		}
		if (GetCurrentX() > MaxX)
			MaxX = GetCurrentX();

	}
	s->x1 = MaxX;
	s->y1 = GetCurrentY();
}
void cat(char key)  //������������ַ�����Ӧλ�� 
{
	int length, i;
	if (point == 200)
		return;
	length = strlen(s->text);
	for (i = length; i > point - 1; i--)
	{
		s->text[i] = s->text[i - 1];
	}
	s->text[length + 1] = '\0';
	s->text[point] = key;
	point++;
}
void delete()  //ִ����ɾ������ɾ�� 
{
	int i, length;
	length = strlen(s->text);
	for (i = point; i < length; i++)
		s->text[i] = s->text[i + 1];
}
void DeleteElement()  //ɾ��ĳ��ͼ�λ��ı�Ԫ�� 
{
	Graph* pg;
	TextString* pt;
	pg = pheadGraph;
	pt = pheadText;
	while (pg)  //ɾ��ͼ�� 
	{
		if (pg->ischoosed)
		{
			chooseGraph(pg, FALSE);
			DrawGraph(pg, FALSE);
			if (pg == pheadGraph)
			{
				pheadGraph = pg->next;
				if (pheadGraph)
					pheadGraph->fore = NULL;
			}
			else
			{
				pg->fore->next = pg->next;
				if (pg->next)
				{
					pg->next->fore = pg->fore;
				}
			}
			free(pg);
			break;
		}
		pg = pg->next;
	}
	while (pt)  //ɾ���ı� 
	{
		if (pt->ischoosed)
		{
			s = pt;
			printtext(FALSE);
			choose(pt->x0 - 0.1, pt->x1 + 0.1, pt->ygraph + 0.03, pt->y1 - 0.1, FALSE);
			if (pt == pheadText)
			{
				pheadText = pt->next;
				if (pheadText)
					pheadText->fore = NULL;
			}
			else
			{
				pt->fore->next = pt->next;
				if (pt->next)
				{
					pt->next->fore = pt->fore;
				}
			}
			free(pt);
			break;
		}
		pt = pt->next;
	}
	ReDraw();
}
