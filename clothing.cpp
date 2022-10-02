#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(std::string category,std::string name, double price, int qty, std::string size, std::string brand) :
		Product::Product(category,name, price,qty),
		brand_(brand),
		size_(size)
{   }

Clothing::~Clothing() {  };

std::set<std::string> Clothing::keywords() const { //concatenates all relevant info
	std::string key = name_ + ',' + brand_;
	std::set<std::string> words = parseStringToWords(key);
	return words;
}

std::string Clothing::displayString() const { //concatenates all relevant info
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << price_;
	std::string p = stream.str();	
	std::string s = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + p + " " + to_string(qty_) + " left.";
	return s;
}

void Clothing::dump(std::ostream& os) const { //dumps all relevant info to os
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}