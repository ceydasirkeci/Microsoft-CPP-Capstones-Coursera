#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>

using namespace std;

// Validates the input and returns int
int getValidInt(const string& prompt) {
    string input;
    int number;
    while (true){
        cout << prompt;
        getline(cin, input);
        
        // Input cannot be empty
        if (input.empty()) {
            cout << "Invalid input! Please enter an integer." << endl;
            continue;
        }

        bool isValid = true;
        int startIndex;

        // First index can be - for negative numbers
        if (input[0] == '-') {
            startIndex = 1;
        }
        else {
            startIndex = 0;
        }

        // If only - is entered, it is invalid
        if (input.length() == startIndex){
            isValid = false;
        }

        // Checks if all the characters in the input are digits
        for (int i = startIndex; i < input.length(); i++){
            if(!isdigit(input[i])){
                isValid = false;
                break;
            }
        }
        // If they do not have 
        if (!isValid){
            cout << "Invalid input! Please enter an integer." << endl;
        }
        else {
            // Turns the input(string) to integer
            number = stoi(input);
            return number;
        }
    }
}

// Validates the input and returns double
double getValidDouble(const string& prompt) {
    double number;
    while (true) {
        cout << prompt;
 
        if (!(cin >> number)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a double." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return number;
        }
    }
}

// Validates the input and returns string
string getValidString(const string& prompt){
    string input;
    while (true){
        cout << prompt;
        getline(cin, input);
        bool hasNumber = false;
        // Checks if the input has number in it
        for (int i = 0; i < input.length(); i++){
            if (isdigit(input[i])){
                hasNumber = true;
                break;
            }
        }

        // Input cannot be empty
        if (input.empty()){
            cout << "Input cannot be empty. Please try again." << endl;
        }
        // If input contains number, it is invalid
        else if (hasNumber){
            cout << "Invalid input. Please enter a string. " << endl;
        }
        else {
            return input;
        }
    }
}

//Displays menu options
void displayMenu(){
    cout << "\n==== UTILITY PROGRAM MENU ====" << endl;
    cout << "1. Basic calculator (addition, subtraction, multiplication and division)" << endl;
    cout << "2. Palindrome checker" << endl;
    cout << "3. Prime number checker" << endl;
    cout << "4. Random password generator" << endl;
    cout << "5. Exit" << endl;
}

// Performs addition operation
double addition(double firstNumber, double secondNumber){
    return firstNumber + secondNumber;
}

// Performs subtraction operation
double subtraction(double firstNumber, double secondNumber){
    return firstNumber - secondNumber;
}

// Performs multiplication operation
double multiplication(double firstNumber, double secondNumber){
    return firstNumber * secondNumber;
}

//Performs division operation
double division(double firstNumber, double secondNumber){
    return firstNumber / secondNumber;
}

//Reverses the given string to later check if it is a palindrome 
string reverseString(string input) {
    string reversed = "";
    for (int i = input.length()-1; i >= 0; i--){
        reversed += input[i];
    }
    return reversed;
}

//Checks if the number is prime 
bool isPrime (int number){
    if (number <=1){
        return false;
    }
    if (number == 2){
        return true;
    }
    if (number % 2 == 0){
        return false;
    }
    for (int i = 3; i * i <= number; i+= 2){
        if (number % i == 0){
            return false;
        }
    }
    return true;
}

//Generates random numbers of 3 or 4 digits
int generateRandomPassword(int digit){
    int result;
    if (digit == 3){
        // Generates numbers between 100 and 999
        result = (rand()% 900) + 100;
    }
    else if (digit == 4){
        // Generates numbers between 1000 and 9999
        result = (rand() % 9000) + 1000;
    }
    return result;
}

// Main function for utility program
int main(){

    // Enables generating different passwords in each run of the program
    srand(static_cast<unsigned int>(time(0)));

    int choice;
    bool running = true;   
    // Continues until exit option is chosen
    while (running) {
        displayMenu();
        choice = getValidInt("Enter your choice (1-5): ");
        switch (choice)
        {
        case 1:{   
            int operation;
            cout << "\n==== BASIC CALCULATOR ====" << endl;
            cout << "This utility performs operations that are listed below." << endl;
            cout << "\nWhich calculation do you want to perform?" << endl;
            cout << "1. Addition" << endl;
            cout << "2. Subtraction" << endl;
            cout << "3. Multiplication" << endl;
            cout << "4. Division" << endl;
            operation = getValidInt("Enter your choice (1-4): ");

            if (operation < 1 || operation > 4){
                cout << "Enter a valid option between 1-4" << endl;
                break;
            }

            double firstNumber = getValidDouble("Enter the first number: ");
            double secondNumber = getValidDouble("Enter the second number: ");
            double result;
            if (operation == 1){
                result = addition(firstNumber, secondNumber);
                cout << "The answer is: " << result << endl;
            }
            else if (operation == 2){
                result = subtraction(firstNumber, secondNumber);
                cout << "The answer is: " << result << endl;
            }
            else if (operation == 3){
                result = multiplication(firstNumber, secondNumber);
                cout << "The answer is: " << result << endl;
            }
            else if (operation == 4){
                if (secondNumber == 0){
                    cout << "Divisor cannot be 0. Please try again." << endl;  // Provides an error message for division by zero
                }
                else {
                    result = division(firstNumber, secondNumber);
                    cout << "The answer is: " << result << endl;
                }
            }
            break;
        }
        
        case 2:{ 
            string input;
            cout << "\n==== PALINDROME CHECKER ====" << endl;
            cout << "This utility checks whether the given string is palindrome or not." << endl;
            input = getValidString("\nEnter a string to check if it is a palindrome: ");
            
            string processedInput = "";

            // Skips the spaces and turns each character to lower case
            for (int i = 0; i < input.length(); i++){
                if (input[i] != ' ') {
                    processedInput += tolower(input[i]);
                }
            }
            
            string reversed = reverseString(processedInput);
            if (reversed == processedInput){
                cout << input << " is a palindrome." << endl;
            }
            else {
                cout << input << " is not a palindrome." << endl;
            }
            break;
        }  
        case 3:{
            int number;
            cout << "\n==== PRIME NUMBER CHECKER ====" << endl;
            cout << "This utility checks whether the given number is prime number or not. " << endl;
            number = static_cast<int>(getValidInt("\nEnter a positive number to check if it is a prime number or not: "));
            if (number <= 0){
                cout << "Please enter a positive number to check" << endl;
            }
            else {
                if (isPrime(number)){
                    cout << number << " is prime number." << endl;
                }
                else {
                    cout << number << " is not a prime number. " << endl;
                }
            }
            break;
        }
        case 4:{
            int digit;
            cout << "\n==== RANDOM PASSWORD GENERATOR ====" << endl;
            cout << "This utility generates a random password of 3 or 4 digits." << endl;
            digit = static_cast<int>(getValidInt("\nHow many digits do you want your password to have? Please select 3 or 4: "));
            if (digit != 3 && digit != 4){
                cout << "Invalid number of digits. Please select 3 or 4." << endl;
            }
            else {
                int password = generateRandomPassword(digit);
                cout << "Password is: " << password << endl;
            }
            break;
        }
        case 5:
            cout << "\nThank you for using utility program. " << endl;
            running = false;
            break;
        default:
            cout << "Please enter a valid menu option between 1-5" << endl;
            break;
        }
    } 
    return 0;
}
