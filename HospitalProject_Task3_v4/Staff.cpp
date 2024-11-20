#include "Staff.h"

int Staff::nextEmployeeSerialNum = 1; // initilazing the global variable

Staff::Staff(const Person& person)
	: Person(person)
{
	setEmployeeSerialNumber();
}

Staff::Staff(const string& name)
	: Person(name)
{
	setEmployeeSerialNumber();
}

Staff::Staff(ifstream& inputFile)
	: Person(inputFile)
{
	inputFile.read((char*)&m_employeeSerialNumber, sizeof(m_employeeSerialNumber));
}

//  Sets the employee serial number of the Nurse.
void Staff::setEmployeeSerialNumber()
{
	m_employeeSerialNumber = nextEmployeeSerialNum;
	nextEmployeeSerialNum++;
}

int Staff::getEmployeeSerialNumber() const
{
	return m_employeeSerialNumber;
}

int Staff::getGlobalNextEmployeeSerialNumber()
{
	return nextEmployeeSerialNum;
}

void Staff::setGlobalNextEmployeeSerialNumber(int newEmployeeSerialNum)
{
	nextEmployeeSerialNum = newEmployeeSerialNum;
}


ostream& operator<<(ostream& os, const Staff& staff)
{
	os << (Person&)staff << ", his Employee ID is - " << staff.m_employeeSerialNumber;
	return os;
}

void Staff::saveToBinaryFile(ofstream& outputFile) const
{
	Person::saveToBinaryFile(outputFile);
	outputFile.write((const char*)&m_employeeSerialNumber, sizeof(m_employeeSerialNumber));
}

void Staff::saveTypeToBinaryFile(ofstream& outputFile) const
{
	int typeSize = strlen(typeid(*this).name());
	outputFile.write((const char*)&typeSize, sizeof(typeSize));
	outputFile.write(typeid(*this).name(), (typeSize * sizeof(char)));
}

void Staff::getTypefromBinaryFile(ifstream& inputFile, string& typeStr)
{
	int typeSize;
	inputFile.read((char*)&typeSize, sizeof(typeSize));
	{
		char* buffer = new char[typeSize];
		inputFile.read(buffer, typeSize);
		typeStr = string(buffer, typeSize);
		delete[] buffer;
	}
}