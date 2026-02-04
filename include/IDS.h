#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "json.hpp"
#include<fstream>

using json = nlohmann::json;
using namespace std;
// declaring all the classes in separate header file ie IDS.h

class Sensors // abstract class
{
protected:
    // protected datamembers to hide the specs of sensors from the other people/machines/intruder
    int sensorID;
    string sensorLocation;
    float range;
    string sensorType;

public:
    // constructors
    Sensors() : sensorID(0), sensorLocation(""), range(0.00), sensorType("") {}                                                                        // default
    Sensors(int ID, string location, float range, string sensorType) : sensorID(ID), sensorLocation(location), range(range), sensorType(sensorType) {} // parameterized
    virtual bool detect(float value) = 0;                                                                                                              // pure virtual function
    void displayStatus();
    int getSensorID() const
    {
        return sensorID;
    }
    string getSensorLocation() const { return sensorLocation; }
    float getRange() const { return range; }
    virtual string getSensorType() = 0;
    ~Sensors() {}
};
class MotionSensor : public Sensors
{
private:
    float motionThreshold;

public:
    MotionSensor() : Sensors(), motionThreshold(0.00) {}
    MotionSensor(int ID, string location, float range, string sensorType, float threshold) : Sensors(ID, location, range, sensorType), motionThreshold(threshold) {}
    bool detect(float value) override;  // overriden function for detection of motion
    void displayStatus();               // displays the details about sensor and its data
    void setMotionSensitivity(float s); // Manually adjust threshold
    void calibrateMotionSensor();       // Simulate realignment (adjust by +/- 10%)
    void resetMotionSensor();           // resets sensitivity and range to default values
    void testMotionSensor();            // Fake detection test (prints expected behavior)
    bool operator==(const MotionSensor &other);
    float getMotionThreshold();
    string getSensorType()
    {
        return "Motion Sensor";
    }
};
class HeatSensor : public Sensors
{
private:
    float temperatureThreshold;

public:
    HeatSensor() : Sensors(), temperatureThreshold(0.00) {}
    HeatSensor(int ID, string location, float range, string sensorType, float threshold) : Sensors(ID, location, range, sensorType), temperatureThreshold(threshold) {}
    bool detect(float value) override;
    void displayStatus();
    void setHeatSensitivity(float sen);
    void calibrateHeatSensor(); // Simulate realignment (adjust by +/- 10%)
    void resetHeatSensor();     // resets sensitivity and range to default values
    void testHeatSensor();      // Fake detection test (prints expected behavior)
    float getTemperatureThreshold();
    string getSensorType()
    {
        return "Heat Sensor";
    }
};

class SensorInventory
{
private:
    vector<Sensors *> sensorList; // vector to store sensor list

public:
    SensorInventory();
    ~SensorInventory();
    void addSensor(Sensors * sensor);
    void removeSensor(int ID);
    void displaySensors();
    void getSensorByID(int ID);
    int getTotalSensors();
};

class Intruder
{
private:
    int intruderID;
    string detectedLocation;
    string detectionTime;
    Sensors *sensorTriggered;
    string sensorType;

public:
    Intruder() : intruderID(0), detectedLocation(""), detectionTime(""), sensorTriggered(nullptr),sensorType("") {}
    Intruder(int ID, string location, string time, Sensors *sensor,string sensorType) : intruderID(ID),
                                                                      detectedLocation(location), detectionTime(time), sensorTriggered(sensor),sensorType(sensorType) {}
    void setIntruderID(int id);
    int getIntruderID() const;
    void setLocation(string loc);
    string getLocation() const;
    void setTime(string time);
    string getTime() const;
    Sensors* getSensorPointer() const; 
    void displayIntruderInfo() const;
    void setSensorType(const string& type) {
        sensorType = type;
    }

    string getSensorType() const {
        return sensorType;
    }
    Sensors* getSensor() const { return sensorTriggered; }
};

class IntrusionLog{
    private:
    vector<Intruder> intrusionVector;
    map<int, Intruder> intrusionMap;
    public:
    void addIntrusion(const Intruder& intruder);
    void displayIntrusions() const;
    Intruder* getIntrusionByID(int id);
    
    void storeToJSON(const string& filename) const;
    void loadFromJSON(const string& filename);
       
};
class Logger//singleton class 
{
    private:
    static Logger* instance;
    ofstream logFile;

    Logger(); // private constructor

public:
    static Logger* getInstance();
    void logEvent(const string& message);
    ~Logger();

};

enum class ThreatType { LOW, MEDIUM, HIGH };

class ThreatLevel {
public:
    static ThreatType analyzeThreat(const Intruder& intruder);
    static void triggerBeep(ThreatType level);
};

template <typename T>
class Storage {
private:
    std::vector<T> items;

public:
    void addItem(const T& item) {
        items.push_back(item);
    }

    void displayAll() const {
        for (const auto& item : items) {
            item.displayIntruderInfo();  // Assumes T has this method
        }
    }

    int getCount() const {
        return items.size();
    }
};

