#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <time.h>

using namespace std::chrono;
using namespace std;


int main();
void input_by_file();
void input_by_hand();
string string_to_hex(const string &input);
string Scrambler(const string &input, int number_char);
int getScrambleKey(vector<int> &values);
string convert_to_string(const string &decimalString);
string convert_to_decimal(const string &input);