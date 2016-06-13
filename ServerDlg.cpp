
// ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "DlgRegesiter.h"
#include "DlgMain.h"


extern CMySqlOperate mysqlOperate;

UserInfo g_sysUseInfo;


/************************************************************************/
/* [function note]
   [list]
   ��Դ�ַ���strSrc�У���ȡlpszCharSet����iTimes�ε�iTimes+1��֮����ַ��Ӵ�
   strSrc��Դ�ַ���
   iTimes���ڼ���ƥ���ʼ��ȡ
   lpszCharSet��ƥ���ַ�

/* [2016/3/14/23-lipengsong]                          	*/
/************************************************************************/
CString GetSubString(const CString strSrc, int iTimes, LPCTSTR lpszCharSet)
{
	CString strCopy = strSrc;
	int iSetLen = strlen(lpszCharSet);
	int iIndex = strCopy.Find(lpszCharSet) + iSetLen - 1;
	for (int i = 0; i < iTimes; ++i)
	{
		if (iIndex == -1)
		{
			strCopy.Empty();
			break;
		}
		strCopy = strCopy.Right(strCopy.GetLength() - iIndex - 1);
		iIndex = strCopy.Find(lpszCharSet);
	}
	if (iSetLen <= 1)
		return strCopy.SpanExcluding(lpszCharSet);
	else
	{
		iIndex = strCopy.Find(lpszCharSet);
		return strCopy.Left(strCopy.GetLength() - iIndex + 1);
	}
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg �Ի���



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
	, str_UserName(_T(""))
	, str_Password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_UserName, str_UserName);
	DDX_Text(pDX, IDC_PWD, str_Password);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CServerDlg::OnBnReg)
	ON_BN_CLICKED(IDCANCEL, &CServerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CServerDlg ��Ϣ��������

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ����Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnBnClickedOk()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString str_Sql;
	CString str_Error;
	UpdateData(TRUE);
	if (str_UserName.Trim(" ").IsEmpty())
	{
		::AfxMessageBox("�������û���");
		return;
	}
	if (str_Password.Trim(" ").IsEmpty())
	{
		::AfxMessageBox("����������");
		return;
	}
	str_Sql.Format("Select * from user where name ='%s' and password ='%s'", str_UserName,str_Password);
	
	char* p = str_Sql.GetBuffer(str_Sql.GetLength());

	CString str_return ="";

	str_return = mysqlOperate.SelectSQL(p,5,str_Error);
	if (str_return.GetLength()>0)
	{
		// uid,name,pwd,realname,sex [10/29/2015 -lipengsong]
		
		g_sysUseInfo.str_UserName = GetSubString(str_return, 1, ",");
		g_sysUseInfo.str_UserSex = GetSubString(str_return, 4, ",");

		::AfxMessageBox(str_return);
		::AfxMessageBox(g_sysUseInfo.str_UserName);
		::AfxMessageBox(g_sysUseInfo.str_UserSex);

		CDialogEx::OnOK();
		CDlgMain  dlgMain;
		dlgMain.DoModal();	
		
	}
	else
	{
		::AfxMessageBox(_T("�û������ڻ��������"));
		return;
	}


}


void CServerDlg::OnBnReg()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CDlgRegesiter  CRegDlg;
	CRegDlg.DoModal();

}


void CServerDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CDialogEx::OnCancel();
}