#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <ctime>
#include <random>
#include <sstream>
#include <algorithm>


using namespace std;

struct transaction {

    string transaction_id;
    string sender_pkey;
    string getter_pkey;
    long value;
    long fee;

    transaction() : transaction_id(""), sender_pkey(""), getter_pkey(""), value(0.0f), fee(0.0f) {}

    transaction(const string& transaction_id, const string& sender_pkey, const string& getter_pkey, long value, long fee) :
    transaction_id(transaction_id), sender_pkey(sender_pkey), getter_pkey(getter_pkey), value(value), fee(fee) {}

    void print_transaction() const {
         cout << "Transaction_id: " << transaction_id << "\n"
         << "Sender_key: " << sender_pkey << "\n"
         << "Getter_key: " << getter_pkey << "\n"
         << "Value: " << value << "\n"
         << "Fee: " << fee << endl;
    }
};

struct user {
    string name;
    string p_key;
    long balance;
    long reserved;

    user() : name(""), p_key(""), balance(0.0f), reserved(0.0f) {}

    user(const string& name, const string& p_key, long balance) :
    name(name), p_key(p_key), balance(balance) {}

    void print_user() const {
        cout << "name: " << name << "\n" 
        << "publick_key: " << p_key << "\n"
        << "balance: " << balance << "\n"
        << "reserved: " << reserved << "\n";
    }
};

extern map<string, transaction> transactions;
extern map<string, user> users;
extern vector<string> keys;

string gen_hash(string input);
string get_transactionID(string u1, string u2, long value, long fee);
long get_rnd_float(long min, long max);
string gen_pkey();
void gen_user(int number_of_users);
void gen_transaction(int number_of_transactions);
int main();