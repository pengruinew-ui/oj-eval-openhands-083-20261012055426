#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    
public:
    CircularLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Insert node at the end of the list
    void insert(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            // First node - points to itself
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
        } else {
            // Insert at end and maintain circular property
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
        size++;
    }
    
    // Remove the m-th node starting from current position
    // Returns the value of the removed node
    int removeMthNode(int m, Node*& current) {
        if (size == 0) return -1;
        
        // Move to the node before the one to be deleted
        for (int i = 1; i < m - 1; i++) {
            current = current->next;
        }
        
        // Node to delete is current->next
        Node* toDelete = current->next;
        int deletedValue = toDelete->data;
        
        // Remove the node
        if (size == 1) {
            // Last node
            head = nullptr;
            tail = nullptr;
            current = nullptr;
        } else {
            // Update links
            current->next = toDelete->next;
            
            // Update head or tail if necessary
            if (toDelete == head) {
                head = toDelete->next;
            }
            if (toDelete == tail) {
                tail = current;
            }
        }
        
        delete toDelete;
        size--;
        
        // Move to next node for counting
        if (current != nullptr) {
            current = current->next;
        }
        
        return deletedValue;
    }
    
    // Get current size
    int getSize() const { return size; }
    
    // Get head pointer
    Node* getHead() const { return head; }
    
    // Destructor to clean up memory
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode;
        
        // Delete all nodes
        for (int i = 0; i < size; i++) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    // Create circular linked list with nodes 1 to n
    CircularLinkedList list;
    for (int i = 1; i <= n; i++) {
        list.insert(i);
    }
    
    // Start from node 1
    Node* current = list.getHead();
    
    // Remove nodes one by one
    while (list.getSize() > 0) {
        int removedValue = list.removeMthNode(m, current);
        cout << removedValue << endl;
    }
    
    return 0;
}