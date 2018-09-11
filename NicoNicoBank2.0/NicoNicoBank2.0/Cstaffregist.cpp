// Cstaffregist.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Cstaffregist.h"
#include "afxdialogex.h"
#include "Logic.h"


// Cstaffregist 对话框
extern CString m_staffaccount;
IMPLEMENT_DYNAMIC(Cstaffregist, CDialogEx)

Cstaffregist::Cstaffregist(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STAFFREGIST, pParent)
	, m_name(_T(""))
	, m_account(_T(""))
	, m_pwd(_T(""))
{

}

Cstaffregist::~Cstaffregist()
{
}

void Cstaffregist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_name, m_name);
	DDX_Text(pDX, IDC_account, m_account);
	DDX_Text(pDX, IDC_pwd, m_pwd);
}


BEGIN_MESSAGE_MAP(Cstaffregist, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cstaffregist::OnBnClickedOk)
END_MESSAGE_MAP()


// Cstaffregist 消息处理程序


//点击进行注册储蓄员前的相关验证
void Cstaffregist::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//bool signInStaff(string account, string pwd, string name);
	UpdateData(TRUE);
	Logic logic;
	std::string _name(CW2A(m_name.GetString()));
	std::string _account(CW2A(m_account.GetString()));
	std::string _pwd(CW2A(m_pwd.GetString()));
	if (m_account == "" || m_pwd == "" || m_name == "")
	{
		AfxMessageBox(_T("不能留有空白项!"));
	}
	else if (!logic.checkText(_name) || !logic.checkPwd(_pwd) || !logic.checkText(_account)) {
		AfxMessageBox(_T("请不要输入特殊字符"));
	}
	else if (logic.judgePasswordStrength(_pwd) == 1) {
		AfxMessageBox(_T("密码太弱，请混合数字和英文大小写字符"));
	}
	else if (m_staffaccount == "未登录") {
		AfxMessageBox(_T("请先登入储蓄员"));
	}
	else
	{
		if (logic.signInStaff(_account, _pwd, _name))
		{
			AfxMessageBox(_T("储蓄员注册成功!"));
			CDialogEx::OnOK();
		}
		else {
			AfxMessageBox(_T("注册失败，请重试!"));
		}
	}
	
	
}
