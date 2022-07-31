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

void trainingDocs::initDocs() {
	bool isSensitive = true;
	std::ifstream sensitiveFile("sensitive.txt");
	if (sensitiveFile.is_open()) {	//read from previous calculations, dont need to process each doc
		string word;
		int numFiles = 0;
		int sensitivityScore = 0;
		while (sensitiveFile >> word) {
			numFiles += 1;
			sensitiveCentroid += stoi(word);
			sensitiveDocs.push_back(pair<bool, int>(isSensitive, stoi(word)));
		}
		sensitiveCentroid /= numFiles;
	}
	else {	//have to calculate sensitivity score for each doc
		std::vector<std::string> fileNames{ "PHI/320-01.txt", "PHI/320-02.txt", "PHI/320-03.txt", "PHI/320-04.txt", "PHI/321-01.txt", "PHI/321-02.txt",
			"PHI/321-03.txt", "PHI/321-04.txt" };
		int numFiles = fileNames.size();
		while (!fileNames.empty()) {
			ifstream trainingFile(fileNames.back());
			ofstream outputFile("sensitive.txt", ios_base::app);
			int sensitivityScore = 0;
			if (trainingFile.is_open() && outputFile.is_open()) {
				string word;
				while (trainingFile >> word)
				{
					//see if word is in sensitive set
					if (find(PHI.begin(), PHI.end(), word) != PHI.end()) {
						sensitivityScore += 1;
					}
				}
			}
			sensitiveCentroid += sensitivityScore;
			sensitiveDocs.push_back(pair<bool, int>(isSensitive, sensitivityScore));
			outputFile << sensitivityScore << "\n";
			fileNames.pop_back();
		}
		sensitiveCentroid /= numFiles;
	}


	isSensitive = false;
	std::ifstream nonsensitiveFile("nonsensitive.txt");
	if (nonsensitiveFile.is_open()) {	//read from previous calculations, dont need to process each doc
		string word;
		int numFiles = 0;
		int sensitivityScore = 0;
		while (nonsensitiveFile >> word) {
			numFiles += 1;
			nonsensitiveCentroid += stoi(word);
			nonsensitiveDocs.push_back(pair<bool, int>(isSensitive, stoi(word)));
		}
		nonsensitiveCentroid /= numFiles;
	}
	else {	//have to calculate sensitivity score for each doc
		std::vector<std::string> fileNames{ "Non-PHI/401-01.txt", "Non-PHI/401-02.txt", "Non-PHI/401-03.txt", "Non-PHI/401-04.txt",
			"Non-PHI/402-01.txt", "Non-PHI/402-02.txt" };
		int numFiles = fileNames.size();
		while (!fileNames.empty()) {
			ifstream trainingFile(fileNames.back());
			ofstream outputFile("nonsensitive.txt", ios_base::app);
			int sensitivityScore = 0;
			if (trainingFile.is_open() && outputFile.is_open()) {
				string word;
				while (trainingFile >> word)
				{
					//see if word is in sensitive set
					if (find(PHI.begin(), PHI.end(), word) != PHI.end()) {
						sensitivityScore += 1;
					}
				}
			}
			nonsensitiveCentroid += sensitivityScore;
			nonsensitiveDocs.push_back(pair<bool, int>(isSensitive, sensitivityScore));
			outputFile << sensitivityScore << "\n";
			fileNames.pop_back();
		}
		sensitiveCentroid /= numFiles;
	}

}

void trainingDocs::printDocs() {
	cout << "Sensitive Docs:\n";
	for (int i = 0; i < sensitiveDocs.size(); i++) {
		cout << sensitiveDocs[i].first << ", ";
		cout << sensitiveDocs[i].second << "\n";
	}
	cout << "Centroid: " << sensitiveCentroid << "\n";
	cout << "Nonsensitive Docs:\n";
	for (int i = 0; i < nonsensitiveDocs.size(); i++) {
		cout << nonsensitiveDocs[i].first << ", ";
		cout << nonsensitiveDocs[i].second << "\n";
	}
	cout << "Centroid: " << nonsensitiveCentroid << "\n";
}