#include "includes.h"
#include "users.h"

istream& User::readUser(istream& is) {
    is >> balance >> username >> public_key;

    return is;
}

istream& operator>>(istream& set, User& Data) {
    string u_name, u_publick_key;  
    float balance;

    cout << "Enter username and public key: ";
    set >> u_name;
    set >> u_publick_key;

    Data.SetUsername(u_name);
    Data.SetPublicKey(u_publick_key);

    return set;
}

ostream& operator<<(ostream& print, User Data) {
    return print;
}

User::User(const User& Data) : username(Data.username), public_key(Data.public_key), balance(Data.balance) {}
// Copy constructor

User& User::operator=(const User& Data) {
    if (this != &Data) {
        username = Data.username;
        public_key = Data.public_key;
        balance = Data.balance;
    }

    return *this;
}
// Copy assignment operator

User::User(User&& Data) noexcept : username(move(Data.username)), public_key(move(Data.public_key)), balance(move(Data.balance)) {
    Data.username.clear();
    Data.public_key.clear();
    Data.balance = 0;
}
// Move constructor

User& User::operator=(User&& Data) noexcept {
    if (this != &Data) {
        username = move(Data.username);
        public_key = move(Data.public_key);
        balance = move(Data.balance);
        Data.username.clear();
        Data.public_key.clear();
        Data.balance = 0;
    }

    return *this;
}
// Move assignment constructor

User::~User() { };
// Deconstructor