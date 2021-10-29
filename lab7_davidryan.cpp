/**
 * lab7_davidryan.cpp
 * author: David ryan
 * class: Numerical Analysis CSCE 440
 * date: 10/29/2021
 * 
 * Calculates the integration of the 
 * function x^2/4 + y^2 = 1 from -1 to 1
 * using the Monte Carlo method.
 * 
 * compile with: g++ lab7_davidryan.cpp -std=c++11
*/

#include <cstdio>
#include <iostream>
#include <chrono>
#include <random>

bool checkFunc(double xValue, double yValue)
{
    if (((xValue * xValue) / 4) + (yValue * yValue) < 1)
        return true;

    return false;
}

double monte(int limit)
{
    int hits = 0;
    double xValue, yValue;

    std::random_device rand;
    std::mt19937 generate(rand());
    std::uniform_real_distribution<double> xDistribute(-1.0, 1.0);
    std::uniform_real_distribution<double> yDistribute(0.0, 1.0);

    for (int i = 0; i < limit; i++)
    {
        xValue = xDistribute(generate);
        yValue = yDistribute(generate);

        if (checkFunc(xValue, yValue))
        {
            hits++;
        };
    }

    return (double)hits / (double)limit;
}

int main(int argc, char *argv[])
{

    double estament;
    int area = 2;
    double actuallValue = 1.91322;

    std::chrono::high_resolution_clock::time_point start, stop;

    if (argc > 1)
    {
        std::cout << "Estimating the integration of  x^2/4 + y^2 = 1  from -1 to 1 using the Monte Carlo method with " << argv[1] << " iterations." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        estament = monte(atoi(argv[1]));
        stop = std::chrono::high_resolution_clock::now();
    }
    else
    {
        std::cout << "Estimating the integration of  x^2/4 + y^2 = 1  from -1 to 1 using the Monte Carlo with 100,000 iterations." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        estament = monte(100000);
        stop = std::chrono::high_resolution_clock::now();
    }

    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Total duration of execution: " << duration.count() << "ms" << std::endl;

    std::cout << "The calculated value is: " << estament * area << std::endl;
    std::cout << "The calculated error is: " << actuallValue - (estament * area) << std::endl;

    return 0;
}
