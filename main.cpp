#include <iostream>
#include <cstring>
using namespace std;

struct node {
    char key;          // last character of the key
    string value;     // actual string value
    bool tombstone;   // flag for soft deletion
};

struct Hash_Table {
    int capacity;
    int number_of_elements;
    struct node **array;
};

void Intialize_Hash(struct Hash_Table *HT) {
    HT->number_of_elements = 0;
    HT->capacity = 26;
    HT->array = (struct node **)malloc(sizeof(struct node *) * HT->capacity);

    // Initialize to null values
    for (int i = 0; i < HT->capacity; i++) {
        HT->array[i] = nullptr;
    }
}

void Intialize_Node(struct node *node, string value) {
    node->key = value.back(); // last character
    node->value = value;
    node->tombstone = false;
}

int Hash_Value(char last_letter) {
    return last_letter - 'a'; // 'a' corresponds to index 0
}

int Search(struct Hash_Table *HT, char key) {
    int pos = Hash_Value(key);
    int loop_counter = 0;

    while (loop_counter < HT->capacity) {
        if (HT->array[pos] == nullptr) {
            return -1; // Not found
        }
        if (!HT->array[pos]->tombstone && HT->array[pos]->key == key) {
            return pos; // Found
        }
        pos = (pos + 1) % HT->capacity; // Linear probing
        loop_counter++;
    }
    return -1; // Not found after probing all slots
}

void Delete(struct Hash_Table *HT, string value) {
    char last_letter = value.back();
    int pos = Search(HT, last_letter);
    if (pos != -1) {
        HT->array[pos]->tombstone = true; // Mark as tombstone
    }
}

void Insert(struct Hash_Table *HT, string value) {
    char last_letter = value.back();
    // Check if the key already exists
    if (Search(HT, last_letter) != -1) {
        return; // Key already exists, do nothing
    }

    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    Intialize_Node(new_node, value);

    int pos = Hash_Value(last_letter);
    int loop_counter = 0;

    while (loop_counter < HT->capacity && HT->array[pos] != nullptr && !HT->array[pos]->tombstone) {
        pos = (pos + 1) % HT->capacity; // Linear probing
        loop_counter++;
    }

    HT->array[pos] = new_node; // Insert new node
    HT->number_of_elements++;
}

void Display_Hash_Table(struct Hash_Table *HT) {
    for (int i = 0; i < HT->capacity; i++) {
        if (HT->array[i] != nullptr && !HT->array[i]->tombstone) {
            cout << HT->array[i]->value << " "; // Display the value
        }
    }
    cout << endl; // Newline at the end of output
}

int main() {
    struct Hash_Table HT;
    Intialize_Hash(&HT);
    string input;
    getline(cin, input);
    int last_space = 0;

    for (int i = 0; i <= input.length(); i++) {
        if (i == input.length() || input[i] == ' ') {
            string values = input.substr(last_space, i - last_space);  // Extracting the word correctly
            last_space = i + 1;

            if (values[0] == 'A') {
                string val = values.substr(1);  // Extract the value after 'A'
                Insert(&HT, val);
            } else if (values[0] == 'D') {
                string val = values.substr(1);  // Extract the value after 'D'
                Delete(&HT, val);
            }
        }
    }

    Display_Hash_Table(&HT);

    // Free allocated memory
    for (int i = 0; i < HT.capacity; i++) {
        if (HT.array[i] != nullptr) {
            free(HT.array[i]); // Free each node
        }
    }
    free(HT.array); // Free the hash table array

    return 0;
}
