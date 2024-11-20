#ifndef __patient_H
#define __patient_H

#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"
#include "visit.h"

#include <vector>

class visit;

class patient : public Person
{
public:
	static const int ID_LENGTH = 9;
	enum eGender { MALE, FEMALE };

private:
	string m_id;
	int m_yearOfBirth;
	int m_gender;

	vector<visit*> m_visitsPtrsVector;

	patient(const patient& other);
	patient(patient&& other);
	const patient& operator=(const patient& other);
	const patient& operator=(patient&& other);

public:
	patient(const string& name, const string& id, int yearOfBirth, int m_gender) noexcept(false);
	~patient();

	void setID(const string& id) noexcept(false);
	void setYearOfBirth(int yearOfBirth) noexcept(true);
	void setGender(eGender gender) noexcept(false);

	const string& getID() const;
	const int getYearOfBirth() const;

	const vector<visit*>& getVisitsPtrsVector();
	static patient* makeNewPatientPtr(const string& patietnID, const string& newPatientName, int newPatientYearOfBirth, eGender newPatientGender);

	void addVisitToArr(visit* newVisitPtr);
	void show() const;
	bool operator==(const string& patientId) const;
};

#endif // __patient_H

