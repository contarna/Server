#pragma once
#include "afxwin.h"


// CDlgRegesiter �Ի���

class CDlgRegesiter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRegesiter)

public:
	CDlgRegesiter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRegesiter();

// �Ի�������
	enum { IDD = IDD_DlgReg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ע���Ա�
	CButton m_RadioSex;
	CString m_strRegUserName;
	CString m_strRegPwd;
	CString m_strRegPwdCheck;
	CString m_strRealName;
	//ע�����Ƿ�Ϸ�
	bool m_bUserExist;

	CBrush m_Greybrush;

	afx_msg void OnBnClickedOk();
	// ����������ݺϷ���
	bool CheckValue();
	// ���ע�������Ƿ����
	bool CheckIsExist(CString RegUserName);
	// ������û�
	bool AddNewUser(CString str_Name, CString str_Pwd, CString str_RealName, CString str_Sex);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
