#include <iostream>
#include "includes.h"
#include "gen_hash.h"
#include "block.h"

using namespace std;

vector<Block> Blockchain;              // Vector that stores the entire Blockchain
map<string, transaction> transactions; // Temporarily holds all transactions, they get deleted when a block is mined and they are validated
map<string, user> users;               // Holds generated users
vector<string> keys;                   // Holds generated publick keys, the only purpose for this is to check if a key was already generated
vector<string> all_txo;                // Temporarily holds generated transaction id's, they get deleted when the blocks are mined

string gen_hash(string input) {
    string hash = get_hash(input);

    return hash;
} // Uses the hash generator to generate a hash

string get_transactionID(string u1, string u2, long value, long fee) {
    string id;
    id = to_string(value) + to_string(fee) + u1 + u2;

    id = gen_hash(id);

    return id;
} // Generates id's for transactions

long get_rnd_long(long min, long max) {
    random_device rd;
    mt19937 gen(rd());

    long val;

    uniform_int_distribution<long> dis(min, max);

    val = dis(gen);

    return val;
} // Generates a random long int value

string gen_pkey() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Symbols that will be used in publick keys

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
} // Generates random publick keys

void gen_user(int number_of_users) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(10000, 1000000);

    string name_temp;
    string p_key_temp;

    for (int i = 0; i < number_of_users; i++) {
        name_temp = "user" + to_string(i + 1);  // Gives user a name
        p_key_temp = gen_pkey();                // Gives user a publick_key
        long balance = dis(gen);                // Generates a balance for user 

        user User(name_temp, p_key_temp, balance);
        users[User.p_key] = User;
        // Inserts users into a map
    }
} // Generates users

void gen_transaction(int number_of_transactions) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, users.size() - 1);

    string user1, user2, t_id;
    int u1, u2;
    long flt_placeholder, value1, fee;

    for (size_t i = 0; i < number_of_transactions; i++) {

        do {
            user1 = keys[dis(gen)];
            user2 = keys[dis(gen)];
        }while (user2 == user1);
        // Picks random two users who will be a part of the transaction

        value1 = users[user1].balance;

        flt_placeholder = get_rnd_long(100, value1);
        fee = flt_placeholder * 0.1;
        // Generates the transactions value 
    
        t_id = get_transactionID(user1, user2, flt_placeholder, fee);
        transaction Transaction(t_id, user1, user2, flt_placeholder, fee);
        transactions[Transaction.transaction_id] = Transaction;
        all_txo.push_back(t_id);
        // Generates the transactions id and ads it to the transaction vecotor, aswell as constructs the transaction and ads it to the transaction map

        cout << "Generated transaction with the id: " << t_id << endl;
    }
}

void mine_blocks() {
    vector<Block> block_candidates;
    vector<string> used_transactions;
    vector<string> candidate_txo;
    int candidate_count = 5;
    int transaction_count = 10;
    bool no_duplicates = false;

    for (int i = 0; i < candidate_count; i++) {
        map<string, transaction> TXO;   // Temp map of transactions

        for (int j = 0; j < transaction_count; j++) {
            string str_placeholder = all_txo[rand() % all_txo.size()];
            
            while (TXO.find(str_placeholder) != TXO.end()) {
                str_placeholder = all_txo[rand() % all_txo.size()];
            }
            // If a selected transaction already is in the block transactions it gets removed

            TXO[str_placeholder] = transactions[str_placeholder];
        }

        Block candidate(1, TXO, "temp");
        block_candidates.push_back(candidate);
    }
    // Randomly allocates transactions to the block

    int mine_attempts = 5;
    bool block_mined = false;
    int max_attempts = 50000;

    while (block_mined == false) {
        for (int i = 0; i < candidate_count; i++) {

            int candidate = rand() % candidate_count;

            used_transactions = block_candidates[candidate].get_transactions();
            block_mined = mine_block(mine_attempts, block_candidates[candidate]);
            // Generates five block candidates and attempts to mine them

            if (block_mined == true) {

                erase_transactions(used_transactions);  // Erases used transactions from the map and vector

                if (Blockchain.size() == 0) {

                    block_candidates[candidate].set_prevhash("");
                    block_candidates[candidate].get_block_hash();
                    Blockchain.push_back(block_candidates[candidate]);
                    // If the block is the first in the chain it points to no previous block and gets added to the blockchain

                }else {

                    int blockchain_size = Blockchain.size();
                    block_candidates[candidate].set_prevhash(Blockchain[blockchain_size - 1].get_blockhash());
                    block_candidates[candidate].get_block_hash();
                    Blockchain.push_back(block_candidates[candidate]);
                    // Adds the hash of the previous block to the block and adds it to the blockchain

                }

                cout << "Block added to Blockchain with hash: " << block_candidates[candidate].get_blockhash() << endl << endl;

                return;
            }
        }

        mine_attempts *= 2;
    }
    // Attempts to mine block candidates if none are mined in the specified attempts the number od attempts is increased

    block_candidates.clear();
}

