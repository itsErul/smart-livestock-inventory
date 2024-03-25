// Made by Amirul and the Geng 
    // (24/03/2024)

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

// Define a struct to represent a livestock item
struct Livestock {
    string name;
    double price;
    int quantity;

    // Constructor
    Livestock(string n, double p, int q) : name(n), price(p), quantity(q) {}
};

// Function to display the menu
void displayMenu() {
    system("cls"); // Clear screen
    cout << "========= Livestock Sales Management System =========" << endl;
    cout << "" << endl;
    cout << "1. View Catalogue" << endl;
    cout << "" << endl;
    cout << "2. Sell Livestock" << endl;
    cout << "" << endl;
    cout << "3. Manage Livestock" << endl;
    cout << "" << endl;
    cout << "4. View Sales Report" << endl;
    cout << "" << endl;
    cout << "5. Profit" << endl;
    cout << "" << endl;
    cout << "6. Exit" << endl;
    cout << "" << endl;
    cout << "=====================================================" << endl;
    cout << "" << endl;
    cout << "Enter your choice: ";
}

void createLivestockDataFile() {
    ifstream file("livestock.txt");
    if (!file.good()) {
        ofstream newFile("livestock.txt");
        if (!newFile.is_open()) {
            cerr << "Error: Unable to create livestock.txt file." << endl;
        }
        else {
            cout << "livestock.txt file created." << endl;
            newFile.close();
        }
    }
}


// Function to load livestock data from file
vector<Livestock> loadLivestockData() {
    vector<Livestock> livestockList;
    ifstream file("livestock.txt");
    if (file.is_open()) {
        string name;
        double price;
        int quantity;
        while (file >> name >> price >> quantity) {
            livestockList.push_back(Livestock(name, price, quantity));
        }
        file.close();
    }
    else {
        cerr << "Error: Unable to open livestock.txt file." << endl;
    }
    return livestockList;
}

// Function to save livestock data to file
void saveLivestockData(const vector<Livestock>& livestockList) {
    ofstream file("livestock.txt");
    if (file.is_open()) {
        for (const auto& livestock : livestockList) {
            file << livestock.name << " " << livestock.price << " " << livestock.quantity << endl;
        }
        file.close();
    }
    else {
        cerr << "Error: Unable to save livestock data to livestock.txt file." << endl;
    }
}

