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
	Staff staff("", account, pwd);
	if (staff.verify()) return true;
	return false;
}

bool Logic::verifyUser(string account, string pwd)
{
	User user;
	if (user.verify(account, pwd)) return true;
	return false;
}

bool Logic::signInUser(string userName, string password, string address, string IDNumber,const Date & now, map<string, string>& result)
{
	Func func;
	User user;
	user.setId(-1);
	string account = "";
	while (1) {
		account = func.getRandomstring(5);
		if (!user.isExist(account)) break;
	}
	result["account"] = account;
	user.setAccount(account);
	user.setPassword(password);
	user.setAddress(address);
	user.setIDNumber(IDNumber);
	user.setUserName(userName);
	user.initDate();
	user.setOpenDate(now);
	user.save();
	return true;
}

bool Logic::userDepositDetail(string account, vector<int>& id, vector<int>& type, vector<double>& principal, vector<Date>& date)
{
	User user;
	if (user.userDepositDetail(account, id, type, principal, date)) return true;
	return false;
}



bool Logic::userWithDrawDetail(string account, vector<Date>& date, vector<double>& money)
{
	User user;
	user.userWithDrawDetail(account, date, money);
	return true;
}

bool Logic::saveMoney(string account, int type, double principal, const Date & now)
{
	Deposit deposit(account, type, principal, now);
	deposit.save();
	return true;
}

int Logic::drawMoney(string account, int id, double money, double & profit, const Date & now)
{
	Deposit deposit;
	deposit.setID(id);
	int result = deposit.drawMoney(account, money, now);
	profit = deposit.countProfit(now);
	return result;
}

bool Logic::signInStaff(string account, string pwd, string name)
{
	Staff staff(account, pwd, name);
	staff.save();
	return true;
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

bool Logic::setAccountLost(string account, string pwd, const Date & now)
{
	if (verifyUser(account, pwd)) {
		User user;
		user.setLost(account, now);
		return true;
	}
	return false;
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

