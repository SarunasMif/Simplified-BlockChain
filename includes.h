#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <random>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

class Block;
// Stating that this class does infact exist

struct transaction {

    string transaction_id;
    string sender_pkey;
    string getter_pkey;
    long value;
    long fee;
    // variables

    transaction() : transaction_id(""), sender_pkey(""), getter_pkey(""), value(0.), fee(0.) {}

    transaction(const string& transaction_id, const string& sender_pkey, const string& getter_pkey, long value, long fee) :
    transaction_id(transaction_id), sender_pkey(sender_pkey), getter_pkey(getter_pkey), value(value), fee(fee) {}
    // Constructors

    void print_transaction() const {

        float usd = value;
        usd = usd / 100;

        float usd_f = fee;
        usd_f = usd_f /100;

        cout << "------------------------------------------------------------------------------------" << endl;
         cout << "Transaction_id  | " << transaction_id << " \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Sender_key      | " << sender_pkey << "                                       \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Getter_key      | " << getter_pkey << "                                       \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Value           | " << usd << " USD" << "                                       \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Transaction fee | " << usd_f << " USD" << "                                         \n" 
         << "------------------------------------------------------------------------------------" << endl;
    }
    // Construct functions

}; // construct for transactions

struct user {
    string name;
    string p_key;
    long balance;
    long reserved = 0; // This values keeps track of how much money the user has already allocated for transactions
    // variables

    user() : name(""), p_key(""), balance(0), reserved(0) {}

    user(const string& name, const string& p_key, long balance) :
    name(name), p_key(p_key), balance(balance) {}
    // Constructor

    void print_user() const {
        cout << "name: " << name << "\n" 
        << "publick_key: " << p_key << "\n"
        << "balance: " << balance << "\n"
        << "reserved: " << reserved << "\n";
    }
    // Construct functions
};

extern map<string, transaction> transactions;
extern map<string, user> users;
extern vector<string> keys;
// Declaration that these maps and vector exist, so that we would avoid multipe declarations

string gen_hash(string input);
string get_transactionID(string u1, string u2, long value, long fee);
long get_rnd_long(long min, long max);
string gen_pkey();
void gen_user(int number_of_users);
void gen_transaction(int number_of_transactions);
void mine_blocks();
bool mine_block(int mine_attempt, Block& block);
void erase_transactions(const vector<string>& used_transactions);
void print_transaction(string txo_hash);
void print_block(string block_hash);
int main();
// main.cpp functions

#endif