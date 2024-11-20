#ifndef __DoctorResercherSurgeon_H
#define __DoctorResercherSurgeon_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

#include "Surgeon.h"
#include "researcher.h"

class DoctorResercherSurgeon : public Surgeon, public researcher
{
protected:
	DoctorResercherSurgeon(const DoctorResercherSurgeon& other) = default;
	DoctorResercherSurgeon(DoctorResercherSurgeon&& other) = default;
	const DoctorResercherSurgeon& operator=(const DoctorResercherSurgeon& other);
	const DoctorResercherSurgeon& operator=(DoctorResercherSurgeon&& other);

public:
	DoctorResercherSurgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg);
	DoctorResercherSurgeon(ifstream& inputFile);


	static DoctorResercherSurgeon* makeNewDoctorResercherSurgeonPtr(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg);
	virtual void show() const;
	friend ostream& operator<<(ostream& os, const DoctorResercherSurgeon& DoctorResercherSurgeon);
	virtual void saveToBinaryFile(ofstream& outputFile) const override;
};

#endif  // __DoctorResercher_H