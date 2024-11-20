#include <math.h>
#include "bs.h"

// Cumulative distribution function for the standard normal distribution
double cumulative_normal(double x) {
    return 0.5 * (1 + erf(x / sqrt(2)));
}

// Black-Scholes formula for a European call option
double black_scholes_call(double S, double K, double r, double sigma, double T) {
    double d1 = (log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    double call_price = S * cumulative_normal(d1) - K * exp(-r * T) * cumulative_normal(d2);
    return call_price;
}

// Black-Scholes formula for a European put option
double black_scholes_put(double S, double K, double r, double sigma, double T) {
    double d1 = (log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    double put_price = K * exp(-r * T) * cumulative_normal(-d2) - S * cumulative_normal(-d1);
    return put_price;
}

