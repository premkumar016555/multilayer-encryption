
//all round decryption

#include <iostream> 
#include <unordered_map> 
#include <cctype> 
#include <string> 
#include <vector> 
#include <sstream> 
#include <iomanip> 
#include <stdexcept> 
#include <cstdlib> 
#include <ctime> 
#include <map> 
 
using namespace std; 
 
// Function to initialize symbol and letter mappings 
void initializeMappings(unordered_map<char, int>& map) { 
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
 
    int startValue = 50; 
    for (char ch = 'A'; ch <= 'Z'; ++ch) { 
        map[ch] = startValue; 
        startValue += 1; 
    } 
 
    startValue = 10; 
    for (char ch = 'a'; ch <= 'z'; ++ch) { 
        map[ch] = startValue; 
        startValue += 1; 
    } 
} 
 
// Function to decrypt a text using Rail Fence cipher 

string railFenceDecrypt(const string &text) {
    int numRails = 3;
    const vector<int> railOrder = {2, 0, 1}; // User-defined rail order
    if (numRails == 1) return text;

    // Create a 2D vector to represent the rails
    vector<string> rail(numRails);

    // Determine the pattern of rail positions
    vector<int> pattern;
    int row = 0;
    bool down = true;
    for (int i = 0; i < text.length(); ++i) {
        pattern.push_back(row);
        if (row == 0) {
            down = true;
        } else if (row == numRails - 1) {
            down = false;
        }
        row += down ? 1 : -1;
    }

    // Calculate the number of characters in each rail
    vector<int> railLengths(numRails, 0);
    for (int pos : pattern) {
        railLengths[pos]++;
    }

    // Distribute the characters of the encrypted text into the rails according to the rail order
    int index = 0;
    for (int i : railOrder) {
        rail[i] = text.substr(index, railLengths[i]);
        index += railLengths[i];
    }

    // Reconstruct the original text using the pattern
    string result;
    vector<int> railPos(numRails, 0);
    for (int pos : pattern) {
        result += rail[pos][railPos[pos]++];
    }

    return result;
}

// Function to decrypt a ciphertext using Caesar cipher

// Function to decrypt the ciphertext using a shuffled alphabet and a shift key
string decryptCaesar(const string& ciphertext, int shift) {
    const string shuffledAlphabet = "ndI;6MXHp.NE5 :TBC*?e/risY8,xqQlU_\"awP3y$fOb'o4)\\+Kv]Vz&%F|-kg~u0>=@{c[7m}jt#W<SAZL2JD9(^`GhR1!";  // Predefined shuffled alphabet
    string plaintext = "";

    for (char c : ciphertext) {
        if (c >= 32 && c <= 126) {  // Check if the character is within the printable ASCII range
            int originalIndex = shuffledAlphabet.find(c);  // Find the index of the character in the shuffled alphabet
            if (originalIndex != string::npos) {  // Check if the character was found
                int newIndex = (originalIndex - shift + 95) % 95;  // Calculate the new index with the reverse shift
                plaintext += shuffledAlphabet[newIndex];  // Map to the shuffled alphabet
            } else {
                plaintext += c;  // If the character is not found, leave it unchanged
            }
        } else {
            plaintext += c;  // If the character is outside the printable ASCII range, do not decrypt it
        }
    }

    return plaintext;
}
// Function to combine numbers from the key 
string combineNumbers(const string& input) { 
    string combined; 
    for (char ch : input) { 
        if (isdigit(ch)) { 
            combined += ch; 
        } 
    } 
    return combined; 
} 
 
// Function to split the combined number string into individual digits 
vector<int> splitIntoShifts(const string& combinedNumbers) { 
    vector<int> shifts; 
    for (char ch : combinedNumbers) { 
        if (isdigit(ch)) { 
            shifts.push_back(ch - '0'); 
        } 
    } 
    return shifts; 
} 
 
