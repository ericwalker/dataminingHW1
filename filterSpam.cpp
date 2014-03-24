#include <iostream>
#include <fstream>
#include "GlobalVariable.h"
#include "TrainingClassApriori.h"
#define STRING_LENGTH 256
using namespace std;

void readSMSTrainingData()
{
	fstream file;
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
	std::vector<PatternUnit> AllCandidatePattern;	
	readSMSTrainingData();
	TrainingClassApriori TA(3,10);
	TA.training();
	return 0;
}
