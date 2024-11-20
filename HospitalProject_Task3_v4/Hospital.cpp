#include <algorithm>
#include <fstream>
#include "Hospital.h"
#include "Surgeon.h"
#include "DoctorResercher.h"
#include "DoctorResercherSurgeon.h"
#include "Surgery.h"

// Constructor for the Hospital class.
Hospital::Hospital()
{
	m_resInst = new researchInstitute();
}

Hospital::Hospital(ifstream& inputFile)
{
	int numOfDepartments;
	inputFile.read((char*)&numOfDepartments, sizeof(numOfDepartments));
	m_DepartmentsPtrsVector.reserve(numOfDepartments);
	for (int i = 0; i < numOfDepartments; i++)
		m_DepartmentsPtrsVector.push_back(new Department(inputFile));
	m_resInst = new researchInstitute(inputFile, *this);
	int currGlobalNextEmployeeSerialNumber;
	inputFile.read((char*)&currGlobalNextEmployeeSerialNumber, sizeof(currGlobalNextEmployeeSerialNumber));
	Staff::setGlobalNextEmployeeSerialNumber(currGlobalNextEmployeeSerialNumber);
}

// Destructor for the Hospital class for releasing dinamic allocated memory.
Hospital::~Hospital()
{
	delete m_resInst;
	for (Department* departmentPtr : m_DepartmentsPtrsVector)
		delete departmentPtr;
}

// Prints the list of available options in the menu.
void Hospital::printOptionsMenu() const
{
	cout << ADD_DEPARTMENT << " - Add new department to the hospital." << endl;
	cout << ADD_NURSE << " - Add new nurse to one of the hospital departments." << endl;
	cout << ADD_DOCTOR << " - Add new doctor to one of the hospital departments." << endl;
	cout << ADD_VISIT << " - Add new visit of a patient in the hospital." << endl;
	cout << ADD_RESEARCHER << " - Add new researcher to the hospital research institute." << endl;
	cout << ADD_ARTICLE << " - Add new article to one of the researchers in the hospital research institute." << endl;
	cout << SHOW_DEPARTMENT_PATIENTS << " - Show all patients in one of the hospital departments." << endl;
	cout << SHOW_ALL_EMPLOYEES << " - Show all employees in the hospital departments." << endl;
	cout << SHOW_ALL_RESEARCHERS << " - Show all researchers in the hospital research institute." << endl;
	cout << SHOW_ALL_RESEARCHERS_DOCTORS << " - Show all researchers who are also doctors in the hospital research institute." << endl;
	cout << FIND_PATIENT_BY_ID << " - Find a patient in the hospital by his/her ID, and print his/her visits list." << endl;
	cout << COMPARE_RESEARCHERS << " - Compare two researchers by their number of articles." << endl;
	cout << FIND_DEPARTMENT_WITH_MAX_PATIENTS << " - Find the deparment with the maximum amount of patients." << endl;
	cout << END_OF_INPUT << " - To finish entering new input." << endl;
}

// Gets the logical size of the Department array.
int Hospital::getNumOfDepartments() const
{
	return m_DepartmentsPtrsVector.size();
}

// Adds a new department to the Hospital.
void Hospital::addNewDepartment(const string& newDepartmentName)
{
	int currVectorSize = m_DepartmentsPtrsVector.size();
	if (currVectorSize == m_DepartmentsPtrsVector.capacity())
		m_DepartmentsPtrsVector.reserve(currVectorSize * 2);
	Department* newDepPtr = new Department(newDepartmentName);
	m_DepartmentsPtrsVector.push_back(newDepPtr);
}

// Gets the array of pointers to Department objects.
const vector<Department*>& Hospital::getDepartmentsPtrsVector() const
{
	return m_DepartmentsPtrsVector;
}

// Gets the array of pointers to Department objects.
vector<Department*>& Hospital::getDepartmentsPtrsVector()
{
	return m_DepartmentsPtrsVector;
}

const researchInstitute* Hospital::getResearchInstitutePtr() const
{
	return m_resInst;
}

const researcher& Hospital::getResearcher(int index) const
{
	return *(m_resInst->getResearchersPtrsVector()[index]);
}

