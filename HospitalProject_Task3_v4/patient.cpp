#include "patient.h"

patient::patient(const string& name, const string& id, int yearOfBirth, int gender)
	: Person(name)
{
	setID(id);;
	setYearOfBirth(yearOfBirth);
	setGender((eGender)gender);
}

patient::~patient()
{
	for (int i = 0; i < m_visitsPtrsVector.size(); i++)
		delete m_visitsPtrsVector[i];
}

// Sets the ID of the patient.
void patient::setID(const string& id)
{
	int len = id.length();
	if (len != ID_LENGTH)
		throw invalid_argument("Invalid ID value!");
	m_id = id;
}

// Sets the year of birth of the patient.
void patient::setYearOfBirth(int yearOfBirth) noexcept(true)
{
	m_yearOfBirth = yearOfBirth;
}

// Sets the gender of the patient.
void patient::setGender(eGender gender)
{
	if ((gender != 0) && (gender != 1))
		throw invalid_argument("Invalid gender value!");
	m_gender = gender;
}

// Gets the ID of the patient.
const string& patient::getID() const
{
	return m_id;
}

// Gets the year of birth of the patient.
const int patient::getYearOfBirth() const
{
	return m_yearOfBirth;
}

// Gets the array of pointers to visit objects.
const vector<visit*>& patient::getVisitsPtrsVector()
{
	return m_visitsPtrsVector;
}

// Creates a new patient object dynamically and returns a pointer to it.
patient* patient::makeNewPatientPtr(const string& patietnID, const string& newPatientName, int newPatientYearOfBirth, eGender newPatientGender)
{
	patient* newPatientPtr = new patient(newPatientName, patietnID, newPatientYearOfBirth, newPatientGender);
	return newPatientPtr;
}

// Adds a new visit to the patient's visit history.
void patient::addVisitToArr(visit* newVisitPtr)
{
	int currVectorSize = m_visitsPtrsVector.size();
	if (currVectorSize == m_visitsPtrsVector.capacity())
		m_visitsPtrsVector.reserve(currVectorSize * 2);
	m_visitsPtrsVector.push_back(newVisitPtr);
}

// Displays the details of the patient.
void patient::show() const
{
	cout << "\nThe patient name is: " << this->getName() << ", the id is: " << m_id << ", the year of birth is: " << m_yearOfBirth << ", the gender is: ";
	if (m_gender == MALE)
		cout << "Male\n";
	else // m_gender == FEMALE
		cout << "Female\n";
}

bool patient::operator==(const string& patientId) const
{
	if (m_id == patientId)
		return true;
	else
		return false;
}