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
	
	bool checkIdNumberFormat(string& IDNumber);
	bool checkIDNumber(string& IDNumber);
	/*
	传入身份证号，返回0，身份证长度不对；返回-1，身份证格式有误；返回1，身份证验证成功
	*/
	int judgeIdNumber(string& IDNumber);

	/*
	传入密码（字符串），返回Int型的密码强度（1-3）依次为（弱，中等，强）
	*/
	int judgePasswordStrength(string password);
	/*
	判断密码输入，通过返回true，否则返回false。只能包含字母，数字，及指定特殊字符 { '~', '!', '@',  '$', '%', '^', '&', '*', '(', ')' }
	*/
	bool checkPwd(string str);
	/*
	检测输入的字符串，通过返回true，否则返回false。不能包含指定字符 { ' ', '#', '-',  ';'}
	*/
	bool checkText(string str);
};
