/*
 Name:		PinBase.cpp
 Created:	6/7/2021 5:44:16 PM
 Author:	Robert
 Editor:	http://www.visualmicro.com
*/

#include <PinBase.h>
#include <ADM.h>

namespace pinbase
{
	using namespace adm::SHORTSTREAMKEYWORDS;
	PWMMETHOD xPWMpin;
	PINMETHOD* PWMpin = &xPWMpin;
	LOGICMETHOD xLogicPin;
	PINMETHOD* LogicPin = &xLogicPin;
	DIGITALINPUT xDigitalInput;
	PINMETHOD* DigitalInput = &xDigitalInput;
	ANALOGINPUT xAnalogInput;
	PINMETHOD* AnalogInput = &xAnalogInput;
	DIGITALINPUTPULLUP xDigitalInputPullup;
	PINMETHOD* DigitalInputPullup = &xDigitalInputPullup;
	ANALOGINPUTPULLUP xAnalogInputPullup;
	PINMETHOD* AnalogInputPullup = &xAnalogInputPullup;

	PINBASE::PINBASE()
	{
		mPinNo = 0;
		mPWMpin = false;
		mConfigured = false;
		mInitialized = false;
	}

	PINBASE::PINBASE(uint32_t inPinNo, bool pwm)
	{
		if (!mInitialized)
		{
			mPinNo = inPinNo;
			mPWMpin = pwm;
			mConfigured = true;
			mInitialized = false;
		}
	}
	bool PINBASE::Setup(uint32_t inPinNo, bool pwm)
	{
		//bug << trace << "\n [_SETUP_]=[_:PINb:_] ";
		if(!mInitialized)
		{
			mPinNo = inPinNo;
			//xbugVar(inPinNo);
			if(pwm && digitalPinHasPWM(mPinNo)) {
				//xbugTrue;
				mPinMethod = PWMpin;
			}
			else {
			//xbugFalse;
				mPinMethod = LogicPin;
			}
			mPinMethod->Setup(mPinNo);
			mInitialized = true;
		}
		//xbugBool(mInitialized);
		return mInitialized;
	}
	PINBASE::PINBASE(uint32_t inPinNo, uint32_t inputType, bool isAnalog)
	{
		Configure(inPinNo, inputType, isAnalog);		
	}

	bool PINBASE::Configure(uint32_t inPinNo, bool pwm)
	{
		return Configure(inPinNo, OUTPUT, pwm);
	}

	bool PINBASE::Configure(uint32_t inPinNo, uint32_t inputType, bool isAnalog)
	{
		if (!mConfigured)
		{
			mPinNo = inPinNo;
			mPWMpin = isAnalog;
			if (inputType == INPUT)
			{
				mPinMethod = isAnalog ? AnalogInput : DigitalInput;
				mConfigured = true;
				return true;
			}
			if (inputType == INPUT_PULLUP)
			{
				mPinMethod = isAnalog ? AnalogInputPullup : DigitalInputPullup;
				mConfigured = true;
				return true;
			}
			if (inputType == OUTPUT)
			{
				mPinMethod = isAnalog ? PWMpin : LogicPin;
				mConfigured = true;
				return true;
			}
		}
		return false;
	}

	bool PINBASE::Initialize()
	{
		if (mConfigured && !mInitialized)
		{
			mPinMethod->Setup(mPinNo);
			return true;
		}
		return false;
	}
	bool PINBASE::SetupInput(uint32_t inPinNo, uint32_t inputType, bool isAnalog)
	{
		//bug << trace << "\n [_SETUP_]=[_:PINb:_] ";
		if (!mInitialized)
		{
			//xbugTrue;
			if (inputType == INPUT)
			{
				//xbugTrue;
				mPinMethod = isAnalog ? AnalogInput : DigitalInput;
				mInitialized = true;
			}
			else
			{
				//xbugFalse;
				if(inputType == INPUT_PULLUP)
				{
					//xbugTrue;
					mPinMethod = isAnalog ? AnalogInputPullup : DigitalInputPullup;
					mInitialized = true;
				}
			}
			if(mInitialized)
			{
				//xbugTrue;
				mPinNo = inPinNo;
				mPinMethod->Setup(mPinNo);
				return true;
			}
		}
		return false;
	}
	uint8_t PINBASE::GetIntensity()
	{
		//bug << trace << "(_:PIN:_)=(_GET_+-+-_) ";
		return mPinMethod->Read(mPinNo);
	}
	void PINBASE::SetIntensity(const uint8_t& _inSetIntensity)
	{
		//bug << trace << "(_:PIN:_)=(_SET_+-+-_) ";
		mPinMethod->PinWrite(mPinNo, _inSetIntensity);
	}
	bool PINBASE::GetPwr()
	{
		//bug << "( :PIN: )=( GETPWR ) ";
		return bool(mPinMethod->Read(mPinNo));
	}
	int PINBASE::Read()
	{
		return mPinMethod->Read(mPinNo);
	}
	uint32_t PINBASE::GetPinNo()
	{
		//bug << "( :PIN: )=( GET# ) ";
		return mPinNo;
	}
	void PWMMETHOD::PinWrite(const uint8_t& pin, const uint8_t& intensity)
	{
		//xbugWatch(__FUNCTION__);
		//bug << bugVar(pin) << bugVar(intensity);
		analogWrite(pin, intensity);

	}
	void PWMMETHOD::Setup(const uint8_t& pin)
	{
		//xbugWatch(__FUNCTION__);
		//bug << trace << "[_SETASOUT_]=[_:PWM:_] ";
		//xbugVar(pin);
		pinMode(pin, OUTPUT);
		//bug << trace << "[_END_]=[_:PWM:_]\n";

	}
	void LOGICMETHOD::PinWrite(const uint8_t& pin, const uint8_t& intensity)
	{
		//bug << trace << "(_WRITE_)=(_:0101:_) ";
		//bug << vars << bugVar(pin) << bugBool(intensity);
		digitalWrite(pin, intensity);
	}
	void LOGICMETHOD::Setup(const uint8_t& pin)
	{
		//bug << trace << "[_:0101:_]=[_SET_OUT_] ";
		//xbugVar(pin);
		pinMode(pin, OUTPUT);
	}

	int DIGITALINPUTPULLUP::Read(const uint8_t& pin)
	{
		//bug << trace << "(_:0101:_)=(_GET_INPUT_)=(_PULLUP_) ";
		//xbugVar(pin);
		return digitalRead(pin);
	}
	void DIGITALINPUTPULLUP::Setup(const uint8_t& pin)
	{
		//bug << trace << "[_:0101:_]=[_SET_INPUT_]=[_PULLUP_] ";
		//xbugVar(pin);		 
		pinMode(pin, INPUT_PULLUP);
	}
	int ANALOGINPUTPULLUP::Read(const uint8_t& pin)
	{
		return 0;
	}
	void ANALOGINPUTPULLUP::Setup(const uint8_t& pin)
	{
	}
	int DIGITALINPUT::Read(const uint8_t& pin)
	{
		//bug << trace << "(_:0101:_)=(_GET_INPUT_)=(_PULLDOWN_) ";
		//xbugVar(pin);
		return digitalRead(pin);
	}
	void DIGITALINPUT::Setup(const uint8_t& pin)
	{
		//bug << trace << "[_:0101:_]=[_SET_INPUT_]=[_PULLDOWN_] ";
		//xbugVar(pin);
		pinMode(pin, INPUT);
	}
	int ANALOGINPUT::Read(const uint8_t& pin)
	{
		return 0;
	}
	void ANALOGINPUT::Setup(const uint8_t& pin)
	{
	}
}
