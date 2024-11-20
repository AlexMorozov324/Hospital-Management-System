#pragma once

#include "Person.h"
#include <string>

class Staff : public Person
{
protected:
	int m_employeeSerialNumber;

	static int nextEmployeeSerialNum; // this will be an global variable using for automatically setting up the serial numbers of the different workers within the hospital.

	Staff(const Staff& other) = default;
	Staff(Staff&& other) = default;
	const Staff& operator=(Staff&& other);
	const Staff& operator=(const Staff& other);

public:
	Staff(const Person& person) noexcept(false);
	Staff(const string& name) noexcept(false);
	Staff(ifstream& inputFile);


	void setEmployeeSerialNumber();
	int getEmployeeSerialNumber() const;
	static int getGlobalNextEmployeeSerialNumber();
	static void setGlobalNextEmployeeSerialNumber(int newEmployeeSerialNum);
	friend ostream& operator<<(ostream& os, const Staff& staff);
	virtual void saveToBinaryFile(ofstream& outputFile) const override;
	void saveTypeToBinaryFile(ofstream& outputFile) const;
	static void getTypefromBinaryFile(ifstream& inputFile, string& typeStr);
};

