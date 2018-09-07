#pragma once
#include "Ccheckinfo.h"

// CwithdrawalDlg2 对话框
//该对话框初期没考虑好，后期发现可以复用

class CwithdrawalDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(CwithdrawalDlg2)

public:
	CwithdrawalDlg2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CwithdrawalDlg2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WITHDRAWAL2 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_withdrabox;
	afx_msg void OnLvnItemchangedwithdralist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickwithdralist(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_sysdate2;
	// 通过这个可以判断这个框的作用
	CString m_infotitle;
	Ccheckinfo checkinfo;
};
