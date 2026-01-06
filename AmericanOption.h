#pragma once
#include "Option.h"
class AmericanOption : public Option
{
public:
	AmericanOption(double expiry);

	// If it's an American Option, ovveride isAmericanOption method
	bool isAmericanOption() override;
};

