#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Size of the hash table (spellbook)
const int TABLE_SIZE = 10;

// Struct to represent a spell (key-value pair)
struct Spell {
    string spellName;
    string effect;
    Spell* next;  // Pointer for collision handling (chaining)

    // Constructor
    Spell(string name, string eff) : spellName(name), effect(eff), next(nullptr) {}
};

// Hash table (spellbook) class
class Spellbook {
private:
    vector<Spell*> table;  // The pages of the spellbook (hash table)

    int hashFunction(string spellName) {
        // Example: Return the sum of ASCII values of the spellName characters
        // as the hash value, then return the modulus of the hash and table size.
        int hash = 0;
        for (int i = 0; i < spellName.length(); i++) {
            hash += spellName[i];  // Sum of ASCII values of characters
        }
        return hash % TABLE_SIZE;        

    }

public:
    // Constructor
    Spellbook() {
        table.resize(TABLE_SIZE, nullptr);  // Initialize the spellbook with empty pages
    }

    // TODO: Complete the addSpell function to insert a spell into the hash table
    void addSpell(string spellName, string effect) {
        int index = hashFunction(spellName);
        Spell* newSpell = new Spell(spellName, effect);

        // Collision handling logic goes here (use chaining)
        // If no collision, insert the spell. If collision, handle it.
        if(table[index] == nullptr)
        {
            table[index] = newSpell;
        }
        else
        {
            Spell* current = table[index];

            while(current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newSpell;

            cout << "Collision at page " << index << ": '" << spellName << "' chained after '" << newSpell->spellName;

        }
        
        cout << "The spell '" << spellName << "' has been added to the spellbook!\n";
    }

    // TODO: Complete the castSpell function to retrieve a spell from the hash table
    void castSpell(string spellName) {
        int index = hashFunction(spellName);
        Spell* current = table[index];
        
        while(current != nullptr && current->spellName != spellName)
        {
            current = current->next;
        }

        // Traverse the linked list (chaining) at the index to find the spell
        // If found, print the spell's effect, else print "not found"
        if(current != nullptr)
        {
            cout << "Casting '" << spellName << "': " << current->effect << endl;
        }
        else{
            cout << "The spell '" << spellName << "' was not found" << endl;
        }
       
    }

    // TODO: Complete the removeSpell function to delete a spell from the hash table
    void removeSpell(string spellName) {
        int index = hashFunction(spellName);
        Spell* current = table[index];
        Spell* previous = nullptr;

        // Traverse the linked list and remove the spell if found
        while(current != nullptr)
        {
            if(current->spellName == spellName)
            {
                if(previous == nullptr)
                {
                    table[index] = current->next;
                }
                else{
                    previous->next = current->next;
                }

                delete current;
                cout << "The spell '" << spellName << "' has been removed from the spellbook.\n";
                return;
            }

            previous = current;
            current = current->next;
        }

    }
};

int main() {
    // Create the spellbook
    Spellbook spellbook;

    // TODO: Add 6 test cases
    spellbook.addSpell("Fireball", "Deals 100 fire damage.");
    spellbook.addSpell("Healing Light", "Restores 50 health.");
    spellbook.addSpell("Lightning Bolt", "Stuns for 1 second, and deals 50 damage.");
    spellbook.addSpell("Freeze", "Stuns for 3 seconds and deals 15 damage. ");
    spellbook.addSpell("Forcefield", "Damage protection for 5 seconds.");
    spellbook.addSpell("Laser Zap", "Deals 75 damage.");

    
    // Test 3 retrievals
    spellbook.castSpell("Fireball");
    spellbook.castSpell("Forcefield");
    spellbook.castSpell("Laser Zap");

    // Test 2 spell deletion
    spellbook.removeSpell("Healing Light");
    spellbook.removeSpell("Freeze");

    // Retrieval attempt
    spellbook.castSpell("Freeze");

    // // ---------- Test Case 2 ----------
    // cout << "\n--- Test Case 2 ---\n";
    // Spellbook book2;
    // book2.addSpell("Invisibility", "Become unseen for 10 seconds.");
    // book2.addSpell("Teleport", "Instantly teleports you to a known location.");
    // book2.addSpell("Frostbite", "Slows enemies by 40 percent.");
    // book2.addSpell("Thunderstrike", "Deals 120 lightning damage.");
    // book2.addSpell("Shadow Step", "Teleports you behind a target.");
    // book2.addSpell("Arcane Shield", "Absorbs 80 damage.");

    // book2.castSpell("Teleport");
    // book2.castSpell("Shadow Step");
    // book2.castSpell("Arcane Shield");

    // book2.removeSpell("Frostbite");
    // book2.removeSpell("Thunderstrike");
    // book2.castSpell("Thunderstrike");

    // // ---------- Test Case 3 ----------
    // cout << "\n--- Test Case 3 ---\n";
    // Spellbook book3;
    // book3.addSpell("Poison Dart", "Deals 10 damage per second for 5 seconds.");
    // book3.addSpell("Earthquake", "Deals 90 damage to all nearby enemies.");
    // book3.addSpell("Wind Gust", "Knocks enemies back 10 feet.");
    // book3.addSpell("Stone Skin", "Reduces damage taken by 30 percent.");
    // book3.addSpell("Mind Read", "Reveals the target's next move.");
    // book3.addSpell("Soul Drain", "Steals 40 health from a target.");

    // book3.castSpell("Poison Dart");
    // book3.castSpell("Soul Drain");
    // book3.castSpell("Mind Read");

    // book3.removeSpell("Earthquake");
    // book3.removeSpell("Wind Gust");
    // book3.castSpell("Earthquake");


    return 0;
}
