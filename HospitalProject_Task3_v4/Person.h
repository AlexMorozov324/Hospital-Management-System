#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <string>
#include <fstream>

class Person
{
protected:
	string m_name;
	
	Person(Person&& other) = default;
	Person(const Person& other) = default;
	const Person& operator=(Person&& other);
	const Person& operator=(const Person& other);

public:
	Person(const string& name) noexcept(false);
	Person(ifstream& inputFile);

	void setName(const string& name) noexcept(false);

	const string& getName() const;
	friend ostream& operator<<(ostream& os, const Person& person);
	virtual void saveToBinaryFile(ofstream& outputFile) const;
};

