#include "Deposit.h"
#include "CppSQLite3.h"
#include "Func.h"
double profitRate[] = {
	0.0035,
	0, 0, 0.011,
	0, 0, 0.013,
	0, 0, 0,
	0, 0, 0.015,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0.021,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0.0275,
};

Deposit::Deposit()
{
	this->id = 0;
	this->userAccount = "";
	this->type = 0;
	this->principal = 0;
	this->date = 0;
	this->takeTimes = 0;
}

Deposit::Deposit(string userAccount, int type, double principal, Date date)
{
	this->id = 0;
	this->userAccount = userAccount;
	this->type = type;
	this->principal = principal;
	this->date = date;
	this->takeTimes = 0;
}

Deposit::Deposit(int id)
{
	this->id = 0;
	this->userAccount = "";
	this->type = 0;
	this->principal = 0;
	this->date = Date(0,0,0);
	this->takeTimes = 0;
}


Deposit::~Deposit()
{
}

bool Deposit::save()
{
	Func func;
	if (this->isExist(this->id)) {
		string sql = "update Deposit set principal = " + to_string(this->principal) + ",takeTimes = "+ to_string(this->takeTimes)+ " where id =" + to_string(this->id) + ';';
		func.sqlExce(sql);
	}
	else {
		Date end(this->date);
		end.addMonth(this->type);
		string sql = "insert into Deposit (userAccount, type, principal, year, month, day, takeTimes, takeYear, takeMonth, takeDay) values (";
		sql += "'" + this->userAccount + "',";
		sql += to_string(this->type) + ",";
		sql += to_string(this->principal) + ",";
		sql += to_string(this->date.get(0)) + ",";
		sql += to_string(this->date.get(1)) + ",";
		sql += to_string(this->date.get(2)) + ",";
		sql += to_string(this->takeTimes) + ",";
		sql += to_string(end.get(0)) + ",";
		sql += to_string(end.get(1)) + ",";
		sql += to_string(end.get(2)) + ");";
		func.sqlExce(sql);
	}
	return false;
}

bool Deposit::readData()
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());

	string sql = "select * from Deposit where id = " + to_string(this->id) + ';';
	CppSQLite3Query q = db.execQuery(sql.c_str());
	this->userAccount = q.getStringField(1);
	this->type = q.getIntField(2);
	this->principal = q.getFloatField(3);
	int year, month, day;
	year = q.getIntField(4);
	month = q.getIntField(5);
	day = q.getIntField(6);
	this->date.setDate(year, month, day);
	this->takeTimes = q.getIntField(7);
	q.finalize();
	db.close();
	return false;
}

bool Deposit::isExist(int id)
{
	Func func;
	string sql = "select * from Deposit where id = " + to_string(id) + ';';
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	CppSQLite3Query q = db.execQuery(sql.c_str());
	if (q.eof()) return false;
	return true;
}

bool Deposit::checkCanBeTake()
{
	if (this->type == 0) {
		return true;
	}
	if(this->takeTimes == 1)
		return false;
	else return true;
}

int Deposit::drawMoney(string account, double money,const Date & now)
{
	Func func;
	this->readData();
	if (money > principal || money < 0) {
		return 2;
	}
	if (money == this->principal) {
		if (this->date > now || this->type == 0) {
			string sql = "insert into WithDraw (userAccount, year, month, day, money) values ('" + account + "'," + to_string(now.get(0)) + "," + to_string(now.get(1)) + "," + to_string(now.get(2)) + "," + to_string(money) + ");";
			func.sqlExce(sql);
			sql = "delete from Deposit where id = " + to_string(id) + ";";
			func.sqlExce(sql);
			return 0;
		}
		else {
			return 3;
		}
	}
	if (checkCanBeTake()) {
		string sql = "insert into WithDraw (userAccount, year, month, day, money) values ('"+ account+ "'," + to_string(now.get(0)) + "," + to_string(now.get(1)) + "," + to_string(now.get(2)) + "," + to_string(money) + ");";
		func.sqlExce(sql);
		this->principal -= money;
		this->save();
		return 0;
	}
	else
		return 1;
}

double Deposit::getRecentEndDepoist(Date now)
{
	Func func;
	string sql = "";
	double sum = 0;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	//先获取全部定期即将到期的，三天内的
	for (int i = 0; i < 3; i++) {
		now = now + i;
		sql = "select * from Deposit where takeYear = " + to_string(now.get(0)) + " and takeMonth = " + to_string(now.get(1)) + " and takeDay = " + to_string(now.get(2)) + " and type != 0;";
		CppSQLite3Query q = db.execQuery(sql.c_str());
		while (!q.eof()) {
			sum += q.getFloatField(3);
			q.nextRow();
		}
		q.finalize();
	}
	//查询全部活期的
	sql = "select * from Deposit where type = 0;";
	CppSQLite3Query q = db.execQuery(sql.c_str());
	while (!q.eof()) {
		sum += q.getFloatField(3);
		q.nextRow();
	}
	q.finalize();
	db.close();
	return sum;
}

int Deposit::settlement(Date now)
{
	now++;
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql = "select * from Deposit where takeYear = " + to_string(now.get(0)) + " and takeMonth = " + to_string(now.get(1)) + " and takeDay = " + to_string(now.get(2)) + ";";
	CppSQLite3Query q = db.execQuery(sql.c_str());
	while (!q.eof()) {
		string sql_t = "insert into Deposit (userAccount, type, principal, year, month, day) values (";
		sql_t += q.getStringField(1) +',';
		sql_t += "0,";
		sql_t += to_string(q.getIntField(2)) + ',';
		sql_t += to_string(now.get(0)) + ',';
		sql_t += to_string(now.get(1)) + ',';
		sql_t += to_string(now.get(2)) + ");";
		func.sqlExce(sql_t);
		q.nextRow();
	}
	db.close();
	return 0;
}

double Deposit::countProfit()
{
	double profit_t = profitRate[this->type];
	profit_t = (profit_t / 360) * 30 * this->type;
	return profit_t * this->principal;
}

void Deposit::setProfit(int type, double profit)
{
	profitRate[type] = profit;
}

int Deposit::getID()
{
	return id;
}

void Deposit::setID(int id)
{
	this->id = id;
}

string Deposit::getUserAccount() {
	return userAccount;
}

void Deposit::setUserAccount(int _userAccount) {
	userAccount = _userAccount;
}

int Deposit::getType() {
	return type;
}

void Deposit::setType(int _type) {
	type = _type;
}

double Deposit::getPrincipal() {
	return principal;
}

void Deposit::setPrincipal(double _principle) {
	principal = _principle;
}

Date Deposit::getDate() {
	return date;
}

void Deposit::setDate(Date _date) {
	date = _date;
}

int Deposit::getTakeTimes()
{
	return this->takeTimes;
}

void Deposit::setTakeTimes(int takeTimes)
{
	this->takeTimes = takeTimes;
}


