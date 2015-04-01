#include "stdafx.h"

#include "String.h"

using namespace std;

//-----------------------------------------------------------------
// global String operator overloads
//-----------------------------------------------------------------

String& operator+=(String& lhs, const wchar_t* wideTextPtr)
{
	return lhs += String(wideTextPtr);
}

String& operator+=(String& lhs, const char* singleTextPtr)
{
	return lhs += String(singleTextPtr);
}

String operator+(String & lhs, const wchar_t* wideTextPtr)
{
	String newString = lhs;

	newString += wideTextPtr;

	return newString;
}

String operator+(String & lhs, char* singleTextPtr)
{
	String newString = lhs;

	newString += singleTextPtr;

	return newString;
}

//-----------------------------------------------------------------
// String methods
//-----------------------------------------------------------------

String::String(String const& sRef)
{
	m_Length = sRef.Length() + 1; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	_tcscpy_s(m_TextPtr, m_Length, sRef.C_str());
}

String::String(wchar_t const* wideTextPtr)
{
	m_Length = (int)wcslen(wideTextPtr) + 1; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	if (sizeof(TCHAR) == 2) _tcscpy_s(m_TextPtr, m_Length, (TCHAR*)wideTextPtr);
	else WideCharToMultiByte(CP_ACP, 0, wideTextPtr, -1, (char*)m_TextPtr, m_Length, NULL, NULL);
}

String::String(char const* singleTextPtr)
{
	m_Length = (int)strlen(singleTextPtr) + 1; // inlude room for null terminator

	m_TextPtr = new TCHAR[m_Length];

	if (sizeof(TCHAR) == 1) strcpy_s((char*)m_TextPtr, m_Length, singleTextPtr);
	else MultiByteToWideChar(CP_ACP, 0, singleTextPtr, -1, (wchar_t*)m_TextPtr, m_Length * 2);
}

String::String(wchar_t character)
{
	m_Length = 2; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	m_TextPtr[0] = (TCHAR)character;
	m_TextPtr[1] = '\0';
}

String::String(char character)
{
	m_Length = 2; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	m_TextPtr[0] = character;
	m_TextPtr[1] = '\0';
}

String::String(int number)
{
	m_Length = 1; // include room for null terminator
	m_TextPtr = new TCHAR[1];
	m_TextPtr[0] = '\0';
	*this += to_string(number).c_str();
}

String::String(unsigned int number)
{
	m_Length = 1; // include room for null terminator
	m_TextPtr = new TCHAR[1];
	m_TextPtr[0] = '\0';
	*this += to_string(number).c_str();
}

String::String(double number, int precision)
{
	m_Length = 1; // include room for null terminator
	m_TextPtr = new TCHAR[1];
	m_TextPtr[0] = '\0';
	*this += to_string(number).c_str();

	// http://www.cplusplus.com/reference/ios/ios_base/precision/

	tstringstream buffer;
	if (precision > -1) buffer << std::fixed << std::setprecision(precision) << number;
	*this = String(buffer.str().c_str());
}

String::~String()
{
	delete m_TextPtr;
}

String& String::operator=(String const& sRef)
{
	if (this != &sRef) // beware of self assignment: s = s
	{
		delete m_TextPtr;
		m_Length = sRef.Length() + 1;
		m_TextPtr = new TCHAR[m_Length];
		_tcscpy_s(m_TextPtr, m_Length, sRef.C_str());
	}
	return *this;
}

String& String::operator+=(String const& sRef)
{
	m_Length = this->Length() + sRef.Length() + 1;

	TCHAR* buffer = new TCHAR[m_Length];

	_tcscpy_s(buffer, m_Length, m_TextPtr);
	_tcscat_s(buffer, m_Length, sRef.m_TextPtr);

	delete m_TextPtr;
	m_TextPtr = buffer;

	return *this;
}

String String::operator+(String const& sRef) const
{
	String newString = *this;

	newString += sRef;

	return newString;
}

bool String::operator==(String const& sRef) const
{
	return this->Compare(sRef);
}

bool String::operator!=(String const& sRef) const
{
	return !this->Compare(sRef);
}

TCHAR String::At(int index) const
{
	if (index > this->Length() - 1) return 0;

	return m_TextPtr[index];
}

String String::SubStr(int index) const
{
	if (index > this->Length() - 1) return String("");

	return String(m_TextPtr + index);
}

String String::SubStr(int index, int length) const
{
	if (index + length - 1 > this->Length() - 1) return String("");

	String newString = *this;
	newString.m_TextPtr[index + length] = TEXT('\0');

	return String(newString.m_TextPtr + index);
}

int String::Find(TCHAR character) const
{
	for (int index = 0; index < m_Length - 1; ++index)
	{
		if (m_TextPtr[index] == character) return index;
	}
	return -1;
}

int String::Rfind(TCHAR character) const
{
	// start on pos, one before the \0
	for (int index = Length() - 1; index >= 0; --index)
	{
		if (m_TextPtr[index] == character) return index;
	}
	return -1;
}

int String::Find(const String & sRef) const
{
	// return false if 2nd string is longer than 1st string 
	if (this->Length() < sRef.Length()) return -1;

	//empty string(s)
	if (sRef.Length() < 1 || this->Length() < 1) return -1;
	int i = 0;
	do
	{
		String temp = this->SubStr(i, sRef.Length());
		if (sRef.Compare(temp)) return i;
		++i;
	} while (i <= this->Length() - sRef.Length());

	return -1;
}

//Work in progress
int String::Rfind(const String& sRef) const
{
	// return false if 2nd string is longer than 1st string 
	if (this->Length() < sRef.Length()) return -1;

	//empty string(s)
	if (sRef.Length() < 1 || this->Length() < 1) return -1;
	int i = 0;
	do
	{
		String temp = this->SubStr(this->Length() - i - sRef.Length(), sRef.Length());
		if (sRef.Compare(temp)) return this->Length() - i - sRef.Length();
		++i;
	} while (i <= this->Length());

	return -1;
}

int String::Length() const
{
	return m_Length - 1; // don't include the null terminator when asked how many characters are in the string
}

bool String::Compare(String const& sRef) const
{
	if (sRef.Length() != this->Length()) return false;

	return _tcscmp(this->C_str(), sRef.C_str()) ? false : true; // return true if cmp returns 0, false if not
}

int String::ToInteger() const
{
	return _tstoi(this->C_str());
}

double String::ToDouble() const
{
	return _tcstod(this->C_str(), 0);
}

TCHAR* String::C_str() const
{
	return m_TextPtr;
}