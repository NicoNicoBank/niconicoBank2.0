#include "User.h"
#include "sqlite3.h"
#include "Func.h"
#include "CppSQLite3.h"
#include "md5.h"
User::User()
{
	this->account = "";
	this->address = "";
	this->id = -1;
	this->IDNumber = "";
	this->isLost = false;
	this->openDate = Date(0, 0, 0);
	this->lostDate = Date(0, 0, 0);
	this->password = "";
	this->userName = "";
}


User::~User()
{
}

User::User(string account, string userName, string password, string address, string IDNumber, Date openDate, bool isLost, Date lostDate, int id)
{
	this->id = id;
	this->account = account;
	this->userName = userName;
	this->password = password;
	this->address = address;
	this->IDNumber = IDNumber;
	this->openDate = openDate;
	this->isLost = isLost;
	this->lostDate = lostDate;
}

bool User::readData(string query)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "SELECT * From user where "; // id = " + to_string(id);
	if (query == "id") {
		sql_temp += "id = " + to_string(this->id) + ";"; 
	}
	if (query == "account") {
		sql_temp += "account = '" + this->account + "';";
	}
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	
	//acccount userName password address IDNumber 
	if (q.fieldValue(1) == NULL)
		this->account = "";
	else
		this->account = q.fieldValue(1);

	if (q.fieldValue(2) == NULL)
		this->userName = "";
	else {
		this->userName = q.fieldValue(2);
		this->userName = func.UTF_82ASCII(this->userName);
	}
	if (q.fieldValue(3) == NULL)
		this->password = "";
	else
		this->password = q.fieldValue(3);

	if (q.fieldValue(4) == NULL)
		this->address = "";
	else {
		this->address = q.fieldValue(4);
		this->address = func.UTF_82ASCII(this->address);
	}
	if (q.fieldValue(5) == NULL)
		this->IDNumber = "";
	else
		this->IDNumber = q.fieldValue(5);

	//openDate
	int year_t, day_t, month_t;
	if (q.fieldValue(6) == NULL)
		year_t = 0;
	else
		year_t = q.getIntField(6);
	if (q.fieldValue(7) == NULL)
		month_t = 0;
	else
		month_t = q.getIntField(7);

	if (q.fieldValue(8) == NULL)
		day_t = 0;
	else
		day_t = q.getIntField(8);

	this->openDate.setDate(year_t, month_t, day_t);

	
	if (q.fieldValue(9) == NULL)
		year_t = 0;
	else
		year_t = q.getIntField(9);
	if (q.fieldValue(10) == NULL)
		month_t = 0;
	else
		month_t = q.getIntField(10);

	if (q.fieldValue(11) == NULL)
		day_t = 0;
	else
		day_t = q.getIntField(11);

	this->lostDate.setDate(year_t, month_t, day_t);
	return true;
}

