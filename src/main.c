#include <stdio.h>
#include <stdlib.h>
#include "bs.h"
#include "heston.h"
#include "merton.h"
#define DAYS_IN_YEAR 365.0

int main() {
    // Common parameters
    double S0 = 136.40;     // Initial stock price
    double K = 115.0;      // Strike price
    double r = 0.0438;       // Risk-free rate
    double Td = 29.0;        // Time to maturity
    double T = Td / DAYS_IN_YEAR;        // Time to maturity
    
    // Black-Scholes parameters
    double sigma_bs = 0.552; // Volatility for Black-Scholes

    // Heston model parameters
    double kappa = 2.0;    // Mean reversion rate of variance
    double sigma_v = 0.3;  // Volatility of volatility
    double theta = (sigma_bs*sigma_bs);   // Long-term variance
    double rho = -0.7;     // Correlation between asset and variance
    double v0 = (sigma_bs*sigma_bs);      // Initial variance

    // Merton model parameters
    double sigma_merton = 0.552;    // Diffusion volatility
    double lambda = 0.2;          // Average jump frequency
    double mu_j = -0.2;           // Average jump size
    double sigma_j = 0.3;         // Jump size volatility

    // Simulation parameters
    int num_simulations = 100000;
    int num_steps = 100;

    // Seed random number generator
    srand(42);

    // Black-Scholes model
    double call_price_bs = black_scholes_call(S0, K, r, sigma_bs, T);
    double put_price_bs = black_scholes_put(S0, K, r, sigma_bs, T);

    // Heston model
    double call_price_heston = heston_call_option_price(
        S0, K, r, T, kappa, theta, sigma_v, rho, v0, num_simulations, num_steps
    );
    double put_price_heston = heston_put_option_price(
        S0, K, r, T, kappa, theta, sigma_v, rho, v0, num_simulations, num_steps
    );

    // Merton model
    double call_price_merton = merton_call_option_price(
        S0, K, r, sigma_merton, T, lambda, mu_j, sigma_j, num_simulations, num_steps
    );
    double put_price_merton = merton_put_option_price(
        S0, K, r, sigma_merton, T, lambda, mu_j, sigma_j, num_simulations, num_steps
    );
    
    double w_bsm = .20;
    double w_heston = .40;
    double w_merton = .40;
    double fve_put = (w_bsm * put_price_bs) + (w_heston * put_price_heston) + (w_merton * put_price_merton);
    double fve_call = (w_bsm * call_price_bs) + (w_heston * call_price_heston) + (w_merton * call_price_merton);
    printf("Fair Value Put Price: %.2f\n", fve_put);
    printf("Fair Value Call Price: %.2f\n", fve_call);
    return 0;
}

