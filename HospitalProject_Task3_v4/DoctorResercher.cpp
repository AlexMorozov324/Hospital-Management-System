#include "DoctorResercher.h"

DoctorResercher::DoctorResercher(const string& newDoctorName, const string& newDoctorspecialization)
	: Staff(newDoctorName), Doctor(newDoctorName, newDoctorspecialization), researcher(newDoctorName)
{
}

DoctorResercher::DoctorResercher(ifstream& inputFile)
	: Staff(inputFile), Doctor(inputFile), researcher(inputFile)
{
}

DoctorResercher* DoctorResercher::makeNewDoctorResercherPtr(const string& newDoctorName, const string& newDoctorspecialization)
{
	DoctorResercher* newDoctorSurgeonPtr = new DoctorResercher(newDoctorName, newDoctorspecialization);
	return newDoctorSurgeonPtr;
}


void DoctorResercher::show() const
{
	cout << "The Doctor-Resercher ";
	cout << *this << endl;
	int numOfArticles = m_articlesPtrsArr.getArrLogSize();
	if (numOfArticles > 0)
	{
		cout << ", and this is the aritcles published list:" << endl;
		for (int i = 0; i < numOfArticles; i++)
			m_articlesPtrsArr[i]->show();
	}
}

ostream& operator<<(ostream& os, const DoctorResercher& DoctorResercher)
{
	os << (Doctor&)DoctorResercher;
	return os;
}

void DoctorResercher::saveToBinaryFile(ofstream& outputFile) const
{
	Doctor::saveToBinaryFile(outputFile);
	researcher::saveToBinaryFile(outputFile, true);
}