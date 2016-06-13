
// ServerDlg.cpp : 实现文件
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
   从源字符串strSrc中，截取lpszCharSet出现iTimes次到iTimes+1次之间的字符子串
   strSrc：源字符串
   iTimes：第几次匹配后开始截取
   lpszCharSet：匹配字符

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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CServerDlg 对话框



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


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str_Sql;
	CString str_Error;
	UpdateData(TRUE);
	if (str_UserName.Trim(" ").IsEmpty())
	{
		::AfxMessageBox("请输入用户名");
		return;
	}
	if (str_Password.Trim(" ").IsEmpty())
	{
		::AfxMessageBox("请输入密码");
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
		::AfxMessageBox(_T("用户不存在或密码错误"));
		return;
	}


}


void CServerDlg::OnBnReg()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgRegesiter  CRegDlg;
	CRegDlg.DoModal();

}


void CServerDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
