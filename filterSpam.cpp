#include<iostream>
#include<vector>
#include<fstream>
#define STRING_LENGTH 256
using namespace std;

vector<string> SMS;
vector<string> SpamSMS;
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
