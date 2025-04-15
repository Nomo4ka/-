#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

class Temperature {
private:
    int day, month, year;
    double TempC, TempF;
    string Temperature_type;

public:
    Temperature():  day(0),month(0),year(0) , TempC(0.0) , TempF(0.0),Temperature_type("C") {}
    Temperature(int d, int m, int y, string TempT, double ValueOfTempC, double ValueOfTempF): day(d), month(m), year(y), TempC(ValueOfTempC), TempF(ValueOfTempF), Temperature_type(TempT) {}
    /*Temperature(int d, int m, int y, string TempT, double ValueOfTempC, double ValueOfTempF) {
        day = d;
        month = m;
        year = y;
        Temperature_type = TempT;
        TempC = ValueOfTempC;
        TempF = ValueOfTempF;
    }*/
    
    int getDay() const { return day;}
    int getMonth() const { return month;}
    int getYear() const { return year; }
    double getTempC() const { return TempC; }
    double getTempF() const { return TempF; }
    string getTemperature_type() const { return Temperature_type; }

    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
    void setTempC(double TC) { TempC = TC; }
    void setTempC(double TF) { TempF = TF; }
    void Temperature_type(string TempType) { Temperature_type = TempType;}

    ~Temperature() {}

    /*void Print() {
        cout << "Date: " << setw(2) << setfill('0') << day << "." << setw(2) << setfill('0') << month << "." << year << "\t Temperature: "
            << fixed << setprecision(2) << (Temperature_type == "C" ? TempC : TempF) << " " << Temperature_type << endl << endl;
    }*/

    void TempTransver() {
        if (Temperature_type == "C") {
            TempF = (9.0 / 5.0) * TempC + 32;
            cout << "Converted to Fahrenheit: " << fixed << setprecision(2) << TempF << " F" << endl;
        }
        else if (Temperature_type == "F") {
            TempC = (TempF - 32.0) * (5.0 / 9.0);
            cout << "Converted to Celsius: " << fixed << setprecision(2) << TempC << " C" << endl;
        }
    }
};

bool isValidDate(int day, int month, int year) {
    if (year < 0) return false;
    if (month < 1 || month > 12) return false;

    if (month == 2) {
        bool isLeap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day < 1 || day > (isLeap_year ? 29 : 28)) return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day < 1 || day > 30) return false;
    }
    else if (day < 1 || day > 31) {
        return false;
    }

    return true;
}

