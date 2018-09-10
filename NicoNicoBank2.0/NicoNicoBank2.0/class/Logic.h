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
	bool saveMoney(string account, int type, double principal, const Date & now);
	/*
	取款,若返回值:
	0: 取款成功
	1: 则说明无法取款，定期已经取过一次;
	2: 金额超过存款数 或 金额小于0
	3: 无法取全额，未到期
	*/
	int drawMoney(string account, int id, double money, double & profit, const Date & now);
	/*
	注册储蓄员
	*/
	bool signInStaff(string account, string pwd, string name);
	/*
	获取即将到期的存款,传入参数为当前日期
	*/
	double getMoneyNeed(const Date & now);
	/*
	获取所有当前存款本金和
	*/
	double getAllPrincipal();
	/*
	挂失某一账户, 输入账户密码，检测其正确性，以便于挂失
	*/
	bool setAccountLost(string account, string pwd, const Date & now);
	/*
	修改地址
	*/
	bool setAccountAddress(string account, string address);
	/*
	修改密码
	参数为账户， 旧密码， 新密码，二次输入新密码
	*/
	bool setAccountPwd(string account, string oldPwd, string newPwd, string newPwd2);
	/*
	获取用户账户信息， IDNumber 
	*/
	bool getIDNumber(string account, string & IDNumber);
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

	/*
	通用检测，对所有值进行检测
	*/
	bool checkAllString(vector <string> & strs);

	/*
	计算当前可获得利息
	*/
	double countProfit(Date & now, int id);
};

