#include <iostream>
#include <map>
#include <vector>
#include <string>
#include"IDS.h"
#include<fstream>
#include "json.hpp"  
#include<windows.h>
using json = nlohmann::json;
void Intruder:: setIntruderID(int id){
    intruderID=id;
}
    int Intruder:: getIntruderID() const{
return intruderID;
    }
    void Intruder:: setLocation(string loc){
        detectedLocation=loc;
    }
    string Intruder:: getLocation() const{
        return detectedLocation;
    }
    void Intruder:: setTime(string time){
        detectionTime=time ;
    }
    string Intruder::getTime() const{
        return detectionTime;
    }
    
   
    void Intruder:: displayIntruderInfo() const{
        cout<<"The unique ID of the Intruder is "<<getIntruderID()<<endl;
        cout<<"The location of Intruder is "<<getLocation()<<endl;
        cout<<"The time of detection of Intruder is  "<<getTime()<<endl;
        if (sensorTriggered != nullptr) {
            cout << "Sensor Triggered: " << sensorTriggered->getSensorType() << endl;
        } else {
            cout << "Sensor Triggered: None" << endl;
        }
       
    }
    void  IntrusionLog :: addIntrusion(const Intruder& intruder){
        intrusionMap [intruder.getIntruderID()] = intruder;

    }
    Intruder* IntrusionLog::getIntrusionByID(int id) {
        auto it = intrusionMap.find(id);
        if (it != intrusionMap.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    
    void IntrusionLog::displayIntrusions() const {
        for (const auto& pair : intrusionMap) {
            pair.second.displayIntruderInfo();
            std::cout << "---------------------------\n";
        }
    }
    Sensors* Intruder::getSensorPointer() const {
        return sensorTriggered;
    }
    void IntrusionLog::storeToJSON(const std::string& filename) const {
        json j;
        std::vector<Intruder> tempVector;
    
        for (const auto& pair : intrusionMap) {
            tempVector.push_back(pair.second);
        }
    
        for (const auto& intruder : tempVector) {
            json entry;
            entry["IntruderID"] = intruder.getIntruderID();
            entry["Location"] = intruder.getLocation();
            entry["Time"] = intruder.getTime();
    
            Sensors* sensor = intruder.getSensorPointer();  // Use new getter
            entry["SensorType"] = (sensor != nullptr) ? sensor->getSensorType() : "Unknown";
    
            j.push_back(entry);
        }
    
        ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4);  // pretty print
            file.close();
        } else {
            cout << "Failed to open file: " << filename << std::endl;
        }
    }

    void IntrusionLog::loadFromJSON(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open JSON file for reading.\n";
            return;
        }
    
        json j;
        file >> j;
        file.close();
    
        intrusionVector.clear();  // Clear any existing data
    
        for (const auto& entry : j) {
            int id = entry.value("IntruderID", 0);
            string location = entry.value("Location", "");
            string time = entry.value("Time", "");
            string sensorType = entry.value("SensorType", "");
    
            // Just storing the sensor type name (not the actual Sensor* pointer)
            Intruder intruder1;//(id, location, time, nullptr,sensorType);
            //intruder.setSensorType(sensorType);  
    
            intrusionVector.push_back(intruder1);
        
            cout<<j<<endl;
        }
    }

    Logger* Logger::instance = nullptr;

    Logger::Logger() {
        logFile.open("log.txt", ios::app); // Opens in append mode
    }
    
    Logger::~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    Logger* Logger::getInstance() {
        if (instance == nullptr) {
            instance = new Logger();
        }
        return instance;
    }
    
    void Logger::logEvent(const string& message) {
        if (logFile.is_open()) {
            logFile << message << endl;
        }
    }
    ThreatType ThreatLevel::analyzeThreat(const Intruder& intruder) {
        string sensorType = intruder.getSensorType();

if (sensorType == "Motion") {
    return ThreatType::MEDIUM;
} else if (sensorType == "Heat") {
    return ThreatType::HIGH;
} else {
    return ThreatType::LOW;
}
    }
    
    void ThreatLevel::triggerBeep(ThreatType type) {
        switch (type) {
            case ThreatType::LOW:
                Beep(750, 200); // Frequency 750 Hz for 200 ms
                break;
            case ThreatType::MEDIUM:
                Beep(750, 200);
                Beep(750, 200);
                break;
            case ThreatType::HIGH:
                Beep(1000, 200);
                Beep(1000, 200);
                Beep(1000, 200);
                break;
        }
    }
