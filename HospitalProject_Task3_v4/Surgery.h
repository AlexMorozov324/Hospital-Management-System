#ifndef __Surgery_H
#define __Surgery_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "visit.h"

class Surgery : public visit
{
protected:
	int m_surgeryRoom;
	bool m_tsum;

	Surgery(const Surgery& other);
	Surgery(Surgery&& other);
	const Surgery& operator=(const Surgery& other);
	const Surgery& operator=(Surgery&& other);

public:
	Surgery(const visit& parentVisit, int surgeryRoom, bool inTsum) noexcept(false);
	
	void setSurgeyRoom(int surgeryRoom) noexcept(true);
	void setTsum(bool inTsum) noexcept(true);

	int getSurgeryRoom() const;
	bool getTsum() const;
	void show() const;

	static Surgery* makeNewSurgeryPtr(const visit& parentVisit, int surgeryRoom, bool inTsum);
};


#endif // __Surgery_H
