#include "researchInstitute.h"
#include "DoctorResercher.h" 
#include "DoctorResercherSurgeon.h"

// Constructor for the researchInstitute class.
researchInstitute::researchInstitute() noexcept(true)
{
}

researchInstitute::researchInstitute(ifstream& inputFile, Hospital& hospital)
{
	int numOfResearchers;
	inputFile.read((char*)&numOfResearchers, sizeof(numOfResearchers));
	m_researchersPtrsVector.reserve(numOfResearchers);
	string currResearcherType;
	int currSerialNum;
	researcher* existingResearcherPtr = nullptr;
	for (int i = 0; i < numOfResearchers; i++)
	{
		Staff::getTypefromBinaryFile(inputFile, currResearcherType);
		if (strcmp(currResearcherType.data(), typeid(researcher).name()) == 0)
			m_researchersPtrsVector.push_back(new researcher(inputFile));
		else if((strcmp(currResearcherType.data(), typeid(DoctorResercher).name()) == 0) || (strcmp(currResearcherType.data(), typeid(DoctorResercherSurgeon).name()) == 0))
		{
			researcher temp(inputFile); // this data was written twice, so it needs to be read again, but it will be deleted so their won't be double pointings in the resInst. instead the existing pointer will be added to the vector.
			currSerialNum = temp.getEmployeeSerialNumber();
			existingResearcherPtr = hospital.searchDocResearcherByEmplySrlNum(currSerialNum);
			m_researchersPtrsVector.push_back(existingResearcherPtr);
		}
	}
}

// Destructor for the researchInstitute class.
researchInstitute::~researchInstitute()
{
	for (researcher* researcherPtr : m_researchersPtrsVector)
		if ((typeid(DoctorResercher) != typeid(*(researcherPtr))) && (typeid(DoctorResercherSurgeon) != typeid(*(researcherPtr))))
			delete researcherPtr;
}

// Gets the array of pointers to researcher objects representing the researchers in the research institute.
const vector<researcher*>& researchInstitute::getResearchersPtrsVector() const
{
	return m_researchersPtrsVector;
}

// Displays the details of the research institute on the console.
void researchInstitute::show() const
{
	cout << "The research institute researchers list is:" << endl;

	for (researcher* researcherPtr : m_researchersPtrsVector)
		researcherPtr->show();
}

const researchInstitute& researchInstitute::operator+=(researcher* newResearcherPtr)
{
	addResearcherToArr(newResearcherPtr);
	return *this;
}

// Adds a new researcher to the research institute.
void researchInstitute::addResearcherToArr(researcher* newResearcherPtr)
{
	int currVectorSize = m_researchersPtrsVector.size();
	if (currVectorSize == m_researchersPtrsVector.capacity())
		m_researchersPtrsVector.reserve(currVectorSize * 2);
	m_researchersPtrsVector.push_back(newResearcherPtr);
}

// Prints the list of researchers in the research institute.
void researchInstitute::printResearchersList() const
{
	int i = 0;
	for (researcher* researcherPtr : m_researchersPtrsVector)
	{
		cout << i << " - " << researcherPtr->getName() << endl;
		i++;
	}
}

void researchInstitute::saveToBinaryFile(ofstream& outputFile) const
{
	int numOfResearchers = m_researchersPtrsVector.size();
	outputFile.write((const char*)&numOfResearchers, sizeof(numOfResearchers));
	for (researcher* researcherPtr : m_researchersPtrsVector)
	{
		if (typeid(*researcherPtr) == typeid(researcher))
		{
			researcherPtr->saveTypeToBinaryFile(outputFile);
			researcherPtr->saveToBinaryFile(outputFile, false);
		}
		else
			researcherPtr->saveToBinaryFile(outputFile, true);
	}
}