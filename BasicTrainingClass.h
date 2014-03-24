#ifndef BASICTRAININGCLASS_H
#define BASICTRAININGCLASS_H
class BasicTrainingClass
{
	public:
		BasicTrainingClass(int maxLengthOfPattern, int numOfLengthOnePattern)
		{
			this->maxLengthOfPattern=maxLengthOfPattern;
			this->numOfLengthOnePattern=numOfLengthOnePattern;
		}
		// float getValueThreshold()
		// {
		// 	return valueThreshold;
		// }
		virtual void training()=0;
		// float valueThreshold;
		int maxLengthOfPattern;
		int numOfLengthOnePattern;
};
#endif