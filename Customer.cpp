#include "Customer.h"

using namespace std;

Customer::Customer(string _name){
    drink_count = 0;
    name = _name;
}

void Customer::Serve(Drink& drink, const STYLE serving_style)
{
    if (drink_count < DRINK_LIMIT)
    {
        drink.Prepare(serving_style);
        drinks[drink_count++] = drink;
    }
}

float Customer::TotalTab(float tip_pct)
{
    float price = 0.0;
    for (int i = 0; i < drink_count; i++)
    {
        price += drinks[i].TotalPrice();
    }
    float tax_val = price*TAX_PCT;
    float tip_val = price*tip_pct/100.0;
    return price + tax_val + tip_val;
}

void Customer::Print(const float tip)
{
    cout << "Your drinks are:" << endl;
    for (int i = 0; i < drink_count; i++)
    {
        drinks[i].Print();
    }
    cout << "***" << endl << fixed << setprecision(2)
         << left << setw(22) << "Tax:"   << TAX_PCT * 100.0 << "%" << endl
         << left << setw(22) << "Tip:"   << tip             << "%" << endl
         << left << setw(22) << "Total:" << "$" << TotalTab(tip)   << endl;
}

bool Customer::ReachedLimit() {
    return drink_count >= DRINK_LIMIT;
}

string Customer::GetName() const{
    return name;
}

//TODO do these operators take in a whole line at a time or just until a space
ostream& operator<<(ostream& out, const Customer custy){
    out << custy.GetName() << " ";
    out << custy.drink_count;
    //might need this to be std::endl;
    out << endl;
    for(int i = 0; i < custy.drink_count; i++){
        out << custy.drinks[i];
    }
    return out;
}

// TODO: not sure if this is the right way to set the name field for the customer
// Does this make a new customer i.e no drinks yet or can there be drinks then make it
// What if the drink count is over the limit, what to do?
istream& operator>>(istream& in, Customer &custy){
    in >> custy.name;
    in >> custy.drink_count;
    //TODO: how to deal with newLines here? since the next stuff is on a newline will the operator
    //know to go to the next line or do i have to "eat" the newline character
    //TODO: int i starting at 0 is assuming that this is a new customer, otherwise it will start
    //at drink count 
    for(int i = 0; i < custy.drink_count; i++){
        Drink newDrink = Drink();
        in >> newDrink;
        custy.drinks[i] = newDrink;
    }
    return in;
}

