#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// Menu & Panels
void WelcomeMenu();
string LoginSignupMenu(string roleInput);
void ShowBanner();
void SignUp(string username[], string password[], string contact[], string cnic[], string role[], string roleInput, int &userCount);
bool SignIn(string username[], string password[], string role[], string roleInput, int userCount, string &uname, string &pass);

// Validations
bool userNameChecker(string uname);
bool passwordChecker(string pass);
bool contactChecker(string contact);
bool cnicChecker(string cnic);

// Helper
void pause();
// admin
void AddFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int &foodCount);
void UpdateFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount);
void DeleteFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int &foodCount);
void DisplayFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount);
void ViewAllOrders(string username[], string foodNames[], string companyNames[],
                   double foodPrices[], int customerOrders[][50],
                   int customerOrderQty[][50], int customerOrderCount[], int userCount);

// customer
void DisplayMenu(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount);
void SearchFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount);
void PlaceOrder(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount,
                int customerOrders[][50], int customerOrderQty[][50], int customerOrderCount[], int userIndex);

void ViewOrder(string foodNames[], string companyNames[], double foodPrices[],
               int customerOrders[][50], int customerOrderQty[][50], int customerOrderCount[], int userIndex);

// Panels
void AdminPanel(
    string foodNames[], string companyNames[],
    double foodPrices[], int foodQuantity[],
    int &foodCount,
    string username[],
    int customerOrders[][50],
    int customerOrderQty[][50],
    int customerOrderCount[],
    int userCount);

void CustomerPanel(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[],
                   int foodCount, int userIndex,
                   int customerOrders[][50], int customerOrderQty[][50], int customerOrderCount[]);

// MAIN FUNCTION
int main()
{
    int customerOrders[10][50] = {0};
    int customerOrderQty[10][50] = {0};
    int customerOrderCount[10] = {0};

    string username[10];
    string password[10];
    string contact[10];
    string cnic[10];
    string role[10];
    int userCount = 0;
    string foodNames[10];
    string companyNames[10];
    double foodPrices[10];
    int foodQuantity[10];
    int foodCount = 0;
    while (true)
    {
        system("clear");
        ShowBanner();

        WelcomeMenu();

        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            while (true)
            {
                string action = LoginSignupMenu("Admin");

                if (action == "1")
                {
                    SignUp(username, password, contact, cnic, role, "Admin", userCount);
                }
                else if (action == "2")
                {
                    string uname, pass;
                    if (SignIn(username, password, role, "Admin", userCount, uname, pass))
                    {
                        cout << "Sign In Successful!" << endl;
                        pause();
                        AdminPanel(foodNames, companyNames, foodPrices, foodQuantity, foodCount,
                                   username, customerOrders, customerOrderQty, customerOrderCount, userCount);
                        break;
                    }
                    else
                    {
                        cout << "Invalid credentials!" << endl;
                        pause();
                    }
                }
                else if (action == "3")
                {
                    break;
                }
            }
        }

        else if (choice == "2")
        {
            while (true)
            {
                string action = LoginSignupMenu("Customer");

                if (action == "1")
                {
                    SignUp(username, password, contact, cnic, role, "Customer", userCount);
                }
                else if (action == "2")
                {
                    string uname, pass;
                    if (SignIn(username, password, role, "Customer", userCount, uname, pass))
                    {
                        int userIndex = -1;
                        for (int i = 0; i < userCount; i++)
                        {
                            if (username[i] == uname && role[i] == "Customer")
                            {
                                userIndex = i;
                                break;
                            }
                        }
                        cout << "Sign In Successful!" << endl;
                        pause();
                        CustomerPanel(foodNames, companyNames, foodPrices, foodQuantity, foodCount, userIndex,
                                      customerOrders, customerOrderQty, customerOrderCount);
                        break;
                    }
                    else
                    {
                        cout << "Invalid credentials!" << endl;
                        pause();
                    }
                }
                else if (action == "3")
                {
                    break;
                }
            }
        }

        else if (choice == "3")
        {
            cout << "Exiting Program!!" << endl;
            break;
        }
        else
        {
            cout << "Invalid Input!!" << endl;
            pause();
        }
    }

    return 0;
}

