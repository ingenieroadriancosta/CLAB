BOOL WHL_CONNECT( void ){
system( "CLS" );
const double DMBs = (1024*1024);
const double DFs = (8*FsReal);

printf( "\nCursSQ0, %i\n", CursSQ0[2] );

WHILE( Connected==TRUE )
    BAvailable = HSerial.GetBytesAvailable();
    printf( "BAvailable, %g\t%i\t\tTime : %5.2f Seg\t\r", BAvailable/DMBs, (int)BAvailable, (BAvailable/DFs) );
    Sleep( 50 );
ENDWHILE;
IOnTry( FALSE, CursSQ0[2] );
// 1048576
return TRUE;
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
BOOL PRB_CONNECT( void ){


EnableMenuItem( MENUGLOBAL, ID_OPEN_F_REST, MF_DISABLED | MF_BYCOMMAND );

// const int MaxTopC = (int)(DTime*FsReal);


FOR int i=0; i<MBs; i++ LOOP
    BInData[i] = (BYTE)0;
ENDLOOP;

InConnect = TRUE;
Connected = TRUE;
EnableWindow( HWTs, FALSE );

SendMessage( HWTime, EM_SETREADONLY, 1, 0);


FOR int i=0; i<4; i++ LOOP
    ShowWindow( HWCursorInfo[i], 0 );
    ShowWindow( HWCursor[i], 0 );
ENDLOOP;



EnableWindow( HWCOMPort, FALSE );
IF OpenSerialProc()!=1 THEN
   ButtonNoConn();
   EnableMenuItem( MENUGLOBAL, ID_OPEN_F_REST, MF_ENABLED );
   EnableWindow( HWTs, TRUE );
   EnableWindow( HWCOMPort, TRUE );
   SendMessage( HWTime, EM_SETREADONLY, 0, 0);
   InConnect = FALSE;
   return 0;
ENDIF;

FOR int IC=0; IC<4; IC++ LOOP
    FOR int i=0; i<SizeBuff/2; i++ LOOP
        BuffData[IC].USData[i] = (BYTE)0;
    ENDLOOP;
ENDLOOP;



FOR int i=0; i<MBs; i = i + 16 LOOP
    BInData[i] = '{';
    BInData[i+1] = 129;
    BInData[i+15] = '}';
ENDLOOP;
//HSerial.SendBuffer( (BYTE*)&BInData[0], 1024 );
//
// BInData = (BYTE*)malloc( 10*MBs );

//


// BOOL GetCommProperties(HANDLE hFile, LPCOMMPROP lpCommProp);
COMMPROP lpCommProp;
memset( &lpCommProp, 0, sizeof(lpCommProp) );
GetCommProperties( HSerial.GetHandleS(), &lpCommProp );
printf( "dwMaxBaud, %f\n", lpCommProp.dwMaxBaud/((double)(1024*1024))  );
//system( "PAUSE" );


BYTE BData = 0;
BData++;
BData = HSerial.GetByte();
system( "PAUSE" );


// StartAdq();
IOnTry( TRUE, CursSQ0[2] );







TimeStatus.setVisible( TRUE );
Input1Status.setVisible( TRUE );
Input2Status.setVisible( TRUE );

InitFrames = 0;
DiffIE = 0;







//SetPriorityClass( HSerial.GetHandleS(), REALTIME_PRIORITY_CLASS );

// FsReal

NFramesReaded = 0;
//NFramesReaded = (int)(59*FsReal);
Sleep( 10 );
MBAvailable = 0;


WHL_CONNECT();


SetPlot = TRUE;
StopAdq();
HSerial.Close();
Sleep( 50 );


ButtonNoConn();
InitFrames = 0;
DiffIE = (int)(DTime*FsReal);
EndFrames = DiffIE;
PosBuff[0] = 0;
PosBuff[1] = DiffIE/4;
PosBuff[2] = (2*DiffIE)/4;
PosBuff[3] = (3*DiffIE);

PLOT_PROC();

EnableMenuItem( MENUGLOBAL, ID_OPEN_F_REST, MF_ENABLED );



EnableWindow( HWCOMPort, TRUE );


EnableWindow( HWTs, TRUE );
EnableWindow( HWCOMPort, TRUE );
SendMessage( HWTime, EM_SETREADONLY, 0, 0);




TimeStatus.setVisible( FALSE );
Input1Status.setVisible( FALSE );
Input2Status.setVisible( FALSE );

InConnect = FALSE;








return TRUE;
}
