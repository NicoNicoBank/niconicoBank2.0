// Cdatechange.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Cdatechange.h"
#include "afxdialogex.h"

extern int m_sysyear;
extern int m_sysmonth;
extern int m_sysday;

// Cdatechange 对话框

IMPLEMENT_DYNAMIC(Cdatechange, CDialogEx)

Cdatechange::Cdatechange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATECHANGE, pParent)
	, m_yearchange(0)
	, m_monthchange(0)
	, m_daychange(0)
{

}

Cdatechange::~Cdatechange()
{
}

void Cdatechange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_yearchange, m_yearchange);
	DDX_Text(pDX, IDC_monthchange, m_monthchange);
	DDX_Text(pDX, IDC_daychange, m_daychange);
}


BEGIN_MESSAGE_MAP(Cdatechange, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cdatechange::OnBnClickedOk)
END_MESSAGE_MAP()


// Cdatechange 消息处理程序

BOOL Cdatechange::OnInitDialog()
{
	//先将时间初始化成系统时间
	m_yearchange = m_sysyear;
	m_monthchange = m_sysmonth;
	m_daychange = m_sysday;
	UpdateData(FALSE);
	return TRUE;
}
void Cdatechange::OnBnClickedOk()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	if (m_yearchange==m_sysyear && m_monthchange ==m_sysmonth && m_daychange == m_sysday)
	{
		AfxMessageBox(_T("时间没有改变"));
	}
	else
	{
		if (::MessageBox(NULL, _T("你确定要修改吗"), _T("确认页"), MB_OKCANCEL) == IDCANCEL)
		{
			return;
		}
		else {

			m_sysyear = m_yearchange;
			m_sysmonth = m_monthchange;
			m_sysday = m_daychange;
			AfxMessageBox(_T("时间修改成功！"));

			CDialogEx::OnOK();
		}
	}
	

}
