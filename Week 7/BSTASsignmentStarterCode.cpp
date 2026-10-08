#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    int phone;
    Contact* left;
    Contact* right;

    // constructor that helps initialize pointer values and can be used later to simplify creating new nodes and assigning their values all in one step
    Contact(string n, int p) {
        name = n;
        phone = p;
        left = nullptr;
        right = nullptr;
    }
};
class ContactBST {
private:
    Contact* root;
    // Insert contact
    Contact* insert(Contact* node, string name, int phone) {
        Contact* t = node;
        Contact* r = NULL;

        // if tree is empty, constructor called to create new node at root
        if(node == NULL)
        {
            node = new Contact(name, phone);
            return node;
        }

        // if tree is not empty, iterate through t pointer in binary search tree conditions until in right spot at end of its subtree depending on alphabetical name
        while(t != NULL)
        {
            r = t;
            if(name < t->name)
            {
                t = t->left;
            }
            else if(name > t->name)
            {
                t = t->right;
            }
            else
            {
                return node;
            }
        }

        // new node p so the root is not overwritten and constructor in 
        // struct uses input parameters to set the name and number = to 
        // those inputs 
        Contact* p = new Contact(name, phone);

        // compare against r pointer to determine which side of the found leaf node the child will be inserted on
        if(name < r->name)
        {
            r->left = p;
        }
        else
        {
            r->right = p;
        }

        return node;
    }

    // Search for a contact by name
    Contact* search(Contact* node, string name) {
        Contact *t = root; // start temp pointer at root

        // iterate through t based on BST restrictions until correct name is found in t
        while(t != NULL)
        {
            if(t->name == name)
            {
                return t;
            }
            else if(name < t->name)
            {
                t = t->left;
            }
            else
                t = t->right;
        }

        return NULL;
    }

    // Find the minimum node (for deletion)
    Contact* findMin(Contact* node) {
        Contact* min = node; // temp min node starting at whereever node is

        // iterate through min while it and its left child are not null
        while(min != NULL && min->left != NULL)
        {
            min = min->left;
        }

        // min has been found 
        return min;
    }

    // Delete a contact by name
    Contact* deleteContact(Contact* node, string name) 
    {
        // if tree is empty
        if(node == NULL)
        {
            return NULL;
        }

        // if only one node in tree
        if(node->left == NULL && node->right == NULL && node->name == name)
        {
            if(node == root)
            {
                root = NULL;
            }

            delete node;
            return NULL;
        }

        // normal cases
        if(name < node->name)
        {
            node->left = deleteContact(node->left, name);
        }
        else if(name > node->name)
        {
            node->right = deleteContact(node->right, name);
        }
        else // once found, we have to determine how to handle children
        {
            if(node->left == NULL) // no left child
            {
                Contact* child = node->right;
                delete node; 
                return child; // returning child in place of the deleted node in the previous if call to keep the tree connected
            }
            else if(node->right == NULL) // no right child
            {
                Contact* child = node->left;
                delete node;
                return child; // returning child in place of the deleted node in the previous if call to keep the tree connected
            }
            else // two children 
            {
                Contact* succ = findMin(node->right); // finding smallest name in right subtree to copy it up and keep the BST structure

                // copy data of replacement(min in right subtree) up to node and delete where the replacement came from
                node->name = succ->name;
                node->phone = succ->phone;
                node->right = deleteContact(node->right, succ->name);
            }
        }

        return node; 
    }

     // Inorder traversal
    void inorder(Contact* node) {
        // base case
        if(node == NULL)
        {
            return;
        }

        // inorder traversal uses recursion going through all the way to farthest left node, outputs values, goes back to root to output and then to the right node
        inorder(node->left);
        cout << "Contact: " << node->name << ", " << node->phone << endl;
        inorder(node->right);
    }

    public:
    ContactBST() : root(nullptr) {}

    void insertContact(string name, int phone) {
        root = insert(root, name, phone);
    }

    void searchContact(string name) {
        Contact* result = search(root, name);
        if (result == nullptr) {
            cout << "Contact not found!" << endl;
        } else {
            cout << "Found: " << result->name << " - " << result->phone << endl;
        }
    }

    void deleteContact(string name) {
        root = deleteContact(root, name);
    }

    void listContacts() {
        inorder(root);
    }
};

int main() {
    ContactBST contacts;
    contacts.insertContact("Alice", 12345);
    contacts.insertContact("Bob", 67890);
    contacts.insertContact("Charlie", 54321);

    cout << "All Contacts (Inorder Traversal): " << endl;
    contacts.listContacts();

    cout << "\nSearching for 'Bob':" << endl;
    contacts.searchContact("Bob");

    cout << "\nDeleting 'Bob':" << endl;
    contacts.deleteContact("Bob");

    cout << "\nAll Contacts After Deletion: " << endl;
    contacts.listContacts();

    return 0;
}