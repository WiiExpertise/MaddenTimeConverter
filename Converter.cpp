#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

int main()
{
    // Print program header
    cout << "This program will convert a list of times formatted like \"1:00 PM\" in a text file named \"times.txt\" to Madden time of day values such as \"780\" in a new text file called \"times_formatted.txt\". Please ensure you have a properly formatted times.txt file in the same folder as this program, and then press enter to continue.";
    cin.get();
    cout << endl;
    
    // Open input and output files
    ifstream fin("times.txt");
    ofstream fout("times_formatted.txt");

    // Verify input and output files are open, otherwise print error and exit.
    if (!fin.is_open())
    {
        cout << "Error opening input file! Press enter to exit.";
        cin.get();

        return 1;
    }
    if (!fout.is_open())
    {
        cout << "Error opening output file! Press enter to exit.";
        cin.get();

        return 1;
    }
    
    string rawTime;

    // Read all lines in input file
    while (getline(fin, rawTime))
    {
        tm parsedTime = {};

        istringstream ss(rawTime);

        int hours, minutes;
        char ampm;

        // Parse time to hours, minutes, and AM/PM
        ss >> hours;
        ss.ignore(); // Ignore the colon
        ss >> minutes >> ampm;

        // Convert hours from 12-hour to 24-hour format
        if (ampm == 'P' || ampm == 'p') {
            hours += 12;
        }

        parsedTime.tm_hour = hours;
        parsedTime.tm_min = minutes;

        int militaryHours = parsedTime.tm_hour;
        int militaryMinutes = parsedTime.tm_min;

        // Convert time to number of seconds since midnight and print to file
        int finalTimeValue = (60 * militaryHours) + militaryMinutes;
        fout << finalTimeValue << endl;
    }
    
    // Print success prompt and exit
    cout << "Conversion successful! Press enter to exit.";
    cin.get();

	return 0;
}