// Function to manage livestock in the catalogue
void manageLivestock(vector<Livestock>& livestockList) {
    system("cls"); // Clear screen
    int choice;
    do {
            system("cls"); // Clear screen
            cout << "=============== Catalogue ==================" << endl;
            cout << "" << endl;
            cout << setw(20) << left << "Name" << setw(15) << "(RM)Price" << setw(10) << "Quantity" << endl;
            for (const auto& livestock : livestockList) {
                cout << setw(20) << left << livestock.name << setw(15) << livestock.price << setw(10) << livestock.quantity << endl;
            }
            cout << "" << endl;
            cout << "=============================================" << endl;
            cout << "" << endl;

        cout << "============= Manage Livestock =============" << endl;
        cout << "" << endl;
        cout << "1. Add new livestock" << endl;
        cout << "" << endl;
        cout << "2. Update livestock" << endl;
        cout << "" << endl;
        cout << "3. Delete livestock" << endl;
        cout << "" << endl;
        cout << "4. Back to main menu" << endl;
        cout << "" << endl;
        cout << "=============================================" << endl;
        cout << "" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string name;
        double price;
        int quantity;
        auto it = livestockList.begin(); // Declare iterator outside the switch statement
        

        switch (choice) {
        case 1:
            // Add new livestock
            cout << "Enter the name of the new livestock: ";
            cin >> name;
            if (find_if(livestockList.begin(), livestockList.end(),
                [name](const Livestock& l) {
                    return l.name == name;
                }) != livestockList.end()) {
                cout << endl;
                cout << "The livestock is already existed in the catalogue." << endl;
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            else {
                cout << "Enter the price of the livestock: ";
                cin >> price;
                cout << "Enter the quantity of the livestock: ";
                cin >> quantity;
                livestockList.push_back(Livestock(name, price, quantity));
                saveLivestockData(livestockList);
                cout << "New livestock added successfully!" << endl;
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            break;
        case 2:
            // Update livestock
            cout << "Enter the name of the livestock to update: ";
            cin >> name;
            it = find_if(livestockList.begin(), livestockList.end(),
                [name](const Livestock& l) {
                    return l.name == name;
                });
            if (it != livestockList.end()) {
                cout << "Enter the updated price of the livestock: ";
                cin >> price;
                cout << "Enter the updated quantity of the livestock: ";
                cin >> quantity;
                it->price = price;
                it->quantity = quantity;
                saveLivestockData(livestockList);
                cout << "Livestock updated successfully!" << endl;
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            else {
                cout << "The livestock is not found in the catalogue." << endl;
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            break;
        case 3:
            // Delete livestock
            cout << "Enter the name of the livestock to delete: ";
            cin >> name;
            it = find_if(livestockList.begin(), livestockList.end(),
                [name](const Livestock& l) {
                    return l.name == name;
                });
            if (it != livestockList.end()) {
                livestockList.erase(it);
                saveLivestockData(livestockList);
                cout << "Livestock deleted successfully!" << endl;
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            else {
                cout << "The livestock is not found in the catalogue." << endl;
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();
            break;
        }
    } while (true);
}


// Function to display catalogue
void displayCatalogue(const vector<Livestock>& livestockList) {
    do {
        system("cls"); // Clear screen
        cout << "=============== Catalogue ==================" << endl;
        cout << "" << endl;
        cout << setw(20) << left << "Name" << setw(15) << "(RM)Price" << setw(10) << "Quantity" << endl;
        for (const auto& livestock : livestockList) {
            cout << setw(20) << left << livestock.name << setw(15) << livestock.price << setw(10) << livestock.quantity << endl;
        }
        cout << "" << endl;
        cout << "=============================================" << endl;
        cout << "" << endl;
        cout << "Enter 'back' to return to the main menu: ";
        string input;
        cin >> input;
        if (input == "back") {
            return; // Return to main menu
        }
        else {
            cout << "Invalid input. Please enter 'back' to return to the main menu." << endl;
        }
    } while (true);
}



// Function to perform livestock sale
void sellLivestock(vector<Livestock>& livestockList) {
    do {
        system("cls"); // Clear screen
        cout << "=============== Catalogue ==================" << endl;
        cout << "" << endl;
        cout << setw(20) << left << "Name" << setw(15) << "(RM)Price" << setw(10) << "Quantity" << endl;
        for (const auto& livestock : livestockList) {
            cout << setw(20) << left << livestock.name << setw(15) << livestock.price << setw(10) << livestock.quantity << endl;
        }
        cout << "" << endl;
        cout << "=============================================" << endl;
        cout << "" << endl;
        cout << "Enter the name of the livestock to sell (or type 'back' to return to the main menu): ";
        string itemName;
        cin >> itemName;
        if (itemName == "back") {
            return; // Return to main menu
        }
        cout << "Enter the quantity to sell: ";
        int quantity;
        cin >> quantity;

        for (auto& livestock : livestockList) {
            if (livestock.name == itemName) {
                if (livestock.quantity >= quantity) {
                    double subtotal = livestock.price * quantity;
                    double tax = subtotal * 0.06; // Assuming 6% tax rate
                    double total = subtotal + tax;

                    livestock.quantity -= quantity;
                    saveLivestockData(livestockList);

                    cout << "Sale Successful!" << endl;
                    cout << "Subtotal: RM" << fixed << setprecision(2) << subtotal << endl;
                    cout << "Tax (6%): RM" << tax << endl;
                    cout << "Total: RM" << total << endl;
                    cout << "" << endl;
                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                    return; // Return to main menu after completing the sale
                }
                else {
                    cout << "Not enough quantity available!" << endl;
                    cout << "Press enter to continue...";
                    cin.ignore();
                    cin.get();
                    return; // Return to main menu if quantity is insufficient
                }
            }
        }
        cout << "Livestock not found!" << endl;
        cout << "Press enter to continue...";
        cin.ignore();
        cin.get();
    } while (true);
}

// Function to view profits
void viewProfits(const vector<Livestock>& livestockList) {
    double totalProfit = 0;
    for (const auto& livestock : livestockList) {
        totalProfit += (livestock.price * livestock.quantity); // Calculate total profit for each item
    }
    cout << "Total Profit: RM" << totalProfit << endl;
    cout << "" << endl;
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

// Function to generate and view sales report
void viewSalesReport(const vector<Livestock>& livestockList) {
    ofstream reportFile("sales_report.txt");
    if (reportFile.is_open()) {
        reportFile << "======= Sales Report =======" << endl;
        reportFile << setw(20) << left << "Name" << setw(15) << "(RM)Price" << setw(10) << "Quantity" << setw(10) << "(RM)Total" << endl;
        double totalSales = 0;
        for (const auto& livestock : livestockList) {
            double total = livestock.price * livestock.quantity;
            reportFile << setw(20) << left << livestock.name << setw(15) << livestock.price << setw(10) << livestock.quantity << setw(10) << total << endl;
            totalSales += total;
        }
        reportFile << "=============================" << endl;
        reportFile << "Total Sales: RM" << totalSales << endl;
        reportFile.close();

        // Displaying the report on console
        cout << "Sales report generated successfully!" << endl;
        cout << "" << endl;
        cout << "Press enter to view the report...";
        cin.ignore();
        cin.get();

        system("cls"); // Clear screen
        ifstream file("sales_report.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            cerr << "Error: Unable to open sales_report.txt file." << endl;
        }
        cout << "Press enter to return to the main menu...";
        cin.ignore();
        cin.get();
    }
    else {
        cerr << "Error: Unable to create sales_report.txt file." << endl;
    }
}


    // Inside main function
    int main() {
        createLivestockDataFile(); // Create livestock data file with sample data if it doesn't exist
        vector<Livestock> livestockList = loadLivestockData();
        int choice;
        do {
            displayMenu();
            cin >> choice;
            getchar(); // To consume the newline character
            system("cls");
            switch (choice) {
            case 1:
                displayCatalogue(livestockList);
                cout << "Press enter to return to the main menu...";
                break;
            case 2:
                sellLivestock(livestockList);
                break;
            case 3:
                manageLivestock(livestockList);
                break;
            case 4:
                viewSalesReport(livestockList);
                break;
            case 5:
                viewProfits(livestockList);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 6); // Corrected exit condition
        return 0;
    }

