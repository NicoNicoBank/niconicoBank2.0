#pragma once


// Ccheckpwd 对话框

class Ccheckpwd : public CDialogEx
{
	DECLARE_DYNAMIC(Ccheckpwd)

public:
	Ccheckpwd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Ccheckpwd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHECKPWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_pwd;
};
