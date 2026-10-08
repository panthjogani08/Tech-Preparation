#include <iostream>
using namespace std;


class SensorSystem {
protected:
    float moisture[3], temp[3], humidity[3];

public:
    virtual void inputData() = 0;
    virtual void processData() = 0;
    virtual void displayResult() = 0;
    virtual ~SensorSystem() {} 
};


class SmartFarm : public SensorSystem {
private:
    float avgMoisture, avgTemp, avgHumidity;
    float predictedMoisture;
    static int systemCount;

public:
   
    SmartFarm() {
        cout << "\nSmart Farm System Initialized...\n";
        systemCount++;
    }

   
    ~SmartFarm() {
        cout << "\nSystem Shutdown...\n";
    }


    void inputData() override {
        for(int i = 0; i < 3; i++) {
            cout << "\nCycle " << i + 1 << ":\n";
            cout << "Enter Moisture: ";
            cin >> moisture[i];
            cout << "Enter Temperature: ";
            cin >> temp[i];
            cout << "Enter Humidity: ";
            cin >> humidity[i];
        }
    }

   
    void processData() override {
        avgMoisture = (moisture[0] + moisture[1] + moisture[2]) / 3.0;
        avgTemp = (temp[0] + temp[1] + temp[2]) / 3.0;
        avgHumidity = (humidity[0] + humidity[1] + humidity[2]) / 3.0;

        predictedMoisture = avgMoisture - (avgTemp / 100.0) * 5;   //predict the moisture from formula
    }


    void decisionEngine() {
        cout << "\n--- System Decisions ---\n";

        if (predictedMoisture < 30 && avgTemp > 35) {
            cout << "CRITICAL: High Temp & Dry Soil -> Pump ON (HIGH) \n";
        }
        else if (predictedMoisture < 35) {
            cout << "WARNING: Soil Getting Dry -> Pump ON \n";
        }
        else if (predictedMoisture < 45) {
            cout << "INFO: Monitor Soil \n";
        }
        else {
            cout << "STABLE: No Action Needed \n";
        }

        if (avgHumidity < 40) {
            cout << "Extra Action: Mist Sprayer ON \n";
        }

        if (avgTemp > 36) {
            cout << "Cooling System: Fan ON \n";
        }
    }

    
    void displayResult() override {
        cout << "\n===== AI FARM REPORT =====\n";
        cout << "Avg Moisture: " << avgMoisture << "%\n";
        cout << "Avg Temp: " << avgTemp << "C\n";
        cout << "Avg Humidity: " << avgHumidity << "%\n";
        cout << "Predicted Moisture: " << predictedMoisture << "%\n";

        decisionEngine();
    } 
};


int SmartFarm::systemCount = 0;

int main() {
    SmartFarm farm;

    farm.inputData();
    farm.processData();
    farm.displayResult();

    return 0;
}