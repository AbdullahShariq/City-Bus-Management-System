#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

// Admin ID:1234
//Admin Password:5678

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void loadingAnimation() {
    setColor(10); 
    cout << "\nProcessing";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(500);
    }
    cout << endl;
    setColor(7); 
}

void displayHeader(const string& title) {
    system("cls");
    setColor(14); 
    cout << "\n================================================================================\n";
    cout << "                    " << title << "                    \n";
    cout << "================================================================================\n\n";
    setColor(7); 
}

class Admin {
    int ID;
    int password;

public:
    int getID() { return ID; }
    int getpassword() { return password; }

    void verify() {
        displayHeader("ADMIN LOGIN");
        int id, password;
        setColor(11); 
        cout << "Enter Your ID: ";
        cin >> id;
        if (id <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }

        cout << "Enter Your Password: ";
        cin >> password;
        if (password <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }

        int count = 0;
        ifstream f("Admin.txt", ios::in | ios::binary);
        if (!f) {
            setColor(12); 
            cout << "Data not Found!\n";
            Sleep(1000);
            exit(1);
        } else {
            loadingAnimation();
            f.read((char*)this, sizeof(*this));
            while (!f.eof()) {
                if (ID == id && this->password == password) {
                    setColor(10); 
                    cout << "\nLogin Credentials Matched! Access Granted!\n";
                    count++;
                    Sleep(1000);
                }
                f.read((char*)this, sizeof(*this));
            }
            if (count == 0) {
                setColor(12); 
                cout << "\nEntered ID and Password does not exist in our Records!\n";
                Sleep(1000);
                exit(1);
            }
            f.close();
        }
    }
};

class User {
    int Id;
    int age;
    int cnic;
    int ticketprice = 100;
    int tickets_bought;
    int total_charges;

public:
    void setId(int id) { Id = id; }
    void setAge(int a) { age = a; }
    void setCnic(int c) { cnic = c; }
    int getName() { return Id; }
    int getAge() { return age; }
    int getCnic() { return cnic; }
    int getTicketPrice() { return ticketprice; }

    void enterchoice() {
        displayHeader("USER MENU");
        char ch1;
        setColor(11); 
        cout << "Select an Option:\n";
        cout << " a) Check Ticket Price\n b) Buy A Ticket\n c) Cancel A Ticket\n d) Check Ticket Details\n";
        cout << "Enter Your Choice: ";
        cin >> ch1;
        setColor(7); 
        if (ch1 == 'a') TicketPrice();
        else if (ch1 == 'b') purchaseTicket();
        else if (ch1 == 'c') cancelTicket();
        else if (ch1 == 'd') checkTicketDetails();
    }

    void TicketPrice() {
        setColor(14); 
        cout << "\nThe Price of Ticket is: " << ticketprice << " Rupees\n";
        Sleep(1000);
        exit(1);
    }

    void purchaseTicket() {
        displayHeader("PURCHASE TICKET");
        setColor(11); 
        cout << "Enter Your ID: ";
        cin >> Id;
        if (Id <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }
        cout << "Enter Your Age: ";
        cin >> age;
        if (age <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }
        cout << "Enter Your CNIC: ";
        cin >> cnic;
        if (cnic <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }
        cout << "Enter the number of tickets you want to buy: ";
        cin >> tickets_bought;
        if (tickets_bought <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }

        total_charges = ticketprice * tickets_bought;
        setColor(10); 
        cout << "\nTotal Ticket Charges: " << total_charges << " Rupees\n";
        Sleep(1000);

        ofstream f1("Users.txt", ios::app);
        if (!f1) {
            setColor(12); 
            cout << "Data not Found!\n";
            Sleep(1000);
        } else {
            f1.write((char*)this, sizeof(*this));
            f1.close();
        }
    }

