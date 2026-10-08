#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Structure to store patient details
struct Patient
{
    int patientID;
    string name;
    int age;
    string condition;
    int priority;
    int arrivalNumber;
};

// Comparator for Priority Queue
struct ComparePriority
{
    bool operator()(const Patient& p1, const Patient& p2)
    {
        // Smaller priority number = higher priority
        if (p1.priority != p2.priority)
        {
            return p1.priority > p2.priority;
        }

        // If priority is same, earlier arrival gets priority
        return p1.arrivalNumber > p2.arrivalNumber;
    }
};

// Priority Queue
priority_queue<Patient, vector<Patient>, ComparePriority> patientQueue;

// Vector to store all patient records
vector<Patient> allPatients;

int arrivalCounter = 0;

// Function to add a patient
void addPatient()
{
    Patient p;

    cout << "\n========== ADD PATIENT ==========\n";

    cout << "Enter Patient ID: ";
    cin >> p.patientID;

    cin.ignore();

    cout << "Enter Patient Name: ";
    getline(cin, p.name);

    cout << "Enter Age: ";
    cin >> p.age;

    cin.ignore();

    cout << "Enter Medical Condition: ";
    getline(cin, p.condition);

    cout << "\nSelect Priority:\n";
    cout << "1. Critical Emergency\n";
    cout << "2. Serious Condition\n";
    cout << "3. Moderate Condition\n";
    cout << "4. Normal Condition\n";

    cout << "Enter Priority (1-4): ";
    cin >> p.priority;

    // Validate priority
    while (p.priority < 1 || p.priority > 4)
    {
        cout << "Invalid priority! Enter between 1 and 4: ";
        cin >> p.priority;
    }

    arrivalCounter++;
    p.arrivalNumber = arrivalCounter;

    patientQueue.push(p);
    allPatients.push_back(p);

    cout << "\nPatient added successfully!\n";
}

// Function to display waiting patients
void displayPatients()
{
    if (patientQueue.empty())
    {
        cout << "\nNo patients are currently waiting.\n";
        return;
    }

    // Make a temporary queue
    priority_queue<Patient, vector<Patient>, ComparePriority> temp = patientQueue;

    cout << "\n================ WAITING PATIENTS ================\n";

    cout << left
         << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(8) << "Age"
         << setw(25) << "Condition"
         << setw(10) << "Priority"
         << endl;

    cout << "---------------------------------------------------------------\n";

    while (!temp.empty())
    {
        Patient p = temp.top();
        temp.pop();

        cout << left
             << setw(10) << p.patientID
             << setw(20) << p.name
             << setw(8) << p.age
             << setw(25) << p.condition
             << setw(10) << p.priority
             << endl;
    }
}

// Function to view next patient
void viewNextPatient()
{
    if (patientQueue.empty())
    {
        cout << "\nNo patients are waiting.\n";
        return;
    }

    Patient p = patientQueue.top();

    cout << "\n========== NEXT PATIENT ==========\n";

    cout << "Patient ID       : " << p.patientID << endl;
    cout << "Name             : " << p.name << endl;
    cout << "Age              : " << p.age << endl;
    cout << "Condition        : " << p.condition << endl;
    cout << "Priority         : " << p.priority << endl;

    if (p.priority == 1)
        cout << "Priority Type    : Critical Emergency\n";
    else if (p.priority == 2)
        cout << "Priority Type    : Serious Condition\n";
    else if (p.priority == 3)
        cout << "Priority Type    : Moderate Condition\n";
    else
        cout << "Priority Type    : Normal Condition\n";
}

// Function to treat next patient
void treatNextPatient()
{
    if (patientQueue.empty())
    {
        cout << "\nNo patients are waiting for treatment.\n";
        return;
    }

    Patient p = patientQueue.top();
    patientQueue.pop();

    cout << "\n========== PATIENT BEING TREATED ==========\n";

    cout << "Patient ID       : " << p.patientID << endl;
    cout << "Name             : " << p.name << endl;
    cout << "Age              : " << p.age << endl;
    cout << "Condition        : " << p.condition << endl;
    cout << "Priority         : " << p.priority << endl;

    cout << "\nPatient treatment completed successfully!\n";
}

// Function to search patient
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

    for (int i = 0; i < allPatients.size(); i++)
    {
        if (allPatients[i].patientID == id)
        {
            Patient p = allPatients[i];

            cout << "\n========== PATIENT FOUND ==========\n";

            cout << "Patient ID       : " << p.patientID << endl;
            cout << "Name             : " << p.name << endl;
            cout << "Age              : " << p.age << endl;
            cout << "Condition        : " << p.condition << endl;
            cout << "Priority         : " << p.priority << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nPatient not found.\n";
    }
}

// Function to display all registered records
void displayAllRecords()
{
    if (allPatients.empty())
    {
        cout << "\nNo patient records available.\n";
        return;
    }

    cout << "\n================ ALL PATIENT RECORDS ================\n";

    cout << left
         << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(8) << "Age"
         << setw(25) << "Condition"
         << setw(10) << "Priority"
         << endl;

    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < allPatients.size(); i++)
    {
        Patient p = allPatients[i];

        cout << left
             << setw(10) << p.patientID
             << setw(20) << p.name
             << setw(8) << p.age
             << setw(25) << p.condition
             << setw(10) << p.priority
             << endl;
    }
}

// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n\n";
        cout << "===============================================\n";
        cout << "       HOSPITAL PATIENT QUEUE SYSTEM\n";
        cout << "===============================================\n";

        cout << "1. Add Patient\n";
        cout << "2. Display Waiting Patients\n";
        cout << "3. View Next Patient\n";
        cout << "4. Treat Next Patient\n";
        cout << "5. Search Patient\n";
        cout << "6. Display All Patient Records\n";
        cout << "7. Exit\n";

        cout << "===============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
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
                cout << "\nThank you for using Hospital Patient Queue System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

        
    } while (choice != 7);

    return 0;
}