// Copenaccount.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Copenaccount.h"
#include "afxdialogex.h"
#include "Logic.h"
#include "Date.h"
#include <vector>


// Copenaccount 对话框
extern int m_sysyear;
extern int m_sysmonth;
extern int m_sysday;

IMPLEMENT_DYNAMIC(Copenaccount, CDialogEx)

Copenaccount::Copenaccount(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENACCOUNT, pParent)
	, m_userpwd(_T(""))
	, m_username(_T(""))
	, m_useraddress(_T(""))
	, m_idnumber(_T(""))
	, m_timedate(_T(""))
{

}

Copenaccount::~Copenaccount()
{
}

void Copenaccount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_userpwd, m_userpwd);
	DDX_Text(pDX, IDC_username, m_username);
	DDX_Text(pDX, IDC_useraddress, m_useraddress);
	DDX_Text(pDX, IDC_idnumber, m_idnumber);
	DDX_Text(pDX, IDC_timedate, m_timedate);
}


BEGIN_MESSAGE_MAP(Copenaccount, CDialogEx)
	ON_BN_CLICKED(IDOK, &Copenaccount::OnBnClickedOk)
END_MESSAGE_MAP()


// Copenaccount 消息处理程序
BOOL Copenaccount::OnInitDialog()
{
	//初始化时间
	CString year3;
	CString month3;
	CString day3;
	year3.Format(_T("%d"), m_sysyear);
	month3.Format(_T("%d"), m_sysmonth);
	day3.Format(_T("%d"), m_sysday);
	m_timedate = year3 + "-" + month3 + "-" + day3;
	UpdateData(FALSE);
	return TRUE;
}

void Copenaccount::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击确定按钮开户
	//bool signInUser(string userName, string password, string address, string IDNumber, const Date & now, map <string, string> & result);
	Logic logic;
	Date date;
	map <string, string> result;
	std::string _username(CW2A(m_username.GetString()));
	std::string _password(CW2A(m_userpwd.GetString()));
	std::string _address(CW2A(m_useraddress.GetString()));
	std::string _idnumber(CW2A(m_idnumber.GetString()));
	date.setDate(m_sysyear, m_sysmonth, m_sysday);
	if (logic.signInUser(_username, _password, _address, _idnumber, date, result))
	{
		CString cbuildaccount;
		string buildaccount = result["account"];
		//cbuildaccount.Format(_T("%s"), buildaccount.c_str());
		//cbuildaccount = buildaccount.c_str();
		AfxMessageBox(_T("开户成功!账号为" + cbuildaccount));
	}
	CDialogEx::OnOK();
}
