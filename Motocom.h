#pragma once

#pragma pack(4)
#include <windows.h>

//僞僀儉傾僂僩弶婜抣
static const long	TIMEOUT					= 500;							//庴怣僞僀儉傾僂僩帪娫(msec)丗弶婜抣
static const long	RETRY					= 3;							//庴怣僞僀儉傾僂僩儕僩儔僀夞悢丗弶婜抣

/****************埲壓偺僒僀僘丒峔憿懱偺掕媊偼曄峏偟側偄偱偔偩偝偄*******************/
//僒僀僘掕媊
static const short	LENGTH_OF_TIME					= 16;							//帪崗偺僨乕僞挿(ex. 2007/05/10 15:49)
static const short	LENGTH_OF_NAME					= 32;							//暥帤楍柤徧偺僨乕僞挿(嵟戝32暥帤)
static const short	LENGTH_OF_SUBCODE_ADDINFO		= 16;							//徻嵶僨乕僞捛壛忣曬暥帤楍挿(嵟戝16暥帤)
static const short	LENGTH_OF_SUBCODE_STRINGDATA	= 96;							//徻嵶僨乕僞暥帤楍挿(嵟戝96暥帤)
static const short	LENGTH_OF_ALARMLIST				= 4;							//傾儔乕儉儕僗僩挿
static const short	NUMBER_OF_AXIS					= 8;							//儘儃僢僩偺嵟戝幉悢
static const short	LENGTH_OF_CONFIGNAME			= 4;							//幉峔惉柤徧偺僨乕僞挿
static const short	LENGTH_OF_ELAPSETIME			= 12;							//宱夁帪娫偺僨乕僞挿
static const short	LENGTH_OF_SYSTEMVER				= 24;							//僔僗僥儉償傽乕僕儑儞偺僨乕僞挿
static const short	LENGTH_OF_ROBOTNAME				= 16;							//婡庬柤徧偺僨乕僞挿
static const short	LENGTH_OF_PARAMNO				= 8;							//僷儔儊乕僞No.偺僨乕僞挿
static const short	NUMBER_OF_BASE_AXIS				= 3;							//憱峴幉偺嵟戝幉悢
static const short	NUMBER_OF_STATION_AXIS			= 6;							//僗僥乕僔儑儞幉偺嵟戝幉悢

static const short	LENGTH_OF_MULTI_1				= 474;							//1僶僀僩僒僀僘偺暋悢僨乕僞嵟戝悢
static const short	LENGTH_OF_MULTI_2				= 237;							//2僶僀僩僒僀僘偺暋悢僨乕僞嵟戝悢
static const short	LENGTH_OF_MULTI_4				= 118;							//4僶僀僩僒僀僘偺暋悢僨乕僞嵟戝悢
static const short	LENGTH_OF_MULTI_STR				= 29;							//暥帤楍偺暋悢僨乕僞嵟戝悢
static const short	LENGTH_OF_MULTI_POS				= 9;							//埵抲僨乕僞偺暋悢僨乕僞嵟戝悢
static const short	LENGTH_OF_MULTI_BPEX			= 13;							//儀乕僗幉埵抲丒奜晹幉埵抲僨乕僞偺暋悢僨乕僞嵟戝悢
static const short	LENGTH_OF_STRING				= 16;							//暥帤楍曄悢偺僨乕僞挿

//傾儔乕儉僨乕僞
typedef struct {
		long alarmCode;														//傾儔乕儉僐乕僪
		long alarmData;														//傾儔乕儉僨乕僞
		long alarmType;														//傾儔乕儉僨乕僞庬暿
		char alarmTime[LENGTH_OF_TIME+1];									//傾儔乕儉敪惗帪崗
		char alarmName[LENGTH_OF_NAME+1];									//傾儔乕儉暥帤楍柤徧
} ESAlarmData;

//傾儔乕儉僒僽僐乕僪僨乕僞
typedef struct {
		char  alarmAddInfo[LENGTH_OF_SUBCODE_ADDINFO+1];					//徻嵶僨乕僞捛壛忣曬暥帤楍
		char  alarmStrData[LENGTH_OF_SUBCODE_STRINGDATA+1];					//徻嵶僨乕僞暥帤楍
		char  alarmHighlightData[LENGTH_OF_SUBCODE_STRINGDATA+1];			//徻嵶僨乕僞斀揮昞帵忣曬
} ESSubcodeData;

//傾儔乕儉僨乕僞(僒僽僐乕僪暥帤楍懳墳)
typedef struct {
		ESAlarmData	alarmData;												//傾儔乕儉僨乕僞
		ESSubcodeData subcodeData;											//僒僽僐乕僪僨乕僞
} ESAlarmDataEx;

