#include "visit.h"

// Constructor for the visit class.
visit::visit(const patient& patient, const Date& arrivingDate, const string& visitReason, Doctor* doctor)
	: m_patient(patient), m_arrivingDate(arrivingDate), m_doctor(doctor)
{
	setVisitReason(visitReason);
}

// Destructor for the visit class.
visit::~visit()
{
}

visit::visit(const visit& other)
	: m_arrivingDate(other.m_arrivingDate), m_patient(other.m_patient), m_visitReason(other.m_visitReason), m_doctor(other.m_doctor)
{
}

visit::visit(visit&& other)
	: m_arrivingDate(other.m_arrivingDate), m_patient(other.m_patient), m_doctor(other.m_doctor)
{
	m_visitReason = other.m_visitReason;
	other.m_visitReason = nullptr;
}

// Sets the reason for the visit.
void visit::setVisitReason(const string& visitReason)
{
	int len = visitReason.length();
	if ((len >= MAX_VISIT_REASON_SIZE) || (len == 0))
		throw invalid_argument("Invalid visit reason value!");
	m_visitReason = visitReason;
}

// Displays the details of the visit on the console.
void visit::show() const
{
	cout << "The visit date is: ";
	m_arrivingDate.show();
	cout << ", under the head doctor: ";
	cout << m_doctor->getName();
	cout << ",and the visit reason is: " << m_visitReason << endl;
}

// Creates a new visit object dynamically and returns a pointer to it.
visit* visit::makeNewVisitPtr(const patient& newVisitPatient, const Department& department, const Date& date, const string& visitReason, Doctor* newVisitDoctor)
{
	visit* newVisitPtr = new visit(newVisitPatient, date, visitReason, newVisitDoctor);
	return newVisitPtr;
}

