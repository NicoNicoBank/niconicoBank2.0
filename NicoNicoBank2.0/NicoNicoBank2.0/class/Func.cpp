#include "Func.h"
#include <direct.h>
#include "User.h"
#include "sqlite3.h"
#include "Func.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <CppSQLite3.h>
const int MAX_LENGTH = 1000;
const char CCH[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


Func::Func()
{
}

Func::~Func()
{
}

string Func::getPwd()
{
	char buff[1000];
	_getcwd(buff, 1000);
	string pwd = buff;
	return pwd;
}

string Func::getDataBaseLocation()
{
	string pwd = getPwd();
	pwd += "\\database\\bank.db";
	return pwd;
}

//UTF-8תUnicode 
wstring Func::Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	return std::wstring(&resultstring[0]);
}

//unicode תΪ ascii 
string Func::WideByte2Acsi(wstring& wstrcode)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(asciisize);
	int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
}

//utf-8 ת ascii 
string Func::UTF_82ASCII(string& strUtf8Code)
{
	string strRet("");
	//�Ȱ� utf8 תΪ unicode 
	wstring wstr = Utf82Unicode(strUtf8Code);
	//���� unicode תΪ ascii 
	strRet = WideByte2Acsi(wstr);
	return strRet;
}

/////////////////////////////////////////////////////////////////////// 
//ascii ת Unicode 
wstring Func::Acsi2WideByte(string& strascii)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	return std::wstring(&resultstring[0]);
}

//Unicode ת Utf8 
string Func::Unicode2Utf8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(utf8size);
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
}


string Func::getRandomstring(int length)
{
	srand((unsigned)time(NULL));
	char ch[MAX_LENGTH];
	for (int i = 0; i < length; ++i)
	{
		//int x = rand() % (sizeof(CCH) - 1); //�����������, ��Ϊ���������������ĵ�λ���ز������,

//RAND MAX ��ANSI ��#define ��<stdlib.h>

//RAND MAX �Ǹ�����, ��������C �⺯��rand() �Ĺ̶���Χ��

//��������RAND MAX Ϊ������ֵ, Ҳû�а취Ҫ��rand() ����������Χ��ֵ��
		int x = rand() % 62;

		ch[i] = CCH[x];
	}
	ch[length] = '\0';
	string temp = ch;
	return string(temp);
}

string Func::sqlExce(string sql)
{
	Func func;
	CppSQLite3DB db;
	//try {
	db.open(func.getDataBaseLocation().c_str());
	CppSQLite3Query q = db.execQuery(sql.c_str());
	q.finalize();
	db.close();
	/*}
	catch (CppSQLite3Exception & e) {
		cout << e.errorMessage() << endl;
	}*/
	return string();
}

//ascii ת Utf8 
string Func::ASCII2UTF_8(string& strAsciiCode)
{
	string strRet("");
	//�Ȱ� ascii תΪ unicode 
	wstring wstr = Acsi2WideByte(strAsciiCode);
	//���� unicode תΪ utf8 
	strRet = Unicode2Utf8(wstr);
	return strRet;
}