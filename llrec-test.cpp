#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


// Recursive helper: reads the remaining integers in the stream into a list
Node* readRest(ifstream& ifile)
{
    int v;
    if( ! (ifile >> v) ) return NULL;
    Node* h = new Node(v, NULL);
    h->next = readRest(ifile);
    return h;
}

Node* readList(const char* filename)
{
    ifstream ifile(filename);
    return readRest(ifile);
}

// Recursive helper: prints each value then moves to the next node
void printRest(Node* head)
{
    if(head == NULL) return;
    cout << head->val << " ";
    printRest(head->next);
}

void print(Node* head)
{
    printRest(head);
    cout << endl;
}

void dealloc(Node* head)
{
    if(head == NULL) return;
    dealloc(head->next);
    delete head;
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------

// Returns true when the value is odd (so odd values get filtered out)
struct IsOdd {
    bool operator()(int value) {
        return value % 2 != 0;
    }
};

// Returns true when the value is greater than a threshold
struct GreaterThan {
    GreaterThan(int t) : threshold(t) {}
    bool operator()(int value) {
        return value > threshold;
    }
    int threshold;
};




int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code

    // llpivot: start smaller/larger as garbage on purpose
    Node* smaller = (Node*) 0x1;
    Node* larger = (Node*) 0x1;
    llpivot(head, smaller, larger, 10);
    cout << "Pivot 10 -> smaller: ";
    print(smaller);
    cout << "Pivot 10 -> larger: ";
    print(larger);
    cout << "Head after pivot: ";
    print(head);

    // llfilter: remove odd values from smaller, values > 15 from larger
    smaller = llfilter(smaller, IsOdd());
    cout << "smaller without odds: ";
    print(smaller);
    larger = llfilter(larger, GreaterThan(15));
    cout << "larger without values > 15: ";
    print(larger);

    dealloc(smaller);
    dealloc(larger);

    // Empty list cases
    Node* empty = NULL;
    llpivot(empty, smaller, larger, 5);
    cout << "Empty pivot -> smaller: ";
    print(smaller);
    cout << "Empty pivot -> larger: ";
    print(larger);
    cout << "Empty filter: ";
    print(llfilter(empty, IsOdd()));

    return 0;

}
