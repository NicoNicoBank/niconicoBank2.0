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
	获取当前工作路径
	*/
	string getPwd();
	/*
	获取数据库位置
	*/
	string getDataBaseLocation();
	/*
	生成随机字符串
	*/
	string getRandomstring(int length);
	/*
	执行一段sql语句
	*/
	string sqlExce(string sql);
	string ASCII2UTF_8(string& strAsciiCode);
	string Unicode2Utf8(const std::wstring& widestring);
	wstring Acsi2WideByte(string& strascii);
	string UTF_82ASCII(string& strUtf8Code);
	string WideByte2Acsi(wstring& wstrcode);
	wstring Utf82Unicode(const std::string& utf8string);
};
