#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "db_parser.h"
#include "datastore.h"

class myDataStore : public DataStore {
	public:
			myDataStore() {};
			~myDataStore() {};
			/**
			* Adds a product to the data store
			*/
			virtual void addProduct(Product* p);

			/**
			* Adds a user to the data store
			*/
			virtual void addUser(User* u);
			/**
			* Performs a search of products whose keywords match the given "terms"
			*  type 0 = AND search (intersection of results for each term) while
			*  type 1 = OR search (union of results for each term)
			*/
			virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

			/**
			* Reproduce the database file from the current Products and User values
			*/
			virtual void dump(std::ostream& ofile);

			virtual void addToCart(std::string username, Product* p);

			virtual void viewCart(std::string username);

			virtual void buyCart(std::string username);

			virtual bool getUser(std::string username);
			virtual void clearProductsAndUsers();

		private:
			std::map<std::string, User*> users;
			std::map<std::string, std::vector<Product*>> userCart;
			std::vector<Product*> productList;
			std::map<std::string, std::set<Product*>> productKeyMap;
			

		
};
#endif