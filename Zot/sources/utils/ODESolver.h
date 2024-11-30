#include <vector>
#include <array>

class ODESolver
{
public:
	ODESolver(double xMin, double xMax, double gamma, int stepsNum): XStart(xMin), XEnd(xMax), Gamma(gamma), StepsNum(stepsNum) 
	{ 
		h = (XEnd - XStart) / (StepsNum - 1);
	}

	std::vector<double> FindSolution();
	double FindFunctionalValue(std::array<double, 3>& a);
	double TrapezoidIntegrationValue(const std::vector<double>& fValues, const std::vector<double>& pValues);

private:
	const double XStart, XEnd, Gamma;
	double h;
	const int StepsNum;

	double static P(std::array<double, 3>& a, double x);
};