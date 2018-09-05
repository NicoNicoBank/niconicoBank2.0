#include "FixedDeposit.h"


FixedDeposit::FixedDeposit()
{
}


FixedDeposit::~FixedDeposit()
{
}

void FixedDeposit::draw()
{
}

void FixedDeposit::save()
{
}

int FixedDeposit::getTimeCounter() {
	int temp = timeCounter;
	return temp;
}

void FixedDeposit::setTimeCounter(int _timeCounter) {
	timeCounter = _timeCounter;
}
int FixedDeposit::timeCounter = 0;