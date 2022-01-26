#include "lucky.h"

void MouseEventProcess(int x, int y, int button, int event)
{
	TextString* pt = pheadText, * pnow = NULL, * pchooseT,*pokt=NULL;
	Graph* pg = pheadGraph, * pchooseG,*pokg=NULL;
	double mx, my;/*��ǰ�������*/
	double dx, dy;
	static isclick = FALSE, secclick = FALSE, down = FALSE;
	static double mx0 = 0, my0 = 0;
	mx = ScaleXInches(x);
	my = ScaleYInches(y);
	static int n10;
	int n1, i;
	bool ChooseDone = FALSE;
	if (!(my<9.4 && my>0.4 && mx > 1.2))//���ڻ����� �����Ϻ�����ͼ���� 
	{
		pchooseT = pheadText;   //���ص�ǰѡ�е�ͼ��/�ı��Խ��в��� 
		pchooseG = pheadGraph;
		//Ѱ�ҵ�ǰѡ�еĶ��� 
		while (pchooseG)         
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
		if (pheadText != NULL)
		{
			DrawCursor(FALSE);
			cancelTimer(TIMER_BLINK500);
			TextChoice(pheadText, 3);
			SetEraseMode(FALSE);
		}
		if (pchooseT && Doing != Choosing)
		{
			pchooseT->ischoosed = FALSE;
			choose(pchooseT->x0 - 0.1, pchooseT->x1 + 0.1, pchooseT->ygraph + 0.03, pchooseT->y1 - 0.1, FALSE);
		}
		if (pchooseG && Doing != Choosing)
		{
			pchooseG->ischoosed = FALSE;
			chooseGraph(pchooseG, FALSE);
		}

		if (mx <= 1.2 && my <= 9.4 && my >= 0.4)//�����ͼ���� 
		{
			if (my < 8.8 && my > 5.8)//��ʮ��sign�У� 
			{
				n1 = 4 - (int)((my - 5.8) / 0.6) + 5 * (int)(mx / 0.6);
				switch (event)
				{
				case BUTTON_DOWN:
					if (button == LEFT_BUTTON)
					{
						for (i = 0; i < 10; i++)
						{
							DrawSign(i, 0);
						}
						Describe = PenType;
						DrawSign(n1, 1);
						Doing = n1;
					}
					break;
				}
			}
			else if (my > 8.8 && my < 9.4)//CLear 
			{
				switch (event)
				{
				case BUTTON_DOWN:
					if (button == LEFT_BUTTON)
					{
						//drawLable(1.5, 0.1, "��ǰ���������");
						clear();
					}
					break;
				}
			}
			else if (my > 4.0 && my < 5.6)//////��ɫ�� 
			{
				n1 = (int)(mx / 0.4) * 4 + 3 - (int)((my - 4) / 0.4);//ȷ���ǵڼ�����ɫ 
				if (event == BUTTON_DOWN && button == LEFT_BUTTON)
				{
					for (i = 0; i < 12; i++)
					{
						DrawColorPan(i, 0);
					}
					Describe = ColorPen;
					DrawColorPan(n1, 1);
					NowColor = n1;
					pg = pheadGraph;
					pt = pheadText;
					if (pchooseG)
					{
						pchooseG->color = NowColor;
						ReDraw();
					}
					if (pchooseT)
					{
						pchooseT->color = NowColor;
						ReDraw();
					}

				}
			}
			else if (my < 3.7 && my>3)///ѡ�ʵĴ�С 
			{
				if (event == BUTTON_DOWN && button == LEFT_BUTTON)
				{
					n1 = 4 - (int)((my - 3) / 0.2);
					Describe = SetSize;
					DrawPenSize(n1);
					NowSize = (n1 * 2 - 1);
				}
			}
			else if (my > 1.2 && my < 2.8)//���·���ť���ƶ�����ת����������䣩  
			{
				n1 = 3 - (int)((my - 1.2) / 0.4);//ȷ������һ����ť 
				if (event == BUTTON_DOWN && button == LEFT_BUTTON)
				{
					if (n1 >= 0 && n1 <= 2)// ǰ���� 
					{
						SetPenColor("left");
						StartFilledRegion(1);
						DrawRectangle(0.6, 2, 1.2, 1.6, 0);
						EndFilledRegion();
						for (i = 0; i < 3; i++)
						{
							DrawButton(i, 0);
						}
						if (Filling == FALSE)
						{
							DrawButton(3, 0);
						}
						else
						{
							DrawButton(3, 1);
						}
						Describe = MoveStyle;
						DrawButton(n1, 1);
						GraphDoing = n1;
					}
					else if (FillingClick == FALSE && n1 == 3)//��䰴ť 
					{
						SetPenColor("left");
						StartFilledRegion(1);
						DrawRectangle(0.6, 1.4, 1.2, 0.4, 0);
						EndFilledRegion();
						if (Filling == FALSE)
						{
							Describe = FillType;
							DrawButton(3, 1);
							Filling = TRUE;
							if (pchooseG)
							{
								pchooseG->fill = TRUE;
								ReDraw();
							}
						}
						else
						{
							Describe = 0;
							DrawButton(3, 0);
							Filling = FALSE;
						}
						FillingClick = TRUE;
					}
				}
				else  if (event == BUTTON_UP && button == LEFT_BUTTON)
				{
					FillingClick = FALSE;
				}
			}
		}//���ͼ�����
		else if (mx > 13 && mx<13.8 && my>9.7 && my < 10)
		{
			if (event == BUTTON_UP && button == LEFT_BUTTON)
			{
				Background++;
				SetBackColor();
				ReDraw();
			}
		}//������ť 
		else if (mx<6.4 && my>9.4 && my < 9.8)//�ϲ�˵� 
		{
			n1 = (int)(mx / 0.8);//��һ���ǵڼ����˵� 
			if (event == BUTTON_DOWN && button == LEFT_BUTTON)
			{
				Describe = Menu;
				DrawMenu(n1, 1);
				switch (n1)
				{
				case 0:
					NewBuild();
					break;
				case 1:
					output();
					break;
				case 2:
					input();
					break;
				case 3:
					copy();
					break;
				case 4:
					if (Pasting == FALSE && !PastClick)
					{
						Pasting = TRUE;
						PastClick = TRUE;
					}
					else if (Pasting == TRUE && !PastClick)
					{
						Describe = 0;
						Pasting = FALSE;
						PastClick = TRUE;
					}
					break;
				case 5:
					DeleteElement();
					break;
				case 7:
					exit(0);
				}
			}
			else if (event == BUTTON_UP && button == LEFT_BUTTON)
			{
				PastClick = FALSE;
				for (i = 0; i < 8; i++)
				{
					DrawMenu(i, 0);
				}
				if (Pasting)
				{
					DrawMenu(4, 1);
				}
			}
		}//�ϲ�˵����� 
	}//���ڻ����� �����Ϻ�����ͼ���� 
	else//�ڻ����� 
	{
		switch (event)
		{
		case BUTTON_DOWN:
			if (button == LEFT_BUTTON)
			{
				if (Doing != Texting)
				{
					startTimer(TIMER_BLINK100, 100);
				}
				down = TRUE;
				ChooseDone = FALSE;
				switch (Doing)
				{
				case Start:
					return;
				case Choosing:
					pt = pheadText;
					while (pt)
					{
						while (pt && !inBox(mx, my, pt->x0 - 0.1, pt->x1 + 0.1, pt->y1 - 0.1, pt->ygraph + 0.03, 0))//�ж�����Ƿ���ĳ�ı����� 
						{
							pt = pt->next;
						}
						if(pt)
							pokt = pt;
						if (!pt)
							break;
						if (pt->ischoosed)
							break;
						else pt = pt->next;
					}
					pt = pokt;
					if (!pt || !pt->ischoosed)  //ѡ�����������հף�ȡ��֮ǰ�����ѡ�� 
					{
						TextString* q = pheadText;
						while (q)
						{
							choose(q->x0 - 0.1, q->x1 + 0.1, q->ygraph + 0.03, q->y1 - 0.1, FALSE);
							q->ischoosed = FALSE;
							q->move = FALSE;
							q = q->next;
						}
					}
					if (pt)
					{
						pt->move = TRUE;
						choose(pt->x0 - 0.1, pt->x1 + 0.1, pt->ygraph + 0.03, pt->y1 - 0.1, TRUE);
						ChooseDone = TRUE;
					}
					pg = pheadGraph;
					while (pg)  ////�ж�����Ƿ���ĳͼ������  
					{
						while (pg && !inBox(mx, my, pg->x1 - 0.1, pg->x2 + 0.1, pg->y1 + 0.1, pg->y2 - 0.1, pg->angle))
						{
							pg = pg->next;
						}
						if(pg)
							pokg = pg;
						if (!pg)
							break;
						if (pg->ischoosed)
							break;
						else pg = pg->next;
					}
					pg = pokg;
					if (!pg || !pg->ischoosed)  ////ѡ�����������հף�ȡ��֮ǰ�����ѡ��  
					{
						Graph* q = pheadGraph;
						while (q)
						{
							chooseGraph(q, FALSE);
							q->ischoosed = FALSE;
							q->move = FALSE;
							q = q->next;
						}
					}
					if (pg && !ChooseDone)
					{
						pg->move = TRUE;
						chooseGraph(pg, TRUE);
					}
					break;
				case Texting:  //�����ı� 
					if (pheadText != NULL)
						DrawCursor(FALSE);
					TextString * p;
					p = creatText(mx, my);
					TextChoice(p, 0);
					break;
				default:creatGraph(mx, my, Doing);  //����ͼ�� 
				}
			}
			if (button == RIGHT_BUTTON)
			{
				if (Pasting)
				{
					paste(mx, my);
				}
			}
			break;
		case BUTTON_UP:      
			cancelTimer(TIMER_BLINK100);
			//ReDraw();
			down = FALSE;
			pt = pheadText;
			pg = pheadGraph;
			switch (Doing)
			{
			case Choosing:  //ȷ���Ƿ����ѡ�� 
				while (pt)
				{
					if (pt->move)
						pt->ischoosed = TRUE;
					pt = pt->next;
				}
				while (pg)
				{
					if (pg->move)
						pg->ischoosed = TRUE;
					pg = pg->next;
				}
				break;
			default:
				pg = pheadGraph;
				while (pg)
				{
					pg->drawing = FALSE;
					pg = pg->next;
				}
			}
			if (Doing != Texting)
			{
				ReDraw();
			}
			break;
		case MOUSEMOVE:
			switch (Doing)
			{
			case Choosing:   //�����ƶ�/��ת/�����Ĳ��� 
				if (down)
				{
					pg = pheadGraph;
					pt = pheadText;
					while (pt)  //���ı������ƶ����� 
					{
						if (pt->ischoosed)
						{
							TextChoice(pt, 2);
							choose(pt->x0 - 0.1, pt->x1 + 0.1, pt->ygraph + 0.03, pt->y1 - 0.1, FALSE);
							pt->x0 += (mx - mx0);
							pt->y0 += (my - my0);
							TextChoice(pt, 1);
							choose(pt->x0 - 0.1, pt->x1 + 0.1, pt->ygraph + 0.03, pt->y1 - 0.1, TRUE);
						}
						pt = pt->next;
					}
					while (pg)  //��ͼ�ν��е�ǰѡ�еĲ��� 
					{
						if (pg->ischoosed)
						{
							switch (GraphDoing)
							{
							case Moving:
								DrawGraph(pg, FALSE);
								chooseGraph(pg, FALSE);
								pg->x1 += (mx - mx0);
								pg->x2 += (mx - mx0);
								pg->xmid += (mx - mx0);
								pg->y1 += (my - my0);
								pg->y2 += (my - my0);
								pg->ymid += (my - my0);
								DrawGraph(pg, TRUE);
								chooseGraph(pg, TRUE);
								break;
							case Spining:
								DrawGraph(pg, FALSE);
								chooseGraph(pg, FALSE);
								pg->angle = atan((my - pg->ymid) / (mx - pg->xmid));
								DrawGraph(pg, TRUE);
								chooseGraph(pg, TRUE);
								break;
							case magnifing:
								DrawGraph(pg, FALSE);
								chooseGraph(pg, FALSE);
								pg->xmid += (mx - mx0) / 2;
								pg->ymid += (my - my0) / 2;
								pg->x2 += mx - mx0;
								pg->y1 += my - my0;
								DrawGraph(pg, TRUE);
								chooseGraph(pg, TRUE);
							}
						}
						pg = pg->next;

					}
				}
				break;
			case Hexagon:
			case Ellipse:
			case Rectangle:
			case Triangle:
			case Diamond:
			case StraightLine:
			case Star:
			case Circle:
				pg = pheadGraph;
				while (pg && down)
				{
					if (pg->drawing)
					{
						PlaceGraph(pg, mx, my, mx0, my0);
						break;
					}
					pg = pg->next;
				}
			}
		}
	}//�ڻ����� 
	mx0 = mx;
	my0 = my;
	n1 = n10;
}

