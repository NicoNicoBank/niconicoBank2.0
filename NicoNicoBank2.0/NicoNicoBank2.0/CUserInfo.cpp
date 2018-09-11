// CUserInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "NicoNicoBank2.0.h"
#include "CUserInfo.h"
#include "afxdialogex.h"
#include "Logic.h"
#include <string>
using namespace std;
// CUserInfo 对话框
extern CString m_staffaccount;
IMPLEMENT_DYNAMIC(CUserInfo, CDialogEx)

CUserInfo::CUserInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERINFO, pParent)
	, UserInfoSearchText(_T(""))
{

}

CUserInfo::~CUserInfo()
{
}

void CUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, UserInfoList);
	DDX_Text(pDX, IDC_EDIT1, UserInfoSearchText);
	DDX_Control(pDX, IDC_COMBO1, UserSearchType);
}


BEGIN_MESSAGE_MAP(CUserInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserInfo::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUserInfo::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BOOL CUserInfo::OnInitDialog() {
	UpdateData(FALSE);
	//初始化listbox
	//UpdateData(TRUE);

	//初始化表头
	UserInfoList.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 30);
	UserInfoList.InsertColumn(1, _T("用户"), LVCFMT_LEFT, 100);
	UserInfoList.InsertColumn(2, _T("姓名"), LVCFMT_LEFT, 100);
	UserInfoList.InsertColumn(3, _T("地址"), LVCFMT_LEFT, 100);
	UserInfoList.InsertColumn(4, _T("身份证"), LVCFMT_LEFT, 120);
	UserInfoList.InsertColumn(5, _T("开户时间"), LVCFMT_LEFT, 100);
	UserInfoList.InsertColumn(6, _T("开户员工账号"), LVCFMT_LEFT, 100);
	//m_withdrabox.InsertColumn(4, _T("单号"), LVCFMT_CENTER, 100);
	//设置风格
	DWORD dwstyle = UserInfoList.GetExtendedStyle();
	dwstyle |= LVS_EX_FULLROWSELECT;
	UserInfoList.SetExtendedStyle(dwstyle);

	//初始化列表
	//先清空
	UserInfoList.DeleteAllItems();
	// 0. 账户名 1.用户姓名 2.地址 3.身份证号 4.开户人员工号
	//string temp = "账户名";
	//CString temp2;
	//temp2 = temp.c_str();
	UserSearchType.AddString(_T("账户名"));
	UserSearchType.AddString(_T("用户姓名"));
	UserSearchType.AddString(_T("地址"));
	UserSearchType.AddString(_T("身份证号"));
	UserSearchType.AddString(_T("开户人员工号"));
	UserSearchType.SetCurSel(0);
	return true;
}
// CUserInfo 消息处理程序


void CUserInfo::OnBnClickedButton2()
{
	UpdateData(TRUE);
	UserInfoList.DeleteAllItems();
	Logic logic;
	if (m_staffaccount == "未登录") {
		AfxMessageBox(_T("请先登录储蓄员!"));
	}
	else {
		int select = UserSearchType.GetCurSel();
		
		string searchText(CW2A(UserInfoSearchText.GetString()));
		vector <string> account;
		vector <string> userName;
		vector <string> address;
		vector <string> IDNumber;
		vector <string> openDate;
		vector <string> staffAccount;
		if (logic.getAccountInfo(searchText, account, userName, address, IDNumber, openDate, staffAccount, select)) {
			int size_t = account.size();
			for (int i = 0; i < size_t; i++){
				CString temp;
				temp.Format(_T("%d"), i);
				UserInfoList.InsertItem(i, temp);
				temp = account[i].c_str();
				UserInfoList.SetItemText(i, 1, temp);
				temp = userName[i].c_str();
				UserInfoList.SetItemText(i, 2, temp);
				temp = address[i].c_str();
				UserInfoList.SetItemText(i, 3, temp);
				temp = IDNumber[i].c_str();
				UserInfoList.SetItemText(i, 4, temp);
				temp = openDate[i].c_str();
				UserInfoList.SetItemText(i, 5, temp);
			}
		}
	}
	
	//UserInfoList.SetItemText(0, 1, UserInfoSearchText);
	// TODO: 在此添加控件通知处理程序代码
}




void CUserInfo::OnCbnSelchangeCombo1()
{
	//int select = UserSearchType.GetCurSel();
	//switch (select) {
	//case 0:AfxMessageBox(_T("0!")); break;
	//case 1:AfxMessageBox(_T("1!")); break;
	//case 2:AfxMessageBox(_T("2!")); break;
	//case 3:AfxMessageBox(_T("3!")); break;
	//case 4:AfxMessageBox(_T("4!")); break;
	//}
	// TODO: 在此添加控件通知处理程序代码
}
