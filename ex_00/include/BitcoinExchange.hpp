#include <iostream>
#include <vector>
#include <string>
#include <utility>

class BitcoinExchange {
	public:

		/* Constructors & Destructor */
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange();
		BitcoinExchange operator=(const BitcoinExchange& rhs);


	private:
		std::vector<std::pair<std::string, int>> exchange_rates_;
		std::vector<std::pair<std::string, int>> values_;


};