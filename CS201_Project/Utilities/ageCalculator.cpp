#include <iostream>
#include <string>
#include <regex>
#include <chrono>
#include <ctime> 

using namespace std;

int ageCalculator(string input) {
    regex datePattern(R"((\d{2})/(\d{2})/(\d{4}))");
    smatch matches;

    if (regex_search(input, matches, datePattern)) {
        int day = stoi(matches[1].str());
        int month = stoi(matches[2].str());
        int year = stoi(matches[3].str());

        // Validate the date
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            cout << "Invalid date." << endl;
            return -1; // Error code for invalid date
        }

        // Check for valid days in month
        if ((month == 2 && day > 29) || (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11))) {
            cout << "Invalid date." << endl;
            return -1; // Error code for invalid date
        }

        tm givenDate = {};
        givenDate.tm_year = year - 1900;
        givenDate.tm_mon = month - 1;
        givenDate.tm_mday = day;

        time_t givenTime = mktime(&givenDate);
        time_t currentTime = time(nullptr);
        
        // Calculate the difference in years
        double secondsDiff = difftime(currentTime, givenTime);
        int yearsDiff = secondsDiff / (365.25 * 24 * 3600);

        // Adjust for whether the birthday has occurred this year
        givenDate.tm_year += yearsDiff; // Adjust to current year
        if (mktime(&givenDate) > currentTime) {
            yearsDiff--; // If birthday hasn't occurred yet this year
        }
        return yearsDiff;

    } else {
        cout << "No valid date found in the given format." << endl;
    }
    return -1;
}



