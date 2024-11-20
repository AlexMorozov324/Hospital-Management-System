// developers details: 
// Rotem Waingart 316140078
// Alexander Morozov 324900216

// Program description:
// This project is building a Hospital Management System that enables efficient management of hospital operations, including departments, doctors, nurses, patients, visits, medical research and more.

using namespace std;

#include "Hospital.h"
#include "DoctorResercher.h"
#include "Doctor.h"
#include <vector>
#include <fstream>
#include <iostream>

#define FILE_NAME_TO_SAVE_TO "HospitalDataFile.bin" // TO EDIT

//Prototypes:
void optionsMenu(Hospital& hospital);

void getNewDeparmentNameInput(string& newDepName);
void mainAddNewDepartment(Hospital& hospital);
void getNurseDetailsInput(string& newNurseName, int& numberOfExperienceYears);
void mainAddNewNurse(Hospital& hospital);
void getDoctorDetailsInput(string& newDoctorName, string& newDoctorspecialization);
void getSurgeonDetailsInput(string& newDoctorSurgeonName, string& newDoctorSurgeonSpecialization, int& numOfsurgeries);
void mainAddNewDoctor(Hospital& hospital);
bool docTypesCases(Hospital& hospital);
void getPatientDetailsInput(string& newPatientName, int& newPatientYearOfBirth, patient::eGender& newPatientGender);
void mainAddNewVisit(Hospital& hospital);
Date* getDateInput();
void getNewVisitDetails(Hospital& hospital, Date*& newVisitDate, int& departmentToAddToIndex, string& newVisitReason, bool& needSurg, int& surgeryRoom, bool& tsum, Doctor*& newVisitDoctor);
void getNewSrugeryDetails(int& surgeryRoom, bool& tsum);
int chooseDepartmentToAddTo(const Hospital& hospital);
void mainAddNewResearcher(Hospital& hospital);
void getResearcherDetailsInput(string& newResearcherName);
void getArticleDetailsInput(string& newArticleName, string& magazineName);
void mainAddNewArticle(Hospital& hospital);
void mainShowDeparmentPatients(const Hospital& hospital);
void mainShowPatient(const Hospital& hospital);
int chooseResearcherToAddTo(const Hospital& hospital);
void chooseAndCompare2Researchers(const Hospital& hospital);
Doctor* chooseDoctorFromDeparment(Department& department);
void mainFindDepartmentWithMaxPatients(const Hospital& hospital);
void mainSaveToBinaryFile(const Hospital& hospital);

void main()
{
	try
	{
		ifstream inputBinaryFile(FILE_NAME_TO_SAVE_TO, ios::binary);
		if (inputBinaryFile.is_open())
		{
			Hospital hospital(inputBinaryFile);
			inputBinaryFile.close();
			optionsMenu(hospital);
		}
		else
		{
			Hospital hospital;
			optionsMenu(hospital);
		}
	}
	catch (const exception& exptn)
	{
		cout << "General error of '" << exptn.what() << "' occured, exiting the program." << endl;
	}
	catch (...)
	{
		cout << "General error ! exiting the program" << endl;
	}
}

// Displays the main options menu for the Hospital program which is calling the relevant function in each choosing of the user, until he is deciding to finish.
void optionsMenu(Hospital& hospital)
{
	int choice;
	do
	{
		cout << "Please enter your choice from the following options for the action you want to do." << endl;
		hospital.printOptionsMenu();
		cin >> choice;
		switch (choice)
		{
		case ADD_DEPARTMENT:
			mainAddNewDepartment(hospital);
		break;

		case ADD_NURSE:
			mainAddNewNurse(hospital);
			break;

		case ADD_DOCTOR:
			mainAddNewDoctor(hospital);
			break;

		case ADD_VISIT:
			mainAddNewVisit(hospital);
			break;

		case ADD_RESEARCHER:
			mainAddNewResearcher(hospital);
			break;

		case ADD_ARTICLE:
			mainAddNewArticle(hospital);
			break;

		case SHOW_DEPARTMENT_PATIENTS:
			mainShowDeparmentPatients(hospital);
			break;

		case SHOW_ALL_EMPLOYEES:
			hospital.showAllWorkers();
			break;

		case SHOW_ALL_RESEARCHERS:
			hospital.showAllReserchers();
			break;

		case SHOW_ALL_RESEARCHERS_DOCTORS:
			hospital.showAllReserchersDoctors();
			break;

		case FIND_PATIENT_BY_ID:
			mainShowPatient(hospital);
			break;

		case COMPARE_RESEARCHERS:
			chooseAndCompare2Researchers(hospital);
			break;

		case FIND_DEPARTMENT_WITH_MAX_PATIENTS:
			mainFindDepartmentWithMaxPatients(hospital);
			break;

		case END_OF_INPUT:
			mainSaveToBinaryFile(hospital);
			cout << "Thank you and goodbye :) " << endl;
			break;

		default:
			cout << "Invalid input! Please enter a valid choice number." << endl;
			break;
		}
		cout << endl;
	} while (choice != END_OF_INPUT);
	return;
}

