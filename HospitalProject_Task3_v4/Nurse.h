#ifndef __Nurse_H
#define __Nurse_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#define _CRT_NONSTDC_NO_DEPRECATE //for strdup() warning. Depends on VS version you might need to use _strdup()

#include "Hospital.h"
#include "Staff.h"

class Nurse : public Staff
{
protected:
    int yearsOfExperience;

    Nurse(const Nurse& other); 
    Nurse(Nurse&& other); 
    const Nurse& operator=(const Nurse& other);
    const Nurse& operator=(Nurse&& other);

public:
    Nurse(const string& nameOfNurse, int yearsOfExperienceOfNurse) noexcept(false);
    Nurse(const Staff& staff, int yearsOfExperienceOfNurse) noexcept(false);
    Nurse(ifstream& inputFile);

    int getYearsOfExperience() const;
    void setYearsOfExperience(int yearsOfExperienceOfNurse) noexcept(false);

    static Nurse* makeNewNursePtr(const string& newNurseName, int numberOfExperienceYears);

    void show() const;
    friend ostream& operator<<(ostream& os, const Nurse& nurse);
    virtual void saveToBinaryFile(ofstream& outputFile) const override;
};

#endif // __Nurse_H
