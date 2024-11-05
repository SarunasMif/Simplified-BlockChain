# Simplified-BlockChain

# How to use

1) If you do not have the necessary compilers to compile c++ code download and set them up by following instructios found in this website: https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/ .

2) Open `cmd` and utilizing the cd command navigate to the folder in which you have installed the program. That into the terminal input this commad:

- `g++ main.cpp gen_hash.cpp blockchain.cpp -o main.exe`

3) You will find the programs main.exe file in the folder.

# Pseudo code

### main.cpp
```plaintext
INITIALIZE vector that stores the blockchain
INITIALIZE map of structs that stores the transactions
INITIALIZE map of users that stores the users
INITIALIZE vector that stores generated publick_keys
INITIALIZE vcetor that stores transaction id's

FUNCTION gen_hash(input)
    generates hash of the provided input
    RETURNS generated hash

FUNCTION get_transactionID(u1, u2, value, fee)
    makes a string that consists of the provided values
    generates hash of the string
    RETURNS generated hash

FUNCTION get_rnd_long(min, max)
    sets up the random value generator
    genarates a long int that is between the provided minimum and maximum value
    RETURNS the generated value

FUNCTION gen_pkey()
    sets up a constant string that contains the character that will be used to generate the public key;
    sets up the random value generator
    DOES 
        generates publick keys
    WHILE the key already exist in keys vector
    adds the new key into keys vector
    RETURNS generated publick key

FUCNTION gen_user(number_of_users)
    sets up random values generator
    FOR the specified number by number_of_users
        genrates users name
        genrates publick key with gen_key()
        genrates a random value between 10000 and 1000000
        makes a user struct
        inputs it into the user map

FUNCTION gen_transactions(number_of_transactions)
    sets up random value genrator
    FOR the specified number by number_of_transactions
        DOES
            generates a random user
            generates a second random user
        WHILE the generated users are not the same
        gets the max value a transaction will have
        IF the value + fee is larger than available user funds
            WHILE   the value + fee is larger than available user funds
                gets the max value a transaction will have
        updates the reserved value in user
        generates transaction_id with get_transactioID()
        creates the transactions struct
        ads the transaction to the transaction map
        ads the transaction id to the transaction vector
        print out the transaction id

FUNCTION mine_blocks()
    INITIALIZES vecotor of blocks
    INITIALIZES vector of transaction
    INITIALIZES vector of block candidates
    FOR the number of candidates
        INITIALIZES map of transactions
        FOR the number of transactions to be placed into the block
            selects a random transaction to be placed into the map
            WHILE the transaction is already in the vector
                reselect a transaction
            places the transaction into the map
        created a block candidate
        puts the candidate into the candidate vector
    WHILE the block is not mined
        FOR the number of candidates
            select a random candidate
            attempts to mine block with mine_block(mine_attempts, block candidate)
            IF block is mined
                removes transactions that were in the block candidate with erase_transactions(vector of transactions)
                IF block chain is empty
                    sets block previous block hash to ""
                    generates block hash
                    places the block into the blockchain vector
                ELSE 
                    sets blocks previous hash to the last block in the blockchain
                    generates block hash
                    places the block into the blockchain vector
        increases mine_attempts if no candidates were succesfully mined

FUNCTION mine_block(mine_attempts, Block address)
    sets up random generator
    gets nonce
    gets difficulty
    FOR the number of mine attempts
        generates a hash
        IF the hash satisfys difficulty
            sets what nonce was used to mine it
            validates transaction inside the block
        ELSE
            increases nonce

FUNCTION erase_transactions(used_transactions)
    FOR each transaction in transactions vector
        makes an itterator
        IF transaction is found in used transactions
            transaction is removed from transactions vector
    FOR each transaction in transactions vector
        makes itterator
        IF transaction is found in transactio map
            transaction is removed

FUNCTION print_transaction(transaction_id)
    FOR each block in blockchain
        INITIALIZES transaction map copy that is that block
        FOR each transaction in the map
            IF transaction is found in that block
                transaction is printed out with print_transactio()

FUNCTION print_block(block_hash)
    FOR each block in the blockchain
        IF block is found
            block is printed with print_block()

FUNCTION main()
    1000 users are generated
    10000 transactions are genrated
    DOES
        mine_blocks()
    WHILE there still are transactions
    WHILE input is not 'exit'
        IF input is 'back'
            input is 'exit'
        prints out information
        IF input is '1'
            asks which transaction to print
            prints transaction with print_transaction()
            DOES
                asks if users wants to print another transaction
                IF input 'y'
                    asks which transaction to print
                    prints transaction with print_transaction()
                IF input is 'n'
                    input is 'back'
            WHILE input is not 'back'
        IF input is '2'
            asks which block to print
            prints block with print_block()
            DOES
                asks if user wants to print another block
                IF input 'y'
                    asks which block to print
                    prints block with print_block()
                IF input is 'n'
                    input is 'back'
            WHILE input is not 'back'
        IF input is 'exit'
            ends function
END
```

