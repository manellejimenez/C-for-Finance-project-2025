#pragma once
#include "Option.h"
#include "EuropeanVanillaOption.h"

class EuropeanDigitalOption : public Option
{
	private :
		double _strike;

	public :

		EuropeanDigitalOption(double, double);

		//methodes
		//destructeur virtuel
		virtual ~EuropeanDigitalOption();
		double GetOptionStrike();

		bool isDigital() override;
		virtual OptionType GetOptionType() override = 0;
		virtual double payoff(double) override = 0;
		friend class BlackSholesPricer;



};




