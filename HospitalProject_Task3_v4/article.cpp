#include "article.h"

// Constructor to initialize the article object with provided attributes
article::article(const string& name, const Date& publishDate, const string& magazineName)
	: m_date(publishDate)
{
	setName(name);
	setMagazineName(magazineName);
}

article::article(ifstream& inputFile)
{
	inputFile.read((char*)&m_date, sizeof(m_date));
	int nameStrSize;
	inputFile.read((char*)&nameStrSize, sizeof(nameStrSize));
	{
		char* buffer = new char[nameStrSize];
		inputFile.read(buffer, nameStrSize);
		m_name = string(buffer, nameStrSize);
		delete[] buffer;
	}
	int magazineStrSize;
	inputFile.read((char*)&magazineStrSize, sizeof(magazineStrSize));
	{
		char* buffer = new char[magazineStrSize];
		inputFile.read(buffer, magazineStrSize);
		m_magazineName = string(buffer, magazineStrSize);
		delete[] buffer;
	}
}

// Sets the article name and return whether the operation was successful
void article::setName(const string& name)
{
	int len = name.length();
	if (len == 0)
		throw invalid_argument("Invalid name value!");
	m_name = name;
}

// Set the magazine name and return whether the operation was successful
void article::setMagazineName(const string& magazineName)
{
	int len = magazineName.length();
	if (len == 0)
		throw invalid_argument("Invalid magazine name value!");
	
	m_magazineName = magazineName;
}

// Gets the name of the article.
const string& article::getName() const
{
	return m_name;
}

// Gets the name of the magazine where the article is published.
const string& article::getMagazineName() const
{
	return m_magazineName;
}

// Gets the publication date of the article.
const Date& article::getDate() const
{
	return m_date;
}

// Displays the article details
void article::show() const
{
	cout << "The article name is: " << m_name << ", it was published on the: ";
	m_date.show();
	cout << ", at the magazine: " << m_magazineName << endl;
}

// Creates and return a new article object pointer with user input
article* article::makeNewArticlePtr(const string& newArticleName, const string& magazineName, const Date& publishDate)
{
	article* newArticlePtr = new article(newArticleName, publishDate, magazineName);
	return newArticlePtr;
}

void article::saveToBinaryFile(ofstream& outputFile) const
{
	outputFile.write((const char*)&m_date, sizeof(m_date));
	int nameStrSize = m_name.size();
	outputFile.write((const char*)&nameStrSize, sizeof(nameStrSize));
	outputFile.write((const char*)m_name.data(), (nameStrSize * sizeof(char)));
	int magazineStrSize = m_magazineName.size();
	outputFile.write((const char*)&magazineStrSize, sizeof(magazineStrSize));
	outputFile.write((const char*)m_magazineName.data(), (magazineStrSize * sizeof(char)));
}
