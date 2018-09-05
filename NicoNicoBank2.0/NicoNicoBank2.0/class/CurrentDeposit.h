#pragma once
#include "Deposit.h"
class CurrentDeposit :
	public Deposit
{
public:
	CurrentDeposit();
	~CurrentDeposit();
	void save();
};

