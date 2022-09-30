#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(std::string category,std::string name, double price, int qty, std::string size, std::string brand) :
		Product::Product(category,name, price,qty),
		brand_(brand),
		size_(size)
{   }

Clothing::~Clothing() {  };

std::set<std::string> Clothing::keywords() const {
	std::string key = name_ + ',' + brand_;
	std::set<std::string> words = parseStringToWords(key);
	return words;
}

std::string Clothing::displayString() const {
	std::string s = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return s;
}

void Clothing::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}