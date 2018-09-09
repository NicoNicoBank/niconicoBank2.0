// Creportloss.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Creportloss.h"
#include "afxdialogex.h"
#include "Logic.h"
#include <vector>
#include "Date.h"


extern int m_sysyear;
extern int m_sysmonth;
extern int m_sysday;
extern CString m_staffaccount;
//extern CString m_useraccount;

// Creportloss 对话框

IMPLEMENT_DYNAMIC(Creportloss, CDialogEx)

Creportloss::Creportloss(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REPORTLOSS, pParent)
	, m_newpwd(_T(""))
	, m_cuseraccount(_T(""))
{

}

Creportloss::~Creportloss()
{
}

void Creportloss::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_newaccount, m_newpwd);
	DDX_Text(pDX, IDC_staffaccount, m_staffaccount);
	DDX_Text(pDX, IDC_timedate, m_sysdate2);
	DDX_Text(pDX, IDC_cuseraccount, m_cuseraccount);
}


BEGIN_MESSAGE_MAP(Creportloss, CDialogEx)
	ON_BN_CLICKED(IDOK, &Creportloss::OnBnClickedOk)
	ON_BN_CLICKED(IDC_checkid, &Creportloss::OnBnClickedcheckid)
END_MESSAGE_MAP()


// Creportloss 消息处理程序





BOOL Creportloss:: OnInitDialog()
{

	//初始化时间
	CString year3;
	CString month3;
	CString day3;
	year3.Format(_T("%d"), m_sysyear);
	month3.Format(_T("%d"), m_sysmonth);
	day3.Format(_T("%d"), m_sysday);
	m_sysdate2 = year3 + "-" + month3 + "-" + day3;
	UpdateData(FALSE);
	return TRUE;
}

void Creportloss::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//确定更改新密码
	//bool setAccountLost(string account, string pwd, const Date & now);
	Logic logic;
	Date date;
	date.setDate(m_sysyear, m_sysmonth, m_sysday);
	UpdateData(TRUE);
	//std::string _newpwd(CW2A(m_newpwd.GetString()));
	std::string _userpwd(CW2A(m_newpwd.GetString()));
	std::string _useraccount(CW2A(m_cuseraccount.GetString()));
	if (logic.setAccountLost(_useraccount, _userpwd, date))
	{
		AfxMessageBox(_T("挂失成功!"));
	}
	else
	{
		AfxMessageBox(_T("挂失失败请重试!"));
	}
	CDialogEx::OnOK();
}


void Creportloss::OnBnClickedcheckid()
{
	// TODO: 在此添加控件通知处理程序代码
	//查询该用户的个人信息，以便核实
	//	bool getIDNumber(string account, string & IDNumber);
	Logic logic;
	CString idnumber;
	string sidnumber;
	std::string _useraccount(CW2A(m_cuseraccount.GetString()));
	if (logic.getIDNumber(_useraccount, sidnumber))
	{
		idnumber = sidnumber.c_str();
		AfxMessageBox(_T("该用户的身份证号是：") + idnumber+_T("请核查"));
	}


}
