#include <iostream>	// Include the input-output stream library
#include <fstream>	// Include the file stream library
#include <string> 	// Include the string library
#include <vector>	// Include the vector library
#include <sstream>	// Include the string stream library
#include <iomanip>	// Include the input-output manipulators library
#include <algorithm>// Include the algorithms library
#include <stdlib.h> // Include the standard library

using namespace std;	// Use the standard namespace
// Define a structure for User
struct User {
    string username;	// User's username
    string password;	// User's password
    string role; 		// "customer", "staff", or "admin"
    string contact;		// User's contact information
};
// Define a structure for Appointment
struct Appointment {
    string username;        // Username of the customer
    string serviceType;		// Type of service
    string serviceDate;		// Date of the service
    string serviceTime;		// Time of the service
    string vehicleRegNo;	// Vehicle registration number
    string customerName;	// Customer's name
    string customerContact;	// Customer's contact information
    string staffUsername;   // Username of the assigned staff 
    bool isComplete;		// Status of the appointment (completed or not)
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
        getline(ss, user.contact, ',');
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
        getline(ss, app.username, ',');			// can construct into different types extarct values clear and reuse string basically string manipulation
        getline(ss, app.serviceType, ',');
        getline(ss, app.serviceDate, ',');
        getline(ss, app.serviceTime, ',');
        getline(ss, app.vehicleRegNo, ',');
        getline(ss, app.customerName, ',');
        getline(ss, app.customerContact, ',');
        getline(ss, app.staffUsername, ',');  // Read staff username
        ss >> app.isComplete;
        appointments.push_back(app);
    }
    file.close();
}

bool authenticateUser(const string& username, const string& password, string& role) { //hold memory address of another variable
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            role = user.role;
            return true;
        }
    }
    return false;
}

void addUser() {
    string username, password, role, contact;
cout <<"     ###    ########  ########    ##     ##  ######  ######## ######## \n"
	   "    ## ##   ##     ## ##     ##   ##     ## ##    ## ##       ##     ##\n" 
	   "   ##   ##  ##     ## ##     ##   ##     ## ##       ##       ##     ##\n" 
	   "  ##     ## ##     ## ##     ##   ##     ##  ######  ######   ######## \n" 
	   "  ######### ##     ## ##     ##   ##     ##       ## ##       ##   ##  \n" 
	   "  ##     ## ##     ## ##     ##   ##     ## ##    ## ##       ##    ## \n" 
	   "  ##     ## ########  ########     #######   ######  ######## ##     ##\n";
	cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t\t   Enter new username: ";
    cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t\t\t ";
    cin >> username;
       for (const auto& user : users) {
        if (user.username == username) {
            cout << "Username already exists. Try a different username.\n";
            return;
        }
    }
    cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t\t     Enter password: ";
    cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t\t\t ";
    cin >> password;
    cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t    Enter role (customer/staff/admin): ";
    cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t\t\t   ";
    cin >> role;
    cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t\t  Enter contact details: ";
    cout << "\n\t\t\t+-----------------------+\n";
    cout << "\t\t\t\t ";
    cin >> contact;

    User newUser = {username, password, role, contact};
    users.push_back(newUser); // used to add an element to the end of the vector
    ofstream file("users.txt", ios::app);
    file << username << "," << password << "," << role << "," << contact << "\n";
    file.close();

    cout << "User added successfully.\n";
}

void viewServiceRecords(const string& username) {
    cout << "Personal Information:\n";
    for (const auto& user : users) {
        if (user.username == username) {
        	cout << "+---------------------------+\n";
            cout << "   Name: " << user.username << "\n";
            cout << "+---------------------------+\n";
            cout << "   Contact: " << user.contact << "\n";
            break;
        }
    }
	cout << "+----------------------------+";
    cout << "\nService Records for " << username << ":\n";
    cout << "+----------------------------+"<< endl;
    for (const auto& app : appointments) {
        if (app.username == username) {
        	cout <<"+--------------------------------------+" << endl;
            cout << "\tService: " << app.serviceType <<endl << "\tDate: " << app.serviceDate <<endl << "\tTime: " << app.serviceTime <<endl
                 << "\tVehicle Reg No: " << app.vehicleRegNo <<endl << "\tCustomer Name: " << app.customerName <<endl
                 << "\tCustomer Contact: " << app.customerContact <<endl << "\tStaff Username: " << app.staffUsername <<endl
                 << "\tComplete: " << (app.isComplete ? "Yes" : "No") << endl <<"+--------------------------------------+"<< endl;
        }
    }
}

