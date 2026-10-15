#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    // Base case: nothing left, so both output lists end here
    if(head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    // Detach the first node from the input list
    Node* curr = head;
    Node* rest = head->next;
    head = NULL;

    if(curr->val <= pivot) {
        // curr becomes the front of smaller; the rest of smaller hangs off curr->next
        smaller = curr;
        llpivot(rest, curr->next, larger, pivot);
    }
    else {
        // curr becomes the front of larger; the rest of larger hangs off curr->next
        larger = curr;
        llpivot(rest, smaller, curr->next, pivot);
    }
}
