#pragma once
#include <string>
#include <time.h>
#include <string>
#include <regex>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<sstream>

using namespace std;
class Func
{
private:
public:
	Func();
	~Func();
	/*
	��ȡ��ǰ����·��
	*/
	string getPwd();
	/*
	��ȡ���ݿ�λ��
	*/
	string getDataBaseLocation();
	/*
	��������ַ���
	*/
	string getRandomstring(int length);
	/*
	ִ��һ��sql���
	*/
	string sqlExce(string sql);
	string ASCII2UTF_8(string& strAsciiCode);
	string Unicode2Utf8(const std::wstring& widestring);
	wstring Acsi2WideByte(string& strascii);
	string UTF_82ASCII(string& strUtf8Code);
	string WideByte2Acsi(wstring& wstrcode);
	wstring Utf82Unicode(const std::string& utf8string);
	
	bool checkIdNumberFormat(string& IDNumber);
	bool checkIDNumber(string& IDNumber);
	/*
	�������֤�ţ�����0�����֤���Ȳ��ԣ�����-1�����֤��ʽ���󣻷���1�����֤��֤�ɹ�
	*/
	int judgeIdNumber(string& IDNumber);

	/*
	�������루�ַ�����������Int�͵�����ǿ�ȣ�1-3������Ϊ�������еȣ�ǿ��
	*/
	int judgePasswordStrength(string password);
	/*
	�ж��������룬ͨ������true�����򷵻�false��ֻ�ܰ�����ĸ�����֣���ָ�������ַ� { '~', '!', '@',  '$', '%', '^', '&', '*', '(', ')' }
	*/
	bool checkPwd(string str);
	/*
	���������ַ�����ͨ������true�����򷵻�false�����ܰ���ָ���ַ� { ' ', '#', '-',  ';'}
	*/
	bool checkText(string str);
};
