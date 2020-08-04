
char                        FileIn1G[1024];

HWND                        HWLogoUPC;

HCURSOR                     HCurHand;
HCURSOR                     HCurDHand;

BOOL                        InGuiSave = FALSE;
HWND                        HWGuiSave = NULL;

BOOL                        InVista = FALSE;
BOOL                        FShowInVista = TRUE;
HWND                        HWInVista = NULL;
BYTE                        VALPHA_VISTA = 180;
BOOL                        PostQuit= FALSE;

BYTE                        VALPHA_MAIN = 255;
BOOL                        SetTransparent = TRUE;
BOOL                        AllOk = FALSE;
BOOL                        ShHiCon;

char                        szClassConsole[256];
char                        szClassName[256];
char                        ClassDataCursor[256];
char                        ClassDataCursorInfo[256];
char                        ClassPanel[256];

char                        WTitle[256];
char                        TDataFile[ 256 ] = "_NewFile.csv";
char                        MatFile[ 256 ] = "_NewFile.mat";


char                        CPortName[256];





HBITMAP                     HB_Fondo;
BITMAP                      B_Fondo;

HBITMAP                     HB_FondoPanel;
BITMAP                      B_FondoPanel;





HBITMAP                     HB_CButt_C[4];



HCURSOR                     HCursorG;

//Cursores


// Controles.
//HWND                        HWCInfo;
//HWND                        HWCFrame;
HWND                        HW_Cal;
HWND                        HWPrb;


#define  XPosWCFrame    1
#define  YPosWCFrame    1
#define  WCFrame        1
#define  HCFrame      129
#define  HCFrameBig   (HCFrame+18)
int                         WFather;
int                         HFather;


int                         VXCFrame = 1;// + 15;
int                         VHCFrame = HCFrame;// + 15;


int                         IFocus;

HWND                        HWPanel;
HWND                        HWCFrame;
SCROLLINFO                  Sinfo;

HWND                        HWTs;
HWND                        HWCOMPort;
HWND                        HWTime;


TagBMPButton                BOpen;
TagBMPButton                BSave;
TagBMPButton                BExport;

TagBMPButton                BSaveBMP;
TagBMPButton                BComp;
TagBMPButton                BNew;


TagBMPButton_Toggle         BVista;
TagBMPButton                BZoomIn;
TagBMPButton                BZoomOut;
TagBMPButton                BAuto;
TagBMPButton                BRedraw;

TagBMPButton                BCopy;

HWND                        HWDataCurAll;
HWND                        HWDataCur[4];






HWND                        HWB_ValB;
HWND                        HWB_Val;

HWND                        HWB_Val_Min;
HWND                        HWD_Val_Min;




HWND                        HWD_ValB;
HWND                        HWD_Val;



HWND                        HWSel_All_In;
HWND                        HWSel_All_Out;


HWND                        HWSel_Chann0_In;
HWND                        HWSel_Chann1_In;
HWND                        HWSel_Chann0_Out;
HWND                        HWSel_Chann1_Out;





HWND                        HWSel_Color_Chann0_In;
HWND                        HWSel_Color_Chann1_In;
HWND                        HWSel_Color_Chann0_Out;
HWND                        HWSel_Color_Chann1_Out;


HWND                        HWClose;
HWND                        HWResMax;
HWND                        HWMin;




HWND                        HWPwmSend;
HWND                        HWPwm1;
HWND                        HWPwm2;


HFONT                       HFont;
HFONT                       HFont_S;
HFONT                       HFontFs;
HFONT                       HFontFsSq;
HFONT                       HFontComm;


HFONT                       HFontPaintP;



HFONT                       HFontButts;




// TagBMPButton_Toggle         BPruebas;
TagBMPButton_Toggle         BConnect;

//TagBMPButton_Toggle         BSQ_Wave0;
//TagBMPButton_Toggle         BSQ_Wave1;


HWND                        HWCB_SQ_Wave0;
HWND                        HWCB_SQ_Wave1;


StaticStatus                TimeStatus;


StaticStatus                Input1Status;
StaticStatus                Input2Status;





StaticStatus                Mp[2];
StaticStatus                Ep[2];
Button                      BtnMp[2];
Button                      BtnEp[2];
unsigned short              USMpActual[2];
unsigned short              USEpActual[2];
int                         S_EP1122[2] = { 1, 3 };
TagBMPButton                BUndock;




HWND                        HWFs_Out0;
HWND                        HWFs_Out1;

