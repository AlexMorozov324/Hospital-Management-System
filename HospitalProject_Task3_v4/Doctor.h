#ifndef __Doctor_H
#define __Doctor_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Hospital.h"
#include "Staff.h"

enum eDoctorsTypes { REGULAR_DOCTOR = 1, SURGEON_DOCTOR, RESEARCHER_DOCTOR, RESEARCHER_SURGEON_DOCTOR};
extern const char* doctorsTypesStrings[]; // definition is in the .cpp file

class Doctor : virtual public Staff
{
protected:
    string specialization;

    Doctor(const Doctor& other) = default;
    Doctor(Doctor&& other) = default;
    const Doctor& operator=(const Doctor& other);
    const Doctor& operator=(Doctor&& other);

public:
    Doctor(const string& nameOfDoc, const string& specializationOfDoc) noexcept(false);
    Doctor(const Staff& staff, const string& specializationOfDoc) noexcept(false);
    Doctor(ifstream& inputFile);
    virtual ~Doctor() {};
    
    const string& getSpecialization() const;

    void setSpecialization(const string& Spec) noexcept(false);

    static Doctor* makeNewDoctorPtr(const string& newDoctorName, const string& newDoctorspecialization);

    virtual void show() const;
    friend ostream& operator<<(ostream& os, const Doctor& doctor);
    static void printDoctorsTypes();
    virtual void saveToBinaryFile(ofstream& outputFile) const override;
};

#endif // __Doctor_H