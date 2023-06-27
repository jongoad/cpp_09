#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <time.h>
#include <cmath>

#define DATA_FILE "data.csv"

class BitcoinExchange {
	public:

		/* Constructors & Destructor */
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange();
		BitcoinExchange operator=(const BitcoinExchange& rhs);


		/* Public Member Functions */
		void readData(void);
		void parseDataLine(const std::string& line);

		 /* Exceptions */
        class fileOpenError : public std::exception {
            public:
                const char *what() const throw() {
                    return ("Unable to open data file");
                }
        };

	private:
		std::map<std::string, int> exchange_rates_;
		std::map<std::string, int> values_;

};

/**
 * 1. Read file
 * 2. Parse file
 * 
 * 
 * 
 * Notes: Run BitcoinExchange in a try/catch in main file
 * 
*/