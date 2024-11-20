#ifndef MERTON_MODEL_H
#define MERTON_MODEL_H

double merton_call_option_price(
    double S0, double K, double r, double sigma, double T,
    double lambda, double mu_j, double sigma_j,
    int num_simulations, int num_steps
);

double merton_put_option_price(
    double S0, double K, double r, double sigma, double T,
    double lambda, double mu_j, double sigma_j,
    int num_simulations, int num_steps
);

#endif // MERTON_MODEL_H

