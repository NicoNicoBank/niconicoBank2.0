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
	���鴢��Ա����������ɹ�����true;
	*/
	bool verifyStaff(string account, string pwd);
	/*
	�����û�����������ɹ�����true;
	*/
	bool verifyUser(string account, string pwd);
	/*
	�����µ��˻���
	map�������������ֶΣ�account ->���ɵ��û��˻�  error -> ������Ϣ
	*/
	bool signInUser(string userName, string password, string address, string IDNumber,const Date & now, map <string, string> & result);
	/*
	��ȡ�û������Ϣ�嵥
	*/
	bool userDepositDetail(string account, vector <int> & id, vector <int> & type, vector <double> & principal, vector <Date> & date);
	/*
	��ȡ�û�ȡ����Ϣ�嵥
	*/
	bool userWithDrawDetail(string account, vector <Date> & date, vector <double>& money);
	/*
	���,����ֵΪ�Ƿ���ɹ�
	*/
	bool saveMoney(string account, int type, double principal, const Date & now);
	/*
	ȡ��,������ֵ:
	0: ȡ��ɹ�
	1: ��˵���޷�ȡ������Ѿ�ȡ��һ��;
	2: ��������� �� ���С��0
	3: �޷�ȡȫ�δ����
	*/
	int drawMoney(string account, int id, double money, double & profit, const Date & now);
	/*
	ע�ᴢ��Ա
	*/
	bool signInStaff(string account, string pwd, string name);
	/*
	��ȡ�������ڵĴ��,�������Ϊ��ǰ����
	*/
	double getMoneyNeed(const Date & now);
	/*
	��ȡ���е�ǰ�����
	*/
	double getAllPrincipal();
};

