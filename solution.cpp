#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // Create circular linked list manually
    Node* head = new Node(1);
    Node* current = head;
    
    for (int i = 2; i <= n; i++) {
        current->next = new Node(i);
        current = current->next;
    }
    
    // Make it circular
    current->next = head;
    
    // Start from node 1
    current = head;
    int remaining = n;
    
    while (remaining > 0) {
        if (remaining == 1) {
            // Last node
            cout << current->data << '\n';
            delete current;
            break;
        }
        
        if (m == 1) {
            // Delete current node
            cout << current->data << '\n';
            
            // Find the previous node
            Node* prev = current;
            while (prev->next != current) {
                prev = prev->next;
            }
            
            // Remove current node
            prev->next = current->next;
            Node* nextNode = current->next;
            
            delete current;
            current = nextNode;
            remaining--;
        } else {
            // Find the node before the one to delete
            Node* prev = current;
            for (int i = 0; i < m - 2; i++) {
                prev = prev->next;
            }
            
            // The node to delete is prev->next
            Node* toDelete = prev->next;
            cout << toDelete->data << '\n';
            
            // Remove the node
            prev->next = toDelete->next;
            
            // Next counting starts from the node after the deleted one
            current = toDelete->next;
            
            delete toDelete;
            remaining--;
        }
    }
    
    return 0;
}