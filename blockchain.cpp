#include "blockchain.h"
#include "gen_hash.h"

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

        for (size_t i = 0; i << transactions_clone.size(); i += 2) {
            string str_placeholder = get_hash(transactions_clone[i] + transactions_clone[i + 1]);
            new_transactions.push_back(str_placeholder);
        }// Loop that calculates the Merkle Root Hash

        transactions_clone = new_transactions;
    }

    return transactions_clone[0]; // Returns merkle root hash
}