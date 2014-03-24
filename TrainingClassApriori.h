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
	void training()
	{
		PatternContainer PC(1);		
	generateOneLengthPattern(PC);
	PC.evaluatePatternValue();
	PC.SortPattern(20);

	nPlusOnePattern(maxLengthOfPattern,maxLengthOfPattern,-1,"",PC.getChoosePattern().size(),PC.getChoosePattern());
		
	for(int i=0;i<AllCandidatePattern.size();i++)
	{				
		vector<string> workVector=splitStringToWords(AllCandidatePattern[i].getPatternName()," ");

		AllCandidatePattern[i].setLength(workVector.size());
		for(int j=0;j<GlobalVariable::SMS.size();j++)
		{
			int findTimes=0;				
			for(int k=0;k<workVector.size();k++)
			{
				string tmp=" ";
				tmp.append(workVector[k]);
				tmp.append(" ");
				if(GlobalVariable::SMS[j].find(tmp)!=std::string::npos)
				{
					findTimes++;							
				}
			}		
			if(findTimes==workVector.size())
			{
				AllCandidatePattern[i].incNormalPatternFreq();
			}
		}
		for(int j=0;j<GlobalVariable::SpamSMS.size();j++)
		{
			int findTimes=0;
			for(int k=0;k<workVector.size();k++)
			{
				string tmp=" ";
				tmp.append(workVector[k]);
				tmp.append(" ");
				if(GlobalVariable::SpamSMS[j].find(tmp)!=std::string::npos)
				{
					findTimes++;
				}
			}		
			if(findTimes==workVector.size())
			{
				AllCandidatePattern[i].incSpamPatternFreq();
			}
		}				
	}
	PatternContainer candidatePC(MAX_LENGTH);
	candidatePC.setPatternVector(AllCandidatePattern);
	candidatePC.evaluatePatternValue();
	candidatePC.SortPattern(20);
	for(int i=0;i<candidatePC.getChoosePattern().size();i++)
	{
		cout<<"Current Pattern: "<<candidatePC.getChoosePattern()[i].getPatternName()<<"           "
		<<"Spam Frequency: "<<candidatePC.getChoosePattern()[i].getSpamFrequency()<<" Normal Frequency: "
		<<candidatePC.getChoosePattern()[i].getNormalFrequency()<<" error rate: "<<candidatePC.getChoosePattern()[i].getValue()<<endl;		
	}
	}
private:
	std::vector<PatternUnit> AllCandidatePattern;
	std::vector<std::string> splitStringToWords(std::string inputString, std::string delim);
	void generateOneLengthPattern(PatternContainer& PC);
	void nPlusOnePattern(int n, int maxLengthPattern, int j, std::string currentPattern,int lengthOfOneWordPattern,std::vector<PatternUnit> oneWordPattern);



};
#endif