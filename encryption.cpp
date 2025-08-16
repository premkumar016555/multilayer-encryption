//encryption
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>  // For std::invalid_argument
#include <cstdlib>    // For rand() and srand()
#include <ctime>      // For time()
#include <map>

using namespace std;

// Function to initialize symbol and letter mappings
void initializeMappings(unordered_map<char, int>& map) {
    // Initialize symbol mappings
    map['!'] = 42;
    map['@'] = 43;
    map['#'] = 44;
    map['$'] = 45;
    map['%'] = 46;
    map['^'] = 47;
    map['&'] = 48;
    map['*'] = 49;
    map['('] = 50;
    map[')'] = 51;
    // Add more symbol mappings as needed

    // Initialize uppercase letter mappings
    int startValue = 50;
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        map[ch] = startValue;
        startValue += 1;
    }

    // Initialize lowercase letter mappings
    startValue = 10;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        map[ch] = startValue;
        startValue += 1;
    }
}

// Function to encrypt a plaintext using Caesar cipher

string encryptCaesar(const string& plaintext, int shift) {  // Removed the extra comma
    const string shuffledAlphabet = "ndI;6MXHp.NE5 :TBC*?e/risY8,xqQlU_\"awP3y$fOb'o4)\\+Kv]Vz&%F|-kg~u0>=@{c[7m}jt#W<SAZL2JD9(^`GhR1!";  // Predefined shuffled alphabet
    string ciphertext = "";

    for (char c : plaintext) {
        if (c >= 32 && c <= 126) {  // Check if the character is within the printable ASCII range
            int originalIndex = shuffledAlphabet.find(c);  // Find the index of the character in the shuffled alphabet
            if (originalIndex != string::npos) {  // Check if the character was found
                int newIndex = (originalIndex + shift) % 95;  // Calculate the new index with the shift
                ciphertext += shuffledAlphabet[newIndex];  // Map to the shuffled alphabet
            } else {
                ciphertext += c;  // If the character is not found, leave it unchanged
            }
        } else {
            ciphertext += c;  // If the character is outside the printable ASCII range, do not encrypt it
        }
    }

    return ciphertext;
}

// Function to encrypt a text using Rail Fence cipher

string railFenceEncrypt(const string &text) {
    int numRails = 3;
   const vector<int> railOrder = {2, 0, 1}; // User-defined rail order
   
    if (numRails == 1) return text;
    
    // Create a 2D vector to represent the rails
    vector<string> rail(numRails);

    // Fill the rails in zigzag pattern
    int row = 0;
    bool down = true;
    for (char c : text) {
        rail[row] += c;
        if (row == 0) {
            down = true;
        } else if (row == numRails - 1) {
            down = false;
        }
        row += down ? 1 : -1;
    }

    // Concatenate the rails based on the user-defined rail order
    string result;
    for (int i : railOrder) {
        result += rail[i];
    }

    return result;
}

// Function to convert a string of numbers into a single concatenated string
string combineNumbers(const string& input) {
    string combined;
    for (char ch : input) {
        if (isdigit(ch)) {
            combined += ch;
        }
    }
    return combined;
}

// Function to safely convert a string to integer and handle exceptions
int safeStoi(const string& str) {
    if (str.empty()) return 0;  // Default to 0 if the string is empty
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        return 0;
    } catch (const out_of_range& e) {
        cerr << "Out of range: " << e.what() << endl;
        return 0;
    }
}

// Function to split a combined number string into individual digits
vector<int> splitIntoShifts(const string& combinedNumbers) {
    vector<int> shifts;
    for (char ch : combinedNumbers) {
        if (isdigit(ch)) {
            shifts.push_back(ch - '0'); // Convert char digit to integer
        }
    }
    return shifts;
}

