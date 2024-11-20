#include "Nurse.h"

// Constructor for the Nurse class.
Nurse::Nurse(const string& nameOfNurse, int yearsOfExperienceOfNurse)
	: Staff(nameOfNurse)
{
	setYearsOfExperience(yearsOfExperienceOfNurse);
}

Nurse::Nurse(const Staff& staff, int yearsOfExperienceOfNurse)
	: Staff(staff)
{
	setYearsOfExperience(yearsOfExperienceOfNurse);
}

Nurse::Nurse(ifstream& inputFile)
	: Staff(inputFile)
{
	inputFile.read((char*)&yearsOfExperience, sizeof(yearsOfExperience));
}

// Gets the years of experience of the Nurse.
int Nurse::getYearsOfExperience() const
{
	return yearsOfExperience;
}

// Sets the years of experience of the Nurse.
void Nurse::setYearsOfExperience(int yearsOfExperienceOfNurse)
{
	if (yearsOfExperienceOfNurse < 0)
		throw invalid_argument("Invalid years of experience value!");
	yearsOfExperience = yearsOfExperienceOfNurse;
}

// Creates a new Nurse object dynamically and returns a pointer to it.
Nurse* Nurse::makeNewNursePtr(const string& newNurseName, int numberOfExperienceYears)
{
	Nurse* newNursePtr = new Nurse(newNurseName, numberOfExperienceYears);
	return newNursePtr;
}

// Displays the details of the Nurse.
void Nurse::show() const
{
	cout << "The Nurse ";
	cout << *this << endl;
}

ostream& operator<<(ostream& os, const Nurse& nurse)
{
	os << (Staff&)nurse << ", and she has " << nurse.yearsOfExperience << " years of experience.";
	return os;
}

void Nurse::saveToBinaryFile(ofstream& outputFile) const
{
	Staff::saveToBinaryFile(outputFile);
	outputFile.write((const char*)&yearsOfExperience, sizeof(yearsOfExperience));
}