bool inBox(double x0, double y0, double x1, double x2, double y1, double y2, double angle)//ȷ����ͼ��ѡ����Χ�� 
{
	if (angle == 0)
		return (x0 >= x1 && x0 <= x2 && y0 >= y1 && y0 <= y2) ||
		(x0 >= x1 && x0 <= x2 && y0 <= y1 && y0 >= y2) ||
		(x0 <= x1 && x0 >= x2 && y0 >= y1 && y0 <= y2) ||
		(x0 <= x1 && x0 >= x2 && y0 <= y1 && y0 >= y2);
	double xa, ya, xb, yb, xc, yc, xd, yd;
	double l = fabs(x2 - x1);
	double s = fabs(y2 - y1);
	//������ת��ͼ�εķ�Χ 
	xa = (x1 + x2) / 2 - 0.5 * l * cos(angle) + 0.5 * s * sin(angle);
	ya = (y1 + y2) / 2 - 0.5 * l * sin(angle) - 0.5 * s * cos(angle);
	xb = xa + l * cos(angle);
	yb = ya + l * sin(angle);
	xc = xb - s * sin(angle);
	yc = yb + s * cos(angle);
	xd = xc - l * cos(angle);
	yd = yc - l * sin(angle);
	x1 = four(xa, xb, xc, xd, 0);
	x2 = four(xa, xb, xc, xd, 1);
	y1 = four(ya, yb, yc, yd, 0);
	y2 = four(ya, yb, yc, yd, 1);
	return (x0 >= x1 && x0 <= x2 && y0 >= y1 && y0 <= y2) ||
		(x0 >= x1 && x0 <= x2 && y0 <= y1 && y0 >= y2) ||
		(x0 <= x1 && x0 >= x2 && y0 >= y1 && y0 <= y2) ||
		(x0 <= x1 && x0 >= x2 && y0 <= y1 && y0 >= y2);
}

