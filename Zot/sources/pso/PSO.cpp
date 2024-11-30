#define _USE_MATH_DEFINES

#include "PSO.h"
#include <algorithm>
#include <cmath>
#include <iostream>

void PSO::InitializePopulation()
{
	Population.resize(N);

	for (auto& individual : Population)
	{
		for (auto& param : individual.Parameters)
		{
			param = LB + (UB - LB) * Rand(gen);
		}

		individual.Fitness = p_Solver->FindFunctionalValue(individual.Parameters);
	}

	BestIndividual = *std::min_element(Population.begin(), Population.end(), [](const Individual& a, const Individual& b)
	{
		return a.Fitness < b.Fitness;
	});
}

void PSO::Optimize(double& EMin)
{
	InitializePopulation();

	// Основной цикл алгоритма
	for (int t = 0; t < T; ++t)
	{
		UpdatePopulation(t);

		for (const auto& individual : Population) {
			if (individual.Fitness < BestIndividual.Fitness) {
				BestIndividual = individual;
			}
		}
	}

	EMin = BestIndividual.Fitness;

	std::cout << "Gamma = " << Gamma << std::endl;
	std::cout << "Best value = " << BestIndividual.Fitness << std::endl;
	std::cout << "a0 = " << BestIndividual.Parameters[0] << "; a1 = " << BestIndividual.Parameters[1] << "; a2 = " << BestIndividual.Parameters[2] << std::endl;
	std::cout << std::endl;
}

void PSO::UpdatePopulation(int t)
{
	Individual XL = *std::min_element(Population.begin(), Population.end(), [](const Individual& a, const Individual& b)
	{
		return a.Fitness < b.Fitness;
	});

	for (auto& individual : Population)
	{
		double temp = Rand(gen) * 15 + 20;
		double p = C1 * (1 / (SIGMA * sqrt(2 * M_PI))) * exp(-pow((temp - MU), 2) / (2 * SIGMA * SIGMA));

		if (temp > 30)
		{
			// Инициализация XShade
			std::array<double, 3> XShade;
			for (int i = 0; i < 3; ++i)
			{
				XShade[i] = (BestIndividual.Parameters[i] + XL.Parameters[i]) / 2;
			}

			if (Rand(gen) < 0.5)
			{
				double C2 = 2 - ((double)t / (double)T);
				for (int i = 0; i < 3; ++i)
				{
					individual.Parameters[i] += C2 * Rand(gen) * (XShade[i] - individual.Parameters[i]);
				}
			}
			else
			{
				int z = Rand(gen) * (N - 1);
				for (int i = 0; i < 3; ++i)
				{
					individual.Parameters[i] -= Population[z].Parameters[i] + XShade[i];
				}
			}
		}
		else
		{
			double Q = C3 * Rand(gen) * (individual.Fitness / BestIndividual.Fitness);
			if (Q > (C3 + 1) / 2)
			{
				std::array<double, 3> XFood;
				for (int i = 0; i < 3; ++i)
				{
					XFood[i] = std::exp(-1 / Q) * BestIndividual.Parameters[i];
				}

				for (int i = 0; i < 3; ++i)
				{
					individual.Parameters[i] += XFood[i] * p * (cos(2 * M_PI * Rand(gen)) - sin(2 * M_PI * Rand(gen)));
				}
			}
			else
			{
				std::array<double, 3> XFood;
				for (int i = 0; i < 3; ++i)
				{
					XFood[i] = BestIndividual.Parameters[i];
				}

				for (int i = 0; i < 3; ++i)
				{
					individual.Parameters[i] = individual.Parameters[i] * p + (individual.Parameters[i] - XFood[i]) * p + p * Rand(gen) * individual.Parameters[i];
				}
			}
		}

		for (auto& param : individual.Parameters)
		{
			param = std::max(LB, std::min(UB, param));
		}

		// Обновление решения для каждой особи рака
		individual.Fitness = p_Solver->FindFunctionalValue(individual.Parameters);
	}
}
