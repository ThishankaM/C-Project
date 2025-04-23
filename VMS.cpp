#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdlib.h> 

using namespace std;

struct User {
    string username;
    string password; 
    string role;     // "customer", "staff", or "admin"
};

struct Appointment {
    string username;
    string serviceType;
    string serviceDate;
};

vector<User> users;
vector<Appointment> appointments;

void loadUsers() {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        User user;
        getline(ss, user.username, ',');
        getline(ss, user.password, ',');
        getline(ss, user.role, ',');
        users.push_back(user);
    }
    file.close();
}

void loadAppointments() {
    ifstream file("appointments.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Appointment app;
        getline(ss, app.username, ',');
        getline(ss, app.serviceType, ',');
        getline(ss, app.serviceDate, ',');
        appointments.push_back(app);
    }
    file.close();
}

bool authenticateUser(const string& username, const string& password, string& role) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            role = user.role;
            return true;
        }
    }
    return false;
}

void addUser() {
    string username, password, role;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (customer/staff/admin): ";
    cin >> role;

    for (const auto& user : users) {
        if (user.username == username) {
            cout << "Username already exists. Try a different username.\n";
            return;
        }
    }

    User newUser = {username, password, role};
    users.push_back(newUser);
    ofstream file("users.txt", ios::app);
    file << username << "," << password << "," << role << "\n";
    file.close();

    cout << "User added successfully.\n";
}

void viewServiceRecords(const string& username) {
    cout << "Service Records for " << username << ":\n";
    for (const auto& app : appointments) {
        if (app.username == username) {
            cout << "Service: " << app.serviceType << ", Date: " << app.serviceDate << endl;
        }
    }
}

void scheduleService(const string& username) {
    string serviceType, serviceDate;
    cout << "Enter service type: ";
    cin >> serviceType;
    cout << "Enter service date (YYYY-MM-DD): ";
    cin >> serviceDate;

    for (const auto& app : appointments) {
        if (app.serviceDate == serviceDate) {
            cout << "This slot is already booked. Please choose another date.\n";
            return;
        }
    }

    Appointment newApp = {username, serviceType, serviceDate};
    appointments.push_back(newApp);
    ofstream file("appointments.txt", ios::app);
    file << username << "," << serviceType << "," << serviceDate << "\n";
    file.close();

    cout << "Service scheduled successfully.\n";
}

void addServiceRecord() {
    string username, serviceType, serviceDate;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter service type: ";
    cin >> serviceType;
    cout << "Enter service date (YYYY-MM-DD): ";
    cin >> serviceDate;

    bool userExists = false;
    for (const auto& user : users) {
        if (user.username == username) {
            userExists = true;
            break;
        }
    }
    if (!userExists) {
        cout << "User does not exist.\n";
        return;
    }

    Appointment newApp = {username, serviceType, serviceDate};
    appointments.push_back(newApp);
    ofstream file("appointments.txt", ios::app);
    file << username << "," << serviceType << "," << serviceDate << "\n";
    file.close();

    cout << "Service record added successfully.\n";
}

void modifyServiceRecord() {
    string username, serviceDate, newServiceType, newServiceDate;
    cout << "Enter username for the service record to modify: ";
    cin >> username;
    cout << "Enter existing service date (YYYY-MM-DD): ";
    cin >> serviceDate;

    auto it = find_if(appointments.begin(), appointments.end(), [&](const Appointment& app) {
        return app.username == username && app.serviceDate == serviceDate;
    });

    if (it != appointments.end()) {
        cout << "Enter new service type: ";
        cin >> newServiceType;
        cout << "Enter new service date (YYYY-MM-DD): ";
        cin >> newServiceDate;

        it->serviceType = newServiceType;
        it->serviceDate = newServiceDate;

        // Rewrite the appointments file
        ofstream file("appointments.txt");
        for (const auto& app : appointments) {
            file << app.username << "," << app.serviceType << "," << app.serviceDate << "\n";
        }
        file.close();

        cout << "Service record modified successfully.\n";
    } else {
        cout << "No matching service record found.\n";
    }
}

void customerMenu(const string& username) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n";
        cout << "1. View Service Records\n";
        cout << "2. Schedule Service Appointment\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                viewServiceRecords(username);
                break;
            case 2:
                scheduleService(username);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

