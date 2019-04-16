#include "StdAfx.h"
#include "SCharts_Pie.h"

SCharts_Pie::SCharts_Pie(void)
{
	//制造假数据
	PIE pie1(60, RGB(255,0,0), "测试1");
	m_vecPies.push_back(pie1);

	PIE pie2(80, RGB(0,255,0), "测试2");
	m_vecPies.push_back(pie2);

	PIE pie3(100, RGB(0,0,255), "测试3");
	m_vecPies.push_back(pie3);

	PIE pie4(120, RGB(100,98,180), "测试4");
	m_vecPies.push_back(pie4);
}

SCharts_Pie::~SCharts_Pie(void)
{
}


void SCharts_Pie::OnPaint(IRenderTarget *pRT)
{
	CRect rcClient = GetClientRect();
	//pRT->DrawRectangle(&rcClient);			//可以使用pRT直接绘制

	RectF rectDraw;
	rectDraw.X = rcClient.left;
	rectDraw.Y = rcClient.top;
	rectDraw.Width = rcClient.Width();
	rectDraw.Height = rcClient.Height();

	HDC hDC = pRT->GetDC();
	Graphics graph(hDC);

	int nSweep = 0;
	graph.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	for (int i = 0; i < m_vecPies.size(); i++)
	{
		Gdiplus::Color color(GetRValue(m_vecPies[i].m_color), GetGValue(m_vecPies[i].m_color), GetBValue(m_vecPies[i].m_color));
		SolidBrush hBrush(color);
		hBrush.SetColor(color);
		int nTemp = nSweep + m_vecPies[i].m_nArg;
		graph.FillPie(&hBrush, rectDraw.X, rectDraw.Y, rectDraw.Width, rectDraw.Height, nSweep, m_vecPies[i].m_nArg);
		nSweep += m_vecPies[i].m_nArg;
	}

	int nTransBase = 0;
	PointF pt(rcClient.CenterPoint().x, rcClient.CenterPoint().y);
	graph.TranslateTransform(pt.X, pt.Y);
	for (int j = 0; j < m_vecPies.size(); j++)
	{
		SStringW sstrTip = S_CA2W(m_vecPies[j].m_strTip.c_str());

		FontFamily fontFamily(L"微软雅黑");
		Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPoint);
		SolidBrush blackBrush(Color(255, 255, 255, 255));
		
		int nTemp = m_vecPies[j].m_nArg/2;
		int nTransForm = nTransBase + nTemp;
	
		StringFormat format;
		format.SetAlignment(StringAlignmentCenter);
		graph.RotateTransform(REAL(nTransForm));
		graph.DrawString(sstrTip, -1, &font, PointF(50,-10), &format, &blackBrush);
		graph.RotateTransform(REAL(-nTransForm));

		nTransBase += m_vecPies[j].m_nArg;
	}

	pRT->ReleaseDC(hDC);
}