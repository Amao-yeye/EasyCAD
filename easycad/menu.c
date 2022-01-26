#include"lucky.h"


void drawLabel(double x, double y, char* label)
{
	if (label && strlen(label) > 0) {
		MovePen(x, y);
		DrawTextString(label);
	}
}


void DrawFace() {
	//DrawPenSize();
	SetPointSize(14);
	SetPenSize(1);
	DefineColor("left", 0.95, 0.95, 0.96);
	DefineColor("B", 1, 0.96, 0.93);
	DefineColor("C", 0.99, 0.80, 0.67);
	//	DefineColor("D", 0.26, 0.80, 0.50);
	//	DefineColor("D", 0.32, 1, 0.62);
	DefineColor("D", 0.7, 0.93, 0.70);
	SetPenColor("A");
	fillRectangle(0, 0, 0.2, 0.5);
	fillRectangle(0, 0, 0.6, 0.2);
	fillRectangle(0, 9.4, 15, 0.6); //�ϲ˵� 
	SetPenColor("left");
	fillRectangle(0, 0.4, 1.2, 9.4);//��� ѡ�� 
	fillRectangle(0, 0, 15, 0.4);//�·� ״̬�� 
	SetPenColor("B");
	SetPenColor("Black");//////////�·�״̬���ļ�ͷ 
	SetPenColor("A");
	fillRectangle(0, 8.8, 1.2, 0.03);
	fillRectangle(0, 5.77, 1.2, 0.03);
	int i;
	for (i = 0; i < 10; i++) {
		DrawSign(i, 0);
	}
	for (i = 0; i < 8; i++) {
		DrawMenu(i, 0);
	}
	for (i = 0; i < 4; i++) {
		DrawButton(i, 0);
	}
	for (i = 0; i < 12; i++) {
		DrawColorPan(i, 0);
	}
	DrawPenSize(0);
	SetPointSize(20);
	SetPenColor("A");
	drawLabel(0.29, 9.02, "CLEAR");
	SetPenColor("A");
	fillRectangle(0, 0, 0.1, 0.5);
	fillRectangle(0, 0, 0.6, 0.1);
	SetPenColor("K");
	fillRectangle(13, 9.7, 0.6, 0.3);
}

void  DrawColorPan(int n, int pd) {
	double x = 0.0 + (n / 4) * 0.4, y = 5.2 - 0.4 * (n % 4);
	SetPenSize(1);
	if (pd) {
		SetPenColor("black");
		DrawRectangle(x + 0.2, y + 0.2, 0.33, 0.33, 0);
		if (Describe == ColorPen)
		{
			SetPointSize(12);
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);//�·� ״̬�� 
			SetPenColor("black");
			drawLabel(1.5, 0.1, "��ǰѡ����ɫ�̣�������Ϊ��ǰ��ˢ��ɫ���ɸı�ͼ�����������֡���ͼ��������ɫ");
		}
	}
	else {
		SetPenColor("white");
		DrawRectangle(x + 0.2, y + 0.2, 0.33, 0.33, 0);
	}
	SetPenColor(AllColor[n]);
	fillRectangle(x + 0.05, y + 0.05, 0.3, 0.3);
}