bool User::save()
{	
	Func func;
	string sql = "";
	bool flag = false;
	if ( this->id != -1 && this->account != "" && this->isExist(this->account)) {
		flag = true;
		//sql = "update user set account = ?,userName = ?,password = ?,address = ?,IDNumber = ?,openDate_year = ?,openDate_month = ?,openDate_day = ?,isLost = ?,lostDate_year = ?,lostDate_month = ?,lostDate_day = ? where id = ?;";
		sql = "update user set password = '" + MD5(this->password).toStr() + "' where account = '" + this->account + "';";
		func.sqlExce(sql);
		sql = "update user set address = '" + func.ASCII2UTF_8(this->address) + "' where account = '" + this->account + "';";
		func.sqlExce(sql);
		int temp = 0;
		if (this->isLost) temp = 1;
		sql = "update user set IDNumber = '" + to_string(temp) + "' where account = '" + this->account + "';";
		func.sqlExce(sql);

		sql = "update user set lostDate_year = " + to_string(this->lostDate.get(0));
		sql += ", lostDate_month = " + to_string(this->lostDate.get(1));
		sql += ", lostDate_day = " + to_string(this->lostDate.get(2));
		sql += " where account = '" + this->account + "';";
		func.sqlExce(sql);
	}
	else {
		//sql = "insert into user (account, userName, password, address, IDNumber, openDate_year,openDate_month, openDate_day, isLost, lostDate_year, lostDate_month, lostDate_day) values  (";
		sql = "insert into user (account) values (";
		sql += "'" + this->account + "');";
		func.sqlExce(sql);
		sql = "update user set userName = '" + func.ASCII2UTF_8(this->userName) + "' where account = '"+this->account+"';";
		func.sqlExce(sql);
		sql = "update user set password = '" + MD5(this->password).toStr() + "' where account = '" + this->account + "';";
		func.sqlExce(sql);
		sql = "update user set address = '" + func.ASCII2UTF_8(this->address) + "' where account = '" + this->account + "';";
		func.sqlExce(sql);
		sql = "update user set IDNumber = '" + this->IDNumber + "' where account = '" + this->account + "';";
		func.sqlExce(sql);
		sql = "update user set openDate_year = " + to_string(this->openDate.get(0));
		sql += ", openDate_month = " + to_string(this->openDate.get(1));
		sql += ", openDate_day = " + to_string(this->openDate.get(2));
		sql += " where account = '" + this->account + "';";
		func.sqlExce(sql);
		int temp = 0;
		if (this->isLost) temp = 1;
		sql = "update user set IDNumber = '" + to_string(temp) + "' where account = '" + this->account + "';";
		func.sqlExce(sql);

		sql = "update user set lostDate_year = " + to_string(this->lostDate.get(0));
		sql += ", lostDate_month = " + to_string(this->lostDate.get(1));
		sql += ", lostDate_day = " + to_string(this->lostDate.get(2));
		sql += " where account = '" + this->account + "';";
		func.sqlExce(sql);
		/*sql += "'" + this->userName + "',";
		sql += "'" + this->password + "',";
		sql += "'" + this->address + "',";
		sql += "'" + this->IDNumber + "',";
		sql += this->openDate.get(0) + ',';
		sql += this->openDate.get(1) + ',';
		sql += this->openDate.get(2) + ',';
		int temp = 0;
		if (isLost) temp = 1;
		sql += temp + ',';
		sql += this->lostDate.get(0) + ',';
		sql += this->lostDate.get(1) + ',';
		sql += this->lostDate.get(2) + ');';*/
	}
	
	////sqlite3_bind_blob(stat, 1, &(date), sizeof(this->openDate), NULL);
	////sqlite3_bind_int(stmt, 1, id);
	//string tempStr[] = { this->account, this->userName, this->password, this->address, this->IDNumber };
	//int tempInt[] = { openDate.get(0), openDate.get(1), openDate.get(2), isLost, lostDate.get(0), lostDate.get(1), lostDate.get(2) };
	//
	//sqlite3 * conn;
	//if (sqlite3_open("d:\\c++ study\\nicobank\\niconicobank\\niconicobank\\database\\bank.db", &conn) != SQLITE_OK) {
	//	return false;
	//}
	//sqlite3_stmt * stmt = NULL;
	////sql语句准备
	////string sql = "insert into user (account, userName, password, address, IDNumber, openDate_year,openDate_month, openDate_day, isLost, lostDate_year, lostDate_month, lostDate_day) values  (?,?,?,?,?,?,?,?,?,?,?,?);";
	////(id, account, username, password, address, idnumber, opendate_year,opendate_month, opendate_day, islost, lostdate_year, lostdate_month, lostdate_day)
	////填入相关数据
	//sqlite3_prepare_v2(conn, sql.c_str(), -1, &stmt, 0);
	//for (int i = 1; i <= 5; i++) {
	//	sqlite3_bind_text(stmt, i, tempStr[i - 1].c_str(), -1, NULL);
	//}
	//for (int i = 6; i <= 12; i++) {
	//	sqlite3_bind_int(stmt, i, tempInt[i - 6]);
	//}
	//if (flag) {
	//	sqlite3_bind_int(stmt, 13, id);
	//}
	////执行
	//int result = sqlite3_step(stmt);
	//sqlite3_finalize(stmt);
	return true;
}

bool User::verify(string account, string pwd)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "select * from user where account =  '"+account+"';";
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	if (q.getIntField(9) == 1) return false;
	if (q.fieldValue(3) == NULL) return false;
	if (MD5(pwd).toStr() == q.fieldValue(3)) {
		this->account = account;
		this->readData("account");
		return true;
	}
	else
		return false;
}

