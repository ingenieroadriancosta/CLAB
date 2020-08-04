#include <stdio.h>
#include <time.h>
#include <math.h>
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////










void Text2Edit( char* TextEditOut , const char* TextEditIn )
{
TextEditOut[0] = '\0';
int indiceInit = 0;
int MaxLenStr = strlen( TextEditIn );
TextEditOut[0] = 0;
FOR int i=0; i<MaxLenStr; i++ LOOP
    IF TextEditIn[i]=='\n' THEN
       TextEditOut[indiceInit] = 13;
       indiceInit++;
       TextEditOut[indiceInit] = '\n';
    ELSE
       TextEditOut[indiceInit] = TextEditIn[i];
    ENDIF;
    indiceInit++;
ENDLOOP;
TextEditOut[indiceInit] = '\0';
TextEditOut[indiceInit+1] = '\0';
}




void GetFileNameA( char* PathPlusFileName, char* FileNameTitle )
{
#ifndef CONSOLEWINDOWCLASS
int LenStr = strlen( PathPlusFileName );

GetFileTitleA( PathPlusFileName , FileNameTitle, LenStr );
LenStr = strlen( FileNameTitle );
while( FileNameTitle[LenStr]!='.' ){
       FileNameTitle[LenStr] = '\0';
       LenStr--;
       }
FileNameTitle[LenStr] = '\0';
#endif
}

void GetFilePathA( char* PathPlusFileName, char* FileNamePath )
{
int LenStr = strlen( PathPlusFileName );
strcpy( FileNamePath, PathPlusFileName);
while( FileNamePath[LenStr]!='\\' ){
       FileNamePath[LenStr] = '\0';
       LenStr--;
       }
}




//MTIME///////////////////////// T I M E___S E R I E S /////////////////////////
double TIME_SERIES_CTIC;//VARIABLES GLOBALES DE TIEMPO.
double TIME_SERIES_CTOC;//VARIABLES GLOBALES DE TIEMPO.
                                       //
double tic()   //TIC -TIC-TIC -TIC-TIC -TIC-TIC -TIC-TIC -TIC-TIC -TIC-TIC " TIC "
{//INICIA LA VARIABLE DE TEIMPO GLOBAL adrianti.
     TIME_SERIES_CTIC=clock();
     return(TIME_SERIES_CTIC);
}//END TIC.
                                       //
double toc()  //TOC -TOC-TOC -TOC-TOC -TOC-TOC -TOC-TOC -TOC-TOC -TOC-TOC " TOC "
 {//RETORNA EL TIEMPO TRANSCURRIDO DESDE QUE SE LLAMÓ LA FUNCION TOC.
      TIME_SERIES_CTOC=(clock()-TIME_SERIES_CTIC)/1000.0;
      return(TIME_SERIES_CTOC);
 }//END TOC.

#define pause(definedoubles)   pause(definedoubles);
#define tic                    tic();
#define toc                    toc()

//////////////////////// C O N S O L E___S E R I E S__E N D ////////////////////




unsigned int CFGWindow = 90;
bool regclass( HINSTANCE hThisInstance , WNDPROC WindowProcedure ,
               LPCSTR szClassName= "WindowsApp",
               LPCSTR Icono="A", LPCSTR Menu=NULL,
               int R=200, int G=200, int B=200, LPCSTR DWCursor=IDC_ARROW  )
{
INSTANCIA_GLOBAL = hThisInstance;
GetModuleInfo( hThisInstance );
WNDCLASSEX wincl;
wincl.hInstance = hThisInstance;
wincl.lpszClassName = (LPCSTR)(szClassName);
wincl.lpfnWndProc = WindowProcedure;
wincl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//CS_DBLCLKS | CS_SAVEBITS;//CS_DBLCLKS;
wincl.style = CS_DBLCLKS;//CS_DBLCLKS | CS_SAVEBITS;//CS_DBLCLKS;
wincl.cbSize = sizeof (WNDCLASSEX);

wincl.hIcon = LoadIcon( hThisInstance , Icono );
wincl.hIconSm = LoadIcon( hThisInstance , Icono );
wincl.hCursor = LoadCursor( NULL, DWCursor );

wincl.lpszMenuName = Menu ;
wincl.cbClsExtra = 0;
wincl.cbWndExtra = 0;
//wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
wincl.hbrBackground = (HBRUSH)CreateSolidBrush( RGB( R , G , B ) );//COLOR_BACKGROUND;




if (!RegisterClassEx (&wincl))
    return false;
return true;
}


//////////////////////
//////////////////////
BOOL SetToolTipW( HWND HWnd, char* W_TextF ){
TOOLINFO           TInfoF;
HWND HW_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                    WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | WS_BORDER,
                                    0, 0, 0, 0, HWnd, NULL, NULL, NULL );