// Adds a new Nurse to the Hospital.
void Hospital::addNewNurse(const string& newNurseName, int numberOfExperienceYears, int departmentToAddTo)
{
	Nurse* newNursePtr = Nurse::makeNewNursePtr(newNurseName, numberOfExperienceYears);
	*(m_DepartmentsPtrsVector[departmentToAddTo]) += newNursePtr;
}

// Adds a new Doctor to the Hospital.
void Hospital::addNewDoctor(const string& newDoctorName, const string& newDoctorspecialization, int departmentToAddTo)
{
	Doctor* newDoctorPtr = Doctor::makeNewDoctorPtr(newDoctorName, newDoctorspecialization);
	*(m_DepartmentsPtrsVector[departmentToAddTo]) += newDoctorPtr;
}

void Hospital::addNewDoctorSurgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg, int departmentToAddTo)
{
	Doctor* newDoctorSurgeonPtr = Surgeon::makeNewDoctorSurgeonPtr(newDoctorName, newDoctorspecialization, numOfSurg);
	*(m_DepartmentsPtrsVector[departmentToAddTo]) += newDoctorSurgeonPtr;
}

void Hospital::addNewDoctorResercher(const string& newDoctorName, const string& newDoctorspecialization, int departmentToAddTo)
{
	DoctorResercher* newDoctorResercherPtr = DoctorResercher::makeNewDoctorResercherPtr(newDoctorName, newDoctorspecialization);
	*(m_DepartmentsPtrsVector[departmentToAddTo]) += newDoctorResercherPtr;
	*(m_resInst) += newDoctorResercherPtr;
}

void Hospital::addNewDoctorResercherSurgeon(const string& newDoctorName, const string& newDoctorspecialization, int numOfSurg, int departmentToAddTo)
{
	DoctorResercherSurgeon* newDoctorResercherSurgeonPtr = DoctorResercherSurgeon::makeNewDoctorResercherSurgeonPtr(newDoctorName, newDoctorspecialization, numOfSurg);
	*(m_DepartmentsPtrsVector[departmentToAddTo]) += newDoctorResercherSurgeonPtr;
	*(m_resInst) += newDoctorResercherSurgeonPtr;
}

// Prints the list of departments in the Hospital.
void Hospital::printDepartmentsList() const
{
	int i = 0;
	for (Department* depPtr : m_DepartmentsPtrsVector)
	{
		cout << i << " - " << depPtr->getName() << endl;
		i++;
	}
}

// Adds a new researcher to the Hospital's research institute.
void Hospital::addNewResearcher(researcher* newResearcherPtr)
{
	m_resInst->addResearcherToArr(newResearcherPtr);
}
 
// Gets the total number of workers (doctors and nurses) in the Hospital.
int Hospital::getNumOfWorkers() const
{
	int sum = 0;
	for (Department* depPtr : m_DepartmentsPtrsVector)
		sum += depPtr->getDoctorsPtrsVector().size() + depPtr->getNursesPtrsVector().size();
	return sum;
}

// Gets the number of doctors in the Hospital.
int Hospital::getNumOfDoctors() const
{
	int sum = 0;
	for (Department* depPtr : m_DepartmentsPtrsVector)
		sum += depPtr->getDoctorsPtrsVector().size();
	return sum;
}

// Gets the number of nurses in the Hospital.
int Hospital::getNumOfNurses() const
{
	int sum = 0;
	for (Department* depPtr : m_DepartmentsPtrsVector)
		sum += depPtr->getNursesPtrsVector().size();
	return sum;
}

