#include "Person.h"
using namespace std;

Person::Person(const string& name)
{
	setName(name);
}

Person::Person(ifstream& inputFile)
{
	int nameStrSize;
	inputFile.read((char*)&nameStrSize, sizeof(nameStrSize));
	{
		char* buffer = new char[nameStrSize];
		inputFile.read(buffer, nameStrSize);
		m_name = string(buffer, nameStrSize);
		delete[] buffer;
	}
}

void Person::setName(const string& name)
{
	int len = name.length();
	if (len == 0)
		throw invalid_argument("Invalid name value! name can't be empty");
	m_name = name;
}

const string& Person::getName() const
{
	return m_name;
}

ostream& operator<<(ostream& os, const Person& person)
{
	os << "name is " << person.getName();
	return os;
}

void Person::saveToBinaryFile(ofstream& outputFile) const
{
	int nameStrSize = m_name.size();
	outputFile.write((const char*)&nameStrSize, sizeof(nameStrSize));
	outputFile.write((const char*)m_name.data(), (nameStrSize * sizeof(char)));
}