// Prompts the user to input details for a new deparment name and return it as a string
void getNewDeparmentNameInput(string& newDepName)
{
	cout << "Please add the name of the new department: ";
	cin.ignore(); // clean the buffer
	getline(cin, newDepName);
}

void mainAddNewDepartment(Hospital& hospital)
{
	string newDepartmentName;
	getNewDeparmentNameInput(newDepartmentName);
	bool objectCreated = false;
	while (objectCreated == false)
	{
		try
		{
			hospital.addNewDepartment(newDepartmentName);
			objectCreated = true;
		}
		catch (const invalid_argument& exptn)
		{
			cout << "Invlaid input ! because of " << exptn.what() << " please re - enter the new department details." << endl;
			getNewDeparmentNameInput(newDepartmentName);
		}
		catch (...)
		{
			cout << "General error ! returning to the main options menu" << endl;
			return;
		}
	}
}

// Prompts the user to input details for a new Nurse and stores them in the given string and integer reference.
void getNurseDetailsInput(string& newNurseName, int& numberOfExperienceYears)
{
	cout << "Please enter the name of the new nurse: ";
	cin.ignore(); // clean the buffer
	getline(cin, newNurseName);
	cout << "Please enter the number of years of experience of the new nurse: ";
	cin >> numberOfExperienceYears;
}

void mainAddNewNurse(Hospital& hospital)
{
	if (hospital.getNumOfDepartments() == 0)
		cout << "Please add a department first" << endl;
	else
	{
		string newNurseName;
		int numberOfExperienceYears;
		getNurseDetailsInput(newNurseName, numberOfExperienceYears);
		int departmentToAddTo = chooseDepartmentToAddTo(hospital);
		bool objectCreated = false;
		while (objectCreated == false)
		{
			try
			{
				hospital.addNewNurse(newNurseName, numberOfExperienceYears, departmentToAddTo);
				objectCreated = true;
			}
			catch (const invalid_argument& exptn)
			{
				cout << "Invlaid input ! because of " << exptn.what() << " please re - enter the new nurse details." << endl;
				getNurseDetailsInput(newNurseName, numberOfExperienceYears);
			}
			catch (...)
			{
				cout << "General error ! returning to the main options menu" << endl;
				return;
			}
		}
	}
}

// Prompts the user to input details for a new Doctor and stores them in the given string.
void getDoctorDetailsInput(string& newDoctorName, string& newDoctorspecialization)
{
	cout << "Please enter the name of the new doctor: ";
	cin.ignore(); // clean the buffer
	getline(cin, newDoctorName);
	cout << "Please enter the specialization field of the new doctor: ";
	getline(cin, newDoctorspecialization);
}

void getSurgeonDetailsInput(string& newDoctorSurgeonName, string& newDoctorSurgeonSpecialization, int& numOfsurgeries)
{
	getDoctorDetailsInput(newDoctorSurgeonName, newDoctorSurgeonSpecialization);
	cout << "enter num of surgeries: ";
	cin >> numOfsurgeries;
}

void mainAddNewDoctor(Hospital& hospital)
{
	if (hospital.getNumOfDepartments() == 0)
		cout << "Please add a department first" << endl;
	else
	{
		bool validInput;
		do
		{
			validInput = docTypesCases(hospital);
		} while (validInput != true);
	}
}

