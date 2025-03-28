#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


// prototypes
void welcome();
void help();
string getAirport();
void getData(string file);
void showInfo();
void logText(string message);
void saveResults();


// file paths
const string AVALONFILE = "./Project 3 - Data Files/Avalon Airport Temperature Data-2022.csv";
const string BENDIGOFILE = "./Project 3 - Data Files/Bendigo Airport Temperature Data-2022.csv";


// structure to store row data
struct rowData {
    string productCode, stationNumber;
    int year, month, day, accumulatedDays;
    float maxTemp;
    char quality;
};


// create counter for to find mode
struct counter {
    float value;
    int count = 0;
};

// create vector of counters
vector<counter> counterTable; 

// create vector of rows
vector<rowData> rows;


int main() {
    // Display welcome message
    welcome();

    char choice = 'c';
    do {
        // Display how to use program
        help();

        // Get input from user for airport data
        string airport = getAirport();
        if (airport == "Avalon") {
            std::cout << "The data for Avalon Airport is as follows: \n";
            logText("The data for Avalon Airport is as follows: \n");
            getData(AVALONFILE);
            showInfo();
            saveResults();
        }
        else if (airport == "Bendigo") {
            std::cout << "The data for Bendigo Airport is as follows: \n";
            logText("The data for Bendigo Airport is as follows: \n");
            getData(BENDIGOFILE);
            showInfo();
            saveResults();
        }
        else if (airport == "Both") {
            std::cout << "The data for Avalon Airport is as follows: \n";
            logText("The data for Avalon Airport is as follows: \n");
            getData(AVALONFILE);
            showInfo();
            saveResults();

            // empty vector
            rows.clear();

            std::cout << "\nThe data for Bendigo Airport is as follows: \n";
            logText("\nThe data for Bendigo Airport is as follows: \n");
            getData(BENDIGOFILE);
            showInfo();
            saveResults();
        }
        else {
            std::cout << "Please refer to the help section to see how to use the program.\n";
        }

        // empty vector
        rows.clear();

        std::cout << "Enter 'e' to exit or 'c' to continue using the program.\n";
        cin >> choice;

    } while (choice == 'c');
    
    std::cout << "\nThank you for using this program!";
}


void welcome() {
    string msg = "Turing Moore Engineering Temperature Data Analyser 1.0\n";
    msg += "Name: \n";
    msg += "Student ID: \n";
    msg += "Due: 24/09/2023\n";
    msg += "Desired Level: Pass";
    std::cout << msg;
    logText(msg);
}


void help() {
    string msg = "\n\nHow to Use:\n";
    msg += "This software will display temperature data for Avalon Airport, Bendigo Airport or Both.\n";
    msg += "You will be prompted to enter the Airport for which the data you would like to see.\n";
    msg += "Enter 'Avalon' for Avalon Airport Data, enter 'Bendigo' for Bendigo Airport Data ";
    msg += "or enter 'Both' to view data for both Airports.\n\n";
    
    std::cout << msg;
    logText(msg);
}


string getAirport() {
    string data;
    string msg = "Select Airport to view data: 'Avalon', 'Bendigo' or 'Both': ";
    std::cout << msg;
    cin >> data;
    msg += data;
    logText(msg);
    return data;
}


int getNumLines(string file) {
    fstream infile;
    infile.open(file, ios::in);
    string line;

    // get number of lines
    int numLines = 0;
    
    // while line not blank increase variable
    while (getline(infile, line)) {
        numLines++;
    }
    string msg = "Number of rows: " + to_string(numLines) + "\n";
    std::cout << msg;
    logText(msg);
    infile.close();
    return numLines;
}


void getMean() {
    float sum = 0;
    for (int i = 0; i < rows.size(); i++) {
        sum += rows[i].maxTemp;
    }

    float avg = sum / rows.size();
    string msg = "The average temperature for the year is " + to_string(avg) + " Degrees Celsius\n";
    logText(msg);
    std::cout << msg;
}


void getColdestDay() {
    float coldest = 10000000;
    int day, month, year;
    for (int i = 0; i < rows.size(); i++) {
        if (rows[i].maxTemp < coldest) {
            // store temp and date of lowest temp
            coldest = rows[i].maxTemp;
            day = rows[i].day;
            month = rows[i].month;
            year = rows[i].year;
        }
    }

    string msg = "Temperature of coldest day is " + to_string(coldest) + " Degrees Celsius on ";
    msg += to_string(day) + '/' + to_string(month) + '/' + to_string(year) + "\n";
    logText(msg);
    std::cout << msg;
}


