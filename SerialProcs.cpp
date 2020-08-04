BOOL SetVolt( double, double, BOOL );
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
BOOL InOpenS = FALSE;
BYTE OpenSerialProc( HWND HWndAct=NULL ){
     IF InOpenS THEN
        return 10;
     ENDIF;
     InOpenS = TRUE;
     sprintf( CPortName, "COM%i", ComPort );
     BYTE ResultS = IsPortAvailable( CPortName, TRUE );

     IF ResultS==0 THEN
        char* TextResult = (char*)malloc(256);
        char* LoadText1 = (char*)malloc(256);
        LoadString( INSTANCIA_GLOBAL, ID_SER_NOPORT, TextResult, 255 );
        LoadString( INSTANCIA_GLOBAL, ID_TMSG_ERROR, LoadText1, 255 );

        sprintf( CPortName, TextResult, ComPort );
        IF HWndAct==NULL THEN
           EnableWindow( HWInVista, FALSE );
           msgbox( CPortName, LoadText1, 16 );
           EnableWindow( HWInVista, TRUE );
        ELSE
           EnableWindow( VENTANA_PADRE, FALSE );
           EnableWindow( HWInVista, FALSE );
           MessageBox( HWndAct, CPortName, LoadText1, 16 );
           EnableWindow( VENTANA_PADRE, TRUE );
           EnableWindow( HWInVista, TRUE );
        ENDIF;
        free( TextResult );
        free( LoadText1 );
        InOpenS = FALSE;
        return 0;
     ELSIF ResultS==255 THEN
        char TextResult[256];
        char LoadText1[256];
        LoadString( INSTANCIA_GLOBAL, ID_SER_BUSYPORT, TextResult, 255 );
        LoadString( INSTANCIA_GLOBAL, ID_TMSG_ERROR, LoadText1, 255 );

        sprintf( CPortName, TextResult, ComPort );
        IF HWndAct==NULL THEN
           EnableWindow( HWInVista, FALSE );
           msgbox( CPortName, LoadText1, 16 );
           EnableWindow( HWInVista, TRUE );
        ELSE
           EnableWindow( VENTANA_PADRE, FALSE );
           EnableWindow( HWInVista, FALSE );
           MessageBox( HWndAct, CPortName, LoadText1, 16 );
           EnableWindow( VENTANA_PADRE, TRUE );
           EnableWindow( HWInVista, TRUE );
        ENDIF;
        InOpenS = FALSE;
        return 0;
     ELSIF ResultS==2 THEN
        char TextResult[2*1024];
        char LoadText1[1024];
        LoadString( INSTANCIA_GLOBAL, ID_STRING_IS_NOT_TAD, LoadText1, 1023 );
        sprintf( TextResult, LoadText1, ComPort );
        IF HWndAct==NULL THEN
           EnableWindow( HWInVista, FALSE );
           IF msgbox( TextResult, " Advertencia ", MB_OKCANCEL | MB_ICONWARNING )==IDOK THEN
              sprintf( CPortName, "COM%i", ComPort );
              HSerial.OpenSerial( CPortName );
              EnableWindow( HWInVista, TRUE );
              InOpenS = FALSE;
              return 1;
              LoadString( INSTANCIA_GLOBAL, ID_STRING_CONN_IS_NOT_TAD, TextResult, 1023 );
              IF msgbox( TextResult, " ¿ ? ", MB_ICONQUESTION | MB_YESNO )==IDYES THEN
                 HSerial.OpenSerial( CPortName );
                 InOpenS = FALSE;
                 return 1;
              ENDIF;
              InOpenS = FALSE;
              return 2;
           ELSE
              EnableWindow( HWInVista, TRUE );
              InOpenS = FALSE;
              return 2;
           ENDIF;
        ELSE

           EnableWindow( VENTANA_PADRE, FALSE );
           EnableWindow( HWInVista, FALSE );
           IF MessageBox( HWndAct, TextResult, " Advertencia ", MB_OKCANCEL | MB_ICONWARNING )==IDOK THEN
              sprintf( CPortName, "COM%i", ComPort );
              HSerial.OpenSerial( CPortName );
              EnableWindow( VENTANA_PADRE, TRUE );
              EnableWindow( HWInVista, TRUE );
              InOpenS = FALSE;
              return 1;
              LoadString( INSTANCIA_GLOBAL, ID_STRING_CONN_IS_NOT_TAD, TextResult, 1023 );
              IF MessageBox( HWndAct, TextResult, " ¿ ? ", MB_ICONQUESTION | MB_YESNO )==IDYES THEN
                 HSerial.OpenSerial( CPortName );
                 EnableWindow( VENTANA_PADRE, TRUE );
                 EnableWindow( HWInVista, TRUE );
                 InOpenS = FALSE;
                 return 1;
              ENDIF;
              EnableWindow( VENTANA_PADRE, TRUE );
              EnableWindow( HWInVista, TRUE );
              InOpenS = FALSE;
              return 2;
           ELSE
              EnableWindow( VENTANA_PADRE, TRUE );
              EnableWindow( HWInVista, TRUE );
              InOpenS = FALSE;
              return 2;
           ENDIF;
        ENDIF;
        // msgbox( CPortName, " ?", 16 );


     ELSE
        sprintf( CPortName, "COM%i", ComPort );
        HSerial.OpenSerial( CPortName );

        EnableWindow( HWPwm2, strcmp( &DevTad[1][0], DevPass )!=0 );
        InOpenS = FALSE;
        return 1;
     ENDIF;

     sprintf( CPortName, "COM%i", ComPort );
     HSerial.OpenSerial( CPortName );

     InOpenS = FALSE;
return 1;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL ButtonNoConn( void ){
     BConnect.setJPGResource( ID_BUTT_ON );
     BConnect.setText( ID_CNNBUTTONI );
     BConnect.setSelected( FALSE );
     BOpen.setEnabled( TRUE );
     Connected = FALSE;
     FOR int i=0; i<4; i++ LOOP
         ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
         ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
     ENDLOOP;
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
BOOL SetVolt( double BDVolt, double BDVoltMin, BOOL BD_Chann=TRUE ){

SendVoltA = FALSE;
double VIns = 0;
int INChann = 1;

int IVChann = 1;
IF !BD_Chann THEN
   IVChann = 2;
   INChann = 3;
   SendVoltB = FALSE;
ENDIF;
BYTE  Msg2TAD[MaxNBTx+1];
Msg2TAD[0] = '{';
Msg2TAD[1] = IVChann;


BYTE BVolt = 0;






BDVolt = (Divisor*BDVolt)/Volt_In_Out[ INChann ];
BDVolt = round(BDVolt);
IF BDVolt>Divisor THEN
   BDVolt = Divisor;
ELSIF BDVolt<0 THEN
   BDVolt = 0;
ENDIF;
BVolt = (BYTE)BDVolt;
Msg2TAD[2] = BVolt;


BDVoltMin = (Divisor*BDVoltMin)/Volt_In_Out[ INChann ];
BDVoltMin = round(BDVoltMin);
IF BDVoltMin>Divisor THEN
   BDVoltMin = Divisor;
ELSIF BDVoltMin<0 THEN
   BDVoltMin = 0;
ENDIF;
BVolt = (BYTE)BDVoltMin;
Msg2TAD[3] = BVolt;



Msg2TAD[4] = (BYTE)SetSQWave0;
Msg2TAD[5] = (BYTE)SetSQWave1;



IF IVChann==1 THEN
   IF SetSQWave0==1 THEN
      Msg2TAD[6] = (BYTE)LOBYTE(FsOuts[VSQ_Wave0]);
      Msg2TAD[7] = (BYTE)HIBYTE(FsOuts[VSQ_Wave0]);
   ELSIF SetSQWave0>1 THEN
      Msg2TAD[6] = CursSQ0[SetSQWave0];



      VIns = abs( B_Val - B_Val_Min );
      VIns = round( Divisor*(VIns/Volt_In_Out[1]) );
      Msg2TAD[7] = (BYTE)VIns;



   ENDIF;
ELSE
   IF SetSQWave1==1 THEN
      Msg2TAD[6] = (BYTE)LOBYTE(FsOuts[VSQ_Wave1]);
      Msg2TAD[7] = (BYTE)HIBYTE(FsOuts[VSQ_Wave1]);
   ELSIF SetSQWave1>1 THEN
      Msg2TAD[6] = CursSQ1[SetSQWave1];


      VIns = abs( D_Val - D_Val_Min );
      VIns = round( Divisor*(VIns/Volt_In_Out[3]) );
      Msg2TAD[7] = (BYTE)VIns;



   ENDIF;
ENDIF;









Msg2TAD[MaxNBTx-1] = '}';

FOR int i=0; i<MaxNBTx; i++ LOOP
    HSerial.SendByte( Msg2TAD[i] );
    Sleep( 1 );
ENDLOOP;
return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
BOOL SetVolts( void ){

BYTE  Msg2TAD[MaxNBTx+1];
Msg2TAD[0] = '{';
Msg2TAD[1] = 3;

BYTE B_BVolt = 0;
IF B_Val>5 THEN
   B_BVolt = Divisor;
ELSIF B_Val<0 THEN
   B_BVolt = 0;
ELSE
   B_BVolt = (BYTE)( (floor(Divisor*B_Val))/Volt_In_Out[1] );
ENDIF;

BYTE D_BVolt = 0;
IF D_Val>5 THEN
   D_BVolt = Divisor;
ELSIF D_Val<0 THEN
   D_BVolt = 0;
ELSE
   D_BVolt = (BYTE)( (floor(Divisor*D_Val))/Volt_In_Out[3] );
ENDIF;

Msg2TAD[2] = B_BVolt;
Msg2TAD[3] = D_BVolt;


Msg2TAD[4] = (BYTE)SetSQWave0;
Msg2TAD[5] = (BYTE)SetSQWave1;



Msg2TAD[MaxNBTx-1] = '}';

FOR int i=0; i<MaxNBTx; i++ LOOP
    HSerial.SendByte( Msg2TAD[i] );
    Sleep( 1 );
ENDLOOP;
return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL StartAdq( void ){



double VIns = 0;
BYTE  Msg2TAD[MaxNBTx+1];
Msg2TAD[0] = '{';
Msg2TAD[1] = 0;
Msg2TAD[2] = 1;

Msg2TAD[3] = LOBYTE( Fs );
Msg2TAD[4] = HIBYTE( Fs );



// Max
VIns = (Divisor*B_Val)/Volt_In_Out[1];
VIns = floor( VIns );
Msg2TAD[5] = Divisor&((BYTE)VIns);

VIns = (Divisor*D_Val)/Volt_In_Out[3];
VIns = floor( VIns );
Msg2TAD[6] = Divisor&((BYTE)VIns);

// Min
VIns = (Divisor*B_Val_Min)/Volt_In_Out[1];
VIns = floor( VIns );
Msg2TAD[7] = Divisor&((BYTE)VIns);


VIns = (Divisor*D_Val_Min)/Volt_In_Out[3];
VIns = floor( VIns );
Msg2TAD[8] = Divisor&((BYTE)VIns);









Msg2TAD[9] = (BYTE)SetSQWave0;
Msg2TAD[10] = (BYTE)SetSQWave1;

IF SetSQWave0==1 THEN
   Msg2TAD[11] = (BYTE)LOBYTE(FsOuts[VSQ_Wave0]);
   Msg2TAD[12] = (BYTE)HIBYTE(FsOuts[VSQ_Wave0]);
ELSIF SetSQWave0>1 THEN
   Msg2TAD[11] = CursSQ0[SetSQWave0];



   VIns = abs( B_Val - B_Val_Min );
   VIns = round( Divisor*(VIns/Volt_In_Out[1]) );
   Msg2TAD[12] = (BYTE)VIns;




ENDIF;


IF SetSQWave1==1 THEN
   Msg2TAD[13] = (BYTE)LOBYTE(FsOuts[VSQ_Wave1]);
   Msg2TAD[14] = (BYTE)HIBYTE(FsOuts[VSQ_Wave1]);
ELSIF SetSQWave1>1 THEN
   Msg2TAD[13] = CursSQ1[SetSQWave1];


   VIns = abs( D_Val - D_Val_Min );
   VIns = round( Divisor*(VIns/Volt_In_Out[3]) );
   Msg2TAD[14] = (BYTE)VIns;

ENDIF;





Msg2TAD[MaxNBTx-1] = '}';

FOR int i=0; i<MaxNBTx; i++ LOOP
    HSerial.SendByte( Msg2TAD[i] );
    Sleep( 1 );
ENDLOOP;



return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL StopAdq( void ){

BYTE  Msg2TAD[MaxNBTx+1];
Msg2TAD[0] = '{';
Msg2TAD[1] = 0;
Msg2TAD[2] = 0;
Msg2TAD[MaxNBTx-1] = '}';

FOR int i=0; i<MaxNBTx; i++ LOOP
    HSerial.SendByte( Msg2TAD[i] );
    Sleep( 1 );
ENDLOOP;
return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void GetParam( void ){
BYTE  Msg2TAD[MaxNBTx+1];
Msg2TAD[0] = '{';
Msg2TAD[1] = 125;
Msg2TAD[MaxNBTx-1] = '}';

FOR int i=0; i<MaxNBTx; i++ LOOP
    HSerial.SendByte( Msg2TAD[i] );
    Sleep( 1 );
ENDLOOP;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int GetError( void ){
int ErrRet = 0;
StopAdq();
Sleep( 1 );
StopAdq();
Sleep( 1 );
DWORD BAva = HSerial.GetBytesAvailable();
BYTE*  Msg2TAD = (BYTE*)malloc( BAva + 4 );
HSerial.Read2Buffer( (BYTE*)&Msg2TAD[0], BAva );
Sleep( 1 );

free( Msg2TAD );
Msg2TAD = (BYTE*)malloc( MaxNBTx+1 );
Msg2TAD[0] = '{';
Msg2TAD[1] = 127;
Msg2TAD[2] = 0;
Msg2TAD[MaxNBTx-1] = '}';

FOR int i=0; i<MaxNBTx; i++ LOOP
    HSerial.SendByte( Msg2TAD[i] );
    Sleep( 1 );
ENDLOOP;
ErrRet = 0;
WHILE( ErrRet<128 )
    ErrRet++;
    Sleep( 1 );
ENDLOOP;

ErrRet = -3;
BAva = HSerial.GetBytesAvailable();
IF BAva>14 && BAva<20 THEN

   HSerial.Read2Buffer( (BYTE*)&Msg2TAD[0], BAva );
   IF Msg2TAD[0]=='{' && Msg2TAD[MaxNBTx-1]=='}' THEN
      ErrRet = (int)(255&Msg2TAD[1]);
   ELSE
      ErrRet = 1;
   ENDIF;
ELSIF BAva<14 THEN
   ErrRet = -1;
ELSIF BAva>20 THEN
   ErrRet = -2;
ENDIF;


return ErrRet;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void IOnTry( BOOL BActive, BYTE Val2Try=4 ){
BYTE  Msg2TAD[32];
Msg2TAD[0] = '{';
Msg2TAD[1] = 126;
Msg2TAD[2] = (BYTE)BActive;
Msg2TAD[3] = Val2Try;
Msg2TAD[MaxNBTx-1] = '}';

FOR int i=0; i<MaxNBTx; i++ LOOP
    HSerial.SendByte( Msg2TAD[i] );
    Sleep( 1 );
ENDLOOP;
}
