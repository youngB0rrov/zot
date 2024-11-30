#include <cmath>
#include <vector>
#include "ODESolver.h"

std::vector<double> ODESolver::FindSolution()
{
    std::vector<double> xValues(StepsNum + 1);
    std::vector<double> fValues(StepsNum + 1);

    // Начальные условия
    xValues[0] = XStart;
    fValues[0] = 1.0;

    for (int i = 0; i < StepsNum; ++i) {
        double x = xValues[i];
        double f = fValues[i];

        double k1 = h * Gamma * f;
        double k2 = h * Gamma * (f + 0.5 * k1);
        double k3 = h * Gamma * (f + 0.5 * k2);
        double k4 = h * Gamma * (f + k3);

        fValues[i + 1] = f + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        xValues[i + 1] = x + h;
    }

    return fValues;
}

double ODESolver::FindFunctionalValue(std::array<double, 3>& a)
{
    std::vector<double> fResults = ODESolver::FindSolution();
    std::vector<double> pResults(StepsNum + 1);

    double x = XStart;
    for (int i = 0; i <= StepsNum; ++i)
    {
        pResults[i] = P(a, x);
        x += h;
    }

    return TrapezoidIntegrationValue(fResults, pResults);
}

double ODESolver::TrapezoidIntegrationValue(const std::vector<double>& fValues, const std::vector<double>& pValues)
{
    double sum = 0.5 * (pow((fValues[0] - pValues[0]), 2)) +
        0.5 * (pow((fValues[fValues.size() - 1] - pValues[pValues.size() - 1]), 2));

    // Для всех внутренних точек
    for (size_t i = 1; i < fValues.size() - 1; ++i) {
        sum += pow((fValues[i] - pValues[i]), 2);
    }

    return sum * h; // Возвращаем результат интегрирования
}

double ODESolver::P(std::array<double, 3>& a, double x)
{
    return a[0] + a[1] * x + a[2] * pow(x, 2);
}
