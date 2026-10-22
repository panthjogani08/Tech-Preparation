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