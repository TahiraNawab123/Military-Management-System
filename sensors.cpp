#include <iostream>
#include <map>
#include <vector>
#include <string>
#include"IDS.h"
// implementing functions in MotionSensor class
bool MotionSensor :: detect (float value) {
if (value>=motionThreshold){
    return true;

}
return false;
}
void MotionSensor :: displayStatus(){
cout<<"The sensor id is "<<sensorID<<endl;
cout<<"The location of sensor is "<<sensorLocation<<endl;
cout<<"The range of sensor is "<<range<<endl;
cout<<"The motion threshold is "<<motionThreshold<<endl;
}
void MotionSensor :: setMotionSensitivity(float s){
    this->motionThreshold=s;
}
void MotionSensor ::calibrateMotionSensor(){
    motionThreshold+=10;
} 
void MotionSensor :: resetMotionSensor(){
*this=MotionSensor();
cout<<"Motion sensor has been reset..."<<endl;
}
void MotionSensor ::testMotionSensor(){
cout << "Testing Motion Sensor at location: " << sensorLocation << endl;

float testValues[] = {10.0, 20.0, 25.0, 30.0};

for (float val : testValues) {
    cout << "Testing with input value: " << val << " -> ";
    if (detect(val)) {
        cout << "Motion Detected!" << endl;
    } else {
        cout << "No Motion." << endl;
    }
}
}
bool MotionSensor :: operator==(const MotionSensor& other) {
    return this->sensorID == other.sensorID;
}
float MotionSensor::getMotionThreshold(){
    return motionThreshold;
}
// implementing functions in HeatSensor class

bool HeatSensor :: detect (float value) {
    if (value>=temperatureThreshold){
        return true;
    
    }
    return false;
    }
    void HeatSensor :: displayStatus(){
    cout<<"The sensor id is "<<sensorID<<endl;
    cout<<"The location of sensor is "<<sensorLocation<<endl;
    cout<<"The range of sensor is "<<range<<endl;
    cout<<"The temperature threshold is "<<temperatureThreshold<<endl;
    }
    void HeatSensor :: setHeatSensitivity(float s){
        this->temperatureThreshold=s;
    }
    void HeatSensor ::calibrateHeatSensor(){
        temperatureThreshold+=10;
    } 
    void HeatSensor :: resetHeatSensor(){
    *this=HeatSensor();
    cout<<"Heat sensor has been reset..."<<endl;
    }
    void HeatSensor ::testHeatSensor(){
    cout << "Testing Motion Sensor at location: " << sensorLocation << endl;
    
    float testValues[] = {10.0, 20.0, 25.0, 30.0};
    
    for (float val : testValues) {
        cout << "Testing with input value: " << val << " -> ";
        if (detect(val)) {
            cout << "Heat Detected!" << endl;
        } else {
            cout << "No heat detected...." << endl;
        }
    }
    }
    float HeatSensor::getTemperatureThreshold(){
        return temperatureThreshold;
    }
    // implementing functions in SensorInventory class

    SensorInventory::SensorInventory() {
    }
    
    SensorInventory::~SensorInventory() {
       
    }
    void SensorInventory:: addSensor(Sensors *sensor){
        sensorList.push_back(sensor);
        cout<<"Sensor added to the sensor inventory"<<endl;
       
    }
    void SensorInventory:: displaySensors(){
        for(auto sensors:sensorList){
            cout<<"Sensor ID is "<<sensors->getSensorID()<<endl;
            cout<<"Sensor range is "<<sensors->getRange()<<endl;
            cout<<"Sensor location is "<<sensors->getSensorLocation()<<endl;
            cout<<"Sensor  is "<<sensors->getSensorType()<<endl;
        }
    }
    void SensorInventory:: getSensorByID(int ID){
        bool found = false;
        for(auto sensor : sensorList){
            if(sensor->getSensorID() == ID){
                cout << "The Sensor range is " << sensor->getRange() << endl;
                cout << "The location of sensor is " << sensor->getSensorLocation() << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Sensor ID not found !!" << endl;
        }
    }
    void SensorInventory:: removeSensor(int ID){
        for(auto it = sensorList.begin(); it != sensorList.end(); ++it){
            if((*it)->getSensorID() == ID){
                sensorList.erase(it);
                cout<<"Sensor with id "<<ID<<" is removed "<<endl;
                return;
            }
        }
        cout<<"Sensor ID not found !!"<<endl;
    }
    int SensorInventory:: getTotalSensors(){
        int count=0;
        for(auto sensor:sensorList){
            count++;
    }
    return count;
}
