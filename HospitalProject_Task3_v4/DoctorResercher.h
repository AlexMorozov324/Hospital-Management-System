#ifndef __DoctorResercher_H
#define __DoctorResercher_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

#include "Doctor.h"
#include "researcher.h"

class DoctorResercher : public Doctor, public researcher
{
protected:
	DoctorResercher(const DoctorResercher& other) = default;
	DoctorResercher(DoctorResercher&& other) = default;
	const DoctorResercher& operator=(const DoctorResercher& other);
	const DoctorResercher& operator=(DoctorResercher&& other);

public:
	DoctorResercher(const string& newDoctorName, const string& newDoctorspecialization);
	DoctorResercher(ifstream& inputFile);


	static DoctorResercher* makeNewDoctorResercherPtr(const string& newDoctorName, const string& newDoctorspecialization);
	virtual void show() const;
	friend ostream& operator<<(ostream& os, const DoctorResercher& DoctorResercher);
	virtual void saveToBinaryFile(ofstream& outputFile) const override;
};

#endif  // __DoctorResercher_H