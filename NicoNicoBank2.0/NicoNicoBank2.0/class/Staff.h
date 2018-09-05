#pragma once
#include <string>
using namespace std;
//储蓄员
class Staff
{
public:
	Staff();
	Staff(string name, string jobNumber, string password, int id = -1);
	~Staff();
	bool readData(string query="id");
	/*
	保存已存入类中数据
	*/
	bool save();
	/*
	验证正确返回true, 验证错误返回false,并且errorMessge为""
	数据库错误返回false, erroMessage;
	*/
	bool verify();

	string getName();
	void setID(int id);
	int getId();
	void setId(int _id);
	void setName(string _name);
	string getJobNumber();
	void setJobNumber(string _jobNumber);
	string getPwd();
	void setPwd(string pwd);
private:
	int id;
	string name; //姓名
	string jobNumber; // 工号
	string password; //staff密码
};

