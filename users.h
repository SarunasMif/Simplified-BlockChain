#ifndef USER_H
#define USER_H

#include "includes.h"

using namespace std;

class User{
private:
    float balance;
    string username;
    string public_key;
public:
    User() : balance(0) { }
    User(const string& name, const string& user_public_key, float user_balance) : username(name), public_key(user_public_key), balance(user_balance) {}
    // Constructors

    string get_username() const { return username; }
    string get_publicKey() const { return public_key; }
    float get_balance() const { return balance; }
    // Getters

    void SetUsername(string name){ username = name;}
    void SetPublicKey(string user_public_key){ public_key = user_public_key;}
    void SetBalance(float user_balance){balance = user_balance;}
    // Setters

    istream& readUser(istream&);

    ~User();
    User(const User& Data); // Copy constructor
    User& operator=(const User& Data); // Copy assignment operator
    User(User&& Data) noexcept; // Move constructor
    User& operator=(User&& Data) noexcept; // Move assignment operator
    // Rule of five
};

istream& operator>>(istream& set, User& Data);
ostream& operator<<(ostream& print, User Data);

#endif