bool mine_block(int mine_attempt, Block& block) {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Symbols that will be used to generate the hash

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dis(0, 61);

    string input;
    int int_placeholder;
    int difficulty = block.get_difficulty();
    int nonce = block.get_nonce();
    bool block_mined = false;
    vector<string> transactions = block.get_transactions();

    for (int i = 0; i < mine_attempt; i++) {
        string new_input;

        for (int i = 0; i < 10 + nonce; i++) {
            new_input += chars[dis(generator)];
        }

        string hash_bin = get_binary_of_hash(new_input);
        int_placeholder = isOne(hash_bin);

        if (int_placeholder >= difficulty) {
            block_mined = true;
            block.set_nonce(nonce);
            validate_transactions(transactions, block);
            return true;
        } else {
            nonce++;
        }
    }

    return false;

}
// Generates a random hash and checks if it matches the difficulty requirement if not it increases the nonce and tries again

void erase_transactions(const vector<string>& used_transactions) {
    for (const auto& transaction : used_transactions) {

        auto it = find(all_txo.begin(), all_txo.end(), transaction);

        if (it != all_txo.end()) {
            all_txo.erase(it);
        }
    }

    for (const auto& transaction : used_transactions) {
        auto it = transactions.find(transaction);

        if (it != transactions.end()) {
            transactions.erase(it);
        }
    }
}
// Goes through the transaction map and vector and removes those that got validated

void print_transaction(string txo_hash) {
    
    for (int i = 0; i < Blockchain.size(); i++) {

        map<string, transaction> transactions = Blockchain[i].get_TRANSACTIONS();

        for (auto it = transactions.begin(); it != transactions.end(); it++) {

            if (transactions[it->first].transaction_id == txo_hash) {

                transactions[it->first].print_transaction();
            }
        }
    }
} // Prints out a specified transaction

void print_block(string block_hash) {

    for (int i = 0; i < Blockchain.size(); i++) {

        if (Blockchain[i].get_blockhash() == block_hash) {

            Blockchain[i].print_block();
        }
    }
} // Prints out a specified block

int main() {
    gen_user(1000);

    gen_transaction(10000);

    do {
        mine_blocks();
    } while (all_txo.size() != 0);

    string input, Input;

    cout << "____________________________________________________________________________________________" << endl;

    while (input != "exit") {

        if (input == "back") {
            input = "exit";
        }

        cout << endl;
        cout << "If at any point you want to exit the application input 'exit'.\n" << "\n"
        << "If you want to print a transaction input '1'." << "\n"
        << "If you want to print a block input '2'." << "\n"
        << "Input: ";

        cin >> input;

        if (input == "1") {

            cout << endl;
            cout << "Which transaction do you want to print?" << "\n"
            << "Input transaction id: ";

            cin >> input;
            cout << endl;

            print_transaction(input);

            do {
                cout << endl
                << "Do you want to print another transaction input 'y' if no 'n'." << "\n";
                cout << "Input: ";

                cin >> input;

                if (input == "y") {

                    cout << endl;
                    cout << "Which transaction do you want to print?" << "\n"
                    << "Input transaction id: ";

                    cin >> input;
                    cout << endl;

                    print_transaction(input);
                } 
                if (input == "n") {

                    input = "back";
                }

            } while (input != "back");
        }

        if (input == "2") {

            cout << endl;
            cout << "Which block do you want to print?" << "\n"
            << "Input block hash: ";

            cin >> input;
            cout << endl;

            print_block(input);

            do {
                cout << endl
                << "Do you want to print another block input 'y' if no 'n'." << "\n";
                cout << "Input: ";

                cin >> input;

                if (input == "y") {

                    cout << endl;
                    cout << "Which block do you want to print?" << "\n"
                    << "Input block hash: ";

                    cin >> input;
                    cout << endl;

                    print_block(input);
                } 
                if (input == "n") {

                    input = "back";
                }

            } while (input != "back");
        }

        if (input == "exit") {
            break;
        }
        
    }

    keys.clear(); // Clears vector that holds generated publick keys
}