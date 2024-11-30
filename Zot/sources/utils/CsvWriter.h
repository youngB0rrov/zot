#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

class CsvWriter
{
public:

	struct Result
	{
		double Gamma;
		double EMin;
	};

	static void WriteDataToCSVFile(const std::string& fileName, const std::vector<Result>& results)
	{
		std::ofstream file(fileName);

		if (!file.is_open())
		{
			std::cerr << "Error, while openning file" << std::endl;
			return;
		}

		file << "gamma,E1_min" << std::endl;

		file << std::fixed << std::setprecision(5);

		for (auto& result : results)
		{
			file << result.Gamma << "," << result.EMin << std::endl;
		}

		file.close();
	}
};