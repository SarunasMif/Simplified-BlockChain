#include <iostream>
#include "gen_hash.h"

using namespace std;

void reg_block() {

}

int main() {

    string input = "hello world";
    string hash;

    hash = get_hash(input);

    cout << hash;

    system("pause");

}