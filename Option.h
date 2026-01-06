#pragma once
#include <iostream>
#include <vector>

//enum class pour l'option type
enum class OptionType { call, put };

class Option
{
	private: double _expiry;

	public:

		
		// Constructeur
		Option(double);

		//Destructueur virtuel 
		virtual ~Option();

		// Methods
		double getExpiry();
		virtual double GetOptionStrike() = 0;
		virtual OptionType GetOptionType() = 0;
		virtual double payoff(double);
		virtual std::vector<double> getTimeSteps();
		virtual double payoffPath(std::vector<double>);

		// Partie 2, sous partie 3
		virtual bool isDigital();
		virtual bool isAsianOption();
		virtual bool isAmericanOption();
			

};
