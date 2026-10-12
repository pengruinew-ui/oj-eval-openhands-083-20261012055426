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
    Node* prev = nullptr;
    
    // Build the circular linked list
    for (int i = 1; i <= n; i++) {
        Node* newNode = new Node(i);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            prev->next = newNode;
        }
        prev = newNode;
    }
    
    // Make it circular
    if (prev != nullptr) {
        prev->next = head;
    }
    
    Node* current = head;
    
    // Josephus elimination process
    while (n > 0) {
        if (n == 1) {
            // Last node
            cout << current->data << endl;
            delete current;
            break;
        }
        
        if (m == 1) {
            // Delete current node
            cout << current->data << endl;
            
            // Find the previous node (need to traverse)
            Node* prev = current;
            while (prev->next != current) {
                prev = prev->next;
            }
            
            // Remove current node
            prev->next = current->next;
            Node* nextNode = current->next;
            
            // Update head if necessary
            if (current == head) {
                head = nextNode;
            }
            
            delete current;
            current = nextNode;
            n--;
        } else {
            // Find the (m-1)th node from current
            for (int i = 1; i < m - 1; i++) {
                current = current->next;
            }
            
            // The node to delete is current->next
            Node* toDelete = current->next;
            cout << toDelete->data << endl;
            
            // Remove the node
            current->next = toDelete->next;
            
            // Update head if necessary
            if (toDelete == head) {
                head = toDelete->next;
            }
            
            // Next counting starts from the node after the deleted one
            current = toDelete->next;
            
            delete toDelete;
            n--;
        }
    }
    
    return 0;
}