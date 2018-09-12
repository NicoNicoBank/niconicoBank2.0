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
const char CCH[] = "0123456789";


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

//UTF-8转Unicode 
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

//unicode 转为 ascii 
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

//utf-8 转 ascii 
string Func::UTF_82ASCII(string& strUtf8Code)
{
	string strRet("");
	//先把 utf8 转为 unicode 
	wstring wstr = Utf82Unicode(strUtf8Code);
	//最后把 unicode 转为 ascii 
	strRet = WideByte2Acsi(wstr);
	return strRet;
}

/////////////////////////////////////////////////////////////////////// 
//ascii 转 Unicode 
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

//Unicode 转 Utf8 
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
	int chLen = strlen(CCH);
	for (int i = 0; i < length; ++i)
	{
		int x = rand() % chLen;

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

//ascii 转 Utf8 
string Func::ASCII2UTF_8(string& strAsciiCode)
{
	string strRet("");
	//先把 ascii 转为 unicode 
	wstring wstr = Acsi2WideByte(strAsciiCode);
	//最后把 unicode 转为 utf8 
	strRet = Unicode2Utf8(wstr);
	return strRet;
}

bool Func::checkIdNumberFormat(string& IDNumber) {
	regex reg1("[0-9]{17}([0-9Xx])", regex_constants::extended);//正则表达式，匹配18位身份证
	smatch result;
	return (regex_match(IDNumber, result, reg1));

}

bool Func::checkIDNumber(string& IDNumber) {
	int weight[] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };//各数字权重
	char validate[] = { '1','0','X','9','8','7','6','5','4','3','2' };
	int sum = 0;
	int mode = 0;
	int length = IDNumber.length();
	if (length == 18)
	{
		for (int i = 0; i < length - 1; i++) {
			sum = sum + (IDNumber[i] - '0')*weight[i];
		}
		mode = sum % 11;
		if (validate[mode] == IDNumber[17])
		{
			return true;
		}
	}

	return false;

}

//传入身份证号，返回0，身份证长度不对；返回-1，身份证格式有误；返回1，身份证验证成功
int Func::judgeIdNumber(string& IDNumber) {
	if (checkIdNumberFormat(IDNumber)) {
		if (checkIDNumber(IDNumber)) {
			return 1;//身份证验证成功
		}
		else {
			return -1;//身份证格式有误
		}
	}
	else {
		return 0;//身份证长度不对
	}
}

//传入密码（字符串），返回Int型的密码强度（1-3）依次为（弱，中等，强）
int Func::judgePasswordStrength(string password) {
	int i, score;
	score = 0;
	int length = password.length();
	if (length < 6)//密码长度小于6,
		return 1;

	//字母 数字
	int flagBig = 0, flagSmall = 0;
	int flagNum = 0;
	int flagOther = 0;

	//判断密码中的字符数目
	for (i = 0; i < length; i++)
	{
		if (password[i] >= 'a' && password[i] <= 'z')
		{
			flagSmall += 1;
		}
		else if (password[i] >= 'A' && password[i] <= 'Z')
		{
			flagBig += 1;
		}
		else if (password[i] >= '0' && password[i] <= '9')
		{
			flagNum += 1;
		}
		else
		{
			flagOther += 1;
		}
	}

	if (flagNum == length)//密码为纯数字
		return 1;

	int pwdLeavel = 0;//

	if (flagBig)
		pwdLeavel++;
	if (flagSmall)
		pwdLeavel++;
	if (flagOther)
		pwdLeavel++;
	if (flagNum)
		pwdLeavel++;

	switch (pwdLeavel) {
	case 0:return 1;
	case 1: return 2;
	case 2: return 2;
	case 3: if (length > 10)
		return 3;
			else return 2;
	case 4: if (length > 10)
		return 3;
			else return 2;
	}
}


//判断密码输入，通过返回true，否则返回false。只能包含字母，数字，及指定特殊字符 { '~', '!', '@',  '$', '%', '^', '&', '*', '(', ')' }
bool Func::checkPwd(string str) {
	int length = str.length();
	char whiteList[] = { '~', '!', '@',  '$', '%', '^', '&', '*', '(', ')' };

	for (int i = 0; i < length; i++) {
		if ((str[i] >= '0'&&str[i] <= '9') || (str[i] >= 'a'&&str[i] <= 'z' || (str[i] >= 'A'&&str[i] <= 'Z')))
			continue;

		bool flag = false;
		for (int t = 0; t < 10; t++) {
			if (str[i] == whiteList[t]) {
				flag = true;
				break;
			}
		}

		if (flag)
			continue;
		else
			return false;
	}
	return true;
}

//检测输入的字符串，通过返回true，否则返回false。不能包含指定字符 { ' ', '#', '-',  ';'}
bool Func::checkText(string str) {
	int length = str.length();
	char blackList[] = { ' ', '#', '-',  ';', '*' };

	for (int i = 0; i < length; i++) {
		for (int t = 0; t < 5; t++) {
			if (str[i] == blackList[t])
				return false;
		}
	}

	return true;
}

bool Func::checkWithdrawalMoney(string & money)
{
	if (money.length() > 20)
		return false;//返回0，超出长度限制
	regex reg1("[0-9]+([.][0-9]{1,2})?", regex_constants::extended);//正则表达式，匹配18位身份证
	smatch result;
	return (regex_match(money, result, reg1));
}
