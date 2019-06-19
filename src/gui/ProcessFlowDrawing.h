#pragma once

#include "../stdafx.h"
#include "StreamProcessingDlg.h"

//to paint the processing flow graph
class ProcessFlowDrawing {
public:
	ProcessFlowDrawing(CStreamProcessingDlg* dlg);

	void DrawEllipse(CDC *pDC, CPoint &relative_center, int radius, CString text);
	void DrawEllipse(CDC *pDC, int x_off, int y_off, int width, int length, CString text);

	void DrawRect(CDC *pDC);
	void DrawArrow(CDC* pdc, CPoint &point1, CPoint &point2, int nFlag);
	void DrawLine(CDC *pDC, const CPoint &p1, const CPoint &p2);
	void DrawText(CDC *pDC, int x, int y, CString str);

	void paintStaticGraph(CDC *pDC);
private:
	CPen m_pen;
	CPoint m_point;
	int x;
	int y;
	CStreamProcessingDlg* dlg;
};