// Function to insert random padding within the plaintext
string addHiddenPadding(const string& plaintext) {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness

    // Characters that can be used for padding
    string paddingChars = "abcdefghijklmnoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:',.<>?";
    string paddedText;
    
    // Generate a random number of padding characters between 1 and 5
    int paddingLength = rand() % 100 + 1;
    
    // Iterate over each character in the plaintext
    for (size_t i = 0; i < plaintext.size(); ++i) {
        paddedText += plaintext[i];  // Add the original character

        // Append padding characters based on the generated padding length
        for (int j = 0; j < paddingLength; ++j) {
            paddedText += paddingChars[rand() % paddingChars.size()];  // Insert random padding characters
        }

        // Add the '~' marker after the first character's padding
        if (i == 0) {
            paddedText += 'p';
        }
    }

    return paddedText;
}
// Function to encrypt the plaintext using the substitution map
string encryptSubstitution(const string& plain_txt) {
    // Complex predefined substitution map for encryption

   unordered_map<char, char> substitution_map = {
        {' ', '$'}, {'!', '\''}, {'"', 'O'}, {'#', 'z'}, {'$', '}'}, {'%', 'v'}, {'&', ')'},
        {'\'', '7'}, {'(', '>'}, {')', '~'}, {'*', 'N'}, {'+', 'y'}, {',', 'b'}, {'-', '8'},
        {'.', 'u'}, {'/', 'D'}, {'0', '\\'}, {'1', 'w'}, {'2', '2'}, {'3', 'i'}, {'4', 'E'},
        {'5', '9'}, {'6', ','}, {'7', 'h'}, {'8', '&'}, {'9', '^'}, {':', 'B'}, {';', 'G'},
        {'<', 'T'}, {'=', '0'}, {'>', 'l'}, {'?', '1'}, {'@', 'L'}, {'A', 'S'}, {'B', 'F'},
        {'C', 'q'}, {'D', 'K'}, {'E', 'm'}, {'F', 'n'}, {'G', 'R'}, {'H', '#'}, {'I', '*'},
        {'J', 'r'}, {'K', '-'}, {'L', 'V'}, {'M', 'g'}, {'N', '%'}, {'O', 'U'}, {'P', '`'},
        {'Q', 'p'}, {'R', '?'}, {'S', 's'}, {'T', 'W'}, {'U', ';'}, {'V', '5'}, {'W', 't'},
        {'X', 'Y'}, {'Y', 'd'}, {'Z', 'e'}, {'[', 'f'}, {'\\', 'I'}, {']', 'a'}, {'^', 'c'},
        {'_', 'j'}, {'`', 'J'}, {'a', '|'}, {'b', '['}, {'c', '3'}, {'d', ' '}, {'e', '+'},
        {'f', '4'}, {'g', '/'}, {'h', 'A'}, {'i', '='}, {'j', '@'}, {'k', 'Q'}, {'l', 'M'},
        {'m', 'x'}, {'n', '!'}, {'o', '('}, {'p', '<'}, {'q', '_'}, {'r', 'k'}, {'s', 'o'},
        {'t', '"'}, {'u', 'X'}, {'v', '.'}, {'w', 'P'}, {'x', '{'}, {'y', 'Z'}, {'z', 'C'},
        {'{', '6'}, {'|', ']'}, {'}', ':'}, {'~', 'H'}
    };

    string cipher_txt;
    
    // Encrypt the plaintext using the substitution map
    for (char c : plain_txt) {
        if (substitution_map.find(c) != substitution_map.end()) {
            cipher_txt += substitution_map.at(c); // Substitute character
        } else {
            cipher_txt += c; // Leave unchanged if not in the substitution map
        }
    }
    
    return cipher_txt;
}

// Main function
int main() {
    string input;
    unordered_map<char, int> mappings;

    // Initialize mappings
    initializeMappings(mappings);

    // Input from the user
    cout << "Enter a key: ";
    cin >> input;

    // Process the input to get encrypted numbers
    string encryptedNumbers;
    for (char ch : input) {
        if (mappings.find(ch) != mappings.end()) {
            encryptedNumbers += to_string(mappings[ch]) + " ";
        } else if (isdigit(ch)) {
            // If digits are found, simply output them as they are
            encryptedNumbers += ch + string(" ");
        } else {
            // For unrecognized characters
            encryptedNumbers += "78 ";
        }
    }

    // Combine numbers for the initial Caesar cipher key
    string combinedNumbers = combineNumbers(encryptedNumbers);
    vector<int> shifts = splitIntoShifts(combinedNumbers); // Get individual shifts

  //  cout << "Encrypted numbers: " << encryptedNumbers << endl;
   // cout << "Caesar cipher shifts: ";
    //for (int shift : shifts) {
    //    cout << shift << " ";  // Print each shift value
    //}
   // cout << endl;

    string plaintext;
    int numRounds;

    cout << "Enter the plaintext: ";
    cin.ignore();  // Ignore leftover newline character
    getline(cin, plaintext);  // Use getline to read the entire line including spaces

    cout << "Enter the number of rounds for encryption: ";
    cin >> numRounds;

    // Encrypt the plaintext using the substitution map
    string encryptedText = encryptSubstitution(plaintext);
   // cout << "After substitution encryption: " << encryptedText << endl;

    // Create a repeating key pattern based on the given key
    string keyPattern = combinedNumbers;
    while (keyPattern.length() < numRounds) {
        keyPattern += combinedNumbers;
    }
    keyPattern = keyPattern.substr(0, numRounds);  // Truncate to the required length

    vector<int> repeatingShifts;
    for (char ch : keyPattern) {
        if (isdigit(ch)) {
            repeatingShifts.push_back(ch - '0'); // Convert char digit to integer
        }
    }

    for (int round = 0; round < numRounds; ++round) {
        int shift = repeatingShifts[round]; // Use the repeating shift value

        // Print the Caesar cipher key (shift) for the current round
      //  cout << "Caesar cipher key for round " << round + 1 << ": " << shift << endl;

        // Perform Caesar cipher encryption
        encryptedText = encryptCaesar(encryptedText, shift);
      //  cout << "After Caesar cipher round " << round + 1 << ": " << encryptedText << endl;
      
        encryptedText = encryptSubstitution(encryptedText);

        // Perform Rail Fence cipher encryption
        encryptedText = railFenceEncrypt(encryptedText);
       // cout << "After Rail Fence cipher round " << round + 1 << ": " << encryptedText << endl;
    }

    // Add hidden padding after final encryption
    string finalEncryptedText = addHiddenPadding(encryptedText);
    cout << "Final encrypted text with padding: " << finalEncryptedText << endl;

    return 0;
}
