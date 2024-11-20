#ifndef __visit_H
#define __visit_H

#include "Date.h"
#include "Doctor.h"

class patient;
class Date;
class Doctor;
class Department;

class visit
{
protected:
	const patient& m_patient;
	const Date m_arrivingDate;
	string m_visitReason;
	Doctor* m_doctor;

	visit(const visit& other);
	visit(visit&& other);
	const visit& operator=(const visit& other);
	const visit& operator=(visit&& other);

public:
	static const int MAX_VISIT_REASON_SIZE = 101; // for simple getting the visit reason input

	visit(const patient& patient, const Date& arrivingDate, const string& visitReason, Doctor* doctor);
	~visit();

	void setVisitReason(const string& visitReason) noexcept(false);
	void show() const;

	static visit* makeNewVisitPtr(const patient& newVisitPatient, const Department& department, const Date& date, const string& visitReason, Doctor* newVisitDoctor);
};


#endif // __visit_H