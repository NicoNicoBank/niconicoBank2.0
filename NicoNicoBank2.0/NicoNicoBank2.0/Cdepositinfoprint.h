#pragma once


// Cdepositinfoprint 对话框

class Cdepositinfoprint : public CDialogEx
{
	DECLARE_DYNAMIC(Cdepositinfoprint)

public:
	Cdepositinfoprint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cdepositinfoprint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEPOSITINFOPRINT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
};
