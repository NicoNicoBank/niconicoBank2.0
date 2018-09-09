// Cinfochange.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "Cinfochange.h"
#include "afxdialogex.h"
#include "Date.h"
#include <vector>
#include "Logic.h"


// Cinfochange 对话框
extern CString m_useraccount;
extern CString m_staffaccount;

IMPLEMENT_DYNAMIC(Cinfochange, CDialogEx)

Cinfochange::Cinfochange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFOCHANGE, pParent)
	, m_newaddress(_T(""))
	, m_oldpwd(_T(""))
	, m_newpwd(_T(""))
{

}

Cinfochange::~Cinfochange()
{
}

void Cinfochange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_newaddress, m_newaddress);
	DDX_Text(pDX, IDC_oldpwd, m_oldpwd);
	DDX_Text(pDX, IDC_newpwd, m_newpwd);
	DDX_Text(pDX, IDC_useraccount, m_useraccount);
	DDX_Text(pDX, IDC_staffaccount, m_staffaccount);
}


BEGIN_MESSAGE_MAP(Cinfochange, CDialogEx)
	ON_BN_CLICKED(IDC_changeaddress, &Cinfochange::OnBnClickedchangeaddress)
	ON_BN_CLICKED(IDOK, &Cinfochange::OnBnClickedOk)
	ON_BN_CLICKED(IDC_changepwd, &Cinfochange::OnBnClickedchangepwd)
END_MESSAGE_MAP()


// Cinfochange 消息处理程序



	/*
	修改地址
	*/
//bool setAccountAddress(string account, string address);
/*
修改密码
参数为账户， 旧密码， 新密码，二次输入新密码
*/
//bool setAccountPwd(string account, string oldPwd, string newPwd, string newPwd2);


//修改账号地址
void Cinfochange::OnBnClickedchangeaddress()
{
	// TODO: 在此添加控件通知处理程序代码
	Logic logic;
	UpdateData(TRUE);
	std::string _useraccount(CW2A(m_useraccount.GetString()));
	std::string _useraddress(CW2A(m_newaddress.GetString()));
	if (logic.setAccountAddress(_useraccount, _useraddress))
	{
		AfxMessageBox(_T("地址修改成功!"));
		CDialogEx::OnOK();
	}
	else {
		AfxMessageBox(_T("地址修改失败，请重试!"));
	}
}


void Cinfochange::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

//修改账号密码
void Cinfochange::OnBnClickedchangepwd()
{
	// TODO: 在此添加控件通知处理程序代码
	checkpwd.m_pwd = "";
	if (checkpwd.DoModal() == IDOK)
	{
		CString newpwd2 = checkpwd.m_pwd;
		//bool setAccountPwd(string account, string oldPwd, string newPwd, string newPwd2);
		Logic logic;
		UpdateData(TRUE);
		std::string _useraccount(CW2A(m_useraccount.GetString()));
		std::string _oldpwd(CW2A(m_oldpwd.GetString()));
		std::string _newpwd(CW2A(m_newpwd.GetString()));
		std::string _newpwd2(CW2A(newpwd2.GetString()));
		if (logic.setAccountPwd(_useraccount, _oldpwd, _newpwd, _newpwd2))
		{
			AfxMessageBox(_T("密码修改成功!"));
			CDialogEx::OnOK();
		}
		else {
			AfxMessageBox(_T("密码修改失败，请重试!"));
		}
	}

}
