#include <fstream> // file handling
#include <iostream> // input/output handling
#include <cmath> // for round()
#define Line "------------------------------------------ " // macros

using namespace std;

class Carriage {
protected:
    string carriageType, carriageID;
    int carriagePlaces;

public:
    void setData(string carriageType, string carriageID, int carriagePlaces) {
        this->carriageType = carriageType;
        this->carriageID = carriageID;
        this->carriagePlaces = carriagePlaces;
    }

    string getCarriageType() { return carriageType; }
    string getCarriageID() { return carriageID; }
    int getCarriagePlace() { return carriagePlaces; }

    void Display() {
        cout << Line << endl;
        cout << "  Carriage: " << carriageID << " " << carriageType << " " << carriagePlaces << endl;
    }
};

class Passenger {
protected:
    string firstName, lastName, ticketType;

public:
    void setData(string firstName, string lastName, string ticketType) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->ticketType = ticketType;
    }

    string getFirstName() { return firstName; }
    string getFamilyName() { return lastName; }
    string getTicketType() { return ticketType; }

    void Display() {
        cout << Line << endl;
        cout << "  Passenger: " << firstName << " " << lastName << " " << ticketType << endl;
    }
};

class Node {
public:
    int data;
    Node* next;
};

class LinkedList {
public:
    LinkedList() {
        head = NULL;
    }
    ~LinkedList() {};

    void addNode(int val);
    void deleteFirst();
    int getFirstElement();
    void display();

private:
    Node* head;
};

int LinkedList::getFirstElement() {
    return head->data;
}

void LinkedList::addNode(int val) {
    Node* newnode = new Node();
    newnode->data = val;
    newnode->next = NULL;
    if (head == NULL) {
        head = newnode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

void LinkedList::display() {
    if (head == NULL) {
        cout << "Passengers list is empty!" << endl;
    } else {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " --> ";
            temp = temp->next;
        }
        cout << endl;
    }
}

void LinkedList::deleteFirst() {
    if (head == NULL)
        cout << "Passengers list is empty!" << endl;
    else {
        Node* temp = head;
        head = head->next;
        delete(temp);
    }
}

class Stack {
    Node* front;

public:
    Stack() {
        front = NULL;
    }

    void push(int);
    void pop();
    void printStack();
};

void Stack::push(int d) {
    Node* temp = new Node();
    temp->data = d;
    if (front == NULL)
        temp->next = NULL;
    else
        temp->next = front;
    front = temp;
}

void Stack::pop() {
    if (front == NULL)
        cout << "UNDERFLOW";
    else {
        Node* temp = front;
        front = front->next;
        delete(temp);
    }
}

void Stack::printStack() {
    if (front == NULL) {
        cout << "UNDERFLOW!";
    } else {
        Node* temp = front;
        while (temp != NULL) {
            cout << temp->data << " <--> ";
            temp = temp->next;
        }
        cout << endl;
    }
}

int main() {
    string firstName, lastName, ticketType, carriageType, carriageID;
    int carriagePlaces;
    int Num = 1;
    int numOfBusiness = 0, numOfFirst = 0;
    double businessSpace = 0, firstSpace = 0;

    Passenger Psg;
    Carriage Crg;

    for (int i = 0; i < 1000; i++) {
        cout << "\t*** MENU *** " << endl;
        cout << "1. Add passenger to file" << endl;
        cout << "2. Read passengers info from file" << endl;
        cout << "3. Add carriage to file" << endl;
        cout << "4. Read carriage info from file" << endl;
        cout << "5. Show linked lists" << endl; 
        cout << "Your choice:";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            ofstream out("Passengers", ios::binary | ios::app);
            cout << "Enter first name: "; cin >> firstName;
            cout << "Enter last name: "; cin >> lastName;
            cout << "Enter ticket type (Business/First): "; cin >> ticketType;
            Psg.setData(firstName, lastName, ticketType);
            out.write((char*)&Psg, sizeof(Passenger));
            out.close();
        }
            break;

        case 2: {
            ifstream in("Passengers", ios::binary);
            while (in.read((char*)&Psg, sizeof(Passenger))) {
                Psg.Display();
            }
            in.close();
        }
            break;

        case 3: {
            ofstream out("Carriages", ios::binary | ios::app);
            cout << "Enter ID: "; cin >> carriageID;
            cout << "Enter type (Business/First): "; cin >> carriageType;
            cout << "Enter number of seats: "; cin >> carriagePlaces;
            Crg.setData(carriageType, carriageID, carriagePlaces);
            out.write((char*)&Crg, sizeof(Carriage));
            out.close();
        }
            break;

        case 4: {
            ifstream in("Carriages", ios::binary);
            while (in.read((char*)&Crg, sizeof(Carriage))) {
                Crg.Display();
            }
            in.close();
        }
            break;

        case 5:
            // Logic for displaying linked lists
            break;

        default:
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
