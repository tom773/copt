#include <math.h>
#include <stdlib.h>
#include "heston.h"

// Random number generator between 0 and 1
static double rand_uniform() {
    return (double)rand() / RAND_MAX;
}

// Standard normal random variable using Box-Muller transform
static double rand_normal() {
    double u1 = rand_uniform();
    double u2 = rand_uniform();
    return sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
}

// Generate correlated normal random variables
static void generate_correlated_normals(double *z1, double *z2, double rho) {
    double x = rand_normal();
    double y = rand_normal();
    *z1 = x;
    *z2 = rho * x + sqrt(1 - rho * rho) * y;
}

// Heston model Monte Carlo simulation for call option
double heston_call_option_price(
    double S0, double K, double r, double T,
    double kappa, double theta, double sigma_v, double rho, double v0,
    int num_simulations, int num_steps
) {
    double dt = T / num_steps;
    double sum_payoffs = 0.0;

    for (int i = 0; i < num_simulations; i++) {
        double S = S0;
        double v = v0;

        for (int j = 0; j < num_steps; j++) {
            double z1, z2;
            generate_correlated_normals(&z1, &z2, rho);

            // Variance process
            v = v + kappa * (theta - v) * dt + sigma_v * sqrt(fmax(v, 0)) * sqrt(dt) * z2;
            v = fmax(v, 0); // Ensure variance remains non-negative

            // Asset price process
            S = S * exp((r - 0.5 * v) * dt + sqrt(v * dt) * z1);
        }

        double payoff = fmax(S - K, 0.0);
        sum_payoffs += payoff;
    }

    double option_price = exp(-r * T) * (sum_payoffs / num_simulations);
    return option_price;
}

// Heston model Monte Carlo simulation for put option
double heston_put_option_price(
    double S0, double K, double r, double T,
    double kappa, double theta, double sigma_v, double rho, double v0,
    int num_simulations, int num_steps
) {
    double dt = T / num_steps;
    double sum_payoffs = 0.0;

    for (int i = 0; i < num_simulations; i++) {
        double S = S0;
        double v = v0;

        for (int j = 0; j < num_steps; j++) {
            double z1, z2;
            generate_correlated_normals(&z1, &z2, rho);

            // Variance process
            v = v + kappa * (theta - v) * dt + sigma_v * sqrt(fmax(v, 0)) * sqrt(dt) * z2;
            v = fmax(v, 0); // Ensure variance remains non-negative

            // Asset price process
            S = S * exp((r - 0.5 * v) * dt + sqrt(v * dt) * z1);
        }

        double payoff = fmax(K - S, 0.0);
        sum_payoffs += payoff;
    }

    double option_price = exp(-r * T) * (sum_payoffs / num_simulations);
    return option_price;
}

