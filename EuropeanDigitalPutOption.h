#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption {

public:

	EuropeanDigitalPutOption(double, double);
	~EuropeanDigitalPutOption();

	double payoff(double) override;
	OptionType GetOptionType() override;

};


