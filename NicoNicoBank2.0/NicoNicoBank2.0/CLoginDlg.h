#pragma once


// CloginDlg 对话框
//#include "NICONICOBANK2.0Dlg.h"

class CloginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CloginDlg)

public:
	CloginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CloginDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 记录当下修改是储蓄员还是用户
	CString m_logintitle;
	// 记录储蓄员或用户的账号
	CString m_account;
	// 记录储蓄员或账户的密码
	CString m_pwd;
	afx_msg void OnBnClickedlogin();
	afx_msg void OnEnChangeaccount();
	afx_msg void OnBnClickedOk();
	//CNICONICOBANK20Dlg maindlg;
};