void getHottestDay() {
    float hottest = -10000000;
    int day, month, year;
    for (int i = 0; i < rows.size(); i++) {
        if (rows[i].maxTemp > hottest) {
            // store temp and date of highest temp
            hottest = rows[i].maxTemp;
            day = rows[i].day;
            month = rows[i].month;
            year = rows[i].year;
        }
    }

    string msg = "Temperature of hottest day is " + to_string(hottest) + " Degrees Celsius on ";
    msg += to_string(day) + '/' + to_string(month) + '/' + to_string(year) + "\n";
    logText(msg);
    std::cout << msg;
}


void getMedian() {
    int temperatures[365];
    for (int i = 0; i < rows.size(); i++) {
        temperatures[i] = rows[i].maxTemp;
    }

    // sort array
    bool swapped;
    for (int i = 0; i < 365; i++) {
        swapped = false;
        for (int j = 0; j < 364; j++) {
            if (temperatures[j] > temperatures[j + 1]) {
                swapped = true;
                int temp = temperatures[j];
                temperatures[j] = temperatures[j + 1];
                temperatures[j + 1] = temp;
            }
        }
 
        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }

    // get median
    int medianTemp;
    int length = rows.size();
    if (length % 2 == 1) { 
        int medianIndex = rows.size() / 2;
        medianTemp = temperatures[medianIndex];
    }
    else {
        int i1, i2;
        i1 = rows.size() / 2;
        i2 = i1 - 1;
        medianTemp = (temperatures[i1] + temperatures[i2]) / 2.0; 
    }
    
    string msg = "The median temperature for the year is " + to_string(medianTemp) + " Degrees Celsius\n";
    logText(msg);
    std::cout << msg;
}


void getData(string file) {
    const int numRows = getNumLines(file);

    fstream infile;
    infile.open(file, ios::in);
    string line;

    // set cursor to second line
    getline(infile, line);
    
    //count colums
    int columns = 1;
    for (char c: line) {
        if (c == ',') columns++;
    }
    string msg = "Number of columns: " + to_string(columns) + "\n";
    std::cout << msg;
    logText(msg);

    // start from second line
    // store data in vector
    for (int i = 1; i < numRows; i++) {
        rowData row;
        string year, month, day, maxTemp, accumulatedDays, quality;
        getline(infile, row.productCode, ',');
        getline(infile, row.stationNumber, ',');
        getline(infile, year, ',');
        getline(infile, month, ',');
        getline(infile, day, ',');
        getline(infile, maxTemp, ',');
        getline(infile, accumulatedDays, ',');
        getline(infile, quality);

        // Convert to proper type from string and store in struct
        row.year = stoi(year);
        row.day = stoi(day);
        row.month = stoi(month);
        row.maxTemp = stof(maxTemp);
        row.accumulatedDays = stoi(accumulatedDays);
        row.quality = quality[0];

        // add row to vector
        rows.push_back(row);
    }

    infile.close();
}

void logText(string message) {
    ofstream outfile;
    // open file in append mode
    outfile.open("log.txt", ios::app);

    // append message to file
    if (outfile) {
        outfile << message;
    }

    outfile.close();
}

// credit
void getMode() {
    float temp;

    // add the first value in counter table
        
    counter c;
    c.value = temp;
    c.count = 0;
    counterTable.push_back(c);
        
    
    // go through row vector
    for (int i = 0; i < rows.size(); i++) {
        temp = rows[i].maxTemp;
        bool found = false;

        // for each temperature in dataset check in counter table
        for (int j = 0; j < counterTable.size(); j++){
            //if found the increase the count
            if (temp == counterTable[j].value) {
                counterTable[j].count++;
                found = true;
                break;
            }
        }
        // otherwise create new instance and set count to one and add to vector
        if (!found) {
            counter c;
            c.value = temp;
            c.count = 1;
            counterTable.push_back(c);
        }
    }


    int maxCount = 0;
    int maxTemp;
    // look through countertable
    for (int i = 0; i < counterTable.size(); i++) {
        // update max temperature every time new count is found
        if (counterTable[i].value > maxCount) {
            maxCount = counterTable[i].count;
            maxTemp = counterTable[i].value;
        }
    }

    string msg = "The modal temperature for the year is " + to_string(maxTemp) + " Degrees Celsius\n";
    std::cout << msg;
    logText(msg);
}


string getMonth(int month) {
    switch (month) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";
    }
}


void getColdestMonth() {
    int coldestMonth;
    float coldestAvgTemp = 10000000;
    for (int i = 1; i < 13; i++) {
        // reset the sum and days for each month
        float sum = 0;
        float days = 0;
        for (int j = 0; j < rows.size(); j++) {

            // if the data is for the specific month
            if (rows[j].month == i) {
                // get total temp and increase the days
                sum += rows[j].maxTemp;
                days++;
            }
        }

        float avgTemp = sum / days;
        // record coldest temperature and the month
        if (avgTemp < coldestAvgTemp) {
            coldestAvgTemp = avgTemp;
            coldestMonth = i;
        }
    }
    string month = getMonth(coldestMonth);
    string msg = "The coldest month is " + month + " with average temperature of " + to_string(coldestAvgTemp);
    msg += " Degrees Celsius\n";
    std::cout << msg;
    logText(msg);
}


