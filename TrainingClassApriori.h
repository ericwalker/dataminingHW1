#ifndef TRAININGCLASS_APRIORI_H
#define TRAININGCLASS_APRIORI_H
#include <iostream>
#include <sstream>
#include "BasicTrainingClass.h"
#include "PatternUnit.h"
#include "PatternContainer.h"
#include "GlobalVariable.h"
using namespace std;
class TrainingClassApriori: public BasicTrainingClass
{
public:
	TrainingClassApriori(int maxLengthOfPattern, int numOfLengthOnePattern):
		BasicTrainingClass( maxLengthOfPattern, numOfLengthOnePattern)
	{
		
	}
	void training();
private:
	std::vector<PatternUnit> AllCandidatePattern;
	std::vector<std::string> splitStringToWords(std::string inputString, std::string delim);
	void generateOneLengthPattern(PatternContainer& PC);
	void nPlusOnePattern(int n, int maxLengthPattern, int j, std::string currentPattern,int lengthOfOneWordPattern,std::vector<PatternUnit> oneWordPattern);

};
#endif