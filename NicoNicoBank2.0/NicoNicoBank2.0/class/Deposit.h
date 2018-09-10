#pragma once
#include <string>
#include "Date.h"
#include <map>
using namespace std;

class Deposit
{
public:
	Deposit();
	Deposit(string userAccount, int type, double principal, Date date, string staffAccount);
	Deposit(int id);
	virtual ~Deposit();

	/*
	���������ݽ��б��棬����id���ڵ��Ӵ��ڣ���������±���
	*/
	bool save();
	/*
	���ݵ�ǰ����id��ѯ���ӣ������������
	*/
	bool readData();
	/*
	��ѯ�Ƿ��д���idֵ�ĵ��Ӵ���
	*/
	bool isExist(int id);
	/*
	�����˻��Ƿ����ȡ��, ִ��ǰӦ�ȶ�ȡ,������Ƿ���
	*/
	bool checkCanBeTake();
	/*
	ȡ��,������ֵ:
	0: ȡ��ɹ�
	1: ��˵���޷�ȡ������Ѿ�ȡ��һ��;
	2: ��������� �� ���С��0
	3: �޷�ȡȫ�δ����
	*/
	int drawMoney(string account, double money, const Date & now, string staffAccount, double & profit, string & saveDate, int & type);
	/*
	��ȡ�����쵽�ڴ��
	*/
	double getRecentEndDepoist(Date now);
	/*
	���㵱����Ҫת������ж��ڣ����ҽ��ڶ�����Ҫ׼���Ľ����㷵��
	���أ� ��������ǰ׼�����
	*/
	int settlement(Date now);
	/*
	���㵱ǰ���е��ӵ���Ϣֵ
	*/
	double countProfit(double principal, int type, Date date, Date now);
	/*
	�޸�����
	*/
	double getAllPrincipal();
	void setProfit(int type, double profit);
	int getID();
	void setID(int id);
	string getUserAccount();
	void setUserAccount(int userid);
	int getType();
	void setType(int type);
	double getPrincipal();
	void setPrincipal(double principle);
	Date getDate();
	void setDate(Date date);
	int getTakeTimes();
	void setTakeTimes(int takeTimes);

protected:
	int id;
	string userAccount;
	int type;
	double principal;
	Date date;	
	int takeTimes;
	string staffAccount;
};

