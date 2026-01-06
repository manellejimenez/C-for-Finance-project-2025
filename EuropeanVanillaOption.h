#pragma once
#include <iostream>
#include "Option.h"


class EuropeanVanillaOption : public Option
{
	private: double _strike;

	public : 

		//constructeur avec strike et expiry
		EuropeanVanillaOption(double, double);

		//destructeur virtuel
		virtual ~EuropeanVanillaOption();

		//methodes
		double GetOptionStrike() override;
		virtual OptionType GetOptionType() override = 0;
		virtual double payoff(double) override = 0;
		friend class BlackSholesPricer;

};