//傾儔乕儉儕僗僩
typedef struct {
	ESAlarmData data[LENGTH_OF_ALARMLIST];									//傾儔乕儉僨乕僞
} ESAlarmList;

//傾儔乕儉儕僗僩(僒僽僐乕僪暥帤楍懳墳)
typedef struct {
	ESAlarmDataEx data[LENGTH_OF_ALARMLIST];								//傾儔乕儉僨乕僞(僒僽僐乕僪懳墳)
} ESAlarmListEx;

//僗僥乕僞僗僨乕僞
typedef struct {
			long status1;													//僗僥乕僞僗僨乕僞1
			long status2;													//僗僥乕僞僗僨乕僞2
} ESStatusData;

//僕儑僽僗僥乕僞僗僨乕僞
typedef struct {
			char jobName[LENGTH_OF_NAME+1];									//僕儑僽柤徧
			long lineNo;													//儔僀儞斣崋
			long stepNo;													//僗僥僢僾斣崋
			long speedOverride;												//懍搙僆乕僶乕儔僀僪抣
} ESJobStatusData;

//幉峔惉僨乕僞
typedef struct {
			char configurations[NUMBER_OF_AXIS][LENGTH_OF_CONFIGNAME+1];	//幉柤徧(SLURBT,XYZRxRyRz)
} ESConfigurationData;

//幉僨乕僞
typedef struct {
			double axis [NUMBER_OF_AXIS];									//幉僨乕僞
} ESAxisData;

//儘儃僢僩埵抲僨乕僞
typedef struct {
			long dataType;													//僨乕僞僞僀僾(僷儖僗抣/捈岎抣)
			long fig;														//宍懺
			long toolNo;													//僣乕儖斣崋
			long userFrameNo;												//儐乕僓嵗昗斣崋
			long exFig;														//奼挘宍懺
			ESAxisData axesData;											//幉僨乕僞
} ESPositionData;

//儀乕僗埵抲/奜晹幉埵抲僨乕僞
typedef struct {
			long dataType;													//僨乕僞僞僀僾(僷儖僗抣/捈岎抣)
			ESAxisData axesData;											//幉僨乕僞
} ESBpexPositionData;

//娗棟帪娫僨乕僞
typedef struct {
			char startTime[LENGTH_OF_TIME+1];								//壱摥奐巒帪崗
			char elapseTime[LENGTH_OF_ELAPSETIME+1];						//宱夁帪娫
} ESMonitoringTimeData;

//僔僗僥儉忣曬僨乕僞
typedef struct {
			char systemVersion[LENGTH_OF_SYSTEMVER+1];						//僔僗僥儉僜僼僩僂僃傾僶乕僕儑儞
			char name[LENGTH_OF_ROBOTNAME+1];								//婡庬柤徧/梡搑柤徧
			char parameterNo[LENGTH_OF_PARAMNO+1];							//僷儔儊乕僞No.
} ESSystemInfoData;

//堏摦忣曬僨乕僞
typedef struct
{
			long  	robotNo;												//儘儃僢僩斣崋
			long  	stationNo;												//僗僥乕僔儑儞斣崋
			long  	speedType;												//懍搙嬫暘巜掕
			double  speed;													//懍搙巜掕
} ESMoveData;

//儘儃僢僩偺栚昗埵抲僨乕僞乮捈岎嵗昗乯
typedef ESPositionData ESCartPosData;										//儘儃僢僩偺栚昗埵抲僨乕僞乮捈岎抣乯

//儘儃僢僩偺栚昗埵抲僨乕僞乮僷儖僗乯
typedef ESAxisData ESPulsePosData;											//儘儃僢僩偺栚昗埵抲僨乕僞乮僷儖僗抣乯

//儀乕僗偺栚昗埵抲僨乕僞
typedef struct {
			double axis[NUMBER_OF_BASE_AXIS];								//儀乕僗偺栚昗埵抲僨乕僞
} ESBaseData;

//僗僥乕僔儑儞偺栚昗埵抲僨乕僞
typedef struct {
			double axis[NUMBER_OF_STATION_AXIS];							//僗僥乕僔儑儞偺栚昗埵抲僨乕僞
} ESStationData;

//堏摦柦椷僨乕僞乮捈岎嵗昗乯
typedef struct {
			ESMoveData		moveData;										//堏摦忣曬僨乕僞
			ESCartPosData	robotPos;										//儘儃僢僩偺栚昗埵抲僨乕僞
			ESBaseData		basePos;										//儀乕僗偺栚昗埵抲僨乕僞
			ESStationData	stationPos;										//僗僥乕僔儑儞偺栚昗埵抲僨乕僞
}ESCartMoveData;

