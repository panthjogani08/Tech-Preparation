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
        {
            return p1.priority > p2.priority;
        }

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
       << localTime->tm_year + 1900 << " ";

    ss << setw(2) << localTime->tm_hour << ":"
       << setw(2) << localTime->tm_min << ":"
       << setw(2) << localTime->tm_sec;

    return ss.str();
}


bool patientIDExists(int id)
{
    for (const Patient& p : allPatients)
    {
        if (p.patientID == id)
        {
            return true;
        }
    }

    return false;
}


void saveData()
{
    ofstream file(FILE_NAME);

    if (!file)
    {
        cout << "\nError: Unable to open file!\n";
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
    {
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

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
            {
                arrivalCounter = p.arrivalNumber;
            }

            if (p.status == "Waiting")
            {
                patientQueue.push(p);
            }
        }
        catch (...)
        {
            cout << "\nWarning: Invalid record found in file.\n";
        }
    }

    file.close();
}


void addPatient()
{
    Patient p;

    cout << "\n";
    cout << "=========================================\n";
    cout << "           ADD NEW PATIENT\n";
    cout << "=========================================\n";

    cout << "Enter Patient ID: ";
    cin >> p.patientID;

    if (patientIDExists(p.patientID))
    {
        cout << "\nPatient ID already exists!\n";
        cout << "Please use a different ID.\n";
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

    cout << "\n";
    cout << "Priority Levels:\n";
    cout << "1. Critical Emergency\n";
    cout << "2. Serious Condition\n";
    cout << "3. Moderate Condition\n";
    cout << "4. Normal Condition\n";

    cout << "\nEnter Priority (1-4): ";
    cin >> p.priority;

    while (p.priority < 1 || p.priority > 4)
    {
        cout << "Invalid priority!\n";
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

    cout << "\n=========================================\n";
    cout << "Patient added successfully!\n";
    cout << "Patient ID    : " << p.patientID << endl;
    cout << "Name          : " << p.name << endl;
    cout << "Priority      : " << p.priority << endl;
    cout << "Arrival Time  : " << p.arrivalTime << endl;
    cout << "Status        : " << p.status << endl;
    cout << "=========================================\n";
}

void displayWaitingPatients()
{
    if (patientQueue.empty())
    {
        cout << "\nNo patients are currently waiting.\n";
        return;
    }

    priority_queue<Patient, vector<Patient>, ComparePriority> temp =
        patientQueue;

    cout << "\n";
    cout << "===============================================================\n";
    cout << "                    WAITING PATIENTS\n";
    cout << "===============================================================\n";

    cout << left
         << setw(8) << "ID"
         << setw(18) << "Name"
         << setw(6) << "Age"
         << setw(20) << "Condition"
         << setw(10) << "Priority"
         << setw(12) << "Status"
         << endl;

    cout << "---------------------------------------------------------------\n";

    while (!temp.empty())
    {
        Patient p = temp.top();
        temp.pop();

        cout << left
             << setw(8) << p.patientID
             << setw(18) << p.name
             << setw(6) << p.age
             << setw(20) << p.condition
             << setw(10) << p.priority
             << setw(12) << p.status
             << endl;
    }

    cout << "===============================================================\n";
}


void viewNextPatient()
{
    if (patientQueue.empty())
    {
        cout << "\nNo patients are waiting.\n";
        return;
    }

    Patient p = patientQueue.top();

    cout << "\n";
    cout << "=========================================\n";
    cout << "             NEXT PATIENT\n";
    cout << "=========================================\n";

    cout << "Patient ID       : " << p.patientID << endl;
    cout << "Name             : " << p.name << endl;
    cout << "Age              : " << p.age << endl;
    cout << "Condition        : " << p.condition << endl;
    cout << "Priority         : " << p.priority << endl;
    cout << "Arrival Time     : " << p.arrivalTime << endl;
    cout << "Status           : " << p.status << endl;

    if (p.priority == 1)
        cout << "Priority Type    : Critical Emergency\n";
    else if (p.priority == 2)
        cout << "Priority Type    : Serious Condition\n";
    else if (p.priority == 3)
        cout << "Priority Type    : Moderate Condition\n";
    else
        cout << "Priority Type    : Normal Condition\n";

    cout << "=========================================\n";
}


void treatNextPatient()
{
    if (patientQueue.empty())
    {
        cout << "\nNo patients are waiting for treatment.\n";
        return;
    }
    Patient p = patientQueue.top();

    patientQueue.pop();

    cout << "\n";
    cout << "=========================================\n";
    cout << "          PATIENT BEING TREATED\n";
    cout << "=========================================\n";

    cout << "Patient ID       : " << p.patientID << endl;
    cout << "Name             : " << p.name << endl;
    cout << "Age              : " << p.age << endl;
    cout << "Condition        : " << p.condition << endl;
    cout << "Priority         : " << p.priority << endl;

    for (Patient& patient : allPatients)
    {
        if (patient.patientID == p.patientID)
        {
            patient.status = "Treated";
            break;
        }
    }

    saveData();

    cout << "\nPatient treatment completed successfully!\n";
    cout << "Patient status updated to: Treated\n";

    cout << "=========================================\n";
}

void searchPatient()
{
    if (allPatients.empty())
    {
        cout << "\nNo patient records available.\n";
        return;
    }

    int id;

    cout << "\nEnter Patient ID to search: ";
    cin >> id;

    bool found = false;

    for (const Patient& p : allPatients)
    {
        if (p.patientID == id)
        {
            cout << "\n";
            cout << "=========================================\n";
            cout << "             PATIENT FOUND\n";
            cout << "=========================================\n";

            cout << "Patient ID       : " << p.patientID << endl;
            cout << "Name             : " << p.name << endl;
            cout << "Age              : " << p.age << endl;
            cout << "Condition        : " << p.condition << endl;
            cout << "Priority         : " << p.priority << endl;
            cout << "Arrival Number   : " << p.arrivalNumber << endl;
            cout << "Arrival Time     : " << p.arrivalTime << endl;
            cout << "Status           : " << p.status << endl;

            cout << "=========================================\n";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nPatient with ID " << id << " was not found.\n";
    }
}
void displayAllRecords()
{
    if (allPatients.empty())
    {
        cout << "\nNo patient records available.\n";
        return;
    }

    cout << "\n";
    cout << "====================================================================\n";
    cout << "                    ALL PATIENT RECORDS\n";
    cout << "====================================================================\n";

    for (const Patient& p : allPatients)
    {
        cout << "\nPatient ID       : " << p.patientID;
        cout << "\nName             : " << p.name;
        cout << "\nAge              : " << p.age;
        cout << "\nCondition        : " << p.condition;
        cout << "\nPriority         : " << p.priority;
        cout << "\nArrival Number   : " << p.arrivalNumber;
        cout << "\nArrival Time     : " << p.arrivalTime;
        cout << "\nStatus           : " << p.status;

        cout << "\n---------------------------------------------\n";
    }
}
void displayStatistics()
{
    int total = allPatients.size();
    int waiting = 0;
    int treated = 0;
    int critical = 0;

    for (const Patient& p : allPatients)
    {
        if (p.status == "Waiting")
            waiting++;

        if (p.status == "Treated")
            treated++;

        if (p.priority == 1 && p.status == "Waiting")
            critical++;
    }

    cout << "\n";
    cout << "=========================================\n";
    cout << "             HOSPITAL STATISTICS\n";
    cout << "=========================================\n";

    cout << "Total Patients       : " << total << endl;
    cout << "Waiting Patients     : " << waiting << endl;
    cout << "Treated Patients     : " << treated << endl;
    cout << "Critical Patients    : " << critical << endl;

    cout << "=========================================\n";
}
int main()
{

    loadData();

    int choice;

    do
    {
        cout << "\n\n";
        cout << "================================================\n";
        cout << "        HOSPITAL PATIENT QUEUE SYSTEM\n";
        cout << "================================================\n";

        cout << "1. Add Patient\n";
        cout << "2. Display Waiting Patients\n";
        cout << "3. View Next Patient\n";
        cout << "4. Treat Next Patient\n";
        cout << "5. Search Patient\n";
        cout << "6. Display All Patient Records\n";
        cout << "7. Display Hospital Statistics\n";
        cout << "8. Exit\n";

        cout << "================================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                displayWaitingPatients();
                break;

            case 3:
                viewNextPatient();
                break;

            case 4:
                treatNextPatient();
                break;

            case 5:
                searchPatient();
                break;

            case 6:
                displayAllRecords();
                break;

            case 7:
                displayStatistics();
                break;

            case 8:
                cout << "\n";
                cout << "Thank you for using Hospital Patient Queue System!\n";
                cout << "All patient records are safely stored.\n";
                break;

            default:
                cout << "\nInvalid choice! Please enter 1-8.\n";
        }

    } while (choice != 8);

    return 0;
}