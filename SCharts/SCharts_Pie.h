#pragma once

#include <string>
#include <vector>

typedef struct _tagPie
{
	int			m_nArg;		//角度大小
	COLORREF	m_color;	//颜色
	std::string m_strTip;	//提示文本

	_tagPie(){
		m_nArg = 0;
		m_color = RGB(0,0,0);
		m_strTip = "无";
	}
	_tagPie(int nArg, COLORREF color, const std::string& strTip){
		m_nArg = nArg;
		m_color = color;
		m_strTip = strTip;
	}
}PIE;
typedef std::vector<PIE>	PIES;

class SCharts_Pie : public SWindow
{
	SOUI_CLASS_NAME(SCharts_Pie, L"SChart_pie")
public:
	SCharts_Pie(void);
	~SCharts_Pie(void);

protected:
	void OnPaint(IRenderTarget *pRT);

protected:
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_PAINT_EX(OnPaint)
	SOUI_MSG_MAP_END()

private:
	PIES		m_vecPies;
};
