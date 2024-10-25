#include "includes.h"
using namespace std;

const int start_N = 33;
const int end_N = 255;

string convert_to_decimal(const string &input)
{
    stringstream ss;

    for (size_t i = 0; i < input.size(); i++)
    {
        ss << static_cast<int>(input[i]);

        if (i != input.size() - 1)
        {
            ss << " ";
        }
    }

    return ss.str();
} // Šis kodas paima string inputa ir paverčia jį į jo decimal vertes 

string convert_to_string(const string &decimalString)
{
    stringstream ss(decimalString);
    string result;
    int decimalValue;

    while (ss >> decimalValue)
    {
        result += static_cast<char>(decimalValue);
    }

    return result;
} // Šis kodas paima string inputa ir paverčia jo vertes į charus.

int getScrambleKey(vector<int> &values)
{
    int scramble_key = 1;
    int count = 0;

    for (int i : values)
    {
        scramble_key *= i;

        if (count == 10)
        {
            break;
        }
        count++;
    }
    return scramble_key;
} // Suskaičiuojamas raktas, kuris bus naudojams randomizuoti hash vertes

string Scrambler(const string &input, int number_char)
{
    stringstream ss(input);
    int int_placeholder = 0;

    vector<int> values;     // Laiko vertes, kurios bus naudojamos gaut maišymo raktą
    vector<int> divisors;   // Laiko trukstamu simboliu kiekio daliklius

    int number;
    int scramble_key = 0; // Raktas, kuris bus naudojamas sumaišyti vertes hashavimui
    int input_interval;   // Vertė, kuri nurodo kiek kartų bus įvedami papildomi simboliai
    int number_of_inputs; // Vertė, kuri nurodo kiek simbolių bus įvedama per kiekvieną intervalą
    int overflow;

    while (ss >> number)
    {
        values.push_back(number);
    }
    // Vertės iš stringo įvedamos į vektorių apdorojimui

    if (number_char > 32)
    {
        overflow = number_char - 32;

        for (size_t i = 0; i < overflow; i++)
        {
            values.erase(values.begin());
        }

        number_char -= overflow;
    }

    int padding_number = 32 - number_char;
    // Gaunamas kiekis kiek simbolių reikės nuimti nuo stringo, kai jų yra daugiau nei 32

    for (int i = 1; i <= padding_number; i++)
    {
        if (padding_number % i == 0)
        {
            divisors.push_back(i);
        }
    }

    int number_of_divisors = divisors.size();
    // Apskaičiuojami daliklei

    if (number_of_divisors == 1)
    {
        input_interval = divisors[0];
        number_of_inputs = padding_number;
    }

    if (number_of_divisors == 2)
    {
        input_interval = divisors[0];
        number_of_inputs = divisors[1];
    }

    if (number_of_divisors == 3)
    {
        input_interval = divisors[1];
        number_of_inputs = divisors[1];
    }

    if (number_of_divisors >= 4)
    {
        divisors.erase(divisors.begin());
        divisors.pop_back();

        input_interval = divisors[0];
        int placeholder = divisors.size();
        number_of_inputs = divisors[placeholder - 1];
    }

    if (padding_number == 0)
    {
        input_interval = 0;
        number_of_inputs = 0;
    }

    // Iš daliklių parenkami skaičiai pagal, kurios bus įvedamos papildomos vertės

    scramble_key = getScrambleKey(values);

    int tracker = 0;
    int track = 0;
    int element_count = 0;

    stringstream result;

    int input_coordinate = 0;

    if (input_interval == 5)
    {
        input_coordinate = 1;
    }
    else
    {
        input_coordinate = input_interval;
    }

    for (size_t i = 0; i < input_interval; i++)
    {
        for (size_t y = 0; y < number_of_inputs; y++)
        {
            values.insert(values.begin() + input_coordinate, 1);
        }

        input_coordinate += number_of_inputs + input_interval;
    }
    // Įvedamos papildomos vertės, jei jų reikia

    srand(scramble_key);
    for (size_t i = 0; i < values.size(); i++)
    {

        int_placeholder = values[i];

        result << (rand() % (end_N - start_N + 1)) + start_N << " ";
    }
    // Vertės sumaišamos pagal raktą

    values.clear();
    divisors.clear();
    return result.str();
}

string string_to_hex(const string &input)
{
    static const char hex_digits[] = "0123456789abcdef";

    string output;

    output.reserve(input.length() * 2);

    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }

    return output;
} // String vertės paverčiamos į hexadecimal formatą

void input_by_hand()
{
    string input;
    cout << "Input: ";
    cin >> input;

    string decimalString = convert_to_decimal(input);
    string scb_dec = Scrambler(decimalString, input.size());
    string scb_string = convert_to_string(scb_dec);
    string hash = string_to_hex(scb_string);

    cout << "Hash: " << hash << endl;
    system("pause");
} // Funkcija, kuri paima ranką įvedamą vertę ir gražina jos hasha

void input_by_file()
{
    string input;
    string str_placeholder;
    int i = 0;
    cout << "File name: ";
    cin >> input;

    ifstream read;
    read.open(input);
    ofstream write(input + "_output.txt");

    while (getline(read, str_placeholder))
    {
        string decimalString = convert_to_decimal(str_placeholder);
        string scb_dec = Scrambler(decimalString, str_placeholder.size());
        string scb_string = convert_to_string(scb_dec);
        string hash = string_to_hex(scb_string);

        write << hash << endl;
    }

    system("pause");
} // Funkcija, kuri paima input failą ir išveda suhashuotas jame esančias vertes į kitą failą

int main()
{
    int input_type;

    do
    {
        cout << "To input by file enter [1]; To input by hand type [2];" << endl;
        cout << "Input: ";
        cin >> input_type;

    } while (input_type < 1 || input_type > 3);

    if (input_type == 2)
    {
        input_by_hand();
    }
    else
    {
        input_by_file();
    }

    return 0;
}