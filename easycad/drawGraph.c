#include "lucky.h"

void DrawGraph(Graph* p, bool flag)   //图形绘制
{
	SetEraseMode(!flag);
	SetPenSize(p->size);
	SetPenColor(AllColor[p->color]);
	if (p->fill)
		StartFilledRegion(1);
	switch (p->type)
	{
	case Ellipse:
		DrawEllipse(p->xmid, p->ymid, p->x2 - p->x1, p->y2 - p->y1, p->angle);
		break;
	case Rectangle:
		DrawRectangle(p->xmid, p->ymid, p->x2 - p->x1, p->y2 - p->y1, p->angle);
		break;
	case Triangle:
		DrawTriangle(p->xmid, p->ymid, p->x2 - p->x1, p->y2 - p->y1, p->angle);
		break;
	case Diamond:
		DrawDiamond(p->xmid, p->ymid, p->x2 - p->x1, p->y2 - p->y1, p->angle);
		break;
	case StraightLine:
		DrawStraightLine(p->xmid, p->ymid, p->x2 - p->x1, p->y2 - p->y1, p->angle);
		break;
	case Star:
		DrawStar(p->xmid, p->ymid, p->x2 - p->x1, p->y2 - p->y1, p->angle);
		break;
	case Circle:
		DrawCircle(p->xmid, p->ymid, p->x2 - p->x1);
		break;
	case Hexagon:
		DrawHexagon(p->xmid, p->ymid, p->x2 - p->x1, p->angle);
	}
	if (p->fill)
		EndFilledRegion();
}

void InitColor()   // 设计颜色 
{
	DefineColor("1", 1, 0.92, 0.8);
	DefineColor("2", 1, 0.38, 0);
	DefineColor("3", 0, 1, 1);
	DefineColor("4", 0.19, 0.80, 0.19);
	DefineColor("5", 0, 1, 0.49);
	DefineColor("6", 0.62, 0.12, 0.94);
	DefineColor("7", 0.85, 0.62, 0.82);
	DefineColor("8", 0.11, 0.56, 1);
	DefineColor("9", 1, 0.18, 0.18);
	DefineColor("10", 1, 0.41, 0.41);
	DefineColor("11", 0.50, 0.54, 0.52);
	DefineColor("12", 0, 0, 0);
	AllColor[0] = "1";
	AllColor[1] = "2";
	AllColor[2] = "3";
	AllColor[3] = "4";
	AllColor[4] = "5";
	AllColor[5] = "6";
	AllColor[6] = "7";
	AllColor[7] = "8";
	AllColor[8] = "9";
	AllColor[9] = "10";
	AllColor[10] = "11";
	AllColor[11] = "12";
}

void choose(double x1, double x2, double y1, double y2, bool flag)   //绘制选择框 
{
	SetPenSize(1);
	SetPenColor("gray");
	SetEraseMode(!flag);
	DrawRectangle((x1 + x2) / 2, (y1 + y2) / 2, fabs(x2 - x1) + 0.4, fabs(y1 - y2) + 0.4, 0);
}

void DrawEllipse(double xc, double yc, double l, double s, double angle)  //绘制椭圆 
{
	l /= 2;
	s /= 2;
	if (angle == 0)
	{
		MovePen(xc + l, yc);
		DrawEllipticalArc(l, s, 0, 360);
		return;
	}
	double t;
	double x0, y0, x, y;
	x0 = xc + l * cos(angle);
	y0 = yc + l * sin(angle);
	MovePen(x0, y0);
	for (t = 0; t <= 2 * 3.2; t += 0.01)
	{
		x = xc + l * cos(t) * cos(angle) - s * sin(t) * sin(angle);
		y = yc + l * cos(t) * sin(angle) + s * sin(t) * cos(angle);
		DrawLine(x - x0, y - y0);
		x0 = x; y0 = y;
	}
}

void DrawRectangle(double xc, double yc, double l, double s, double angle)  //绘制矩形 
{

	if (angle == 0)
	{
		MovePen(xc - 0.5 * l, yc - 0.5 * s);
		DrawLine(l, 0);
		DrawLine(0, s);
		DrawLine(-l, 0);
		DrawLine(0, -s);
		return;
	}
	MovePen(xc - 0.5 * l * cos(angle) + 0.5 * s * sin(angle)
		, yc - 0.5 * l * sin(angle) - 0.5 * s * cos(angle));
	DrawLine(l * cos(angle), l * sin(angle));
	DrawLine(-s * sin(angle), s * cos(angle));
	DrawLine(-l * cos(angle), -l * sin(angle));
	DrawLine(s * sin(angle), -s * cos(angle));
}

