// DlgRegesiter.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "DlgRegesiter.h"
#include "afxdialogex.h"

extern CMySqlOperate mysqlOperate;

// CDlgRegesiter 对话框

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


// CDlgRegesiter 消息处理程序


void CDlgRegesiter::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
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
			str_Sex = m_RadioSex > 0 ? "女" : "男";
			bool  m_bAddResult =AddNewUser(m_strRegUserName, m_strRegPwd, m_strRealName, str_Sex);
			if (!m_bAddResult)
			{
				::AfxMessageBox("添加新用户失败!");
			}
			else
			{
				::AfxMessageBox("添加成功，请登录");
			}
		}
	}
	CDialogEx::OnOK();
}


// 检查输入数据合法性
bool CDlgRegesiter::CheckValue()
{
	UpdateData(TRUE);
	if (m_strRegUserName.Trim(" ").IsEmpty() 
		|| m_strRegPwdCheck.Trim(" ").IsEmpty()
		|| m_strRegPwd.Trim(" ").IsEmpty())
	{
		::AfxMessageBox("*内容不能为空！");
		return false;
	}

	if (m_strRegPwd != m_strRegPwdCheck)
	{
		::AfxMessageBox("两次密码不一致！");
		return false;
	}
	
	return true;
}

/*根据注册用户名查询数据库中对应uid,若返回非零，代表已存在同名用户*/
// 检查注册名称是否存在
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
		::AfxMessageBox(_T("用户名已存在"));
		return true;
	}
	else
	{
		return false;
	}

	//return false;
}


// 添加新用户
bool CDlgRegesiter::AddNewUser(CString str_Name, CString str_Pwd, CString str_RealName, CString str_Sex)
{
	CString str_Sql;
	CString str_Error;

	str_Sql.Format("Insert into user(name,password,realname,sex) values('%s','%s','%s','%s');", str_Name,str_Pwd,str_RealName,str_Sex);
	char* p = str_Sql.GetBuffer(str_Sql.GetLength());

	bool m_bAdd = mysqlOperate.ExcuteSQL(p);
	return  m_bAdd;
}

// 离开用户名控件时检查注册名是否已存在 [10/9/2015 -lipengsong]
void CDlgRegesiter::OnEnKillfocusEdit1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_bUserExist = CheckIsExist(m_strRegUserName);

	GetDlgItem(IDC_EDIT_RegName)->Invalidate();
	GetDlgItem(IDC_EDIT_RegName)->UpdateWindow();
	
}


HBRUSH CDlgRegesiter::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor ==CTLCOLOR_EDIT)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case  IDC_EDIT_RegName:
			if (m_bUserExist)
			{
				//用户名已存在，更改编辑框颜色
				pDC->SetTextColor(RGB(255, 0, 0));
				pDC->SetBkColor(RGB(220, 220, 220));
				pDC->SetBkMode(TRANSPARENT);
				return m_Greybrush;
			}
	
		default:
			break;
		}

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CDlgRegesiter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//创建灰色画刷
	m_Greybrush.CreateSolidBrush(RGB(200,200,200));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
