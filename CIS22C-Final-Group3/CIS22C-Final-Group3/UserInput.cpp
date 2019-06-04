#include "UserInput.h"

int UserInput::getUserInputInt(const int min, const int max)
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
				std::cerr << "ERROR: Invalid option, option must be between " << min << " and " << max << " inclusive." << std::endl;
				err = true;
			}
		}
		catch (std::invalid_argument&)
		{
			std::cerr << "ERROR: Invalid option, option is not a valid argument. Are you correctly typing a number or a string?" << std::endl;
			err = true;
		}
		catch (std::out_of_range&)
		{
			std::cerr << "ERROR: Invalid option, option is out of range." << std::endl;
			err = true;
		}
		catch (...)
		{
			std::cerr << "ERROR: An exception occurred." << std::endl;
			err = true;
		}

	} while (err || !std::cin);

	return inputInt;
}

double UserInput::getUserInputDouble(const double min, const double max)
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
				std::cerr << "ERROR: Invalid option, option must be between " << min << " and " << max << " inclusive." << std::endl;
				err = true;
			}
		}
		catch (std::invalid_argument&)
		{
			std::cerr << "ERROR: Invalid option, option is not a valid argument. Are you correctly typing a number or a string?" << std::endl;
			err = true;
		}
		catch (std::out_of_range&)
		{
			std::cerr << "ERROR: Invalid option, option is out of range." << std::endl;
			err = true;
		}
		catch (...)
		{
			std::cerr << "ERROR: An exception occurred." << std::endl;
			err = true;
		}

	} while (err || !std::cin);

	return inputDouble;
}

std::string UserInput::getUserInputString()
{
	std::string input;

	std::getline(std::cin, input);

	return input;
}