bool User::isExist(string account)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "select * from user where account =  '" + account + "';";
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	if (q.eof()) {
		return false;
	}
	else return true;
}

void User::initDate()
{
	this->openDate = Date(0, 0, 0);
	this->isLost = false;
	this->lostDate = Date(0, 0, 0);
}

void User::print(string account)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "SELECT * From Deposit where userAccount = '" + account + "';";
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	int counter = 1;
	cout << "工单号\t存款种类\t本金\t存入时间" << endl;
	while (!q.eof()) {
		int type = q.getIntField(2);
		cout << q.getIntField(0) <<"\t" << type << "月\t\t";
		cout << q.getIntField(3) << "\t";
		cout << q.getIntField(4) << "." << q.getIntField(5) << "." <<q.getIntField(6) << endl;
		q.nextRow();
	}
	q.finalize();
	db.close();
}

void User::setLost(string account,const Date & now)
{
	Func func;
	string sql = "update user set isLost = 1, lostDate_year = " + to_string(now.get(0)) +", lostDate_month = " + to_string(now.get(1)) + ", lostDate_day = " + to_string(now.get(2)) + " where account = '" + account + "';";
	func.sqlExce(sql);
}

bool User::userDepositDetail(string account, vector<int>& id, vector<int>& type, vector<double>& principal, vector<Date>& date)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "SELECT * From Deposit where userAccount = '" + account + "';";
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	//先清空
	id.clear();
	type.clear();
	principal.clear();
	date.clear();
	while (!q.eof()) {

		type.push_back(q.getIntField(2));
		id.push_back(q.getIntField(0));
		principal.push_back(q.getFloatField(3));
		date.push_back(Date(q.getIntField(4), q.getIntField(5), q.getIntField(6)));
		q.nextRow();
	}
	return true;
}

bool User::userWithDrawDetail(string account, vector<Date>& date, vector<double>& money, vector<string> & staffAccount, vector <int> & depositID)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "SELECT * From WithDraw where userAccount = '" + account + "';";
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	while (!q.eof()) {
		date.push_back(Date(q.getIntField(2), q.getIntField(3), q.getIntField(4)));
		money.push_back(q.getFloatField(5));
		staffAccount.push_back(q.getStringField(6));
		depositID.push_back(q.getIntField(7));
		q.nextRow();
	}
	return true;
}

void User::cancelLost(string account)
{
	Func func;
	string sql = "update user set isLost = 0 where account = '" + account + "';";
	func.sqlExce(sql);
}

void User::changePwd(string account, string newPwd)
{
	Func func;
	string sql = "update user set password = '" + MD5(newPwd).toStr() + "' where account = '" + account + "';";
	func.sqlExce(sql);
}

void User::changeAddress(string account, string address)
{
	Func func;
	string sql = "update user set address = '" + address + "' where account = '" + account + "';";
	func.sqlExce(sql);
}

string User::getIDNumberFromDatabase(string account)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "SELECT IDNumber From user where account = '" + account + "';";
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	string IDNumber = q.getStringField(0);
	q.finalize();
	db.close();
	return IDNumber;
}

int User::getId()
{
	return 0;
}

void User::setId(int _id)
{
	this->id = id;
}

string User::getAccount() {
	return account;
}

void User::setAccount(string _account) {
	account = _account;
}

string User::getUserName() {
	return userName;
}

void User::setUserName(string _userName) {
	userName = _userName;
}

string User::getPassword() {
	return password;
}

void User::setPassword(string _password) {
	password = _password;
}

string User::getAddress() {
	return address;
}

void User::setAddress(string _address) {
	address = _address;
}

string User::getIDNumber() {
	return IDNumber;
}

void User::setIDNumber(string _IDNumber) {
	IDNumber = _IDNumber;
}

Date User::getOpenDate() {
	return openDate;
}

void User::setOpenDate(Date _openDate) {
	openDate = _openDate;
}

Date User::getLostDate() {
	return lostDate;
}

void User::setLostDate(Date _lostDate) {
	lostDate = _lostDate;
}

bool User::getIsLost() {
	return isLost;
}

void User::setIsLost(bool _isLost) {
	isLost = _isLost;
}
