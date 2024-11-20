#pragma once

#include "researchInstitute.h"
#include "Department.h"
#include <vector>

class Department;
class researchInstitute;
class patient;
class Doctor;
class DoctorResercher;
class DoctorResercherSurgeon;

enum eMenuOptions { END_OF_INPUT, ADD_DEPARTMENT, ADD_NURSE, ADD_DOCTOR, ADD_VISIT, ADD_RESEARCHER, ADD_ARTICLE, SHOW_DEPARTMENT_PATIENTS, SHOW_ALL_EMPLOYEES, SHOW_ALL_RESEARCHERS, SHOW_ALL_RESEARCHERS_DOCTORS, FIND_PATIENT_BY_ID, COMPARE_RESEARCHERS, FIND_DEPARTMENT_WITH_MAX_PATIENTS}; // this will be used for the main options menu for the user to choose between the different options.

class Hospital
{
private:
    vector<Department*> m_DepartmentsPtrsVector;
    researchInstitute* m_resInst;

    Hospital(const Hospital& other);
    Hospital(Hospital&& other);
    const Hospital& operator=(const Hospital& other);
    const Hospital& operator=(Hospital&& other);

public:
    Hospital();
    Hospital(ifstream& inputFile);
    ~Hospital();

    void printOptionsMenu() const;

    int getNumOfDepartments() const;
    void addNewDepartment(const string& newDepartmentName);
    vector<Department*>& getDepartmentsPtrsVector();
    const vector<Department*>& getDepartmentsPtrsVector() const;
    const researchInstitute* getResearchInstitutePtr() const;

    void addNewNurse(const string& newNurseName, int numberOfExperienceYears, int departmentToAddTo);
    void addNewDoctor(const string& newDoctorName, const string& newDoctorspecialization, int departmentToAddTo);
    void addNewDoctorSurgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg, int departmentToAddTo);
    void addNewDoctorResercher(const string& newDoctorName, const string& newDoctorspecialization, int departmentToAddTo);
    void addNewDoctorResercherSurgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg, int departmentToAddTo);
    void addVisit(patient* patientPtr, const Date& newVisiDate, bool isNewPatient, int departmentToAddTo, const string& visitReason, const bool& needSurg, const int& surgeryRoom, const bool& tsum, Doctor* newVisitDoctor);
    void addNewResearcher(researcher* newResearcherPtr);
    void addArticle(article* newArticle, int ResearcherToAddTo);

    void showDeparmentPatients(int choice) const;
    int getNumOfWorkers() const;
    int getNumOfDoctors() const;
    int getNumOfNurses() const;
    int getNumOfResercherDoctors() const;
    const researcher& getResearcher(int index) const;
    void showAllWorkers();
    void showAllReserchers();
    void showAllReserchersDoctors();

    patient* findPatientByID(const string& id) const;
    void showVisitHistory(patient* p) const;
    void showPatient(const string& ID) const;
    researcher* searchDocResearcherByEmplySrlNum(int serialNum);

    void printDepartmentsList() const;
    const Department* findDepartmentWithMaxPatients() const;
    void saveToBinaryFile(ofstream& outputFile) const;
};