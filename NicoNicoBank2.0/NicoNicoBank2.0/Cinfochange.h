#pragma once

#include "Ccheckpwd.h"
// Cinfochange 对话框

class Cinfochange : public CDialogEx
{
	DECLARE_DYNAMIC(Cinfochange)

public:
	Cinfochange(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cinfochange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFOCHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_newaddress;
	CString m_oldpwd;
	CString m_newpwd;
	afx_msg void OnBnClickedchangeaddress();
	afx_msg void OnBnClickedOk();
	Ccheckpwd checkpwd;
	afx_msg void OnBnClickedchangepwd();
};
