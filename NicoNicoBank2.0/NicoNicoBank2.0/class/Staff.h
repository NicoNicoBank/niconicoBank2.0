#pragma once
#include <string>
using namespace std;
//����Ա
class Staff
{
public:
	Staff();
	Staff(string name, string jobNumber, string password, int id = -1);
	~Staff();
	bool readData(string query="id");
	/*
	�����Ѵ�����������
	*/
	bool save();
	/*
	��֤��ȷ����true, ��֤���󷵻�false,����errorMessgeΪ""
	���ݿ���󷵻�false, erroMessage;
	*/
	bool verify();

	string getName();
	void setID(int id);
	int getId();
	void setId(int _id);
	void setName(string _name);
	string getJobNumber();
	void setJobNumber(string _jobNumber);
	string getPwd();
	void setPwd(string pwd);
private:
	int id;
	string name; //����
	string jobNumber; // ����
	string password; //staff����
};

