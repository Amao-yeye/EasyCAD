#include "lucky.h"

void MouseEventProcess(int x, int y, int button, int event)
{
	TextString* pt = pheadText, * pnow = NULL, * pchooseT,*pokt=NULL;
	Graph* pg = pheadGraph, * pchooseG,*pokg=NULL;
	double mx, my;/*当前鼠标坐标*/
	double dx, dy;
	static isclick = FALSE, secclick = FALSE, down = FALSE;
	static double mx0 = 0, my0 = 0;
	mx = ScaleXInches(x);
	my = ScaleYInches(y);
	static int n10;
	int n1, i;
	bool ChooseDone = FALSE;
	if (!(my<9.4 && my>0.4 && mx > 1.2))//不在画板中 ，在上和左侧的图标中 
	{
		pchooseT = pheadText;   //加载当前选中的图形/文本以进行操作 
		pchooseG = pheadGraph;
		//寻找当前选中的对象 
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

		if (mx <= 1.2 && my <= 9.4 && my >= 0.4)//在左侧图表中 
		{
			if (my < 8.8 && my > 5.8)//在十个sign中， 
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
						//drawLable(1.5, 0.1, "当前画板已清空");
						clear();
					}
					break;
				}
			}
			else if (my > 4.0 && my < 5.6)//////颜色盘 
			{
				n1 = (int)(mx / 0.4) * 4 + 3 - (int)((my - 4) / 0.4);//确定是第几个颜色 
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
			else if (my < 3.7 && my>3)///选笔的大小 
			{
				if (event == BUTTON_DOWN && button == LEFT_BUTTON)
				{
					n1 = 4 - (int)((my - 3) / 0.2);
					Describe = SetSize;
					DrawPenSize(n1);
					NowSize = (n1 * 2 - 1);
				}
			}
			else if (my > 1.2 && my < 2.8)//左下方按钮（移动、旋转、放缩、填充）  
			{
				n1 = 3 - (int)((my - 1.2) / 0.4);//确定是哪一个按钮 
				if (event == BUTTON_DOWN && button == LEFT_BUTTON)
				{
					if (n1 >= 0 && n1 <= 2)// 前三个 
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
					else if (FillingClick == FALSE && n1 == 3)//填充按钮 
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
		}//左侧图标结束
		else if (mx > 13 && mx<13.8 && my>9.7 && my < 10)
		{
			if (event == BUTTON_UP && button == LEFT_BUTTON)
			{
				Background++;
				SetBackColor();
				ReDraw();
			}
		}//换肤按钮 
		else if (mx<6.4 && my>9.4 && my < 9.8)//上册菜单 
		{
			n1 = (int)(mx / 0.8);//数一数是第几个菜单 
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
		}//上册菜单结束 
	}//不在画板中 ，在上和左侧的图标中 
	else//在画板中 
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
						while (pt && !inBox(mx, my, pt->x0 - 0.1, pt->x1 + 0.1, pt->y1 - 0.1, pt->ygraph + 0.03, 0))//判定鼠标是否在某文本区域 
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
					if (!pt || !pt->ischoosed)  //选中其他对象或空白，取消之前对象的选中 
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
					while (pg)  ////判定鼠标是否在某图形区域  
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
					if (!pg || !pg->ischoosed)  ////选中其他对象或空白，取消之前对象的选中  
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
				case Texting:  //绘制文本 
					if (pheadText != NULL)
						DrawCursor(FALSE);
					TextString * p;
					p = creatText(mx, my);
					TextChoice(p, 0);
					break;
				default:creatGraph(mx, my, Doing);  //绘制图形 
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
			case Choosing:  //确认是否进行选中 
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
			case Choosing:   //进行移动/旋转/放缩的操作 
				if (down)
				{
					pg = pheadGraph;
					pt = pheadText;
					while (pt)  //对文本进行移动操作 
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
					while (pg)  //对图形进行当前选中的操作 
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
	}//在画板中 
	mx0 = mx;
	my0 = my;
	n1 = n10;
}

bool inBox(double x0, double y0, double x1, double x2, double y1, double y2, double angle)//确定在图形选定范围内 
{
	if (angle == 0)
		return (x0 >= x1 && x0 <= x2 && y0 >= y1 && y0 <= y2) ||
		(x0 >= x1 && x0 <= x2 && y0 <= y1 && y0 >= y2) ||
		(x0 <= x1 && x0 >= x2 && y0 >= y1 && y0 <= y2) ||
		(x0 <= x1 && x0 >= x2 && y0 <= y1 && y0 >= y2);
	double xa, ya, xb, yb, xc, yc, xd, yd;
	double l = fabs(x2 - x1);
	double s = fabs(y2 - y1);
	//计算旋转后图形的范围 
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

double four(double x1, double x2, double x3, double x4, int flag)  //确定四个数中的最大值或最小值 
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

void chooseGraph(Graph * q, bool flag)     //画图形选定框 
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

TextString * creatText(double mx, double my)   //创建新文本 
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
Graph* creatGraph(double mx, double my, int itstype)  //创建新图形 
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

void PlaceGraph(Graph * pg, double mx, double my, double mx0, double my0)   //画图时移动图形 
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

void clear()      //清空画板 
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

void copy()    //复制选中元素 
{
	TextString* pt = pheadText;
	Graph* pg = pheadGraph;
	while (pt)  //检查文本选中状态，进行复制 
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
	while (pg)  //检查图形选中状态，进行复制 
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

void paste(double mx, double my)  //粘贴选中元素 
{
	TextString* pt, * p1;
	Graph* pg, * p2;
	double l, s;
	switch (Copying)
	{
	case 0:
		return;
		break;
	case 1:  //粘贴文本 
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
	case 2:  //粘贴图形 
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
void NewBuild()  //清空txt文件 
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
