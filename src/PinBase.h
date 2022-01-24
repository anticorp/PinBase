/*
 Name:		PinBase.h
 Created:	6/7/2021 5:44:16 PM
 Author:	Robert
 Editor:	http://www.visualmicro.com
*/

#ifndef _PinBase_h
#define _PinBase_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

	namespace pinbase
	{
		struct PINMETHOD
		{
			virtual void PinWrite(const uint8_t& pin, const uint8_t& intensity) {}
			virtual int Read(const uint8_t& pin) {}
			virtual void Setup(const uint8_t& pin) {}
		};
		struct PWMMETHOD : public PINMETHOD
		{
			PWMMETHOD() {}
			void PinWrite(const uint8_t& pin, const uint8_t& intensity) override;
			void Setup(const uint8_t& pin) override;
		};
		struct LOGICMETHOD : public PINMETHOD
		{
			LOGICMETHOD() {}
			void PinWrite(const uint8_t& pin, const uint8_t& intensity) override;
			void Setup(const uint8_t& pin) override;

		};
		struct DIGITALINPUTPULLUP : public PINMETHOD
		{
			DIGITALINPUTPULLUP() {}
			int Read(const uint8_t& pin) override;
			void Setup(const uint8_t& pin) override;
		};
		struct ANALOGINPUTPULLUP : public PINMETHOD
		{
			ANALOGINPUTPULLUP() {}
			int Read(const uint8_t& pin) override;
			void Setup(const uint8_t& pin) override;
		};
		struct DIGITALINPUT : public PINMETHOD
		{
			DIGITALINPUT() {}
			int Read(const uint8_t& pin) override;
			void Setup(const uint8_t& pin) override;
		};
		struct ANALOGINPUT : public PINMETHOD
		{
			ANALOGINPUT() {}
			int Read(const uint8_t& pin) override;
			void Setup(const uint8_t& pin) override;
		};
		extern PINMETHOD* PWMpin;
		extern PINMETHOD* LogicPin;
		extern PINMETHOD* DigitalInput;
		extern PINMETHOD* AnalogInput;
		extern PINMETHOD* DigitalInputPullup;
		extern PINMETHOD* AnalogInputPullup;

		class PINBASE
		{
		public:
			PINBASE();
			PINBASE(uint32_t inPinNo, bool pwm);
			PINBASE(uint32_t inPinNo, uint32_t inputType, bool isAnalog);
			bool Configure(uint32_t inPinNo, bool pwm);
			bool Configure(uint32_t inPinNo, uint32_t inputType, bool isAnalog);
			bool Initialize();
			bool Setup(uint32_t inPinNo, bool pwm);
			bool SetupInput(uint32_t inPinNo, uint32_t inputType, bool isAnalog);
			uint8_t GetIntensity();
			void SetIntensity(const uint8_t& intensity);
			bool GetPwr();
			int Read();
			uint32_t GetPinNo();
			~PINBASE() {}

		protected:

		private:
			bool mConfigured = false;
			bool mInitialized = false;
			uint32_t mPinNo = 0;
			bool mPWMpin = false;
			bool mLOGICpin = false;
			PINMETHOD* mPinMethod;
		};
	}




#endif