double four(double x1, double x2, double x3, double x4, int flag)  //ȷ���ĸ����е����ֵ����Сֵ 
{
	double min = x1, max = x1;
	if (flag)
	{
		if (min > x2)
			min = x2;
		if (min > x3)
			min = x3;
		if (min > x4)
			min = x4;
		return min;
	}
	else {

		if (max < x2)
			max = x2;
		if (max < x3)
			max = x3;
		if (max < x4)
			max = x4;
		return max;
	}
}

void chooseGraph(Graph * q, bool flag)     //��ͼ��ѡ���� 
{
	if (q->angle == 0)
	{
		choose(q->x1, q->x2, q->y1, q->y2, flag);
		return;
	}
	double xa, ya, xb, yb, xc, yc, xd, yd;
	double l = q->x2 - q->x1;
	double s = q->y2 - q->y1;
	xa = (q->x1 + q->x2) / 2 - 0.5 * l * cos(q->angle) + 0.5 * s * sin(q->angle);
	ya = (q->y1 + q->y2) / 2 - 0.5 * l * sin(q->angle) - 0.5 * s * cos(q->angle);
	xb = xa + l * cos(q->angle);
	yb = ya + l * sin(q->angle);
	xc = xb - s * sin(q->angle);
	yc = yb + s * cos(q->angle);
	xd = xc - l * cos(q->angle);
	yd = yc - l * sin(q->angle);
	choose(four(xa, xb, xc, xd, 1), four(xa, xb, xc, xd, 0), four(ya, yb, yc, yd, 1), four(ya, yb, yc, yd, 0), flag);
}