    void cancelTicket() {
        displayHeader("CANCEL TICKET");
        int ID, count = 0;
        setColor(11); 
        cout << "Enter Your ID: ";
        cin >> ID;
        if (ID <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }

        ifstream f2("Users.txt", ios::in | ios::binary);
        if (!f2) {
            setColor(12); 
            cout << "Data not Found!\n";
            Sleep(1000);
        } else {
            f2.read((char*)this, sizeof(*this));
            while (!f2.eof()) {
                if (ID == Id) {
                    f2.close();
                    ifstream f2("Users.txt", ios::in | ios::binary);
                    ofstream f3("temp.txt", ios::out);
                    if (!f2 || !f3) {
                        setColor(12); 
                        cout << "Data not Found!\n";
                        Sleep(1000);
                    }
                    while (f2.read((char*)this, sizeof(*this))) {
                        if (ID != Id)
                            f3.write((char*)this, sizeof(*this));
                    }
                    f2.close();
                    f3.close();
                    count++;
                    setColor(10); 
                    cout << "\nYour Ticket has been Cancelled!\n";
                    Sleep(1000);
                    goto A;
                }
                f2.read((char*)this, sizeof(*this));
            }
        }
        if (count == 0) {
            setColor(12); 
            cout << "\nEntered ID does not exist in our Records!\n";
            Sleep(1000);
            exit(1);
        }
        f2.close();
A:
        remove("Users.txt");
        rename("temp.txt", "Users.txt");
        exit(1);
    }

    void checkTicketDetails() {
        displayHeader("TICKET DETAILS");
        int ID, count = 0;
        setColor(11); 
        cout << "Enter Your ID: ";
        cin >> ID;
        if (ID <= 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }

        ifstream f("Users.txt", ios::in | ios::binary);
        if (!f) {
            setColor(12); 
            cout << "Data not Found!\n";
            Sleep(1000);
        } else {
            f.read((char*)this, sizeof(*this));
            while (!f.eof()) {
                if (ID == Id) {
                    setColor(14); 
                    cout << "\nID: " << Id << endl;
                    cout << "Age: " << age << endl;
                    cout << "CNIC: " << cnic << endl;
                    cout << "Total Tickets Bought: " << tickets_bought << endl;
                    cout << "Total Charges: " << total_charges << " Rupees\n";
                    count++;
                    Sleep(1000);
                    exit(1);
                }
                f.read((char*)this, sizeof(*this));
            }
            if (count == 0) {
                setColor(12); 
                cout << "\nEntered ID does not exist in our Records!\n";
                Sleep(1000);
                exit(1);
            }
            f.close();
        }
    }
};

