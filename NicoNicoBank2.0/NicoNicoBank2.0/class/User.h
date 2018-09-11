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
	��ʼ��user
	*/
	User(string account, string userName, string password, string address, string IDNumber, Date openDate, bool isLost, Date lostDate, int id = -1);
	/*
	���ݵ�ǰidֵ��ȡ���и�idֵ�µ�user���е�����
	*/
	bool readData(string query);
	/*
	����ǰ��������д�����ݿ�, id������Ϊ���£�idΪ-1���ʾ����
	*/
	bool save();
	/*
	���鵱ǰ�˻���ȷ��
	*/
	bool verify(string account, string pwd);
	/*
	�����Ƿ���ڸ��˻�
	*/
	bool isExist(string account);
	/*
	��ʼ������������Ϣ
	*/
	void initDate();
	/*
	�����ǰ�˻������Ϣ
	*/
	void print(string account);
	/*
	�˻���ʧ��������ָ���˻����й�ʧ
	*/
	void setLost(string account, string newAccount, string pwd, const Date & now);
	/*
	ȡ����ʧ��������ָ���˻�����Ϊδ��ʧ״̬
	*/
	/*
	��ȡ��ǰ�����Ϣ
	*/
	bool userDepositDetail(string account, vector <int> & id, vector <int> & type, vector <double> & principal, vector <Date> & date);
	/*
	��ȡȡ���嵥
	*/
	bool userWithDrawDetail(string account, vector <Date> & date, vector <double>& money, vector<string> & staffAccount, vector <int> & depositID);
	/*
	ȡ����ʧ
	*/
	void cancelLost(string account);
	/*
	�޸�����
	*/
	void changePwd(string account, string newPwd);
	/*
	�޸ĵ�ַ
	*/
	void changeAddress(string account, string address);
	/*	
	�����ݿ�ֱ�ӻ�ȡ���֤��
	*/
	string getIDNumberFromDatabase(string account);

	/*
	��ȡ�û���Ϣ�б�
	*/
	int getAccountInfo(string vagueAccount, vector<string> & account, vector<string> & userName, vector<string> & address, vector<string> & IDNumber, vector<string> & openDate);

	/*
	ע�����û�
	*/
	int signInUser(string account, string userName, string password, string address, string IDNumber, const Date & now, string staffAccount);
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
	int id;  //Ψһ��ʶ
	string account; // �˺�
	string userName;  // ����
	string password; // ����
	string address;// ��ַ
	string IDNumber;// ���֤����
	Date openDate;// ��������
	bool isLost;// �Ƿ��ʧ
	Date lostDate;// ��ʧ����

};

