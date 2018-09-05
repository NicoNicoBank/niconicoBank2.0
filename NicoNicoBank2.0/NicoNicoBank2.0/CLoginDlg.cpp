// CloginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "NICONICOBANK2.0.h"
#include "CloginDlg.h"
#include "afxdialogex.h"
#include "Logic.h"
#include "Resource.h"

/*该板块一共会承担5个模块功能
1.储蓄员登录
2.用户登录
3.储蓄员账户切换
4.用户账号切换
5.用户密码验证(即进行存取款等一系列操作的时候)
6.用户注销
7.储蓄员注销
*/

//这里是全局变量m_staffaccount

extern CString m_staffaccount;
extern CString m_useraccount;


//CButton *pBtn1 = (CButton *)GetDlgItem(IDC_staffchange);

// CloginDlg 对话框

IMPLEMENT_DYNAMIC(CloginDlg, CDialogEx)

CloginDlg::CloginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_logintitle(_T(""))
	, m_account(_T(""))
	, m_pwd(_T(""))
{

}

CloginDlg::~CloginDlg()
{
}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_logintitle, m_logintitle);
	DDX_Text(pDX, IDC_account, m_account);
	DDX_Text(pDX, IDC_pwd, m_pwd);
}


BEGIN_MESSAGE_MAP(CloginDlg, CDialogEx)


	ON_BN_CLICKED(IDOK, &CloginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CloginDlg 消息处理程序

BOOL CloginDlg::OnInitDialog()
{
	UpdateData(FALSE);
	return true;
}





void CloginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Logic logic;
	//1.储蓄员登录
	//CButton *pBtn1 = (CButton *)GetDlgItem(IDC_staffchange);
	//CButton *pBtn2 = (CButton *)GetDlgItem(IDC_userchange);
	if (m_logintitle == "储蓄员登录")
	{
		std::string _pwd(CW2A(m_pwd.GetString()));
		std::string _account(CW2A(m_account.GetString()));
		if (logic.verifyStaff(_account, _pwd))
		{
			AfxMessageBox(_T("欢迎回来！"));
			//m_staffaccount = m_account;
			//将主页的登录改成切换


			//CDialog::OnOK();

			CDialogEx::OnOK();

		}
		else {
			AfxMessageBox(_T("账号或密码有误，登录失败!"));
		}

	}
	else if (m_logintitle == "储蓄员账号切换")
	{
		std::string _pwd(CW2A(m_pwd.GetString()));
		std::string _account(CW2A(m_account.GetString()));
		//若为当前账号
		if (m_staffaccount == m_account)
		{
			AfxMessageBox(_T("这是当前账号!"));
			return;

		}
		if (logic.verifyStaff(_account, _pwd))
		{
			AfxMessageBox(_T("账户切换成功！"));
			//m_staffaccount = m_account;
			//将主页的登录改成切换


			//CDialog::OnOK();

			CDialogEx::OnOK();

		}
		else {
			AfxMessageBox(_T("账号或密码有误，切换账号失败!"));
		}
	}
	else if (m_logintitle == "用户登录")
	{
		std::string _pwd(CW2A(m_pwd.GetString()));
		std::string _account(CW2A(m_account.GetString()));
		if (logic.verifyUser(_account, _pwd))
		{
			AfxMessageBox(_T("用户登录成功！"));

			//将主页的登录改成切换


			//CDialog::OnOK();

			CDialogEx::OnOK();

		}
		else {
			AfxMessageBox(_T("账号或密码有误，登录失败!"));
		}
	}
	else if (m_logintitle == "用户账号切换")
	{
		std::string _pwd(CW2A(m_pwd.GetString()));
		std::string _account(CW2A(m_account.GetString()));
		if (m_useraccount == m_account)
		{
			AfxMessageBox(_T("这是当前账号!"));
			return;

		}
		if (logic.verifyUser(_account, _pwd))
		{
			AfxMessageBox(_T("账号切换成功！"));

			//将主页的登录改成切换


			//CDialog::OnOK();

			CDialogEx::OnOK();

		}
		else {
			AfxMessageBox(_T("账号或密码有误，切换账号失败!"));
		}
	}


}
