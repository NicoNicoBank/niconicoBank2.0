#pragma once


// Cdatechange 对话框

class Cdatechange : public CDialogEx
{
	DECLARE_DYNAMIC(Cdatechange)

public:
	Cdatechange(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cdatechange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATECHANGE };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_yearchange;
	int m_monthchange;
	int m_daychange;
	afx_msg void OnBnClickedOk();
};
