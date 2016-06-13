#pragma once
#include "afxwin.h"


// CDlgMain �Ի���

class CDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMain();

// �Ի�������
	enum { IDD = IDD_DlgMain };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton m_btnUserPic;
	CString m_strUserName;
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox m_ListIndex;
	CString RecordFile(CString FilePath);
	int MatchFileExten(CString FileName);
};
