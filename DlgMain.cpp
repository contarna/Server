// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "DlgMain.h"
#include "afxdialogex.h"

extern UserInfo g_sysUseInfo;

// CDlgMain 对话框

IMPLEMENT_DYNAMIC(CDlgMain, CDialogEx)

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
	, m_strUserName(_T(""))
{

}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btnUserPic);
	DDX_Text(pDX, IDC_STATIC_UserName, m_strUserName);
	DDX_Control(pDX, IDC_LIST_Index, m_ListIndex);
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgMain::OnBnClickedButton1)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CDlgMain 消息处理程序


void CDlgMain::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	HBITMAP hBitmap;
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_Female));
	((CButton*)GetDlgItem(IDC_BUTTON1))->SetBitmap((HBITMAP)hBitmap);
}


BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设定字体
	CFont m_font;
	m_font.CreatePointFont(200, _T("华文彩云"));
	((CStatic*)GetDlgItem(IDC_STATIC_UserName))->SetFont(&m_font);
	m_strUserName = g_sysUseInfo.str_UserName;
	m_font.Detach();
	UpdateData(FALSE);

	//初始化对话
	((CListBox *)GetDlgItem(IDC_LIST_Index))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgMain::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目
	for (int i = 0; i < DropCount; i++)
	{
		char wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名
	
		CString str_Filename;
		str_Filename.Format("%s", wcStr);

		//处理文件名，写入数据库,待开发
		//加入对文件格式的筛选，同时文件存入数据表，以便程序再次运行时重新显示列表
		//此处写入数据库，应当包含文件名、文件存储路径、文件格式
		str_Filename = RecordFile(str_Filename);
		m_ListIndex.AddString(str_Filename);
	}
	DragFinish(hDropInfo);  //拖放结束后,释放内存
	CDialogEx::OnDropFiles(hDropInfo);
}


/************************************************************************/
/* [function note]
   [list]
   根据文件路径，返回文件名
/* [2016/3/14/22-lipengsong]                          	*/
/************************************************************************/
CString CDlgMain::RecordFile(CString FilePath)
{
	CString str_Filename;
	str_Filename =FilePath;
	int n = str_Filename.ReverseFind('\\');
	str_Filename = str_Filename.Right(str_Filename.GetLength() - n - 1);
	return str_Filename;
}

/************************************************************************/
/* [function note]
   [list]
   根据文件名返回文件格式分类，分类依据来自于enum File_Extensions
/* [2016/3/14/22-lipengsong]                          	*/
/************************************************************************/
int CDlgMain::MatchFileExten(CString FileName)
{

	return File_Err;
}
