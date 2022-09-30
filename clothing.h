#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product {
	public:
		Clothing(const std::string category,const std::string name, double price, int qty, std::string size, std::string brand); //std::string category, std::string name, double price, int qty, isbn, author entered in this order
		
		~Clothing();

		virtual std::set<std::string> keywords() const;

		virtual std::string displayString() const;

		virtual void dump(std::ostream& os) const;
		
	private:
		std::string size_;
		std::string brand_;
};

#endif