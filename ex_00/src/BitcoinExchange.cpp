#include "../include/BitcoinExchange.hpp"

/* Extenstion for tm date/time struct*/
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

date_t::date_t(tm* time) {
    tm_gmtoff = time->tm_gmtoff;
    tm_hour = time->tm_hour;
    tm_isdst = time->tm_isdst;
    tm_mday = time->tm_mday;
    tm_min = time->tm_min;
    tm_mon = time->tm_mon;
    tm_sec = time->tm_sec;
    tm_wday = time->tm_wday;
    tm_yday = time->tm_yday;
    tm_year = time->tm_year;
    tm_zone = time->tm_zone;
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
  os << date.tm_year + 1900 << '-' << date.tm_mon + 1 << '-' << date.tm_mday;
  return os;
}

/* Constructors & Destructor */
BitcoinExchange::BitcoinExchange(const std::string& input) {
    //Read and parse the data.csv file
    try {
        readData();
    } catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
    }

    //Set min and max keys to save calculations later
    setMinMax();

    //Read and parse the input.txt file. then print results
    try {
        readInput(input);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
    *this = other;
};

BitcoinExchange::~BitcoinExchange() {};

BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange& rhs) {
    exchange_rates_ = rhs.exchange_rates_;
    values_ = rhs.values_;
    min_ = rhs.min_;
    max_ = rhs.max_;
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
    std::string valueStr = line.substr(line.find_first_of(',') + 1, std::string::npos);
    std::string dateStr = line.substr(0, line.size() - (line.size() - line.find_first_of(',')));

    //Convert value to float and check for errors
    double value;
    try {
        value = std::stod(valueStr);
        if (std::isnan(value) || std::isinf(value)) {
            std::cout << "Error: NAN or INF found" << std::endl;
            return;
        }
    } catch (const std::exception& e) {
        return;
    }
 
    //Convert date to struct and check for errors
    time_t t = time(NULL);
    struct tm *res = localtime(&t);
    char *buf = (char *)dateStr.c_str();
    strptime(buf, "%Y-%m-%d", res);
    date_t date(res);
    if (date.tm_year >= 2009 - 1900 && date.tm_year <= 2023 - 1900
        && date.tm_mon >= 0 && date.tm_mon <= 11
        && date.tm_mday >= 1 && date.tm_mday <= 31
        && mktime((tm *)&date) != -1) {
        exchange_rates_[date] = value;
    }
};

void BitcoinExchange::readInput(const std::string& input) {
    std::ifstream   data;
    std::string     line;

    data.open(input);

    //Check for failbit on stream, if fail detected then throw exception
    if (!data.good()) {
        throw BitcoinExchange::fileOpenError();
    }

    //Read entire file, parse and place in map
    while (std::getline(data, line)) {
        parseInputLine(line);
    }
    data.close();
};

void BitcoinExchange::parseInputLine(const std::string& line) {
    std::string valueStr = line.substr(line.find_first_of('|') + 1, std::string::npos);
    std::string dateStr = line.substr(0, line.size() - (line.size() - line.find_first_of('|')));

    //Remove whitespace
    valueStr = valueStr.substr(valueStr.find_first_of(' ') + 1, std::string::npos);
    dateStr = dateStr.substr(0, dateStr.size() - (dateStr.size() - dateStr.find_first_of(' ')));

    //Convert date
    time_t t = time(NULL);
    struct tm *res = localtime(&t);
    char *buf = (char *)dateStr.c_str();
    strptime(buf, "%Y-%m-%d", res);
    date_t date(res);
    if (!(date.tm_year >= 2008 - 1900 && date.tm_year <= 2023 - 1900
        && date.tm_mon >= 0 && date.tm_mon <= 11
        && date.tm_mday >= 1 && date.tm_mday <= 31
        && mktime((tm *)&date) != -1)) {
        std::cerr << "Error: bad input => " << dateStr << std::endl;
        return;
    }

    //Convert value
    double value;
    try {
        value = std::stod(valueStr);
        if (std::isnan(value) || std::isinf(value)) {
            std::cerr << "Error: NAN or INF found" << std::endl;
            return;
        } else if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            return;
        } else if (value > 1000) {
            std::cerr << "Error: number is too large." << std::endl;
            return;
        }
    } catch (const std::exception& e) {
        return;
    }

    //Call exchanger function
    exchanger(date, value);
};

void BitcoinExchange::setMinMax(void) {
    std::map<date_t, float>::iterator it = exchange_rates_.begin();
    this->min_ = it;
    this->max_ = it;

    for (; it != exchange_rates_.end(); it++) {
        if (it->first < min_->first) {
            min_ = it;
        } else if (it->first > max_->first) {
            max_ = it;
        } 
    }
};

void BitcoinExchange::exchanger(date_t date, float value) {
    std::map<date_t, float>::iterator it = exchange_rates_.find(date);

    if ( it != exchange_rates_.end()) {
        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    } else if (date < min_->first) {    //Handle smaller than lowest value
        std::cout << date << " => " << value << " = " << value * min_->second << std::endl;
    } else if (date > max_->first) {    //Handle larger than largest value
        std::cout << date << " => " << value << " = " << value * max_->second << std::endl;
    } else {
        it = exchange_rates_.lower_bound(date);
        it--;
        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    }
};