//堏摦柦椷僨乕僞乮僷儖僗乯
typedef struct {
			ESMoveData		moveData;										//堏摦忣曬僨乕僞
			ESPulsePosData	robotPos;										//儘儃僢僩偺栚昗埵抲僨乕僞
			ESBaseData		basePos;										//儀乕僗偺栚昗埵抲僨乕僞
			ESStationData	stationPos;										//僗僥乕僔儑儞偺栚昗埵抲僨乕僞
			long			toolNo;											//僣乕儖斣崋
}ESPulseMoveData;

//1僶僀僩偺暋悢僨乕僞
typedef struct {
			char data[LENGTH_OF_MULTI_1];
}ESMultiByteData;

//2僶僀僩偺暋悢僨乕僞
typedef struct {
			short data[LENGTH_OF_MULTI_2];
}ESMultiShortData;

//2僶僀僩偺暋悢僨乕僞乮Unsigned乯
typedef struct {
			unsigned short data[LENGTH_OF_MULTI_2];
}ESMultiUShortData;

//LONG偺暋悢僨乕僞
typedef struct {
			long data[LENGTH_OF_MULTI_4];
}ESMultiLongData;

//DOUBLE偺暋悢僨乕僞
typedef struct {
			double data[LENGTH_OF_MULTI_4];
}ESMultiRealData;

//暥帤楍偺暋悢僨乕僞
typedef struct {
			char data[LENGTH_OF_MULTI_STR][LENGTH_OF_STRING+1];
}ESMultiStrData;

//ESPositionData偺暋悢僨乕僞
typedef struct {
			ESPositionData data[LENGTH_OF_MULTI_POS];
}ESMultiPositionData;

//ESBpexPositionData偺暋悢僨乕僞
typedef struct {
			ESBpexPositionData data[LENGTH_OF_MULTI_BPEX];
}ESMultiBpexPositionData;

#define STDCALL __stdcall

/*僐儅儞僪*/
//偦偺懠偺娭悢
LONG	STDCALL	ESOpen(long controllerType, char *ipAddress, HANDLE *handle);						//愙懕
LONG	STDCALL	ESClose(HANDLE handle);																//愗抐
LONG	STDCALL ESSetTimeOut(HANDLE handle, long timeOut, long retry);								//僞僀儉傾僂僩丒儕僩儔僀愝掕

//儕乕僪丒娔帇宯
LONG	STDCALL	ESGetAlarm(HANDLE handle, ESAlarmList *alarmList);									//敪惗拞傾儔乕儉撉傒弌偟
LONG	STDCALL	ESGetAlarmHist(HANDLE handle, long alarmHistNo, ESAlarmData *alarmData);			//傾儔乕儉棜楌撉傒弌偟
LONG	STDCALL	ESGetAlarmEx(HANDLE handle, ESAlarmListEx *alarmList);								//敪惗拞傾儔乕儉撉傒弌偟(僒僽僐乕僪暥帤楍懳墳)
LONG	STDCALL	ESGetAlarmHistEx(HANDLE handle, long alarmHistNo, ESAlarmDataEx *alarmData);		//傾儔乕儉棜楌撉傒弌偟(僒僽僐乕僪暥帤楍懳墳)
LONG	STDCALL	ESGetStatus(HANDLE handle, ESStatusData *statusData);								//僗僥乕僞僗撉傒弌偟
LONG	STDCALL	ESGetJobStatus(HANDLE handle, long taskNo, ESJobStatusData *jobStatusData);			//幚峴僕儑僽忣曬撉傒弌偟
LONG	STDCALL	ESGetConfiguration(HANDLE handle, long ctrlGrp, ESConfigurationData *configData);	//幉峔惉撉傒弌偟
LONG	STDCALL	ESGetPosition(HANDLE handle, long ctrlGrp, ESPositionData *positionData);			//儘儃僢僩埵抲偺撉傒弌偟
LONG	STDCALL	ESGetDeviation(HANDLE handle, long ctrlGrp, ESAxisData *deviationData);				//奺幉埵抲曃嵎撉傒弌偟
LONG	STDCALL	ESGetTorque(HANDLE handle, long ctrlGrp, ESAxisData *torqueData);					//奺幉僩儖僋偺撉傒弌偟
LONG	STDCALL ESGetMonitoringTime(HANDLE handle, long timeType, ESMonitoringTimeData *timeData);	//娗棟帪娫撉傒弌偟
LONG	STDCALL ESGetSystemInfo(HANDLE handle, long systemType, ESSystemInfoData *infoData);		//僔僗僥儉忣曬撉傒弌偟

