#ifndef TRAININGCLASS_SAMPLE_H
#define TRAININGCLASS_SAMPLE_H
#include <iostream>
#include <sstream>
#include "BasicTrainingClass.h"
#include "GlobalVariable.h"
using namespace std;
class TrainingClass_Sample: public BasicTrainingClass
{
	
	public:
		TrainingClass_Sample(int maxLengthOfPattern, int numOfLengthOnePattern): 
						BasicTrainingClass( maxLengthOfPattern, numOfLengthOnePattern)
		{
			
		}
		void training();
		void run();


private:
	std::vector<PatternUnit> AllCandidatePattern;
	std::vector<std::string> splitStringToWords(std::string inputString, std::string delim);
	void generateOneLengthPattern(PatternContainer& PC);
	void nPlusOnePattern(int n, int maxLengthPattern, int j, std::string currentPattern,int lengthOfOneWordPattern,std::vector<PatternUnit> oneWordPattern);

};
#endif