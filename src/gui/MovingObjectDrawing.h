#pragma once

#include "../stdafx.h"
#include "StreamProcessingDlg.h"


class MovingObjDrawing {
private:
	int moving_obj_size ;
	int temp_count = 0;
	vector<vector<EventPtr>*> trajectories;// array of moving object[ array of events of an object[] ] 

public:
	MovingObjDrawing(CStreamProcessingDlg* dlg, string sample);

	void doDraw();

	void drawRectangle(CDC *pDC);

	void DrawLine(CDC *pDC, const CPoint &relativePoint1, const CPoint &relativePoint2);

	void DrawEllipse(CDC *pDC, CPoint &relative_center, int radius);

	void DrawEllipse(CDC *pDC, int x_off, int y_off, int width, int length);

	CPoint scale(float x, float y);

	//Transform sample data to EventPtrs.
	//vector<EventPtr> tranform(string str);

	void drawText(CDC *pDC, CPoint& p, string str, int x_offset=0, int y_offset=0);

	~MovingObjDrawing();

public:
	CPen m_pen;
	int min_x = 20;
	int max_x = 810;
	int min_y = 440;
	int max_y = 860;

	CStreamProcessingDlg* dlg;
};