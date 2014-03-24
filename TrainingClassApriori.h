#ifndef TRAININGCLASS_APRIORI_H
#define TRAININGCLASS_APRIORI_H
#include <iostream>
#include "BasicTrainingClass.h"
#include "PatternUnit.h"
#include "PatternContainer.h"
class TrainingClassApriori: public BasicTrainingClass
{
	public:
		TrainingClassApriori(int maxLengthOfPattern, int numOfLengthOnePattern):
										 BasicTrainingClass( maxLengthOfPattern, numOfLengthOnePattern){}
		
		void run()
		{
			training();
		}
		
	private:
		
		std::vector<std::string> splitStringToWords(std::string inputString, std::string delim);
		void generateOneLengthPattern(PatternContainer& PC);
		void nPlusOnePattern(int n, int maxLengthPattern, int j, std::string currentPattern,int lengthOfOneWordPattern,std::vector<PatternUnit> oneWordPattern);
		void training();
		

};
#endif