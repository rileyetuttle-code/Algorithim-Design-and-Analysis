/// Implementing Hashing Technique - Linear Probing
#include <iostream>
#include <stdlib.h>

using namespace std;

template<class T>
class HashTable {
private:
    // Returns an index where key k should be placed OR already exists.
    // NOTE: despite the name, this does BOTH the base hash (k % D)
    // and the linear probing loop to find an open slot or the key.
    int HashFunction(const T& k) const;

    int D;      // Table size (divisor for modulo hash)
    T *ht;      // The actual bucket array
    int *empty; // Parallel array: 1 = empty bucket, 0 = occupied
public:
    // Construct a table of size 'divisor' and mark all buckets empty.
    HashTable(int divisor = 11);

    // Destroy arrays allocated in the constructor.
    ~HashTable() {
        delete [] ht;
        delete [] empty;
    }

    // Look up key k; if found, copy it to e and return 1, else return 0.
    int Search(const T& k, T& e) const;

    // Insert element e using linear probing. Returns *this for chaining.
    HashTable<T>& Insert(const T& e);

    // Print the table contents; empty buckets are shown as 0.
    void Display();

    // Remove element e if present (simple "mark empty" delete).
    void Delete(T e);
};

template<class T>
HashTable<T>::HashTable(int divisor) {
    D = divisor;
    ht = new T[D];
    empty = new int[D];
    // Initially every bucket is empty.
    for (int i = 0; i < D; i++)
        empty[i] = 1;
}

template<class T>
int HashTable<T>::HashFunction(const T& k) const {
    // Start at the base hash index.
    int i = k % D;
    int j = i;

    // Scan forward one step at a time (linear probing)
    // until we find an empty bucket or the key itself.
    // If we wrap around to the start, stop.
    do {
        if (empty[j] || ht[j] == k) return j;   // found hole or match
        j = (j + 1) % D;                        // next bucket
    } while (j != i);

    // If table is full, this returns the start index.
    // (Insert will treat this as "No memory" later.)
    return j;
}

template<class T>
void HashTable<T>::Delete(T e) {
    // Locate the bucket where e would live or be inserted.
    int b = HashFunction(e);

    // If that bucket is occupied by e, mark it empty.
    // (This implementation uses "true empty", not a tombstone.)
    if (!empty[b] && ht[b] == e) {
        ht[b] = 0;     // sets value to 0 (works for int, not generic T)
        empty[b] = 1;  // mark bucket empty
    } else {
        cout << "\nElement not found";
    }
}

template<class T>
int HashTable<T>::Search(const T& k, T& e) const {
    // Find the bucket where k would be or where the scan should stop.
    int b = HashFunction(k);

    // If bucket is empty or contains a different key, it's not found.
    if (empty[b] || ht[b] != k) return 0;

    // Otherwise, return the stored element.
    e = ht[b];
    return 1;
}

template<class T>
HashTable<T>& HashTable<T>::Insert(const T& e) {
    T k = e;
    int b = HashFunction(k);

    // Case 1: we found an empty slot — place the element here.
    if (empty[b]) {
        empty[b] = 0;
        ht[b] = e;
        return *this;
    }

    // Case 2: the same key already exists at b — reject as duplicate.
    if (ht[b] == k) {
        cout << "\nBad input";
        return *this;
    }

    // Case 3: table was full during probing — no slot available.
    cout << "\nNo memory";
    return *this;
}

template<class T>
void HashTable<T>::Display() {
    cout << endl;
    for (int i = 0; i < D; i++) {
        if (empty[i]) cout << "0 ";
        else          cout << ht[i] << " ";
    }
    cout << endl;
}

int main() {
    HashTable<int> h(11);
    int e;

    // Insert a few values.
    e = 80; h.Insert(e);
    e = 40; h.Insert(e);
    e = 65; h.Insert(e);
    cout << "\nAfter inserting 80,40,65:";
    h.Display();
    cout << endl;

    // Delete one value.
    h.Delete(40);
    cout << "\nAfter deleting 40:";
    h.Display();
    cout << endl;

    // More inserts.
    e = 58; h.Insert(e);
    e = 24; h.Insert(e);
    cout << "\nAfter appending 58, 24:";
    h.Display();

    // Attempt to delete a non-existent value.
    cout << "\nTrying to delete element 25:";
    h.Delete(25);
    h.Display();

    // Fill in more values to exercise probing.
    e = 2;  h.Insert(e);
    e = 13; h.Insert(e);
    e = 46; h.Insert(e);
    e = 16; h.Insert(e);
    e = 7;  h.Insert(e);
    e = 21; h.Insert(e);
    h.Insert(10);
    cout << "\nAfter inserting more values:" << endl;
    h.Display();

    // Try to insert when the table may be near full.
    e = 99;
    cout << "\nTrying to insert 99:";
    h.Insert(e);
    h.Display();
}
