#include "Surgery.h"

// Constructor for the Surgery class.
Surgery::Surgery(const visit& parentVisit, int surgeryRoom, bool inTsum)
	:visit(parentVisit)
{
	setSurgeyRoom(surgeryRoom);
	setTsum(inTsum);
}

void Surgery::setSurgeyRoom(int surgeryRoom) noexcept(true)
{
	m_surgeryRoom = surgeryRoom;
}

void Surgery::setTsum(bool inTsum) noexcept(true)
{
	m_tsum = inTsum;
}

int Surgery::getSurgeryRoom() const
{
	return m_surgeryRoom;
}

bool Surgery::getTsum() const
{
	return m_tsum;
}

// Displays the details of the visit on the console.
void Surgery::show() const
{
	visit::show();
	cout << "the visit is for surgery." << endl;
	cout << "surgry room: " << this->m_surgeryRoom << endl;
	if (this->m_tsum)
		cout << "the petient is in tsum." << endl;
	else
		cout << "the petient is not in tsum." << endl;
}

Surgery* Surgery::makeNewSurgeryPtr(const visit& parentVisit, int surgeryRoom, bool inTsum)
{
	Surgery* newSurgeryPtr = new Surgery(parentVisit, surgeryRoom, inTsum);
	return newSurgeryPtr;
}
