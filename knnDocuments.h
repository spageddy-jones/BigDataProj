#pragma once

/* knnDocuments.h
*
* Author:     Robin Oster
* Created On : 29/7/2022
*/

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <utility>

class trainingDocs {
public:
	trainingDocs(){
		initDocs();
	}
	void printDocs();

	const std::vector<std::string> PHI{ "mrn", "ssn", "md" "name", "Dr.", "Center", "Hospital", "Mrs.", "Ms.",
		"Mr." "history", "medical", "record", "number", "MEDICAL", "NO.", "no.", "No.", "RECORD", "NUMBER", "date", "date:", "Date:", "physician", "intern", "room", "unit", "MD", "MD,", "DR" }; //list of potentially sensitive words to search for

	int getSensitiveCentroid() { return sensitiveCentroid; }
	int getNonsensitiveCentroid() { return nonsensitiveCentroid; }
private:
	void initDocs();

	std::vector<std::pair<bool, int>> sensitiveDocs; //sensitive docs, and associated score
	std::vector<std::pair<bool, int>> nonsensitiveDocs; //nonsensitive docs, and associated score
	int sensitiveCentroid;
	int nonsensitiveCentroid;
};