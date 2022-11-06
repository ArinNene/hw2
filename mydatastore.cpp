#include "mydatastore.h"

using namespace std;

/**
	* Adds a product to the data store
	*/
void myDataStore::addProduct(Product* p) {
	productList.push_back(p);
	std::set<std::string>::iterator it;
	std::set<std::string> key = p->keywords();
	for (it = key.begin(); it != key.end(); ++it) {
		if (productKeyMap.find(*it) == productKeyMap.end()) { //keyword not registered
			std::set<Product*> keyList;
			keyList.insert(p);
			productKeyMap.insert({*it, keyList});
		}
		else { //keyword already registered
			productKeyMap[*it].insert(p);
		}
	}

}

/**
	* Adds a user to the data store
	*/
void myDataStore::addUser(User* u) { //add a user and initialize their cart to an empty one.
	
	users.insert({convToLower(u->getName()),u});
	std::vector<Product*> cart = {};
	userCart.insert({u->getName(),cart});

}

/**
	* Performs a search of products whose keywords match the given "terms"
	*  type 0 = AND search (intersection of results for each term) while
	*  type 1 = OR search (union of results for each term)
	*/
std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int type) { //returns hits as output. When you're running this function, use string parse to get key words and eliminate AND/OR. Use separate cins to separate AND/OR from keywords.
	std::vector<Product*> processed_hits;
	if (terms.size() == 0) { //no terms
		return processed_hits; //empty processed hits
	}
	std::set<Product*> raw_hits = {};
	std::set<Product*> temp = {}; //setUnion processing

	if (type) { //OR SEARCH. if type == 1, then if is true.
		std::vector<std::string>::iterator it; 
		for (it = terms.begin(); it != terms.end(); ++it) { //iterating through input
			if (productKeyMap.find(*it) != productKeyMap.end()) { //If the key can be found in keymap 			
				temp = setUnion(raw_hits, productKeyMap[*it]); //combine empty set and new set
				raw_hits = temp;
			}
		}
		std::set<Product*>::iterator setIt;
		for (setIt = raw_hits.begin(); setIt != raw_hits.end(); ++setIt) {
			processed_hits.push_back(*setIt); //taking the raw hits set and pushing it into processed hits for return
		}
		return processed_hits;
	}
	else { //AND SEARCH. if type == 0, if is false and else is triggered. use set intersection. 
		std::vector<std::string>::iterator it;
		it = terms.begin();
		raw_hits = setUnion(raw_hits,productKeyMap[*it]); //initialize raw hits with some terms. Note that all end hits must have all user-specified key terms, so order in which products are added to raw hits wont matter.
		++it;
		while (it != terms.end()) { //running through input terms
			if (productKeyMap.find(*it) != productKeyMap.end()) { //If the term has products, add it to raw hits
				raw_hits = setIntersection(raw_hits, productKeyMap[*it]); //intersection
			}
			 ++it;
		}
		std::set<Product*>::iterator setIt; 
		for (setIt = raw_hits.begin(); setIt != raw_hits.end(); ++setIt) {
			processed_hits.push_back(*setIt); //push results to correct return format and send it out.
		}
		return processed_hits;
	}
	
	return processed_hits;
}

void myDataStore::addToCart(std::string username, Product* product) { //when calling, call it as hits[index-1].
	//maintain FIFO order. 
	if (!product || !users[username]) {
		cout << "Invalid request." << endl;
		return; //If there's no valid product or the user doesn't exist, this is an invalid request.
	}
	else {
		userCart[username].push_back(product); //vector push_back is matched by erase to maintain fifo order when buying cart. note that the hits_result number must be cleaned in main
	}
}

void myDataStore::viewCart(std::string username) {
	std::vector<Product*>::iterator it;
	if (users.find(username) == users.end()) { //Invalid username?
		cout << "Invalid username." << endl;
		return;
	}
	else if (userCart[username].size() == 0) { //Empty cart?
		cout << "Cart is empty." << endl;
	}
	int i = 1;
	for (it = userCart[username].begin(); it != userCart[username].end(); ++it) { //Iterate through the user's cart and dump the info to cout.
		cout << "Item " << i << endl; 
		cout << (*it)->displayString() << endl;
		cout << endl;
		i++;
	}
}

void myDataStore::buyCart(std::string username) {
	if (!users[username] || userCart[username].size() == 0) { //Invalid user or empty cart can't buy cart.
		cout << "Invalid request." << endl;
	}
	else {
		std::vector<Product*> copyCart = userCart[username]; //operate on a copy cart to avoid weird mem issues
		std::vector<Product*> remainsCart;
		std::vector<Product*>::iterator it;

		for (it = copyCart.begin(); it != copyCart.end(); ++it) { //iterate through copy

			int bal = users[username]->getBalance(); //store balance to variable
			double price = (*it)->getPrice(); //store price to variable
			if (bal < price || (*it)->getQty() < 1) { //If the purchase can't be made, the item should remain in cart.
				remainsCart.push_back(*it);
			}
			else { //successful transaction! Money leaves user's account and quantity of available items reduces by 1.
				users[username]->deductAmount((*it)->getPrice());
				(*it)->subtractQty(1);
			}
			copyCart.erase(it);
			it--;
		}
		userCart[username] = remainsCart; //slatt
	}
}

bool myDataStore::getUser(std::string username) {

	//return (bool)users[username];
	if (users.find(username) == users.end()) {
		return false;
	}
	else {
		return true;
	}

}

void myDataStore::clearProductsAndUsers() {
	//super important. 
	//Clears all dynamic memory allocated to all user and product objects. 
	//Uses the lists of users and products in datastore 
	//to access and delete the objects themselves. 
	//Call at end of main.
	for (unsigned int i = 0; i < productList.size(); i++) {
		delete productList[i];
	}
	std::map<std::string, User*>::iterator it;
	for (it = users.begin(); it != users.end(); ++it) {
		delete it->second;
	}
}

/**
	* Reproduce the database file from the current Products and User values
	*/
void myDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << endl;
	std::vector<Product*>::iterator it;
	for (it = productList.begin(); it != productList.end(); ++it) { //iterate through product list
		(*it)->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	std::map<std::string, User*>::iterator itB;
	for (itB = users.begin(); itB != users.end(); ++itB) { //iterate through user b
		(*itB).second->dump(ofile);
	}
	ofile << "</users>" << endl;
}