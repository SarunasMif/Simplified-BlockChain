#include <iostream>
#include "includes.h"
#include "gen_hash.h"
#include "block.h"

using namespace std;

vector<Block> Blockchain;

map<string, transaction> transactions; // kai blokas iskastas is cia istrint transakcijas
map<string, user> users;
vector<string> keys;
vector<string> all_txo;

string gen_hash(string input) {
    string hash = get_hash(input);

    return hash;
}

string get_transactionID(string u1, string u2, long value, long fee) {
    string id;
    id = to_string(value) + to_string(fee) + u1 + u2;

    id = gen_hash(id);

    return id;
}

long get_rnd_float(long min, long max) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<long> dis(min, max);

    return dis(gen);
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

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(100, 100000);

    string name_temp;
    string p_key_temp;

    for (int i = 0; i < number_of_users; i++) {
        name_temp = "user" + to_string(i + 1);
        p_key_temp = gen_pkey();
        long balance = dis(gen);

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
    long flt_placeholder, value1, value2, fee;

    for (size_t i = 0; i < number_of_transactions; i++) {

        // cout << "Generating transaction: " << i + 1 << endl;

        do {
            user1 = keys[dis(gen)];
            user2 = keys[dis(gen)];
        }while (user2 == user1);

        value1 = users[user1].balance - users[user1].reserved;
        // value2 = users[user2].balance - users[user2].reserved;

        // cout << "Current value: " << value1 << endl;
        flt_placeholder = get_rnd_float(10, value1);
        fee = flt_placeholder * 0.1;

        if (flt_placeholder + fee > value1) {
            while (flt_placeholder + fee > value1) {
                flt_placeholder = get_rnd_float(10, value1);
                fee = flt_placeholder * 0.1;
            }
        }

        // cout << "reserved_amount: " << users[user1].reserved << " ," 
        // << "\n" << "\n";
        users[user1].reserved = users[user1].reserved + flt_placeholder + fee;
        // cout << "reserved_amount: " << users[user1].reserved << " ,"  
        // "user: " << user1 << "\n" << "\n";
        
        t_id = get_transactionID(user1, user2, flt_placeholder, fee);

        transaction Transaction(t_id, user1, user2, flt_placeholder, fee);
        transactions[Transaction.transaction_id] = Transaction;
        all_txo.push_back(t_id);

    }
}

void mine_blocks() {
    vector<Block> block_candidates;
    vector<string> used_transactions;
    vector<string> candidate_txo;
    int candidate_count = 5;
    int transaction_count = 3;
    bool no_duplicates = false;

    for (int i = 0; i < candidate_count; i++) {
        // cout << "making candidate: " << i + 1 << endl;
        vector<string> txo;
        map<string, transaction> TXO;

        // cout << "num of txo: " << all_txo.size() << endl;
        for (int j = 0; j < transaction_count; j++) {
            // txo.push_back(all_txo[rand() % all_txo.size()]);
            string str_placeholder = all_txo[rand() % all_txo.size()];
            
            while (find(txo.begin(), txo.end(), str_placeholder) != txo.end()) {
                str_placeholder = all_txo[rand() % all_txo.size()];
            }

            TXO[str_placeholder] = transactions[str_placeholder];
            txo.push_back(str_placeholder);
        }

        Block candidate(1, txo, "temp");
        block_candidates.push_back(candidate);
        txo.clear();
    }

    int mine_attempts = 5;
    bool block_mined = false;
    int max_attempts = 50000; // galimai istrint

    while (block_mined == false) {
        for (int i = 0; i < candidate_count; i++) {
            // cout << "Trying to mine with candidate: " << i + 1 << endl;

            int candidate = rand() % candidate_count;

            used_transactions = block_candidates[candidate].get_transactions();
            block_mined = block_candidates[candidate].mine_block(mine_attempts);

            if (block_mined == true) {
                // cout << "Block mined with candidate: " << i + 1 << endl;
                // cout << "num of txo: " << all_txo.size() << endl;

                for (const auto& transaction : used_transactions) {
                    auto it = find(all_txo.begin(), all_txo.end(), transaction);

                    // cout << "Looking for transaction: " << transaction << endl;

                    if (it != all_txo.end()) {
                        // cout << "Deleting transaction: " << transaction << endl;
                        all_txo.erase(it);
                    }else {
                         //cout << "transaction not found" << endl;
                    }
                }
                // cout << "num of txo: " << all_txo.size() << endl;

                // Blockchain.push_back(block_candidates[candidate]);
                if (Blockchain.size() == 0) {
                    block_candidates[candidate].set_prevhash("");
                    Blockchain.push_back(block_candidates[candidate]);
                }else {
                    int blockchain_size = Blockchain.size();
                    block_candidates[candidate].set_prevhash(Blockchain[blockchain_size - 1].hash);
                    Blockchain.push_back(block_candidates[candidate]);
                }
                return;
            }
        }

        mine_attempts *= 2;
    }



    block_candidates.clear();
} // expand so that it generates candidates and adds the to temp vector

void print_transaction(string txo_hash) {

}

int main() {
    gen_user(2);
    gen_transaction(6);

    do {
        mine_blocks();
    } while (all_txo.size() != 0);

    for (const auto& [id, user] : users) {
        cout << endl;
        user.print_user();
        cout << endl;
    }

    cout << "Block in blockchain: " << Blockchain.size() << endl;

    for (const auto& block : Blockchain) {
        cout << "Block hash: " << block.hash << endl;
        cout << "Previous block hash: " << block.get_prevblock_hash() << endl << endl;
    }

    keys.clear();
    system("pause");

}