class Routes : public Admin {
protected:
    int select;
    int destination;

public:
    void route() {
        displayHeader("ROUTE SELECTION");
        setColor(14); 
        cout << "\t**** WELCOME TO THE ROUTE SECTION ****\n\n";
        cout << "Available Stops:\n";
        cout << " 1: SALAHUDDIN AYYUBI ROAD\n 2: ABDULLAH GOTH\n 3: MALIR SESSION COURT\n";
        cout << " 4: DRIGH ROAD STATION\n 5: METROPOLE\n 6: NUMAISH\n";
        cout << " 7: FRERE HALL\n 8: DHA PHASE 6\n 9: IBRAHIM HYDERI\n";
        cout << "10: NAGAN CHOWRANGI\n 11: NIPA\n 12: COLONY GATE\n";
        setColor(11); 
        cout << "\n****** SELECT THE STOP FOR DEPARTURE ******\n";
        cin >> select;

        setColor(14); 
        if (select == 1) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: SALAHUDDIN AYYUBI ROAD (DEPARTURE, 10:00 AM)\n";
            cout << "2: ALLAH WAALI CHOWRANGI (10:10 AM)\n";
            cout << "3: NATIONAL HIGHWAY 5 (10:20 AM)\n";
            cout << "4: STEEL MILL (10:30 AM)\n";
            cout << "5: PORT BIN QASIM (10:35 AM)\n";
            cout << "6: RAZZAKABAD (10:45 AM)\n";
        } else if (select == 2) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: ABDULLAH GOTH (DEPARTURE, 11:00 AM)\n";
            cout << "2: CHOWKUNDI MOR (11:10 AM)\n";
            cout << "3: FAST UNIVERSITY (11:20 AM)\n";
            cout << "4: BHAINS COLONY (11:30 AM)\n";
            cout << "5: MANZIL P-MP (11:40 AM)\n";
            cout << "6: QUAIDA BAAD (11:50 AM)\n";
            cout << "7: MURGHI KHAANA (12:00 NOON)\n";
            cout << "8: NADRA CENTRE MALIR (12:10 PM)\n";
        } else if (select == 3) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: MALIR SESSION COURT (DEPARTURE, 12:20 PM)\n";
            cout << "2: MALIR 15 (12:30 PM)\n";
            cout << "3: KALABOARD (12:40 PM)\n";
            cout << "4: MALIR HALT (12:50 PM)\n";
            cout << "5: COLONY GATE (1:00 PM)\n";
            cout << "6: NATA KHAN BRIDGE (1:15 PM)\n";
        } else if (select == 4) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: DRIGH ROAD STATION (DEPARTURE, 1:20 PM)\n";
            cout << "2: PAF BASE (1:30 PM)\n";
            cout << "3: LAAL KOTHI (1:40 PM)\n";
            cout << "4: KARSAAZ (1:45 PM)\n";
            cout << "5: NURSERY (1:55 PM)\n";
            cout << "6: FTC (2:05 PM)\n";
            cout << "7: REGENT PLAZA (2:15 PM)\n";
        } else if (select == 5) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: METROPOLE (DEPARTURE, 1:20 PM)\n";
            cout << "2: FAWWARA CHOWK (1:30 PM)\n";
            cout << "3: ARTS COUNCIL (1:40 PM)\n";
            cout << "4: SHAHEEN COMPLEX (1:45 PM)\n";
            cout << "5: I.I CHUNDRIGARH (1:55 PM)\n";
        } else if (select == 6) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: NUMAISH (DEPARTURE, 10:00 PM)\n";
            cout << "2: TAJ COMPLEX (10:10 PM)\n";
            cout << "3: CAPRI CINEMA (10:20 PM)\n";
            cout << "4: MOBILE MARKET (10:30 PM)\n";
            cout << "5: REGAL (10:35 PM)\n";
            cout << "6: ZAINAB MARKET (10:45 PM)\n";
            cout << "7: FAWARA CHOWK (10:50 PM)\n";
        } else if (select == 7) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: FRERE HALL (DEPARTURE, 11:00 PM)\n";
            cout << "2: PSO HEAD OFFICE (11:10 PM)\n";
            cout << "3: TEEN TALWAR (11:20 PM)\n";
            cout << "4: OCEAN MALL (11:30 PM)\n";
            cout << "5: ABDULLAH SHAH GHAZI (11:40 PM)\n";
            cout << "6: DOLMEN CLIFTON (11:50 PM)\n";
            cout << "7: SEA-VIEW CLOCK TOWER (12:00 MIDNIGHT)\n";
            cout << "8: DHA PHASE 7 (12:10 AM)\n";
        } else if (select == 8) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: DHA PHASE 6 (DEPARTURE, 12:20 PM)\n";
            cout << "2: DHA PHASE 2 (12:30 PM)\n";
            cout << "3: KPT INTERCHANGE (12:40 PM)\n";
            cout << "4: KORANGI CROSSING (12:50 PM)\n";
            cout << "5: INDUS HOSPITAL (1:00 PM)\n";
            cout << "6: CBM UNIVERSITY (1:15 PM)\n";
        } else if (select == 9) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: IBRAHIM HYDERI (DEPARTURE, 1:20 PM)\n";
            cout << "2: KDA CHOWRANGI (1:30 PM)\n";
            cout << "3: NAZIMABAD NO.1 (1:40 PM)\n";
            cout << "4: URDU BAZAAR (1:45 PM)\n";
            cout << "5: GURUMANDIR (1:55 PM)\n";
            cout << "6: TEEN HATTI (2:05 PM)\n";
            cout << "7: LIAQUATABAD (2:15 PM)\n";
        } else if (select == 10) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: NAGAN CHOWRANGI (DEPARTURE, 10:00 AM)\n";
            cout << "2: SHAFIQ MOR (10:10 AM)\n";
            cout << "3: SOHRAB GOTH (10:20 AM)\n";
        } else if (select == 11) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: NIPA (DEPARTURE, 11:00 PM)\n";
            cout << "2: JOHAR MOR (11:10 PM)\n";
            cout << "3: COD (11:20 PM)\n";
            cout << "4: DRIGH ROAD STATION (11:30 PM)\n";
        } else if (select == 12) {
            cout << "\nTHE ROUTES WILL BE:\n";
            cout << "1: COLONY GATE (DEPARTURE, 12:20 PM)\n";
            cout << "2: SHAH FAISAL COLONY (12:30 PM)\n";
            cout << "3: SINGER CHOWRANGI (12:40 PM)\n";
            cout << "4: LANDHI ROAD (12:50 PM)\n";
        } else {
            setColor(12); 
            cout << "\nInvalid choice!\n";
            Sleep(1000);
            exit(0);
        }
        setColor(11);
        cout << "\n****** SELECT THE DESTINATION ******\n";
        cin >> destination;
        setColor(7); 
        system("cls");
    }
};

