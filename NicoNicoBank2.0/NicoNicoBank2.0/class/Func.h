#pragma once
#include <string>

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
};
