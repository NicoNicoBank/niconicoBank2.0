#include "Staff.h"
#include "sqlite3.h"
#include "CppSQLite3.h"
#include "Func.h"
#include "md5.h"
#include <iostream>
using namespace std;
Staff::Staff()
{
	this->id = -1;
	this->jobNumber = "";
	this->name = "";
	this->password = "";
}

Staff::Staff(string name, string jobNumber, string password, int id)
{
	this->name = name;
	this->jobNumber = jobNumber;
	this->password = password;
	this->id = id;
}


Staff::~Staff()
{
}

bool Staff::readData(string query)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "select * from staff where " + query + " =  ";
	if (query == "id") {
		sql_temp += to_string(id);
		sql_temp += ";";
	}
	else if (query == "jobNumber") {
		sql_temp += "\"" + jobNumber + "\";";
	}
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	if (q.fieldValue(1) == NULL)
		this->jobNumber = "";
	else
		this->jobNumber = q.fieldValue(1);
	if (q.fieldValue(2) == NULL)
		this->password = "";
	else
		this->password = q.fieldValue(2);
	if (q.fieldValue(3) == NULL)
		this->name = "";
	else {
		string temp = q.fieldValue(3);
		this->name = func.UTF_82ASCII(temp);
	}
	db.close();
	return true;
}

bool Staff::save()
{
	Func func;
	string sql = "";
	bool flag = false;
	string err_msg;
	if (id != -1) {
		flag = true;
		sql = "update Staff set ";
		sql += "jobNumber = '" + this->jobNumber + "',";
		sql += "name = '" + func.ASCII2UTF_8(this->name) +"',";
		sql += "password = '" + this->password + "' ";
		sql += "where id = " + to_string(this->id) + ";";

	}
	else {
		sql = "insert into Staff (jobNumber, name, password) values ";
		sql += "('" + this->jobNumber + "','" + func.ASCII2UTF_8(this->name) + "','" + MD5(this->password).toStr() + "');";
	}
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	db.execDML(sql.c_str());
	db.close();
	return true;
}

bool Staff::verify()
{
	string enterJobNumber = this->jobNumber;
	string enterPassword = this->password;
	if (!readData("jobNumber")) {
		return false;
	}
	if (this->password == MD5(enterPassword).toStr()) {
		return true;
	}
	return false;
}

void Staff::setID(int id)
{
	this->id = id;
}

int Staff::getId() {
	return id;
}

void Staff::setId(int _id) {
	id = _id;
}

string Staff::getName() {
	return name;
}

void Staff::setName(string _name) {
	name = _name;
}

string Staff::getJobNumber() {
	return jobNumber;
}

void Staff::setJobNumber(string _jobNumber) {
	jobNumber = _jobNumber;
}

string Staff::getPwd()
{
	return string(this->password);
}

void Staff::setPwd(string pwd)
{
	this->password = pwd;
}

