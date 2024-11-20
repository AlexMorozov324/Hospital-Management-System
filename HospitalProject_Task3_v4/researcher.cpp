#include "researcher.h"

// Constructor for the researcher class.
researcher::researcher(const string& name)
	: Staff(name), m_articlesPtrsArr()
{
}

researcher::researcher(const Staff& staff)
	: Staff(staff), m_articlesPtrsArr()
{
}

researcher::researcher(ifstream& inputFile)
	: Staff(inputFile), m_articlesPtrsArr()
{
	int numOfArticles;
	inputFile.read((char*)&numOfArticles, sizeof(numOfArticles));
	for (int i = 0; i < numOfArticles; i++)
		m_articlesPtrsArr += new article(inputFile);
}

// Destructor for the researcher class.
researcher::~researcher()
{
	for (int i = 0; i < m_articlesPtrsArr.getArrLogSize(); i++)
		delete m_articlesPtrsArr[i];
}

// Gets the array of pointers to article objects representing the researcher's articles.
Array<article*>& researcher::getArticlesPtrsArr()
{
	return m_articlesPtrsArr;
}

int researcher::getNumOfArticles() const
{
	return m_articlesPtrsArr.getArrLogSize();
}

// Displays the details of the researcher.
void researcher::show() const
{
	cout << "The researcher name is " << m_name << ", his Employee number in the hospital is - " << m_employeeSerialNumber << ", and this is the aritcles published list:" << endl;
	for (int i = 0; i < m_articlesPtrsArr.getArrLogSize(); i++)
		m_articlesPtrsArr[i]->show();
}

// Adds a new article to the researcher's list of articles.
void researcher::addArticleToArr(article* newArticle)
{
	m_articlesPtrsArr += newArticle;
}

// Creates a new researcher object dynamically and returns a pointer to it.
researcher* researcher::makeNewResearcherPtr(const string& newResearcherName)
{
	researcher* newResearcherPtr = new researcher(newResearcherName);
	return newResearcherPtr;
}

// return true if the operating object has more articles then the parameter object, and false otherwise
bool researcher::operator>(const researcher& other) const
{
	return (this->m_articlesPtrsArr.getArrLogSize() > other.m_articlesPtrsArr.getArrLogSize());
}

void researcher::saveToBinaryFile(ofstream& outputFile, bool isAlsoDoc) const
{
	if (isAlsoDoc == false)
		Staff::saveToBinaryFile(outputFile);
	int numOfArticles = m_articlesPtrsArr.getArrLogSize();
	outputFile.write((const char*)&numOfArticles, sizeof(numOfArticles));
	for (int i = 0; i < numOfArticles; i++)
		(*m_articlesPtrsArr[i]).saveToBinaryFile(outputFile);
}