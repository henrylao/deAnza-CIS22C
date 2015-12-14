#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "Date.h"

class Person {
private:
	std::string m_first_name;
	std::string m_last_name;
	Date m_dob;
	bool by_last_name;
	bool by_first_name;
	bool by_dob;

public:
	Person() : m_first_name(""), m_last_name(""), 
		by_last_name(false), by_first_name(false), by_dob(true) {

	}
	Person(std::string f_name, std::string l_name, Date dob) 
		: m_first_name(f_name), m_last_name(l_name), m_dob(dob), 
		by_last_name(false), by_first_name(false), by_dob(true) {

	}
	~Person() {

	}

	std::string getFirstName() {
		return m_first_name;
	}
	std::string getLastName() {
		return m_last_name;
	}
	Date getDOB() {
		return m_dob;
	}

	void byLastName() {
		by_last_name = true;
		by_first_name = false;
		by_dob = false;
	}

	void byFirstName() {
		by_last_name = false;
		by_first_name = true;
		by_dob = false;
	}

	void byDob() {
		by_last_name = false;
		by_first_name = false;
		by_dob = true;
	}

	void setFirstName(std::string f_name) {
		m_first_name = f_name;
	}
	void setLastName(std::string l_name) {
		m_last_name = l_name;
	}
	void setDOB(Date dob) {
		m_dob = dob;
	}

	bool operator== (const Person& rhs) {
		return (m_dob == rhs.m_dob && m_first_name == rhs.m_first_name && m_last_name == rhs.m_last_name);
	}

	bool operator> (const Person& rhs) {
		if (by_first_name){
			return (m_first_name > rhs.m_first_name) 
				|| (m_first_name == rhs.m_first_name && m_last_name > rhs.m_last_name);
		}
		else if (by_last_name) {
			return (m_last_name > rhs.m_last_name)
				|| (m_last_name == rhs.m_last_name && m_first_name > rhs.m_first_name);
		}
		else
			return (m_dob < rhs.m_dob);
	}

	bool operator<= (const Person& rhs) {
		return !(*this > rhs);
	}

	bool operator< (const Person& rhs) {
		if (by_first_name){
			return (m_first_name < rhs.m_first_name)
				|| (m_first_name == rhs.m_first_name && m_last_name < rhs.m_last_name);
		}
		else if (by_last_name) {
			return (m_last_name < rhs.m_last_name)
				|| (m_last_name == rhs.m_last_name && m_first_name < rhs.m_first_name);
		}
		else
			return (m_dob > rhs.m_dob);
	}

	bool operator>= (const Person& rhs) {
		return !(*this < rhs);
	}

	friend std::ostream& operator<< (std::ostream& outs, Person person) {
		outs << person.m_first_name << " " << person.m_last_name << " " << person.m_dob;
		return outs;
	}
};

#endif // PERSON_H