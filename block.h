#ifndef BLOCK_H
#define BLOCK_H

#include "gen_hash.h"
#include "blockchain.h"
#include "includes.h"

using namespace std;

void clear_transactions();

class Block {
private:

    string prev_block_hash;                 // Holds the hash of the previous block in the blockchain
    time_t timestamp;                       // Holds the time and date of the the block got mined
    int Version;                            // Version of the blockchain
    string merkel_root_hash;                // Holds the Merkle Root of the block
    int difficulty;                         // Holds the number of required zeroes at the beggining of the hash(binary)
    vector<string> transactions;            // Holds the transaction id's in a vector. Why? No comment. 
    map<string, transaction> TRANSACTIONS;  // Holds the transactions in the map
    string hash;                            // Holds the hash of the block
    int nonce;                              // Holds the number that was required to mine the block (attempts kinda)
    
public:

    Block() : prev_block_hash(""), timestamp(0), Version(0), merkel_root_hash(""), difficulty(4), nonce(0), hash("") {}

    Block(int Version, const map<string, transaction> TRANSACTIONS, const string& prev_block_hash) : Version(Version), TRANSACTIONS(TRANSACTIONS), prev_block_hash(prev_block_hash) {

        for (auto it = TRANSACTIONS.begin(); it != TRANSACTIONS.end(); it++) {
            transactions.push_back(it->first);
        }
        // Inserts the keys of the transaction into the transactions vector, because I can not read

        time(&timestamp);

        vector<string> temp = transactions;
        merkel_root_hash = get_MerkleRoot(temp);

        difficulty = 4;

        nonce = 0;
    }
    // Constructors

    void get_block_hash() {
        hash = merkel_root_hash + prev_block_hash + to_string(timestamp) + to_string(Version) + to_string(difficulty) + to_string(nonce);

        hash = get_hash(hash);
    }
    // Genrates the hash of the block

    void print_block() {

        int num_txo = TRANSACTIONS.size();
        float Value, fees;
        float plh;

        for (auto it = TRANSACTIONS.begin(); it != TRANSACTIONS.end(); it++) {
            plh = it->second.value;
            Value += plh;
            plh = it->second.fee;
            fees += plh;
        }

        Value = Value / 100;
        fees = fees / 100;

        cout
        << "------------------------------------------------------------------------------------------" << endl 
        << "Hash                  | " << hash << "\n" 
        << "------------------------------------------------------------------------------------------" << endl
        << "Transactions          | " << num_txo << "\n"
        << "------------------------------------------------------------------------------------------" << endl
        << "Value                 | " << Value << " USD" << "\n"
        << "------------------------------------------------------------------------------------------" << endl
        << "Fees                  | " << fees << " USD" << "\n"
        << "------------------------------------------------------------------------------------------" << endl
        << "Mined On              | " << ctime(&timestamp)
        << "------------------------------------------------------------------------------------------" << endl
        << "Version               | " << Version << "\n"
        << "------------------------------------------------------------------------------------------" << endl
        << "Difficulty            | " << difficulty << "\n"
        << "------------------------------------------------------------------------------------------" << endl
        << "Nonce                 | " << nonce << "\n"
        << "------------------------------------------------------------------------------------------" << endl
        << "Merkle Root           | " << merkel_root_hash << "\n"
        << "------------------------------------------------------------------------------------------" << endl
        << "Previous Block Hash   | " << prev_block_hash << "\n"
        << "------------------------------------------------------------------------------------------" << endl;

    } // Prints out the block values and the combined of value of transactions in the block

    void print_block_transactions() {
        for (auto it = TRANSACTIONS.begin(); it != TRANSACTIONS.end(); it++) {
            TRANSACTIONS[it->first].print_transaction();
        }
    } // Prints out the transactions that are in the block

    void remove_invalid_txo() {
        map<string, transaction> new_txo;

        for (const auto& transaction : transactions) {
            auto it = TRANSACTIONS.find(transaction);

            if (it != TRANSACTIONS.end() && it->second.POE()) {
                new_txo[transaction] = TRANSACTIONS[transaction];
                cout << "Valid transaction added with the id: " << TRANSACTIONS[transaction].transaction_id << endl << endl;
            } // Uses POE(proof of existence) function to remove phantom transactions
        }

        TRANSACTIONS = move(new_txo);
    }// Removes transactions that were invalid

    // Class functions

    int get_difficulty() const { return difficulty; }
    int get_nonce() const { return nonce; }
    const vector<string>& get_transactions() const { return transactions; }
    string get_blockhash() const { return hash; }
    string get_prevblock_hash() const { return prev_block_hash; }
    const map<string, transaction>& get_TRANSACTIONS() const { return TRANSACTIONS; }
    // Getters

    void set_nonce(int NONCE) { nonce = NONCE; }
    void set_prevhash(string hash){ prev_block_hash = hash; }
    void set_txo (vector<string>& txo) { transactions = move(txo); }
    // Setters

    ~Block() {}
    // Deconstructor
};

#endif