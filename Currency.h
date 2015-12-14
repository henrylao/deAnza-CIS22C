// Thomas Tang 
// Yuan Zheng
// CIS22C Lab1 Bag Project
// Currency.h


#ifndef _CURRENCY
#define _CURRENCY
#include <iostream>
#include <sstream>
#include <string>

class Currency {
public:
	/*
	enum currencyType { Dollar, Euro, Franc, Peso,
	Pound, Rubel, Rupee, Shilling, Won, Yen, Yuan
	};
	enum currencySubType{Cents, Cents, Centimes, Centavos,
	Pence, Kopeks, Paise, Cents, Chon, Sen, Fen
	};
	Currency(currencyType curName, int wholePart,
	int fractPart, currencySubType fractName);
	*/
	Currency();
	Currency(std::string curName, int wholePart, int fractPart, std::string fractName);
	~Currency();

	std::string getCurrencyName() const;
	bool operator== (const Currency& rhs);
	bool operator!=	(const Currency& rhs);
	bool operator<	(const Currency& rhs);
	bool operator>	(const Currency& rhs);

	Currency operator+ (const Currency& rhs);
	Currency operator- (const Currency& rhs);

	friend std::ostream& operator<< (std::ostream& os, const Currency& currency);

private:
	std::string m_currencyName;
	int m_wholeParts;
	int m_fractionalParts;
	std::string m_fractionalName;
};



Currency::Currency() : m_currencyName(""), m_wholeParts(0), m_fractionalParts(0), m_fractionalName("") {
}

Currency::Currency(std::string curName, int wholePart, int fractPart, std::string fractName)
: m_currencyName(curName), m_wholeParts(wholePart), m_fractionalParts(fractPart), m_fractionalName(fractName) {
}



Currency::~Currency() {
}


//returns the name of the currency
std::string Currency::getCurrencyName() const {
	return m_currencyName;
}


// checks if currencies are equal. both names and values
bool Currency::operator== (const Currency& rhs) {
	if (&rhs == this) return true;
	if (m_currencyName == rhs.m_currencyName
		&& m_fractionalName == rhs.m_fractionalName) {
		if (m_wholeParts == rhs.m_wholeParts
			&& m_fractionalParts == rhs.m_fractionalParts){
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}


// checks if currencies are not equal. both names and values
bool Currency::operator!= (const Currency& rhs) {
	return !(*this == rhs);
}

// only checks if the values are higher, 
// not if the currency names are the same
bool Currency::operator> (const Currency& rhs){
	if (m_wholeParts > rhs.m_wholeParts) {
		return true;
	}
	else if (m_wholeParts == rhs.m_wholeParts) {
		if (m_fractionalParts > rhs.m_fractionalParts)
			return true;
		else
			return false;
	}
	else
		return false;
}


// only checks if the values are lower, 
// not if the currency names are the same
bool Currency::operator< (const Currency& rhs) {
	if (m_wholeParts < rhs.m_wholeParts) {
		return true;
	}
	else if (m_wholeParts == rhs.m_wholeParts) {
		if (m_fractionalParts < rhs.m_fractionalParts)
			return true;
		else
			return false;
	}
	else
		return false;
}

// adds currencies of the same name, if not the same do nothing
Currency Currency::operator+ (const Currency& rhs) {
	Currency sum(m_currencyName, m_wholeParts, m_fractionalParts, m_fractionalName);
	// add fractional parts .. if over 100, add 1 to whole parts
	if (sum.m_currencyName == rhs.m_currencyName) {
		if ((sum.m_fractionalParts += rhs.m_fractionalParts) >= 100) {
			sum.m_fractionalParts -= 100;
			sum.m_wholeParts++;
		}
		sum.m_wholeParts += rhs.m_wholeParts; // add whole parts
	}
	return sum; // return a copy of the sum
}


// subtracts currencies of the same name, if not the same do nothing
Currency Currency::operator- (const Currency& rhs) {
	Currency diff(m_currencyName, m_wholeParts, m_fractionalParts, m_fractionalName);
	// substract fractional parts .. if rhs > this :. sub 1 from whole parts
	if (diff.m_currencyName == rhs.m_currencyName) {
		if (rhs.m_fractionalParts > m_fractionalParts) {
			diff.m_wholeParts--;
			diff.m_fractionalParts += 100;
			diff.m_fractionalParts -= rhs.m_fractionalParts;
		}
		else {
			diff.m_fractionalParts -= rhs.m_fractionalParts;
		}
		diff.m_wholeParts -= rhs.m_wholeParts; // subtract whole parts
	}
	return diff; // return a copy of the difference
}



// when used with std::cout..
// will print : "currency name, whole parts, frac parts, fracitonal name"
std::ostream& operator<<(std::ostream& os, const Currency& currency) {
	os << currency.m_currencyName << ", " << currency.m_wholeParts << ", " << currency.m_fractionalParts
		<< ", " << currency.m_fractionalName;
	return os;
}

#endif // _CURRENCY