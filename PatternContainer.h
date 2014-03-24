#ifndef PATTERN_CONTAINER_H
#define PATTERN_CONTAINER_H
#include "PatternUnit.h"
class PatternContainer{
private:
	static bool sortPatternUnit(const PatternUnit PU_A,const PatternUnit PU_B);
		// {
		// 	return PU_A.getValue()>PU_B.getValue();
		// }
	std::vector<PatternUnit> pattern;
	std::vector<PatternUnit> choosePattern;
	int lengthOfPattern;
public:  
	PatternContainer(int length);
	// {
	// 	this->lengthOfPattern=length;
	// }
	void evaluatePatternValue();
		// {
		// 	//cout<<PC.getPattern().size()<<endl;
		// 	for(int i=0;i<pattern.size();i++)
		// 	{
		// 		for(int j=0;j<SMS.size();j++)
		// 		{
		// 			string temp;
		// 			temp.append(" ");
		// 			temp.append(pattern[i].getPatternName());
		// 			temp.append(" ");
		// 			if(SMS[j].find(temp)!=string::npos)
		// 			{
		// 				pattern[i].incNormalPatternFreq();
		// 			}	
		// 		}
		// 	}
		// 	for(int i=0;i<pattern.size();i++)
		// 		pattern[i].calValue();

		// }
	std::vector<PatternUnit> getChoosePattern();
		// {
		// 	return choosePattern;
		// }
	void SortPattern(int numOfPattern);
		// {
		// 	//vector<PatternUnit>::iterator PatternIterator;
		// 	sort(pattern.begin(),pattern.end(),sortPatternUnit);
		// 	if(numOfPattern>0)
		// 	{				
		// 		for(int i=0;i<numOfPattern;i++)
		// 		{
		// 			choosePattern.push_back(pattern[i]);
		// 		}				
		// 	}
		// }
	std::vector<PatternUnit> getPattern();
		// {
		// 	return pattern;
		// }
	int findAndIncPatternFreq(PatternUnit PU);
		// {			
		// 	bool isFind=false;
		// 	for(int i=0;i<pattern.size();i++)
		// 	{
		// 		if(pattern[i]==PU)
		// 		{
		// 			pattern[i].incSpamPatternFreq();
		// 			isFind=true;
		// 			return pattern[i].getSpamFrequency();
		// 		}
		// 	}
		// 	if(!isFind)
		// 	{
		// 		return 0;
		// 	}
		// 	return 0;
		// }
	int getPatternLength();
		// {
		// 	return lengthOfPattern;  
		// }
	void setPatternVector(std::vector<PatternUnit> PC);
		// {
		// 	pattern=PC;
		// }
	bool addPatternUnit(PatternUnit PU);
		// {
		// 	pattern.push_back(PU);
		// 	// cout<<pattern.size()<<endl;
		// 	// char a;
		// 	// cin>>a;
		// 	return 1;
		// }
};
#endif