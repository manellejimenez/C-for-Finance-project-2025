#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption {

	public:

		EuropeanDigitalCallOption(double, double);
		~EuropeanDigitalCallOption();

		double payoff(double) override;
		OptionType GetOptionType() override;

};


