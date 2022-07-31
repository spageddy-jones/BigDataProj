/* BigDataProj.cpp
*
* Author:     Robin Oster
* Created On : 29/7/2022
*/

#include "knnDocuments.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main()
{
    trainingDocs trainingSet;

    vector<string> testFiles{ "TestSet/501-01.txt", "TestSet/501-02.txt", "TestSet/502-01.txt", "TestSet/502-02.txt"};

	while (!testFiles.empty()) {
		ifstream fileStream(testFiles.back()); //use last file in vector
		int sensitivityScore = 0;
		if (fileStream.is_open()) {
			string word;
			while (fileStream >> word)
			{
				//see if word is in sensitive set
				if (find(trainingSet.PHI.begin(), trainingSet.PHI.end(), word) != trainingSet.PHI.end()) {
					sensitivityScore += 1;
				}
			}
		}
		//sort according to closest centroid
		//document is sensitive
		if (abs(sensitivityScore - trainingSet.getSensitiveCentroid()) < abs(sensitivityScore - trainingSet.getNonsensitiveCentroid())) {

			// word suppression goes here
			//
			//
			//
			//
			cout << "Sensitive: " << sensitivityScore << endl;
			testFiles.pop_back();
		}
		//document is nonsensitive
		else {
			cout << "Nonsensitive: " << sensitivityScore << endl;
			testFiles.pop_back();
		}
	}
}

