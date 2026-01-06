#pragma once
#include "EuropeanVanillaOption.h"
#include "Option.h"

class CallOption : public EuropeanVanillaOption
{

public:

	//constructeur de la classe
	CallOption(double, double);
	~CallOption();

	double payoff(double) override;
	OptionType GetOptionType() override;
};