TextString * creatText(double mx, double my)   //�������ı� 
{
	TextString* p, * q;
	q = pheadText;
	p = malloc(sizeof(TextString));
	if (pheadText == NULL)
	{
		pheadText = p;
		p->fore = NULL;
	}
	else
	{
		while ((q->next) != NULL)
		{
			q = q->next;
		}
		p->fore = q;
		q->next = p;
	}
	p->x0 = p->cx = p->x1 = mx;
	p->y0 = p->cy = p->y1 = my;
	p->text[0] = '\0';
	p->text[1] = '\0';
	p->next = NULL;
	p->size = NowSize * 6 - 5;
	p->color = NowColor;
	p->move = p->ischoosed = FALSE;
	p->ischoosed = FALSE;
	return p;
}
Graph* creatGraph(double mx, double my, int itstype)  //������ͼ�� 
{
	Graph* p, * q;
	q = pheadGraph;
	p = malloc(sizeof(Graph));
	if (pheadGraph == NULL)
	{
		pheadGraph = p;
		p->fore = NULL;
	}
	else
	{
		while ((q->next) != NULL)
		{
			q = q->next;
		}
		p->fore = q;
		q->next = p;
	}
	p->x1 = p->x2 = p->xmid = mx;
	p->y1 = p->y2 = p->ymid = my;
	p->type = itstype;
	p->next = NULL;
	p->ischoosed = p->move = FALSE;
	p->drawing = TRUE;
	p->angle = 0;
	p->color = NowColor;
	p->fill = Filling;
	p->size = NowSize;
}

