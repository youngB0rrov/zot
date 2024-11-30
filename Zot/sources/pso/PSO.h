#include <array>
#include <limits>
#include <vector>
#include <random>
#include "../utils/ODESolver.h"

class PSO
{
public:
	PSO(double minX, double maxX, double gamma, double stepsNum) : LB(-100), UB(100), Gamma(gamma), N(50), T(1000), C1(0.2), C3(3), SIGMA(3), MU(25)
	{
		p_Solver = new ODESolver(minX, maxX, gamma, stepsNum);
	}

	~PSO()
	{
		delete p_Solver;
	}

	void InitializePopulation();
	void Optimize(double& EMin);
	void UpdatePopulation(int t);

private:

	struct Individual
	{
		std::array<double, 3> Parameters;
		double Fitness;

		Individual()
		{
			Parameters = { 0.0, 1.1, 1.1 };
			Fitness = std::numeric_limits<double>::max();
		}
	};

	// Размер популяции
	const int N;

	// Максимальное количество итераций
	const int T;

	// Параметр, от которого завист функция f1(x)
	double Gamma;

	// Параметры алгоритма
	const double LB, UB;
	const double C1, C3;
	const double SIGMA, MU;

	std::vector<Individual> Population;
	Individual BestIndividual;
	std::vector<double> BestFitnessHistory;


	std::mt19937 gen;
	std::uniform_real_distribution<> Rand{ 0.0, 1.0 };

	ODESolver* p_Solver;
};