#include "../stdafx.h"

#include "MovingObjectDrawing.h"

MovingObjDrawing::MovingObjDrawing(CStreamProcessingDlg* dlg, string sample) {
	vector<EventPtr> es = tranform(sample);
	//int size = ((int)(es.size() / moving_obj_size)) * moving_obj_size;
	//get minimum and maximum moving object ids
	int min = 999999;
	int max = -1;
	for (EventPtr e : es) {
		int objId = e->getInt("objid");
		if (objId < min) min = objId;
		if (objId > max) max = objId;
	}
	int objId_range_size = max - min + 1;
	for (int i = 0; i < objId_range_size; i++) {
		trajectories.push_back(new vector<EventPtr>);
	}

	for (EventPtr e: es) {
		int objId = e->getInt("objid");
		this->trajectories[objId]->push_back(e);
	}

	this->dlg = dlg;
	this->moving_obj_size = objId_range_size;
	
}


void MovingObjDrawing::doDraw() {
	//set pen 
	m_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPaintDC dc(dlg);
	drawRectangle(&dc);
	int radius = 10;

	int step_num = this->trajectories[0]->size();
	for (int stepIndex = 0; stepIndex < step_num; stepIndex++) {
		for (int objIndex = 0; objIndex < this->trajectories.size(); objIndex++) {
			EventPtr e = trajectories[objIndex]->at(stepIndex);
			CPoint scalePoint = scale(e->getFloat("lon"), e->getFloat("lat"));

			DrawEllipse(&dc, scalePoint, radius);
			stringstream ss;
			ss << objIndex;
			drawText(&dc, scalePoint, ss.str(), radius/2, radius/2);
			

			if (stepIndex > 0) {//draw lines
				DrawEllipse(&dc, scalePoint, radius);

				EventPtr previousEvent = trajectories[objIndex]->at(stepIndex-1);
				CPoint scalePreviousPoint = scale(previousEvent->getFloat("lon"), previousEvent->getFloat("lat"));

				DrawLine(&dc, scalePreviousPoint, scalePoint);
			}
			
		}
		Sleep(900);
		
	}
}

void MovingObjDrawing::drawRectangle(CDC *pDC) {
	int x_length = max_x - min_x;
	int y_length = max_y - min_y;

	DrawLine(pDC, CPoint(0, 0), CPoint(0, y_length));
	DrawLine(pDC, CPoint(0, 0), CPoint(x_length, 0));
	DrawLine(pDC, CPoint(0, y_length), CPoint(x_length, y_length));
	DrawLine(pDC, CPoint(x_length, 0), CPoint(x_length, y_length));
}

void MovingObjDrawing::DrawLine(CDC *pDC, const CPoint &relativePoint1, const CPoint &relativePoint2) {
	CPen *oldPen = pDC->SelectObject(&m_pen);//保存DC原始画笔

	CBrush brush(RGB(199, 199, 199));//画刷
	pDC->SelectObject(&brush);//将画刷选入DC

	//pDC->SelectObject(&m_pen);        //将画笔选入DC
	pDC->MoveTo(relativePoint1.x + min_x, relativePoint1.y + min_y);         //设置DC当前点
	pDC->LineTo(relativePoint2.x + min_x, relativePoint2.y + min_y);            //绘制直线
	pDC->SelectObject(oldPen);       //回复DC原画笔
}

void MovingObjDrawing::DrawEllipse(CDC *pDC, CPoint &relative_center, int radius) {
	int x = relative_center.x - radius;
	int y = relative_center.y - radius;
	DrawEllipse(pDC, x, y, 2 * radius, 2 * radius);
}

void MovingObjDrawing::DrawEllipse(CDC *pDC, int x_off, int y_off, int width, int length) {
	CRect rect(min_x + x_off, min_y + y_off, min_x + x_off + width, min_y + y_off + length);
	CPen *oldPen = pDC->SelectObject(&m_pen);

	//rect.OffsetRect(80, 0);
	pDC->SelectObject(&m_pen);
	pDC->Ellipse(&rect);

	pDC->SelectObject(oldPen);
}

CPoint MovingObjDrawing::scale(float x, float y) {
	float lon_range_min = 127;
	float lon_range_max = 129;
	float lat_range_min = 35;
	float lat_range_max = 37;

	float scale_x = (max_x - min_x)*(x - lon_range_min) / (lon_range_max - lon_range_min) + min_x;
	float scale_y = (max_y - min_y)*(y - lat_range_min) / (lat_range_max - lat_range_min) + min_y;
	scale_x -= min_x;
	scale_y -= min_y;
	return CPoint(scale_x, scale_y);
}

//Transform sample data to EventPtrs.
vector<EventPtr> MovingObjDrawing::tranform(string str) {
	vector<EventPtr> result;
	vector<string> lines = Utils::split(str, "\n");
	for (string line : lines) {
		if (line.find(",") == -1) continue;
		vector<string> pieces = Utils::split(line, ",");
		string id_str = Utils::split(pieces[0], ":")[1];
		stringstream ss;
		int id = 0;
		ss << id_str;
		ss >> id;
		Event* e = new Event(id, Utils::getTime());
		for (int i = 2; i < pieces.size(); i++) {
			vector<string> key_value = Utils::split(pieces[i], ":");
			e->addAttr(key_value[0], key_value[1]);
		}
		result.push_back(EventPtr(e));
	}
	return result;
}

void MovingObjDrawing::drawText(CDC *pDC, CPoint& p, string str, int x_offset, int y_offset) {
	int x = p.x + min_x + x_offset;
	int y = p.y + min_y + y_offset;
	//pDC->SetBkMode(TRANSPARENT);//可以设置透明
	//CPen *oldPen = pDC->SelectObject(&m_pen);
	//pDC->SelectObject(&m_pen);
	CString s(str.c_str());
	pDC->TextOutW(x, y, s);
	//pDC->SelectObject(oldPen);
}

MovingObjDrawing::~MovingObjDrawing() {
	for (vector<EventPtr>* v : trajectories) {
		v->clear();
		delete v;
		v = nullptr;
	}
}