#include "../sources/pso/PSO.h"
#include "../sources/utils/CsvWriter.h"
#include <filesystem>
#include <iostream>
#include <vector>

int main()
{
    const double xMin = -1.0, xMax = 10.0;
    const double gammaMin = -0.5, gammaMax = 0.5;
    const int steps = 50;

    try
    {
        std::filesystem::path exePath = std::filesystem::current_path();
        std::filesystem::path assetsPath = exePath / "assets";
        std::filesystem::create_directories(assetsPath);

        std::string fileName = "result.csv";
        std::string filePath = (assetsPath / fileName).string();

        std::vector<CsvWriter::Result> results;

        for (double g = gammaMin; g <= gammaMax; g += 0.1)
        {
            double functionalMin;

            PSO pso(xMin, xMax, g, steps);
            pso.Optimize(functionalMin);

            CsvWriter::Result result;
            result.EMin = functionalMin;
            result.Gamma = g;

            results.insert(results.end(), result);
        }

        CsvWriter::WriteDataToCSVFile(filePath, results);
    }
    catch (std::exception& ex)
    {
        std::cerr << "An unhandled exception occured: " << ex.what() << std::endl;
    }
}
