#include <stdio.h>  // Provides printf()
#include <stdlib.h> // Provides malloc(), free(), and NULL

struct Node // Define a node for the doubly linked list
{
    int data;          // Stores the data of the node
    struct Node *next; // Stores the address of the next node
    struct Node *prev; // Stores the address of the previous node
};

struct Node *head = NULL; // head points to the first node of the list

void addFirst(int data) // Function to add a node at the beginning
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // Allocate memory for a new node
    newNode->data = data;                                              // Store the given data in the new node
    newNode->next = head;                                              // Connect the new node to the current first node
    if (head != NULL)                                                  // Check if the list already contains a node
    {
        head->prev = newNode; // Make the old first node point back to the new node
    }
    newNode->prev = NULL; // New first node has no previous node
    head = newNode;       // Make the new node the first node
}

void addLast(int data) // Function to add a node at the end
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // Allocate memory for a new node
    newNode->data = data;                                              // Store the given data in the new node
    newNode->next = NULL;                                              // Last node does not have a next node
    newNode->prev = NULL;                                              // Initially set previous pointer to NULL
    if (head == NULL)                                                  // Check if the list is empty
    {
        head = newNode; // Make the new node the first node
        return;         // Stop the function
    }
    struct Node *currNode = head;  // Start traversing from the first node
    while (currNode->next != NULL) // Move until the last node is reached
    {
        currNode = currNode->next; // Move to the next node
    }
    currNode->next = newNode; // Connect the old last node to the new node
    newNode->prev = currNode; // Connect the new node back to the old last node
}

void deleteFirst() // Function to delete the first node
{
    if (head == NULL) // Check if the list is empty
    {
        printf("List is empty .. \n"); // Print an empty-list message
        return;                        // Stop the function
    }
    struct Node *temp = head; // Store the current first node temporarily
    head = head->next;        // Move head to the second node
    if (head != NULL)         // Check if another node exists
    {
        head->prev = NULL; // The new first node should have no previous node
    }
    printf("Deleted Data : %d \n", temp->data); // Print the deleted data
    free(temp);                                 // Release the memory of the deleted node
}

void deleteLast() // Function to delete the last node
{
    if (head == NULL) // Check if the list is empty
    {
        printf("List is empty .. \n"); // Print an empty-list message
        return;                        // Stop the function
    }
    if (head->next == NULL) // Check if there is only one node
    {
        struct Node *temp = head;                   // Store the only node temporarily
        head = NULL;                                // Make the list empty
        printf("Deleted Data : %d \n", temp->data); // Print the deleted data
        free(temp);                                 // Release the memory of the deleted node
        return;                                     // Stop the function
    }
    struct Node *currNode = head;  // Start traversing from the first node
    while (currNode->next != NULL) // Move until the last node is reached
    {
        currNode = currNode->next; // Move to the next node
    }
    currNode->prev->next = NULL;                    // Remove the last node from the forward link
    printf("Deleted Data : %d \n", currNode->data); // Print the deleted data
    free(currNode);                                 // Release the memory of the deleted node
}

void addAtIndex(int data, int pos) // Function to insert a node at a given position
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // Allocate memory for a new node
    newNode->data = data;                                              // Store the given data in the new node
    if (pos <= 1)                                                      // Check if the node should be inserted at the beginning
    {
        newNode->next = head; // Connect new node to the current first node
        newNode->prev = NULL; // New first node has no previous node
        if (head != NULL)     // Check if the list is not empty
        {
            head = newNode; // Make the new node the first node
            return;         // Stop the function
        }
    }
    struct Node *currNode = head;                         // Start traversing from the first node
    for (int i = 1; i < pos - 1 && currNode != NULL; i++) // Move to the node before the required position
    {
        currNode = currNode->next; // Move to the next node
    }
    if (currNode == NULL) // Check if the given position is invalid
    {
        printf("Invalid index or position ...!"); // Print an invalid-position message
        free(newNode);                            // Release the allocated memory
        return;                                   // Stop the function
    }
    newNode->next = currNode->next; // Connect new node to the next node
    newNode->prev = currNode;       // Connect new node back to the current node
    currNode->next = newNode;       // Connect current node to the new node
    if (newNode->next != NULL)      // Check if a node exists after the new node
    {
        newNode->next->prev = newNode; // Update the next node's previous pointer
    }
}