bool isDateValid(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (month == 2 && day > 29) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    return true;
}

bool isTimeValid(const string& time) {
    if (time.size() != 5 || time[2] != ':') return false;
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    return true;
}

void scheduleService(const string& username) {
    string serviceType, serviceDate, serviceTime, vehicleRegNo, customerName, customerContact, staffUsername;

    // Get service details from the user
    cout << "Enter service type: ";
    cin.ignore();  // Clear the newline character from the input buffer
    getline(cin, serviceType);
    cout << "Enter service date (YYYY-MM-DD): ";
    getline(cin, serviceDate);
    if (!isDateValid(serviceDate)) { //! mean false
        cout << "Invalid date format.\n";
        return;
    }
    cout << "Enter service time (HH:MM): ";
    getline(cin, serviceTime);
    if (!isTimeValid(serviceTime)) {
        cout << "Invalid time format.\n";
        return;
    }
    cout << "Enter vehicle registration number: ";
    getline(cin, vehicleRegNo);
    cout << "Enter customer name: ";
    getline(cin, customerName);
    cout << "Enter customer contact: ";
    getline(cin, customerContact);

    // Display available staff members
    cout << "Available staff members:\n";
    for (const auto& user : users) {
        if (user.role == "staff") {
            cout << user.username << "\n";
        }
    }

    cout << "Enter staff username: ";
    getline(cin, staffUsername);

    // Validate if the staff member exists
    bool staffExists = false;
    for (const auto& user : users) {
        if (user.username == staffUsername && user.role == "staff") {
            staffExists = true;
            break;
        }
    }
    if (!staffExists) {
        cout << "Invalid staff username.\n";
        return;
    }

    // Check for overlapping appointments
    bool hasOverlap = false;
    for (const auto& app : appointments) {
        if (app.username == username && app.serviceDate == serviceDate && app.serviceTime == serviceTime) {
            hasOverlap = true;
            break;
        }
    }

    if (hasOverlap) {
        cout << "Error: There is already an appointment scheduled for this date and time.\n";
        return;
    }

    // Create a new appointment
    Appointment newApp = {username, serviceType, serviceDate, serviceTime, vehicleRegNo, customerName, customerContact, staffUsername, false};
    appointments.push_back(newApp);

    // Save the new appointment to the file
    ofstream file("appointments.txt", ios::app);
    if (file.is_open()) {
        file << username << "," << serviceType << "," << serviceDate << "," << serviceTime << "," << vehicleRegNo << "," << customerName << "," << customerContact << "," << staffUsername << "," << 0 << "\n";
        file.close();
        cout << "Service scheduled successfully.\n";
    } else {
        cout << "Error: Could not open appointments file for writing.\n";
    }
}

void cancelServiceAppointment(const string& username) {
    string serviceDate;
    string serviceTime;
    cout << "Enter the service date (YYYY-MM-DD) of the appointment to cancel: ";
    cin >> serviceDate;
    cout << "Enter service time (HH:MM): ";
    cin >> serviceTime;

    auto it = remove_if(appointments.begin(), appointments.end(), [&](const Appointment& app) {
        return app.username == username && app.serviceDate == serviceDate && app.serviceTime == serviceTime;
    });

    if (it != appointments.end()) {
        appointments.erase(it, appointments.end());

        // Rewrite the appointments file
        ofstream file("appointments.txt");
        for (const auto& app : appointments) {
            file << app.username << "," << app.serviceType << "," << app.serviceDate << "," << app.serviceTime << "," << app.vehicleRegNo << "," << app.customerName << "," << app.customerContact << "," << app.staffUsername << "," << app.isComplete << "\n";
        }
        file.close();

        cout << "Service appointment cancelled successfully.\n";
    } else {
        cout << "No matching appointment found.\n";
    }
}

void updatePersonalInfo(const string& username) {
    string newContact;
    cout << "Enter new contact details: ";
    cin >> newContact;

    for (auto& user : users) {
        if (user.username == username) {
            user.contact = newContact;
            break;
        }
    }

    // Rewrite the users file
    ofstream file("users.txt");
    for (const auto& user : users) {
        file << user.username << "," << user.password << "," << user.role << "," << user.contact << "\n";
    }
    file.close();

    cout << "Personal information updated successfully.\n";
}

