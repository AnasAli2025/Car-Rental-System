#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Car {
public:
    int car_id;
    string brand;
    string model;
    double rental_Price;
    Car* next;
    Car(int id, string b, string m, double price) {
        car_id = id;
        brand = b;
        model = m;
        rental_Price = price;
        next = nullptr;
    }
    void display() {
        cout << "Car ID: " << car_id << ", Brand: " << brand
             << ", Model: " << model << ", Price per day: $" << rental_Price << endl;
    }
};
class CarList {
public:
    Car* head;
    CarList() { 
        head = nullptr; 
        }
    void addCar(int id, string brand, string model, double price) {
        Car* newCar = new Car(id, brand, model, price);
        newCar->next = head;
        head = newCar;
        save_file();
    }
    void save_file() {
        ofstream outFile("cars.txt");
        Car* temp = head;
        while (temp != nullptr) {
            outFile << temp->car_id << " " << temp->brand << " " << temp->model
                    << " " << temp->rental_Price << endl;
            temp = temp->next;
        }
        outFile.close();
    }
    void display_Cars() {
        Car* temp = head;
        if (temp == nullptr) {
            cout << "No cars available.\n";
            return;
        }
        cout << "Available Cars:" << endl;
        while (temp != nullptr) {
            temp->display();
            temp = temp->next;
        }
    }
    Car* findCar(int id) {
        Car* temp = head;
        while (temp != nullptr) {
            if (temp->car_id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};
class Rent {
public:
    int car_id;
    int cust_id;
    int rent_days;
    Rent* next;
    Rent(int c, int cust, int rent) {
        car_id = c;
        cust_id = cust;
        rent_days = rent;
        next = nullptr;
    }
    void display() {
        cout << "Car ID: " << car_id << ", Customer ID: " << cust_id
             << ", Days Rented: " << rent_days << endl;
    }
};
class RentList {
public:
    Rent* head;
    RentList() { 
        head = nullptr; 
        }
    void add_rent(int car_id, int cust_id, int rent_days) {
        Rent* newRent = new Rent(car_id, cust_id, rent_days);
        newRent->next = head;
        head = newRent;
        save_file();
    }
    void save_file() {
        ofstream outFile("Rental.txt");
        Rent* temp = head;
        while (temp != nullptr) {
            outFile << temp->car_id << " " << temp->cust_id << " " << temp->rent_days << endl;
            temp = temp->next;
        }
        outFile.close();
    }
    void return_Car(int car_id, int cust_id) {
        Rent* temp = head;
        Rent* prev = nullptr;
        while (temp != nullptr) {
            if (temp->car_id == car_id && temp->cust_id == cust_id) {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                save_file();
                cout << "Car is  returned!\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Rent record not found!\n";
    }
    bool Available(int car_id) {
        Rent* temp = head;
        while (temp != nullptr) {
            if (temp->car_id == car_id) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }
    void Rental_History() {
        Rent* temp = head;
        cout << "Rental History:" << endl;
        if (temp == nullptr) {
            cout << " Rental history is not available.\n";
            return;
        }
        while (temp != nullptr) {
            temp->display();
            temp = temp->next;
        }
    }
};
           CarList obj1; 
           RentList obj2;
void rent_car() {
    int car_id, cust_id, day;
    cout << "Enter Customer ID: ";
    cin >> cust_id;
    cout << "Enter Car ID to rent: ";
    cin >> car_id;
    cout << "Enter number of days: ";
    cin >> day;
    if (obj2.Available(car_id)) {
        Car* temp = obj1.findCar(car_id);
        if (temp != nullptr) {
            double rental_amount = temp->rental_Price * day;
            obj2.add_rent(car_id, cust_id, day);
            cout << "Car on rent!" << endl;
            cout << "Total Amount:  "<<endl;
            cout<<  "Car ID       : " << car_id<<endl;
            cout<<  "Customer ID  : " << cust_id<<endl;
            cout<<  "Days         : " << day<<endl;
            cout<<  "Total Cost   : " << rental_amount << endl;
        } 
        else {
            cout << "Car does not exist!" << endl;
        }
    } 
    else {
        cout << "Car is not available for rent!" << endl;
    }
}
void returning_car() {
    int car_id, cust_id;
    cout << "Enter Car ID to return: ";
    cin >> car_id;
    cout << "Enter Customer ID: ";
    cin >> cust_id;

    if (!obj2.Available(car_id)) {
        obj2.return_Car(car_id, cust_id);
    }
     else {
        cout << "This car is not currently rented!\n";
    }
}
int main() {
    obj1.addCar(10, "Toyota", "Camr ",5000);
    obj1.addCar(9, "Honda", " Civic", 4500);
    obj1.addCar(8, "Crolla", "Focus", 4000);
    obj1.addCar(7, "Toyota", "Camry", 5000);
    obj1.addCar(6, "Honda", " Civic", 4500);
    obj1.addCar(5, "Crolla", "Focus", 4000);
    obj1.addCar(4, "Toyota", "Camry", 5000);
    obj1.addCar(3, "Honda", " Civic", 4500);
    obj1.addCar(2, "Crolla", "Focus", 4000);
    obj1.addCar(1, "Crolla","Focus",  4000);
    int choice;
    while (true) {
        cout << "***********************************************\n";
        cout << "*            Car Rental Management System     *\n";
        cout << "*              1. Rent a Car                  *\n";
        cout << "*              2. Return a Car                *\n";
        cout << "*              3. Display All Car             *\n";
        cout << "*              4. View Rental History         *\n";
        cout << "*              5. Exit                        *\n";
        cout << "***********************************************";
        cout<<endl;
        cout<<endl;
        cout << "***********************************************\n";
        cout << "*              Enter your choice:             *\n";
        cout << "***********************************************"<<endl;
        cin>>choice;
        switch (choice) {
        case 1:
          rent_car();
            break;
        case 2:
          returning_car();
            break;
        case 3:
            obj1.display_Cars();
            break;
        case 4:
            obj2.Rental_History();
            break;
        case 5:
            cout << "Thank you!" << endl;
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}