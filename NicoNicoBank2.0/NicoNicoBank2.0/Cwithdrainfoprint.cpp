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
	CString temp;
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_username, m_username);
	temp.Format(_T("%.2lf"), withdramoney);
	DDX_Text(pDX, IDC_withdramoney, temp);
	DDX_Text(pDX, IDC_withdradate, m_withdradate);
	temp.Format(_T("%.2lf"), m_profit);
	DDX_Text(pDX, IDC_profit, temp);
	temp.Format(_T("%.2lf"), m_principal);
	DDX_Text(pDX, IDC_principal, temp);
	DDX_Text(pDX, IDC_begindate, m_begindate);
	DDX_Text(pDX, IDC_type, m_type);
	DDX_Text(pDX, IDC_useraccount, m_useraccount);
}


BEGIN_MESSAGE_MAP(Cwithdrainfoprint, CDialogEx)
	ON_EN_CHANGE(IDC_type, &Cwithdrainfoprint::OnEnChangetype)
END_MESSAGE_MAP()


// Cwithdrainfoprint 消息处理程序


void Cwithdrainfoprint::OnEnChangetype()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
