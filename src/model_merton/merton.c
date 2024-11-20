#include <math.h>
#include <stdlib.h>
#include "merton.h"

// Uniform random number between 0 and 1
static double rand_uniform() {
    return (double)rand() / RAND_MAX;
}

// Standard normal random variable
static double rand_normal() {
    double u1 = rand_uniform();
    double u2 = rand_uniform();
    return sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
}

// Poisson random variable using inversion by sequential search
static int rand_poisson(double lambda) {
    double L = exp(-lambda);
    double p = 1.0;
    int k = 0;

    do {
        k++;
        p *= rand_uniform();
    } while (p > L);

    return k - 1;
}

// Merton model Monte Carlo simulation for call option
double merton_call_option_price(
    double S0, double K, double r, double sigma, double T,
    double lambda, double mu_j, double sigma_j,
    int num_simulations, int num_steps
) {
    double dt = T / num_steps;
    double sum_payoffs = 0.0;

    // Precompute k
    double k = exp(mu_j + 0.5 * sigma_j * sigma_j) - 1.0;

    for (int i = 0; i < num_simulations; i++) {
        double S = S0;

        for (int j = 0; j < num_steps; j++) {
            // Number of jumps in this time interval
            int num_jumps = rand_poisson(lambda * dt);

            // Calculate jump component
            double jump_multiplier = 1.0;
            for (int l = 0; l < num_jumps; l++) {
                double Y = mu_j + sigma_j * rand_normal();
                jump_multiplier *= exp(Y);
            }

            // Asset price process
            double dS = (r - lambda * k - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * rand_normal();
            S = S * exp(dS) * jump_multiplier;
        }

        double payoff = fmax(S - K, 0.0);
        sum_payoffs += payoff;
    }

    double option_price = exp(-r * T) * (sum_payoffs / num_simulations);
    return option_price;
}

// Merton model Monte Carlo simulation for put option
double merton_put_option_price(
    double S0, double K, double r, double sigma, double T,
    double lambda, double mu_j, double sigma_j,
    int num_simulations, int num_steps
) {
    double dt = T / num_steps;
    double sum_payoffs = 0.0;

    // Precompute k
    double k = exp(mu_j + 0.5 * sigma_j * sigma_j) - 1.0;

    for (int i = 0; i < num_simulations; i++) {
        double S = S0;

        for (int j = 0; j < num_steps; j++) {
            // Number of jumps in this time interval
            int num_jumps = rand_poisson(lambda * dt);

            // Calculate jump component
            double jump_multiplier = 1.0;
            for (int l = 0; l < num_jumps; l++) {
                double Y = mu_j + sigma_j * rand_normal();
                jump_multiplier *= exp(Y);
            }

            // Asset price process
            double dS = (r - lambda * k - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * rand_normal();
            S = S * exp(dS) * jump_multiplier;
        }

        double payoff = fmax(K - S, 0.0);
        sum_payoffs += payoff;
    }

    double option_price = exp(-r * T) * (sum_payoffs / num_simulations);
    return option_price;
}