void viewSchedule(const string& staffUsername) {
    cout << "Appointments assigned to " << staffUsername << ":\n";
    for (const auto& app : appointments) {
        if (app.staffUsername == staffUsername) {
        	cout << endl;
        	cout <<"+--------------------------------------+" << endl;
            cout << "\tCustomer: " << app.username <<endl << "\tService: " << app.serviceType <<endl << "\tDate: " << app.serviceDate <<endl
                 << "\tTime: " << app.serviceTime <<endl << "\tVehicle Reg No: " << app.vehicleRegNo <<endl
                 << "\tCustomer Name: " << app.customerName <<endl << "\tCustomer Contact: " << app.customerContact <<endl
                 << "\tComplete: " << (app.isComplete ? "Yes" : "No") << endl <<"+--------------------------------------+" << endl;
        }
    }
}
void accessVehicleRecords() {
    string regNo;
    cout << "Enter vehicle registration number: ";
    cin >> regNo;

    cout << "Service Records for Vehicle " << regNo << ":\n";
    for (const auto& app : appointments) {
        if (app.vehicleRegNo == regNo) {
        	cout <<"+--------------------------------------+" << endl;
            cout << "\tService: " << app.serviceType << endl << "\tDate: " << app.serviceDate <<endl << "\tTime: " << app.serviceTime <<endl << "\tCustomer Name: " << app.customerName <<endl << "\tCustomer Contact: " << app.customerContact <<endl << "\tComplete: " << (app.isComplete ? "Yes" : "No") << endl;
        }
    }
}
void addServiceRecord() {
    string username, serviceType, serviceDate, serviceTime, vehicleRegNo, customerName, customerContact,staffMember;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter service type: ";
    cin >> serviceType;
    cout << "Enter service date (YYYY-MM-DD): ";
    cin >> serviceDate;
    cout << "Enter service time (HH:MM): ";
    cin >> serviceTime;
    cout << "Enter vehicle registration number: ";
    cin >> vehicleRegNo;
    cout << "Enter customer name: ";
    cin >> customerName;
    cout << "Enter customer contact: ";
    cin >> customerContact;
    cout << "Enter Staff ID: ";
    cin >> staffMember;

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

    Appointment newApp = {username, serviceType, serviceDate, serviceTime, vehicleRegNo, customerName, customerContact, staffMember,false};
    appointments.push_back(newApp);
    ofstream file("appointments.txt", ios::app);
    file << username << "," << serviceType << "," << serviceDate << "," << serviceTime << "," << vehicleRegNo << "," << customerName << "," << customerContact << "," << 0 << "\n";
    file.close();

    cout << "Service record added successfully.\n";
}
void markServiceAsComplete() {
    string username, serviceDate;
    cout << "Enter username for the service record to mark as complete: ";
    cin >> username;
    cout << "Enter service date (YYYY-MM-DD): ";
    cin >> serviceDate;

    auto it = find_if(appointments.begin(), appointments.end(), [&](const Appointment& app) {
        return app.username == username && app.serviceDate == serviceDate;
    });

    if (it != appointments.end()) {
        it->isComplete = true;

        // Rewrite the appointments file
        ofstream file("appointments.txt");
        for (const auto& app : appointments) {
            file << app.username << "," << app.serviceType << "," << app.serviceDate << "," << app.serviceTime << "," << app.vehicleRegNo << "," << app.customerName << "," << app.customerContact << "," << app.isComplete << "\n";
        }
        file.close();

        cout << "Service marked as complete.\n";
    } else {
        cout << "No matching service record found.\n";
    }
}