// FUNCTION DEFINITIONS
void ShowBanner()
{
    cout << "\e[0;33m==============================================================" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|                                                            |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|             ██████╗  █████╗ ██╗  ██╗██╗███████╗            |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|            ██╔════╝ ██╔══██╗██║ ██╔╝██║╚══███╔╝            |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|            ██║  ███╗███████║█████╔╝ ██║  ███╔╝             |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|            ██║   ██║██╔══██║██╔═██╗ ██║ ███╔╝              |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|            ╚██████╔╝██║  ██║██║  ██╗██║███████╗            |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|             ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝            |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|                                                            |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|                  BAKERY MANAGEMENT SYSTEM                  |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "|                                                            |" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    cout << "==============================================================" << endl;
}

// MENU & PANELS
void WelcomeMenu()
{
    cout << "\033[1;31m============================================================" << endl;
    cout << "          WELCOME TO GAKIZ BAKERY MANAGEMENT SYSTEM                              " << endl;
    cout << "============================================================" << endl;
    cout << "1. Admin                                                                               " << endl;
    cout << "2. Customer                                                                            " << endl;
    cout << "3. Exit                                                                                " << endl;
    cout << "Enter your choice: ";
}

string LoginSignupMenu(string roleInput)
{
    while (true)
    {
        system("clear");
        cout << "\033[1;35m--------------------------------------------------------------------------------------" << endl;
        cout << "                  SIGN UP / SIGN IN PAGE                                              " << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
        cout << "Role: " << roleInput << endl;
        cout << "1. Sign Up                                                                            " << endl;
        cout << "2. Sign In                                                                            " << endl;
        cout << "3. Exit                                                                               " << endl;
        cout << "Enter your choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1" || choice == "2" || choice == "3")
        {
            return choice;
        }
        else
        {
            cout << "Invalid Input!!" << endl;
            pause();
        }
    }
}

void SignUp(string username[], string password[], string contact[], string cnic[], string role[], string roleInput, int &userCount)
{
    system("clear");
    string uname, pass, contct, cnicNo;
    int attempts = 0;

    while (true)
    {
        cout << "\033[1;35mEnter Username: ";
        getline(cin, uname);
        cout << "Enter Password: ";
        getline(cin, pass);
        cout << "Enter Contact: ";
        getline(cin, contct);
        cout << "Enter CNIC: ";
        getline(cin, cnicNo);

        bool valid = true;

        if (!userNameChecker(uname))
            valid = false;
        if (!passwordChecker(pass))
            valid = false;
        if (!contactChecker(contct))
            valid = false;
        if (!cnicChecker(cnicNo))
            valid = false;

        if (valid)
        {
            username[userCount] = uname;
            password[userCount] = pass;
            contact[userCount] = contct;
            cnic[userCount] = cnicNo;
            role[userCount] = roleInput;
            userCount++;

            cout << "Sign Up Successful!!" << endl;
            pause();
            break;
        }
        else
        {
            attempts++;
            cout << "Please correct the above errors and try again." << endl;

            if (attempts >= 3)
            {
                cout << "Too many failed attempts! Returning to " << roleInput << " menu..." << endl;
                pause();
                break;
            }
        }
    }
}
bool SignIn(string username[], string password[], string role[], string roleInput, int userCount, string &uname, string &pass)
{
    cout << "Enter Username: ";
    getline(cin, uname);
    cout << "Enter Password: ";
    getline(cin, pass);

    for (int i = 0; i < userCount; i++)
    {
        if (username[i] == uname && password[i] == pass && role[i] == roleInput)
        {
            return true;
        }
    }
    return false;
}

