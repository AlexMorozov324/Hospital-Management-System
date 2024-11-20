#ifndef __researcher_H
#define __researcher_H

#include "Staff.h"
#include "article.h"
#include "Hospital.h"
#include "Array.h"
#include "myRealloc.h"

class researcher : virtual public Staff
{
protected:
	Array<article*> m_articlesPtrsArr;

	researcher(const researcher& other); // disabling copy c'tor option, becasue we don't want to duplicate researchers
	researcher(researcher&& other); // disabling move c'tor option, becasue we don't want to duplicate researchers
	const researcher& operator=(const researcher& other);
	const researcher& operator=(researcher&& other);

public:
	researcher(const string& name) noexcept(false);
	researcher(const Staff& staff) noexcept(false);
	researcher(ifstream& inputFile);
	virtual ~researcher();

	Array<article*>& getArticlesPtrsArr();
	int getNumOfArticles() const;

	virtual void show() const;
	void addArticleToArr(article* newArticle);

	static researcher* makeNewResearcherPtr(const string& newResearcherName);
	bool operator>(const researcher& other) const;
	void saveToBinaryFile(ofstream& outputFile, bool isAlsoDoc) const;
};

#endif // __researcher_H