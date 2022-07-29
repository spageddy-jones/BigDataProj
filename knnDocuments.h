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
private:
	bool initDocs();

	std::vector<std::string> PHI{"mrn", "ssn", "md" "name", "Dr.", "Center", "Hospital", "Mrs.", "Ms.", 
		"Mr." "history", "medical", "record", "number", "date", "date:", "signed", "physician", "intern", "room", "unit", "MD", "MD,", "DR"}; //list of potentially sensitive words to search for
	std::vector<std::pair<bool, int>> documents; //whether or not a document is sensitive, and associated score
	int groupClassifier; // centroid
};