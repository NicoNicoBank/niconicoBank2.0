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

Deposit::Deposit(string userAccount, int type, double principal, Date date, string staffAccount)
{
	this->id = 0;
	this->userAccount = userAccount;
	this->type = type;
	this->principal = principal;
	this->date = date;
	this->takeTimes = 0;
	this->staffAccount = staffAccount;
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
		string sql = "insert into Deposit (userAccount, type, principal, year, month, day, takeTimes, takeYear, takeMonth, takeDay, staffAccount) values (";
		sql += "'" + this->userAccount + "',";
		sql += to_string(this->type) + ",";
		sql += to_string(this->principal) + ",";
		sql += to_string(this->date.get(0)) + ",";
		sql += to_string(this->date.get(1)) + ",";
		sql += to_string(this->date.get(2)) + ",";
		sql += to_string(this->takeTimes) + ",";
		sql += to_string(end.get(0)) + ",";
		sql += to_string(end.get(1)) + ",";
		sql += to_string(end.get(2)) + ",";
		sql += staffAccount + ");";
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
/*
	取款,若返回值:
	0: 取款成功
	1: 则说明无法取款，定期已经取过一次;
	2: 金额超过存款数 或 金额小于0
	3: 无法取全额，未到期
*/
int Deposit::drawMoney(string account, double money,const Date & now, string staffAccount, double & profit,string & saveDate, int & type)
{
	//用户名， 取款，取款日期, 利息，存入时间，存款类型
	//初始化
	Func func;
	this->readData();
	Date now_t(now);
	string sql = "";
	if (this->type == 0) { //活期
		//记录数据
		sql = "insert into WithDraw (userAccount, year, month, day, money, staffAccount, depositID) values ('" + account + "'," + to_string(now.get(0)) + "," + to_string(now.get(1)) + "," + to_string(now.get(2)) + "," + to_string(money) + ",'" + staffAccount + "'," + to_string(id) + ");";
		func.sqlExce(sql);
		//传出信息
		type = this->type;
		profit = countProfit(money, this->type, date, now);
		saveDate = to_string(date.get(0)) + "-" + to_string(date.get(1)) + "-" + to_string(date.get(2));
		//全取删除该笔单款
		if (money == principal) { //是否全部取走
			sql = "delete from Deposit where id = " + to_string(id) + ";";
			func.sqlExce(sql);
		}
		else {
			principal -= money;
			sql = "update Deposit set principal = " + to_string(principal) + " where id = " + to_string(id) + ";";
			func.sqlExce(sql);
		}
		return 0;
	}
	else { //定期
		Date takeDate(date);
		takeDate.addMonth(this->type);
		if (takeDate > now) {//到期
			//记录数据
			sql = "insert into WithDraw (userAccount, year, month, day, money, staffAccount, depositID) values ('" + account + "'," + to_string(now.get(0)) + "," + to_string(now.get(1)) + "," + to_string(now.get(2)) + "," + to_string(money) + ",'" + staffAccount + "'," + to_string(id) + ");";
			func.sqlExce(sql);
			//传出数据
			type = this->type;
			profit = countProfit(money, this->type, date, now);
			saveDate = to_string(date.get(0)) + "-" + to_string(date.get(1)) + "-" + to_string(date.get(2));
			if (money == principal) {
				sql = "delete from Deposit where id = " + to_string(id) + ";";
				func.sqlExce(sql);
			}
			else {
				principal -= money;
				sql = "update Deposit set principal = " + to_string(principal) + " where id = " + to_string(id) + ";";
				func.sqlExce(sql);
			}
		}
		else { //未到期
			if (takeTimes == 1) { //已取过
				return 1;
			}
			else {
				if (money == principal) { //定期无法全额
					return 3;
				}
				else {
					sql = "insert into WithDraw (userAccount, year, month, day, money, staffAccount, depositID) values ('" + account + "'," + to_string(now.get(0)) + "," + to_string(now.get(1)) + "," + to_string(now.get(2)) + "," + to_string(money) + ",'" + staffAccount + "," + to_string(id) + "');";
					func.sqlExce(sql);
					principal -= money;
					sql = "update Deposit set principal = " + to_string(principal) + ", takeTimes = 1 where id = " + to_string(id) + ";";
					func.sqlExce(sql);
				}
			}
		}
	}
	/*if (money > principal || money < 0) {
		return 2;
	}
	else if (money == this->principal) {
		Date takeDate(date);
		takeDate.addMonth(type);
		if (takeDate > now || this->type == 0) {
			string sql = "insert into WithDraw (userAccount, year, month, day, money, staffAccount, depositID) values ('" + account + "'," + to_string(now.get(0)) + "," + to_string(now.get(1)) + "," + to_string(now.get(2)) + "," + to_string(money) + ",'" + staffAccount + "," + to_string(id) +"');";
			func.sqlExce(sql);
			sql = "delete from Deposit where id = " + to_string(id) + ";";
			func.sqlExce(sql);
			return 0;
		}
		else {
			return 3;
		}
	}
	else if (checkCanBeTake()) {
		string sql = "insert into WithDraw (userAccount, year, month, day, money) values ('"+ account+ "'," + to_string(now.get(0)) + "," + to_string(now.get(1)) + "," + to_string(now.get(2)) + "," + to_string(money) + ");";
		func.sqlExce(sql);
		this->principal -= money;
		this->save();
		return 0;
	}
	else
		return 1;*/
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

double Deposit::countProfit(double principal, int type, Date date, Date now)
{
	//修改为取款时间
	date.addMonth(type);
	if (type == 0) { //活期
		return principal * (now - date) * (profitRate[0] / 360);
	}
	else { // 定期
		if (now > date) { //到期
			double ans = principal * (profitRate[type] / 360) * 30 * type;
			principal += ans;
			ans += principal * (now - date) * (profitRate[0] / 360);
			return ans;
		}
		else {
			return principal * (now - date) * (profitRate[0] / 360);
		}
	}
	/*double profit_t = profitRate[this->type];
	profit_t = (profit_t / 360) * 30 * this->type;
	Date now_t(now);
	Date takeDate(date);
	takeDate.addMonth(type);
	this->principal = profit_t * this->principal;

	int days = takeDate - now_t;
	profit_t = (profitRate[0] / 360) * days;

	if (type == 0 || now_t > takeDate)
		return profit_t * this->principal;
	else {
		takeDate = date;
		days = now_t - takeDate;
		profit_t = (profitRate[0] / 360) * days;
		return profit_t * money;
	}*/
}

double Deposit::getAllPrincipal()
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql = "select principal from Deposit;";
	CppSQLite3Query q = db.execQuery(sql.c_str());
	double sum = 0;
	while (!q.eof()) {
		sum += q.getFloatField(0);
		q.nextRow();
	}
	q.finalize();
	db.close();
	return sum;
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