bool docTypesCases(Hospital& hospital)
{
	bool objectCreated = false;
	bool validInput = true;
	int departmentToAddTo, numOfSurg;
	string newDoctorName;
	string newDoctorspecialization;
	Doctor::printDoctorsTypes();
	int kindOfDoc;
	cin >> kindOfDoc;
	switch (kindOfDoc)
	{
	case REGULAR_DOCTOR:

		getDoctorDetailsInput(newDoctorName, newDoctorspecialization);
		departmentToAddTo = chooseDepartmentToAddTo(hospital);
		while (objectCreated == false)
		{
			try
			{
				hospital.addNewDoctor(newDoctorName, newDoctorspecialization, departmentToAddTo);
				objectCreated = true;
			}
			catch (const invalid_argument& exptn)
			{
				cout << "Invlaid input ! because of " << exptn.what() << " please re - enter the new doctor details." << endl;
				getDoctorDetailsInput(newDoctorName, newDoctorspecialization);
			}
			catch (...)
			{
				cout << "General error ! returning to the main options menu" << endl;
				return validInput;
			}
		}
		break;

	case SURGEON_DOCTOR:
		getSurgeonDetailsInput(newDoctorName, newDoctorspecialization, numOfSurg);
		departmentToAddTo = chooseDepartmentToAddTo(hospital);
		while (objectCreated == false)
		{
			try
			{
				hospital.addNewDoctorSurgeon(newDoctorName, newDoctorspecialization, numOfSurg, departmentToAddTo);
				objectCreated = true;
			}
			catch (const invalid_argument& exptn)
			{
				cout << "Invlaid input ! because of " << exptn.what() << " please re - enter the new surgeon details." << endl;
				getSurgeonDetailsInput(newDoctorName, newDoctorspecialization, numOfSurg);
			}
			catch (...)
			{
				cout << "General error ! returning to the main options menu" << endl;
				return validInput;
			}
		}
		break;

	case RESEARCHER_DOCTOR:
		getDoctorDetailsInput(newDoctorName, newDoctorspecialization);
		departmentToAddTo = chooseDepartmentToAddTo(hospital);
		while (objectCreated == false)
		{
			try
			{
				hospital.addNewDoctorResercher(newDoctorName, newDoctorspecialization, departmentToAddTo);
				objectCreated = true;
			}
			catch (const invalid_argument& exptn)
			{
				cout << "Invlaid input ! because of " << exptn.what() << " please re - enter the new doctor-resercher details." << endl;
				getDoctorDetailsInput(newDoctorName, newDoctorspecialization);
			}
			catch (...)
			{
				cout << "General error ! returning to the main options menu" << endl;
				return validInput;
			}
		}
		break;

	case RESEARCHER_SURGEON_DOCTOR:
		getSurgeonDetailsInput(newDoctorName, newDoctorspecialization, numOfSurg);
		departmentToAddTo = chooseDepartmentToAddTo(hospital);
		while (objectCreated == false)
		{
			try
			{
				hospital.addNewDoctorResercherSurgeon(newDoctorName, newDoctorspecialization, numOfSurg, departmentToAddTo);
				objectCreated = true;
			}
			catch (const invalid_argument& exptn)
			{
				cout << "Invlaid input ! because of " << exptn.what() << " please re - enter the new surgeon-researcher details." << endl;
				getSurgeonDetailsInput(newDoctorName, newDoctorspecialization, numOfSurg);
			}
			catch (...)
			{
				cout << "General error ! returning to the main options menu" << endl;
				return validInput;
			}
		}
		break;

	default:
		validInput = false;
		cout << "Invalid input! Please enter a valid choice number." << endl;
		break;
	}
	return validInput;
}

// Prompts the user to input details for a new Patient and stores them in the given string reference, integer reference and eGender reference.
void getPatientDetailsInput(string& newPatientName, int& newPatientYearOfBirth, patient::eGender& newPatientGender)
{
	cout << "Please enter the name of the new patient: " << endl;
	getline(cin, newPatientName);
	cout << "Please enter the new patient year of birth: ";
	cin >> newPatientYearOfBirth;
	cout << "Please enter the new patient gender\n" << patient::MALE << " - male\n" << patient::FEMALE << " - famale" << endl;
	int genderInput;
	cin >> genderInput;
	newPatientGender = (patient::eGender)genderInput;
}

