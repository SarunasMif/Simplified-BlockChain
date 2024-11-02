#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

vector<Block> Blockchain;

string get_MerkleRoot(vector<string> transactions);
string get_block_hash();

class Block {
private:

    string prev_block_hash; // use to get hash
    time_t timestamp; // use to get hash
    int Version; // use to get hash
    string merkel_root_hash; // use to get hash
    int difficulty; // set after getting block hash
    vector<string> transactions;
    string hash;

    void mine_block() {
        cout << "realize block mining" << endl;
    }
public:
    int nonce;

    Block(int Version, const vector<string>& transactions) : Version(Version), transactions(transactions) {

        if (Blockchain.empty()) {
            prev_block_hash = "";
        }else {
            prev_block_hash = Blockchain.back();
        }
        
        time(&timestamp);

        merkel_root_hash = get_MerkleRoot(transactions);

        get_block_hash();

        mine_block();

        print_block();
    }

    void print_block() {
        cout << "prev_block_hash: " << prev_block_hash << "\n"
        << "timestamp: " << ctime(&timestamp) << "\n"
        << "Version: " << Version << "\n"
        << "merkle_root_hash: " << merkel_root_hash << "\n"
        << "nonce: " << nonce << "\n"
        << "difficulty: " << difficulty << "\n" << "\n"; 
    }

    ~Block() {}
    // Deconstructor
};