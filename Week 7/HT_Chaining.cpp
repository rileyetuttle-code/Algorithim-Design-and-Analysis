/// Implementing Hashing Technique - Chaining
#include <iostream>
#include <vector>

using namespace std;

/// ---------- Node for a single bucket's linked list ----------
struct Node {
    int key;        // stored key
    int value;      // associated value
    Node* next;     // next node in the chain

    Node(int k, int v) : key(k), value(v), next(nullptr) {}
};

/// ---------- Hash table using separate chaining ----------
class HashTable {
private:
    vector<Node*> table; // array of bucket heads; each bucket is a linked list
    int size;            // number of buckets

    // Simple modulo-based hash function mapping a key to a bucket index
    int hash(int key) { return key % size; }

public:
    /// ----- Construct a table with 'sz' buckets, all initially empty -----
    HashTable(int sz) : size(sz) {
        table.resize(size, nullptr);
    }

    /// ----- Destructor: delete every node in every bucket to free memory -----
    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;   // save node
                current = current->next; // move forward
                delete temp;            // free saved node
            }
        }
    }

    /// ----- Insert a (key, value) pair into its bucket chain -----
    void insert(int key, int value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);

        // If bucket is empty, new node becomes head
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            // Otherwise, walk to the end of the chain and append
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    /// ----- Search for a key; return its value or -1 if not found -----
    int search(int key) {
        int index = hash(key);
        Node* current = table[index];

        // Linear scan through the bucket's linked list
        while (current != nullptr) {
            if (current->key == key)
                return current->value; // found
            current = current->next;
        }
        return -1; // not found in this bucket
    }

    /// ----- Remove a key (if present) by unlinking and deleting its node -----
    void remove(int key) {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                // If removing head of the chain, advance bucket head
                if (prev == nullptr) table[index] = current->next;
                else                 prev->next = current->next;
                delete current;  // free the removed node
                return;
            }
            prev = current;
            current = current->next;
        }
        // If we reach here, key wasn't found; function is a no-op
    }
};

/// ---------- Demo ----------
int main() {
    // Create a hash table with 10 buckets
    HashTable ht(10);

    // Insert some (key, value) pairs
    ht.insert(10, 100);
    ht.insert(20, 200);
    ht.insert(30, 300);

    // Search for a key
    int value = ht.search(20);
    if (value != -1) cout << "Value found: " << value << endl;
    else             cout << "Value not found" << endl;

    // Remove a key
    ht.remove(20);

    // Search again after removal
    value = ht.search(20);
    if (value != -1) cout << "Value found: " << value << endl;
    else             cout << "Value not found" << endl;

    return 0;
}
