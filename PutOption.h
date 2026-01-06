#pragma once
#include "Option.h"
#include "EuropeanDigitalOption.h"

class PutOption : public EuropeanVanillaOption
{
public:
	//constructeur de la classe
	PutOption(double, double);
	~PutOption();

	OptionType GetOptionType() override;
	double payoff(double) override;
};

