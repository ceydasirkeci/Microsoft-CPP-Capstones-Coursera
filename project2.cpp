#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "json.hpp"

using json = nlohmann::json;

// Variables that will hold user data
struct User {
    std::string userName;
    int age;
    bool isStudent;
    std::array <std::string, 2> talents;
};

// Parse user data from JSON file
std::array<User, 3> parseJsonData(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()){
        throw std::runtime_error("Could not open JSON file.");
    }
    json data;
    inputFile >> data;

    // Array for 3 users
    std::array<User, 3> userList;

    for (size_t i = 0; i < 3 && i < data.size(); ++i){
        userList[i].userName = data[i]["user_name"];
        userList[i].age = data[i].value("age", 0);   //AI-Assisted Optimization: .value() is used to handle missing JSON fields gracefully.
        userList[i].isStudent = data[i]["is_student"];
        userList[i].talents = data[i]["talents"].get<std::array<std::string, 2>>();  //Gets two talents from the talent section
    }

    return userList;
}

//Shows users who are students
void showStudents(const std::array<User, 3>& userList, std::ofstream& outputFile) {
    if (!outputFile.is_open()){
        throw std::runtime_error("Could not open output file.");
    }

    outputFile << "\n--- Users that are students ---" << std::endl;

    bool studentFound = false;

    // If student is found among the user list, it prints out the username of the student. 
    for (const auto& user : userList) {
        if (user.isStudent == true){
            outputFile << "- " << user.userName << std::endl;
            studentFound = true;
        }
    }
    if (!studentFound) {
        outputFile << "There are no students among users." << std::endl;
    }
}

// Shows users who has the same talent together
void showUsersTogetherWithSameTalent(const std::array<User, 3>& userList, std::ofstream& outputFile){
    if (!outputFile.is_open()){
        throw std::runtime_error("Could not open output file.");
    }

    outputFile << "\n--- Users Who Know C++ ---" << std::endl;

    bool knowCpp = false;

    // It scans the user list, and prints out the users who knows C++
    for (const auto& user : userList){
        for (size_t i = 0; i < 2; ++i){
            if (user.talents[i] == "C++"){
                outputFile << "- " << user.userName << std::endl;
                knowCpp = true;
            }
        }
    }
    if (!knowCpp){
        outputFile << "There are no users who know C++." << std::endl;
    }

    outputFile << "\n--- Users Who Know Java ---" << std::endl;
    bool knowJava = false;

    // It scans the user list, and prints out the users who knows Java
    for (const auto& user : userList){
        for (size_t i = 0; i < 2; ++i){
            if (user.talents[i] == "Java"){
                outputFile << "- " << user.userName << std::endl;
                knowJava = true;
            }
        }
    }
    if (!knowJava){
        outputFile << "There are no users who know Java." << std::endl;
    }

    outputFile << "\n--- Users Who Know Python ---" << std::endl;    
    bool knowPython = false;

    // It scans the user list, and prints out the users who knows Python
    for (const auto& user : userList){
        for (size_t i = 0; i < 2; ++i){
            if (user.talents[i] == "Python"){
                outputFile << "- " << user.userName << std::endl;
                knowPython = true;
            }
        }
    }
    if (!knowPython){
        outputFile << "There are no users who know Python." << std::endl;
    }
}

int main() {
    // Creating output file
    std::ofstream outputFile("report.txt");
    if (!outputFile){
        std::cerr << "Error creating report file." << std::endl;
        return 1;
    }

    try {
        outputFile << "---User Data Processing Report---" << std::endl;
        std::array<User, 3> userList = parseJsonData("user_data.json");

        for (const auto& user : userList){
            outputFile << "User: " << user.userName << std::endl;
            if (user.age <= 0) {
                outputFile << "User age is not valid." << std::endl;
            }
            else {
                outputFile << "Age: " << user.age << std::endl;
            }
            outputFile << "Talents: ";
            for(size_t i = 0; i < 2; ++i){
                outputFile << user.talents[i];

                // Adds commas after each talent except the last one
                if (i < user.talents.size() - 1){
                    outputFile << ", ";
                }
            }
            outputFile << std::endl << std::endl;
        }

        showStudents(userList, outputFile);

        showUsersTogetherWithSameTalent(userList, outputFile);

        outputFile.close();

        std::cout << "Data Processing Report is created successfully." << std::endl;

    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}


