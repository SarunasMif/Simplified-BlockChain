#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <vector>
#include <string>

class Block;

using namespace std;

string get_MerkleRoot(vector<string> transactions);
int isOne(const string& input);
void validate_transactions(const vector<string>& Transactions, Block& block);

#endif 