#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Person.h"
#include "BinarySearchTree.h"

class Database {
private:
	BinarySearchTree<Person> m_bst;
	std::string m_infile;

protected:
	void ClearTemp() {
		std::ofstream outfile;
		outfile.open("temp.txt");
		outfile << "";
		outfile.close();
	}


	Date StringToDate(std::string str_date){
		Date date;
		std::istringstream iss1(str_date.substr(0, 2));
		iss1 >> date.month;
		std::istringstream iss2(str_date.substr(3, 2));
		iss2 >> date.day;
		std::istringstream iss3(str_date.substr(6, 4));
		iss3 >> date.year;
		return date;
	}

	void FileToPersonBST(std::string fileName, char sort_by){
		std::ifstream infile;
		infile.open(fileName);
		std::string line;
		for (std::string line; getline(infile, line);) {
			std::istringstream ss(line);
			Person entry;
			switch (sort_by) {
			case 'f':
				entry.byFirstName();
				break;
			case 'l':
				entry.byLastName();
				break;
			case 'd':
				entry.byDob();
				break;
			default:
				entry.byDob();
				break;
			}
			std::string first, last, date;
			ss >> first >> last >> date;

			entry.setFirstName(first);
			entry.setLastName(last);
			entry.setDOB(StringToDate(date));
			m_bst.add(entry);
		}
		infile.close();
	}

	char initialCommand(std::string filename) {
		char input = 'x';
		std::cout << "ENTER...\n  q: to quit;\n  l: to sort by last name;\n  f: to sort by first name;\n  d: to sort by date of birth; \n  any other char: to sort by date of birth;\n";
		std::cin >> input;
		if (input != 'q'){
			FileToPersonBST(filename, input);
		}
		return input;
	}

	void removeCommand() {
		std::string first, last, date;
		std::cout << "Enter entry to remove: \n";
		std::cout << "First Name: \n";
		std::cin >> first;
		std::cout << "Last Name: \n";
		std::cin >> last;
		std::cout << "Date of Birth[mm/dd/yyyy] ... ex. Feb. 14, 1922 => 02/14/1922: \n";
		std::cin >> date;

		Person toFind;
		toFind.setFirstName(first);
		toFind.setLastName(last);
		toFind.setDOB(StringToDate(date));
		if (m_bst.contains(toFind)) {
			m_bst.remove(toFind);
		}
		else {
			std::cout << "Sorry, that entry does not exist in the database";
		}
	}

	void listCommand(std::string fileName) {
		char choice;
		std::cout << "List all whose...\n  f: First name is;\n  l: Last name is;\n  m: born in this month;\n  y: born in this year;\n";
		std::cin >> choice; 

		std::string n;
		int d;
		switch (choice) {
		case 'f':
			std::cout << "Enter first name: ";
			std::cin >> n;
			break;
		case 'l':
			std::cout << "Enter last name: ";
			std::cin >> n;
			break;
		case 'm':
			std::cout <<"Enter month[1 - 12] : ";
			std::cin >> d;
			break;
		case 'y':
			std::cout << "Enter year: ";
			std::cin >> d;
			break;
		default:
			break;
		}

		m_bst.clear();

		std::ifstream infile;
		infile.open(fileName);
		std::string line;

		for (std::string line; getline(infile, line);) {
			std::istringstream ss(line);
			Person entry;
			std::string first, last, date;
			ss >> first >> last >> date;
			entry.setFirstName(first);
			entry.setLastName(last);
			entry.setDOB(StringToDate(date)); switch (choice) {
			case 'f':
				if (entry.getFirstName() == n) {
					m_bst.add(entry);
				}
				break;
			case 'l':
				if (entry.getLastName() == n) {
					m_bst.add(entry);
				}
				break;
			case 'm':
				if (entry.getDOB().month == d){
					m_bst.add(entry);
				}
				break;
			case 'y':
				if (entry.getDOB().year == d) {
					m_bst.add(entry);
				}
			default:
					m_bst.add(entry);
				break;
			}
		}
		infile.close();
	}

	char secondaryCommand(void visit(Person&), void ToTemp(Person&)) {
		
		std::string input;
		std::cout << "\nCommands...\n  q: to quit;\n  r: to remove an entry;\n  rs: to resort;\n  o: to print original text input;\n  p: to print tree\n  in: to print inorder;\n  pre: to print preorder;\n  post: to print postorder;\n  bf: to print breadth first;\n  li: list according to... \n  anything else: to print breadth first;\n";
		std::cin >> input;

		if (input == "q") {
			return 'q';
		}
		else if (input == "li") {
			listCommand(m_infile);
		}
		else if (input == "r") {
			removeCommand();
		}
		else if (input == "p"){
			std::cout << "PRINTING TREE:\n";
			m_bst.print();
		}
		else if (input == "rs") {
			ClearTemp();
			m_bst.breadthFirstTraverse(ToTemp);
			m_bst.clear();
			initialCommand("temp.txt");
		}
		else if (input == "o") {
			std::ifstream infile;
			infile.open(m_infile);
			std::string line;
			std::cout << "ORIGINAL: \n";
			for (std::string line; getline(infile, line);){
				std::cout << line << std::endl;
			}
		}
		else if (input == "in") {
			std::cout << "INORDER: \n";
			m_bst.inorderTraverse(visit);
		}
		else if (input == "pre") {
			std::cout << "PREORDER: \n";
			m_bst.preorderTraverse(visit);
		}
		else if (input == "post") {
			std::cout << "POSTORDER: \n";
			m_bst.postorderTraverse(visit);
		}
		else {
			std::cout << "BREADTH FIRST: \n";
			m_bst.breadthFirstTraverse(visit);
		}
		return 'x';
	}

public:
	Database(std::string filename) : m_infile(filename) {
	}

	char QueryLoop(void visit(Person&), void toTemp(Person&)) {
		if (initialCommand(m_infile) != 'q'){
			while (secondaryCommand(visit, toTemp) != 'q'){}
		}
		return 'q';
	}

	void Output(void visit1(Person&), void visit2(Person&)) {
		m_bst.clear();
		FileToPersonBST(m_infile, 'd');
		std::cout << "PRINTING TREE:\n";
		m_bst.print();

		std::cout << "\nwriting tree to 'BirthdayOutput.txt' by postorder traversal...\n";
		m_bst.postorderTraverse(visit1);

		std::cout << "\nwriting tree to 'NameOutput.txt' by breadth first traversal...\n";
		m_bst.breadthFirstTraverse(visit2);
	}
};

#endif // DATABASE_H