#pragma once


// Ccheckinfo 对话框

class Ccheckinfo : public CDialogEx
{
	DECLARE_DYNAMIC(Ccheckinfo)

public:
	Ccheckinfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Ccheckinfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHECKINFO };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeaccount();
//	CString m_userpwd;
	CString m_userpwd;
};
