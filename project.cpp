#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Reservation {
    int flightNumber;
    string passengerName;
    int seatNumber;
    string destination;
    Reservation* next;

    Reservation(int fn, string name, int seat, string dest) {
        flightNumber = fn;
        passengerName = name;
        seatNumber = seat;
        destination = dest;
        next = nullptr;
    }
};

void writeToFile(Reservation* head) {
    ofstream outFile("r.txt");
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    
    Reservation* temp = head;
    while (temp != nullptr) {
        outFile << temp->flightNumber << " "
                << temp->passengerName << " "
                << temp->seatNumber << " "
                << temp->destination << endl;
        temp = temp->next;
    }
    outFile.close();
}

void readFromFile(Reservation*& head) {
    ifstream inFile("r.txt");
    if (!inFile) {
        cout << "No previous reservations found." << endl;
        return;
    }
    
    int flightNumber;
    string passengerName;
    int seatNumber;
    string destination;
    
    while (inFile >> flightNumber >> passengerName >> seatNumber >> destination) {
        Reservation* newReservation = new Reservation(flightNumber, passengerName, seatNumber, destination);
        if (head == nullptr) {
            head = newReservation;
        } else {
            Reservation* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newReservation;
        }
    }
    inFile.close();
}

void bookFlight(Reservation*& head, int flightNumber, string passengerName, int seatNumber, string destination) {
    Reservation* newReservation = new Reservation(flightNumber, passengerName, seatNumber, destination);
    
    if (head == nullptr) {
        head = newReservation;
    } else {
        Reservation* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newReservation;
    }
    writeToFile(head);
    cout << "Reservation for " << passengerName << " has been booked!" << endl;
}

void cancelReservation(Reservation*& head, string passengerName) {
    if (head == nullptr) {
        cout << "No reservations to cancel." << endl;
        return;
    }

    Reservation* temp = head;
    Reservation* prev = nullptr;

    while (temp != nullptr && temp->passengerName != passengerName) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Reservation not found!" << endl;
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    writeToFile(head); 
    cout << "Reservation for " << passengerName << " has been canceled." << endl;
}

void modifyReservation(Reservation* head, string passengerName, int newSeatNumber, string newDestination) {
    Reservation* temp = head;

    while (temp != nullptr) {
        if (temp->passengerName == passengerName) {
            temp->seatNumber = newSeatNumber;
            temp->destination = newDestination;
            writeToFile(head);
            cout << "Reservation modified for " << passengerName << "." << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Reservation not found!" << endl;
}

void displayReservations(Reservation* head) {
    if (head == nullptr) {
        cout << "No reservations found." << endl;
        return;
    }

    Reservation* temp = head;
    while (temp != nullptr) {
        cout << "Flight Number: " << temp->flightNumber
             << ", Passenger Name: " << temp->passengerName
             << ", Seat Number: " << temp->seatNumber
             << ", Destination: " << temp->destination << endl;
        temp = temp->next;
    }
}

void searchReservation(Reservation* head, string passengerName) {
    Reservation* temp = head;
    while (temp != nullptr) {
        if (temp->passengerName == passengerName) {
            cout << "Reservation found for " << passengerName << ": "
                 << "Flight Number: " << temp->flightNumber
                 << ", Seat Number: " << temp->seatNumber
                 << ", Destination: " << temp->destination << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Reservation not found!" << endl;
}

int main() {
    Reservation* head = nullptr;
    readFromFile(head);  
    
    int choice;
    do {
        cout << "\n--- Flight Reservation System ---\n";
        cout << "1. Book a Flight\n";
        cout << "2. Cancel a Reservation\n";
        cout << "3. Modify a Reservation\n";
        cout << "4. Display All Reservations\n";
        cout << "5. Search for a Reservation\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int flightNumber, seatNumber;
            string passengerName, destination;
            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            cout << "Enter Passenger Name: ";
            cin >> passengerName;
            cout << "Enter Seat Number: ";
            cin >> seatNumber;
            cout << "Enter Destination: ";
            cin >> destination;
            bookFlight(head, flightNumber, passengerName, seatNumber, destination);
        }
        else if (choice == 2) {
            string passengerName;
            cout << "Enter Passenger Name to cancel reservation: ";
            cin >> passengerName;
            cancelReservation(head, passengerName);
        }
        else if (choice == 3) {
            string passengerName, newDestination;
            int newSeatNumber;
            cout << "Enter Passenger Name to modify reservation: ";
            cin >> passengerName;
            cout << "Enter New Seat Number: ";
            cin >> newSeatNumber;
            cout << "Enter New Destination: ";
            cin >> newDestination;
            modifyReservation(head, passengerName, newSeatNumber, newDestination);
        }
        else if (choice == 4) {
            displayReservations(head);
        }
        else if (choice == 5) {
            string passengerName;
            cout << "Enter Passenger Name to search: ";
            cin >> passengerName;
            searchReservation(head, passengerName);
        }
    } while (choice != 6);

    writeToFile(head);  
    cout << "Exiting the system. All data saved to file." << endl;

    return 0;
}
