#pragma once
#include "Deposit.h"
class FixedDeposit :
	public Deposit
{
public:
	FixedDeposit();
	~FixedDeposit();
	void draw();
	void save();

	int getTimeCounter();
	void setTimeCounter(int _timeCounter);
	static int timeCounter;
private:
	
};

