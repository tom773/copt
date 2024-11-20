#ifndef HESTON_MODEL_H
#define HESTON_MODEL_H

double heston_call_option_price(
    double S0, double K, double r, double T,
    double kappa, double theta, double sigma_v, double rho, double v0,
    int num_simulations, int num_steps
);

double heston_put_option_price(
    double S0, double K, double r, double T,
    double kappa, double theta, double sigma_v, double rho, double v0,
    int num_simulations, int num_steps
);

#endif // HESTON_MODEL_H

