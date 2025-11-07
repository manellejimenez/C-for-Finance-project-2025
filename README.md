# C-for-Finance-project-2025
class Option
{
private :
  double _expiry;
public :
  string getExpiry() {return _expiry;}
  virtual double payoff(double) = 0;

  Option (double e) 
  {
    _expiry = e;
    cout<< "Une option à été créé" << endl;
  }
}
