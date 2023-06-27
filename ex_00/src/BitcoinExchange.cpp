#include "../include/BitcoinExchange.hpp"

date_t::date_t() {
  tm_sec   = 0;
  tm_min   = 0;
  tm_hour  = 0;
  tm_mday  = 0;
  tm_mon   = 0;
  tm_year  = 0;
  tm_wday  = 0;
  tm_yday  = 0;
  tm_isdst = 0;
}

bool date_t::operator<(const date_t &rhs) const { return mktime((tm *)this) < mktime((tm *)&rhs); }

bool date_t::operator>(const date_t &rhs) const { return mktime((tm *)this) > mktime((tm *)&rhs); }

bool date_t::operator<=(const date_t &rhs) const {
  return mktime((tm *)this) <= mktime((tm *)&rhs);
}

bool date_t::operator>=(const date_t &rhs) const {
  return mktime((tm *)this) >= mktime((tm *)&rhs);
}

bool date_t::operator==(const date_t &rhs) const {
  return mktime((tm *)this) == mktime((tm *)&rhs);
}

bool date_t::operator!=(const date_t &rhs) const {
  return mktime((tm *)this) != mktime((tm *)&rhs);
}

std::ostream &operator<<(std::ostream &os, const date_t &date) {
  os << date.tm_year << '-' << date.tm_mon << '-' << date.tm_mday;
  return os;
}




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

    //Convert value to float and check for errors
    double value;
    try {
        value = std::stod(valueStr);
        if (std::isnan(value) || std::isinf(value)) {
            std::cout << "NAN or INF found" << std::endl;
            return;
        }
    } catch (const std::exception& e) {
        std::cerr << "std::stod exception" << std::endl;
        return;
    }
 

    //Convert date to struct and check for errors

    time_t t = time(NULL);
    struct tm *res = localtime(&t);
    char *test = (char *)dateStr.c_str();
    strptime(test, "%Y-%m-%d", res);
    

    std::cout << res << std::endl;
    //Convert back to string to debug
    char dateRes[20];
    strftime(dateRes, 20, "%Y-%m-%d", res);

    // time_t today = time(NULL);
    // struct tm* now = localtime(&today); 
   
    

    /* debug */
    // std::cout << "Date string: " << dateStr << std::endl;
    // std::cout << "Value string: " << valueStr << std::endl;

    // std::cout << "Date: " << dateRes << std::endl << std::endl;
    // std::cout << "Value: " << value << std::endl;
    
};