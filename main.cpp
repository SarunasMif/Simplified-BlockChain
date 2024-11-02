#include <iostream>
#include "includes.h"
#include "gen_hash.h"
#include "blockchain.h"

using namespace std;

vector<Block> Blockchain;

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
    float reserved;
    float available_amount;

    user() : name(""), p_key(""), balance(0.0f), reserved(0.0f), available_amount(0.0f) {}

    user(const string& name, const string& p_key, float balance) :
    name(name), p_key(p_key), balance(balance) { available_amount = balance; }

    void print_user() const {
        cout << "name: " << name << "\n" 
        << "publick_key: " << p_key << "\n"
        << "balance: " << balance << "\n"
        << "reserved: " << reserved << "\n"
        << "available_amount: " << available_amount <<endl;
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

    return id;
}

float get_rnd_float(float min, float max) {
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<float> dis(min, max);

    return dis(gen);
}

void gen_block() {

}

string gen_pkey() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dis(0, 61);

    string public_key;

    do {
        public_key.clear();
        
        for (int i = 0; i < 10; i++) {
            public_key += chars[dis(generator)];
        }
    }while(find(keys.begin(), keys.end(), public_key) != keys.end());

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

        value1 = users[user1].balance - users[user1].reserved;
        // value2 = users[user2].balance - users[user2].reserved;

        cout << "Current value: " << value1 << endl;
        flt_placeholder = get_rnd_float(0.001, value1);
        fee = flt_placeholder * 0.02;

        if (flt_placeholder + fee > value1) {
            while (flt_placeholder + fee > value1) {
                flt_placeholder = get_rnd_float(0.001, value1);
                fee = flt_placeholder * 0.02;
            }
        }

        cout << "reserved_amount: " << users[user1].reserved << " ," 
        << "available amount: " << users[user1].available_amount << "\n" << "\n";
        users[user1].reserved = users[user1].reserved + flt_placeholder + fee;
        users[user1].available_amount = users[user1].available_amount - flt_placeholder - fee;
        cout << "reserved_amount: " << users[user1].reserved << " ," 
        << "available amount: " << users[user1].available_amount << " ," 
        "user: " << user1 << "\n" << "\n";
        
        t_id = get_transactionID(user1, user2, flt_placeholder, fee);

        transaction Transaction(t_id, user1, user2, flt_placeholder, fee);
        transactions[Transaction.transaction_id] = Transaction;

    }
}

int main() {
    vector<string> tx;

    gen_user(2);

    // for (const auto& [id, user] : users) {
    //     user.print_user();
    //     cout << endl;
    // }

    gen_transaction(6);

    cout << endl;

    for (const auto& [id, transaction] : transactions) {
        transaction.print_transaction();
        tx.push_back(transaction.transaction_id);
        cout << endl << endl;
    }

    int verion = 1;
    string prev_hash;
    int diff = 0;

    if (Blockchain.empty()) {
        prev_hash = "";
    }else {
        prev_hash = Blockchain.back().hash;
    }
        

    Block block(verion, tx, prev_hash);

    // for (const auto& [id, user] : users) {
    //     user.print_user();
    //     cout << endl;
    // }

    // string a, b, c;
    // a = "HEllo world";
    // b = "b";
    // c = "c";

    // cout << "string: " << a << "\n"
    // << "hash: " << get_hash(a) << "\n"
    // << "binary: " << get_binary_of_hash(get_hash(a)) << "\n" << "\n";

    // cout << "string: " << b << "\n"
    // << "hash: " << get_hash(b) << "\n"
    // << "binary: " << get_binary_of_hash(get_hash(b)) << "\n" << "\n";

    // cout << "string: " << c << "\n"
    // << "hash: " << get_hash(c) << "\n"
    // << "binary: " << get_binary_of_hash(get_hash(c)) << "\n" << "\n";

    keys.clear();
    system("pause");

}