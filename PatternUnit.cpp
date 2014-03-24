
#include "PatternUnit.h"

std::string PatternUnit::getPatternName()
{
	return patternName;
}
void PatternUnit::incSpamPatternFreq()
{
	freqInSpamOccur++;
}
void PatternUnit::incNormalPatternFreq()
{
	freqInNormalOccur++;
}
int PatternUnit::getSpamFrequency()
{
	return freqInSpamOccur;
}
int PatternUnit::getNormalFrequency()
{
	return freqInNormalOccur;
}
void PatternUnit::setLength(int length)
{
	this->patternLength=length;
}
int PatternUnit::getLength()
{
	return patternLength;
}
float PatternUnit::getValue() const
{
	return value;
}
void PatternUnit::calValue()
{
	this->value=(float)(freqInSpamOccur-freqInNormalOccur)/(GlobalVariable::SMS.size()+GlobalVariable::SpamSMS.size());
}
