/* knnDocuments.cpp
*
* Author:     Robin Oster
* Created On : 29/7/2022
*/

#include "knnDocuments.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace::std;

bool trainingDocs::initDocs() {
	bool isSensitive = true;
	std::vector<std::string> fileNames{ "PHI/320-01.txt", "PHI/320-02.txt", "PHI/320-03.txt", "PHI/320-04.txt", "PHI/321-01.txt", "PHI/321-02.txt", 
		"PHI/321-03.txt", "PHI/321-04.txt" };
	while (!fileNames.empty()) {
		std::ifstream trainingFile(fileNames.back());
		int sensitivityScore = 0;
		if (trainingFile.is_open()) {
			string word;
			while (trainingFile >> word)
			{
				//see if word is in sensitive set
				if (find(PHI.begin(), PHI.end(), word) != PHI.end()) {
					sensitivityScore += 1;
				}
			}
		}
		documents.push_back(pair<bool, int>(isSensitive, sensitivityScore));
		fileNames.pop_back();
	}
	return true;

}

void trainingDocs::printDocs() {
	for (int i = 0; i < documents.size(); i++) {
		cout << documents[i].first << ", ";
		cout << documents[i].second << "\n";
	}
}