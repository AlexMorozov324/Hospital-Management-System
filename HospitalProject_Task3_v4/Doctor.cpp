#include "Doctor.h"
using namespace std;

const char* doctorsTypesStrings[] = { "", "Regular doctor", "Surgeon doctor", "Researcher doctor", "Researcher surgeon doctor" };

// Constructor for the Doctor class.
Doctor::Doctor(const string& nameOfDoc, const string& specializationOfDoc)
	: Staff(nameOfDoc)
{
	setSpecialization(specializationOfDoc);
}

Doctor::Doctor(const Staff& staff, const string& specializationOfDoc)
	: Staff(staff)
{
	setSpecialization(specializationOfDoc);
}

Doctor::Doctor(ifstream& inputFile)
	: Staff(inputFile)
{
	int specStrSize;
	inputFile.read((char*)&specStrSize, sizeof(specStrSize));
	{
		char* buffer = new char[specStrSize];
		inputFile.read(buffer, specStrSize);
		specialization = string(buffer, specStrSize);
		delete[] buffer;
	}
}

// Gets the specialization of the Doctor.
const string& Doctor::getSpecialization() const
{
	return specialization;
}

// // Sets the specialization of the Doctor and returning true if succeeded or false otherwise
void Doctor::setSpecialization(const string& specializationOfDoc)
{
	int len = specializationOfDoc.length();
	if (len == 0)
		throw invalid_argument("Invalid specialization value!");
	specialization = specializationOfDoc;
}

// Creates a new Doctor object dynamically and returns a pointer to it.
Doctor* Doctor::makeNewDoctorPtr(const string& newDoctorName, const string& newDoctorspecialization)
{
	Doctor* newDoctorPtr = new Doctor(newDoctorName, newDoctorspecialization);
	return newDoctorPtr;
}

// Displays the details of the Doctor on the console.
void Doctor::show() const
{
	cout << "The Doctor ";
	cout << *this << endl;
}

ostream& operator<<(ostream& os, const Doctor& doctor)
{
	os << (Staff&)doctor << ", his specialization is: " << doctor.specialization;
	return os;
}

// this function is a global function which is logically related to this class, but can be called even without an exciting instance of a doctor
void Doctor::printDoctorsTypes()
{
	cout << "What kind of doctor would you like to add?" << endl;
	for (int i = REGULAR_DOCTOR; i <= RESEARCHER_SURGEON_DOCTOR; i++)
		cout << i << ". " << doctorsTypesStrings[i] << endl;
}

void Doctor::saveToBinaryFile(ofstream& outputFile) const
{
	Staff::saveToBinaryFile(outputFile);
	int specStrSize = specialization.size();
	outputFile.write((const char*)&specStrSize, sizeof(specStrSize));
	outputFile.write((const char*)specialization.data(), (specStrSize * sizeof(char)));
}