// VALIDATIONS
bool userNameChecker(string uname)
{
    if (uname.length() == 0)
    {
        cout << "\033[0;31mInvalid Username! Username cannot be empty.\033[0m" << endl;
        return false;
    }
    if (uname.length() > 12)
    {
        cout << "\033[0;31mInvalid Username! Username cannot be more than 12 characters.\033[0m" << endl;
        return false;
    }
    if (!(uname[0] >= 'A' && uname[0] <= 'Z'))
    {
        cout << "\033[0;31mInvalid Username! First letter must be capital.\033[0m" << endl;
        return false;
    }
    for (int i = 0; i < uname.length(); i++)
    {
        if (uname[i] == ' ')
        {
            cout << "\033[0;31mInvalid Username! Spaces are not allowed.\033[0m" << endl;
            return false;
        }
    }
    return true;
}

bool passwordChecker(string pass)
{
    if (pass.length() < 6)
    {
        cout << "\033[0;31mInvalid Password! Password must be at least 6 characters long.\033[0m" << endl;
        return false;
    }

    bool hasNumber;
    hasNumber = false;
    bool hasSpecial;
    hasSpecial = false;

    string specialChars = "@!#$%&*()_+=-{}[];:,./?";

    for (int i = 0; i < pass.length(); i++)
    {
        if (pass[i] >= '0' && pass[i] <= '9')
        {
            hasNumber = true;
        }
        for (int j = 0; j < specialChars.length(); j++)
        {
            if (pass[i] == specialChars[j])
            {
                hasSpecial = true;
            }
        }
    }

    if (!hasNumber || !hasSpecial)
    {
        cout << "\033[0;31mInvalid Password! Password must contain at least 1 number and 1 special character.\033[0m" << endl;
        return false;
    }

    return true;
}

bool contactChecker(string contact)
{
    if (contact.length() == 0)
    {
        cout << "\033[0;31mInvalid Contact Number! It cannot be empty.\033[0m" << endl;
        return false;
    }
    if (contact.length() != 11)
    {
        cout << "\033[0;31mInvalid Contact Number! It must be exactly 11 digits.\033[0m" << endl;
        return false;
    }

    for (int i = 0; i < contact.length(); i++)
    {
        if (!(contact[i] >= '0' && contact[i] <= '9'))
        {
            cout << "\033[0;31mInvalid Contact Number! Only digits are allowed.\033[0m" << endl;
            return false;
        }
    }
    return true;
}

bool cnicChecker(string cnic)
{
    if (cnic.length() == 0)
    {
        cout << "\033[0;31mInvalid CNIC! CNIC cannot be empty.\033[0m" << endl;
        return false;
    }
    if (cnic.length() != 13)
    {
        cout << "\033[0;31mInvalid CNIC! CNIC must be exactly 13 digits.\033[0m" << endl;
        return false;
    }

    for (int i = 0; i < cnic.length(); i++)
    {
        if (cnic[i] == ' ')
        {
            cout << "\033[0;31mInvalid CNIC! Spaces are not allowed.\033[0m" << endl;
            return false;
        }
        if (!(cnic[i] >= '0' && cnic[i] <= '9'))
        {
            cout << "\033[0;31mInvalid CNIC! Only digits are allowed.\033[0m" << endl;
            return false;
        }
    }
    return true;
}

