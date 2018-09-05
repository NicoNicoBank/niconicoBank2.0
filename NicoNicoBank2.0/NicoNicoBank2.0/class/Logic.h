#pragma once
#include <string>
#include <map>
#include "Date.h"
#include <vector>
using namespace std;
class Logic
{
public:
	Logic();
	~Logic();
	/*
	检验储蓄员登入情况，成功返回true;
	*/
	bool verifyStaff(string account, string pwd);
	/*
	检验用户登入情况，成功返回true;
	*/
	bool verifyUser(string account, string pwd);
	/*
	开设新的账户，
	map中有两个可用字段，account ->生成的用户账户  error -> 错误信息
	*/
	bool signInUser(string userName, string password, string address, string IDNumber,const Date & now, map <string, string> & result);
	/*
	获取用户存款信息清单
	*/
	bool userDepositDetail(string account, vector <int> & id, vector <int> & type, vector <double> & principal, vector <Date> & date);
	/*
	获取用户取款信息清单
	*/
	bool userWithDrawDetail(string account, vector <Date> & date, vector <double>& money);
	/*
	存款,返回值为是否存款成功
	*/
	bool saveMoney(string account, int type, int principal, const Date & now);
	/*
	取款
	*/
	bool drawMoney(string account, int id, double money, string & error, const Date & now);
	/*
	注册储蓄员
	*/
	bool signInStaff(string account, string pwd, string name);
	/*
	获取即将到期的存款,传入参数为当前日期
	*/
	double getMoneyNeed(const Date & now);
};

