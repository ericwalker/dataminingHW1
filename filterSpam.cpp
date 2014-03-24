#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include "PatternUnit.h"
#include "PatternContainer.h"
#include "BasicTrainingClass.h"
#include "TrainingClassApriori.h"
#include "TrainingClass_Sample.h"
#define STRING_LENGTH 256
#define MAX_LENGTH 3
using namespace std;
vector<string> SMS;
vector<string> SpamSMS;
vector<PatternUnit> AllCandidatePattern;

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
	TrainingClassApriori TA(3,10);
	TA.run();
	return 0;
}
