// DlgMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "DlgMain.h"
#include "afxdialogex.h"

extern UserInfo g_sysUseInfo;

// CDlgMain �Ի���

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


// CDlgMain ��Ϣ�������


void CDlgMain::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HBITMAP hBitmap;
	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_Female));
	((CButton*)GetDlgItem(IDC_BUTTON1))->SetBitmap((HBITMAP)hBitmap);
}


BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//�趨����
	CFont m_font;
	m_font.CreatePointFont(200, _T("���Ĳ���"));
	((CStatic*)GetDlgItem(IDC_STATIC_UserName))->SetFont(&m_font);
	m_strUserName = g_sysUseInfo.str_UserName;
	m_font.Detach();
	UpdateData(FALSE);

	//��ʼ���Ի�
	((CListBox *)GetDlgItem(IDC_LIST_Index))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgMain::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//ȡ�ñ��϶��ļ�����Ŀ
	for (int i = 0; i < DropCount; i++)
	{
		char wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
	
		CString str_Filename;
		str_Filename.Format("%s", wcStr);

		//�����ļ�����д�����ݿ�,������
		//������ļ���ʽ��ɸѡ��ͬʱ�ļ��������ݱ��Ա�����ٴ�����ʱ������ʾ�б�
		//�˴�д�����ݿ⣬Ӧ�������ļ������ļ��洢·�����ļ���ʽ
		str_Filename = RecordFile(str_Filename);
		m_ListIndex.AddString(str_Filename);
	}
	DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�
	CDialogEx::OnDropFiles(hDropInfo);
}


/************************************************************************/
/* [function note]
   [list]
   �����ļ�·���������ļ���
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
   �����ļ��������ļ���ʽ���࣬��������������enum File_Extensions
/* [2016/3/14/22-lipengsong]                          	*/
/************************************************************************/
int CDlgMain::MatchFileExten(CString FileName)
{

	return File_Err;
}
