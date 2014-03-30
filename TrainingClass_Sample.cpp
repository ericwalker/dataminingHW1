#include "TrainingClass_Sample.h"

	//void TrainingClass_Sample::training(){}
	//void TrainingClass_Sample::run(){};


using namespace std;

vector<string> TrainingClass_Sample::splitStringToWords(string inputString,string delim)
{
	vector<string> wordVector;
	stringstream stringStream(inputString);
	string line;
	getline(stringStream, line); 
	{
		std::size_t prev = 0, pos;
		while ((pos = line.find_first_of(delim, prev)) != std::string::npos)
		{
			if (pos > prev)
				wordVector.push_back(line.substr(prev, pos-prev));
			prev = pos+1;
		}
		if (prev < line.length())
			wordVector.push_back(line.substr(prev, std::string::npos));
	}
	return wordVector;
}
void TrainingClass_Sample::generateOneLengthPattern(PatternContainer& PC)
{				
	for(int i=0;i<100;i++)
	{
		vector<string> wordVector;
		wordVector=splitStringToWords(SpamSMS[i],"	 ,/?.;&");

		int tempFreq=0;
		for(int j=0;j<wordVector.size();j++)
		{
			if(wordVector[j]!="spam")
			{
				PatternUnit PU(wordVector[j],1);
						// cout<<"QQ"<<endl;
				if((tempFreq=PC.findAndIncPatternFreq(PU))==0)
				{
					PC.addPatternUnit(PU);
					tempFreq=1;
				}

			}					
		}
	}
}
void TrainingClass_Sample::nPlusOnePattern(int n, int maxLengthPattern, int j,string currentPattern,int lengthOfOneWordPattern,vector<PatternUnit> oneWordPattern)
{
	if(maxLengthPattern-n>0&&n>=0)
	{
		PatternUnit PU(currentPattern,maxLengthPattern-n);
		AllCandidatePattern.push_back(PU);						
	}			
	if(n>0)
	{
		for(int i=j+1;i<lengthOfOneWordPattern;i++)
		{
			string temp=currentPattern;
			temp.append(oneWordPattern[i].getPatternName());
			temp.append(" ");
			nPlusOnePattern(n-1,maxLengthPattern,i,temp,lengthOfOneWordPattern,oneWordPattern);
		}	
	}

}	
void TrainingClass_Sample::training()
{  
	PatternContainer PC(1);		
	generateOneLengthPattern(PC);		

	PC.evaluatePatternValue();
	PC.SortPattern(numOfLengthOnePattern);

	nPlusOnePattern(maxLengthOfPattern,maxLengthOfPattern,-1,"",PC.getChoosePattern().size(),PC.getChoosePattern());
		
	for(int i=0;i<AllCandidatePattern.size();i++)
	{				
		vector<string> workVector=splitStringToWords(AllCandidatePattern[i].getPatternName()," ");

		AllCandidatePattern[i].setLength(workVector.size());
		for(int j=0;j<SMS.size();j++)
		{
			int findTimes=0;				
			for(int k=0;k<workVector.size();k++)
			{
				string tmp=" ";
				tmp.append(workVector[k]);
				tmp.append(" ");
				if(SMS[j].find(tmp)!=std::string::npos)
				{
					findTimes++;							
				}
			}		
			if(findTimes==workVector.size())
			{
				AllCandidatePattern[i].incNormalPatternFreq();
			}
		}
		for(int j=0;j<SpamSMS.size();j++)
		{
			int findTimes=0;
			for(int k=0;k<workVector.size();k++)
			{
				string tmp=" ";
				tmp.append(workVector[k]);
				tmp.append(" ");
				if(SpamSMS[j].find(tmp)!=std::string::npos)
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
	PatternContainer candidatePC(3);
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
