#include <cstdlib>

#include "refrigerator.hpp"

int main(int argc, char* argv[])
{
	ascii_refrigerator::refrigerator refrigerator;

	bool success = refrigerator.generate(argc, argv);

	if (!success)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
