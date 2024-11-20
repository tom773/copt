#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

double cumulative_normal(double x);
double black_scholes_call(double S, double K, double r, double sigma, double T);
double black_scholes_put(double S, double K, double r, double sigma, double T);

#endif // BLACK_SCHOLES_H

