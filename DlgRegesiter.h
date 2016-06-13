#pragma once
#include "afxwin.h"


// CDlgRegesiter 对话框

class CDlgRegesiter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRegesiter)

public:
	CDlgRegesiter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRegesiter();

// 对话框数据
	enum { IDD = IDD_DlgReg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 注册性别
	CButton m_RadioSex;
	CString m_strRegUserName;
	CString m_strRegPwd;
	CString m_strRegPwdCheck;
	CString m_strRealName;
	//注册名是否合法
	bool m_bUserExist;

	CBrush m_Greybrush;

	afx_msg void OnBnClickedOk();
	// 检查输入数据合法性
	bool CheckValue();
	// 检查注册名称是否存在
	bool CheckIsExist(CString RegUserName);
	// 添加新用户
	bool AddNewUser(CString str_Name, CString str_Pwd, CString str_RealName, CString str_Sex);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
