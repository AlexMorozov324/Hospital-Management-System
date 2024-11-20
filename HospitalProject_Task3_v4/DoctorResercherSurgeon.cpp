#include "DoctorResercherSurgeon.h"

DoctorResercherSurgeon::DoctorResercherSurgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg)
	: Staff(newDoctorName), Doctor(newDoctorName, newDoctorspecialization), Surgeon(newDoctorName, newDoctorspecialization, numOfSurg), researcher(newDoctorName)
{
}

DoctorResercherSurgeon::DoctorResercherSurgeon(ifstream& inputFile)
	: Staff(inputFile), Doctor(inputFile), Surgeon(inputFile), researcher(inputFile)
{
}

DoctorResercherSurgeon* DoctorResercherSurgeon::makeNewDoctorResercherSurgeonPtr(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg)
{
	DoctorResercherSurgeon* newDoctorResercherSurgeonPtr = new DoctorResercherSurgeon(newDoctorName, newDoctorspecialization, numOfSurg);
	return newDoctorResercherSurgeonPtr;
}

void DoctorResercherSurgeon::show() const
{
	cout << "The Surgeon-Doctor-Resercher ";
	cout << *this << endl;
	int numOfArticles = m_articlesPtrsArr.getArrLogSize();
	if (numOfArticles > 0)
	{
		cout << ", and this is the aritcles published list:" << endl;
		for (int i = 0; i < numOfArticles; i++)
			m_articlesPtrsArr[i]->show();
	}
}

ostream& operator<<(ostream& os, const DoctorResercherSurgeon& DoctorResercherSurgeon)
{
	os << (Surgeon&)DoctorResercherSurgeon;
	return os;
}

void DoctorResercherSurgeon::saveToBinaryFile(ofstream& outputFile) const
{
	Surgeon::saveToBinaryFile(outputFile);
	researcher::saveToBinaryFile(outputFile, true);
}