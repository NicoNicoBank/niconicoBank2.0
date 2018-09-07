#pragma once


// Copenaccount 对话框

class Copenaccount : public CDialogEx
{
	DECLARE_DYNAMIC(Copenaccount)

public:
	Copenaccount(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Copenaccount();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENACCOUNT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_userpwd;
	CString m_username;
	CString m_useraddress;
	CString m_idnumber;
	CString m_timedate;
	afx_msg void OnBnClickedOk();
};
