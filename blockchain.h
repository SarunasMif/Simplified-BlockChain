#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <random>
#include "gen_hash.h"

using namespace std;

string get_MerkleRoot(vector<string> transactions);
int isOne(const string& input);
void validate_transactions(const vector<string>& Transactions);
void clear_transactions();

class Block {
private:

    string prev_block_hash; // use to get hash
    time_t timestamp; // use to get hash
    int Version; // use to get hash
    string merkel_root_hash; // use to get hash
    int difficulty; // set after getting block hash
    vector<string> transactions;
    
public:
    int nonce;
    string hash;

    Block() : prev_block_hash(""), timestamp(0), Version(0), merkel_root_hash(""), difficulty(4), nonce(0), hash("") {}

    Block(int Version, const vector<string>& transactions, const string& prev_block_hash) : Version(Version), transactions(transactions), prev_block_hash(prev_block_hash) {

        time(&timestamp);

        vector<string> temp = transactions;
        merkel_root_hash = get_MerkleRoot(temp);

        difficulty = 4;

        nonce = 0;

        get_block_hash();

        print_block();
    }


    // string get_merkle_hash() const { return merkel_root_hash; }
    // time_t get_timestap() const { return timestamp; }
    // int get_version() const { return Version; }
    // string get_prev_block_hash() const { return prev_block_hash; }
    // string get_block_hash() const { return hash; }
    // Getters

    // void get_difficulty() {
    //     string bin_hash = get_binary_of_hash(hash);
    //     int int_placeholder;
    //     int i = 0;

    //     int_placeholder = isOne(bin_hash);

    //     do {
    //         hash = merkel_root_hash + prev_block_hash + to_string(timestamp) + to_string(i);
    //         hash = get_hash(hash);
    //         bin_hash = get_binary_of_hash(hash);

    //         int_placeholder = isOne(bin_hash);
    //         i++;
    //     }while (int_placeholder < 1); // If the hash has no 0 zeroes before one in binary form of hash the hash is modified untiul it has atleast one
        
    //     difficulty = int_placeholder;
    // }// should be in private

    void get_block_hash() {
        hash = merkel_root_hash + prev_block_hash + to_string(timestamp) + to_string(Version) + to_string(difficulty);

        hash = get_hash(hash);
    }// should be in private

    void print_block() {
        cout << "prev_block_hash: " << prev_block_hash << "\n"
        << "timestamp: " << ctime(&timestamp)
        << "Version: " << Version << "\n"
        << "merkle_root_hash: " << merkel_root_hash << "\n"
        << "nonce: " << nonce << "\n"
        << "difficulty: " << difficulty << "\n" 
        << "blockhash: "<< hash << "\n" << "\n"; 
    }

    void mine_block() {
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> dis(0, 61);

        string input;
        int int_placeholder;
        bool block_mined = false;

        for (int i = 0; i < 10; i++) {
            input += chars[dis(generator)];
        }

        while (block_mined == false) {
            string new_input;

            for (int i = 0; i < 10 + nonce; i++) {
                new_input += chars[dis(generator)];
            }

            string hash_bin = get_binary_of_hash(new_input);
            int_placeholder = isOne(hash_bin);

            cout << int_placeholder << endl;
            if (int_placeholder >= 1) {
                block_mined = true;
                validate_transactions(transactions);
            } else {
                nonce++;
            }
        }
    }

    void clear_transactions() {
        transactions.clear();

        cout << transactions.size() << endl;
    }

    ~Block() {}
    // Deconstructor
};