class Tickets : public Routes, public User {
    int ticketId;
    int seatNum;
    int ticketPrice;
    int discPrice;

public:
    void calculateFair() {
        displayHeader("TICKET FARE CALCULATION");
        int category;
        setColor(11); 
        cout << "Select Category:\n";
        cout << " 1: Regular\n 2: Disabled\n 3: Student (Verify through student card)\n";
        cin >> category;
        if (category == 1) {
            setTicketPrice(100);
            setColor(14); 
            cout << "\nTicket fare: " << getTicketPrice() << " Rupees\n\n";
        } else if (category == 2 || category == 3) {
            calculateDiscountedFair();
            setColor(14); 
            cout << "\nTicket fare: " << getDiscountedTicketPrice() << " Rupees\n\n";
        }
        Sleep(1000);
    }

    void calculateDiscountedFair() {
        ticketPrice = 100;
        setColor(14); 
        cout << "\nInitial ticket price was: " << ticketPrice << " Rupees\n";
        cout << "You have been offered 30% discount\n";
        discPrice = ticketPrice - (0.3 * 100);
    }

    void bookTicket() {
        ticketId = displayRandomTicketNum();
        setColor(10); 
        cout << "\nYour ticket (ID: " << ticketId << ") has successfully been purchased\n";
        Sleep(1000);
    }

    void bookSeat() {
        seatNum = displayRandomSeatNum();
        setColor(10); 
        cout << "\nYour Seat (Number: " << seatNum << ") has successfully been booked\n";
        Sleep(1000);
    }

    void ticketConfirmation() {
        displayHeader("TICKET CONFIRMATION");
        char choice;
        setColor(11); 
        cout << "Would you like to confirm the ticket reservation or Update/Cancel the booking?\n";
        cout << "Press U/C to cancel or Update, and any other key to confirm: ";
        cin >> choice;

        if (choice == 'C' || choice == 'c' || choice == 'U' || choice == 'u') {
            setColor(12); 
            cout << "\nTicket booking canceled.\n";
            setTicketPrice(0);
            setDiscountedFairPrice(0);
            ticketId = 0;
            seatNum = 0;
            system("cls");
            setColor(11); 
            cout << "Press 1 if you want to make another booking\n";
            cout << "Press 2 to exit the application\n";
            int s;
            cin >> s;
            if (s == 1) {
                Tickets r1;
                r1.route();
                r1.calculateFair();
                r1.ticketConfirmation();
                r1.bookTicket();
                r1.bookSeat();
                r1.displayTicketingInfo();
                exit(0);
            } else if (s == 2) {
                exit(0);
            }
        } else {
            setColor(10); 
            cout << "\nTicket reservation confirmed.\n";
            Sleep(1000);
            system("cls");
        }
    }

    void displayTicketingInfo() {
        displayHeader("TICKET INFORMATION");
        setColor(14); 
        cout << string(80, '-') << endl;
        cout << "\t\tThank you for choosing City Bus Services\n\n";
        cout << "\t\tYOUR TICKET DETAILS ARE AS FOLLOWS:\n\n";
        cout << "\t\t\tTicket ID: " << ticketId << endl;
        cout << "\t\t\tSeat Number: " << seatNum << endl;
        cout << "\t\t\tStart Point: Route# " << select << endl;
        cout << "\t\t\tDestination: Route# " << destination << endl;
        cout << string(80, '-') << endl;
        setColor(7); 
        Sleep(2000);
    }

