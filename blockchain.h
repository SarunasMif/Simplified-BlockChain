#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

struct Block_Head {
    string prev_block_hash;
    time_t timestamp;
    int Version;
    string merkel_root_hash;
    int nonce;
    int difficulty;
};

struct Block_Body {
    vector<string> transactions;
};

class Block {
public:
    Block_Head header;
    Block_Body body;
    string hash;

    //  Block(int ver, const std::string &prev, int diff, const std::vector<std::string> &txs)
    //     : hash(""), header({ver, prev, "", std::time(nullptr), diff, 0}), body({txs}) {
    //     header.merkleRootHash = calculateMerkleRoot(body.transactions);
    //     hash = mineBlock();
    // }
    // Constructor

    ~Block() {}
    // Deconstructor
};