//I/O儕乕僪丒儔僀僩宯
LONG	STDCALL	ESReadIO1(HANDLE handle, long ioNumber, short *ioData);								//IO僨乕僞偺撉傒弌偟
LONG	STDCALL	ESWriteIO1(HANDLE handle, long ioNumber, short ioData);								//IO僨乕僞偺彂偒崬傒
LONG	STDCALL	ESReadIO2(HANDLE handle, long ioNumber, short *ioData);								//IO僨乕僞偺撉傒弌偟乮1僶僀僩擖弌椡嬛巭巇條乯
LONG	STDCALL	ESWriteIO2(HANDLE handle, long ioNumber, short ioData);								//IO僨乕僞偺彂偒崬傒乮1僶僀僩擖弌椡嬛巭巇條乯
LONG	STDCALL	ESReadRegister(HANDLE handle, long regNumber, unsigned short *regData);				//儗僕僗僞僨乕僞偺撉傒弌偟
LONG	STDCALL	ESWriteRegister(HANDLE handle, long regNumber, unsigned short regData);				//儗僕僗僞僨乕僞偺彂偒崬傒
LONG	STDCALL	ESReadIOM(HANDLE handle, long ioNumber, long number, ESMultiByteData *ioData);		//IO僨乕僞偺撉傒弌偟(Multi)
LONG	STDCALL	ESWriteIOM(HANDLE handle, long ioNumber, long number, ESMultiByteData ioData);		//IO僨乕僞偺彂偒崬傒(Multi)
LONG	STDCALL	ESReadRegisterM(HANDLE handle, long regNumber, long number,							//儗僕僗僞僨乕僞偺撉傒弌偟(Multi)
								ESMultiUShortData *regData);
LONG	STDCALL	ESWriteRegisterM(HANDLE handle, long regNumber, long number,						//儗僕僗僞僨乕僞偺彂偒崬傒(Multi)
								 ESMultiUShortData regData);

//儕乕僪丒僨乕僞傾僋僙僗宯仌曇廤宯
LONG	STDCALL	ESGetVarData1(HANDLE handle, long type, long number, double *data);					//曄悢偺撉傒弌偟
LONG	STDCALL	ESSetVarData1(HANDLE handle, long type, long number, double data);					//曄悢偺彂偒崬傒
LONG	STDCALL	ESGetVarData2(HANDLE handle, long type, long number, double *data);					//曄悢偺撉傒弌偟乮1僶僀僩擖弌椡嬛巭巇條乯
LONG	STDCALL	ESSetVarData2(HANDLE handle, long type, long number, double data);					//曄悢偺彂偒崬傒乮1僶僀僩擖弌椡嬛巭巇條乯
LONG	STDCALL	ESGetStrData(HANDLE handle, long number, char *cp);									//暥帤宆曄悢(S)偺撉傒弌偟
LONG	STDCALL	ESSetStrData(HANDLE handle, long number, char *cp);									//暥帤宆曄悢(S)偺彂偒崬傒
LONG	STDCALL	ESGetPositionData(HANDLE handle, long number, ESPositionData *positionData);		//儘儃僢僩埵抲宆曄悢(P)偺撉傒弌偟
LONG	STDCALL	ESSetPositionData(HANDLE handle, long number, ESPositionData positionData);			//儘儃僢僩埵抲宆曄悢(P)偺彂偒崬傒
LONG	STDCALL	ESGetBpexPositionData(HANDLE handle, long type, long number,						//儀乕僗埵抲宆曄悢(BP)丒奜晹幉埵抲宆曄悢(EX)偺撉傒弌偟
									  ESBpexPositionData *positionData);
LONG	STDCALL	ESSetBpexPositionData(HANDLE handle, long type, long number,						//儀乕僗埵抲宆曄悢(BP)丒奜晹幉埵抲宆曄悢(EX)偺彂偒崬傒
									  ESBpexPositionData positionData);
