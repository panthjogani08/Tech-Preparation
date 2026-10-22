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

void displayWaitingPatients()
{
    if (patientQueue.empty())
    {
        cout << "No patients are currently waiting.\n";
        return;
    }

    auto temp = patientQueue;

    cout << "\nID\tName\t\tAge\tPriority\tStatus\n";

    while (!temp.empty())
    {
        Patient p = temp.top();
        temp.pop();

        cout << p.patientID << "\t"
             << p.name << "\t\t"
             << p.age << "\t"
             << p.priority << "\t\t"
             << p.status << endl;
    }
}

void viewNextPatient()
{
    if (patientQueue.empty())
    {
        cout << "No patients are waiting.\n";
        return;
    }

    Patient p = patientQueue.top();

    cout << "\nNext Patient\n";
    cout << "Patient ID: " << p.patientID << endl;
    cout << "Name: " << p.name << endl;
    cout << "Age: " << p.age << endl;
    cout << "Condition: " << p.condition << endl;
    cout << "Priority: " << p.priority << endl;
    cout << "Arrival Time: " << p.arrivalTime << endl;
    cout << "Status: " << p.status << endl;
}

void treatNextPatient()
{
    if (patientQueue.empty())
    {
        cout << "No patients are waiting for treatment.\n";
        return;
    }

    Patient p = patientQueue.top();
    patientQueue.pop();

    for (Patient& patient : allPatients)
    {
        if (patient.patientID == p.patientID)
        {
            patient.status = "Treated";
            break;
        }
    }

    saveData();

    cout << "\nPatient treatment completed!\n";
    cout << "Patient ID: " << p.patientID << endl;
    cout << "Name: " << p.name << endl;
    cout << "Status updated to Treated.\n";
}

void searchPatient()
{
    int id;

    cout << "Enter Patient ID to search: ";
    cin >> id;

    for (const Patient& p : allPatients)
    {
        if (p.patientID == id)
        {
            cout << "\nPatient Found\n";
            cout << "ID: " << p.patientID << endl;
            cout << "Name: " << p.name << endl;
            cout << "Age: " << p.age << endl;
            cout << "Condition: " << p.condition << endl;
            cout << "Priority: " << p.priority << endl;
            cout << "Status: " << p.status << endl;
            return;
        }
    }

    cout << "Patient not found.\n";
}

void displayAllRecords()
{
    if (allPatients.empty())
    {
        cout << "No patient records available.\n";
        return;
    }

    for (const Patient& p : allPatients)
    {
        cout << "\nPatient ID: " << p.patientID << endl;
        cout << "Name: " << p.name << endl;
        cout << "Age: " << p.age << endl;
        cout << "Condition: " << p.condition << endl;
        cout << "Priority: " << p.priority << endl;
        cout << "Arrival Time: " << p.arrivalTime << endl;
        cout << "Status: " << p.status << endl;
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

    cout << "\nHospital Statistics\n";
    cout << "Total Patients: " << total << endl;
    cout << "Waiting Patients: " << waiting << endl;
    cout << "Treated Patients: " << treated << endl;
    cout << "Critical Patients: " << critical << endl;
}

int main()
{
    loadData();

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "  HOSPITAL PATIENT QUEUE SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Waiting Patients\n";
        cout << "3. View Next Patient\n";
        cout << "4. Treat Next Patient\n";
        cout << "5. Search Patient\n";
        cout << "6. Display All Patient Records\n";
        cout << "7. Display Hospital Statistics\n";
        cout << "8. Exit\n";
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
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Enter 1-8.\n";
        }

    } while (choice != 8);

    return 0;
}