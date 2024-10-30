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
    float fee;

    transaction() : transaction_id(""), sender_pkey(""), getter_pkey(""), value(0.0f), fee(0.0f) {}

    transaction(const string& transaction_id, const string& sender_pkey, const string& getter_pkey, float value, float fee) :
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

string gen_hash(string input) {
    string hash = get_hash(input);

    return hash;
}

string get_transactionID(string u1, string u2, float value, float fee) {
    string id;
    id = u1 + u2 + to_string(value) + to_string(fee);

    id = gen_hash(id);

    return id;
}

float get_rnd_float(float min, float max) {
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<float> dis(min, max);

    return dis(gen);
}

void reg_block() {

}

void gen_user(int number_of_users) {

    srand(time(NULL));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(100, 100000);

    string name_temp = "user";
    string p_key_temp = "p_key";

    for (int i = 0; i < number_of_users; i++) {
        name_temp = "user" + to_string(i + 1);
        p_key_temp = "p_key" + to_string(i + 1);
        float balance = dis(gen);

        user User(name_temp, p_key_temp, balance);
        users[User.p_key] = User;
    }
}

void gen_transaction(int number_of_transactions) {

    srand(time(NULL));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, users.size() - 1);

    string user1, user2, t_id;
    int u1, u2;
    float flt_placeholder, value1, value2, fee;

    for (size_t i = 0; i < number_of_transactions; i++) {

        do {
            u1 = dis(gen);
            u2 = dis(gen);
        }while (u2 == u1);

        user1 = "p_key" + to_string(u1);
        user2 = "p_key" + to_string(u2);

        value1 = users[user1].balance;
        value2 = users[user2].balance;

        // cout << "user1: " << user1 << "\n"
        // << "value1: " << value1 << "\n";

        // cout << "user2: " << user2 << "\n"
        // << "value2: " << value2 << "\n";

        flt_placeholder = get_rnd_float(0.0001, value1);
        fee = flt_placeholder * 0.02;

        value1 = value1 - flt_placeholder - fee;
        value2 += flt_placeholder;

        users[user1].balance = value1;
        users[user2].balance = value2;

        t_id = get_transactionID(user1, user2, flt_placeholder, fee);

        transaction Transaction(t_id, user1, user2, flt_placeholder, fee);
        transactions[Transaction.transaction_id] = Transaction;

        cout << "transaction generated: " << i << endl;
    }
}

int main() {

    gen_user(5);

    for (const auto& [id, user] : users) {
        user.print_user();
        cout << endl;
    }

    gen_transaction(5);

    cout << endl;

    for (const auto& [id, transaction] : transactions) {
        transaction.print_transaction();
        cout << endl << endl;
    }

    system("pause");

}