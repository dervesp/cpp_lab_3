#include "stdafx.h"
#include "Car.h"

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Car.h"

void ProcessCommandLine(CCar & car, std::string & line, std::ostream & ostream);

void ProcessInfoCommand(CCar & car, std::istringstream & istream, std::ostream & ostream);
void ProcessEngineCommand(CCar & car, std::istringstream & istream, std::ostream & ostream);
void ProcessSpeedCommand(CCar & car, std::istringstream & istream, std::ostream & ostream);
void ProcessGearCommand(CCar & car, std::istringstream & istream, std::ostream & ostream);

void main()
{
	CCar car = CCar();
	std::string line;
	while (std::getline(std::cin, line))
	{
		ProcessCommandLine(car, line, std::cout);
	}
}

void ProcessCommandLine(CCar & car, std::string & line, std::ostream & ostream)
{
	std::istringstream istream(line);

	std::string command;

	if (istream >> command)
	{
		if (command == "info")
		{
			ProcessInfoCommand(car, istream, std::cout);
		}
		else if (command == "engine")
		{
			ProcessEngineCommand(car, istream, std::cout);
		}
		else if (command == "speed")
		{
			ProcessSpeedCommand(car, istream, std::cout);
		}
		else if (command == "gear")
		{
			ProcessGearCommand(car, istream, std::cout);
		}

	}
	else
	{
		ostream << "Command error" << std::endl;
	}
	ostream << std::endl;

}