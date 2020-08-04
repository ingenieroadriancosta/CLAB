BOOL InWheel;
DWORD WINAPI ThreadWheel( LPVOID pv=NULL ){
PLOT_PROC();
//Pltrs[0].Inval();
//Pltrs[1].Inval();
InWheel = FALSE;
return 0;
}



//////////////////////////------------------->
DWORD WHEEL_PROC( int wParam ){

IF InWheel THEN
   return 0;
ENDIF;
InWheel = TRUE;
const int MaxTop = (int)(DTime*FsReal);
short rueda = HIWORD(wParam);
rueda /= WHEEL_DELTA;

int Diff1 = EndFrames - InitFrames;
int NDiv = 50;
IF ISDOWNKEY( VK_CONTROL ) THEN
   NDiv = 5;
ENDIF;

IF (Diff1/NDiv)<1 THEN
   NDiv = Diff1;
ENDIF;
//
IF rueda<0 THEN
   Diff1 = Diff1 - Diff1/NDiv;
ELSE
   Diff1 = Diff1 + Diff1/NDiv;
ENDIF;
//
IF Diff1<10 THEN
   Diff1 = 10;
ENDIF;
//
IF Diff1>MaxTop THEN
   Diff1 = MaxTop;
ENDIF;

IF Diff1==MaxTop && DiffIE==MaxTop THEN
   
   SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );
   
   InWheel = FALSE;
   return 0;
ENDIF;
DiffIE = Diff1;
SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCurHand );


DWORD IdThWhell = 0;
CreateThread( NULL, 0, ThreadWheel, NULL, 0, &IdThWhell );
//
//PLOT_PROC();
//
//InWheel = FALSE;
return 0;
}