void DrawSign(int n, int pd) {
	if (n == -1)
		return;
	SetPenSize(1);
	SetEraseMode(FALSE);
	SetPointSize(12);
	double x = 0.0 + (n / 5) * 0.6, y = 8.2 - 0.6 * (n % 5), k = 1.1;
	if (pd) {
		SetPenColor("left");
		fillRectangle(x, y, 0.6, 0.6);
	}
	else {
		SetPenColor("white");
		fillRectangle(x, y, 0.6, 0.6);
	}
	SetPenColor("left");
	DrawRectangle(x + 0.3, y + 0.3, 0.6, 0.6, 0);
	SetPenColor("black");
	switch (n) {
	case 0: DrawMouseSign(pd, x, y); break;
	case 1: DrawLineSign(pd, x, y); break;
	case 2: DrawRectangleSign(pd, x, y); break;
	case 3: DrawEllipsesign(pd, x, y); break;
	case 4: DrawStringSign(pd, x, y); break;
	case 5: DrawSuiBiHuaSign(pd, x, y); break;
	case 6: DrawDiamondSign(pd, x, y); break;
	case 7: DrawTriangleSign(pd, x, y); break;
	case 8: DrawFourPointStarSign(pd, x, y); break;
	case 9: DrawCircularSign(pd, x, y); break;
	}
}
void DrawMenu(int n, int pd) {
	SetEraseMode(FALSE);
	SetPointSize(12);
	double x = 0 + 0.8 * n, y = 9.4;
	if (pd) {
		SetPenColor("White");
		fillRectangle(x, y, 0.8, 0.4);
		SetPenColor("A");
	}
	else {
		SetPenColor("A");
		fillRectangle(x, y, 0.8, 0.4);
		SetPenColor("White");
	}
	switch (n) {
	case 0: DrawNewBuildMenu(pd, x, y); break;
	case 1: DrawKeepMenu(pd, x, y); break;
	case 2: DrawImportMenu(pd, x, y); break;
	case 3: DrawCopyMenu(pd, x, y); break;
	case 4: DrawStickMenu(pd, x, y); break;
	case 5: DrawDeleteMenu(pd, x, y); break;
	case 6: DrawHelpMenu(pd, x, y); break;
	case 7: DrawQuitMenu(pd, x, y); break;
	}
}
void DrawButton(int n, int pd) {
	double x = 0, y = 2.4 - 0.4 * n;
	SetPenSize(1);
	if (pd) {
		SetPenColor("A");
		fillRectangle(0, y, 1.2, 0.3);
	}
	else {
		SetPenColor("A");
		fillRectangle(0.15, y, 0.86, 0.3);
	}
	SetPointSize(12);
	switch (n) {
	case 0: DrawMoveBotton(pd, x, y); break;
	case 1: DrawScaleBotton(pd, x, y); break;
	case 2: DrawSpinBotton(pd, x, y); break;
	case 3: DrawFillBotton(pd, x, y); break;
	}
}
///////////////////////////////////////////////////////////////////////
void DrawMoveBotton(bool pd, double x, double y) {
	if (pd) {
		if (Describe == MoveStyle)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ���ƶ���ť���ɶ�ѡ�е�ͼ�Ρ����ֽ���λ���ƶ�");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "�ƶ�");
}
void DrawScaleBotton(bool pd, double x, double y) {
	if (pd) {
		if (Describe == MoveStyle)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ�з�����ť����ס������ƶ���꣬�ɶ�ѡ�е�ͼ�ν��з�������");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "����");
}
void DrawSpinBotton(bool pd, double x, double y) {
	if (pd) {
		if (Describe == MoveStyle)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ����ת��ť����ס������ƶ���꣬�ɶ�ѡ�е�ͼ�ν�����ת");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "��ת");
}
void DrawFillBotton(bool pd, double x, double y) {
	if (pd) {
		if (Describe == FillType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ����䰴ť��ͬʱѡ����ɫ��ͼ�κ󣬿ɻ��Ƴ�����ѡ��ɫ����ͼ��");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "���");
}
////////////////////////////////////////////////////////////////////////
void DrawMouseSign(bool pd, double x, double y) {
	double k = 1.1;
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ���ģʽ����ѡ�в˵�����ť���Լ����Ƶ�ͼ�����֣����в�����ͼ�����ܳ��־��ο�Ϊ��ѡ��");
		}
	}
	MovePen(x + 0.3 * SignSize, y + 0.9 * SignSize);
	DrawLine(0.7071 * 0.6 * k * SignSize, -0.7071 * 0.6 * k * SignSize);
	MovePen(x + 0.3 * SignSize, y + 0.9 * SignSize);
	DrawLine(0, -0.6 * k * SignSize);
	DrawLine(0.92388 * 0.18 * k * SignSize, 0.38268 * 0.18 * k * SignSize);
	DrawLine(0.38268 * 0.2 * k * SignSize, -0.92388 * 0.2 * k * SignSize);
	DrawLine(0.92388 * 0.1 * k * SignSize, 0.38268 * 0.1 * k * SignSize);
	DrawLine(-0.38268 * 0.2 * k * SignSize, 0.92388 * 0.2 * k * SignSize);
	DrawLine(0.92388 * 0.18 * k * SignSize, 0.38268 * 0.18 * k * SignSize);
}
void DrawLineSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µ�ֱ��");
		}
	}
	MovePen(x + 0.2 * SignSize, y + 0.8 * SignSize);
	DrawLine(0.6 * SignSize, -0.6 * SignSize);

}
void DrawRectangleSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µľ���");
		}
	}
	DrawRectangle(x + 0.15 * SignSize + 0.35 * SignSize, y + 0.25 * SignSize + 0.25 * SignSize, SignSize * 0.7, SignSize * 0.5, 0);
}
void DrawEllipsesign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µ���Բ");
		}
	}
	MovePen(x + 0.9 * SignSize, y + 0.5 * SignSize);
	DrawEllipticalArc(0.4 * SignSize, 0.25 * SignSize, 0, 360);
}
void DrawStringSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ�ı�ģʽ���ڿհ״�������½�һ���ı���ʹ�ü����������ݣ��س��������");
		}
	}
	MovePen(x + 0.2 * SignSize, y + 0.15 * SignSize);
	DrawLine(0.3 * SignSize, 0.7 * SignSize);
	DrawLine(0.3 * SignSize, -0.7 * SignSize);
	MovePen(x + 0.36 * SignSize, y + 0.4 * SignSize);
	DrawLine(0.32 * SignSize, 0);
}
void DrawSuiBiHuaSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µ�������");
		}
	}
	MovePen(x + SignSize * 0.1, y + SignSize * 0.5);
	DrawLine(SignSize * 0.2, SignSize * 0.2 * 1.73);
	DrawLine(SignSize * 0.4, 0);
	DrawLine(SignSize * 0.2, -SignSize * 0.2 * 1.73);
	DrawLine(-SignSize * 0.2, -SignSize * 0.2 * 1.73);
	DrawLine(-SignSize * 0.4, 0);
	DrawLine(-SignSize * 0.2, SignSize * 0.2 * 1.73);

}
void DrawDiamondSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µ�����");
		}
	}
	MovePen(x + SignSize * 0.5, y + SignSize * 0.5);
	DrawDiamond(x + SignSize * 0.5, y + SignSize * 0.5, SignSize * 0.8, SignSize * 0.4, 0);
}
void DrawTriangleSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µ�������");
		}
	}
	DrawTriangle(x + SignSize * 0.5, y + SignSize * 0.5, SignSize * 0.6, SignSize * 0.7, 0);
}
void DrawFourPointStarSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µ��Ľ���");
		}
	}
	MovePen(x + SignSize * 0.4, y + SignSize * 0.6);
	DrawStar(x + SignSize * 0.5, y + SignSize * 0.5, SignSize * 0.8, SignSize * 0.8, 0);
}
void DrawCircularSign(bool pd, double x, double y) {
	if (pd) {
		if (Describe == PenType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰ״̬Ϊ��ͼģʽ���ڿհ״�������϶����ɻ���һ���µ�Բ");
		}
	}
	MovePen(x + SignSize * 0.8, y + SignSize * 0.5);
	DrawArc(SignSize * 0.3, 0, 360);
}
////////////////////////////////////////////////////////////////////////
void DrawNewBuildMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ���½��˵������½�CAD  (F1)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "�½�");
}
void  DrawKeepMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ�б���˵����ɱ����ѻ��Ƶ�CAD  (F2)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "����");
}
void  DrawImportMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "���ѡ�в˵����в�������ǰ����˵����ɵ��뱣��õ�CAD  (F3)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "����");
}
void  DrawCopyMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ�и��Ʋ˵���ѡ��ͼ�Ρ����ֺ󣬵���������ƣ��ɸ��Ƹ�ͼ�Ρ�����  (F4)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "����");
}
void  DrawStickMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ��ճ���˵������������ճ�����󣬵����Ҽ�������������ڴ�ճ���Ѹ��Ƶ�ͼ�Ρ�����  (F5)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "ճ��");
}
void  DrawDeleteMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "��ǰѡ��ɾ���˵��������������ɾ��ѡ�е�ͼ�Ρ�����  (F6)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "ɾ��");
}

