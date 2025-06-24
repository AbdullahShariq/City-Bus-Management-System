#  City Bus Management System

A console-based C++ application for managing city bus operations including ticketing, route scheduling and driver assignments. This project demonstrates Object-Oriented Programming (OOP) principles and file handling using binary files, offering a robust platform for three types of users: **Admin**, **Passengers**, and **Drivers**.

---

##  Overview

The **City Bus Management System** is designed to simulate and manage daily city transport operations. It provides:

- An interactive, color-coded console interface  
- Modular classes for buses, routes, drivers, users, and tickets  
- Role-based features and access control  
- Binary file I/O for data persistence  

---

##  Key Features

###  Admin Panel
- Secure login with hardcoded credentials (`ID: 1234`, `Password: 5678`)
- Add/update bus details (bus number, capacity, fuel, passengers)
- Assign drivers to buses and predefined routes
- Manage ticket bookings and fare calculations (standard and discounted)
- Full access to passenger and route information

###  Passenger (User) Module
- View ticket prices 
- Purchase and cancel tickets (stored in `Users.txt`)
- View complete ticket information (ID, age, CNIC, charges)

###  Driver Module
- Login with 4-digit password
- Access assigned routes and detailed stop schedules
- Monitor fuel level and request maintenance if needed

###  Route Management
- Routes with departure times and stops  
  *(e.g., Salahuddin Ayyubi Road, DHA Phase 6, etc.)*
- Route-based ticket and driver assignment

###  Bus Management
- Tracks bus capacity and available seats
- Fuel monitoring
- Alerts for low fuel and maintenance status

###  Data Persistence
- Binary file-based storage of all records:
  - `Admin.txt`: Admin credentials
  - `Users.txt`: Passenger data
  - `BUS.txt`: Bus data

---

## 🗂️ Project Structure
```
city-bus-management-system/
├── main.cpp # All classes and logic implemented here
├── Admin.txt # Admin credentials
├── Users.txt # Passenger ticket records
├── BUS.txt # Bus details
```

---


---

##  Prerequisites

- **Compiler**: Any C++ compiler supporting C++11 or above (e.g., `g++`, MSVC)  
- **OS**: Windows (required for `windows.h` and `conio.h`)  
- **Libraries**: `iostream`, `fstream`, `ctime`, `string`, `iomanip`, etc.

---

##  Installation & Run

1. **Clone the Repository**
```bash
git clone https://github.com/your-username/city-bus-management-system.git
```
2. **Navigate to Project Directory**
```bash
cd city-bus-management-system
```
3. **Compile the Program**
```bash
g++ main.cpp -o bus_management
```
4.**Run the Executable**
```bash
./bus_management
```

---

##  Usage Instructions

Launch the program and choose from the main menu:

- **Admin Login**: Enter `ID = 1234`, `Password = 5678`
- **Passenger**: Access options to book, cancel, or view tickets
- **Driver**: Authenticate with 4-digit password to access route and bus status

Follow the on-screen prompts to interact with the system.


