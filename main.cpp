#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.cpp"
using namespace std;

// Max number of nodes in our tree
const int MAX_NODES = 64;

// Global arrays for node information
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};  // start all letter counts at 0

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // if file had no letters, exit nicely
    if (nextFree == 0) {
        cout << "Character : Code\n\nEncoded message:\n\n";
        return 0;
    }

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i; // store character
            weightArr[nextFree] = freq[i]; // store count
            leftArr[nextFree] = -1; // no children yet
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    MinHeap heap;

    // 2. Push all leaf node indices into the heap.
    for(int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }
    int curr = nextFree; // next open slot for internal nodes

    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    while(heap.size > 1) {
        int leftNode = heap.pop(weightArr); // smallest
        int rightNode = heap.pop(weightArr); // second smallest

        charArr[curr] = '\0'; // internal node
        leftArr[curr] = leftNode; // set left child
        rightArr[curr] = rightNode; // set right child
        weightArr[curr] = weightArr[leftNode] + weightArr[rightNode]; // cobined

        heap.push(curr, weightArr);
        curr++;
    }

    // 4. Return the index of the last remaining node (root)
    return heap.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    if(leftArr[root] == -1 && rightArr[root] == -1) {
        codes[charArr[root]-'a'] = "0";
        return;
    }

    stack<pair<int,string>> st;
    st.push({root, ""});

    while(!st.empty()) {
        auto top = st.top();
        st.pop();

        int node = top.first;
        string path = top.second;

        if (leftArr[node] == -1 && rightArr[node] == -1) {
            codes[charArr[node]-'a'] = path;
        } else {
            if (rightArr[node] != -1) {
                st.push({rightArr[node], path +"1"});

            }
            if (leftArr[node] != -1) {
                st.push({leftArr[node], path +"0"});
            }
        }

    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}