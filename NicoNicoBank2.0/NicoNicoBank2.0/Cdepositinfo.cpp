// Cdepositinfo.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Cdepositinfo.h"
#include "afxdialogex.h"

extern int m_sysyear;
extern int m_sysmonth;
extern int m_sysday;

// Cdepositinfo 对话框

IMPLEMENT_DYNAMIC(Cdepositinfo, CDialogEx)

Cdepositinfo::Cdepositinfo(CWnd* pParent /*=nullptr*/)
	//: CDialogEx(IDD_DIALOG2, pParent)
	, m_monthchange(0)
	, m_yearchange(0)

{

}

Cdepositinfo::~Cdepositinfo()
{
}

void Cdepositinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_yearchange, m_yearchange);
	DDX_Text(pDX, IDC_monthchange, m_monthchange);
	DDX_Text(pDX, IDC_yearchange, m_yearchange);
	DDX_Text(pDX, IDC_daychange, m_daychange);
}


BEGIN_MESSAGE_MAP(Cdepositinfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cdepositinfo::OnBnClickedOk)
END_MESSAGE_MAP()


// Cdepositinfo 消息处理程序


void Cdepositinfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
