#include <iostream>
#include <vector>
#include <fstream> 
#include <string>
using namespace std;

class Car {
public:
    string model;
    string brand;
    int year;

    Car(string m, string b, int y) {
        model = m;
        brand = b;
        year = y;
    }

    void start() const {
        cout << "The " << year << " " << brand << " " << model << " is starting..." << endl;
    }
};


void saveToFile(const vector<Car>& garage, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& car : garage) {
            file << car.model << " " << car.brand << " " << car.year << endl;
        }
        file.close();
    }
    else {
        cout << "Error opening file for saving!" << endl;
    }
}


vector<Car> loadFromFile(const string& filename) {
    vector<Car> garage;
    ifstream file(filename);
    if (file.is_open()) {
        string model, brand;
        int year;
        while (file >> model >> brand >> year) {
            garage.push_back(Car(model, brand, year));
        }
        file.close();
    }
    else {
        cout << "No saved garage found. Starting with an empty garage." << endl;
    }
    return garage;
}

int main() {
    const string filename = "garage.txt";
    vector<Car> garage = loadFromFile(filename); 

    while (true) {
        cout << "\nGarage Menu:\n";
        cout << "1. Start a car\n";
        cout << "2. Add a car to the garage\n";
        cout << "3. View all cars\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the model or brand of the car to start: ";
            string carName;
            cin >> carName;

            bool found = false;
            for (const auto& car : garage) {
                if (car.model == carName || car.brand == carName) {
                    car.start();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "No such car in this garage..." << endl;
            }
        }
        else if (choice == 2) {
            string model, brand;
            int year;
            cout << "Enter car model: ";
            cin >> model;
            cout << "Enter car brand: ";
            cin >> brand;
            cout << "Enter car year: ";
            cin >> year;

            garage.push_back(Car(model, brand, year));
            cout << "Car added successfully!" << endl;
        }
        else if (choice == 3) {
            cout << "Cars in the garage:\n";
            for (const auto& car : garage) {
                cout << "- " << car.year << " " << car.brand << " " << car.model << endl;
            }
        }
        else if (choice == 4) {
            saveToFile(garage, filename); 
            cout << "Garage saved. Exiting program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}