void mainAddNewVisit(Hospital& hospital)
{
	if (hospital.getNumOfDepartments() == 0)
		cout << "Please add a department first" << endl;
	else if (hospital.getNumOfDoctors() == 0)
		cout << "Please add new doctors to the hospital first" << endl;
	else
	{
		cout << "For adding a new visit, please follow the instructions." << endl;
		string patientID;
		cout << "Please enter the ID of the patient with length of - " << (patient::ID_LENGTH) << " digits: ";
		cin.ignore(); // clean the buffer
		getline(cin, patientID);
		patient* patientPtr = hospital.findPatientByID(patientID);
		bool isNewPatient = false;
		bool objectCreated = false;
		if (patientPtr == nullptr)
		{
			isNewPatient = true;
			string newPatientName;
			int newPatientYearOfBirth;
			patient::eGender newPatientGender;
			getPatientDetailsInput(newPatientName, newPatientYearOfBirth, newPatientGender);
			while (objectCreated == false)
			{
				try
				{
					patientPtr = patient::makeNewPatientPtr(patientID, newPatientName, newPatientYearOfBirth, newPatientGender);
					objectCreated = true;
				}
				catch (const invalid_argument& exptn)
				{
					cout << "Invlaid input ! because of " << exptn.what() << " please re-enter the new patient details." << endl;
					cin.ignore(); // clean the buffer
					getPatientDetailsInput(newPatientName, newPatientYearOfBirth, newPatientGender);
				}
				catch (...)
				{
					cout << "General error ! returning to the main options menu" << endl;
					return;
				}
			}
		}
		int departmentToAddToIndex, surgeryRoom;
		string newVisitReason;
		bool needSurg, tsum;
		Date* newVisitDate = nullptr;
		Doctor* newVisitDoctor = nullptr;
		getNewVisitDetails(hospital, newVisitDate, departmentToAddToIndex, newVisitReason, needSurg, surgeryRoom, tsum, newVisitDoctor);
		hospital.addVisit(patientPtr, *newVisitDate, isNewPatient, departmentToAddToIndex, newVisitReason, needSurg, surgeryRoom, tsum, newVisitDoctor);
		delete newVisitDate;
	}
}

// Prompts the user to input the date of the visit and returns a pointer to the Date object.
Date* getDateInput()
{
	int day, month, year;
	cout << "day: ";
	cin >> day;
	cout << "month: ";
	cin >> month;
	cout << "year: ";
	cin >> year;
	return new Date(day, month, year);
}

void getNewVisitDetails(Hospital& hospital, Date*& newVisitDate, int& departmentToAddToIndex, string& newVisitReason, bool& needSurg, int& surgeryRoom, bool& tsum, Doctor*& newVisitDoctor)
{
	cout << "Please enter the new visit date:" << endl;
	bool objectCreated = false;
	while (objectCreated == false)
	{
		try
		{
			newVisitDate = getDateInput();
			objectCreated = true;
		}
		catch (const invalid_argument& exptn)
		{
			cout << "Invlaid input ! because of " << exptn.what() << " please re-enter the date details." << endl;
		}
		catch (...)
		{
			cout << "General error ! returning to the main options menu" << endl;
			return;
		}
	}
	departmentToAddToIndex = chooseDepartmentToAddTo(hospital);
	cout << "Please enter the new visit reason:" << endl;
	cin.ignore(); // clean the buffer
	getline(cin, newVisitReason);

	cout << "is the visit for surgey?\n0. No\n1. Yes " << endl;
	cin >> needSurg;
	if (needSurg == true)
		getNewSrugeryDetails(surgeryRoom, tsum);
	newVisitDoctor = chooseDoctorFromDeparment(*(hospital.getDepartmentsPtrsVector()[departmentToAddToIndex]));
}

void getNewSrugeryDetails(int& surgeryRoom, bool& tsum)
{
	cout << "Please enter the surgery room: " << endl;
	cin >> surgeryRoom;
	cout << "is the pecifiant in tsum?\n0. No\n1. Yes " << endl;
	cin >> tsum;
}

// Allows the user to choose a department to add a new employee to.
int chooseDepartmentToAddTo(const Hospital& hospital)
{
	int choice;
	cout << "Please choose the department you would like to add to from the current existing deparemants in the hospital list:" << endl;
	hospital.printDepartmentsList();
	cin >> choice;
	while ((choice < 0) || (choice >= hospital.getNumOfDepartments()))
	{
		cout << "Invalid choice ! Please enter an option from the following current existing deparemants in the hospital list:" << endl;
		hospital.printDepartmentsList();
		cin >> choice;
	}
	return choice;
}