// HELPER FUNCTION
void pause()
{
    cout << "Press Enter to continue....";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// PANELS
void AdminPanel(
    string foodNames[], string companyNames[],
    double foodPrices[], int foodQuantity[],
    int &foodCount,
    string username[],
    int customerOrders[][50],
    int customerOrderQty[][50],
    int customerOrderCount[],
    int userCount)

{

    while (true)
    {
        system("clear");
        cout << "========================================================================================" << endl;
        cout << "                             ADMIN PANEL                                                " << endl;
        cout << "========================================================================================" << endl;
        cout << "1. Add food item                                                                        " << endl;
        cout << "2. Update food item                                                                       " << endl;
        cout << "3. Delete food item                                                                     " << endl;
        cout << "4. Display food item                                                                 " << endl;
        cout << "5. View All order food item                                                                 " << endl;

        cout << "6. Log out                                                                              " << endl;
        cout << "Enter your choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            AddFood(foodNames, companyNames, foodPrices, foodQuantity, foodCount);
        }

        else if (choice == "2")
        {
            UpdateFood(foodNames, companyNames, foodPrices, foodQuantity, foodCount);
        }

        else if (choice == "3")
        {
            DeleteFood(foodNames, companyNames, foodPrices, foodQuantity, foodCount);
        }

        else if (choice == "4")
        {
            DisplayFood(foodNames, companyNames, foodPrices, foodQuantity, foodCount);
        }
        else if (choice == "5")
        {
            ViewAllOrders(username, foodNames, companyNames, foodPrices,
                          customerOrders, customerOrderQty, customerOrderCount, userCount);
        }
        else if (choice == "6")
        {
            cout << "Logging Out!!" << endl;
            pause();
            break;
        }
        else
        {
            cout << "Invalid Input!!" << endl;
            pause();
        }
    }
}
void AddFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int &foodCount)
{
    string foodName, companyName;
    double price;
    int quantity;

    cout << "Enter Food Name: ";
    getline(cin, foodName);
    cout << "Enter Company Name: ";
    getline(cin, companyName);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Quantity: ";
    cin >> quantity;
    cin.ignore();

    foodNames[foodCount] = foodName;
    companyNames[foodCount] = companyName;
    foodPrices[foodCount] = price;
    foodQuantity[foodCount] = quantity;
    foodCount++;

    cout << "Food added successfully!" << endl;
    pause();
}
void UpdateFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount)
{
    if (foodCount == 0)
    {
        cout << "No food available to update!" << endl;
        pause();
        return;
    }

    cout << left << setw(5) << "No."
         << setw(20) << "Food Name"
         << setw(20) << "Company"
         << setw(20) << "Price (per packet)"
         << setw(20) << "Qty" << endl;

    for (int i = 0; i < foodCount; i++)
    {
        cout << left << setw(5) << i + 1
             << setw(20) << foodNames[i]
             << setw(20) << companyNames[i]
             << setw(20) << foodPrices[i]
             << setw(20) << foodQuantity[i] << endl;
    }

    int index;
    cout << "Enter the number of food to update: ";
    cin >> index;
    cin.ignore();
    index--;

    if (index >= 0 && index < foodCount)
    {
        cout << "Enter Updated Food Name: ";
        getline(cin, foodNames[index]);

        cout << "Enter Updated Company Name: ";
        getline(cin, companyNames[index]);

        cout << "Enter Updated Price: ";
        cin >> foodPrices[index];

        cout << "Enter Updated Quantity: ";
        cin >> foodQuantity[index];
        cin.ignore();

        cout << "Food updated successfully!" << endl;
    }
    else
    {
        cout << "Invalid selection!" << endl;
    }
    pause();
}
void DeleteFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int &foodCount)
{
    if (foodCount == 0)
    {
        cout << "No food available to delete!" << endl;
        pause();
        return;
    }

    cout << left
         << setw(5) << "No"
         << setw(20) << "Food Name"
         << setw(20) << "Company"
         << setw(20) << "Price(per packet)"
         << setw(20) << "Qty" << endl;

    cout << string(65, '-') << endl;

    for (int i = 0; i < foodCount; i++)
    {
        cout << left
             << setw(5) << i + 1
             << setw(20) << foodNames[i]
             << setw(20) << companyNames[i]
             << setw(20) << foodPrices[i]
             << setw(20) << foodQuantity[i] << endl;
    }

    int index;
    cout << endl;
    cout << "Enter the number of food to delete: ";
    cin >> index;
    cin.ignore();
    index--;

    if (index >= 0 && index < foodCount)
    {
        for (int i = index; i < foodCount - 1; i++)
        {
            foodNames[i] = foodNames[i + 1];
            companyNames[i] = companyNames[i + 1];
            foodPrices[i] = foodPrices[i + 1];
            foodQuantity[i] = foodQuantity[i + 1];
        }
        foodCount--;
        cout << "Food deleted successfully!" << endl;
    }
    else
    {
        cout << "Invalid selection!" << endl;
    }

    pause();
}
void DisplayFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount)
{
    if (foodCount == 0)
    {
        cout << "No food available!" << endl;
    }
    else
    {

        cout << left
             << setw(5) << "No"
             << setw(20) << "Food Name"
             << setw(20) << "Company"
             << setw(20) << "Price(pre packet)"
             << setw(20) << "Qty" << endl;

        cout << string(65, '-') << endl;

        for (int i = 0; i < foodCount; i++)
        {
            cout << left
                 << setw(5) << i + 1
                 << setw(20) << foodNames[i]
                 << setw(20) << companyNames[i]
                 << setw(20) << foodPrices[i]
                 << setw(20) << foodQuantity[i] << endl;
        }
    }
    pause();
}
void ViewAllOrders(string username[], string foodNames[], string companyNames[],
                   double foodPrices[], int customerOrders[][50],
                   int customerOrderQty[][50], int customerOrderCount[], int userCount)
{
    bool anyOrder = false;

    for (int i = 0; i < userCount; i++)
    {
        if (customerOrderCount[i] == 0)
            continue;

        anyOrder = true;
        cout << "Orders for User: " << username[i] << endl;

        // Header
        cout << left << setw(5) << "No."
             << setw(20) << "Food Name"
             << setw(20) << "Company"
             << setw(10) << "Qty"
             << setw(10) << "Price" << endl;

        cout << string(65, '-') << endl;

        for (int j = 0; j < customerOrderCount[i]; j++)
        {
            int foodIdx = customerOrders[i][j];
            cout << left << setw(5) << j + 1
                 << setw(20) << foodNames[foodIdx]
                 << setw(20) << companyNames[foodIdx]
                 << setw(10) << customerOrderQty[i][j]
                 << setw(10) << foodPrices[foodIdx] << endl;
        }
        cout << "----------------------------" << endl;
    }

    if (!anyOrder)
    {
        cout << "No orders placed yet!" << endl;
    }

    pause();
}
void CustomerPanel(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[],
                   int foodCount, int userIndex,
                   int customerOrders[][50], int customerOrderQty[][50], int customerOrderCount[])

