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

bool Func::checkIdNumberFormat(string& IDNumber) {
	regex reg1("[0-9]{17}([0-9Xx])", regex_constants::extended);//������ʽ��ƥ��18λ���֤
	smatch result;
	return (regex_match(IDNumber, result, reg1));

}

bool Func::checkIDNumber(string& IDNumber) {
	int weight[] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };//������Ȩ��
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

//�������֤�ţ�����0�����֤���Ȳ��ԣ�����-1�����֤��ʽ���󣻷���1�����֤��֤�ɹ�
int Func::judgeIdNumber(string& IDNumber) {
	if (checkIdNumberFormat(IDNumber)) {
		if (checkIDNumber(IDNumber)) {
			return 1;//���֤��֤�ɹ�
		}
		else {
			return -1;//���֤��ʽ����
		}
	}
	else {
		return 0;//���֤���Ȳ���
	}
}

//�������루�ַ�����������Int�͵�����ǿ�ȣ�1-3������Ϊ�������еȣ�ǿ��
int Func::judgePasswordStrength(string password) {
	int i, score;
	score = 0;
	int length = password.length();
	if (length < 6)//���볤��С��6,
		return 1;

	//��ĸ ����
	int flagBig = 0, flagSmall = 0;
	int flagNum = 0;
	int flagOther = 0;

	//�ж������е��ַ���Ŀ
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

	if (flagNum == length)//����Ϊ������
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


//�ж��������룬ͨ������true�����򷵻�false��ֻ�ܰ�����ĸ�����֣���ָ�������ַ� { '~', '!', '@',  '$', '%', '^', '&', '*', '(', ')' }
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

//���������ַ�����ͨ������true�����򷵻�false�����ܰ���ָ���ַ� { ' ', '#', '-',  ';'}
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
		return false;//����0��������������
	regex reg1("[0-9]+([.][0-9]{1,2})?", regex_constants::extended);//������ʽ��ƥ��18λ���֤
	smatch result;
	return (regex_match(money, result, reg1));
}
