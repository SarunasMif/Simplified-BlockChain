#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <random>
#include "gen_hash.h"
#include "blockchain.h"

using namespace std;

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

    bool mine_block(int mine_attempt) {
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> dis(0, 61);

        string input;
        int int_placeholder;
        bool block_mined = false;

        for (int i = 0; i < mine_attempt; i++) {
            string new_input;

            for (int i = 0; i < 10 + nonce; i++) {
                new_input += chars[dis(generator)];
            }

            string hash_bin = get_binary_of_hash(new_input);
            int_placeholder = isOne(hash_bin);

            cout << int_placeholder << endl;
            if (int_placeholder >= 3) {
                block_mined = true;
                validate_transactions(transactions, *this);
                return true;
            } else {
                nonce++;
            }
        }

        cout << "block mining failed!" << endl;
        return false;

    }// Move this function somewhere else

    int get_difficulty() const { return difficulty; }
    const vector<string>& get_transactions() const { return transactions; }
    string get_blockhash() const { return hash; }
    string get_prevblock_hash() const { return prev_block_hash; }
    // Getters

    void set_prevhash(string hash){ prev_block_hash = hash; }
    // Setters

    ~Block() {}
    // Deconstructor
};

#endif