void PlaceGraph(Graph * pg, double mx, double my, double mx0, double my0)   //��ͼʱ�ƶ�ͼ�� 
{
	SetEraseMode(TRUE);
	MovePen(pg->x2, pg->ymid);
	DrawGraph(pg, FALSE);
	if (pg->type == Circle || pg->type == Hexagon)
	{
		double k = sqrt(pow(mx - pg->xmid, 2) + pow(my - pg->ymid, 2)) / 1.5;
		pg->x2 = pg->xmid + k;
		pg->y2 = pg->ymid + k;
		pg->x1 = pg->xmid - k;
		pg->y1 = pg->ymid - k;
	}
	else
	{
		pg->x2 += (mx - mx0);
		pg->y2 += (my - my0);
		pg->x1 -= (mx - mx0);
		pg->y1 -= (my - my0);
	}
	SetEraseMode(FALSE);
	DrawGraph(pg, TRUE);
}

void clear()      //��ջ��� 
{
	TextString* pt = pheadText, * pt1;
	Graph* pg = pheadGraph, * pg1;
	while (pt)
	{
		pt1 = pt;
		pt = pt->next;
		free(pt1);
	}
	pheadText = NULL;
	while (pg)
	{
		pg1 = pg;
		pg = pg->next;
		free(pg1);
	}
	pheadGraph = NULL;
	ReDraw();

}

void copy()    //����ѡ��Ԫ�� 
{
	TextString* pt = pheadText;
	Graph* pg = pheadGraph;
	while (pt)  //����ı�ѡ��״̬�����и��� 
	{
		if (pt->ischoosed)
		{
			pTextWait = malloc(sizeof(TextString));
			*pTextWait = *pt;
			Copying = 1;
			return;
		}
		pt = pt->next;
	}
	while (pg)  //���ͼ��ѡ��״̬�����и��� 
	{
		if (pg->ischoosed)
		{
			pGraphWait = malloc(sizeof(TextString));
			*pGraphWait = *pg;
			Copying = 2;
			return;
		}
		pg = pg->next;
	}

}

void paste(double mx, double my)  //ճ��ѡ��Ԫ�� 
{
	TextString* pt, * p1;
	Graph* pg, * p2;
	double l, s;
	switch (Copying)
	{
	case 0:
		return;
		break;
	case 1:  //ճ���ı� 
		pt = malloc(sizeof(TextString));
		*pt = *pTextWait;
		p1 = pheadText;
		if (!p1)
		{
			pheadText = pt;
			pt->fore = NULL;
		}
		else
		{
			while (p1->next)
			{
				p1 = p1->next;
			}
			p1->next = pt;
			pt->fore = p1;
		}
		pt->x0 = mx;
		pt->y0 = my;
		pt->next = NULL;
		pt->move = FALSE;
		pt->ischoosed = FALSE;
		TextChoice(pt, 1);
		break;
	case 2:  //ճ��ͼ�� 
		pg = malloc(sizeof(Graph));
		*pg = *pGraphWait;
		p2 = pheadGraph;
		if (!p2)
		{
			pheadGraph = pg;
			pg->fore = NULL;
		}
		else
		{
			while (p2->next)
			{
				p2 = p2->next;
			}
			p2->next = pg;
			pg->fore = p2;
		}
		l = pg->x2 - pg->x1;
		s = pg->y2 - pg->y1;
		pg->x2 = mx - l / 2;
		pg->x1 = mx + l / 2;
		pg->y1 = my - s / 2;
		pg->y2 = my + s / 2;
		pg->xmid = mx;
		pg->ymid = my;
		pg->next = NULL;
		pg->move = FALSE;
		DrawGraph(pg, TRUE);
		pg->ischoosed = FALSE;
		break;
	}
	ReDraw();
}
void NewBuild()  //���txt�ļ� 
{
	NowColor = 11;
	Filling = FALSE;
	Pasting = FALSE;
	Copying = 0;
	NowSize = 1;
	Doing = Start;
	GraphDoing = Moving;
	clear();
	FILE* fp;
	fp = fopen("savefile.txt", "w");
	fprintf(fp, "ToText\n");
	fclose(fp);
}
