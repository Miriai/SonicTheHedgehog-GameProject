#include <iostream>
#include <Controller.h>

int main()
{
	try {
		Controller().run();
		return EXIT_SUCCESS;
	}

	catch (std::exception& e)
	{
		std::fstream errorFile;
		errorFile.open("log.txt");
		errorFile << "Exeption: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::fstream errorFile;
		errorFile.open("log.txt");
		errorFile << "Unknown exeption\n" << '\n';
		return EXIT_FAILURE;
	}
}