#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */

class MyDataStore : public DataStore
{
public:
  virtual ~MyDataStore();

  /**
   * Adds a product to the data store
   */
  void addProduct(Product *p);

  /**
   * Adds a user to the data store
   */
  void addUser(User *u);

  void addCart(User *u, Product *p);
  void buyCart(User *u);
  void viewCart(User *u);

  User* getUser(const std::string& username);

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
  virtual std::vector<Product *> search(std::vector<std::string> &terms, int type);

  /**
   * Reproduce the database file from the current Products and User values
   */
  virtual void dump(std::ostream &ofile);

private:
  std::vector<Product *> products_;
  std::vector<User *> users_;
  std::map<User *, std::vector<Product *>> userCarts;
};

#endif