// Prompts the user to input details for a new researcher and stores them in the given string.
void getResearcherDetailsInput(string& newResearcherName)
{
	cout << "Please enter the name of the new researcher: ";
	cin.ignore(); // clean the buffer
	getline(cin, newResearcherName);
}

void mainAddNewResearcher(Hospital& hospital)
{
	string newResearcherName;
	getResearcherDetailsInput(newResearcherName);
	researcher* newResearcherPtr = nullptr;
	bool objectCreated = false;
	while (objectCreated == false)
	{
		try
		{
			newResearcherPtr = researcher::makeNewResearcherPtr(newResearcherName);
			objectCreated = true;
		}
		catch (const invalid_argument& exptn)
		{
			cout << "Invlaid input ! because of " << exptn.what() << " please re-enter the new researcher details." << endl;
			getResearcherDetailsInput(newResearcherName);
		}
		catch (...)
		{
			cout << "General error ! returning to the main options menu" << endl;
			return;
		}
	}
	hospital.addNewResearcher(newResearcherPtr);
}

// Gets user input for new article details
void getArticleDetailsInput(string& newArticleName, string& magazineName)
{
	cout << "Please enter the name of the new article: ";
	cin.ignore(); // clean the buffer
	getline(cin, newArticleName);
	cout << "Please enter the name of the magazine: ";
	getline(cin, magazineName);
}



void mainAddNewArticle(Hospital& hospital)
{
	if (hospital.getResearchInstitutePtr()->getResearchersPtrsVector().size() == 0)
		cout << "please add a resercher first." << endl;
	else
	{
		cout << "Please enter the article publishing date:" << endl;
		Date* newArticlePublishDate = nullptr;
		bool objectCreated = false;
		while (objectCreated == false)
		{
			try
			{
				newArticlePublishDate = getDateInput();
				objectCreated = true;
			}
			catch (const invalid_argument& exptn)
			{
				cout << "Invlaid input ! because of " << exptn.what() << " please re-enter the date details." << endl;
			}
			catch (...)
			{
				cout << "General error ! returning to the main options menu" << endl;
				return;
			}
		}
		string newArticleName;
		string magazineName;
		getArticleDetailsInput(newArticleName, magazineName);
		article* newArticlePtr = nullptr;
		objectCreated = false;
		while (objectCreated == false)
		{
			try
			{
				newArticlePtr = article::makeNewArticlePtr(newArticleName, magazineName, *newArticlePublishDate);
				objectCreated = true;
			}
			catch (const invalid_argument& exptn)
			{
				cout << "Invlaid input ! because of " << exptn.what() << " please re-enter the new article details." << endl;
				getArticleDetailsInput(newArticleName, magazineName);
			}
			catch (...)
			{
				cout << "General error ! returning to the main options menu" << endl;
				return;
			}
		}
		int researcherToAddTo = chooseResearcherToAddTo(hospital);
		hospital.addArticle(newArticlePtr, researcherToAddTo);
		delete newArticlePublishDate;
	}
}

void mainShowDeparmentPatients(const Hospital& hospital)
{
	if (hospital.getNumOfDepartments() == 0)
		cout << "There aren't any departments in the hospital, so there aren't any patients in the hospital in them to show as well. Please enter departments and patients first, and then try to show them." << endl;
	else
	{
		int choice;
		cout << "Please choose the department you would like to show all patients of, from the current existing deparemants in the hospital list:" << endl;
		hospital.printDepartmentsList();
		cin >> choice;
		while ((choice < 0) || (choice >= hospital.getNumOfDepartments()))
		{
			cout << "Invalid choice ! Please enter an option from the following current existing deparemants in the hospital list:" << endl;
			hospital.printDepartmentsList();
			cin >> choice;
		}
		hospital.showDeparmentPatients(choice);
	}
}

void mainShowPatient(const Hospital& hospital)
{
	if (hospital.getNumOfDepartments() == 0)
		cout << "There aren't any departments in the hospital, so there aren't any patients in the hospital in them to show as well. Please enter departments and patients first, and then try to show a specific patient." << endl;
	else
	{
		string ID;
		cout << "Please enter the searched patient ID with length of " << patient::ID_LENGTH << " digits: ";
		cin.ignore();
		getline(cin, ID);
		hospital.showPatient(ID);
	}
}

