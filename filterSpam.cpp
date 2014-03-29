#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include "GlobalVariable.h"
#include "TrainingClassApriori.h"
#include "TrainingClass_Sample.h"
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

// void generateSample(double sampleRate)
// {
// 	rand() % 200;
// }

int main(int argc, char* argv[]){
	std::vector<PatternUnit> AllCandidatePattern;	
	readSMSTrainingData();

	cout << "Aprioori's Result: \n";
	TrainingClassApriori TA(3,10);
	TA.training();

	cout << endl<<endl<< "Sample's Result: \n";
	TrainingClass_Sample TS(3,10);
	TS.training();

	return 0;
}
