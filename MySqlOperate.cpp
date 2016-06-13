#include "stdafx.h"
#include "MySqlOperate.h"


CMySqlOperate::CMySqlOperate()
{

}


CMySqlOperate::~CMySqlOperate()
{
}


bool CMySqlOperate::ConnectMysql(char* host, int port, char* user, char* password, char* DBName, char* charset, CString& Msg)
{
	// 初始化mysql [9/20/2015 -lipengsong]
	if (mysql_init(&mysql)== NULL)
	{
		Msg = "initial mysql failed";
		return false;
	}
	// 连接数据库 [9/20/2015 -lipengsong]
	if (mysql_real_connect(&mysql,host,user,password,DBName,port,NULL,0) ==NULL)
	{
		Msg.Format(_T("Connect %s failed"), DBName);
		return false;
	}
	// 设置字符集 [9/20/2015 -lipengsong]
	if (mysql_set_character_set(&mysql,charset) !=0)
	{
		Msg = "Set charset failed";
		return false;
	}
	return true;
}

// 执行SQL语句 [9/20/2015 -lipengsong]
bool CMySqlOperate::ExcuteSQL(char* str_sql)
{
	char sql[2048];
	sprintf_s(sql,str_sql);

	if (mysql_query(&mysql,sql) !=0)
	{
		return false;
	}

	return true;
}


CString CMySqlOperate::SelectSQL(char* sql, int Connum, CString& str_result)
{
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;

	int rnum = 0;
	char rg = '|'; //行隔开
	char cg = ','; //字段隔开

	CString str = _T("");

	if (mysql_query(&mysql, sql) != 0)
	{
		str_result = "select ps_info_Error!";

		return str;
	}

	m_res = mysql_store_result(&mysql);
	if (m_res == NULL)
	{
		str_result = "select username Error!";
		return str;
	}

	while (m_row = mysql_fetch_row(m_res))
	{
		for (int i = 0; i < Connum; i++)
		{
			str += m_row[i];
			str += cg;
		}
		str += rg;
		rnum++;
	}

	mysql_free_result(m_res);
	return str;
}
