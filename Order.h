#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>

using namespace std;

// Base class for all orders
class Order {

public:
    bool* executed;     // Was the order executed?
    string* type;       // order type
	
    Order();
    Order(string t);
	Order(const Order& rhs);

    ~Order();

    Order& operator=(const Order& rhs);

    bool validate();

    void execute();
	
	friend ostream& operator<<(ostream& out, const Order& order);
};

// OrdersList class to manage a list of orders
class OrdersList {
	
	int* ordersCount = new int(0);
	public:
		Order* orders;
		
		// Constructor for OrdersList
		OrdersList();;

		// Copy constructor for OrdersList
		OrdersList(const OrdersList& rhs);

		// Assignment operator for OrdersList
		OrdersList& operator=(const OrdersList& rhs);

		~OrdersList();
		
		int getOrdersCount();

		void addOrder(Order order);

		// Move an order from one position to another within the list
		void moveOrder(size_t fromIndex, size_t toIndex);

		// Remove an order from the list by index
		void removeOrder(size_t index);

		// Execute all valid orders in the list
		void executeOrders();
		
		friend ostream& operator<<(ostream& out, const OrdersList& ordersList);
};

#endif
