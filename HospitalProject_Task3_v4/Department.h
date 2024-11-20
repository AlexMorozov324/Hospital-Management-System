#ifndef __Department_H
#define __Department_H

#define _CRT_SECURE_NO_WARNINGS
#include "Doctor.h"
#include "Nurse.h"
#include "patient.h"
#include "researcher.h"
#include <vector>
#include <string>

class Nurse;
class Doctor;
class patient;
class researcher;

class Department
{
private:
    string name;
    vector<Doctor*> doctorsPtrsVector;
    vector<Nurse*> nursesPtrsVector;
    vector<patient*> patientsPtrsVector;

    Department(const Department& other); // disabling copy c'tor option, becasue we don't want to duplicate Departments
    Department(Department&& other); // disabling move c'tor option, becasue we don't want to duplicate Departments

public:
    Department(const string& nameOfDep) noexcept(false);
    Department(ifstream& inputFile);
    ~Department();

    void setName(const string& nameOfDep) noexcept(false);
    const string& getName() const;
    int getNumOfPatients() const;

    const vector<Doctor*>& getDoctorsPtrsVector();
    const vector<Nurse*>& getNursesPtrsVector();
    const vector<patient*>& getPatientsPtrsVector();

    const Department& operator+=(Doctor* newDoctorPtr);
    void addDoctorToArr(Doctor* newDoctorPtr);
    const Department& operator+=(Nurse* newNursePtr);
    void addNurseToArr(Nurse* newNursePtr);
    const Department& operator+=(patient* newPatientPtr);
    void addPatientToArr(patient* newPatientPtr);

    void printDoctorsArr() const;
    void saveToBinaryFile(ofstream& outputFile) const;
};

#endif // __Department_H

