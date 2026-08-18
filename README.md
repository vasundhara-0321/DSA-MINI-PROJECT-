# Warehouse Order Sorting & Delivery Dispatcher

A high-performance C program designed to eliminate warehouse shipping bottlenecks using data structure principles. The system dynamically prioritizes incoming orders using a **Max Heap** priority queue and tracks dispatch history using an **Array-Based Stack**.

---

## 📌 Project Overview

Traditional First-In, First-Out (FIFO) warehouse systems cause severe operational delays by processing low-priority, standard shipments ahead of urgent or express orders. 

This project solves that bottleneck by:
1. **Dynamic Priority Routing:** Automatically sorting incoming orders by shipping urgency (Express > Urgent > Normal).
2. **Logarithmic Efficiency:** Using a Max Heap structure to guarantee $O(\log n)$ insertion and removal times.
3. **Audit History Tracking:** Utilizing a Last-In, First-Out (LIFO) Stack to log dispatched orders for immediate compliance and tracking checks.

---

## 🛠️ Data Structures & Architecture

| Data Structure | Implementation | Purpose | Time Complexity |
| :--- | :--- | :--- | :---: |
| **Max Heap** | `Order heap[100]` | Priority Queue for storing and dynamic rebalancing of pending orders. | $O(\log n)$ |
| **Stack** | `Order stack[100]` | History log for tracking dispatched shipments in LIFO order. | $O(1)$ push/read |
| **Struct** | `typedef struct Order` | Encapsulates order metadata (`orderId`, `customer`, `destination`, `priority`). | $O(1)$ |

---

## 🚦 Priority Mapping Scheme

When adding an order, the numerical priority determines its place in the Max Heap:

| Input Choice | Order Type | Internal Priority Level | Dispatch Order |
| :---: | :--- | :---: | :--- |
| `1` | **Express** | **3** | Dispatched First (Highest Priority) |
| `2` | **Urgent** | **2** | Dispatched Second |
| `3` | **Normal** | **1** | Dispatched Last (Lowest Priority) |

---

## ⚡ Core Functions & Logic

* **`insertOrder(Order order)`**: Appends a new order to the end of the heap array and performs an **Up-Heapify** loop to maintain heap properties.
* **`dispatchOrder()`**: Extracts the top-priority root node (`heap[0]`), replaces it with the last leaf element, performs a **Down-Heapify** rebalance, and pushes the dispatched order onto the history `stack`.
* **`displayPendingOrders()`**: Performs a sequential scan of active orders currently residing in the heap memory.
* **`displayDispatchedOrders()`**: Traverses the stack from index `top` down to `0` to output the most recently dispatched shipments.

---

## 🛡️ Boundary Conditions & Exception Guards

* **Queue Overflow Safety:** `if (heapSize >= MAX)` checks prevent heap buffer overruns.
* **Queue Underflow Safety:** `if (heapSize == 0)` intercepts illegal extraction calls on empty queues.
* **Stack Memory Safeguard:** `if (top < MAX - 1)` guards memory bounds during LIFO logging.
* **Input Scrubbing:** Uses `scanf(" %[^\n]", ...)` scanset reading to handle full customer names with spaces safely.

---

## 🚀 How to Run the Code

### 1. Prerequisites
You need a standard C compiler (such as `gcc`, `clang`, or MSVC).

### 2. Compilation
Open your terminal/command prompt and navigate to the project directory:

```bash
gcc warehouse_dispatcher.c -o warehouse_dispatcher
