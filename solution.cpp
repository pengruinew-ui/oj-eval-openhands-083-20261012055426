#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

int main() {
    int n, m;
    cin >> n >> m;
    
    // Create circular linked list with nodes 1 to n
    Node* head = nullptr;
    Node* tail = nullptr;
    
    // Build the circular linked list
    for (int i = 1; i <= n; i++) {
        Node* newNode = new Node(i);
        
        if (head == nullptr) {
            // First node
            head = newNode;
            tail = newNode;
            newNode->next = newNode; // Points to itself
        } else {
            // Add to end
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
    }
    
    Node* current = head;
    int remaining = n;
    
    // Josephus elimination process
    while (remaining > 0) {
        if (remaining == 1) {
            // Last node - output and delete
            cout << current->data << endl;
            delete current;
            break;
        }
        
        if (m == 1) {
            // Special case: delete current node
            Node* toDelete = current;
            cout << toDelete->data << endl;
            
            // Find the previous node (tail)
            Node* prev = tail;
            prev->next = current->next;
            
            // Update head or tail if necessary
            if (toDelete == head) {
                head = toDelete->next;
            }
            if (toDelete == tail) {
                tail = prev;
            }
            
            current = current->next;
            delete toDelete;
            remaining--;
        } else {
            // Find the node before the one to delete
            Node* prev = current;
            for (int i = 1; i < m - 1; i++) {
                prev = prev->next;
            }
            
            // Node to delete
            Node* toDelete = prev->next;
            cout << toDelete->data << endl;
            
            // Remove the node
            prev->next = toDelete->next;
            
            // Update head or tail if necessary
            if (toDelete == head) {
                head = toDelete->next;
            }
            if (toDelete == tail) {
                tail = prev;
            }
            
            // Next counting starts from the node after the deleted one
            current = toDelete->next;
            delete toDelete;
            remaining--;
        }
    }
    
    return 0;
}