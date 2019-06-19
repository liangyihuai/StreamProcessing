#include "../stdafx.h"
#include "ProcessFlowDrawing.h"


CPoint& nextXPoint(CPoint p) {
	p.x = p.x + 80;
	return p;
}

CPoint& nextYPoint(CPoint p) {
	p.y = p.y + 80;
	return p;
}

void ProcessFlowDrawing::paintStaticGraph(CDC *pDC) {
	DrawRect(pDC);

	CPoint cp1(30, 30);
	CPoint cp2(100, 30);

	DrawEllipse(pDC, cp1, 15, CString("rawData"));
	DrawEllipse(pDC, cp2, 15, CString("allytarget"));
	DrawLine(pDC, cp1, cp2);

	CPoint cp3(200, 30);
	DrawEllipse(pDC, cp3, 15, CString("flyingAllyTarget"));
	DrawLine(pDC, cp2, cp3);

	CPoint cp4(100, 80);
	DrawEllipse(pDC, cp4, 15, CString("enemyTarget"));
	DrawLine(pDC, cp1, cp4);

	CPoint cp5(200, 80);
	DrawEllipse(pDC, cp5, 15, CString("nearbyEnemyTarget"));
	DrawLine(pDC, cp4, cp5);

	CPoint cp6(200, 130);
	DrawEllipse(pDC, cp6, 15, CString("flyingEnemyTarget"));
	DrawLine(pDC, cp4, cp6);

	CPoint cp7(340, 80);
	DrawEllipse(pDC, cp7, 15, CString("dangerousTarget"));
	DrawLine(pDC, cp5, cp7);
	DrawLine(pDC, cp6, cp7);

	CPoint cp8(340, 30);
	DrawEllipse(pDC, cp8, 15, CString("CEPTarget2"));
	DrawLine(pDC, cp3, cp8);
	DrawLine(pDC, cp5, cp8);
}

ProcessFlowDrawing::ProcessFlowDrawing(CStreamProcessingDlg* dlg) {
	this->dlg = dlg;

	//set pen to draw a eclipse
	m_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	
	this->x = 370;
	this->y = 260;

	m_point.x = x;
	m_point.y = y;

	CPaintDC dc(dlg); // 用于绘制的设备上下文
	CBrush brush(RGB(190, 190, 190));//画刷
	dc.SelectObject(&brush);//将画刷选入DC

	paintStaticGraph(&dc);

	/*DrawRect(&dc);
	DrawEllipse(&dc, 30, 30, 20, 20, CString("hellfaso"));

	CPoint p1 = m_point;
	CPoint p2;
	p2.x = m_point.x + 50;
	p2.y = m_point.y + 100;

	DrawArrow(&dc, p2, p1, 0);*/

	//DrawText(&dc, 10, 10, CString("hello"));
}

void ProcessFlowDrawing::DrawEllipse(CDC *pDC, 
		CPoint &relative_center, int radius, CString text) {
	int x = relative_center.x - radius;
	int y = relative_center.y - radius;
	DrawEllipse(pDC, x, y, 2*radius, 2*radius, text);
}

void ProcessFlowDrawing::DrawEllipse(CDC *pDC, int x_off, 
					int y_off, int width, int length, CString text){
	CRect rect(m_point.x + x_off, m_point.y + y_off,
		m_point.x + x_off + width, m_point.y + y_off + length);
	CPen *oldPen = pDC->SelectObject(&m_pen);

	//rect.OffsetRect(80, 0);
	pDC->SelectObject(&m_pen);
	pDC->Ellipse(&rect);

	DrawText(pDC, m_point.x + x_off-15, m_point.y + y_off+ width, text);

	pDC->SelectObject(oldPen);
}


void ProcessFlowDrawing::DrawText(CDC *pDC, int x, int y, CString str){
	pDC->SetBkMode(TRANSPARENT);//可以设置透明
	//CPen *oldPen = pDC->SelectObject(&m_pen);
	//pDC->SelectObject(&m_pen);
	pDC->TextOutW(x, y, str);
	//pDC->SelectObject(oldPen);
}


void ProcessFlowDrawing::DrawArrow(CDC* pdc, CPoint &point1, CPoint &point2, int nFlag){
	point1.x = point1.x + m_point.x;
	point1.y = point1.y + m_point.y;
	point2.x = point2.x + m_point.x;
	point2.y = point2.y + m_point.y;

	//连接起始点与终点
	pdc->MoveTo(point1);//起始点
	pdc->LineTo(point2);//终点

	//CPoint point3,point4;//好像可以不用
	double PI = 3.1415926;
	double theta = PI / 6;//箭头两侧直线与所画直线之间的夹角
	double len = 15.0;//箭头两侧直线的长度
	double theta1;//所画直线与水平方向之间的夹角
	if (nFlag == 0){//
		theta1 = atan2(double(point2.y - point1.y), double(point2.x - point1.x));
	}else{
		theta1 = -atan2(double(point2.y - point1.y), double(point2.x - point1.x));
	}
	pdc->MoveTo(point1);
	pdc->LineTo((int)(point1.x + len * cos(theta + theta1)), (int)(point1.y + len * sin(theta + theta1)));//point3
	pdc->MoveTo(point1);
	pdc->LineTo((int)(point1.x + len * cos(theta1 - theta)), (int)(point1.y + len * sin(theta1 - theta)));//point4
}


void ProcessFlowDrawing::DrawRect(CDC *pDC)
{
	CPen m_pen;

	m_pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	CRect rect(m_point.x, m_point.y, m_point.x + 445, m_point.y + 185);
	CPen *oldPen = pDC->SelectObject(&m_pen);
	//rect.OffsetRect(80, 0);//每次绘图右移80个像素
	pDC->SelectObject(&m_pen);
	pDC->Rectangle(&rect);//绘制矩形

	pDC->SelectObject(oldPen);
}


//绘制直线函数
void ProcessFlowDrawing::DrawLine(CDC *pDC, const CPoint &p1, const CPoint &p2)
{
	
	CPen *oldPen = pDC->SelectObject(&m_pen);//保存DC原始画笔
	pDC->SelectObject(&m_pen);        //将画笔选入DC
	pDC->MoveTo(p1.x + x, p1.y + y);         //设置DC当前点
	pDC->LineTo(p2.x + x, p2.y + y);            //绘制直线
	pDC->SelectObject(oldPen);       //回复DC原画笔
}