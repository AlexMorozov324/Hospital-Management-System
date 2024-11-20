#include "Department.h"
#include "Hospital.h"
#include <fstream>
#include "Surgeon.h"
#include "DoctorResercher.h"
#include "DoctorResercherSurgeon.h"
class Surgeon;
class DoctorResercher;
class DoctorResercherSurgeon;
using namespace std;

// Constructor for the Department class.
Department::Department(const string& nameOfDep)
{
	setName(nameOfDep);
}

Department::Department(ifstream& inputFile)
{
	int nameStrSize;
	inputFile.read((char*)&nameStrSize, sizeof(nameStrSize));
	{
		char* buffer = new char[nameStrSize];
		inputFile.read(buffer, nameStrSize);
		name = string(buffer, nameStrSize);
		delete[] buffer;
	}
	int numOfDoctors;
	inputFile.read((char*)&numOfDoctors, sizeof(numOfDoctors));
	doctorsPtrsVector.reserve(numOfDoctors);
	string currDocType;
	for (int i = 0; i < numOfDoctors; i++)
	{
		Staff::getTypefromBinaryFile(inputFile, currDocType);
		if(strcmp(currDocType.data(), typeid(Doctor).name()) == 0)
			doctorsPtrsVector.push_back(new Doctor(inputFile));
		else if(strcmp(currDocType.data(), typeid(Surgeon).name()) == 0)
			doctorsPtrsVector.push_back(new Surgeon(inputFile));
		else if(strcmp(currDocType.data(), typeid(DoctorResercher).name()) == 0)
			doctorsPtrsVector.push_back(new DoctorResercher(inputFile));
		else if (strcmp(currDocType.data(), typeid(DoctorResercherSurgeon).name()) == 0)
			doctorsPtrsVector.push_back(new DoctorResercherSurgeon(inputFile));
	}
	int numOfNurses;
	inputFile.read((char*)&numOfNurses, sizeof(numOfNurses));
	nursesPtrsVector.reserve(numOfNurses);
	for (int i = 0; i < numOfNurses; i++)
		nursesPtrsVector.push_back(new Nurse(inputFile));
}


// Destructor for the Department class to release dynamically allocated memory.
Department::~Department()
{
	for (Doctor* docPtr : doctorsPtrsVector)
		delete docPtr;

	for (Nurse* nursePtr : nursesPtrsVector)
		delete nursePtr;

	for (patient* patientPtr : patientsPtrsVector)
		delete patientPtr;
}

// Sets the name of the department.
void Department::setName(const string& nameOfDep)
{
	int len = nameOfDep.length();
	if(len == 0)
		throw invalid_argument("Invalid name value!");
	name = nameOfDep;
}

// Gets the vector of pointers to Doctor objects.
const vector<Doctor*>& Department::getDoctorsPtrsVector()
{
	return doctorsPtrsVector;
}

// Gets the vector of pointers to Nurse objects.
const vector<Nurse*>& Department::getNursesPtrsVector()
{
	return nursesPtrsVector;
}

// Gets the vector of pointers to patient objects.
const vector<patient*>& Department::getPatientsPtrsVector()
{
	return patientsPtrsVector;
}

const string& Department::getName() const
{
	return name;
}

int Department::getNumOfPatients() const
{
	return patientsPtrsVector.size();
}

const Department& Department::operator+=(Doctor* newDoctorPtr)
{
	addDoctorToArr(newDoctorPtr);
	return *this;
}

//  Adds a Doctor pointer to the Doctor vector.
void Department::addDoctorToArr(Doctor* newDoctorPtr)
{
	int currVectorSize = doctorsPtrsVector.size();
	if (currVectorSize == doctorsPtrsVector.capacity())
		doctorsPtrsVector.reserve(currVectorSize * 2);
	doctorsPtrsVector.push_back(newDoctorPtr);
}

const Department& Department::operator+=(Nurse* newNursePtr)
{
	addNurseToArr(newNursePtr);
	return *this;
}

// Adds a Nurse pointer to the Nurse vector.
void Department::addNurseToArr(Nurse* newNursePtr)
{
	int currVectorSize = nursesPtrsVector.size();
	if (currVectorSize == nursesPtrsVector.capacity())
		nursesPtrsVector.reserve(currVectorSize * 2);
	nursesPtrsVector.push_back(newNursePtr);
}

const Department& Department::operator+=(patient* newPatientPtr)
{
	addPatientToArr(newPatientPtr);
	return *this;
}

// Adds a patient pointer to the patient vector.
void Department::addPatientToArr(patient* newPatientPtr)
{
	int currVectorSize = patientsPtrsVector.size();
	if (currVectorSize == patientsPtrsVector.capacity())
		patientsPtrsVector.reserve(currVectorSize * 2);
	patientsPtrsVector.push_back(newPatientPtr);
}

void Department::printDoctorsArr() const
{
	int i = 0;
	for (Doctor* docPtr : doctorsPtrsVector)
	{
		cout << i << " - " << docPtr->getName() << endl;
		i++;
	}
}

void Department::saveToBinaryFile(ofstream& outputFile) const
{
	int nameStrSize = name.size();
	outputFile.write((const char*)&nameStrSize, sizeof(nameStrSize));
	outputFile.write((const char*)name.data(), (nameStrSize * sizeof(char)));
	int numOfDoctors = doctorsPtrsVector.size();
	outputFile.write((const char*)&numOfDoctors, sizeof(numOfDoctors));
	for (Doctor* doctorPtr : doctorsPtrsVector)
	{
		doctorPtr->saveTypeToBinaryFile(outputFile);
		doctorPtr->saveToBinaryFile(outputFile);
	}
	int numOfNurses = nursesPtrsVector.size();
	outputFile.write((const char*)&numOfNurses, sizeof(numOfNurses));
	for (Nurse* nursePtr : nursesPtrsVector)
		nursePtr->saveToBinaryFile(outputFile);
}