// Displays the details of all workers (doctors and nurses) in the Hospital.
void Hospital::showAllWorkers()
{
	if (m_DepartmentsPtrsVector.size() == 0)
	{
		cout << "There aren't any departments in the hospital, so there aren't any employess in the hospital in them to show as well. Please enter departments and employees first, and then try to show them." << endl;
		return;
	}
	else if (getNumOfWorkers() == 0)
	{
		cout << "there aren't any workers in the hospital at the moment." << endl;
		return;
	}
	else
	{
		for (Department* depPtr : m_DepartmentsPtrsVector)
		{
			cout << "The team members under '" << depPtr->getName() << "' department are:" << endl;
			vector<Doctor*> currDepDocsArr = depPtr->getDoctorsPtrsVector();
			vector<Nurse*> currDepNurseArr = depPtr->getNursesPtrsVector();

			if ((depPtr->getDoctorsPtrsVector().size() == 0) && (depPtr->getNursesPtrsVector().size() == 0))
				cout << "There are no team members in this department" << endl;
			else
			{
				for (Doctor* docPtr : depPtr->getDoctorsPtrsVector())
					docPtr->show();
				for (Nurse* nursePtr : depPtr->getNursesPtrsVector())
					nursePtr->show();
			}
			cout << endl;
		}
	}
}

// Displays the details of all researchers in the Hospital's research institute.
void Hospital::showAllReserchers()
{
	if (m_resInst->getResearchersPtrsVector().size() == 0)
	{
		cout << "there arent any reserchers in the hospital at the moment." << endl;
		return;
	}
	else
	{
		const vector<researcher*>& researchersVector = m_resInst->getResearchersPtrsVector();
		for (researcher* researcherPtr : researchersVector)
			researcherPtr->show();
	}
	return;
}

// Displays the details of all researchers-doctors in the Hospital's research institute.
void Hospital::showAllReserchersDoctors()
{
	if (getNumOfResercherDoctors() == 0)
	{
		cout << "there aren't any resercher - doctors in the hospital at the moment, Please enter resercher - doctors first, and then try to show them." << endl;
		return;
	}
	else
	{
		cout << "The resercher - doctors are: " << endl;
		for (Department* departmentPtr : m_DepartmentsPtrsVector)
		{
			const vector<Doctor*>& currDepDocsVector = departmentPtr->getDoctorsPtrsVector();
			for (Doctor* doctorPtr : currDepDocsVector)
			{
				DoctorResercher* temp1 = dynamic_cast<DoctorResercher*>(doctorPtr);
				if (temp1 != nullptr)
					temp1->show();
				else
				{
					DoctorResercherSurgeon* temp2 = dynamic_cast<DoctorResercherSurgeon*>(doctorPtr);
					if (temp2 != nullptr)
						temp2->show();
				}
			}
		}
		cout << endl;
	}
}

// Gets the number of resercher-doctors in the Hospital.
int Hospital::getNumOfResercherDoctors() const
{
	int sum = 0;
	for (Department* departmentPtr : m_DepartmentsPtrsVector)
	{
		const vector<Doctor*>& currDepDocsVector = departmentPtr->getDoctorsPtrsVector();
		for (Doctor* doctorPtr : currDepDocsVector)
		{
			DoctorResercher* temp1 = dynamic_cast<DoctorResercher*>(doctorPtr);
			if (temp1 != nullptr)
				sum++;
			else
			{
				DoctorResercherSurgeon* temp2 = dynamic_cast<DoctorResercherSurgeon*>(doctorPtr);
				if (temp2 != nullptr)
					sum++;
			}
		}
	}
	return sum;
}

// Adds a new article to a researcher's list of articles.
void Hospital::addArticle(article* newArticle, int ResearcherToAddTo)
{
	vector<researcher*> researchersArr = m_resInst->getResearchersPtrsVector();
	researchersArr[ResearcherToAddTo]->addArticleToArr(newArticle);
}

// Finds a patient by their ID and returns a pointer to it, or nullptr if not found.
patient* Hospital::findPatientByID(const string& id) const
{
	patient* resPatient = nullptr;
	auto customPredicate = [id](const patient* patientPtr) { // lambda expression for using the 'find_if' algorithm to search the patient by his id
		return *patientPtr == id;
	};
	for (Department* departmentPtr : m_DepartmentsPtrsVector)
	{
		vector<patient*> PatientsVectorInDepartment = departmentPtr->getPatientsPtrsVector();

		vector<patient*>::iterator foundItr = find_if(PatientsVectorInDepartment.begin(), PatientsVectorInDepartment.end(), customPredicate);
		if (foundItr != PatientsVectorInDepartment.end())
		{
			resPatient = *foundItr;
			break;
		}
	}
	return resPatient;
}

