#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(std::string category,std::string name, double price, int qty, std::string isbn, std::string author) : 
		Product::Product(category,name,price,qty),
		isbn_(isbn),
		author_(author)
{  }

Book::~Book() {
	
}

std::set<string> Book::keywords() const { //concatenates relevant info and parses it. adds isbn_ separately
	std::string key = name_ + ',' + author_;
	std::set<std::string> words = parseStringToWords(key);
	words.insert(isbn_);
	return words;
}

std::string Book::displayString() const { //concatenates output string in format provided
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << price_;
	std::string p = stream.str();
	std::string s = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + p + " " + to_string(qty_) + " left.";
	return s;
}

void Book::dump(std::ostream& os) const { //dumps product>book info
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << author_ << "\n" << isbn_ << endl;
}