void deleteFromIndex(int pos) // Function to delete a node from a given position
{
    if (pos <= 0) // Check whether the position is invalid
    {
        printf("Invalid position ....!\n"); // Print invalid-position message
        return;                             // Stop the function
    }
    if (head == NULL) // Check whether the list is empty
    {
        printf("List is Empty....! \n"); // Print empty-list message
        return;                          // Stop the function
    }
    else if (pos == 1 && head->next == NULL) // Check if position 1 is the only node
    {
        printf("Deleted Data : %d \n", head->data); // Print the data being deleted
        free(head);                                 // Free the memory of the only node
        head = NULL;                                // Set head to NULL because the list is now empty
        return;                                     // Stop the function
    }
    else if (pos == 1) // Check if the first node needs to be deleted
    {
        printf("Deleted Data : %d \n", head->data); // Print the data being deleted
        struct Node *temp = head;                   // Store the current head temporarily
        head = head->next;                          // Move head to the second node
        head->prev = NULL;                          // The new first node has no previous node
        free(temp);                                 // Free the old first node
        return;                                     // Stop the function
    }
    struct Node *currNode = head; // Start traversal from the first node
    int i = 1;                    // Start position counting from 1
    while (currNode != NULL)      // Traverse until the end of the list
    {
        if (i == pos) // Check whether the current node is at the required position
        {
            if (currNode->next == NULL) // Check if the node is the last node
            {
                printf("Deleted Data : %d \n", currNode->data); // Print the data being deleted
                currNode->prev->next = NULL;                    // Remove the last node from the forward link
                currNode->prev = NULL;                          // Remove the previous link from the current node
                free(currNode);                                 // Free the memory of the last node
                return;                                         // Stop the function
            }
            else // Case where the node is somewhere in the middle
            {
                printf("Deleted Data : %d \n", currNode->data); // Print the data being deleted
                currNode->prev->next = currNode->next;          // Connect previous node to next node
                currNode->next->prev = currNode->prev;          // Connect next node back to previous node
                free(currNode);                                 // Free the memory of the deleted node
                return;                                         // Stop the function
            }
        }
        i++;                       // Move to the next position number
        currNode = currNode->next; // Move to the next node
    }
    printf("Position not found ....! \n"); // Print message if the position does not exist
}

void printList() // Function to display the doubly linked list
{
    if (head == NULL) // Check if the list is empty
    {
        printf("NULL \n"); // Print NULL for an empty list
        return;            // Stop the function
    }
    struct Node *currNode = head; // Start traversing from the first node
    while (currNode != NULL)      // Continue until the end of the list
    {
        if (currNode->next != NULL) // Check if this is not the last node
        {
            printf("%d <--> ", currNode->data); // Print the current node with a two-way link
        }
        else // Execute for the last node
        {
            printf("%d --> ", currNode->data); // Print the last node
        }
        currNode = currNode->next; // Move to the next node
    }
    printf("NULL \n"); // Show the end of the list
}

int count() // Function to count the total number of nodes
{
    if (head == NULL) // Check if the list is empty
    {
        return 0; // Return 0 because there are no nodes
    }
    int count = 0;                // Store the number of nodes
    struct Node *currNode = head; // Start traversing from the first node
    while (currNode != NULL)      // Continue until the end of the list
    {
        count++;                   // Increase the node count
        currNode = currNode->next; // Move to the next node
    }
    return count; // Return the total number of nodes
}

void search(int target) // Function to search for a given value
{
    if (head == NULL) // Check if the list is empty
    {
        printf("List is empty ...!"); // Print an empty-list message
        return;                       // Stop the function
    }
    struct Node *currNode = head; // Start searching from the first node
    int i = 1;                    // Store the position of the current node
    while (currNode != NULL)      // Continue until the end of the list
    {
        if (currNode->data == target) // Check if the current node contains the target
        {
            printf("Element is found at : %d \n", i); // Print the position of the found element
            return;                                   // Stop searching after finding the element
        }
        i++;                       // Move to the next position
        currNode = currNode->next; // Move to the next node
    }
    printf("Element not found ...! \n"); // Print message if the target is not found
}

int main() // Program execution starts here
{
    addFirst(5);                      // Add 5 at the beginning
    addFirst(4);                      // Add 4 at the beginning
    addFirst(2);                      // Add 2 at the beginning
    addFirst(1);                      // Add 1 at the beginning
    printList();                      // Display the current list
    addAtIndex(3, 3);                 // Insert 3 at position 3
    printList();                      // Display the list after insertion
    printf("Count : %d \n", count()); // Count and print the total nodes
    search(4);                        // Search for the element 4
    deleteFirst();                    // Delete the first node
    printList();                      // Display the list after deletion
    deleteFromIndex(0);
    printList();

    return 0; // End the program successfully
}