//  Adds a new visit to a patient's visit history.
void Hospital::addVisit(patient* patientPtr, const Date& newVisiDate, bool isNewPatient, int departmentToAddTo, const string& visitReason, const bool& needSurg, const int& surgeryRoom, const bool& tsum, Doctor* newVisitDoctor)
{
	if (isNewPatient == true)
		m_DepartmentsPtrsVector[departmentToAddTo]->addPatientToArr(patientPtr);

	visit* newVisitPtr = visit::makeNewVisitPtr(*patientPtr, *m_DepartmentsPtrsVector[departmentToAddTo], newVisiDate, visitReason, newVisitDoctor);
	if (needSurg == true)
	{
		Surgery* newSurgeryPtr = Surgery::makeNewSurgeryPtr(*newVisitPtr, surgeryRoom, tsum);
		patientPtr->addVisitToArr(newSurgeryPtr);
	}
	else
		patientPtr->addVisitToArr(newVisitPtr);
}

// Displays the patients in a department.
void Hospital::showDeparmentPatients(int choice) const
{
	Department* chosenDepartmentPtr = m_DepartmentsPtrsVector[choice];
	if (m_DepartmentsPtrsVector[choice]->getPatientsPtrsVector().size() == 0)
		cout << "there arent any parients in this Department." << endl;
	else
	{
		cout << "The list of the patient in " << chosenDepartmentPtr->getName() << " department is:" << endl;
		for (patient* patientPtr : chosenDepartmentPtr->getPatientsPtrsVector())
			patientPtr->show();
	}
}

// Shows the visit history of a patient.
void Hospital::showVisitHistory(patient* p) const
{
	vector<visit*> visitsPtrsVector = p->getVisitsPtrsVector();
	vector<visit*>::iterator itr = visitsPtrsVector.begin();
	vector<visit*>::iterator itrEnd = visitsPtrsVector.end();
	for (; itr < itrEnd; ++itr)
		(*itr)->show();
}

researcher* Hospital::searchDocResearcherByEmplySrlNum(int serialNum)
{
	vector<Doctor*> currDocsVector;
	for (Department* depPtr : m_DepartmentsPtrsVector)
	{
		currDocsVector = depPtr->getDoctorsPtrsVector();
		for (Doctor* docPtr : currDocsVector)
		{
			if (docPtr->getEmployeeSerialNumber() == serialNum)
				return (researcher*)docPtr;
		}
	}
	return nullptr;
}


// Displays the details of a patient.
void Hospital::showPatient(const string& ID) const
{
	patient* p = findPatientByID(ID);
	if (p == nullptr)
		cout << "There is no such patient with the id of: " << ID << " in the system" << endl;
	else
	{
		cout << "The patient details are: ";
		p->show();
		showVisitHistory(p);
	}
}

const Department* Hospital::findDepartmentWithMaxPatients() const
{
	vector<int> numOfPatientsInEachDep;
	numOfPatientsInEachDep.reserve(m_DepartmentsPtrsVector.size());
	for (Department* depPtr : m_DepartmentsPtrsVector)
		numOfPatientsInEachDep.push_back(depPtr->getPatientsPtrsVector().size());
	vector<int>::iterator itrMaxElem = std::max_element(numOfPatientsInEachDep.begin(), numOfPatientsInEachDep.end());
	int maxIndx = std::distance(numOfPatientsInEachDep.begin(), itrMaxElem);
	return m_DepartmentsPtrsVector[maxIndx];
}

void Hospital::saveToBinaryFile(ofstream& outputFile) const
{
	int numOfDepartments = m_DepartmentsPtrsVector.size();
	outputFile.write((const char*)&numOfDepartments, sizeof(numOfDepartments));
	for (Department* departmentPtr : m_DepartmentsPtrsVector)
		departmentPtr->saveToBinaryFile(outputFile);
	m_resInst->saveToBinaryFile(outputFile);
	int currGlobalNextEmployeeSerialNumber = Staff::getGlobalNextEmployeeSerialNumber();
	outputFile.write((const char*)&currGlobalNextEmployeeSerialNumber, sizeof(currGlobalNextEmployeeSerialNumber));
}