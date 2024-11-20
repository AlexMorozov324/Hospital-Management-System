#pragma once

#include "researcher.h"
//#include "Hospital.h"
#include <vector>

class Hospital;
class researcher;

class researchInstitute
{
protected:
	vector<researcher*> m_researchersPtrsVector;

	researchInstitute(const researchInstitute& other); // disabling copy c'tor option, becasue we don't want to duplicate research institute
	researchInstitute(researchInstitute&& other); // disabling move c'tor option, becasue we don't want to duplicate research institute
	const researchInstitute& operator=(const researchInstitute& other);
	const researchInstitute& operator=(researchInstitute&& other);

public:
	researchInstitute() noexcept(true);
	researchInstitute(ifstream& inputFile, Hospital& hospital);
	~researchInstitute();

	const vector<researcher*>& getResearchersPtrsVector() const;

	void show() const;
	const researchInstitute& operator+=(researcher* newResearcherPtr);
	void addResearcherToArr(researcher* newResearcherPtr);
	void printResearchersList() const;
	void saveToBinaryFile(ofstream& outputFile) const;
};