    int displayRandomSeatNum() { return rand() % 50 + 1; }
    int displayRandomTicketNum() { return rand() % 800 + 1; }
    void allFuncCalling() {
        route();
        system("cls");
        calculateFair();
        ticketConfirmation();
        bookTicket();
        bookSeat();
        srand(time(NULL));
        displayTicketingInfo();
    }
    void allFuncCalling2() {
        route();
        system("cls");
        ticketConfirmation();
        bookTicket();
        bookSeat();
        srand(time(NULL));
        displayTicketingInfo();
    }
    void setTicketPrice(int price) { ticketPrice = price; }
    int getTicketPrice() { return ticketPrice; }
    void setDiscountedFairPrice(int price2) { discPrice = price2; }
    int getDiscountedTicketPrice() { return discPrice; }
    int getTicketId() { return ticketId; }
};

class Bus {
    int capacity, currentpass, remcapacity, fuel;
public:
    int number;

    Bus() : number(0), capacity(50), currentpass(0), remcapacity(0), fuel(220) {}
    Bus(int number, int currentpass) : number(number), capacity(50), currentpass(currentpass), remcapacity(capacity - currentpass), fuel(220) {}
    Bus(int number) : number(number), capacity(50), currentpass(0), remcapacity(capacity), fuel(220) {}

    void setBusNumber(int id) {
        if (id < 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
        } else {
            number = id;
        }
    }
    int getBusNumber() { return number; }
    void setBusCapacity(int cap) { capacity = cap; }
    int getBusCapacity() { return capacity; }
    void setBusCurrentPassengers(int pass) { currentpass = pass; }
    int getBusCurrentPassengers() { return currentpass; }
    int getAvailableSeats() { remcapacity = capacity - currentpass; return remcapacity; }
    int getBusFuel() { return fuel; }

    void CheckCapacity() {
        remcapacity = capacity - currentpass;
        setColor(14); 
        cout << "\n---------------------- Capacity -------------------------\n";
        cout << "\nTotal Capacity: \t" << capacity << "\n";
        cout << "Current Passengers: \t" << currentpass << "\n";
        cout << "Available Seats: \t" << remcapacity << "\n";
        cout << "-------------------------------------------------------\n";
        setColor(7); 
        Sleep(1000);
    }

    virtual void inputBus() {
        displayHeader("BUS INFORMATION");
        setColor(11); 
        cout << "Input Bus Number (1-11): ";
        cin >> number;
        cout << "Input No of Current Passengers: ";
        cin >> currentpass;
        remcapacity = capacity - currentpass;
        setColor(7); 
    }

    virtual void outputBus() {
        displayHeader("BUS DETAILS");
        remcapacity = capacity - currentpass;
        setColor(14);
        cout << string(80, '-') << endl;
        cout << "\t\tBus Number: \t" << number << "\n";
        cout << "\t\tTotal Capacity: \t" << capacity << "\n";
        cout << "\t\tCurrent Passengers: \t" << currentpass << "\n";
        cout << "\t\tAvailable Seats: \t" << remcapacity << "\n";
        cout << "\t\tCurrent Fuel: \t\t" << fuel << " Litres\n";
        cout << string(80, '-') << endl;
        setColor(7); 
        Sleep(2000);
    }

    friend void Maintainance(Bus);
};

void Maintainance(Bus obj) {
    displayHeader("BUS MAINTENANCE");
    if (obj.fuel < 80) {
        setColor(12);
        cout << "\nNeed to Refuel the tank!\n";
    } else {
        setColor(10); 
        cout << "\nReady to go!\n";
    }
    Sleep(1000);
    setColor(7); 
}

class Driver : public Bus {
    string name;
    int password;
    int duration;
public:
    Bus* b;

    Driver() : name("Unknown"), password(0) {}
    Driver(string name, int password, int num) : Bus(num), name(name), password(password) {}

    void setDriverName(string n) { name = n; }
    string getDriverName() { return name; }
    void setDriverPassword(int p) { password = p; }
    int getDriverPassword() { return password; }

    void setDriverDetails() {
        displayHeader("DRIVER INFORMATION");
        setColor(11); 
        cout << "Input Driver Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Input Driver Password: ";
        cin >> password;
        setColor(7); 
    }

