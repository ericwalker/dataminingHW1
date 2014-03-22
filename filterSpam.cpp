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
		int freqInSpamOccur;
		int freqInNormalOccur;
		float value;
		int patternLength;
	public:
		PatternUnit(string patternName, int length)
		{
			this->patternName=patternName;
			this->freqInSpamOccur=1;
			this->freqInNormalOccur=0;
			this->patternLength=length;
		}
		string getPatternName()
		{
			return patternName;
		}
		void incSpamPatternFreq()
		{
			freqInSpamOccur++;
		}
		void incNormalPatternFreq()
		{
			freqInNormalOccur++;
		}
		int getSpamFrequency()
		{
			return freqInSpamOccur;
		}
		int getNormalFrequency()
		{
			return freqInNormalOccur;
		}
		int getLength()
		{
			return patternLength;
		}
		float getValue() const
		{
			return value;
		}
		void calValue()
		{
			this->value=(float)(freqInSpamOccur-freqInNormalOccur)/(SMS.size()+SpamSMS.size());
		}
};
bool operator== (PatternUnit& a ,PatternUnit& b) {
	return (a.getPatternName()==b.getPatternName()&&a.getLength()==b.getLength());
}
class PatternContainer{
	private:
		static bool sortPatternUnit(const PatternUnit PU_A,const PatternUnit PU_B)
		{
			return PU_A.getValue()>PU_B.getValue();
		}
		vector<PatternUnit> pattern;
		vector<PatternUnit> choosePattern;
		int lengthOfPattern;
	public:  
		PatternContainer(int length)
		{
			this->lengthOfPattern=length;
		}
		void evaluatePatternValue()
		{
			//cout<<PC.getPattern().size()<<endl;
			for(int i=0;i<pattern.size();i++)
			{
				for(int j=0;j<SMS.size();j++)
				{
					string temp;
					temp.append(" ");
					temp.append(pattern[i].getPatternName());
					temp.append(" ");
					if(SMS[j].find(temp)!=string::npos)
					{
						pattern[i].incNormalPatternFreq();
					}	
				}
			}
			for(int i=0;i<pattern.size();i++)
				pattern[i].calValue();

		}
		vector<PatternUnit> getChoosePattern()
		{
			return choosePattern;
		}
		void SortPattern(int numOfPattern)
		{
			//vector<PatternUnit>::iterator PatternIterator;
			sort(pattern.begin(),pattern.end(),sortPatternUnit);
			for(int i=0;i<numOfPattern;i++)
			{
				choosePattern.push_back(pattern[i]);
			}

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
					pattern[i].incSpamPatternFreq();
					isFind=true;
					return pattern[i].getSpamFrequency();
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
		PatternDatabase()
		{

		}
		PatternDatabase(vector<PatternContainer> PatternSet)
		{
			lengthPatternSet=PatternSet;
		}
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


PatternDatabase PDB;

class BasicTrainingClass
{
	public:
		BasicTrainingClass(float valueThreshold, int maxLengthOfPattern, int numOfLengthOnePattern)
		{
			this->valueThreshold=valueThreshold;
			this->maxLengthOfPattern=maxLengthOfPattern;
			this->numOfLengthOnePattern=numOfLengthOnePattern;
		}
		float getValueThreshold()
		{
			return valueThreshold;
		}
		virtual void training()=0;
		float valueThreshold;
		int maxLengthOfPattern;
		int numOfLengthOnePattern;
};
class TrainingClass_Apriori: public BasicTrainingClass
{
	public:
		TrainingClass_Apriori(float valueThreshold, int maxLengthOfPattern, int numOfLengthOnePattern):
										 BasicTrainingClass(valueThreshold, maxLengthOfPattern, numOfLengthOnePattern){}
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
				wordVector=splitStringToWords(SpamSMS[i],"	 ,/?.;&");
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
			for (int i=1;i<=this->maxLengthOfPattern;i++)
			{
				PatternContainer PC(i);
				PDB.addLengthPattern(PC,i);
			}
			PatternContainer PC=PDB.getLengthPattern()[0];		
			generateOneLengthPattern(PC);			
			PC.evaluatePatternValue();
			PC.SortPattern(10);
			for(int i=0;i<PC.getChoosePattern().size();i++)
			{
				cout<<"Current Pattern: "<<(PC.getChoosePattern()[i]).getPatternName()<<"           "
				<<"Spam Frequency: "<<(PC.getChoosePattern()[i]).getSpamFrequency()<<" Normal Frequency: "
				<<(PC.getChoosePattern()[i]).getNormalFrequency()<<" error rate: "<<(PC.getChoosePattern()[i]).getValue()<<endl;		
			}

		}

};
class TrainingClass_Sample: public BasicTrainingClass
{
	
	public:
		TrainingClass_Sample(float valueThreshold,int maxLengthOfPattern, int numOfLengthOnePattern): 
						BasicTrainingClass(valueThreshold, maxLengthOfPattern, numOfLengthOnePattern)
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
	TrainingClass_Apriori TA(0.0125,3,10);
	TA.run();
	return 0;
}
