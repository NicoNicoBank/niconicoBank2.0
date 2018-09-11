#pragma once


// CUserInfo 对话框

class CUserInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CUserInfo)

public:
	CUserInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERINFO };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl UserInfoList;
	CString UserInfoSearchText;
	afx_msg void OnBnClickedButton2();
	CComboBox UserSearchType;
	afx_msg void OnCbnSelchangeCombo1();
};
