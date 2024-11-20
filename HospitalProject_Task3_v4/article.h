#ifndef __article_H
#define __article_H

#include "Date.h"
#include <string>
#include <fstream>

using namespace std;

class article
{
private:
	string m_name;
	Date m_date;
	string m_magazineName;

	article(const article& other) noexcept(false) = default;
	article(article&& other) noexcept(false) = default;

public:
	article(const string& name, const Date& publishDate, const string& magazineName) noexcept(false);
	article(ifstream& inputFile);

	void setName(const string& name) noexcept(false);
	void setMagazineName(const string& magazineName) noexcept(false);

	const string& getName() const;
	const string& getMagazineName() const;
	const Date& getDate() const;

	void show() const;

	static article* makeNewArticlePtr(const string& newArticleName, const string& magazineName, const Date& publishDate);
	void saveToBinaryFile(ofstream& outputFile) const;
};

#endif // __article_H