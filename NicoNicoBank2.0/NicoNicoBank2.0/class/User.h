#pragma once
#include <string>
#include <cstring>
#include "Date.h"
#include <windows.h>
#include <vector>
using namespace std;
class User
{
public:
	User();
	~User();
	/*
	初始化user
	*/
	User(string account, string userName, string password, string address, string IDNumber, Date openDate, bool isLost, Date lostDate, int id = -1);
	/*
	根据当前id值读取所有该id值下的user表中的数据
	*/
	bool readData(string query);
	/*
	将当前类中数据写入数据库, id存在则为更新，id为-1则表示更新
	*/
	bool save();
	/*
	检验当前账户正确性
	*/
	bool verify(string account, string pwd);
	/*
	检验是否存在该账户
	*/
	bool isExist(string account);
	/*
	初始化两个日期信息
	*/
	void initDate();
	/*
	输出当前账户存款信息
	*/
	void print(string account);
	/*
	账户挂失函数，对指定账户进行挂失
	*/
	void setLost(string account, const Date & now);
	/*
	取消挂失函数，对指定账户设置为未挂失状态
	*/
	/*
	获取当前存款信息
	*/
	bool userDepositDetail(string account, vector <int> & id, vector <int> & type, vector <double> & principal, vector <Date> & date);
	/*
	获取取款清单
	*/
	bool userWithDrawDetail(string account, vector <Date> & date, vector <double>& money);
	/*
	取消挂失
	*/
	void cancelLost(string account);
	int getId();
	void setId(int _id);

	string getAccount();
	void setAccount(string _account);

	string getUserName();
	void setUserName(string _userName);

	string getPassword();
	void setPassword(string _password);

	string getAddress();
	void setAddress(string _address);

	string getIDNumber();
	void setIDNumber(string _IDNumber);

	Date getOpenDate();
	void setOpenDate(Date _openDate);

	Date getLostDate();
	void setLostDate(Date _lostDate);

	bool getIsLost();
	void setIsLost(bool _isLost);

private:
	int id;  //唯一标识
	string account; // 账号
	string userName;  // 姓名
	string password; // 密码
	string address;// 地址
	string IDNumber;// 身份证号码
	Date openDate;// 开户日期
	bool isLost;// 是否挂失
	Date lostDate;// 挂失日期

};

