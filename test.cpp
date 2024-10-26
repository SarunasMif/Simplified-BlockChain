#include "includes.h"
#include "users.h"
// g++ test.cpp users.cpp -o test.exe 

void test_constructors() {
    User u1;

    cout << "Default constructor:" << endl;
    cout << "Name: " << u1.get_username() << endl;
    cout << "Public_key: " << u1.get_publicKey() << endl;
    cout << "Balance: " << u1.get_balance() << endl;
    // Test default constructor

    istringstream iss("1009 User1 User_key1");
    User u2;

    cout << "Test with input stream" << endl << endl;
    cout << "Data to be inputed: Username(user1), public_key(User_key1), balance(1009)" << endl;
    cout << "Original u2 data" << endl;

    cout << "Name: " << u2.get_username() << endl;
    cout << "Public_key: " << u2.get_publicKey() << endl;
    cout << "Balance: " << u2.get_balance() << endl;

    u2.readUser(iss);
    cout << "u2 data after input: " << endl;
    cout << "Name: " << u2.get_username() << endl;
    cout << "Public_key: " << u2.get_publicKey() << endl;
    cout << "Balance: " << u2.get_balance() << endl;
}

int main() {
    test_constructors();

    system("pause");
}