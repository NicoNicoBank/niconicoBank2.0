// Ccheckinfo.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Ccheckinfo.h"
#include "afxdialogex.h"


//在这个身份确认框中重要的是再次输入密码
extern CString m_useraccount;

// Ccheckinfo 对话框

IMPLEMENT_DYNAMIC(Ccheckinfo, CDialogEx)

Ccheckinfo::Ccheckinfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHECKINFO, pParent)
	, m_userpwd(_T(""))

	, m_withdraamount(0)
{

}

Ccheckinfo::~Ccheckinfo()
{
}

void Ccheckinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_account, m_userpwd);
	DDX_Text(pDX, IDC_pwd, m_userpwd);
	DDX_Text(pDX, IDC_account, m_useraccount);
	DDX_Text(pDX, IDC_withdraamount, m_withdraamount);
}


BEGIN_MESSAGE_MAP(Ccheckinfo, CDialogEx)
	ON_EN_CHANGE(IDC_account, &Ccheckinfo::OnEnChangeaccount)
	ON_BN_CLICKED(IDOK, &Ccheckinfo::OnBnClickedOk)
END_MESSAGE_MAP()


// Ccheckinfo 消息处理程序


void Ccheckinfo::OnEnChangeaccount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}
BOOL Ccheckinfo::OnInitDialog()
{
	UpdateData(FALSE);
	return TRUE;
}

void Ccheckinfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
