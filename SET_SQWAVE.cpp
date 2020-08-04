BOOL SetFsSin( HWND, BYTE*, int );
BOOL SET_SQWAVE( int Opt ){
BConnect.setEnabled( FALSE );
char Texto1[64];
IF Opt==0 THEN
   EnableWindow( HWCB_SQ_Wave0, FALSE );
   EnableWindow( HWCB_SQ_Wave1, FALSE );
   
   EnableWindow( HWFs_Out0, FALSE );
   EnableWindow( HWFs_Out1, FALSE );
   
   int SetSQWave0T = 0;
   RepSelW0:
   SetSQWave0T = (int)SendMessage( HWCB_SQ_Wave0, CB_GETCURSEL, 0, 0 );
   SetSQWave0 = SetSQWave0T;
   /*
   IF Connected THEN
      SetSqWave();
   ELSIF OpenSerialProc()==1 THEN
      SetSqWave();
      HSerial.Close();
   ENDIF;
   //*/
   Sleep( 100 );
   SetSQWave0T = (int)SendMessage( HWCB_SQ_Wave0, CB_GETCURSEL, 0, 0 );
   IF SetSQWave0T!=SetSQWave0 THEN
      goto RepSelW0;
   ENDIF;
   
   
   IF SetSQWave0<1 THEN
      SendMessage( HWFs_Out0, CB_RESETCONTENT, 0, 0 );
      //SendMessage( HWFs_Out0, CB_ADDSTRING, 0, (LPARAM)"--------" );
      SendMessage( HWFs_Out0, CB_SETCURSEL, 0, 0 );
   ELSIF SetSQWave0<2 THEN
      SendMessage( HWFs_Out0, CB_RESETCONTENT, 0, 0 );
      FOR int i = 0; i<MaxCurs; i++ LOOP
          sprintf( Texto1, "%g Hz", MaxFsReal/(10.0*(FsOuts[i])) );
          SendMessage( HWFs_Out0, CB_ADDSTRING, 0, (LPARAM)Texto1 );
      ENDLOOP;
      SendMessage( HWFs_Out0, CB_SETCURSEL, CursSQ0[1], CursSQ0[1] );
   ELSIF SetSQWave0<4 THEN
      SetFsSin( HWFs_Out0, (BYTE*)&CursSQ0[0], SetSQWave0 );
      /*
      SendMessage( HWFs_Out0, CB_RESETCONTENT, 0, 0 );
      
      FOR int i = 0; i<17; i++ LOOP
          sprintf( Texto1, "%i", i );
          SendMessage( HWFs_Out0, CB_ADDSTRING, 0, (LPARAM)Texto1 );
      ENDLOOP;
      
      SendMessage( HWFs_Out0, CB_SETCURSEL, CursSQ0[2], CursSQ0[2] );
      //*/
   ENDIF;
   
   EnableWindow( HWCB_SQ_Wave0, TRUE );
   EnableWindow( HWCB_SQ_Wave1, TRUE );
   
   
   
   EnableWindow( HWFs_Out0, SetSQWave0>0 );
   EnableWindow( HWFs_Out1, SetSQWave1>0 );
   
   
   
   
   
   //EnableWindow( HWFs_Out0, TRUE );
   //EnableWindow( HWFs_Out1, TRUE );
   
   
   
ELSIF Opt==1 THEN
   
   EnableWindow( HWCB_SQ_Wave0, FALSE );
   EnableWindow( HWCB_SQ_Wave1, FALSE );
   
   EnableWindow( HWFs_Out0, FALSE );
   EnableWindow( HWFs_Out1, FALSE );
   
   int SetSQWave1T = 0;
   RepSelW1:
   SetSQWave1T = (int)SendMessage( HWCB_SQ_Wave1, CB_GETCURSEL, 0, 0 );
   SetSQWave1 = SetSQWave1T;
   /*
   IF Connected THEN
      SetSqWave();
   ELSIF OpenSerialProc()==1 THEN
      SetSqWave();
      HSerial.Close();
   ENDIF;
   //*/
   Sleep( 100 );
   SetSQWave1T = (int)SendMessage( HWCB_SQ_Wave1, CB_GETCURSEL, 0, 0 );
   IF SetSQWave1T!=SetSQWave1 THEN
      goto RepSelW1;
   ENDIF;
   
   
   IF SetSQWave1<1 THEN
      SendMessage( HWFs_Out1, CB_RESETCONTENT, 0, 0 );
      //SendMessage( HWFs_Out1, CB_ADDSTRING, 0, (LPARAM)"--------" );
      SendMessage( HWFs_Out1, CB_SETCURSEL, 0, 0 );
   ELSIF SetSQWave1<2 THEN
      SendMessage( HWFs_Out1, CB_RESETCONTENT, 0, 0 );
      FOR int i = 0; i<MaxCurs; i++ LOOP
          sprintf( Texto1, "%g Hz", MaxFsReal/(10.0*(FsOuts[i])) );
          SendMessage( HWFs_Out1, CB_ADDSTRING, 0, (LPARAM)Texto1 );
      ENDLOOP;
      SendMessage( HWFs_Out1, CB_SETCURSEL, CursSQ1[1], CursSQ1[1] );
   ELSIF SetSQWave1<4 THEN
      SetFsSin( HWFs_Out1, (BYTE*)&CursSQ1[0], SetSQWave1 );
      
      
   ENDIF;
   
   EnableWindow( HWCB_SQ_Wave0, TRUE );
   EnableWindow( HWCB_SQ_Wave1, TRUE );
   
   EnableWindow( HWFs_Out0, SetSQWave0>0 );
   EnableWindow( HWFs_Out1, SetSQWave1>0 );
   
   
ELSIF Opt==2 THEN
   
   IF SetSQWave0<1 THEN
      BConnect.setEnabled( TRUE );
      return FALSE;
   ENDIF;
   
   EnableWindow( HWFs_Out0, FALSE );
   EnableWindow( HWFs_Out1, FALSE );
   
   BYTE CurVSQ0;
   ReCurVSQ0:
   CurVSQ0 = (int)SendMessage( HWFs_Out0, CB_GETCURSEL, 0, 0 );
   VSQ_Wave0 = (BYTE)CurVSQ0;
   
   CursSQ0[SetSQWave0] = VSQ_Wave0;
   
   /*
   IF Connected THEN
      SetSqWave();
   ELSIF OpenSerialProc()==1 THEN
      SetSqWave();
      HSerial.Close();
   ENDIF;
   //*/
   CurVSQ0 = (int)SendMessage( HWFs_Out0, CB_GETCURSEL, 0, 0 );
   IF CurVSQ0!=VSQ_Wave0 THEN
      goto ReCurVSQ0;
   ENDIF;
   
   
   
   EnableWindow( HWFs_Out0, SetSQWave0>0 );
   EnableWindow( HWFs_Out1, SetSQWave1>0 );
   
ELSIF Opt==3 THEN
   
   IF SetSQWave1<1 THEN
      BConnect.setEnabled( TRUE );
      return FALSE;
   ENDIF;
   
   EnableWindow( HWFs_Out0, FALSE );
   EnableWindow( HWFs_Out1, FALSE );
   
   BYTE CurVSQ1;
   ReCurVSQ1:
   CurVSQ1 = (int)SendMessage( HWFs_Out1, CB_GETCURSEL, 0, 0 );
   VSQ_Wave1 = (BYTE)CurVSQ1;
   
   CursSQ1[SetSQWave1] = VSQ_Wave1;
   
   
   /*
   IF Connected THEN
      SetSqWave();
   ELSIF OpenSerialProc()==1 THEN
      SetSqWave();
      HSerial.Close();
   ENDIF;
   //*/
   
   CurVSQ1 = (int)SendMessage( HWFs_Out1, CB_GETCURSEL, 0, 0 );
   IF CurVSQ1!=VSQ_Wave1 THEN
      goto ReCurVSQ1;
   ENDIF;
   
   
   
   EnableWindow( HWFs_Out0, TRUE );
   EnableWindow( HWFs_Out1, TRUE );
ENDIF;
//*/




EnableWindow( HWB_Val_Min, SetSQWave0!=0 );
EnableWindow( HWD_Val_Min, SetSQWave1!=0 );

BConnect.setEnabled( TRUE );
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
BOOL SetFsSin( HWND HWndS, BYTE* Curs01, int Indi ){
char Texto1[256];
SendMessage( HWndS, CB_RESETCONTENT, 0, 0 );



const float		ValPlus[16] = { 25.600,// 200   Hz
							    16.000,// 125   Hz
							    12.800,// 100   Hz
							    7.6800,//  60   Hz
							     6.400,//  50   Hz
							     2.560,//  20   Hz
							     1.280,//  10   Hz
							     0.640,//   5   Hz
							     0.256,//   2   Hz
							     0.128,//   1   Hz
							     0.064,//   0.5 Hz
							     0.0256,//  0.2 Hz
							     0.0128,//  0.1 Hz
							};



FOR int i=0; i<13; i++ LOOP
    double Val2 = ValPlus[i];
    Val2 = 256/Val2;
    Val2 = Val2/2000;
    Val2 = 1/Val2;
    
    sprintf( Texto1, "%g Hz", Val2 );
    SendMessage( HWndS, CB_ADDSTRING, 0, (LPARAM)Texto1 );
ENDLOOP;

/*
// MaxFsReal
sprintf( Texto1, "%g Hz", 0.5/0.004 );
SendMessage( HWndS, CB_ADDSTRING, 0, (LPARAM)Texto1 );

sprintf( Texto1, "%g Hz", 0.5/0.008 );
SendMessage( HWndS, CB_ADDSTRING, 0, (LPARAM)Texto1 );

sprintf( Texto1, "%g Hz", 0.5/0.016 );
SendMessage( HWndS, CB_ADDSTRING, 0, (LPARAM)Texto1 );


sprintf( Texto1, "%g Hz", 0.5/0.032 );
SendMessage( HWndS, CB_ADDSTRING, 0, (LPARAM)Texto1 );


sprintf( Texto1, "%g Hz", 0.5/0.064 );
SendMessage( HWndS, CB_ADDSTRING, 0, (LPARAM)Texto1 );
//*/




/*
SendMessage( HWndS, CB_RESETCONTENT, 0, 0 );
FOR int i = 0; i<17; i++ LOOP
    sprintf( Texto1, "%i", i );
    SendMessage( HWndS, CB_ADDSTRING, 0, (LPARAM)Texto1 );
ENDLOOP;
//*/
SendMessage( HWndS, CB_SETCURSEL, Curs01[Indi], Curs01[Indi] );
return TRUE;
}