/*
const unsigned short        FsOuts[32] = {    1,    2,   4,     5,
                                             10,   20,  25,    50,
                                            100,  200,  400,  800,
                                           2000, 4000,    1,    1 };
//*/
const unsigned short        FsOuts[32] = {    1,    2,   4,     10,
                                             20,   40,  100,    200,
                                            400,  1000,  2000,  400,
                                           1000, 2000,    1,    1 };


HBRUSH                      pincel;

BOOL                        Connected;



int                         SetSQWave0 = 0;
int                         SetSQWave1 = 0;
BYTE                        CursSQ0[4];
BYTE                        CursSQ1[4];

BYTE                        VSQ_Wave0;
BYTE                        VSQ_Wave1;


BOOL                        InConnect;
BOOL                        SendVoltA = FALSE;
BOOL                        SendVoltB = FALSE;

BOOL                        SetPlot = FALSE;
BOOL                        SetPlotRes = FALSE;

BOOL                        IsMinimized;

// Buffers.
//BYTE*                       BInData;
BYTE                        BInData[MBs];

class TagBuffers{
public:
TagBuffers(){
     USData=NULL;
     Show = TRUE;
}
~TagBuffers(){
     if( USData ){free( USData );USData=NULL;}
}
unsigned short*   USData;
BOOL              Show;
};
TagBuffers                  BuffData[4];
WORD                        Divisor = 255;



const int                   EndPoint = 16;
const int                   EndBuf = EndPoint-1;
const int                   MEndPoint = 1*EndPoint;// 4
/*--------------------------------------*/
 int                   TopDTime = 300;
int                         DTime = 150;
/*--------------------------------------*/

DWORD                       BAvailable;
DWORD                       MBAvailable;





///#define  VoltPrb00 0
#ifdef VoltPrb00
double                      B_Val = 4;
double                      D_Val = 3;

double                      B_Val_Min = 1;
double                      D_Val_Min = 2;
#else

double                      B_Val = 5;
double                      D_Val = 5;

double                      B_Val_Min = 0;
double                      D_Val_Min = 0;

#endif



double                      A0_Val = 0;
double                      A1_Val = 0;

double                      B0_Val = 0;
double                      D1_Val = 0;

WORD                        BPwm1;
WORD                        BPwm2;


const int                   MaxFsReal = 2000;

int                         CurTs = 0;
const WORD                  Cur2Send[16] = {    0,     2,     4,   10, // 5ms
                                               20,    40,   100,   200,// 100ms
                                              400,  1000,  2000,  4000,// 2s
                                            10000, 20000, 65535, 65535 };
// Con Fs's MaxFsReal = 2000;
const double                CurFs[16] = {     1,     2,     4,    10, // 5ms
                                             20,    40,   100,   200,// 100ms
                                            400,  1000,  2000,  4000,// 1s
                                          10000, 20000, 65535, 65535 };
WORD                        Fs = 1;
double                      FsReal = (double)MaxFsReal;


double                      Max_Volt;
double                      Volt_In_Out[5];
//const double                      Volt_Out = 5;


int                         NFramesReaded = DTime*Fs;
int                         DiffIE = NFramesReaded;
const int                   MaxBuffs = (TopDTime*MaxFsReal);
const int                   SizeBuff = 4*MaxBuffs*sizeof(WORD) + 10*1024;
const int                   SizeBuffMed = SizeBuff/2 - 1;
BOOL                        MActivate = FALSE;

int                         InitFrames = 0;
int                         EndFrames = MaxBuffs;



int                         GStyle = 1;
BOOL                        ActGStyle = TRUE;
BOOL                        InvGrid;
BOOL                        OnTop = FALSE;

int                         LineWidth = 1;



int                         ComPort = 1;





int                         PltrNDiv = 1;



int                         WPan;
int                         HPan;






////////////////// cursor
HWND                        HWCursor[4];
HWND                        HWCursorInfo[4];
HWND                        HWCursorText[4];

BOOL                        EnDataCursor[4];
BOOL                        EnAllDCursor = TRUE;

BOOL                        DivGraph = FALSE;

BOOL                        CActivate = FALSE;

int                         PosBuff[4] = { 0, (DTime*Fs)/4, (2*DTime*Fs)/4, (3*DTime*Fs) };


HBRUSH                      WCHbrsh[4];
RECT                        WCRre;











////////////////////////
BOOL InMaxWin = FALSE;
int LastXPos;
int WWidth;
int HHeigth;
BOOL ActSize;
BOOL IsMaxed;
//////////////////////////