// Function to remove hidden padding based on the known pattern 
string removeHiddenPadding(const string& paddedText) { 
    string originalText;
    int paddingLength = 0;
    
    // Find the position of the 'p' marker, but ensure it's not the first character
    size_t markerPos = paddedText.find('p', 1); // Start searching from the second character
    
    if (markerPos != string::npos && markerPos > 0) {
        // Calculate padding length as the distance between the first character and the 'p' marker
        paddingLength = markerPos - 1;
    } else {
        // If no marker is found or marker is at the first position, return the original text
        return paddedText;
    }

    // Iterate through the padded text and remove the padding
    for (size_t i = 0; i < paddedText.size();) {
        char ch = paddedText[i];

        // Add the first character to decrypted text and handle padding
        if (i == 0) {
            originalText += ch;
            i += paddingLength + 2;  // Skip padding and the marker
        } else {
            originalText += ch;
            i += paddingLength + 1;  // Skip the padding after each character
        }
    }

    return originalText;
}
 
// Function to decrypt the text using the reverse substitution map 
string decryptSubstitution(const string& cipher_txt) { 
    // Reverse substitution map for decryption 
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

    // Create a reverse substitution map for decryption
    unordered_map<char, char> reverse_substitution_map;
    for (const auto& pair : substitution_map) {
        reverse_substitution_map[pair.second] = pair.first;
    }

    string decrypted_txt;
    
    // Decrypt the ciphertext using the reverse substitution map
    for (char c : cipher_txt) {
        if (reverse_substitution_map.find(c) != reverse_substitution_map.end()) {
            decrypted_txt += reverse_substitution_map.at(c); // Reverse substitute character
        } else {
            decrypted_txt += c; // Leave unchanged if not in the reverse substitution map
        }
    }
    
    return decrypted_txt;
}
 
// Main decryption function 
int main() { 
    string encryptedText; 
    unordered_map<char, int> mappings; 
 
    initializeMappings(mappings); 
 
     
    int numRounds; 
 
    cout << "Enter the encrypted text with padding:"; 
    getline(cin, encryptedText); // Use getline to handle spaces 
  //  cout << "Enter the number of rounds for decryption: "; 
   // cin >> numRounds; 
    // Remove hidden padding before decryption 
    string textWithoutPadding = removeHiddenPadding(encryptedText); 
  //  cout << "Text without padding: " << textWithoutPadding << endl; 
   // cin.ignore();  // Ignore leftover newline character 
    string input; 
    cout << "Enter the key used for encryption: "; 
    getline(cin, input); // Use getline to handle keys with spaces 
 
 for(numRounds=0;numRounds<=100;numRounds++){
    string encryptedNumbers; 
    for (char ch : input) { 
        if (mappings.find(ch) != mappings.end()) { 
            encryptedNumbers += to_string(mappings[ch]) + " "; 
        } else if (isdigit(ch)) { 
            encryptedNumbers += ch + string(" "); 
        } else { 
            encryptedNumbers += "78 "; 
        } 
    } 
 
    string combinedNumbers = combineNumbers(encryptedNumbers); 
    vector<int> shifts = splitIntoShifts(combinedNumbers); 
 
   // cout << "Combined numbers: " << combinedNumbers << endl; 
  //  cout << "Shifts: "; 
   // for (int shift : shifts) { 
       // cout << shift << " "; 
    //} 
   // cout << endl; 
 
    string decryptedText = textWithoutPadding; 
 
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
 
    // Debug output for key pattern 
   // cout << "Key Pattern: " << keyPattern << endl; 
    //cout << "Repeating Shifts: "; 
   // for (int shift : repeatingShifts) { 
      //  cout << shift << " "; 
  //  } 
    //cout << endl; 
 
    // Decrypt in reverse order 
    for (int round = numRounds - 1; round >= 0; --round) { 
        int shift = (round < repeatingShifts.size()) ? repeatingShifts[round] : 0; 
 
        // Print the Caesar cipher key (shift) for the current round 
   //     cout << "Caesar cipher key for round " << round + 1 << ": " << shift << endl; 
 
        // Perform Rail Fence cipher decryption 
        decryptedText = railFenceDecrypt(decryptedText); 
        
        decryptedText = decryptSubstitution(decryptedText); 
 
        // Perform Caesar cipher decryption 
        decryptedText = decryptCaesar(decryptedText, shift); 
    //    cout << "After Caesar cipher round " << round + 1 << ": " << decryptedText << endl; 
    } 
 
    // Reverse Substitution map decryption 
    decryptedText = decryptSubstitution(decryptedText); 
    cout << numRounds<<":"<< decryptedText << endl; 
 
}
    return 0;
}


