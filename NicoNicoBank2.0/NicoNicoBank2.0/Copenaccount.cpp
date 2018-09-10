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
	UpdateData(TRUE);
	std::string _username(CW2A(m_username.GetString()));
	std::string _password(CW2A(m_userpwd.GetString()));
	std::string _address(CW2A(m_useraddress.GetString()));
	std::string _idnumber(CW2A(m_idnumber.GetString()));
	date.setDate(m_sysyear, m_sysmonth, m_sysday);
	if (m_username == "" || m_userpwd == "" || m_useraddress == "" || m_idnumber == "")
	{
		AfxMessageBox(_T("不能留有空白项!"));
	}
	else if (!logic.checkText(_username) || !logic.checkPwd(_password) || !logic.checkText(_address) || !logic.checkText(_idnumber)) {
		AfxMessageBox(_T("请不要输入特殊字符"));
	}
	else if (int resultOfJudgeIdNumber = logic.judgeIdNumber(_idnumber) != 1) {
		if (resultOfJudgeIdNumber == 0) {
			AfxMessageBox(_T("身份证长度错误"));
		}
		else {
			AfxMessageBox(_T("身份证格式有误"));
		}
	}
	else if (logic.judgePasswordStrength(_password) == 1) {
		AfxMessageBox(_T("密码太弱，请混合数字和英文大小写字符"));
	}
	else {
		if (logic.signInUser(_username, _password, _address, _idnumber, date, result))
		{
			CString cbuildaccount;
			string buildaccount = result["account"];
			//cbuildaccount.Format(_T("%s"), buildaccount.c_str());
			cbuildaccount = buildaccount.c_str();
			AfxMessageBox(_T("开户成功!账号为" + cbuildaccount));
			CDialogEx::OnOK();
		}
		else {
			AfxMessageBox(_T("开户失败!"));
		}
		
	}
	
}
