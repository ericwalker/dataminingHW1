#ifndef PATTERN_UNIT_H
#define PATTERN_UNIT_H
class PatternUnit{
	private:
		std::string patternName;
		int freqInSpamOccur;
		int freqInNormalOccur;
		float value;
		int patternLength;
	public:
		PatternUnit(std::string patternName)
		{
			this->patternName=patternName;
			this->freqInSpamOccur=0;
			this->freqInNormalOccur=0;	
		}
		PatternUnit(std::string patternName, int length)
		{
			this->patternName=patternName;
			this->freqInSpamOccur=0;
			this->freqInNormalOccur=0;
			this->patternLength=length;
		}
		std::string getPatternName();
		// {
		// 	return patternName;
		// }
		void incSpamPatternFreq();
		// {
		// 	freqInSpamOccur++;
		// }
		void incNormalPatternFreq();
		// {
		// 	freqInNormalOccur++;
		// }
		int getSpamFrequency();
		// {
		// 	return freqInSpamOccur;
		// }
		int getNormalFrequency();
		// {
		// 	return freqInNormalOccur;
		// }
		void setLength(int length);
		// {
		// 	this->patternLength=length;
		// }
		int getLength();
		// {
		// 	return patternLength;
		// }
		float getValue() const;
		// {
		// 	return value;
		// }
		void calValue();
		// {
		// 	this->value=(float)(freqInSpamOccur-freqInNormalOccur)/(SMS.size()+SpamSMS.size());
		// }
};
#endif