{

    while (true)
    {
        system("clear");
        cout << "=====================================================================================" << endl;
        cout << "                        CUSTOMER PANEL                                               " << endl;
        cout << "=====================================================================================" << endl;
        cout << "1. Display food   Menu                                                                 " << endl;
        cout << "2. Search food item                                                                 " << endl;
        cout << "3. Place Order                                                                             " << endl;
        cout << "4. View my Order                                                                             " << endl;
        cout << "5. Log out                                                                             " << endl;
        cout << "Enter your choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            DisplayMenu(foodNames, companyNames, foodPrices, foodQuantity, foodCount);
        }

        else if (choice == "2")
        {
            SearchFood(foodNames, companyNames, foodPrices, foodQuantity, foodCount);
        }

        else if (choice == "3")
        {
            PlaceOrder(foodNames, companyNames, foodPrices, foodQuantity, foodCount, customerOrders, customerOrderQty, customerOrderCount, userIndex);
        }

        else if (choice == "4")
        {
            ViewOrder(foodNames, companyNames, foodPrices, customerOrders, customerOrderQty, customerOrderCount, userIndex);
        }

        else if (choice == "5")
        {
            cout << "Logging out!!" << endl;
            pause();
            break;
        }
        else
        {
            cout << "Invalid Input !!" << endl;
            pause();
        }
    }
}

