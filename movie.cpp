#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(std::string category, std::string name, double price, int qty, std::string genre, std::string rating) : 
		Product::Product(category, name, price, qty),
		genre_(genre),
		rating_(rating)
{   }

Movie::~Movie() {  };

std::set<std::string> Movie::keywords() const { //keywords of movie. concatenates into string and parses it.
	std::string key = name_ + ',' + genre_ + ',' + rating_;
	std::set<std::string> words = parseStringToWords(key);
	return words;
}

std::string Movie::displayString() const { //dumping info out to the shits.
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << price_;
	std::string p = stream.str();
	std::string s = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + p + " " + to_string(qty_) + " left.";
	return s;	
}

void Movie::dump(std::ostream& os) const { //dumping info out
	os << category_ << fixed << setprecision(2) << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}