#include <iostream>
#include "includes.h"
#include "gen_hash.h"

using namespace std;

// TODO: gen transaction_id(), finish gen_transaction()

struct transaction {

    string transaction_id;
    string sender_pkey;
    string getter_pkey;
    float value;

    transaction() : transaction_id(""), sender_pkey(""), getter_pkey(""), value(0.0f) {}

    transaction(const string& transaction_id, const string& sender_pkey, const string& getter_pkey, float value) :
    transaction_id(transaction_id), sender_pkey(sender_pkey), getter_pkey(getter_pkey), value(value) {}

    void print_transaction() const {
         cout << "Transaction_id: " << transaction_id << "\n"
         << "Sender_key: " << sender_pkey << "\n"
         << "Getter_key: " << getter_pkey << "\n"
         << "Value: " << value << "\n";
    }
};

struct user {
    string name;
    string p_key;
    float balance;

    user() : name(""), p_key(""), balance(0.0f) {}

    user(const string& name, const string& p_key, float balance) :
    name(name), p_key(p_key), balance(balance) {}

    void print_user() const {
        cout << "name: " << name << "\n" 
        << "publick_key: " << p_key << "\n"
        << "balance: " << balance << endl;
    }
};

map<string, transaction> transactions;
map<string, user> users;

void reg_block() {

}

void gen_user(int number_of_users) {

    srand(time(NULL));

    string name_temp = "user";
    string p_key_temp = "p_key";

    for (int i = 0; i < number_of_users; i++) {
        name_temp = "user" + to_string(i + 1);
        p_key_temp = "p_key" + to_string(i + 1);
        float balance = rand() % (1000000 - 100 + 1);

        user User(name_temp, p_key_temp, balance);
        users[User.p_key] = User;
    }
}

void gen_transaction(int number_of_transactions) {

    srand(time(NULL));

    string user1, user2, t_id1, t_id2;
    int u1, u2;
    float flt_placeholder, value1, value2;

    for (size_t i = 0; i < number_of_transactions; i++) {

        u1 = rand() % (users.size());
        u2 = u1;

        do {
            u2 = rand() % (users.size());
        }while (u2 == u1);

        user1 = "p_key" + to_string(u1);
        user2 = "p_key" + to_string(u2);

        value1 = users[user1].balance;
        value2 = users[user2].balance;

        cout << "user1: " << user1 << "\n"
        << "value1: " << value1 << "\n";

        cout << "user2: " << user2 << "\n"
        << "value2: " << value2 << "\n";

    }
}

int main() {

    gen_user(5);

    for (const auto& [id, user] : users) {
        user.print_user();
        cout << endl;
    }

    gen_transaction(2);

    system("pause");

}