void DisplayMenu(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount)
{
    if (foodCount == 0)
    {
        cout << "No food item available!" << endl;
    }
    else
    {
        cout << left << setw(5) << "No."
             << setw(20) << "Food Name"
             << setw(20) << "Company"
             << setw(10) << "Price"
             << setw(10) << "Qty" << endl;

        for (int i = 0; i < foodCount; i++)
        {
            cout << left << setw(5) << i + 1
                 << setw(20) << foodNames[i]
                 << setw(20) << companyNames[i]
                 << setw(10) << foodPrices[i]
                 << setw(10) << foodQuantity[i] << endl;
        }
    }
    pause();
}
void SearchFood(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount)
{
    if (foodCount == 0)
    {
        cout << "No food item available to search!" << endl;
        pause();
        return;
    }

    string searchFood, searchCompany;
    bool found = false;

    cout << "Enter Food Name to search: ";
    getline(cin, searchFood);

    cout << "Enter Company Name to search: ";
    getline(cin, searchCompany);

    cout << "\nSearch Result:\n";
    cout << left << setw(5) << "No."
         << setw(20) << "Food Name"
         << setw(20) << "Company"
         << setw(20) << "Price (per packet)"
         << setw(20) << "Qty" << endl;

    for (int i = 0; i < foodCount; i++)
    {
        if (foodNames[i] == searchFood && companyNames[i] == searchCompany)
        {
            cout << left << setw(5) << i + 1
                 << setw(20) << foodNames[i]
                 << setw(20) << companyNames[i]
                 << setw(20) << foodPrices[i]
                 << setw(20) << foodQuantity[i] << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No matching food item found!" << endl;
    }

    pause();
}
void PlaceOrder(string foodNames[], string companyNames[], double foodPrices[], int foodQuantity[], int foodCount,
                int customerOrders[][50], int customerOrderQty[][50], int customerOrderCount[], int userIndex)
{
    if (foodCount == 0)
    {
        cout << "No food item available to order!" << endl;
        pause();
        return;
    }

    cout << left
         << setw(5) << "No"
         << setw(20) << "Food Name"
         << setw(20) << "Company"
         << setw(10) << "Price"
         << setw(10) << "Qty" << endl;

    cout << string(65, '-') << endl;

    for (int i = 0; i < foodCount; i++)
    {
        cout << left
             << setw(5) << i + 1
             << setw(20) << foodNames[i]
             << setw(20) << companyNames[i]
             << setw(10) << foodPrices[i]
             << setw(10) << foodQuantity[i] << endl;
    }

    cout << "\nEnter the number of food to order: ";
    int choiceOrder;
    cin >> choiceOrder;
    cin.ignore();

    if (choiceOrder >= 1 && choiceOrder <= foodCount)
    {
        int idx = choiceOrder - 1;

        cout << "Enter quantity to order: ";
        int qty;
        cin >> qty;
        cin.ignore();

        if (qty > 0 && qty <= foodQuantity[idx])
        {
            foodQuantity[idx] -= qty;
            customerOrders[userIndex][customerOrderCount[userIndex]] = idx;
            customerOrderQty[userIndex][customerOrderCount[userIndex]] = qty;
            customerOrderCount[userIndex]++;

            cout << "\nOrder Placed Successfully!\n";
            cout << left
                 << setw(15) << "Food:"
                 << foodNames[idx] << endl
                 << setw(15) << "Company:"
                 << companyNames[idx] << endl
                 << setw(15) << "Quantity:"
                 << qty << endl;
        }
        else
        {
            cout << "Only " << foodQuantity[idx]
                 << " available. Cannot place order for " << qty << endl;
        }
    }
    else
    {
        cout << "Invalid selection!" << endl;
    }

    pause();
}

void ViewOrder(string foodNames[], string companyNames[], double foodPrices[],
               int customerOrders[][50], int customerOrderQty[][50], int customerOrderCount[], int userIndex)

{
    if (customerOrderCount[userIndex] == 0)
    {
        cout << "No orders placed yet!" << endl;
    }
    else
    {
        cout << "Your Orders:" << endl;
        cout << left << setw(5) << "No."
             << setw(20) << "Food Name"
             << setw(20) << "Company"
             << setw(10) << "Price"
             << setw(10) << "Qty" << endl;

        for (int i = 0; i < customerOrderCount[userIndex]; i++)
        {
            int idx = customerOrders[userIndex][i];

            cout << left << setw(5) << i + 1
                 << setw(20) << foodNames[idx]
                 << setw(20) << companyNames[idx]
                 << setw(10) << foodPrices[idx]
                 << setw(10) << customerOrderQty[userIndex][i] << endl;
        }
    }
    pause();
}