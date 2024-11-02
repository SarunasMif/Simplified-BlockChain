#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "gen_hash.h"

using namespace std;

string get_MerkleRoot(vector<string> transactions);
int isOne(const string& input);

class Block {
private:

    string prev_block_hash; // use to get hash
    time_t timestamp; // use to get hash
    int Version; // use to get hash
    string merkel_root_hash; // use to get hash
    int difficulty; // set after getting block hash
    vector<string> transactions;

    void mine_block() {
        cout << "realize block mining" << endl;
    }
public:
    int nonce;
    string hash;

    Block(int Version, const vector<string>& transactions, const string& prev_block_hash) : Version(Version), transactions(transactions), prev_block_hash(prev_block_hash) {

        time(&timestamp);

        merkel_root_hash = get_MerkleRoot(transactions);

        get_block_hash();

        get_difficulty();

        mine_block();

        print_block();
    }


    // string get_merkle_hash() const { return merkel_root_hash; }
    // time_t get_timestap() const { return timestamp; }
    // int get_version() const { return Version; }
    // string get_prev_block_hash() const { return prev_block_hash; }
    // string get_block_hash() const { return hash; }
    // Getters

    void get_difficulty() {
        string bin_hash = get_binary_of_hash(hash);
        int int_placeholder;
        int i = 0;

        int_placeholder = isOne(bin_hash);

        do {
            hash = merkel_root_hash + prev_block_hash + to_string(timestamp) + to_string(i);
            hash = get_hash(hash);
            bin_hash = get_binary_of_hash(hash);

            int_placeholder = isOne(bin_hash);
            i++;
        }while (int_placeholder == 0); // If the hash hash no 0 zeroes before one in binary form of hash the hash is modified untiul it has atleast one
        
        difficulty = int_placeholder;
    }

    void get_block_hash() {
        hash = merkel_root_hash + prev_block_hash + to_string(timestamp) + to_string(Version);

        hash = get_hash(hash);
    }

    void print_block() {
        cout << "prev_block_hash: " << prev_block_hash << "\n"
        << "timestamp: " << ctime(&timestamp)
        << "Version: " << Version << "\n"
        << "merkle_root_hash: " << merkel_root_hash << "\n"
        << "nonce: " << nonce << "\n"
        << "difficulty: " << difficulty << "\n" 
        << "blockhash: "<< hash << "\n" << "\n"; 
    }

    ~Block() {}
    // Deconstructor
};
