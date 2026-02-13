#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc < 2) 
	{
		std::cout << "Usage: aegis <jwt_token>\n";
		return 1;
	}

	std::string token = argv[1];

	std::cout << "Received JWT:\n" << token << std::endl;

	return 0;
}