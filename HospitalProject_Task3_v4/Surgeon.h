#ifndef __Surgeon_H
#define __Surgeon_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Doctor.h"

class Surgeon : virtual public Doctor
{
protected:
	int m_numOfSurgeries;

	Surgeon(const Surgeon& other) = default;
	Surgeon(Surgeon&& other) = default;
	const Surgeon& operator=(const Surgeon& other);
	const Surgeon& operator=(Surgeon&& other);

public:
	Surgeon(const Doctor& doctor, int numOfSurgeries = 0) noexcept(false);
	Surgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg) noexcept(false);
	Surgeon(ifstream& inputFile);
	void setNumOfSurgeries(int numOfSurgeries) noexcept(false);

	int getNumOfSurgeries() const;
	static Surgeon* makeNewDoctorSurgeonPtr(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg);
	virtual void show() const;
	friend ostream& operator<<(ostream& os, const Surgeon& surgeon);
	virtual void saveToBinaryFile(ofstream& outputFile) const override;
};

#endif  // __Surgeon_H