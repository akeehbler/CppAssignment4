#include <iostream>
#include "Customer.h"
#include "Drink.h"

using namespace std;

enum MAIN_MENU { ORDER=1, PAY=2, EXIT=3 };
enum DRINK_MENU { WHOLE=1, TWO=2, HEAVY=3, MILKSHAKE=4, MALT=5, SKIM=6, RETURN=7 };

void PrintMain();
void PrintDrinks(Drink menu[], int count);
void PrintStyles();

int main() {
    int input = 0;
    int drink_choice = 0;
    int style_choice = 0;
    float tip;
    Customer customer = Customer();
    Drink menu[6];
    menu[0] = Drink("Whole Milk", 2.50);
    menu[1] = Drink("2% Milk", 2.00);
    menu[2] = Drink("Heavy Cream", 3.50);
    menu[3] = Drink("Milkshake", 5.00);
    menu[4] = Drink("Malt", 6.00);
    menu[5] = Drink("Skim Milk", 1.00);
    Drink next_drink;
    do {
        PrintMain();
        cin >> input;
        while (!cin || input < 1 || input > 3) {
            if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
            cout << "Please enter a valid menu item: ";
            cin >> input;
        }
        // now we have good input, handle the cases:
        switch (input) {
        case ORDER:
            if (customer.ReachedLimit()) {
                cout << "You've reached your limit!" << endl;
            }
            else {
                PrintDrinks(menu, 6);
                cin >> drink_choice;
                while (!cin || drink_choice < 1 || drink_choice > 6) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid menu item: ";
                    cin >> drink_choice;
                }
                PrintStyles();
                cin >> style_choice;
                while (!cin || style_choice < 1 || style_choice > 4) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid menu item: ";
                    cin >> style_choice;
                }
                next_drink = Drink(menu[drink_choice-1]); // copy a drink from the menu.
                switch(style_choice) {
                case NEAT:
                    customer.Serve(next_drink, NEAT);
                    break;
                case ROCKS:
                    customer.Serve(next_drink, ROCKS);
                    break;
                case DOUBLE:
                    customer.Serve(next_drink, DOUBLE);
                    break;
                case TALL:
                    customer.Serve(next_drink, TALL);
                    break;
                }
            }
            break;
        case PAY:
            cout << "Please enter your tip percent (%): ";
            cin >> tip;
            while (!cin || tip < 0.0) {
                if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                cout << "Please enter a valid tip percent (%): ";
                cin >> tip;
            }
            customer.Print(tip); // divide tip by 100 to go from percent to proportion
            customer = Customer(); // reset after paying tab.
            break;
        case EXIT:
            break;
        }
    } while (input != EXIT);

    return 0;
}

void PrintMain() {
    cout << "[" << ORDER << "] Order a Drink" << endl
         << "[" << PAY   << "] Pay Your Tab"  << endl
         << "[" << EXIT  << "] Exit"          << endl
         << "Please enter a menu item: ";
}

void PrintDrinks(Drink menu[], int count) {
    cout << "[" << WHOLE     << "] Whole Milk"          << endl
         << "[" << TWO       << "] 2% Milk"             << endl
         << "[" << HEAVY     << "] Heavy Cream"         << endl
         << "[" << MILKSHAKE << "] Milkshake"           << endl
         << "[" << MALT      << "] Malt"                << endl
         << "[" << SKIM      << "] Skim Milk"           << endl
         << "[" << count+1   << "] Return to main menu" << endl
         << "Please enter a menu item: ";
}

void PrintStyles() {
    cout << "[" << NEAT   << "] Neat"         << endl
         << "[" << ROCKS  << "] On the Rocks" << endl
         << "[" << DOUBLE << "] Double"       << endl
         << "[" << TALL   << "] Tall"         << endl
         << "Please enter a menu item: ";
}
