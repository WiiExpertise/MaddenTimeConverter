#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

int main()
{
    cout << "This program will convert a list of times formatted like \"1:00 PM\" in a text file named \"times.txt\" to Madden time of day values such as \"780\" in a new text file called \"times_formatted.txt\". Please ensure you have a properly formatted times.txt file in the same folder as this program, and then press enter to continue.";
    cin.get();
    cout << endl;
    
    ifstream fin("times.txt");
    ofstream fout("times_formatted.txt");

    if (!fin.is_open())
    {
        cout << "Error opening input file! Press enter to exit.";
        cin.get();

        if (fout.is_open())
        {
            fout.close();
        }
        return 1;
    }

    if (!fout.is_open())
    {
        cout << "Error opening output file! Press enter to exit.";
        cin.get();

        if (fin.is_open())
        {
            fin.close();
        }
        return 1;
    }
    
    string rawTime;

    while (getline(fin, rawTime))
    {
        tm parsedTime = {};

        istringstream ss(rawTime);

        int hours, minutes;
        char ampm;

        ss >> hours;
        ss.ignore(); // Ignore the colon
        ss >> minutes >> ampm;

        if (ampm == 'P' || ampm == 'p') {
            hours += 12;
        }

        parsedTime.tm_hour = hours;
        parsedTime.tm_min = minutes;

        int militaryHours = parsedTime.tm_hour;
        int militaryMinutes = parsedTime.tm_min;

        int finalTimeValue = (60 * militaryHours) + militaryMinutes;
        fout << finalTimeValue << endl;
    }
    
    cout << "Conversion successful! Press enter to exit.";
    cin.get();

	return 0;
}