    void getDriverDetails() {
        displayHeader("DRIVER DETAILS");
        setColor(14);
        cout << string(80, '-') << endl;
        cout << "\t\tDriver Name: \t" << name << "\n";
        cout << "\t\tDriver Password: \t" << password << "\n";
        cout << string(80, '-') << endl;
        setColor(7); 
        Sleep(2000);
    }

    int write_in_file() {
        ofstream fout("driver", ios::app | ios::binary);
        fout.write((char*)this, sizeof(*this));
        fout.close();
        return 0;
    }

    int read_from_file() {
        ifstream fin("driver", ios::in | ios::binary);
        if (!fin) {
            setColor(12); 
            cout << "Data not Found!\n";
            Sleep(1000);
        } else {
            fin.read((char*)this, sizeof(*this));
            while (!fin.eof()) {
                getDriverDetails();
                fin.read((char*)this, sizeof(*this));
            }
            fin.close();
        }
        return 0;
    }

    void search(int p) {
        displayHeader("DRIVER AUTHENTICATION");
        if (p == 1234 || p == 2345 || p == 3456 || p == 4567 || p == 5678) {
            setColor(10); 
            cout << "Access Granted!\n";
            Sleep(1000);
        } else {
            setColor(12); 
            cout << "Access Not Granted!\n";
            cout << "Exiting the application...\n";
            Sleep(1000);
            exit(1);
        }
    }

