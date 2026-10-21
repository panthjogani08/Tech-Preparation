
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

Node* head = NULL;

void insertBeginning(int x)
{
    Node* newNode = new Node{x, head};
    head = newNode;
}

void insertEnd(int x)
{
    Node* newNode = new Node{x, NULL};

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void insertAfter(int key, int x)
{
    Node* temp = head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL)
    {
        cout << "Node not found\n";
        return;
    }

    Node* newNode = new Node{x, temp->next};
    temp->next = newNode;
}

void deleteFirst()
{
    if (head == NULL)
    {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;
}

void deleteLast()
{
    if (head == NULL)
    {
        cout << "List is empty\n";
        return;
    }

    if (head->next == NULL)
    {
        delete head;
        head = NULL;
        return;
    }

    Node* temp = head;

    while (temp->next->next != NULL)
        temp = temp->next;

    delete temp->next;
    temp->next = NULL;
}

void deleteAfter(int key)
{
    Node* temp = head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
    {
        cout << "Node not found or no next node\n";
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;
    delete del;
}

void display()
{
    Node* temp = head;

    if (temp == NULL)
    {
        cout << "List is empty\n";
        return;
    }

    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << "NULL\n";
}

int main()
{
    insertBeginning(20);
    insertBeginning(10);
    insertEnd(30);
    insertAfter(20, 25);

    cout << "Linked List: ";
    display();

    deleteFirst();
    cout << "After deleting first node: ";
    display();

    deleteLast();
    cout << "After deleting last node: ";
    display();

    insertEnd(40);
    insertEnd(50);
    deleteAfter(25);

    cout << "After deleting node after 25: ";
    display();

    return 0;
}
