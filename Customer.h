#include <string>
#include "Drink.h"
// if you need any additional includes, add them here.

#ifndef CUSTOMER_HEADER
#define CUSTOMER_HEADER
using namespace std;

const int DRINK_LIMIT = 10;
const float TAX_PCT = 0.05;

class Customer {
private:
    Drink drinks[DRINK_LIMIT];
    int drink_count;
    string name;
public:
    Customer() { drink_count = 0; } // just writing the constructor inline, since it's a one-liner.
    Customer(string _name);

    void Serve(Drink& drink, const STYLE style);
    float TotalTab(const float tip);
    void Print(const float tip);

    bool ReachedLimit(); // adding an extra function to let us print a message when we reach the limit, NOT required.

    string GetName() const;
    friend ostream& operator<<(ostream& out, const Customer custy);
    friend istream& operator>>(istream& in, Customer& custy);
    //don't need getters and setters becuase of the friend keyword, can just access the fields
};
#endif