    void takeBreak(Bus* bus) {
        displayHeader("DRIVER BREAK");
        char choice;
        setColor(11); 
        cout << "Enter this section only if your travel hours for the day are greater than 2 and less than 7\n";
        cout << "Enter y/Y to enter this section: ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            b = bus;
            cout << "Enter your travel hours (in int) for the day: ";
            cin >> duration;
            if (duration >= 3 && duration <= 6) {
                setColor(10); 
                cout << "\nTake Some Rest!\n";
                Sleep(1000);
            } else if (duration > 6) {
                setColor(12); 
                cout << "\nInvalid duration!\n";
                Sleep(1000);
                exit(0);
            } else if (duration < 3) {
                setColor(12); 
                cout << "\nYou need to continue to work for " << duration + 1 << " hours before taking a break\n";
                Sleep(1000);
            }
        } else {
            setColor(12); 
            cout << "\nBus section terminated!\n";
            Sleep(1000);
            exit(0);
        }
    }

    void AssignRoute() {
        displayHeader("ROUTE ASSIGNMENT");
        setColor(14); 
        if (number == 1) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: SALAHUDDIN AYYUBI ROAD (DEPARTURE, 10:00 AM)\n";
            cout << "2: ALLAH WAALI CHOWRANGI (10:10 AM)\n";
            cout << "3: NATIONAL HIGHWAY 5 (10:20 AM)\n";
            cout << "4: STEEL MILL (10:30 AM)\n";
            cout << "5: PORT BIN QASIM (10:35 AM)\n";
            cout << "6: RAZZAKABAD (10:45 AM)\n";
        } else if (number == 2) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: ABDULLAH GOTH (DEPARTURE, 11:00 AM)\n";
            cout << "2: CHOWKUNDI MOR (11:10 AM)\n";
            cout << "3: FAST UNIVERSITY (11:20 AM)\n";
            cout << "4: BHAINS COLONY (11:30 AM)\n";
            cout << "5: MANZIL PUMP (11:40 AM)\n";
            cout << "6: QUAIDA BAAD (11:50 AM)\n";
            cout << "7: MURGHI KHAANA (12:00 NOON)\n";
            cout << "8: NADRA CENTRE MALIR (12:10 PM)\n";
        } else if (number == 3) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: MALIR SESSION COURT (DEPARTURE, 12:20 PM)\n";
            cout << "2: MALIR 15 (12:30 PM)\n";
            cout << "3: KALABOARD (12:40 PM)\n";
            cout << "4: MALIR HALT (12:50 PM)\n";
            cout << "5: COLONY GATE (1:00 PM)\n";
            cout << "6: NATA KHAN BRIDGE (1:15 PM)\n";
        } else if (number == 4) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: DRIGH ROAD STATION (DEPARTURE, 1:20 PM)\n";
            cout << "2: PAF BASE (1:30 PM)\n";
            cout << "3: LAAL KOTHI (1:40 PM)\n";
            cout << "4: KARSAAZ (1:45 PM)\n";
            cout << "5: NURSERY (1:55 PM)\n";
            cout << "6: FTC (2:05 PM)\n";
            cout << "7: REGENT PLAZA (2:15 PM)\n";
        } else if (number == 5) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: METROPOLE (DEPARTURE, 1:20 PM)\n";
            cout << "2: FAWWARA CHOWK (1:30 PM)\n";
            cout << "3: ARTS COUNCIL (1:40 PM)\n";
            cout << "4: SHAHEEN COMPLEX (1:45 PM)\n";
            cout << "5: I.I CHUNDRIGARH (1:55 PM)\n";
        } else if (number == 6) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: NUMAISH (DEPARTURE, 10:00 PM)\n";
            cout << "2: TAJ COMPLEX (10:10 PM)\n";
            cout << "3: CAPRI CINEMA (10:20 PM)\n";
            cout << "4: MOBILE MARKET (10:30 PM)\n";
            cout << "5: REGAL (10:35 PM)\n";
            cout << "6: ZAINAB MARKET (10:45 PM)\n";
            cout << "7: FAWARA CHOWK (10:50 PM)\n";
        } else if (number == 7) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: FRERE HALL (DEPARTURE, 11:00 PM)\n";
            cout << "2: PSO HEAD OFFICE (11:10 PM)\n";
            cout << "3: TEEN TALWAR (11:20 PM)\n";
            cout << "4: OCEAN MALL (11:30 PM)\n";
            cout << "5: ABDULLAH SHAH GHAZI (11:40 PM)\n";
            cout << "6: DOLMEN CLIFTON (11:50 PM)\n";
            cout << "7: SEA-VIEW CLOCK TOWER (12:00 MIDNIGHT)\n";
            cout << "8: DHA PHASE 7 (12:10 AM)\n";
        } else if (number == 8) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: DHA PHASE 6 (DEPARTURE, 12:20 PM)\n";
            cout << "2: DHA PHASE 2 (12:30 PM)\n";
            cout << "3: KPT INTERCHANGE (12:40 PM)\n";
            cout << "4: KORANGI CROSSING (12:50 PM)\n";
            cout << "5: INDUS HOSPITAL (1:00 PM)\n";
            cout << "6: CBM UNIVERSITY (1:15 PM)\n";
        } else if (number == 9) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: IBRAHIM HYDERI (DEPARTURE, 1:20 PM)\n";
            cout << "2: KDA CHOWRANGI (1:30 PM)\n";
            cout << "3: NAZIMABAD NO.1 (1:40 PM)\n";
            cout << "4: URDU BAZAAR (1:45 PM)\n";
            cout << "5: GURUMANDIR (1:55 PM)\n";
            cout << "6: TEEN HATTI (2:05 PM)\n";
            cout << "7: LIAQUATABAD (2:15 PM)\n";
        } else if (number == 10) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: NAGAN CHOWRANGI (DEPARTURE, 10:00 AM)\n";
            cout << "2: SHAFIQ MOR (10:10 AM)\n";
            cout << "3: SOHRAB GOTH (10:20 AM)\n";
        } else if (number == 11) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: NIPA (DEPARTURE, 11:00 PM)\n";
            cout << "2: JOHAR MOR (11:10 PM)\n";
            cout << "3: COD (11:20 PM)\n";
            cout << "4: DRIGH ROAD STATION (11:30 PM)\n";
        } else if (number == 12) {
            cout << "\nRoute Assigned to Driver:\n";
            cout << "1: COLONY GATE (DEPARTURE, 12:20 PM)\n";
            cout << "2: SHAH FAISAL COLONY (12:30 PM)\n";
            cout << "3: SINGER CHOWRANGI (12:40 PM)\n";
            cout << "4: LANDHI ROAD (12:50 PM)\n";
        } else {
            setColor(12); 
            cout << "\nInvalid route!\n";
            Sleep(1000);
            exit(1);
        }
        setColor(7); 
        Sleep(2000);
    }

    void BusAssignment(Bus* bus) {
        b = bus;
        setColor(10); 
        cout << "\nDriver " << name << " is Assigned to Bus # " << b->number << "\n\n";
        setColor(7); 
        Sleep(1000);
    }
};