void adminMenu() {
    int choice;
    do {
cout <<"     ###    ########  ##     ## #### ##    ##   ########     ###    ##    ## ######## ##      \n"
	   "    ## ##   ##     ## ###   ###  ##  ###   ##   ##     ##   ## ##   ###   ## ##       ##      \n"
	   "   ##   ##  ##     ## #### ####  ##  ####  ##   ##     ##  ##   ##  ####  ## ##       ##      \n"
	   "  ##     ## ##     ## ## ### ##  ##  ## ## ##   ########  ##     ## ## ## ## ######   ##      \n"
	   "  ######### ##     ## ##     ##  ##  ##  ####   ##        ######### ##  #### ##       ##      \n"
	   "  ##     ## ##     ## ##     ##  ##  ##   ###   ##        ##     ## ##   ### ##       ##      \n"
	   "  ##     ## ########  ##     ## #### ##    ##   ##        ##     ## ##    ## ######## ########\n";
        cout << "1. Add User\n";
        cout << "2. Add Service Record\n";
        cout << "3. Modify Service Record\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                addServiceRecord();
                break;
            case 3:
                modifyServiceRecord();
                break;
            case 4:
                system("cls");
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

void staffMenu() {
    int choice;
    do {
        cout << "\nStaff Menu:\n";
        cout << "1. Modify Service Record\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                modifyServiceRecord();
                break;
            case 2:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
}

void login() {
cout <<"  ##        #######   ######   #### ##    ## \n" 
	   "  ##       ##     ## ##    ##   ##  ###   ## \n" 
	   "  ##       ##     ## ##         ##  ####  ## \n" 
	   "  ##       ##     ## ##   ####  ##  ## ## ## \n" 
	   "  ##       ##     ## ##    ##   ##  ##  #### \n" 
	   "  ##       ##     ## ##    ##   ##  ##   ### \n" 
	   "  ########  #######   ######   #### ##    ## \n"; 
    string username, password, role;
    cout << "\n\t   +-----------------------+\n";
    cout << "\t\tEnter username: ";
    cout << "\n\t   +-----------------------+\n";
    cout << "\t\t     ";
    cin >> username;
    cout << "\t   +-----------------------+\n";
    cout << "\t\tEnter password: ";
    cout << "\n\t   +-----------------------+\n";
    cout << "\t\t     ";
    cin >> password;

    if (authenticateUser(username, password, role)) {
    	system("cls");
        if (role == "customer") {
            customerMenu(username);
        } else if (role == "admin") {
            adminMenu();
        } else if (role == "staff") {
            staffMenu();
        } else {
            cout << "Access denied. Invalid role.\n";
        }
    } else {
        cout << "Invalid username or password.\n";
    }
}

void mainMenu() {
    int choice;
    do {
cout << "  ##     ## ##     ##    ######  ##    ##  ######  ######## ######## ##     ##\n" 
        "  ##     ## ###   ###   ##    ##  ##  ##  ##    ##    ##    ##       ###   ###\n" 
        "  ##     ## #### ####   ##         ####   ##          ##    ##       #### ####\n" 
        "  ##     ## ## ### ##    ######     ##     ######     ##    ######   ## ### ##\n" 
        "   ##   ##  ##     ##         ##    ##          ##    ##    ##       ##     ##\n" 
        "    ## ##   ##     ##   ##    ##    ##    ##    ##    ##    ##       ##     ##\n" 
        "     ###    ##     ##    ######     ##     ######     ##    ######## ##     ##\n";
		 
		cout << "\n\t\t\t+-----------------------+\n"
				"\t\t\t|\t\t\t|\n"
				"\t\t\t|\tMain Menu:\t|\n"
				"\t\t\t|\t\t\t|\n"
				"\t\t\t+-----------------------+\n";
        cout << "\t\t\t\t1. Login\n";
        cout << "\t\t\t\t2. Exit\n";
        cout << "\t\t\t    Enter your choice: ";
        cin >> choice;
        system("cls");
        if (choice == 1) {
            login();
        } else if (choice != 2) {
            cout << "\n\t\t\tInvalid choice. Try again.\n\n";
        }
    } while (choice != 2);
}

int main() {
    loadUsers();
    loadAppointments();
    mainMenu();
    return 0;
}