void DrawTriangle(double xc, double yc, double l, double s, double angle)  //绘制三角形 
{
	if (angle == 0)
	{
		MovePen(xc - 0.5 * l, yc - 0.5 * s);
		DrawLine(l, 0);
		DrawLine(-l / 2, s);
		DrawLine(-l / 2, -s);
		return;
	}
	double waist = sqrt((l * l / 4 + s * s));
	MovePen(xc - 0.5 * l * cos(angle) + 0.5 * s * sin(angle)
		, yc - 0.5 * l * sin(angle) - 0.5 * s * cos(angle));
	DrawLine(l * cos(angle), l * sin(angle));
	angle += (Pi - atan(2 * s / l));
	DrawLine(waist * cos(angle), waist * sin(angle));
	angle += (Pi - 2 * atan(l / 2 / s));
	DrawLine(waist * cos(angle), waist * sin(angle));
}

void DrawDiamond(double xc, double yc, double l, double s, double angle)  //绘制菱形 
{
	if (angle == 0)
	{
		MovePen(xc - l / 2, yc);
		DrawLine(l / 2, -s / 2);
		DrawLine(l / 2, s / 2);
		DrawLine(-l / 2, s / 2);
		DrawLine(-l / 2, -s / 2);
		return;
	}
	double waist = sqrt(l * l + s * s) / 2, dangle = atan(s / l);

	MovePen(xc - 0.5 * l * cos(angle), yc - 0.5 * l * sin(angle));
	angle -= dangle;
	DrawLine(waist * cos(angle), waist * sin(angle));
	angle += 2 * dangle;
	DrawLine(waist * cos(angle), waist * sin(angle));
	angle += Pi - 2 * dangle;
	DrawLine(waist * cos(angle), waist * sin(angle));
	angle += 2 * dangle;
	DrawLine(waist * cos(angle), waist * sin(angle));
}

void DrawStraightLine(double xc, double yc, double l, double s, double angle)  //绘制直线 
{
	if (angle == 0)
	{
		MovePen(xc - l / 2, yc - s / 2);
		DrawLine(l, s);
	}
	else
	{
		MovePen(xc - sqrt(l * l + s * s) * cos(angle) / 2, yc - sqrt(l * l + s * s) * sin(angle) / 2);
		DrawLine(sqrt(l * l + s * s) * cos(angle), sqrt(l * l + s * s) * sin(angle));
	}
}

