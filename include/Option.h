#include <iostream>

enum class optionType { CALL, PUT };

class Option
{
private:
    double _expiry;

public:
    Option();
    Option(double e);

    double getExpiry() const;

    // Méthode virtuelle pure (rend la classe abstraite)
    virtual double payoff(double z) const = 0;

    // Nouvelle méthode pour la partie 4 (virtuelle simple)
    virtual bool isAmericanOption();

    // Destructeur virtuel
    virtual ~Option();
};
