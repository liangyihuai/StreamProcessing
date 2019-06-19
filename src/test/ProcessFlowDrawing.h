#pragma once

namespace gui {
	class ProcessFlowDrawing {
	public:

		void DrawEllipse(CDC *pDC)
		{
			CRect rect(m_point.x, m_point.y, m_point.x + 20, m_point.y + 20);
			CPen *oldPen = pDC->SelectObject(&m_pen);

			//rect.OffsetRect(80, 0);
			pDC->SelectObject(&m_pen);
			pDC->Ellipse(&rect);

			pDC->SelectObject(oldPen);
		}


		void DrawRect(CDC *pDC)
		{
			CPen m_pen;

			m_pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

			CRect rect(m_point.x, m_point.y, m_point.x + 445, m_point.y + 185);
			CPen *oldPen = pDC->SelectObject(&m_pen);
			//rect.OffsetRect(80, 0);//Ã¿´Î»æÍ¼ÓÒÒÆ80¸öÏñËØ
			pDC->SelectObject(&m_pen);
			pDC->Rectangle(&rect);//»æÖÆ¾ØÐÎ

			pDC->SelectObject(oldPen);
		}
	};

}