#ifndef ORDER_CPP
#define ORDER_CPP

#include "Order.h"

#include <iostream>
#include <string>
#include "ArrayLib.h"

using namespace std;

Order::Order(): executed(new bool(false)), type(new string("Generic Order")) {};
Order::Order(string t): executed(new bool(false)), type(new string(t)) {};
Order::Order(const Order& rhs): executed(new bool(*rhs.executed)), type(new string(*rhs.type)) {};

Order::~Order() {
	delete executed;
	delete type;
}

Order& Order::operator=(const Order& rhs) {
	if (this != &rhs) {
		executed = new bool(*rhs.executed);
		type = new string(*rhs.type);
	}
	return *this;
}

bool Order::validate() {
	return true;
};

void Order::execute() {
	if (validate()) {
		*executed = true;
		cout << *type << " order executed successfully.\n";
	} else {
		cout << "Order is invalid.\n";
	}
};

ostream& operator<<(ostream& out, const Order& order) {
	Order& cOrder = const_cast <Order&>(order);
	
	out << "Order: " << *cOrder.type;
	if (*cOrder.executed) {
		out << " (Executed)";
	}
	return out;
}

// OrdersList functions

// Constructor for OrdersList
OrdersList::OrdersList() {
	orders = new Order[0];
}; 

// Copy constructor for OrdersList
OrdersList::OrdersList(const OrdersList& rhs) {
	orders = new Order[*rhs.ordersCount];
	ordersCount = new int(*rhs.ordersCount);
	for (int i = 0; i < *ordersCount; i++) {
		orders[i] = Order(rhs.orders[i]); 
	}
};

// Assignment operator for OrdersList
OrdersList& OrdersList::operator=(const OrdersList& rhs) {
	if (this != &rhs) {
		orders = new Order[*rhs.ordersCount];
		ordersCount = new int(*rhs.ordersCount);
		for (int i = 0; i < *ordersCount; i++) {
			orders[i] = Order(rhs.orders[i]); 
		}
	}
	return *this;
};

OrdersList::~OrdersList() {
	delete [] orders;
	delete ordersCount;
};

int OrdersList::getOrdersCount() {
	return *ordersCount;
}

void OrdersList::addOrder(Order order) {
	push(orders, *ordersCount, order);
};

// Move an order from one position to another within the list
void OrdersList::moveOrder(size_t fromIndex, size_t toIndex) {
	swap(orders, *ordersCount, fromIndex, toIndex);
};

// Remove an order from the list by index
void OrdersList::removeOrder(size_t index) {
	remove(orders, *ordersCount, index);
};

// Execute all valid orders in the list
void OrdersList::executeOrders() {
	for (int i = 0; i < *ordersCount; i++) {
		orders[i].execute();
	}
};

ostream& operator<<(ostream& out, const OrdersList& ordersList) {
	OrdersList& cOrdersList = const_cast <OrdersList&>(ordersList);
	
	out << "OrdersList:\n";
	for (int i = 0; i < cOrdersList.getOrdersCount(); i++) {
		out << cOrdersList.orders[i] << endl;
	}
	return out;
}

#endif