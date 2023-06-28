#include <iostream>
#include "../include/BitcoinExchange.hpp"
#include <string>


int main (int argc, char **argv) {

	//Check for file
	if (argc < 2) {
		std::cerr << ERR_FILE_OPEN << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string filePath = argv[1];
	BitcoinExchange exchange(filePath);

}