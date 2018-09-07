// Cwithdrainfoprint.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Cwithdrainfoprint.h"
#include "afxdialogex.h"


// Cwithdrainfoprint 对话框
extern CString m_useraccount;
IMPLEMENT_DYNAMIC(Cwithdrainfoprint, CDialogEx)

Cwithdrainfoprint::Cwithdrainfoprint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WITHDRAINFOPRINT, pParent)
	, m_username(_T(""))
	, withdramoney(0)
	, m_withdradate(_T(""))
	, m_profit(0)
	, m_principal(0)
	, m_begindate(_T(""))
{

}

Cwithdrainfoprint::~Cwithdrainfoprint()
{
}

void Cwithdrainfoprint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_username, m_username);
	DDX_Text(pDX, IDC_withdramoney, withdramoney);
	DDX_Text(pDX, IDC_withdradate, m_withdradate);
	DDX_Text(pDX, IDC_profit, m_profit);
	DDX_Text(pDX, IDC_principal, m_principal);
	DDX_Text(pDX, IDC_begindate, m_begindate);
	DDX_Text(pDX, IDC_type, m_type);
	DDX_Text(pDX, IDC_useraccount, m_useraccount);
}


BEGIN_MESSAGE_MAP(Cwithdrainfoprint, CDialogEx)
END_MESSAGE_MAP()


// Cwithdrainfoprint 消息处理程序
