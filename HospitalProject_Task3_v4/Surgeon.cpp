#include "Surgeon.h"

Surgeon::Surgeon(const Doctor& doctor, int numOfSurgeries)
	: Staff(doctor), Doctor(doctor)
{
	setNumOfSurgeries(numOfSurgeries);
}

Surgeon::Surgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg)
	: Staff(newDoctorName), Doctor(newDoctorName, newDoctorspecialization)
{
	setNumOfSurgeries(numOfSurg);
}


Surgeon::Surgeon(ifstream& inputFile)
	: Staff(inputFile), Doctor(inputFile)
{
	inputFile.read((char*)&m_numOfSurgeries, sizeof(m_numOfSurgeries));
}

void Surgeon::setNumOfSurgeries(int numOfSurgeries)
{
	if (numOfSurgeries < 0)
		throw invalid_argument("Invalid num of surgeries value!");
	m_numOfSurgeries = numOfSurgeries;
}

int Surgeon::getNumOfSurgeries() const
{
	return m_numOfSurgeries;
}

Surgeon* Surgeon::makeNewDoctorSurgeonPtr(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg)
{
	Surgeon* newDoctorSurgeonPtr = new Surgeon(newDoctorName, newDoctorspecialization, numOfSurg);
	return newDoctorSurgeonPtr;
}

void Surgeon::show() const
{
	cout << "The Surgeon ";
	cout << *this << endl;
}

ostream& operator<<(ostream& os, const Surgeon& surgeon)
{
	os << (Doctor&)surgeon << ", his number of surgeries is: " << surgeon.m_numOfSurgeries;
	return os;
}

void Surgeon::saveToBinaryFile(ofstream& outputFile) const
{
	Doctor::saveToBinaryFile(outputFile);
	outputFile.write((const char*)&m_numOfSurgeries, sizeof(m_numOfSurgeries));
}