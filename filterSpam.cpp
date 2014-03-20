#include<iostream>
#include<vector>
#include<fstream>
#define STRING_LENGTH 256
#define MAX_LENGTH 3
using namespace std;

vector<string> SMS;
vector<string> SpamSMS;

class PatternUnit{
	private:
		string patternName;
		int freqOfOccur;
	public:
		PatternUnit(string patternName, int freq)
		{
			this.patternName=patternName;
			this.freqOfOccur=freq;
		}
		string getPatternName()
		{
			return patternName;
		}
		int getFrequency()
		{
			return freqOfOccur;
		}
};
class PatternContainer{
	private:
		vector<PatternUnit> pattern;
	public:  
		vector<PatternUnit> getPattern()
		{
			return pattern;
		}
		bool addPatternUnit(PatternUnit PU)
		{
			pattern.push_back(PU);
			return 1;
		}
};
class Database{
	private: 
		vector<PatternContainer> lengthPatternSet;
	public:
		vector<PatternContainer> getLengthPattern()
		{
			return lengthPatternSet;
		}
		bool addLengthPattern(PatternContainer PC , int length)
		{
			return 1;
		}
  
};
class BasicTrainingClass
{
	public:
		virtual void training()=0;
};
class TrainingClass_Apriori:BasicTrainingClass
{
	private:
		void training();
};
class TrainingClass_Sample:BasicTrainingClass
{
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
			cout<<tempStr<<endl;
			if(tempStr.find("spam")==0)
			{
				SpamSMS.push_back(tempStr);
				cout<<"------------------------------"<<endl;
				cout<<"This Message is Spam SMS"<<endl;
			}
			else
			{
				cout<<"------------------------------"<<endl;
				cout<<"This Message is normal SMS"<<endl;
				SMS.push_back(tempStr);
			}
			char a;cin>>a;

		}
	}
	else
	{
		cout<<"Cannot open file!"<<endl;
	}
}
int main(int argc, char* argv[]){
	readSMSTrainingData();
	return 0;
}
