#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <time.h>
#include <cmath>
#include <ctime>

#define DATA_FILE "data.csv"

struct date_t : public tm {
	date_t();

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