LONG	STDCALL	ESGetVarDataMB(HANDLE handle, long varNo, long number, ESMultiByteData *varData);	//B曄悢偺撉傒弌偟(Multi)
LONG	STDCALL	ESSetVarDataMB(HANDLE handle, long varNo, long number, ESMultiByteData varData);	//B曄悢偺彂偒崬傒(Multi)
LONG	STDCALL	ESGetVarDataMI(HANDLE handle, long varNo, long number, ESMultiShortData *varData);	//I曄悢偺撉傒弌偟(Multi)
LONG	STDCALL	ESSetVarDataMI(HANDLE handle, long varNo, long number, ESMultiShortData varData);	//I曄悢偺彂偒崬傒(Multi)	
LONG	STDCALL	ESGetVarDataMD(HANDLE handle, long varNo, long number, ESMultiLongData *varData);	//D曄悢偺撉傒弌偟(Multi)
LONG	STDCALL	ESSetVarDataMD(HANDLE handle, long varNo, long number, ESMultiLongData varData);	//D曄悢偺彂偒崬傒(Multi)
LONG	STDCALL	ESGetVarDataMR(HANDLE handle, long varNo, long number, ESMultiRealData *varData);	//R曄悢偺撉傒弌偟(Multi)
LONG	STDCALL	ESSetVarDataMR(HANDLE handle, long varNo, long number, ESMultiRealData varData);	//R曄悢偺彂偒崬傒(Multi)
LONG	STDCALL	ESGetStrDataM(HANDLE handle, long varNo, long number, ESMultiStrData *varData);		//S曄悢偺撉傒弌偟(Multi)
LONG	STDCALL	ESSetStrDataM(HANDLE handle, long varNo, long number, ESMultiStrData varData);		//S曄悢偺彂偒崬傒(Multi)
LONG	STDCALL	ESGetPositionDataM(HANDLE handle, long varNo, long number,							//P曄悢偺撉傒弌偟(Multi)
								   ESMultiPositionData *positionData);
LONG	STDCALL	ESSetPositionDataM(HANDLE handle, long varNo, long number,							//P曄悢偺彂偒崬傒(Multi)
								   ESMultiPositionData positionData);
LONG	STDCALL	ESGetBpexPositionDataM(HANDLE handle, long type, long varNo, long number,			//BP曄悢丒EX曄悢偺撉傒弌偟(Multi)
									   ESMultiBpexPositionData *positionData);
LONG	STDCALL	ESSetBpexPositionDataM(HANDLE handle, long type, long varNo, long number,			//BP曄悢丒EX曄悢偺彂偒崬傒(Multi)
									   ESMultiBpexPositionData positionData);

//憖嶌宯
LONG	STDCALL	ESReset(HANDLE handle);																//儕僙僢僩
LONG	STDCALL	ESCancel(HANDLE handle);															//僉儍儞僙儖
LONG	STDCALL	ESHold(HANDLE handle, long onOff);													//儂乕儖僪
LONG	STDCALL	ESServo(HANDLE handle, long onOff);													//僒乕儃僆儞
LONG	STDCALL	ESHlock(HANDLE handle, long onOff);													//PP偲IO偺憖嶌宯怣崋偺僀儞僞儘僢僋
LONG	STDCALL	ESCycle(HANDLE handle, long cycle);													//僗僥僢僾/僒僀僋儖/楢懕帺摦
LONG	STDCALL	ESBDSP(HANDLE handle, char *message);												//儁儞僟儞僩傊偺暥帤楍昞帵

//婲摦宯
LONG	STDCALL	ESStartJob(HANDLE handle);															//僕儑僽僗僞乕僩
LONG	STDCALL ESCartMove(HANDLE handle, long moveType, ESCartMoveData moveData);					//堏摦柦椷乮捈岎嵗昗乯
LONG	STDCALL ESPulseMove(HANDLE handle, long moveType, ESPulseMoveData moveData);				//堏摦柦椷乮僷儖僗乯

//僕儑僽慖戰宯
LONG	STDCALL	ESSelectJob(HANDLE handle, long jobType, long lineNo, char *jobName);				//僕儑僽慖戰

//僼傽僀儖惂屼宯
LONG	STDCALL	ESSaveFile(HANDLE handle, char *savePath, char *fileName);							//僼傽僀儖僙乕僽
LONG	STDCALL	ESLoadFile(HANDLE handle, char *filePath);											//僼傽僀儖儘乕僪
LONG	STDCALL	ESDeleteJob(HANDLE handle, char *jobName);											//僕儑僽嶍彍
LONG	STDCALL	ESFileListFirst(HANDLE handle, long fileType, char *fileName);						//僼傽僀儖儕僗僩偺峏怴偟愭摢傪撉傒崬傓
LONG	STDCALL	ESFileListNext(HANDLE handle, char *fileName);										//僼傽僀儖儕僗僩傪撉傒崬傓
#undef AFX_DATA
#define AFX_DATA


//Qin Zhengke
//注意：这里一定要用下面的语句取消四字节对齐，否则4字节对齐会影响其他头文件，产生莫名其妙
//的问题，例如：结构体最后一个变量赋值永远出错。
#pragma pack()
