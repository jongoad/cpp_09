#include "../include/BitcoinExchange.hpp"

/* Constructors & Destructor */
BitcoinExchange::BitcoinExchange() {
    try {
        readData();
    } catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
    }
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){

};

BitcoinExchange::~BitcoinExchange() {

};

BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange& rhs) {
    return *this;
};

/* Public Member Functions */

void BitcoinExchange::readData(void) {
    std::ifstream   data;
    std::string     line;

    data.open(DATA_FILE);

    //Check for failbit on stream, if fail detected then throw exception
    if (!data.good()) {
        throw BitcoinExchange::fileOpenError();
    }

    //Read entire file, parse and place in map
    while (std::getline(data, line)) {
        parseDataLine(line);
    }
    data.close();
};

void BitcoinExchange::parseDataLine(const std::string& line) {
    std::size_t delimPos = line.find_first_of(',');
    std::string valueStr = line.substr(delimPos + 1, std::string::npos);
    std::string dateStr = line.substr(0, line.size() - (line.size() - delimPos));

    //Check to make sure date and value are valid, then add to map
    double value = std::stod(valueStr);
    if (std::isnan(value) || std::isinf(value)) {
        std::cout << "NAN or INF found" << std::endl;
        return;
    }



    /* debug */
    std::cout << dateStr << std::endl;
    std::cout << valueStr << std::endl << std::endl;

};