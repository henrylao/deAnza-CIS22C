// Thomas Tang 
// Yuan Zheng
// CIS22C Lab1 Bag Project
// Wallet.h

#ifndef _WALLET
#define _WALLET
#include "BagInterface.h"

template <class ItemType>
class Wallet : public BagInterface<ItemType> {
public:
	Wallet(); // constructor
	~Wallet(); // destructor

	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	int getFrequencyOf(const ItemType& anEntry) const;
	bool contains(const ItemType& anEntry) const;

	std::vector<ItemType> toVector() const;

	//========= Debug Methods ========================
	void printAddedEntries();
	void printRemovedEntries();
	void printTotals();
	// ======== / Debug Methods ======================


private:
	// m_Entries are data entries
	// used to check if currency exists
	// used to display total / frequency
	// used to hold each entrie
	struct m_Entries {
		std::string Name; // name to specify what kind of currency
		ItemType Total = ItemType(" ", 0, 0, " "); // to keep a running total of a certain currency
		std::vector<ItemType> AddedEntries; // to keep track of added entries
		std::vector<ItemType> RemovedEntries; // to keep track of removed entries
	};

	// m_Data is a vector that holds m_Entries 
	std::vector<m_Entries> m_Data;

}; // end class definition

// Debug Methods
template<class ItemType>
void Wallet<ItemType>::printAddedEntries() {
	std::cout << "Added Entries:\n";
	for (unsigned int i = 0; i < m_Data.size(); i++){
		for (unsigned int j = 0; j < (m_Data[i].AddedEntries).size(); j++) {
			std::cout << "+ " << m_Data[i].AddedEntries[j] << std::endl;
		}
	}
}
template<class ItemType>
void Wallet<ItemType>::printRemovedEntries() {
	std::cout << "Removed Entries:\n";
	for (unsigned int i = 0; i < m_Data.size(); i++){
		for (unsigned int j = 0; j < (m_Data[i].RemovedEntries).size(); j++) {
			std::cout << "- " << m_Data[i].RemovedEntries[j] << std::endl;
		}
	}
}
template<class ItemType>
void Wallet<ItemType>::printTotals() {
	std::cout << "Totals:\n";
	for (unsigned int i = 0; i < m_Data.size(); i++){
		std::cout << "  " << m_Data[i].Total << std::endl;
	}
}
// /Debug Methods

// constructor
template <class ItemType>
Wallet<ItemType>::Wallet() {}


// destructor 
template <class ItemType>
Wallet<ItemType>::~Wallet() {}


// return number of currencyTypes currently in the wallet
template <class ItemType>
int Wallet<ItemType>::getCurrentSize() const {
	return m_Data.size();
}


// check if the wallet is empty (check if the wallet contains any money)
// a wallet is empty if it contains no types of currency
// ASSUME THAT a wallet is empty if it has negative money
template <class ItemType>
bool Wallet<ItemType>::isEmpty() const {
	if (m_Data.empty())
		return true;
	for (unsigned int i = 0; i < m_Data.size(); ++i) {
		ItemType total = m_Data[i].Total;
		if (total > ItemType()) {
			return false;
		}
	}
	return false;
}


// adds a new entry into the wallet.
// if the currency exists, add value to total value
//   and add the entry into a list of added values, then return true
// if currency does not exist, add new entry 
//   and currency type into the wallet, make the total equal to the value
//   and return false
template <class ItemType>
bool Wallet<ItemType>::add(const ItemType& newEntry) {
	for (unsigned int i = 0; i < m_Data.size(); ++i) {
		if (m_Data[i].Name == newEntry.getCurrencyName()) {
			(m_Data[i].AddedEntries).push_back(newEntry);
			m_Data[i].Total = m_Data[i].Total + newEntry;
			return true;
		}
	}
	m_Entries entry;
	entry.Name = newEntry.getCurrencyName();
	(entry.AddedEntries).push_back(newEntry);
	entry.Total = newEntry;
	m_Data.push_back(entry);
	return false;
}


// removes an entry from the wallet
// if currency to remove does not exist, return false
// if currency to remove does exist, remove from total 
//   if is the exact amount as an added entry, remove from added entries list 
//   otherwise, add to removed entries list
template <class ItemType>
bool Wallet<ItemType>::remove(const ItemType& anEntry) {
	for (unsigned int curType = 0; curType < m_Data.size(); ++curType) {
		if (m_Data[curType].Name == anEntry.getCurrencyName()) {
			m_Data[curType].Total = m_Data[curType].Total - anEntry;
			/*for (unsigned int entry = 0; entry < (m_Data[curType].AddedEntries).size(); ++entry) {
			ItemType c = (m_Data[curType].AddedEntries)[entry];
			if (c == anEntry) {
			(m_Data[curType].AddedEntries).erase((m_Data[curType].AddedEntries).begin() + entry);
			return true;
			}
			}*/
			ItemType c = anEntry;
			(m_Data[curType].RemovedEntries).push_back(c - (c + c));
			return true;
		}
	}
	return false;
}


// clears the wallet of any data 
// empties the wallet
template <class ItemType>
void Wallet<ItemType>::clear() {
	m_Data.clear();
}


// returns the amount of times an entry of a certain type has been added
template <class ItemType>
int Wallet<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
	for (unsigned int i = 0; i < m_Data.size(); ++i) {
		if (m_Data[i].Name == anEntry.getCurrencyName())
			return (m_Data[i].AddedEntries).size();
	}
	return 0;
}


// a wallet contains the entry if it has the same kind of entry 
//   and if the entry is less than or equal to the total ammount
// eg. a wallet does NOT contain $5.50 if it has a total of $4.00
//   but a wallet DOES contain $5.50 if it has a total of $6.00
template <class ItemType>
bool Wallet<ItemType>::contains(const ItemType& anEntry) const {
	for (unsigned int i = 0; i < m_Data.size(); ++i) {
		if (m_Data[i].Name == anEntry.getCurrencyName()){
			ItemType total = m_Data[i].Total;
			return (total > anEntry || total == anEntry);
		}
	}
	return false;
}



template <class ItemType>
std::vector<ItemType> Wallet<ItemType>::toVector() const {
	std::vector<ItemType> toReturn;
	for (unsigned int x = 0; x < m_Data.size(); ++x) {
		toReturn.push_back(m_Data[x].Total);
	}
	/*
	for (unsigned int i = 0; i < m_Data.size(); ++i) {
	// add all added entries to vector
	for (unsigned int j = 0; j < (m_Data[i].AddedEntries).size(); ++j) {
	toReturn.push_back(m_Data[i].AddedEntries[j]);
	}
	// add all removed entries to vector
	for (unsigned int k = 0; k < (m_Data[i].RemovedEntries).size(); ++k) {
	toReturn.push_back(m_Data[i].RemovedEntries[k]);
	}
	}*/
	return toReturn;
}


#endif // _WALLET


