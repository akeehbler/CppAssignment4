#include <iostream>
#include <fstream>
#include "Customer.h"
#include "Drink.h"

using namespace std;

enum MAIN_MENU { ORDER=1, PAY=2, SAVE=3, LOAD=4, EXIT=5 };

void PrintMain();
void PrintDrinks(Drink menu[], int count);
void PrintStyles();
void PromptCustomerName(Customer &custy);

int main() {
    int input = 0;
    int drink_choice = 0;
    int style_choice = 0;
    float tip;
    Customer customer = Customer();

    //File Stream for menu
    ifstream input_file;
    ofstream output_file;

    //Menu.txt fields
    int num_menu_drinks = 0;
    string drink_name;
    float drink_price;
    STYLE drink_style;

    /*
    Drink menu[6];
    menu[0] = Drink("Whole Milk", 2.50);
    menu[1] = Drink("2% Milk", 2.00);
    menu[2] = Drink("Heavy Cream", 3.50);
    menu[3] = Drink("Milkshake", 5.00);
    menu[4] = Drink("Malt", 6.00);
    menu[5] = Drink("Skim Milk", 1.00);
    */

    //Prompt for the customer name
    PromptCustomerName(customer);

    // Get the menu Drinks
    input_file.open("menu.txt");
    input_file >> num_menu_drinks;
    //TODO: do I need to eat newline here?
    //Create Menu
    Drink *menu = new Drink[num_menu_drinks];
    for(int i = 0; i < num_menu_drinks; i++){
        Drink add_drink = Drink();
        input_file >> add_drink;
        menu[i] = add_drink;
    }
    input_file.close();


    Drink next_drink;
    
    do {
        PrintMain();
        cin >> input;
        while (!cin || input < 1 || input > 5) {
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
                PrintDrinks(menu, num_menu_drinks);
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
            PromptCustomerName(customer);
            break;
        case SAVE:
            //TODO: can I do this?
            string output_file_name = customer.getName() + ".txt";
            output_file.open(output_file_name);
            //TODO: Does this automattically use the overwritten << operator?
            output_file << customer;
            output_file.close();
            PromptCustomerName(customer);
            break;
        case LOAD:
            string input_file_name = customer.getName() + ".txt";
            input_file.open(input_file_name);
            input_file >> customer;
            input_file.close();
            break;
        case EXIT:
            break;
        }
    } while (input != EXIT);
    delete [] menu;
    return 0;
}

void PrintMain() {
    cout << "Welcome to the Downtown Dairy Bar!"    << endl
         << "[" << ORDER << "] Order a Drink"       << endl
         << "[" << PAY   << "] Pay Your Tab"        << endl
         << "[" << SAVE  << "] Save Tab for Later"  << endl
         << "[" << LOAD  << "] Load Previous Tab"   << endl
         << "[" << EXIT  << "] Exit program"        << endl
         << "Please enter a menu item: ";
}

// Changed this to be dynamic based on the input from menu.txt
void PrintDrinks(Drink menu[], int count) {
    cout << "Which Drink Would you Like to Order?"        << endl;
    for(int i = 0; i < count; i++){
        cout << "[" << (i+1) << "] ";
        cout << menu[i].name << endl;
    }
    cout << "[" << (count + 1) << "] Return to main menu" << endl;
    cout << "Please enter a menu item: "                  << endl;
}

void PrintStyles() {
    cout << "[" << NEAT   << "] Neat"         << endl
         << "[" << ROCKS  << "] On the Rocks" << endl
         << "[" << DOUBLE << "] Double"       << endl
         << "[" << TALL   << "] Tall"         << endl
         << "Please enter a menu item: ";
}

void PromptCustomerName(Customer &custy){
    bool exit = false;
    string customer_name;
    do{
        cout << "Please enter your name: ";
        //TODO: do I need to handle cases where the customer inputs spaces in their name?
        // Also can cin put into a string?
        cin >> customer_name;
        //TODO: Might need newLines here
        if(!cin){
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        custy = new Customer(customer_name);
        exit = true;
    }while(!exit);
}
