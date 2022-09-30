#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(std::string category,std::string name, double price, int qty, std::string isbn, std::string author) : 
		Product::Product(category,name,price,qty),
		isbn_(isbn),
		author_(author)
{  }

Book::~Book() {

}

std::set<string> Book::keywords() const {
	std::string key = name_ + ',' + author_;
	std::set<std::string> words = parseStringToWords(key);
	words.insert(isbn_);
	return words;
}

std::string Book::displayString() const {
	std::string s = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return s;
}

void Book::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << author_ << "\n" << isbn_ << endl;
}