RECT Rect;
GetClientRect ( HWnd, &Rect );
TInfoF.cbSize = sizeof(TOOLINFO);
TInfoF.uFlags = TTF_SUBCLASS;
TInfoF.hwnd = HWnd;
TInfoF.hinst = NULL;
TInfoF.uId = 0;
TInfoF.lpszText = &W_TextF[0];
TInfoF.rect.left = Rect.left;
TInfoF.rect.top = Rect.top;
TInfoF.rect.right = Rect.right;
TInfoF.rect.bottom = Rect.bottom;
SendMessage( HW_ToolTip, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&TInfoF );

return TRUE;
}
//////////////////////
BOOL SetToolTipW( HWND HWnd, int I_TextF ){
char WTextF[256];
LoadString( INSTANCIA_GLOBAL, I_TextF, WTextF, 255);
return SetToolTipW( HWnd, WTextF );
}
////////////////////////////

void SetIcon( char* icono, HWND hwnd=VENTANA_PADRE,HINSTANCE hInstance=INSTANCIA_GLOBAL)
{
HICON hIcon;
hIcon = LoadIconA( hInstance , icono );
SendMessage( hwnd , WM_SETICON , ICON_SMALL , (LPARAM)hIcon );
SendMessage( hwnd , WM_SETICON , ICON_BIG , (LPARAM)hIcon );
}
//

void SetIcon( int IReso, HWND hwnd=VENTANA_PADRE,HINSTANCE hInstance=INSTANCIA_GLOBAL )
{
HICON hIcon;
hIcon = LoadIconA( hInstance , MAKEINTRESOURCE(IReso) );
SendMessage( hwnd , WM_SETICON , ICON_SMALL , (LPARAM)hIcon );
SendMessage( hwnd , WM_SETICON , ICON_BIG , (LPARAM)hIcon );
}




inline bool ISDOWNKEY( int Key = VK_SPACE )
{
return bool(GetKeyState( Key )& 0x80);
}



inline void CursorPos( int* x, int* y)
{
POINT punto;
GetCursorPos(&punto);
*x = punto.x;
*y = punto.y;
};

inline void WindowSize(HWND hwnd, int* w , int* h )
{
RECT re;
GetClientRect(hwnd, &re);
w[0] = re.right;
h[0] = re.bottom;
}

inline void WindowPos(HWND hwnd, int* x,int* y)
{
POINT pos;
POINT posF;
pos.x=0;
pos.y=0;

posF.x=0;
posF.y=0;

ClientToScreen( hwnd, &pos);

HWND hwndP = GetParent( hwnd );
if( hwndP==NULL ){
    x[0] = pos.x;
    y[0] = pos.y;
}else{
    ClientToScreen( hwndP, &posF );
    x[0] = pos.x - posF.x;
    y[0] = pos.y - posF.y;
}

//GetWindowPos(hwnd, pos);

}




const int oiuX = 10;
const int oiuY = 32;
HWND TOPMOST( HWND hwnd=NULL , bool sel=true , int SW_STYLE = SW_NORMAL )
{
int posw_x = 0 , posw_y = 0 ;
HWND tipo;
HWND HWindow;
if ( sel == true )
   tipo = HWND_TOPMOST;
else
   tipo = HWND_NOTOPMOST;
IF hwnd == NULL THEN
   char NAMEEXE[256];
   int ID = (int)GetCurrentProcessId();
   GetModuleFileNameA( NULL , NAMEEXE , ID );
   HWindow = FindWindowA("consoleWindowClass", NAMEEXE );
   if( HWindow==NULL )
       HWindow = FindWindowA("consoleWindowClass", NULL );
   WindowPos( HWindow , &posw_x, &posw_y);
   SetWindowPos( HWindow , tipo ,
                              posw_x - oiuX , posw_y - oiuY , 300 , 300 , 1 );
ELSE
   HWindow = hwnd;
   WindowPos( hwnd , &posw_x, &posw_y);
   SetWindowPos( hwnd , tipo ,
                              posw_x - oiuX , posw_y - oiuY , 300 , 300 , 1 );
ENDIF;

ShowWindow( HWindow , SW_STYLE );
return HWindow;
}









int CXSCREEN;
int CYSCREEN;

int CXFULLSCREEN;
int CYFULLSCREEN;
int CYMENU;

