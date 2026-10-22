#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

struct Patient
{
    int patientID;
    string name;
    int age;
    string condition;
    int priority;
    int arrivalNumber;
    string arrivalTime;
    string status;
};

struct ComparePriority
{
    bool operator()(const Patient& p1, const Patient& p2)
    {
        if (p1.priority != p2.priority)
            return p1.priority > p2.priority;

        return p1.arrivalNumber > p2.arrivalNumber;
    }
};

priority_queue<Patient, vector<Patient>, ComparePriority> patientQueue;
vector<Patient> allPatients;

int arrivalCounter = 0;
const string FILE_NAME = "patients.txt";

string getCurrentDateTime()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_mday << "-"
       << setw(2) << localTime->tm_mon + 1 << "-"
       << localTime->tm_year + 1900 << " "
       << setw(2) << localTime->tm_hour << ":"
       << setw(2) << localTime->tm_min << ":"
       << setw(2) << localTime->tm_sec;

    return ss.str();
}

bool patientIDExists(int id)
{
    for (const Patient& p : allPatients)
    {
        if (p.patientID == id)
            return true;
    }

    return false;
}

void saveData()
{
    ofstream file(FILE_NAME);

    if (!file)
    {
        cout << "Error: Unable to open file!\n";
        return;
    }

    for (const Patient& p : allPatients)
    {
        file << p.patientID << "|"
             << p.name << "|"
             << p.age << "|"
             << p.condition << "|"
             << p.priority << "|"
             << p.arrivalNumber << "|"
             << p.arrivalTime << "|"
             << p.status << "\n";
    }

    file.close();
}

void loadData()
{
    ifstream file(FILE_NAME);

    if (!file)
        return;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string value;
        Patient p;

        try
        {
            getline(ss, value, '|');
            p.patientID = stoi(value);

            getline(ss, p.name, '|');

            getline(ss, value, '|');
            p.age = stoi(value);

            getline(ss, p.condition, '|');

            getline(ss, value, '|');
            p.priority = stoi(value);

            getline(ss, value, '|');
            p.arrivalNumber = stoi(value);

            getline(ss, p.arrivalTime, '|');
            getline(ss, p.status);

            allPatients.push_back(p);

            if (p.arrivalNumber > arrivalCounter)
                arrivalCounter = p.arrivalNumber;

            if (p.status == "Waiting")
                patientQueue.push(p);
        }
        catch (...)
        {
            cout << "Warning: Invalid patient record.\n";
        }
    }

    file.close();
}

void addPatient()
{
    Patient p;

    cout << "\nEnter Patient ID: ";
    cin >> p.patientID;

    if (patientIDExists(p.patientID))
    {
        cout << "Patient ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Patient Name: ";
    getline(cin, p.name);

    cout << "Enter Age: ";
    cin >> p.age;
    cin.ignore();

    cout << "Enter Medical Condition: ";
    getline(cin, p.condition);

    cout << "\nPriority Levels:\n";
    cout << "1. Critical Emergency\n";
    cout << "2. Serious Condition\n";
    cout << "3. Moderate Condition\n";
    cout << "4. Normal Condition\n";

    cout << "Enter Priority (1-4): ";
    cin >> p.priority;

    while (p.priority < 1 || p.priority > 4)
    {
        cout << "Enter priority between 1 and 4: ";
        cin >> p.priority;
    }

    arrivalCounter++;
    p.arrivalNumber = arrivalCounter;
    p.arrivalTime = getCurrentDateTime();
    p.status = "Waiting";

    allPatients.push_back(p);
    patientQueue.push(p);

    saveData();

    cout << "\nPatient added successfully!\n";
    cout << "Patient ID: " << p.patientID << endl;
    cout << "Name: " << p.name << endl;
    cout << "Priority: " << p.priority << endl;
    cout << "Arrival Time: " << p.arrivalTime << endl;
    cout << "Status: " << p.status << endl;
}