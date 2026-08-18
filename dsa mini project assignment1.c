#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure for an Order
typedef struct {
    int orderId;
    char customer[50];
    char destination[50];
    int priority;
} Order;

// Priority Queue using Max Heap
Order heap[MAX];
int heapSize = 0;

// Stack for dispatched orders
Order stack[MAX];
int top = -1;

// Swap two orders
void swap(Order *a, Order *b) {
    Order temp = *a;
    *a = *b;
    *b = temp;
}

// Insert order into Priority Queue
void insertOrder(Order order) {
    if (heapSize >= MAX) {
        printf("\nWarehouse queue is full!\n");
        return;
    }

    int i = heapSize;
    heap[heapSize++] = order;

    // Heapify upward
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent].priority >= heap[i].priority)
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }

    printf("\nOrder %d added successfully.\n", order.orderId);
}

// Remove highest-priority order
Order dispatchOrder() {
    Order empty = {-1, "", "", -1};

    if (heapSize == 0) {
        printf("\nNo pending orders.\n");
        return empty;
    }

    Order dispatched = heap[0];

    heap[0] = heap[--heapSize];

    // Heapify downward
    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heapSize &&
            heap[left].priority > heap[largest].priority)
            largest = left;

        if (right < heapSize &&
            heap[right].priority > heap[largest].priority)
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    // Push dispatched order into stack
    if (top < MAX - 1) {
        stack[++top] = dispatched;
    }

    printf("\nOrder %d dispatched successfully!\n", dispatched.orderId);
    return dispatched;
}

// Display pending orders
void displayPendingOrders() {
    if (heapSize == 0) {
        printf("\nNo pending orders.\n");
        return;
    }

    printf("\n--- Pending Orders ---\n");

    for (int i = 0; i < heapSize; i++) {
        printf("Order ID: %d | Customer: %s | Destination: %s | Priority: %d\n",
               heap[i].orderId,
               heap[i].customer,
               heap[i].destination,
               heap[i].priority);
    }
}

// Display dispatched orders
void displayDispatchedOrders() {
    if (top == -1) {
        printf("\nNo orders have been dispatched.\n");
        return;
    }

    printf("\n--- Recently Dispatched Orders ---\n");

    for (int i = top; i >= 0; i--) {
        printf("Order ID: %d | Customer: %s | Destination: %s\n",
               stack[i].orderId,
               stack[i].customer,
               stack[i].destination);
    }
}

// Priority selection
int getPriority(int type) {
    switch (type) {
        case 1:
            return 3;   // Express
        case 2:
            return 2;   // Urgent
        case 3:
            return 1;   // Normal
        default:
            return 0;
    }
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("   WAREHOUSE ORDER & DELIVERY DISPATCHER\n");
        printf("========================================\n");

        printf("1. Add Order\n");
        printf("2. Dispatch Next Order\n");
        printf("3. Display Pending Orders\n");
        printf("4. Display Dispatched Orders\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {

            Order order;
            int type;

            printf("\nEnter Order ID: ");
            scanf("%d", &order.orderId);

            printf("Enter Customer Name: ");
            scanf(" %[^\n]", order.customer);

            printf("Enter Destination: ");
            scanf(" %[^\n]", order.destination);

            printf("\nSelect Order Type:\n");
            printf("1. Express\n");
            printf("2. Urgent\n");
            printf("3. Normal\n");

            printf("Enter type: ");
            scanf("%d", &type);

            order.priority = getPriority(type);

            if (order.priority == 0) {
                printf("\nInvalid order type!\n");
            } else {
                insertOrder(order);
            }

        } else if (choice == 2) {

            dispatchOrder();

        } else if (choice == 3) {

            displayPendingOrders();

        } else if (choice == 4) {

            displayDispatchedOrders();

        } else if (choice == 5) {

            printf("\nThank you for using the Warehouse Dispatcher!\n");
            break;

        } else {

            printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}