void getHottestMonth() {
    int hottestMonth;
    float hottestAvgTemp = -10000000;
    for (int i = 1; i < 13; i++) {
        // reset the sum and days for each month
        float sum = 0;
        float days = 0;
        for (int j = 0; j < rows.size(); j++) {

            // if the data is for the specific month
            if (rows[j].month == i) {
                // get total temp and increase the days
                sum += rows[j].maxTemp;
                days++;
            }
        }

        float avgTemp = sum / days;
        // record hottest temperature and the month
        if (avgTemp > hottestAvgTemp) {
            hottestAvgTemp = avgTemp;
            hottestMonth = i;
        }
    }
    string month = getMonth(hottestMonth);
    string msg = "The hottest month is " + month + " with average temperature of " + to_string(hottestAvgTemp);
    msg += " Degrees Celsius\n";
    std::cout << msg;
    logText(msg);
}

void getConsistentMonth() {
    int consistentMonth;
    float lowestVariance = 1000000, avgTemp = 0;
    for (int i = 1; i < 13; i++) {
        // reset the sum and days for each month
        float sum = 0, days = 0;
        vector<float> temps;
        for (int j = 0; j < rows.size(); j++) {
            // if the data is for the specific month
            if (rows[j].month == i) {
                // get total temp and increase the days for avg
                sum += rows[j].maxTemp;
                days++;

                // add to array
                temps.push_back(rows[j].maxTemp);
            }
        }

        //calculate average
        float avg = sum / days;

        //calculate variance
        float variance = 0, x;
        for (int k = 0; k < temps.size(); k++) {
            x = avgTemp - temps[k];
            variance += x * x;
        }
        // record hottest temperature and the month
        if (variance < lowestVariance) {
            lowestVariance = variance;
            consistentMonth = i;
            avgTemp = avg;
        }
        temps.clear();
    }
    string month = getMonth(consistentMonth);
    string msg = "The most consistent month is " + month + " with average temperature of " + to_string(avgTemp);
    msg += " Degrees Celsius and a variance of " + to_string(lowestVariance) + "\n";
    std::cout << msg;
    logText(msg);
}


void saveResults() {
    const string resultsDIR = "./Results/results.csv";
    string line;
    fstream outfile;

    outfile.open(resultsDIR, ios::app);
    outfile << "Year,Month,Hottest Temperature,Coldest  Temperature,Average Temperature,Median Temperature\n";
    outfile.close();
    
    for (int i = 1; i < 13; i++) {
        // reset the sum and days for each month
        float sum = 0, days = 0;
        vector<float> temps;
        for (int j = 0; j < rows.size(); j++) {
            // if the data is for the specific month
            if (rows[j].month == i) {
                // get total temp and increase the days for avg
                sum += rows[j].maxTemp;
                days++;

                // add to array
                temps.push_back(rows[j].maxTemp);
            }
        }

        //calculate average
        float avgTemp = sum / days;


        // sort
        bool swapped;
        int length = temps.size(); 
        for (int i = 0; i < length; i++) {
            swapped = false;
            for (int j = 0; j < length - 1; j++) {
                if (temps[j] > temps[j + 1]) {
                    swapped = true;
                    int x = temps[j];
                    temps[j] = temps[j + 1];
                    temps[j + 1] = x;
                }
            }
            // If no two elements were swapped
            // by inner loop, then break
            if (swapped == false)
                break;
        }

        // max will be last element of array
        float maxTemp = temps[length - 1];
        // min will be first element
        float minTemp = temps[0];
        int medianTemp;
        // median for odd length is middle numbers
        if (length % 2 == 1) { 
            int medianIndex = rows.size() / 2;
            medianTemp = temps[medianIndex];
        }
        // median for even length is average of 2 middle numbers
        else {
            int i1, i2;
            i1 = rows.size() / 2;
            i2 = i1 - 1;
            medianTemp = (temps[i1] + temps[i2]) / 2.0; 
        }

        //string of data
        string line = "2022," + to_string(i) + "," + to_string(maxTemp) + "," + to_string(minTemp) + ",";
        line += to_string(avgTemp) + "," + to_string(medianTemp) + "\n";

        // append to file
        outfile.open(resultsDIR, ios::app);
        if (outfile) outfile << line;
        outfile.close();        
    }  
    
}

void showInfo() {
    getHottestDay();
    getColdestDay();
    getMean();
    getMedian();
    getMode();
    getColdestMonth();
    getHottestMonth();
    getConsistentMonth();
}