// Allows the user to choose a researcher to add to the research institute.
int chooseResearcherToAddTo(const Hospital& hospital)
{
	int choice;
	cout << "Please choose the researcher you would like to add the new article to : " << endl;
	hospital.getResearchInstitutePtr()->printResearchersList();
	cin >> choice;
	while ((choice < 0) || (choice >= hospital.getResearchInstitutePtr()->getResearchersPtrsVector().size()))
	{
		cout << "Invalid choice ! Please enter an option from the following current existing deparemants in the hospital list:" << endl;
		hospital.getResearchInstitutePtr()->printResearchersList();
		cin >> choice;
	}
	return choice;
}

void chooseAndCompare2Researchers(const Hospital& hospital)
{
	const researchInstitute* mainResearchInstitutePtr = hospital.getResearchInstitutePtr();
	int numOfResearchers = mainResearchInstitutePtr->getResearchersPtrsVector().size();
	if (numOfResearchers == 0)
	{
		cout << "There aren't any researchers in the research institute. Please enter two researchers first, and then try to compare between them." << endl;
		return;
	}
	else if (numOfResearchers == 1)
	{
		cout << "There is only one researcher in the research institute. Please enter another researcher first, and then try to compare between them." << endl;
		return;
	}
	cout << "Please choose 2 researchers from the list." << endl;
	mainResearchInstitutePtr->printResearchersList();
	int FirstResearchers1Ind, SecondResearcher1Ind;
	cout << "First choice: ";
	cin >> FirstResearchers1Ind;
	while ((FirstResearchers1Ind < 0) || (FirstResearchers1Ind >= numOfResearchers))
	{
		cout << "Invalid input! please try again from the options in the researchers list." << endl;
		cout << "First choice: ";
		cin >> FirstResearchers1Ind;
	}
	cout << "Second choice: ";
	cin >> SecondResearcher1Ind;
	while ((SecondResearcher1Ind < 0) || (SecondResearcher1Ind >= numOfResearchers))
	{
		cout << "Invalid input! please try again from the options in the researchers list:" << endl;
		cout << "Second choice: ";
		cin >> SecondResearcher1Ind;
	}
	const researcher& firstResearcherRef = hospital.getResearcher(FirstResearchers1Ind);
	const researcher& secondResearcherRef = hospital.getResearcher(SecondResearcher1Ind);

	if (firstResearcherRef > secondResearcherRef)
		cout << "The first choice - '" << firstResearcherRef.getName() << "' has more articles, with " << firstResearcherRef.getNumOfArticles() << " articles." << endl;
	else
		cout << "The second choice - '" << secondResearcherRef.getName() << "' has more or equal number of articles, with " << secondResearcherRef.getNumOfArticles() << " articles." << endl;
}

// Allows the user to choose a Doctor from the department and returning pointer to this doctor
Doctor* chooseDoctorFromDeparment(Department& department)
{
	int choice;
	vector<Doctor*> doctorsPtrsVector = department.getDoctorsPtrsVector();
	cout << "Which of the following doctors in the department would you like to choose:" << endl;
	int i = 0;
	for (Doctor* doctorPtr : doctorsPtrsVector)
	{
		cout << i << " - " << doctorPtr->getName() << endl;
		i++;
	}
	cin >> choice;
	while ((choice < 0) || (choice >= doctorsPtrsVector.size()))
	{
		cout << "Invalid choice ! please try again from the doctors list." << endl;
		cin >> choice;
	}
	return doctorsPtrsVector[choice];
}

void mainFindDepartmentWithMaxPatients(const Hospital& hospital)
{
	if (hospital.getNumOfDepartments() == 0)
		cout << "There aren't any departments in the hospital, so there aren't any patients in the hospital in them to show as well. Please enter departments and patients first, and then try again." << endl;
	else
	{
		const Department* depWithMaxPatientsPtr = hospital.findDepartmentWithMaxPatients();
		if (depWithMaxPatientsPtr->getNumOfPatients() == 0)
			cout << "All of the departments in the hospital are empty" << endl;
		else
			cout << "The Department with the most patients is the " << depWithMaxPatientsPtr->getName() << " Department" << endl;
	}
}

void mainSaveToBinaryFile(const Hospital& hospital)
{
	ofstream outputBinaryFile(FILE_NAME_TO_SAVE_TO, ios::binary | ios::trunc);
	hospital.saveToBinaryFile(outputBinaryFile);
	outputBinaryFile.close();
}