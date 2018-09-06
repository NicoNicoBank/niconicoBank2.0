
// NICONICOBANK2.0Dlg.h: 头文件
//

#pragma once
#include "CloginDlg.h"
#include "CdepositDlg.h"
#include "CwithdrawalDlg.h"
#include "CwithdrawalDlg2.h"

// CNICONICOBANK20Dlg 对话框
class CNICONICOBANK20Dlg : public CDialogEx
{
	// 构造
public:
	CNICONICOBANK20Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NICONICOBANK20_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 记录储蓄员的账号
//	CString staffaccount;
	// 记录储蓄员的密码// 记录储蓄员的密码
//	CString staffpwd;
	afx_msg void OnBnClickedstafflogin();
	// 这里是调用的登录子框
	CloginDlg logindlg;
	afx_msg void OnBnClickedstaffchange();

	afx_msg void OnBnClickeduserchange();
	//显示隐藏注销按钮
	void showstafflogout();
	void hidestafflogout();
	void showuserlogout();
	void hideuserlogout();
	afx_msg void OnBnClickedstafflogout();
	afx_msg void OnBnClickeduserlogout();

	//这里是存款框
	//CdepositDlg depositdlg;
	afx_msg void OnBnClickeddeposit();
	CdepositDlg depositdlg;
	afx_msg void OnEnChangeEdit1();
	//CwithdrawalDlg withdrwaldlg;
	

	afx_msg void OnBnClickedwithdrawal();
	// 这个是取款框
//	CwithdrawalDlg withdrawaldlg;
//	Cwithdrawaldlg withdrawaldlg;
	CwithdrawalDlg withdrawaldlg;
	CwithdrawalDlg2 withdrawaldlg2;
};
