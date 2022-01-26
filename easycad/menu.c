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
	fillRectangle(0, 9.4, 15, 0.6); //上菜单 
	SetPenColor("left");
	fillRectangle(0, 0.4, 1.2, 9.4);//左侧 选项 
	fillRectangle(0, 0, 15, 0.4);//下方 状态栏 
	SetPenColor("B");
	SetPenColor("Black");//////////下方状态栏的箭头 
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
			fillRectangle(1.2, 0, 13.8, 0.4);//下方 状态栏 
			SetPenColor("black");
			drawLabel(1.5, 0.1, "当前选中颜色盘，方框内为当前笔刷颜色，可改变图形线条、文字、和图形填充的颜色");
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
			drawLabel(1.4, 0.1, "当前选中移动按钮，可对选中的图形、文字进行位置移动");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "移动");
}
void DrawScaleBotton(bool pd, double x, double y) {
	if (pd) {
		if (Describe == MoveStyle)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "当前选中放缩按钮，按住左键，移动鼠标，可对选中的图形进行放缩操作");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "放缩");
}
void DrawSpinBotton(bool pd, double x, double y) {
	if (pd) {
		if (Describe == MoveStyle)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "当前选中旋转按钮，按住左键，移动鼠标，可对选中的图形进行旋转");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "旋转");
}
void DrawFillBotton(bool pd, double x, double y) {
	if (pd) {
		if (Describe == FillType)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "当前选中填充按钮，同时选择颜色、图形后，可绘制出被已选颜色填充的图形");
		}
	}
	SetPenColor("white");
	drawLabel(x + 0.4, y + 0.1, "填充");
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
			drawLabel(1.4, 0.1, "当前状态为鼠标模式，可选中菜单、按钮、以及绘制的图形文字，进行操作，图形四周出现矩形框为已选择");
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
			drawLabel(1.4, 0.1, "当前状态为绘图模式，在空白处点击并拖动即可绘制一条新的直线");
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
			drawLabel(1.4, 0.1, "当前状态为绘图模式，在空白处点击并拖动即可绘制一个新的矩形");
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
			drawLabel(1.4, 0.1, "当前状态为绘图模式，在空白处点击并拖动即可绘制一个新的椭圆");
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
			drawLabel(1.4, 0.1, "当前状态为文本模式，在空白处点击可新建一个文本，使用键盘输入内容，回车输入结束");
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
			drawLabel(1.4, 0.1, "当前状态为绘图模式，在空白处点击并拖动即可绘制一个新的六边形");
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
			drawLabel(1.4, 0.1, "当前状态为绘图模式，在空白处点击并拖动即可绘制一个新的菱形");
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
			drawLabel(1.4, 0.1, "当前状态为绘图模式，在空白处点击并拖动即可绘制一个新的三角形");
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
			drawLabel(1.4, 0.1, "当前状态为绘图模式，在空白处点击并拖动即可绘制一个新的四角星");
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
			drawLabel(1.4, 0.1, "左当前状态为绘图模式，在空白处点击并拖动即可绘制一个新的圆");
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
			drawLabel(1.4, 0.1, "当前选中新建菜单，可新建CAD  (F1)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "新建");
}
void  DrawKeepMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "当前选中保存菜单，可保存已绘制的CAD  (F2)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "保存");
}
void  DrawImportMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "左键选中菜单进行操作，当前导入菜单，可导入保存好的CAD  (F3)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "导入");
}
void  DrawCopyMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "当前选中复制菜单，选中图形、文字后，单击左键复制，可复制该图形、文字  (F4)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "复制");
}
void  DrawStickMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "当前选中粘贴菜单，左键单击“粘贴”后，单击右键，可在鼠标所在处粘贴已复制的图形、文字  (F5)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "粘贴");
}
void  DrawDeleteMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "当前选中删除菜单，单击左键，可删除选中的图形、文字  (F6)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "删除");
}

void  DrawHelpMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "左键选中菜单进行操作，当前选中帮助菜单，内有此程序的相关说明  (F7)");
			SetPenColor("D");
			fillRectangle(2, 2, 12, 7.4);
			SetPenColor("Black");
			drawLabel(2.1, 9.1, "一、上侧菜单");
			drawLabel(2.1, 8.7, "新建：(F1)      保存：(F2)      导入：导入保存好的CAD(F3)      复制：单击左键复制选中图形、文字(F4)");
			drawLabel(2.1, 8.3, "粘贴：左键单击粘贴后，单击右键，可在鼠标所在处粘贴已复制的图形、文字(F5)  ");
			drawLabel(2.1, 7.9, "删除：删除选中的图形、文字(F6)(Backspace)    帮助：内有此程序的相关说明（F7)     退出：(F8)");
			drawLabel(2.1,7.5,"右侧不同颜色方块：改变当前皮肤色");
			drawLabel(2.1, 6.9, "二、左侧按钮");
			drawLabel(2.1, 6.5, "1、“CLEAR”:      可以清屏");
			drawLabel(2.1, 6.1, "2、鼠标模式：可选中菜单、按钮、以及绘制的图形文字，进行操作，图形四周出现矩形框为已选择");
			drawLabel(2.1, 5.7, "3、绘图：        点击左侧其他图形按钮可以绘制相应图形（如直线、矩形等）");
			drawLabel(2.1, 5.3, "4、文字输入：在空白处点击可新建一个文本，使用键盘输入，回车输入结束,支持光标移动、删除");
			drawLabel(2.1, 4.9, "5、颜色盘：    颜色盘方框内为当前笔刷的颜色，可改变图形线条、文字、和图形填充的颜色 ");
			drawLabel(2.1, 4.5, "6、PenSize：  选中PenSize中粗细不同的线条，更改笔的大小");
			drawLabel(2.1, 4.1, "7、移动按钮--可对选中的图形、文字进行位置移动       ");
			drawLabel(2.1, 3.7, "    放缩按钮--按住左键，移动鼠标，可对选中的图形进行放缩操作");
			drawLabel(2.1, 3.3, "    旋转按钮--按住左键，移动鼠标，可对选中的图形进行旋转");
			drawLabel(2.1, 2.9, "    填充按钮--同时选择颜色、图形后，可绘制出被已选颜色填充的图形");
			drawLabel(2.1, 2.3, "三、下方状态栏:    即时更新显示操作的中间状态");


		}
	}
	drawLabel(x + 0.1, y + 0.1, "帮助");
}
void  DrawQuitMenu(bool pd, double x, double y) {
	if (pd) {
		if (Describe == Menu)
		{
			SetPenColor("left");
			fillRectangle(1.2, 0, 13.8, 0.4);
			SetPenColor("black");
			drawLabel(1.4, 0.1, "左键选中菜单进行操作，当前选中退出菜单，可退出CAD  (F8)");
		}
	}
	drawLabel(x + 0.1, y + 0.1, "退出");
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
}//注意此函数中的x y是长方体的左下点 
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

