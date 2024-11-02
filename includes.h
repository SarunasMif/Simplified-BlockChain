#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <ctime>
#include <random>
#include <sstream>
#include <algorithm>


using namespace std;

string gen_hash(string input);
string get_transactionID(string u1, string u2, float value, float fee);
float get_rnd_float(float min, float max);
string gen_pkey();
void gen_user(int number_of_users);
void gen_transaction(int number_of_transactions);
int main();