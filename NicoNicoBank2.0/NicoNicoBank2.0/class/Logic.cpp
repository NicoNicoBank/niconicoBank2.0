#include "Logic.h"
#include "Staff.h"
#include "User.h"
#include "Func.h"
#include "Deposit.h"

Logic::Logic()
{
}


Logic::~Logic()
{
}

bool Logic::verifyStaff(string account, string pwd)
{
	Staff staff(account, pwd, "");
	if (staff.verify()) return true;
	return false;
}

bool Logic::verifyUser(string account, string pwd)
{
	User user;
	if (user.verify(account, pwd)) return true;
	return false;
}

bool Logic::signInUser(string & account, string userName, string password, string address, string IDNumber,const Date & now, string staffAccount)
{
	Func func;
	User user;
	user.setId(-1);
	while (1) {
		account = func.getRandomstring(5);
		if (!user.isExist(account)) break;
	}
	user.signInUser(account, userName, password, address, IDNumber, now, staffAccount);
	return true;
}

bool Logic::userDepositDetail(string account, vector<int>& id, vector<int>& type, vector<double>& principal, vector<Date>& date)
{
	User user;
	if (user.userDepositDetail(account, id, type, principal, date)) return true;
	return false;
}



bool Logic::userWithDrawDetail(string account, vector<Date>& date, vector<double>& money, vector<string> & staffAccount, vector <int> & depositID)
{
	User user;
	user.userWithDrawDetail(account, date, money,  staffAccount, depositID);
	return true;
}

bool Logic::saveMoney(string account, int type, double principal, const Date & now, string staffAccount)
{
	Deposit deposit(account, type, principal, now, staffAccount);
	deposit.save();
	return true;
}

int Logic::drawMoney(string account, int id, double money, const Date & now, string staffAccount, double & profit, string & saveDate, int & type)
{
	//用户名， 取款，取款日期, 利息，存入时间，存款类型
	Deposit deposit;
	deposit.setID(id);
	int result = deposit.drawMoney(account, money, now, staffAccount, profit, saveDate, type);
	return result;
}

bool Logic::signInStaff(string account, string pwd, string name)
{
	Staff staff(account, pwd, name);
	if (staff.save())return true;
	return false;
}

double Logic::getMoneyNeed(const Date & now)
{
	Deposit deposit;
	return deposit.getRecentEndDepoist(now);
}

double Logic::getAllPrincipal()
{
	Deposit deposit;
	return deposit.getAllPrincipal();
}

bool Logic::setAccountLost(string account, string newAccount, string pwd, const Date & now)
{
	User user;
	user.setLost(account, newAccount, pwd, now);
	return true;
}

bool Logic::setAccountAddress(string account, string address)
{
	User user;
	user.changeAddress(account, address);
	return true;
}

bool Logic::setAccountPwd(string account, string oldPwd, string newPwd, string newPwd2)
{
	if (verifyUser(account, oldPwd) && newPwd == newPwd2) {
		User user;
		user.changePwd(account, newPwd);
		return true;
	}
	return false;
}

bool Logic::getIDNumber(string account, string & IDNumber)
{
	User user;
	IDNumber = user.getIDNumberFromDatabase(account);
	return true;
}

int Logic::judgeIdNumber(string & IDNumber)
{
	Func func;
	return func.judgeIdNumber(IDNumber);
}

int Logic::judgePasswordStrength(string password)
{
	Func func;
	return func.judgePasswordStrength(password);
}

bool Logic::checkPwd(string str)
{
	Func func;
	return func.checkPwd(str);
}

bool Logic::checkText(string str)
{
	Func func;
	return func.checkText(str);
}

bool Logic::checkAllString(vector<string> &strs)
{
	bool flag = true;
	int size = strs.size();
	for (int i = 0; i < size; i++) {
		string & str = strs[i];
		if (str.length() <= 0 || str.length() > 100 || !checkText(str)){
			flag = false;
			break;
		}
	}
	return flag;
}

double Logic::countProfit(double principal, int type, const Date & date, const Date & now)
{
	Deposit deposit;
	return deposit.countProfit(principal, type, date, now);
}

string Logic::getRandomAccount()
{
	Func func;
	return func.getRandomstring(5);
}

int Logic::getAccountInfo(string searchText, vector<string> & account, vector<string> & userName, vector<string> & address, vector<string> & IDNumber, vector<string> & openDate, vector <string> & staffAccount, int select)
{
	// 0. 账户名 1.用户姓名 2.地址 3.身份证号 4.开户人员工号
	User user;
	user.getAccountInfo(searchText, account, userName, address, IDNumber, openDate, staffAccount, select);
	return 1;
}

bool Logic::isProcessExist() {
	Func func;
	return func.isProcessExist();
}