void  DrawHelpMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "���ѡ�в˵����в�������ǰѡ�а����˵������д˳�������˵��  (F7)");
			SetPenColor("D");
			fillRectangle(2, 2, 12, 7.4);
			SetPenColor("Black");
			drawLabel(2.1, 9.1, "һ���ϲ�˵�");
			drawLabel(2.1, 8.7, "�½���(F1)      ���棺(F2)      ���룺���뱣��õ�CAD(F3)      ���ƣ������������ѡ��ͼ�Ρ�����(F4)");
			drawLabel(2.1, 8.3, "ճ�����������ճ���󣬵����Ҽ�������������ڴ�ճ���Ѹ��Ƶ�ͼ�Ρ�����(F5)  ");
			drawLabel(2.1, 7.9, "ɾ����ɾ��ѡ�е�ͼ�Ρ�����(F6)(Backspace)    ���������д˳�������˵����F7)     �˳���(F8)");
			drawLabel(2.1,7.5,"�Ҳ಻ͬ��ɫ���飺�ı䵱ǰƤ��ɫ");
			drawLabel(2.1, 6.9, "������ఴť");
			drawLabel(2.1, 6.5, "1����CLEAR��:      ��������");
			drawLabel(2.1, 6.1, "2�����ģʽ����ѡ�в˵�����ť���Լ����Ƶ�ͼ�����֣����в�����ͼ�����ܳ��־��ο�Ϊ��ѡ��");
			drawLabel(2.1, 5.7, "3����ͼ��        ����������ͼ�ΰ�ť���Ի�����Ӧͼ�Σ���ֱ�ߡ����εȣ�");
			drawLabel(2.1, 5.3, "4���������룺�ڿհ״�������½�һ���ı���ʹ�ü������룬�س��������,֧�ֹ���ƶ���ɾ��");
			drawLabel(2.1, 4.9, "5����ɫ�̣�    ��ɫ�̷�����Ϊ��ǰ��ˢ����ɫ���ɸı�ͼ�����������֡���ͼ��������ɫ ");
			drawLabel(2.1, 4.5, "6��PenSize��  ѡ��PenSize�д�ϸ��ͬ�����������ıʵĴ�С");
			drawLabel(2.1, 4.1, "7���ƶ���ť--�ɶ�ѡ�е�ͼ�Ρ����ֽ���λ���ƶ�       ");
			drawLabel(2.1, 3.7, "    ������ť--��ס������ƶ���꣬�ɶ�ѡ�е�ͼ�ν��з�������");
			drawLabel(2.1, 3.3, "    ��ת��ť--��ס������ƶ���꣬�ɶ�ѡ�е�ͼ�ν�����ת");
			drawLabel(2.1, 2.9, "    ��䰴ť--ͬʱѡ����ɫ��ͼ�κ󣬿ɻ��Ƴ�����ѡ��ɫ����ͼ��");
			drawLabel(2.1, 2.3, "�����·�״̬��:    ��ʱ������ʾ�������м�״̬");


		}
	}
	drawLabel(x + 0.1, y + 0.1, "����");
}
void  DrawQuitMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "���ѡ�в˵����в�������ǰѡ���˳��˵������˳�CAD  (F8)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "�˳�");
}
///////////////////////////////////////
void  DrawPenSize(int n) {
	double penpen = GetPenSize();
	int i;
	SetPenColor("left");
	fillRectangle(0, 2.9, 1.2, 1);
	SetPenColor("A");
	SetPointSize(18);
	drawLabel(0.05, 3.7, "PenSize");
	for (i = 1; i <= 4; i++) {
		SetPenSize(i * 2 - 1);
		MovePen(0.4 - 0.05 * (i - 1), 3.6 - 0.2 * (i - 1));
		DrawLine(0.4 + 0.1 * (i - 1), 0);
	}
	if (n > 0)
	{
		SetPenSize(n * 2 - 1);
		MovePen(0, 3.6 - 0.2 * (n - 1));
		DrawLine(1.19, 0);
	}
	SetPenSize(penpen);
}//ע��˺����е�x y�ǳ���������µ� 
void fillRectangle(double x, double y, double w, double h) {
	StartFilledRegion(1);
	DrawRectangle(x + w * 0.5, y + h * 0.5, w, h, 0);
	EndFilledRegion();
}
void fillEllipticalArc(double rx, double ry, double start, double sweep) {
	StartFilledRegion(1);
	DrawEllipticalArc(rx, ry, start, sweep);
	EndFilledRegion();
}
void fillIstriangle(double x, double y, double basis, double height) {
	StartFilledRegion(1);
	DrawTriangle(x, y, basis, height, 0);
	EndFilledRegion();
}

