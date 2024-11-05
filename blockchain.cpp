#include "block.h"
#include "gen_hash.h"
#include "includes.h"
#include "blockchain.h"

using namespace std;

string get_MerkleRoot(vector<string> transactions) {
    if (transactions.size() == 0) {
        return "";
    }// If the there are no transactions returns empty string

    vector<string> transactions_clone = transactions;

    while (transactions_clone.size() > 1) {

        if (transactions_clone.size() % 2 != 0) {

            transactions_clone.push_back(transactions_clone.back());

        } // If the number of transaction is not even, we add an extra hash of a copied transaction

        vector<string> new_transactions;

        for (size_t i = 0; i < transactions_clone.size(); i += 2) {

            string str_placeholder = get_hash(transactions_clone[i] + transactions_clone[i + 1]);
            new_transactions.push_back(str_placeholder);

        }// Loop that calculates the Merkle Root Hash

        transactions_clone = new_transactions;
    }

    return transactions_clone[0]; // Returns merkle root hash
}

int isOne(const string& input) {
    int num_of_0 = 0;

    for (char c : input) {
        if (c == '1') {
            break;
        }
        num_of_0++;
    }

    return num_of_0;
} // Returns the number of 0 before 1 at the beggining of the hash(binary)

void validate_transactions(const vector<string>& Transactions, Block& block) {
    long value, fee;
    string user1, user2;

    size_t nmb_tx = Transactions.size();

    for (size_t i = 0; i < nmb_tx; i++) {
        auto tx = transactions.find(Transactions[i]);

      
        value = tx->second.value;
        user1 = tx->second.sender_pkey;
        user2 = tx->second.getter_pkey;

        fee = tx->second.fee;

        auto getter = users.find(user2);
        auto sender = users.find(user1);

        sender->second.balance -= value + fee;
        sender->second.reserved -= value + fee;

        getter->second.balance += value;
        // Goes through the users that are a part of the transaction and changes their balances and reserved funds accordingly to the value and fee of the transaction
    }
}// Validates transactions by going through the ones that are in the Block