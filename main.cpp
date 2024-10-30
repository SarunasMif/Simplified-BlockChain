#include <iostream>
#include "includes.h"
#include "gen_hash.h"

using namespace std;

// 

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
vector<string> keys;

string gen_hash(string input) {
    string hash = get_hash(input);

    return hash;
}

string get_transactionID(string u1, string u2, float value, float fee) {
    string id;
    id = to_string(value) + to_string(fee) + u1 + u2;

    id = gen_hash(id);

    cout << "Transaction_id: " << id << endl;
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

string gen_pkey() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dis(0, 9);

    string public_key;

    for (int i = 0; i < 10; i++) {
        public_key += chars[dis(generator)];
    }

    keys.push_back(public_key);

    return public_key;
}

void gen_user(int number_of_users) {

    // srand(time(NULL));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(100, 100000);

    string name_temp;
    string p_key_temp;

    for (int i = 0; i < number_of_users; i++) {
        name_temp = "user" + to_string(i + 1);
        p_key_temp = gen_pkey();
        float balance = dis(gen);

        user User(name_temp, p_key_temp, balance);
        users[User.p_key] = User;
    }
}

void gen_transaction(int number_of_transactions) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, users.size() - 1);

    string user1, user2, t_id;
    int u1, u2;
    float flt_placeholder, value1, value2, fee;

    for (size_t i = 0; i < number_of_transactions; i++) {

        do {
            user1 = keys[dis(gen)];
            user2 = keys[dis(gen)];
        }while (user2 == user1);

        value1 = users[user1].balance;
        value2 = users[user2].balance;

        flt_placeholder = get_rnd_float(0.001, value1);
        fee = flt_placeholder * 0.02;

        t_id = get_transactionID(user1, user2, flt_placeholder, fee);

        transaction Transaction(t_id, user1, user2, flt_placeholder, fee);
        transactions[Transaction.transaction_id] = Transaction;

        cout << "transaction generated: " << i << endl;
        cout << "map size: " << transactions.size() << endl;
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

    cout << transactions.size() << endl;
    cout << keys[0] << endl;

    system("pause");

}