bool isBelowAbsoluteZero(double value, const string& type) {
    if (type == "C" && value <= -273.15) {
        return true;
    }
    if (type == "F" && value <= -459.67) {
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Temperature& temp) {
    os << "Date: " << setw(2) << setfill('0') << temp.getDay() << "." << setw(2) << setfill('0') << temp.getMonth() << "." << temp.getYear() << "\t Temperature: "
        << fixed << setprecision(2) << (temp.getTemperature_type() == "C" ? temp.getTempC() : temp.getTempF()) << " " << temp.getTemperature_type() << endl << endl;
    return os;
}

istream& operator>>(istream& is, Temperature& temp) {
    string dateInput;
    int day, month, year;
    string TempT;
    double ValueOfTemp;

    cin >> dateInput;

    size_t dot1 = dateInput.find('.');
    size_t dot2 = dateInput.find('.', dot1 + 1);

    if (dot1 == string::npos && dot2 == string::npos) {
        throw("Invalid date format! Use DD.MM.YYYY.");
    }

    try {
        day = stoi(dateInput.substr(0, dot1));
        month = stoi(dateInput.substr(dot1 + 1, dot2 - dot1 - 1));
        year = stoi(dateInput.substr(dot2 + 1));
        temp.setDay(day);
        temp.setMonth(month);
        temp.setYear(year);
    }
    catch (const invalid_argument) {
        throw ("Invalid date format! Use numbers for day, month, and year.");
        return 1;
    }
    catch (const out_of_range) {
        cerr << "Invalid date format! Date is out of range." << endl;
        return 1;
    }

    if (!isValidDate(day, month, year)) {
        cerr << "Invalid date entered!" << endl;
        return 1;
    }


    cout << "Enter temperature value and type: ";
    cin >> ValueOfTemp >> TempT;

    if (TempT != "C" && TempT != "F") {
        cerr << "Invalid temperature type! Use 'C' for Celsius or 'F' for Fahrenheit." << endl;
        return 1;
    }

    if (isBelowAbsoluteZero(ValueOfTemp, TempT)) {
        cerr << "Error: Temperature cannot be below or qual absolute zero!" << endl;
        return 1;
    }
}

//int inputfromconsole() {
//    int n;
//    vector<Temperature> temperatures;
//
//    cout << "Enter numbers of dates: ";
//    cin >> n;
//    if (n < 1) {
//        cerr << "Invalid input! Please enter a positive integer." << endl;
//        return 1;
//    }
//
//
//
//    for (int i = 0; i < n; i++) {
//        string dateInput;
//        int day, month, year;
//        string TempT;
//        double ValueOfTemp;
//
//        cout << "Entry " << i + 1 << " - Enter date (format DD.MM.YYYY): ";
//        cin >> dateInput;
//
//        size_t dot1 = dateInput.find('.');
//        size_t dot2 = dateInput.find('.', dot1 + 1);
//
//        if (dot1 == string::npos && dot2 == string::npos) {
//            cerr << "Invalid date format! Use DD.MM.YYYY." << endl;
//            return 1;
//        }
//
//        try {
//            day = stoi(dateInput.substr(0, dot1));
//            month = stoi(dateInput.substr(dot1 + 1, dot2 - dot1 - 1));
//            year = stoi(dateInput.substr(dot2 + 1));
//        }
//        catch (const invalid_argument) {
//            cerr << "Invalid date format! Use numbers for day, month, and year." << endl;
//            return 1;
//        }
//        catch (const out_of_range) {
//            cerr << "Invalid date format! Date is out of range." << endl;
//            return 1;
//        }
//
//        if (!isValidDate(day, month, year)) {
//            cerr << "Invalid date entered!" << endl;
//            return 1;
//        }
//
//
//        cout << "Enter temperature value and type: ";
//        cin >> ValueOfTemp >> TempT;
//
//        if (TempT != "C" && TempT != "F") {
//            cerr << "Invalid temperature type! Use 'C' for Celsius or 'F' for Fahrenheit." << endl;
//            return 1;
//        }
//
//        if (isBelowAbsoluteZero(ValueOfTemp, TempT)) {
//            cerr << "Error: Temperature cannot be below or qual absolute zero!" << endl;
//            return 1;
//        }
//
//        temperatures.push_back(Temperature(day, month, year, TempT, (TempT == "C" ? ValueOfTemp : 0), (TempT == "F" ? ValueOfTemp : 0)));
//    }
//    return 0;
//}

//int inputfromfile() {
//    string filename;
//    cout << "Please enter the file name to record the values: ";
//    cin >> filename;
//    ifstream inputfile;
//    inputfile.open(filename);
//    if(inputfile.is_open()){
//
//    }
//
//    return 0;
//}

int main() {
    int n;
   /* char userchoise;
    string filename;
    cout << "Choose a suitable option for data input: " <<
        "\n1. from the console " <<
        "\n2. from the file \n";
    cin >> userchoise;
    switch (userchoise) {
    case('1'):
        inputfromconsole();
        break;
    case('2'):
        inputfromfile();
        break;
    default:
        cerr << "Error! Please enter 1 or 2!";
        return 1;
    }*/
    vector<Temperature> temperatures;
    
    cout << "Enter numbers of dates: ";
    cin >> n;
    if (n < 1) {
        cerr << "Invalid input! Please enter a positive integer." << endl;
        return 1;
    }

    

    for (int i = 0; i < n; i++) {
        string dateInput;
        int day, month, year;
        string TempT;
        double ValueOfTemp;

        cout << "Entry " << i + 1 << " - Enter date (format DD.MM.YYYY): ";
        cin >> dateInput;

        size_t dot1 = dateInput.find('.');
        size_t dot2 = dateInput.find('.', dot1 + 1);

        if (dot1 == string::npos && dot2 == string::npos) {
            cerr << "Invalid date format! Use DD.MM.YYYY." << endl;
            return 1;
        }

        try {
            day = stoi(dateInput.substr(0, dot1));
            month = stoi(dateInput.substr(dot1 + 1, dot2 - dot1 - 1));
            year = stoi(dateInput.substr(dot2 + 1));
        }
        catch (const invalid_argument) {
            cerr << "Invalid date format! Use numbers for day, month, and year." << endl;
            return 1;
        }
        catch (const out_of_range) {
            cerr << "Invalid date format! Date is out of range." << endl;
            return 1;
        }

        if (!isValidDate(day, month, year)) {
            cerr << "Invalid date entered!" << endl;
            return 1;
        }


        cout << "Enter temperature value and type: ";
        cin >> ValueOfTemp >> TempT;

        if (TempT != "C" && TempT != "F") {
            cerr << "Invalid temperature type! Use 'C' for Celsius or 'F' for Fahrenheit." << endl;
            return 1;
        }

        if (isBelowAbsoluteZero(ValueOfTemp, TempT)) {
            cerr << "Error: Temperature cannot be below or qual absolute zero!" << endl;
            return 1;
        }

        temperatures.push_back(Temperature(day, month, year, TempT, (TempT == "C" ? ValueOfTemp : 0), (TempT == "F" ? ValueOfTemp : 0)));
    }

    for (auto& temp : temperatures) {
        //temp.Print();
        temp.TempTransver();
        cout << "-----------------------------" << endl;
    }
    return 0;
}