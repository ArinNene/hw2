#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(std::string category, std::string name, double price, int qty, std::string genre, std::string rating) : 
		Product::Product(category, name, price, qty),
		genre_(genre),
		rating_(rating)
{   }

Movie::~Movie() {  };

std::set<std::string> Movie::keywords() const {
	std::string key = name_ + ',' + genre_ + ',' + rating_;
	std::set<std::string> words = parseStringToWords(key);
	return words;
}

std::string Movie::displayString() const {
	std::string s = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return s;	
}

void Movie::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}