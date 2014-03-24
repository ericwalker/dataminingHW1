#ifndef TRAININGCLASS_SAMPLE_H
#define TRAININGCLASS_SAMPLE_H
#include "BasicTrainingClass.h"
class TrainingClass_Sample: public BasicTrainingClass
{
	
	public:
		TrainingClass_Sample(int maxLengthOfPattern, int numOfLengthOnePattern): 
						BasicTrainingClass( maxLengthOfPattern, numOfLengthOnePattern)
		{
			
		}
		void training();
		void run();
	
		
};
#endif