void staffMenu(const string& username) {
    int choice;
    do {
cout <<"   ######  ########    ###    ######## ########   ########     ###    ##    ## ######## ##      \n" 
	   "  ##    ##    ##      ## ##   ##       ##         ##     ##   ## ##   ###   ## ##       ##      \n" 
	   "  ##          ##     ##   ##  ##       ##         ##     ##  ##   ##  ####  ## ##       ##      \n" 
	   "   ######     ##    ##     ## ######   ######     ########  ##     ## ## ## ## ######   ##      \n" 
	   "        ##    ##    ######### ##       ##         ##        ######### ##  #### ##       ##      \n" 
	   "  ##    ##    ##    ##     ## ##       ##         ##        ##     ## ##   ### ##       ##      \n" 
	   "   ######     ##    ##     ## ##       ##         ##        ##     ## ##    ## ######## ########\n"; 
		
		cout << "\t\t\t+----------------------------------------+\n"
				"\t\t		1. View Schedule					\n"
				"\t\t		2. Access Vehicle Records			\n"
				"\t\t		3. Add Service Record				\n"
				"\t\t		4. Modify Service Record			\n"
				"\t\t		5. Logout							\n"
				"\t\t\t+----------------------------------------+\n";
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                viewSchedule(username);
                break;
            case 2:
                accessVehicleRecords();
                break;
            case 3:
                addServiceRecord();
                break;
            case 4:
                markServiceAsComplete();
                break;
            case 5:
                cout << "Logging out...\n";
                return; // Exit the menu and return to the login screen
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void customerMenu(const string& username) {
    int choice;
    do {
cout <<"   ######  ##     ##  ######  ########  #######  ##     ## ######## ########    ########     ###    ##    ## ######## ##      \n"
	   "  ##    ## ##     ## ##    ##    ##    ##     ## ###   ### ##       ##     ##   ##     ##   ## ##   ###   ## ##       ##      \n" 
	   "  ##       ##     ## ##          ##    ##     ## #### #### ##       ##     ##   ##     ##  ##   ##  ####  ## ##       ##      \n" 
	   "  ##       ##     ##  ######     ##    ##     ## ## ### ## ######   ########    ########  ##     ## ## ## ## ######   ##      \n" 
	   "  ##       ##     ##       ##    ##    ##     ## ##     ## ##       ##   ##     ##        ######### ##  #### ##       ##      \n" 
	   "  ##    ## ##     ## ##    ##    ##    ##     ## ##     ## ##       ##    ##    ##        ##     ## ##   ### ##       ##      \n" 
	   "   ######   #######   ######     ##     #######  ##     ## ######## ##     ##   ##        ##     ## ##    ## ######## ########\n"; 
	    cout << "\t\t\t\t\t+----------------------------------------+\n"
	    		"\t\t\t\t\t|      1. View Service Records           |\n"
	    		"\t\t\t\t\t|      2. Schedule Service               |\n"
	    		"\t\t\t\t\t|      3. Cancel Service Appointment     |\n"
	    		"\t\t\t\t\t|      4. Update Personal Information    |\n"
	    		"\t\t\t\t\t|      5. Logout                         |\n"
	    		"\t\t\t\t\t+----------------------------------------+\n";
        cout << "\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                viewServiceRecords(username);
                break;
            case 2:
                scheduleService(username);
                break;
            case 3:
                cancelServiceAppointment(username);
                break;
            case 4:
                updatePersonalInfo(username);
                break;
            case 5:
                cout << "Logging out...\n";
                return; // Exit the menu and return to the login screen
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
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
	   	cout << "\n\t\t\t+-----------------------+\n"
				"\t\t\t|\t\t\t|\n"
				"\t\t\t|\t1.Add User\t|\n"
				"\t\t\t|\t2.Logout\t|\n"
				"\t\t\t|\t\t\t|\n"
				"\t\t\t+-----------------------+\n";
        cout << "\t\t\t    Enter your choice: ";
        cout << "\n\t\t\t\t   ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                cout << "Logging out...\n";
                return; // Exit the menu and return to the login screen
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 2);
}

int main() {
    loadUsers();
    loadAppointments();

    while (true) {
        string username, password, role;
cout << "  ##     ## ##     ##    ######  ##    ##  ######  ######## ######## ##     ##\n" 
        "  ##     ## ###   ###   ##    ##  ##  ##  ##    ##    ##    ##       ###   ###\n" 
        "  ##     ## #### ####   ##         ####   ##          ##    ##       #### ####\n" 
        "  ##     ## ## ### ##    ######     ##     ######     ##    ######   ## ### ##\n" 
        "   ##   ##  ##     ##         ##    ##          ##    ##    ##       ##     ##\n" 
        "    ## ##   ##     ##   ##    ##    ##    ##    ##    ##    ##       ##     ##\n" 
        "     ###    ##     ##    ######     ##     ######     ##    ######## ##     ##\n";
        cout << "\n\t\t\t Welcome! Please login.\n";
        cout << "\n+-----------------------+\n";
        cout << "\tUsername: ";
        cout << "\n+-----------------------+\n";
        cout << "\t";
        cin >> username;
        cout << "\n+-----------------------+\n";
        cout << "\tPassword: ";
        cout << "\n+-----------------------+\n";
        cout << "\t";
        cin >> password;
        system("cls");

        if (authenticateUser(username, password, role)) {
            if (role == "admin") {
                adminMenu();
            } else if (role == "staff") {
                staffMenu(username);
            } else if (role == "customer") {
                customerMenu(username);
            }
        } else {
            cout << "Invalid username or password.\n";
        }
    }

    return 0;
}

