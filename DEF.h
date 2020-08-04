#define WINVER 0x0501
#define _WIN32_IE 0x0400
#define _WIN32_WINNT 0x0502
#include <windows.h>
#include <commctrl.h>
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sleep                   Sleep
#define msgc                    printf
#define Image( H_B, H_W )       SendMessage( H_W, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)H_B)
#define RETURN                  }
#define FUNCTION                void
#define IF                      if(
#define THEN                    ){
#define ELSE                    }else{
#define ELSIF                   }else if(
#define ENDIF                   }
#define endwhile                }
#define endfor                  }
#define FOR                     for(
#define WHILE(definebools)      while(definebools){
#define LOOP                    ){
#define ENDLOOP                 }
#define BREAK                   break
#define ENDCASE                 }}
#define END                     }
#define ENDWHILE                }
#define ENDCONTROLSCOMAND       break;}break;
#define ENDWPROC                return 0;}
#define ENDMESSAGES             ENDCASE
#define ENDMAINWINDOW           return 0;}
#define WPROC                   LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam){
#define CONTROLS_COMAND         case WM_COMMAND: switch( LOWORD(wParam) ){
#define MAINWINDOW              int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil){
#define CASE                    switch(
#define IS                      ){{
#define MESSAGES                CASE( message )IS
#define WHEN(id)                }break;case id:{
#define SEQWHEN(id)             }break;case id:{
#define DEFAULT                 }break;default:{
#define GET_BIT(var,pos)        ( (((var) & (1<<(pos))))/( 1<<(pos)) )
#define CHECK_BIT(var,pos)      ( (((var) & (1<<(pos))))/( 1<<(pos)) )
#define CHECK_BITM(var,pos)     ( (((var) & (1<<(pos))))/( 1<<(pos)) )
#define SizeOf(T)               sizeof(T)/sizeof(T[0])
#define BitesOf(T)              sizeof(T[0])
//#define FILLVAR(VAR)            for( int i=0; i<SizeOf(VAR); i++ )VAR[i] = i;
#define KILOBYTES               1024
#define KBs                     KILOBYTES
#define MEGABYTES               1048576
#define MBs                     MEGABYTES
#define MAX_UINT                2147483647
#define MSGBOX                  msgbox
#define pi                      3.14159//26535897932384626433832795
//*/

HWND HWFCon( void ){
HWND HWCon = GetConsoleWindow();
IF HWCon==NULL THEN
   AllocConsole();
   HWCon = GetConsoleWindow();
ENDIF;
ShowWindow(HWCon, 0 );
return HWCon;
}



BOOL                        PermissionAJC = FALSE;
BOOL                        Permission = FALSE;
HWND VENTANA_PADRE=NULL;
HWND CONSOLA_PADRE=HWFCon();
HINSTANCE INSTANCIA_GLOBAL;
char  TextoGlobal[40*KBs];
const RGBQUAD VERDE = {0, 255, 0, 0};
const RGBQUAD NEGRO = {0, 0, 0, 0};
const RGBQUAD BLANCO = {255, 255, 255, 0};
const RGBQUAD GRIS = {128, 128, 128, 0};

LRESULT CALLBACK WindowProcedure(HWND , UINT  , WPARAM , LPARAM );
DWORD WINAPI ThreadCommands( LPVOID );
double definedoubles=0;
HWND CONSOLA_VENTANA_PADRE=NULL;
HACCEL HAcelerador_GLOBAL;
BOOL GLOBALQUIT_GLOBAL = FALSE;
BOOL SHOWMENU_GLOBAL = TRUE;
HMENU MENUGLOBAL;
HMENU MENUGLOBALPOUP;
char  GLOBAL_ACTUAL_DIRECTORY[MAX_PATH];
char  GLOBAL_ACTUAL_MODULE_NAME[MAX_PATH];
char  CUSER[256];
DWORD GLOBAL_PROCESSID;


HANDLE   EventControls;
HWND     HWThread;
WPARAM   wParamC;
LPARAM   lParamC;
BOOL     INPROCESS = FALSE;



int  CursorX;
int  CursorY;
double EndToc = 0;
void GetModuleInfo( HINSTANCE hThisInstance )
{
GLOBAL_PROCESSID = GetCurrentProcessId();
GetModuleFileNameA( hThisInstance , GLOBAL_ACTUAL_DIRECTORY , GLOBAL_PROCESSID );
GetModuleFileNameA( hThisInstance , GLOBAL_ACTUAL_MODULE_NAME , GLOBAL_PROCESSID );

int LenC = strlen( GLOBAL_ACTUAL_DIRECTORY );
while( GLOBAL_ACTUAL_DIRECTORY[LenC]!='\\' ){
    GLOBAL_ACTUAL_DIRECTORY[LenC] = 0;
    LenC--;
}
GLOBAL_ACTUAL_DIRECTORY[LenC] = 0;
}






int msgbox( LPCSTR Textout="", LPCSTR titulo="", unsigned int option=0 ){
// VENTANA_PADRE
//int i = MessageBox( GetActiveWindow() , Textout , titulo , option );
HWND HWnd = VENTANA_PADRE;
if( HWnd==NULL ){
    HWnd = GetActiveWindow();
}
if( HWnd==NULL ){
    HWnd = GetConsoleWindow();
}
if( HWnd==NULL ){
    HWnd = FindWindowA( NULL, "" );
}
int i = MessageBox( HWnd , Textout , titulo , option );
return i;
}



#include <stdio.h>
////////////////////////////////////////////////////////////////////////////////
int msgboxf( const char* szTypes, ... ){
static char* Text2;
if( Text2!=NULL ){
    //free( &Text2[0] );
}
DWORD LCIn = strlen( &szTypes[0] );
Text2 = (char*)malloc( 64*LCIn );

va_list arguments;
va_start ( arguments, szTypes );
vsnprintf( Text2, 64*LCIn, szTypes, arguments );

int VRet = msgbox( &Text2[0] );
free( &Text2[0] );
Text2 = NULL;
return VRet;
}
////////////////

////////////////
////////////////////////////////////////////////////////////////////////////////
int msgboxErrorf( const char* szTypes, ... ){
static char* Text2;
if( Text2!=NULL ){
    //free( &Text2[0] );
}
DWORD LCIn = strlen( &szTypes[0] );
Text2 = (char*)malloc( 64*LCIn );

va_list arguments;
va_start ( arguments, szTypes );
vsnprintf( Text2, 64*LCIn, szTypes, arguments );

int VRet = msgbox( &Text2[0], " Error ", 16 );
free( &Text2[0] );
Text2 = NULL;
return VRet;
}////////////////////////////////////////////////////////////////


////////////////
////////////////////////////////////////////////////////////////////////////////
int msgboxErrorf( HWND H_W, const char* szTypes, ... ){
static char* Text2;
if( Text2!=NULL ){
    //free( &Text2[0] );
}
DWORD LCIn = strlen( &szTypes[0] );
Text2 = (char*)malloc( 64*LCIn );

va_list arguments;
va_start ( arguments, szTypes );
vsnprintf( Text2, 64*LCIn, szTypes, arguments );

int VRet = MessageBoxA( H_W, &Text2[0], " Error ", 16 );
free( &Text2[0] );
Text2 = NULL;
return VRet;
}////////////////////////////////////////////////////////////////


