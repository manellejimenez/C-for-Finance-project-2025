# C-for-Finance-project-2025
class Option
{
  private :
  
    double _expiry;
    
  public :
  
    string getExpiry() {return _expiry;}
    
    virtual double payoff(double) = 0;
    ~Option() {}
    
    Option (double e) 
    {
      _expiry = e;
      cout<< "Une option à été créé" << endl;
    }
};

Class EuropeanVanillaOption : public Option
{
  private :
    double _strike;

  public :
  
    EuropeanVanillaOption(Option expiry , double strike) : option(expiry), _strike(strike)
    {
      if (expiry < 0 || strike < 0)
      {
         throw std::invalid_argument("Expiry et strike doivent être non-négatifs");
      }
    }

    enum optionType { CALL , PUT};

    virtual optionType GetOptionType() =0;
    
};

class CallOption : public EuropeanVanillaOption
{
  CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}
  
  double payoff(double z) const override
  {
    return (z <= getStrike()) ? (z - getStrike()) : 0.0;
  }

  optionType GetOptionType() const override 
  {
        return CALL;
  }
};

class PutOption : public EuropeanVanillaOption
{
  PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}
  
  double payoff(double z) const override
  {
    return (z <= getStrike()) ? ( getStrike()-Z) : 0.0;
  }

  optionType GetOptionType() const override 
  {
        return PUT;
  }
};












