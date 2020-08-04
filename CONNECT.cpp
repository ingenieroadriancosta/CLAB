DWORD WINAPI CONNECT( LPVOID pv=NULL ){
IF InConnect THEN
   return 0;
ENDIF;
InConnect = TRUE;

// PRB_CONNECT();return 0;

EnableMenuItem( MENUGLOBAL, ID_OPEN_F_REST, MF_DISABLED | MF_BYCOMMAND );
// BOpen.setEnabled( FALSE );
const int MaxTopC = (int)(DTime*FsReal);


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
SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );

TimeStatus.setVisible( TRUE );
Input1Status.setVisible( TRUE );
Input2Status.setVisible( TRUE );


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
Divisor = DevDivisor;
CreateThread( NULL, 0, SEG_CONNECT, NULL, 0, &IdThPlt );

H_Plt_Cnn = CreateThread( NULL, 0, PLOT_CONNECT, NULL, 0, &IdThPlt );




Pltrs[0].Text2ShowF( "" );
Pltrs[1].Text2ShowF( "" );


char TextError[256];

DWORD PEndPoint = MEndPoint;
PEndPoint = MEndPoint;

NFramesReaded = 0;
DWORD DWBytesRead = 0;
InitFrames = 0;
DiffIE = 0;
MBAvailable = 0;


SetPwm( FALSE );
Sleep( 50 );
StartAdq();
// BOOL SetPwm( BOOL );

// Sleep( 10 );
WHILE( Connected==TRUE )
    IWhile:
    BAvailable = HSerial.GetBytesAvailable();
    IF ShHiCon THEN
       printf( "BAvailable, %i\t%i\t\t\r", (int)BAvailable, (int)MBAvailable );
    ENDIF;
    //BAvailable = 64*PEndPoint;
    WHILE( Connected && BAvailable<PEndPoint  )
         BAvailable = HSerial.GetBytesAvailable();
    ENDWHILE;
    IF !Connected THEN
       break;
    ENDIF;

    IF MBAvailable<BAvailable THEN
       MBAvailable = BAvailable;
    ENDIF;


    //BAvailable = BAvailable/2;
    //BAvailable = HSerial.GetBytesAvailable();
    WHILE( (BAvailable%PEndPoint)!=0 && BAvailable>0 )
         BAvailable--;
    ENDLOOP;


    //FOR int i=0; i<2*BAvailable; i++ LOOP
        //BInData[i] = (BYTE)i;
    //ENDLOOP;

    DWBytesRead = HSerial.Read2Buffer( (BYTE*)&BInData[0], (DWORD)BAvailable );
    // ReadFile( HSerial.GetHandleS(), &BInData[0], BAvailable, &DWBytesRead, NULL );
    IF (char)BInData[0]!='{' || (char)BInData[EndBuf]!='}' || BAvailable<0 || BAvailable!=DWBytesRead  THEN
       int Err = GetError();

       char* ErrT = HSerial.GetErrorText();
       HSerial.ClearError();
       sprintf( TextError,
                "Descripción del error:\n"
                "%s\n\n"
                "Otros Datos:\n\n"
                "LastE, %i\n"
                "Err, %i\n\n"

                "BAv, %i\n"
                "DWBRe, %i\n\n"
                "MBAv, %i\n\n"

                "I, %i\n"
                "E, %i\n\n"
                "Seg, %g\n\n"
                "Continuar?",
                ErrT,
                (int)ERROR_NOT_SUPPORTED, (int)Err,
                (int)BAvailable, (int)DWBytesRead,
                (int)MBAvailable,

                (int)BInData[0], (int)BInData[7],
                (DiffIE/FsReal) );
       //msgbox( TextError, "Error", 16 );


       IF !(msgbox( TextError, "Error", 16 | MB_ICONQUESTION | MB_YESNO )==IDYES) THEN
          break;
       ENDIF;
       NFramesReaded = 0;
       StartAdq();
       goto IWhile;
    ENDIF;
    //
    FOR int i=0; i<(int)BAvailable; i = i + EndPoint LOOP
        int ActIndex = NFramesReaded + i/EndPoint;
        BuffData[0].USData[ActIndex] = (unsigned short)(MAKEWORD( BInData[i+1], BInData[i+2] ));
        BuffData[1].USData[ActIndex] = BInData[i+3];
        // (unsigned short)BInData[i+3];
        BuffData[2].USData[ActIndex] = (unsigned short)(MAKEWORD( BInData[i+4], BInData[i+5] ));
        BuffData[3].USData[ActIndex] = BInData[i+6];
        //(unsigned short)BInData[i+6];
    ENDLOOP;
    NFramesReaded = NFramesReaded + BAvailable/EndPoint;
    DiffIE = NFramesReaded - 1;


    A0_Val = (double)BuffData[0].USData[DiffIE];
    A0_Val = (Volt_In_Out[0]*A0_Val)/1023;
    A1_Val = (double)BuffData[2].USData[DiffIE];
    A1_Val = (Volt_In_Out[2]*A1_Val)/1023;


    B0_Val = (double)BuffData[1].USData[DiffIE];
    B0_Val = (Volt_In_Out[1]*B0_Val)/255;
    D1_Val = (double)BuffData[3].USData[DiffIE];
    D1_Val = (Volt_In_Out[3]*D1_Val)/255;


    IF DiffIE>=MaxTopC THEN
       break;
    ENDIF;
    SetPlot = TRUE;
    Sleep( 1 );
ENDWHILE;
BConnect.setEnabled( FALSE );


IF Permission THEN
   //SetVolt( 0, 0, TRUE );
   //SetVolt( 0, 0, FALSE );
   PwmOff();
   SendAny( 1 );
   SendAny( 2 );
   Sleep( 100 );
ENDIF;
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
/*
TimeStatus.setVisible( FALSE );
Input1Status.setVisible( FALSE );
Input2Status.setVisible( FALSE );
//*/
BConnect.setEnabled( TRUE );

InConnect = FALSE;

// free( BInData );
// msgbox();
return 0;
}
