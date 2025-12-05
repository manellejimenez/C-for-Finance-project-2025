#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>

// Abstract option interface
struct Option {
    virtual ~Option() = default;
    virtual double payoff(double S) const = 0;
};

// Example: European call option
struct EuropeanCall : Option {
    double K_;
    explicit EuropeanCall(double K) : K_(K) {}
    double payoff(double S) const override { return std::max(S - K_, 0.0); }
};

// CRR pricer using an internal 2D vector as the tree
class CRRPricer {
public:
    CRRPricer(Option* option, int depth, double S0, double U, double D, double R)
        : option_(option), N_(depth), S0_(S0), U_(U), D_(D), R_(R), computed_(false)
    {
        if (!option_) throw std::invalid_argument("Option pointer cannot be null");
        if (!(D_ < R_ && R_ < U_))
            throw std::invalid_argument("Arbitrage condition violated: require D < R < U");
        // allocate tree: row n has (n+1) nodes
        tree_.assign(N_ + 1, std::vector<double>());
        for (int n = 0; n <= N_; ++n) tree_[n].assign(n + 1, 0.0);
    }

    // Compute option prices by backward induction
    void compute() {
        // Terminal payoff
        for (int i = 0; i <= N_; ++i) {
            double S = stockPriceAt(N_, i);
            tree_[N_][i] = option_->payoff(S);
        }

        const double q_ = q(); // risk-neutral probability

        // Backward induction
        for (int n = N_ - 1; n >= 0; --n) {
            for (int i = 0; i <= n; ++i) {
                double upVal   = tree_[n + 1][i + 1];
                double downVal = tree_[n + 1][i];
                double H = (q_ * upVal + (1.0 - q_) * downVal) / (1.0 + R_);
                tree_[n][i] = H;
            }
        }
        computed_ = true;
    }

    // get node (n,i)
    double get(int n, int i) {
        if (!computed_) compute();
        if (n < 0 || n > N_ || i < 0 || i > n) throw std::out_of_range("Invalid node indices");
        return tree_[n][i];
    }

    // Evaluate price: either via tree root or closed-form binomial probability sum
    double operator()(bool closed_form = false) {
        if (!closed_form) {
            if (!computed_) compute();
            return tree_[0][0];
        }

        // closed-form binomial sum
        long double sum = 0.0L;
        const long double q_ = q();
        const long double discount = std::pow(1.0L + R_, -N_);
        for (int i = 0; i <= N_; ++i) {
            long double prob = binomial(N_, i) * std::pow(q_, i) * std::pow(1.0L - q_, N_ - i);
            double S = stockPriceAt(N_, i);
            sum += prob * option_->payoff(S);
        }
        return static_cast<double>(discount * sum);
    }

private:
    Option* option_;
    int N_;
    double S0_, U_, D_, R_;
    std::vector<std::vector<double>> tree_;
    bool computed_;

    // risk-neutral probability (assumes U != D)
    long double q() const {
        return (R_ - D_) / (U_ - D_);
    }

    // stock price at node (n,i) where i = number of up moves
    double stockPriceAt(int n, int i) const {
        // Using your convention: U and D are period returns (e.g. 0.1 for +10%)
        // so factor is (1+U) for each up, (1+D) for each down
        return S0_ * std::pow(1.0 + U_, i) * std::pow(1.0 + D_, n - i);
    }

    // compute binomial coefficient n choose k
    static long double binomial(int n, int k) {
        if (k < 0 || k > n) return 0.0L;
        if (k == 0 || k == n) return 1.0L;
        if (k > n - k) k = n - k;
        long double result = 1.0L;
        for (int i = 1; i <= k; ++i) {
            result *= static_cast<long double>(n - i + 1) / static_cast<long double>(i);
        }
        return result;
    }
};


