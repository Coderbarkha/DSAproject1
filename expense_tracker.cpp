#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Expense {
    string category;
    double amount;
};

void addExpense(vector<Expense>& expenses) {
    Expense newExpense;
    cout << "Enter category (e.g., Food, Travel, Entertainment): ";
    cin >> newExpense.category;
    cout << "Enter amount: ";
    cin >> newExpense.amount;

    expenses.push_back(newExpense);

    ofstream outFile("expenses.txt", ios::app);
    if (outFile.is_open()) {
        outFile << newExpense.category << " " << newExpense.amount << endl;
        outFile.close();
        cout << "Expense added successfully!\n";
    } else {
        cout << "Unable to open file.\n";
    }
}

void viewExpenses(const vector<Expense>& expenses) {
    cout << "\nExpenses:\n";
    for (size_t i = 0; i < expenses.size(); ++i) {
        cout << i + 1 << ". " << expenses[i].category << " - $" << fixed << setprecision(2) << expenses[i].amount << endl;
    }
}

void deleteExpense(vector<Expense>& expenses) {
    int index;
    cout << "Enter the number of the expense to delete: ";
    cin >> index;
    if (index > 0 && index <= expenses.size()) {
        expenses.erase(expenses.begin() + index - 1);
        cout << "Expense deleted successfully!\n";

        ofstream outFile("expenses.txt");
        if (outFile.is_open()) {
            for (const auto& expense : expenses) {
                outFile << expense.category << " " << expense.amount << endl;
            }
            outFile.close();
        } else {
            cout << "Unable to open file.\n";
        }
    } else {
        cout << "Invalid index.\n";
    }
}

void loadExpenses(vector<Expense>& expenses) {
    ifstream inFile("expenses.txt");
    if (inFile.is_open()) {
        Expense expense;
        while (inFile >> expense.category >> expense.amount) {
            expenses.push_back(expense);
        }
        inFile.close();
    } else {
        cout << "No existing expenses found.\n";
    }
}

int main() {
    vector<Expense> expenses;
    loadExpenses(expenses);

    int choice;
    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Delete Expense\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                deleteExpense(expenses);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
