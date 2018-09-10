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
	/*
	��ʧĳһ�˻�, �����˻����룬�������ȷ�ԣ��Ա��ڹ�ʧ
	*/
	bool setAccountLost(string account, string pwd, const Date & now);
	/*
	�޸ĵ�ַ
	*/
	bool setAccountAddress(string account, string address);
	/*
	�޸�����
	����Ϊ�˻��� �����룬 �����룬��������������
	*/
	bool setAccountPwd(string account, string oldPwd, string newPwd, string newPwd2);
	/*
	��ȡ�û��˻���Ϣ�� IDNumber 
	*/
	bool getIDNumber(string account, string & IDNumber);
	/*
	�������֤�ţ�����0�����֤���Ȳ��ԣ�����-1�����֤��ʽ���󣻷���1�����֤��֤�ɹ�
	*/
	int judgeIdNumber(string& IDNumber);

	/*
	�������루�ַ�����������Int�͵�����ǿ�ȣ�1-3������Ϊ�������еȣ�ǿ��
	*/
	int judgePasswordStrength(string password);
	/*
	�ж��������룬ͨ������true�����򷵻�false��ֻ�ܰ�����ĸ�����֣���ָ�������ַ� { '~', '!', '@',  '$', '%', '^', '&', '*', '(', ')' }
	*/
	bool checkPwd(string str);
	/*
	���������ַ�����ͨ������true�����򷵻�false�����ܰ���ָ���ַ� { ' ', '#', '-',  ';'}
	*/
	bool checkText(string str);

	/*
	ͨ�ü�⣬������ֵ���м��
	*/
	bool checkAllString(vector <string> & strs);

	/*
	���㵱ǰ�ɻ����Ϣ
	*/
	double countProfit(Date & now, int id);
};

