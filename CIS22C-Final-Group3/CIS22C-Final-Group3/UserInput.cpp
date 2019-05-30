#include <iostream>
#include <string>

int getUserInputInt(const int& min, const int& max)
{
	std::string input;
	int inputInt;
	bool err;

	do
	{
		err = false;

		std::getline(std::cin, input);

		//Exception handling
		try
		{
			inputInt = stoi(input);

			//Input must be between min and max
			if (inputInt < min || inputInt > max)
			{
				std::cerr << UI::ERR_INVALID_OPTION_RANGE << min << " and " << max << " inclusive." << std::endl;
				err = true;
			}
		}
		catch (invalid_argument&)
		{
			std::cerr << UI::ERR_EXCEPTION_INVALID_ARGUMENT << std::endl;
			err = true;
		}
		catch (out_of_range&)
		{
			std::cerr << UI::ERR_EXCEPTION_OUT_OF_RANGE << std::endl;
			err = true;
		}
		catch (...)
		{
			std::cerr << UI::ERR_EXCEPTION_GENERIC << std::endl;
			err = true;
		}

	} while (err || !std::cin);

	return inputInt;
}

double getUserInputDouble(const double& min, const double& max)
{
	std::string input;
	double inputDouble;
	bool err;

	do
	{
		err = false;

		std::getline(std::cin, input);

		//Exception handling
		try
		{
			inputDouble = std::stod(input);

			//Input must be between min and max
			if (inputDouble < min || inputDouble > max)
			{
				std::cerr << UI::ERR_INVALID_OPTION_RANGE << min << " and " << max << " inclusive." << std::endl;
				err = true;
			}
		}
		catch (invalid_argument&)
		{
			std::cerr << UI::ERR_EXCEPTION_INVALID_ARGUMENT << std::endl;
			err = true;
		}
		catch (out_of_range&)
		{
			std::cerr << UI::ERR_EXCEPTION_OUT_OF_RANGE << std::endl;
			err = true;
		}
		catch (...)
		{
			std::cerr << UI::ERR_EXCEPTION_GENERIC << std::endl;
			err = true;
		}

	} while (err || !std::cin);

	return inputDouble;
}

std::string getUserInputString()
{
	std::string input;

	std::getline(std::cin, input);

	return input;
}