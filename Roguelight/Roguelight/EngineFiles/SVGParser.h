//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - version v2_16 jan 2015 
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once
//-----------------------------------------------------------------
// SVGParser Class
//-----------------------------------------------------------------
class SVGParser
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	SVGParser(const String& svgFilePathRef, std::vector<std::vector<DOUBLE2>> &verticesArrRef);
	virtual ~SVGParser();

	// C++11 make the class non-copyable
	SVGParser(const SVGParser&) = delete;
	SVGParser& operator=(const SVGParser&) = delete;

	//---------------------------
	// General Methods
	//---------------------------
	bool LoadGeometryFromSvgFile(const String& svgFilePathRef, std::vector<std::vector<DOUBLE2>> &verticesArrRef);

private:
	//---------------------------
	// Private methods
	//---------------------------
	bool ExtractTransformInformation(tstring& svgTextRef, tstring& sTransformInfoRef);
	bool ExtractPathInformation(tstring& svgTextRef, tstring& sPathInfoRef);
	bool ReadSvgFromData(tstring& sTransformInfoRef, tstring& sPathInfoRef, std::vector<std::vector<DOUBLE2>> &verticesArrRef);
	bool GetGeometryOrGroup(ID2D1Factory* factoryPtr, std::vector<ID2D1Geometry*>& childrenRef, ID2D1Geometry*& geometryPtrRef);
	MATRIX3X2 ReadTransform(tstring& sTransformInfoRef);
	bool ReadSvgPath(tstring& sPathInfoRef, std::vector<std::vector<DOUBLE2>> &verticesArrRef);

	TCHAR WhiteSpaceMapper(TCHAR c);														// Replace all whitespace by space.

	// Skips any optional commas in the stream
	// SVG has a really funky format,
	// not sure this code works for all cases.
	// TODO: Test cases!
	void SkipSvgComma(tstringstream& ssRef, bool isRequired);
	double ReadSvgValue(tstringstream& ssRef, double defaultValue);
	double ReadSvgValue(tstringstream& ssRef, bool separatorRequired);

	DOUBLE2 ReadSvgPoint(tstringstream& ssRef);												// Reads a single point

	// Read the first point, 
	// taking into account relative and absolute positioning.
	// Stores this point, needed when path is closed
	// Advances the cursor if requested.
	DOUBLE2 FirstSvgPoint(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen, bool advance);
	// Read the next point, 
	// taking into account relative and absolute positioning.
	// Advances the cursor if requested.
	// Throws an exception if the figure is not open
	DOUBLE2 NextSvgPoint(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen, bool advance);

	DOUBLE2 NextSvgCoordX(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen);	// Reads next point, given only the new x coordinate
	DOUBLE2 NextSvgCoordY(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen);	// Reads next point, given only the new y coordinate 
};
