// DlgRegesiter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "DlgRegesiter.h"
#include "afxdialogex.h"

extern CMySqlOperate mysqlOperate;

// CDlgRegesiter �Ի���

IMPLEMENT_DYNAMIC(CDlgRegesiter, CDialogEx)

CDlgRegesiter::CDlgRegesiter(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRegesiter::IDD, pParent)
	, m_strRegUserName(_T(""))
	, m_strRegPwd(_T(""))
	, m_strRegPwdCheck(_T(""))
	, m_strRealName(_T(""))
	, m_bUserExist(false)
{

}

CDlgRegesiter::~CDlgRegesiter()
{
}

void CDlgRegesiter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_Sex, m_RadioSex);
	DDX_Text(pDX, IDC_EDIT_RegName, m_strRegUserName);
	//  DDV_MaxChars(pDX, m_strRegUserName, 64);
	DDX_Text(pDX, IDC_EDIT_RegPwd, m_strRegPwd);
	DDV_MaxChars(pDX, m_strRegPwd, 32);
	DDX_Text(pDX, IDC_EDIT_RegPwdCheck, m_strRegPwdCheck);
	DDV_MaxChars(pDX, m_strRegPwdCheck, 32);
	//  DDX_Text(pDX, IDC_EDIT3, m);
	DDX_Text(pDX, IDC_EDIT_RegRealName, m_strRealName);
	DDV_MaxChars(pDX, m_strRealName, 32);
}


BEGIN_MESSAGE_MAP(CDlgRegesiter, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRegesiter::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CDlgRegesiter::OnEnKillfocusEdit1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgRegesiter ��Ϣ�������


void CDlgRegesiter::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// Check information [10/8/2015 -lipengsong]
	bool result = CheckValue();
	if (!result)
	{
		return;
	}
	else
	{
		bool m_bIsExist = CheckIsExist(m_strRegUserName);
		if (!m_bIsExist)
		{
			CString str_Sex;
			str_Sex = m_RadioSex > 0 ? "Ů" : "��";
			bool  m_bAddResult =AddNewUser(m_strRegUserName, m_strRegPwd, m_strRealName, str_Sex);
			if (!m_bAddResult)
			{
				::AfxMessageBox("������û�ʧ��!");
			}
			else
			{
				::AfxMessageBox("��ӳɹ������¼");
			}
		}
	}
	CDialogEx::OnOK();
}


// ����������ݺϷ���
bool CDlgRegesiter::CheckValue()
{
	UpdateData(TRUE);
	if (m_strRegUserName.Trim(" ").IsEmpty() 
		|| m_strRegPwdCheck.Trim(" ").IsEmpty()
		|| m_strRegPwd.Trim(" ").IsEmpty())
	{
		::AfxMessageBox("*���ݲ���Ϊ�գ�");
		return false;
	}

	if (m_strRegPwd != m_strRegPwdCheck)
	{
		::AfxMessageBox("�������벻һ�£�");
		return false;
	}
	
	return true;
}

/*����ע���û�����ѯ���ݿ��ж�Ӧuid,�����ط��㣬�����Ѵ���ͬ���û�*/
// ���ע�������Ƿ����
bool CDlgRegesiter::CheckIsExist(CString RegUserName)
{
	CString str_Sql;
	CString str_Error;

	str_Sql.Format("Select uid from user where name ='%s'", RegUserName);
	char* p = str_Sql.GetBuffer(str_Sql.GetLength());

	CString str_return = "";

	str_return = mysqlOperate.SelectSQL(p, 1, str_Error);
	if (str_return.GetLength() > 0)
	{
		::AfxMessageBox(_T("�û����Ѵ���"));
		return true;
	}
	else
	{
		return false;
	}

	//return false;
}


// ������û�
bool CDlgRegesiter::AddNewUser(CString str_Name, CString str_Pwd, CString str_RealName, CString str_Sex)
{
	CString str_Sql;
	CString str_Error;

	str_Sql.Format("Insert into user(name,password,realname,sex) values('%s','%s','%s','%s');", str_Name,str_Pwd,str_RealName,str_Sex);
	char* p = str_Sql.GetBuffer(str_Sql.GetLength());

	bool m_bAdd = mysqlOperate.ExcuteSQL(p);
	return  m_bAdd;
}

// �뿪�û����ؼ�ʱ���ע�����Ƿ��Ѵ��� [10/9/2015 -lipengsong]
void CDlgRegesiter::OnEnKillfocusEdit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_bUserExist = CheckIsExist(m_strRegUserName);

	GetDlgItem(IDC_EDIT_RegName)->Invalidate();
	GetDlgItem(IDC_EDIT_RegName)->UpdateWindow();
	
}


HBRUSH CDlgRegesiter::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor ==CTLCOLOR_EDIT)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case  IDC_EDIT_RegName:
			if (m_bUserExist)
			{
				//�û����Ѵ��ڣ����ı༭����ɫ
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->SetBkColor(RGB(220, 220, 220));
				pDC->SetBkMode(TRANSPARENT);
				return m_Greybrush;
			}
	
		default:
			break;
		}

	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CDlgRegesiter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//������ɫ��ˢ
	m_Greybrush.CreateSolidBrush(RGB(200,200,200));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
