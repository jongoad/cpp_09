#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <time.h>
#include <cmath>
#include <ctime>
#include <limits.h>

#define DATA_FILE "data.csv"
#define ERR_FILE_OPEN "Error: could not open file."

struct date_t : public tm {
	date_t();
	date_t(tm* time);

	bool operator<(const date_t &rhs) const;
	bool operator>(const date_t &rhs) const;
	bool operator<=(const date_t &rhs) const;
	bool operator>=(const date_t &rhs) const;
	bool operator==(const date_t &rhs) const;
	bool operator!=(const date_t &rhs) const;
};

class BitcoinExchange {
	public:

		/* Constructors & Destructor */
		BitcoinExchange(const std::string& input);
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange();
		BitcoinExchange operator=(const BitcoinExchange& rhs);


		/* Public Member Functions */
		void readData(void);
		void parseDataLine(const std::string& line);
		void readInput(const std::string& input);
		void parseInputLine(const std::string& line);

		void exchanger(date_t date, float value);

		 /* Exceptions */
        class fileOpenError : public std::exception {
            public:
                const char *what() const throw() {
                    return ERR_FILE_OPEN;
                }
        };

	private:
		std::map<date_t, float> exchange_rates_;
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