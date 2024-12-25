#include <iostream>
#include <string>
using namespace std;

// Structure for a patient record in the BST
struct PatientRecord {
    int id; // Unique patient ID
    string name;
    string history;
    PatientRecord* left;
    PatientRecord* right;
};

// Structure for a node in the patient queue
struct PatientQueue {
    int id; // Patient ID
    string name;
    string condition; // Condition description
    PatientQueue* next;
};

// Class for managing the patient queue
class PatientQueueManager {
private:
    PatientQueue* front;
    PatientQueue* rear;

public:
    PatientQueueManager() : front(nullptr), rear(nullptr) {}

    // Add a patient to the queue
    void enqueue(int id, string name, string condition) {
        PatientQueue* newNode = new PatientQueue{ id, name, condition, nullptr };
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Patient " << name << " added to the queue.\n";
    }

    // Remove a patient from the queue
    void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }
        PatientQueue* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        cout << "Patient " << temp->name << " treated and removed from the queue.\n";
        delete temp;
    }

    // Display the current queue
    void displayQueue() {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }
        PatientQueue* temp = front;
        cout << "Current Patient Queue:\n";
        while (temp != nullptr) {
            cout << "ID: " << temp->id << ", Name: " << temp->name
                << ", Condition: " << temp->condition << "\n";
            temp = temp->next;
        }
    }
};

// Class for managing patient records using a BST
class PatientRecordManager {
private:
    PatientRecord* root;

    // Helper function to insert a record
    PatientRecord* insertRecord(PatientRecord* node, int id, string name, string history) {
        if (node == nullptr) {
            return new PatientRecord{ id, name, history, nullptr, nullptr };
        }
        if (id < node->id) {
            node->left = insertRecord(node->left, id, name, history);
        }
        else if (id > node->id) {
            node->right = insertRecord(node->right, id, name, history);
        }
        return node;
    }

    // Helper function to search for a record
    PatientRecord* searchRecord(PatientRecord* node, int id) {
        if (node == nullptr || node->id == id) {
            return node;
        }
        if (id < node->id) {
            return searchRecord(node->left, id);
        }
        return searchRecord(node->right, id);
    }

    // In-order traversal to display records
    void displayRecords(PatientRecord* node) {
        if (node == nullptr) return;
        displayRecords(node->left);
        cout << "ID: " << node->id << ", Name: " << node->name
            << ", History: " << node->history << "\n";
        displayRecords(node->right);
    }

public:
    PatientRecordManager() : root(nullptr) {}

    // Insert a new patient record
    void addRecord(int id, string name, string history) {
        root = insertRecord(root, id, name, history);
        cout << "Record for " << name << " added.\n";
    }

    // Search for a patient record
    void searchRecord(int id) {
        PatientRecord* record = searchRecord(root, id);
        if (record == nullptr) {
            cout << "Record not found.\n";
        }
        else {
            cout << "Found Record - ID: " << record->id
                << ", Name: " << record->name
                << ", History: " << record->history << "\n";
        }
    }

    // Display all records
    void displayAllRecords() {
        cout << "Patient Records:\n";
        displayRecords(root);
    }
};

int main() {
    PatientQueueManager queueManager;
    PatientRecordManager recordManager;

    // Example usage:
    queueManager.enqueue(101, "Alice", "Flu");
    queueManager.enqueue(102, "Bob", "Fracture");
    queueManager.enqueue(103, "Charlie", "Headache");

    recordManager.addRecord(101, "Alice", "History of seasonal flu.");
    recordManager.addRecord(102, "Bob", "History of orthopedic issues.");
    recordManager.addRecord(103, "Charlie", "No prior medical history.");

    cout << "\n--- Patient Queue ---\n";
    queueManager.displayQueue();

    cout << "\n--- Patient Records ---\n";
    recordManager.displayAllRecords();

    cout << "\n--- Treating a Patient ---\n";
    queueManager.dequeue();

    cout << "\n--- Updated Patient Queue ---\n";
    queueManager.displayQueue();

    cout << "\n--- Searching for a Record ---\n";
    recordManager.searchRecord(102);

    return 0;
}