#pragma once

using namespace std;

#include "winsock.h"
#include "mysql.h"


#pragma comment(lib,"libmysql.lib")

class CMySqlOperate
{
public:
	CMySqlOperate();
	~CMySqlOperate();

	MYSQL mysql;
	

	bool ConnectMysql(char* host, int port, char* user, char* password, char* DBName, char* charset, CString& Msg);
	bool ExcuteSQL(char* str_sql);
	CString SelectSQL(char* sql, int Connum, CString& str_result);
};

