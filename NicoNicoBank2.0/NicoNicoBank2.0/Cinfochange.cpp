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
//三级联动
//一共34项
extern string provinces[34];
////每项有25个以内的市区
extern string citys[34][25];

IMPLEMENT_DYNAMIC(Cinfochange, CDialogEx)

Cinfochange::Cinfochange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFOCHANGE, pParent)
	, m_oldpwd(_T(""))
	, m_newpwd(_T(""))
{

}

Cinfochange::~Cinfochange()
{
}

BOOL Cinfochange::OnInitDialog()
{
	UpdateData(FALSE);
	CString temp;
	ProvinceSel.ResetContent();
	for (int i = 0; i < 34; i++) {
		temp = provinces[i].c_str();
		ProvinceSel.AddString(temp);
	}
	ProvinceSel.SetCurSel(0);

	citySel.ResetContent();
	for (int i = 0; i < 25; i++) {
		temp = citys[0][i].c_str();
		citySel.AddString(temp);
	}
	citySel.SetCurSel(0);
	
	return TRUE;
}

void Cinfochange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_oldpwd, m_oldpwd);
	DDX_Text(pDX, IDC_newpwd, m_newpwd);
	DDX_Text(pDX, IDC_useraccount, m_useraccount);
	DDX_Text(pDX, IDC_staffaccount, m_staffaccount);
	//  DDX_Control(pDX, IDC_COMBO1, ProvinceSel);
	DDX_Control(pDX, IDC_COMBO2, citySel);
	DDX_Control(pDX, IDC_COMBO1, ProvinceSel);
}


BEGIN_MESSAGE_MAP(Cinfochange, CDialogEx)
	ON_BN_CLICKED(IDC_changeaddress, &Cinfochange::OnBnClickedchangeaddress)
	ON_BN_CLICKED(IDOK, &Cinfochange::OnBnClickedOk)
	ON_BN_CLICKED(IDC_changepwd, &Cinfochange::OnBnClickedchangepwd)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cinfochange::OnCbnSelchangeCombo1)
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
	int selectProvince = ProvinceSel.GetCurSel();
	int selectCity = citySel.GetCurSel();
	string _useraddress = provinces[selectProvince] + "-" + citys[selectProvince][selectCity];
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


void Cinfochange::OnCbnSelchangeCombo1()
{
	CString temp;
	int select = ProvinceSel.GetCurSel();
	citySel.ResetContent();
	for (int i = 0; i < 25; i++) {
		temp = citys[select][i].c_str();
		citySel.AddString(temp);
	}
	citySel.SetCurSel(0);
	// TODO: 在此添加控件通知处理程序代码
}
