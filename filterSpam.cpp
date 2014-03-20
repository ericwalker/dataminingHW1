#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#define STRING_LENGTH 256
#define MAX_LENGTH 3
using namespace std;

vector<string> SMS;
vector<string> SpamSMS;

class PatternUnit{
	private:
		string patternName;
		int freqOfOccur;
		int patternLength;
	public:
		PatternUnit(string patternName, int length)
		{
			this->patternName=patternName;
			this->freqOfOccur=1;
			this->patternLength=length;
		}
		string getPatternName()
		{
			return patternName;
		}
		void incPatternFreq()
		{
			freqOfOccur++;
		}
		int getFrequency()
		{
			return freqOfOccur;
		}
		int getLength()
		{
			return patternLength;
		}
};
bool operator== (PatternUnit& a ,PatternUnit& b) {
	return (a.getPatternName()==b.getPatternName()&&a.getLength()==b.getLength());
}
class PatternContainer{
	private:
		vector<PatternUnit> pattern;
		int lengthOfPattern;
	public:  
		PatternContainer(int length)
		{
			this->lengthOfPattern=length;
		}
		vector<PatternUnit> getPattern()
		{
			return pattern;
		}
		int findAndIncPatternFreq(PatternUnit PU)
		{
			bool isFind=false;
			for(int i=0;i<pattern.size();i++)
			{
				if(pattern[i]==PU)
				{
					pattern[i].incPatternFreq();
					isFind=true;
					return pattern[i].getFrequency();
				}
			}
			if(!isFind)
			{
				return 0;
			}
			return 0;
		}
		int getPatternLength()
		{
			return lengthOfPattern;  
		}
		bool addPatternUnit(PatternUnit PU)
		{
			pattern.push_back(PU);
			return 1;
		}
};
class PatternDatabase{
	private: 
		vector<PatternContainer> lengthPatternSet;
	public:
		vector<PatternContainer> getLengthPattern()
		{
			return lengthPatternSet;
		}
		bool addLengthPattern(PatternContainer PC , int length)
		{
			lengthPatternSet.push_back(PC);
			return 1;
		}
};
class BasicTrainingClass
{
	public:
		BasicTrainingClass(float errorRateThreshold, int maxLengthOfPattern, int numOfLengthOnePattern)
		{
			this->errorRateThreshold=errorRateThreshold;
			this->maxLengthOfPattern=maxLengthOfPattern;
			this->numOfLengthOnePattern=numOfLengthOnePattern;
		}
		static PatternDatabase PDB;
		virtual void training()=0;
	private:
		float errorRateThreshold;
		int maxLengthOfPattern;
		int numOfLengthOnePattern;
};
class TrainingClass_Apriori: public BasicTrainingClass
{
	public:
		TrainingClass_Apriori(float errorRateThreshold, int maxLengthOfPattern, int numOfLengthOnePattern):
										 BasicTrainingClass(errorRateThreshold, maxLengthOfPattern, numOfLengthOnePattern){}
		void run()
		{
			training();
		}
	private:
		vector<string> splitStringToWords(string inputString,string delim)
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
		void generateOneLengthPattern(PatternContainer& PC)
		{				
			for(int i=0;i<SpamSMS.size();i++)
			{
				vector<string> wordVector;
				wordVector=splitStringToWords(SpamSMS[i],"	 ,/?.;");
				int tempFreq=0;
				for(int j=0;j<wordVector.size();j++)
				{
					if(wordVector[j]!="spam")
					{
						PatternUnit PU(wordVector[j],1);
						if((tempFreq=PC.findAndIncPatternFreq(PU))==0)
						{
							PC.addPatternUnit(PU);
							tempFreq=1;
						}

					}					
				}

			}
		}
				
		void training()
		{  
			PatternContainer PC(1);			
			generateOneLengthPattern(PC);
			for(int i=0;i<PC.getPattern().size();i++)
			{
				cout<<"Current Pattern: "<<(PC.getPattern()[i]).getPatternName()<<"           "<<"Frequency: "<<(PC.getPattern()[i]).getFrequency()<<endl;	
			}
		}

};
class TrainingClass_Sample: public BasicTrainingClass
{
	
	public:
		TrainingClass_Sample(float errorRateThreshold,int maxLengthOfPattern, int numOfLengthOnePattern): 
						BasicTrainingClass(errorRateThreshold, maxLengthOfPattern, numOfLengthOnePattern)
		{
			
		}
	private:
		void training();
};

void readSMSTrainingData()
{
	fstream file;
	char str[STRING_LENGTH];
	file.open("SMSSpamCollection",ios::in);
	if(file)
	{
	    string tempStr="";
		while(getline(file,tempStr))
		{
			//  cout<<tempStr<<endl;
			if(tempStr.find("spam")==0)
			{
				SpamSMS.push_back(tempStr);
			//	cout<<"------------------------------"<<endl;
			//	cout<<"This Message is Spam SMS"<<endl;
			}
			else
			{
			//	cout<<"------------------------------"<<endl;
			//	cout<<"This Message is normal SMS"<<endl;
				SMS.push_back(tempStr);
			}

		}
	}
	else
	{
		cout<<"Cannot open file!"<<endl;
	}
}
int main(int argc, char* argv[]){
	readSMSTrainingData();
	TrainingClass_Apriori TA(80,3,10);
	TA.run();
	return 0;
}