### blockchain.cpp

```plaintext
START

FUNCTION get_MerkleRoot(transactions)
    IF transactions is empty
        RETURNS ""
    INITIALIZES clone vector of transactions
    WHILE transactions_clone has more than one value
        IF transactions_clone is not even
            clones the last value and adds it to transactions_clone
        INITIALIZES new_transaction vector
        FOR the size of the transactions_clone
            calculates combined hash of two values
            adds hash too new_transaction vector
    RETURNS Merkle Root 

FUNCTION isOne(input)
    FOR each character in input
        IF that character is 1
            breaks loop
        increases number of zeroes
    RETURNS number of zeroes

FUNCTION validate_transaction(Transaction. block)
    gets number of transactions
        FOR the number of transactions
            finds transaction in the map
            gets values
            finds users in map
            updates their balance accordingly
            updates their reserved value accordingly
```

# Code examples

### block class
```cpp
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

        int num_txo = transactions.size();
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
    // Setters

    ~Block() {}
    // Deconstructor
};
```

### User and transaction structs

```cpp
struct transaction {

    string transaction_id;
    string sender_pkey;
    string getter_pkey;
    long value;
    long fee;
    // variables

    transaction() : transaction_id(""), sender_pkey(""), getter_pkey(""), value(0.), fee(0.) {}

    transaction(const string& transaction_id, const string& sender_pkey, const string& getter_pkey, long value, long fee) :
    transaction_id(transaction_id), sender_pkey(sender_pkey), getter_pkey(getter_pkey), value(value), fee(fee) {}
    // Constructors

    void print_transaction() const {

        float usd = value;
        usd = usd / 100;

        float usd_f = fee;
        usd_f = usd_f /100;

        cout << "------------------------------------------------------------------------------------" << endl;
         cout << "Transaction_id  | " << transaction_id << " \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Sender_key      | " << sender_pkey << "                                       \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Getter_key      | " << getter_pkey << "                                       \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Value           | " << usd << " USD" << "                                       \n"
         << "------------------------------------------------------------------------------------" << endl
         << "Transaction fee | " << usd_f << " USD" << "                                         \n" 
         << "------------------------------------------------------------------------------------" << endl;
    }
    // Construct functions

}; // construct for transactions

struct user {
    string name;
    string p_key;
    long balance;
    long reserved = 0; // This values keeps track of how much money the user has already allocated for transactions
    // variables

    user() : name(""), p_key(""), balance(0), reserved(0) {}

    user(const string& name, const string& p_key, long balance) :
    name(name), p_key(p_key), balance(balance) {}
    // Constructor

    void print_user() const {
        cout << "name: " << name << "\n" 
        << "publick_key: " << p_key << "\n"
        << "balance: " << balance << "\n"
        << "reserved: " << reserved << "\n";
    }
    // Construct functions
};
```