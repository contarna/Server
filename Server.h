
// Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Common.h"

// CServerApp: 
// �йش����ʵ�֣������ Server.cpp
//
struct mysql_Connect
{
	char* host;
	char* username;
	char* password;
	char* dbname;
	char* charset;
	int port;
};

class CServerApp : public CWinApp
{
public:
	CServerApp();
	mysql_Connect mysql_ConData;
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServerApp theApp;