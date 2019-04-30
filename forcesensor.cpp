#include "forcesensor.h"
#include"QFile"
#include"QTextStream"
int32 EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData)
{
    int32       error=0;
    char        errBuff[2048]={'\0'};
    static int  totalRead=0;
    int32       read=0;
    float64     data[6];

    ForceSensor * forceSensorObject = (ForceSensor* )callbackData;

    /*********************************************/
    // DAQmx Read Code
    /*********************************************/
   DAQmxReadAnalogF64(taskHandle,-1,10.0,DAQmx_Val_GroupByScanNumber,data,6,&read,NULL);

    if( read>0 )
    {
        totalRead += read;
//        std::cout<<"Acquired "<<read<<" samples. Total "<< totalRead<<std::endl;
        fflush(stdout);

        char *calfilepath = "config/FT17734.cal";
        Calibration *cal = NULL;		// struct containing calibration information
        cal = createCalibration(calfilepath, 1);
        if (cal==NULL) {
            printf("\nSpecified calibration could not be loaded.\n");
            scanf(".");
            return 0;
        }

        short sts;              // return value from functions
        // Set force units.
        // This step is optional; by default, the units are inherited from the calibration file.
        sts=SetForceUnits(cal,"N");
        switch (sts) {
            case 0: break;	// successful completion
            case 1: printf("Invalid Calibration struct"); return 0;
            case 2: printf("Invalid force units"); return 0;
            default: printf("Unknown error"); return 0;
        }


        // Set torque units.
        // This step is optional; by default, the units are inherited from the calibration file.
        sts=SetTorqueUnits(cal,"N-m");
        switch (sts) {
            case 0: break;	// successful completion
            case 1: printf("Invalid Calibration struct"); return 0;
            case 2: printf("Invalid torque units"); return 0;
            default: printf("Unknown error"); return 0;
        }

        float data_32[6];
        for(int i=0; i<6; i++)
            data_32[i] = (float)data[i];


        float ft[6];
        // convert a loaded measurement into forces and torques
        ConvertToFT(cal, data_32, ft);



        emit forceSensorObject->sendForceData(Force6D(ft[0],ft[1],ft[2],ft[3],ft[4],ft[5]));

        emit forceSensorObject->onlineStatus(true);

    }
    else
    {
        emit forceSensorObject->onlineStatus(false);
    }

Error:
    if( DAQmxFailed(error) ) {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
        printf("DAQmx Error: %s\n",errBuff);
    }
    return 0;
}

int32 DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData)
{
    int32   error=0;
    char    errBuff[2048]={'\0'};

    // Check to see if an error stopped the task.
//    DAQmxErrChk (status);

Error:
    if( DAQmxFailed(error) ) {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        DAQmxClearTask(taskHandle);
        printf("DAQmx Error: %s\n",errBuff);
    }
    return 0;
}

ForceSensor::ForceSensor(QObject *parent) : QObject(parent)
{
    // NI DAQ mx

    taskHandle=0;


}

void ForceSensor::onInit()
{
    emit sendMessage(tr("Init force sensor..."));
    int32       error=0;
    char        errBuff[2048]={'\0'};

    int32       Read=0;
    float64     Sata[6];
    /*********************************************/
    // DAQmx Configure Code
    /*********************************************/
    if(0 != DAQmxCreateTask("",&taskHandle))
    {
        emit sendMessage(tr("Cannot create NI-DAQMAX task!"));
        emit initDone(false);
        return ;
    }
    if(0 != DAQmxAddGlobalChansToTask(taskHandle, "FFx,FFy,FFz,TTx,TTy,TTz"))
    {
        emit sendMessage(tr("Cannot add channel to NI-DAQMAX task!"));
        emit initDone(false);
        return ;
    }
    if(0 != DAQmxCfgSampClkTiming(taskHandle,"",10.0,DAQmx_Val_Rising,DAQmx_Val_ContSamps,1000))
    {
        emit sendMessage(tr("Cannot config sample timing for NI_DAQMAX!"));
        emit initDone(false);
        return ;
    }


    DAQmxRegisterEveryNSamplesEvent(taskHandle,DAQmx_Val_Acquired_Into_Buffer,1,0, EveryNCallback, (void*)this);
    DAQmxRegisterDoneEvent(taskHandle,0, DoneCallback,NULL);

    /*********************************************/
    // DAQmx Start Code
    /*********************************************/
    if(0 != DAQmxStartTask(taskHandle))
    {
        emit sendMessage(tr("Cannot start NI-DAQMAX task!"));
        emit initDone(false);

        return ;
    }

    printf("Acquiring samples continuously. Press Enter to interrupt\n");

    emit sendMessage(tr("Done!"));

    emit initDone(true);

}

ForceSensor::~ForceSensor()
{

}

