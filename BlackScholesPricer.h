#pragma once
#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "Option.h"

class BlackScholesPricer
{
	private :
		Option* _option;
		double _asset_price;
		double _interest_rate;
		double _volatility;


	public :

		BlackScholesPricer(Option*, double, double, double);
		virtual ~BlackScholesPricer();

		//pricing part 
		double NormalDistr(double);
		//Operation sur l'object d'intance creer dans le main
		//On aurait pu faire une methode CalculPrice a a place
		double operator()();

		//Delta part
		double NormalDensity(double);
		double delta();


};