void DrawHexagon(double xc, double yc, double l, double angle)  //绘制六边形 
{
	if (angle == 0)
	{
		MovePen(xc - l / 2, yc);
		DrawLine(l / 4, 1.732 * l / 4);
		DrawLine(l / 2, 0);
		DrawLine(l / 4, -1.732 * l / 4);
		DrawLine(-l / 4, -1.732 * l / 4);
		DrawLine(-l / 2, 0);
		DrawLine(-l / 4, 1.732 * l / 4);
		return;
	}
	double waist = l / 2;
	MovePen(xc - 0.5 * l * cos(angle), yc - 0.5 * l * sin(angle));
	DrawLine(waist * cos(angle + Pi / 3), waist * sin(angle + Pi / 3));
	DrawLine(waist * cos(angle), waist * sin(angle));
	DrawLine(waist * cos(angle - Pi / 3), waist * sin(angle - Pi / 3));
	DrawLine(-waist * cos(angle + Pi / 3), -waist * sin(angle + Pi / 3));
	DrawLine(waist * cos(angle + Pi), waist * sin(angle + Pi));
	DrawLine(waist * cos(angle + Pi * 2 / 3), waist * sin(angle + Pi * 2 / 3));

}
void DrawStar(double xc, double yc, double l, double s, double angle)  //绘制四角星 
{
	if (angle == 0)
	{
		MovePen(xc - l / 2, yc);
		DrawLine(3 * l / 8, s / 8);
		DrawLine(l / 8, 3 * s / 8);
		DrawLine(l / 8, -3 * s / 8);
		DrawLine(3 * l / 8, -s / 8);
		DrawLine(-3 * l / 8, -s / 8);
		DrawLine(-l / 8, -3 * s / 8);
		DrawLine(-l / 8, 3 * s / 8);
		DrawLine(-3 * l / 8, s / 8);
	}
	else 
	{ 
		s = fabs(s);
		double waist1 = sqrt(l * l / 64 + s * s * 9 / 64);
		double waist2 = sqrt(s * s / 64 + l * l * 9 / 64);
		double dangle1 = atan(s  / (3 * l) );
		double dangle2 = atan(l / (3 * s) );
		double x0 = xc - l / 2 * cos(angle);
		double y0 = yc - l / 2 * sin(angle);
		double xnew, ynew;
		MovePen(xc - l / 2 * cos(angle), yc - l / 2 * sin(angle)); 
		angle += dangle1;
		DrawLine(waist2 * cos(angle), waist2 * sin(angle));
		angle += Pi/2 - dangle1 - dangle2;
		DrawLine(waist1 * cos(angle), waist1 * sin(angle));
		angle -= Pi - 2 * dangle2;
		DrawLine(waist1 * cos(angle), waist1 * sin(angle));
		angle += Pi / 2 - dangle1 - dangle2;;
		DrawLine(waist2 * cos(angle), waist1 * sin(angle));
		angle -= Pi - 2 * dangle1;
		DrawLine(waist2 * cos(angle), waist1 * sin(angle));
		angle += Pi / 2 - dangle1 - dangle2;
		DrawLine(waist1 * cos(angle), waist1 * sin(angle));
		angle -= Pi - 2 * dangle2;
		DrawLine(waist1 * cos(angle), waist1 * sin(angle));
		angle += Pi / 2 - dangle1 - dangle2;
		xnew = GetCurrentX();
		ynew = GetCurrentY();
		DrawLine(x0-xnew,y0-ynew);
	}
}

void DrawCircle(double xc, double yc, double l)  //绘制圆形 
{
	l /= 2;
	MovePen(xc + l, yc);
	DrawArc(l, 0, 360);
}
void ReDraw()  //重新绘制界面及元素 
{
	Graph* pg = pheadGraph;
	TextString* pt = pheadText;
	SetEraseMode(FALSE);
	SetPenColor("white");
	StartFilledRegion(1);
	DrawRectangle(7.5, 5, 15, 10, 0);
	EndFilledRegion();
	while (pg)
	{
		DrawGraph(pg, TRUE);
		if (pg->ischoosed)
		{
			chooseGraph(pg, TRUE);
		}
		pg = pg->next;
	}
	while (pt)
	{
		TextChoice(pt, 1);
		if (pt->ischoosed)
		{
			choose(pt->x0 - 0.1, pt->x1 + 0.1, pt->ygraph + 0.03, pt->y1 - 0.1, TRUE);
		}
		pt = pt->next;
	}
	SetEraseMode(FALSE);
	DrawFace();
	DrawSign(Doing, 1);
	DrawColorPan(NowColor, 1);
	DrawPenSize((NowSize + 1) / 2);
	DrawButton(GraphDoing,1);
	if (Filling)
	{
		DrawButton(3, 1);
	}
	if (Pasting)
	{
		DrawMenu(4, 1);
	}
}

void SetBackColor()  //设置皮肤色 
{
	Background %= 5;
	switch (Background)
	{
	case 0:
		DefineColor("A", 0.180, 0.545, 0.341);
		DefineColor("K", 0.0784, 0.2666, 0.4157);
		break;
	case 1:
		DefineColor("A", 0.0784, 0.2666, 0.4157);
		DefineColor("K", 0.698, 0.784, 0.733);
		break;
	case 2:
		DefineColor("A", 0.698, 0.784, 0.733);
		DefineColor("K", 0.898, 0.514, 0.031);
		break;
	case 3:
		DefineColor("A", 0.898, 0.514, 0.031);
		DefineColor("K", 0.0557, 0.792, 0.678);
		break;
	case 4:
		DefineColor("A", 0.0557, 0.792, 0.678);
		DefineColor("K", 0.180, 0.545, 0.341);
		break;
	}
}