int main() {
    displayHeader("CITY BUS MANAGEMENT SYSTEM");
    setColor(14);
    cout << "************ CHOOSE THE RELEVANT CATEGORY **************\n";
    cout << " 1: ADMIN\n 2: USER\n 3: DRIVER\n";
    setColor(11); 
    cout << "Enter Your Choice: ";
    int choice;
    cin >> choice;
    setColor(7); 

    Admin objad;
    User objus;

    if (choice == 1) {
        objad.verify();
        displayHeader("ADMIN PANEL");
        setColor(11); 
        cout << "Select an Option:\n";
        cout << "1. Bus\n2. Driver\n3. Routes & Tickets\n";
        int sel;
        cin >> sel;
        if (sel == 1) {
            int number, currentpass, remcapacity, capacity = 50;
            displayHeader("BUS MANAGEMENT");
            setColor(11); 
            cout << "Input Bus Number (1-11): ";
            cin >> number;
            cout << "Input No of Current Passengers: ";
            cin >> currentpass;
            remcapacity = capacity - currentpass;
            Bus obj(number, currentpass);
            fstream f("BUS.txt", ios::out);
            f.write((char*)&obj, sizeof(obj));
            f.close();
            f.open("BUS.txt", ios::in);
            f.read((char*)&obj, sizeof(obj));
            obj.outputBus();
        } else if (sel == 2) {
            int num, currentpass, remcapacity, capacity = 50;
            displayHeader("DRIVER MANAGEMENT");
            setColor(11); 
            cout << "Total Capacity: 50\n";
            cout << "Input Bus Number (1-11): ";
            cin >> num;
            cout << "Input No of Current Passengers: ";
            cin >> currentpass;
            if (currentpass < 0) {
                setColor(12); 
                cout << "Invalid Input!\n";
                Sleep(1000);
                exit(1);
            }
            remcapacity = capacity - currentpass;
            if (remcapacity < 0) {
                setColor(12); 
                cout << "No space available!\n";
                Sleep(1000);
                exit(0);
            }
            Bus obj(num, currentpass);
            string name;
            int password;
            system("cls");
            setColor(11); 
            cout << "Enter Driver's Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter 4-digit Password: ";
            cin >> password;
            Driver dr(name, password, num);
            dr.search(password);
            dr.AssignRoute();
            Maintainance(obj);
            dr.BusAssignment(&obj);
            dr.takeBreak(&obj);
        } else if (sel == 3) {
            srand(static_cast<unsigned int>(time(0)));
            Tickets r;
            r.allFuncCalling();
            srand(time(NULL));
        } else {
            setColor(12); 
            cout << "Invalid choice!\n";
            Sleep(1000);
            exit(0);
        }
    } else if (choice == 2) {
        objus.enterchoice();
        srand(static_cast<unsigned int>(time(0)));
        Tickets r;
        r.allFuncCalling2();
        srand(time(NULL));
    } else if (choice == 3) {
        int number, currentpass, remcapacity, capacity = 50;
        displayHeader("DRIVER SECTION");
        setColor(11); 
        cout << "Total Capacity: 50\n";
        cout << "Input Bus Number (1-11): ";
        cin >> number;
        cout << "Input No of Current Passengers: ";
        cin >> currentpass;
        if (currentpass < 0) {
            setColor(12); 
            cout << "Invalid Input!\n";
            Sleep(1000);
            exit(1);
        }
        remcapacity = capacity - currentpass;
        if (remcapacity < 0) {
            setColor(12); 
            cout << "No space available!\n";
            Sleep(1000);
            exit(0);
        }
        Bus obj(number, currentpass);
        fstream f("BUS.txt", ios::out);
        f.write((char*)&obj, sizeof(obj));
        f.close();
        f.open("BUS.txt", ios::in);
        f.read((char*)&obj, sizeof(obj));
        obj.outputBus();
        string name;
        int password;
        setColor(11); 
        cout << "Enter Driver's Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter 4-digit Password: ";
        cin >> password;
        Driver dr(name, password, number);
        dr.search(password);
        dr.AssignRoute();
        Maintainance(obj);
        dr.BusAssignment(&obj);
        dr.takeBreak(&obj);
    } else {
        setColor(12); 
        cout << "Invalid Input!\n";
        Sleep(1000);
        exit(1);
    }
}