int beforeW;
int beforeH;
int beforeX;
int beforeY;
bool Wmaximized = false;
bool Maxed = false;
bool MaximizandoWindow = false;
bool maximizar( HWND hwnd=VENTANA_PADRE, HWND Opt=HWND_NOTOPMOST  ){

CXSCREEN = GetSystemMetrics( SM_CXSCREEN );
CYSCREEN = GetSystemMetrics( SM_CYSCREEN );

CXFULLSCREEN = GetSystemMetrics( SM_CXFULLSCREEN );
CYFULLSCREEN = GetSystemMetrics( SM_CYFULLSCREEN );


MaximizandoWindow = TRUE;
IF Wmaximized == false THEN
   Wmaximized = true;
   int WW = 0, HH = 0;
   WindowSize( hwnd, &WW, &HH );

   IF !GetMenu(hwnd) THEN
      IF WW!=GetSystemMetrics( SM_CXFULLSCREEN ) || HH!=GetSystemMetrics( SM_CYFULLSCREEN ) THEN
         WindowSize( hwnd, &beforeW, &beforeH );
         WindowPos( hwnd, &beforeX, &beforeY );
         Maxed = false;
      ELSE
         Maxed = true;
      ENDIF;
   ELSE
      IF WW!=(GetSystemMetrics( SM_CXFULLSCREEN )) ||
                                HH!=(GetSystemMetrics( SM_CYFULLSCREEN ) - GetSystemMetrics( SM_CYMENU ) ) THEN

         WindowSize( hwnd, &beforeW, &beforeH );
         WindowPos( hwnd, &beforeX, &beforeY );
         Maxed = false;
      ELSE
         Maxed = true;
      ENDIF;
   ENDIF;
      SetWindowLong( hwnd , GWL_STYLE , WS_POPUP );
      ShowWindow( hwnd , SW_MAXIMIZE );
ELSE
   Wmaximized = false;
   SetWindowLong( hwnd , GWL_STYLE, WS_OVERLAPPEDWINDOW );


   IF !GetMenu(hwnd) THEN
      SetWindowPos( hwnd, Opt, beforeX-8, beforeY-30, beforeW+16, beforeH+38, 0 );
      //  MoveWindow( hwnd, beforeX-8, beforeY-30, beforeW+16, beforeH+38, TRUE );
   ELSE
      SetWindowPos( hwnd, Opt, beforeX-8, beforeY-30-GetSystemMetrics( SM_CYMENU ), beforeW+16, beforeH+38+GetSystemMetrics( SM_CYMENU ), 0 );
      //  MoveWindow( hwnd, beforeX-8, beforeY-30, beforeW+16, beforeH+38+GetSystemMetrics( SM_CYMENU ), TRUE );
   ENDIF;
   //*/



   if( Maxed==true )
       ShowWindow( hwnd , SW_MAXIMIZE );
   else
       ShowWindow( hwnd , SW_RESTORE );
   SendMessage( hwnd, WM_EXITSIZEMOVE, 0, 0 );
ENDIF;
MaximizandoWindow = FALSE;
return Wmaximized;
}











double abs( double DVal ){
if( DVal<0 ){DVal = -DVal;}
return DVal;
}


















////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <sys/stat.h>

BOOL IsFile( char* NFile ){
    struct stat st;
    stat( NFile, &st );
    return S_ISREG(st.st_mode);
}
//

BOOL IsDir( char* NFile ){
    struct stat st;
    stat( NFile, &st );
    return S_ISDIR(st.st_mode);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DWORD EnumFiles_IF( LPSTR LP_DIR, char** FNamesPtr ){
    WIN32_FIND_DATA findFileData = {0};
    HANDLE          hFind = NULL;
    int NFold = 0;
    int IdFAt = 0;
    int StrL = strlen( LP_DIR );
    char* DiarAct = (char*)malloc( StrL + 1024 );
    strcpy( DiarAct, LP_DIR );
    strcat( DiarAct, "\\*" );
    hFind = FindFirstFile( DiarAct, &findFileData );
    if( hFind == INVALID_HANDLE_VALUE ){
        free( DiarAct );
        exit( -1231231 );
        return 0;
    }
    do{
        IdFAt = findFileData.dwFileAttributes;
        IdFAt++;
        /// msgboxf( "IdFAt = %i\nFName,\n%s", IdFAt, findFileData.cFileName );
        // msgboxf( "%s\n%i", findFileData.cFileName, IdFAt );
        //MAXDWORD
        if( findFileData.cFileName[0]!='.' ){
        /// if( IdFAt==32 || IdFAt==16 || IdFAt==8230 || IdFAt==8224 || IdFAt==9238 ){
            ///msgboxf( "IdFAt = %i\nFName,\n%s", IdFAt, findFileData.cFileName );
            if( FNamesPtr!=NULL ){
                sprintf( FNamesPtr[NFold], "%s", findFileData.cFileName );
            }
            NFold++;
            ///
        }
    }while( FindNextFile(hFind, &findFileData) != 0 );
    free( DiarAct );
    return NFold;
}



