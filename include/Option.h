#pragma once
#include <iostream>
using namespace std;

class Option
{
private:
    double _expiry;

public:
    Option();
    Option(double e);
    virtual ~Option();

    double getExpiry() const;

    virtual double payoff(double z) const = 0;
};
