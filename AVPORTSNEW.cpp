BOOL AVPORTSNEW( void ){

int NPorts = Av_Ports();
ValNPorts = NPorts;

char CAVPort[10*1024];
CAVPort[0] = 0;
CAVEDITPort[0] = 0;

char CTAVPort[10*1024];


char MsgDisp[256];
char MsgNDisp[256];
char MsgTADDisp[256];
LoadString( INSTANCIA_GLOBAL, ID_SER_DISPONIB, MsgDisp, 255 );
LoadString( INSTANCIA_GLOBAL, ID_SER_NODISPONIB, MsgNDisp, 255 );
LoadString( INSTANCIA_GLOBAL, ID_SER_TADDISPONIB, MsgTADDisp, 255 );


/*
HKEY_LOCAL_MACHINE
DECLSPEC_NORETURN WINBASEAPI void WINAPI ExitProcess(UINT);
DECLSPEC_NORETURN WINBASEAPI void WINAPI ExitThread(DWORD);

//*/

DWORD IdTh = 0;
CreateThread( NULL, 0, ThreadDlgFindAVP, NULL, 0, &IdTh );
Sleep( 500 );


//
//SendMessage( HWCOMPort, CB_RESETCONTENT, 0, 0 );

BOOL Check = TRUE;
FOR int i=0; i<NPorts; i++ LOOP
    sprintf( CTAVPort, "COM%i", (int)PortAV[i] );
    //SetWindowText( HWFathPORT, CTAVPort );

    //sprintf( CTAVPort, NamePorts[i] );

    Check = ValidPort( ValuePorts[i] );

    int ResAV = IsPortAvailable( NamePorts[i], Check );
    IF ResAV==1 THEN
       sprintf( CTAVPort, MsgTADDisp, PortAV[i], DevPass );
       strcat( CAVPort, CTAVPort );

       Text2Edit( CAVEDITPort, CAVPort );
       SetWindowText( HWTextFPORT, CAVEDITPort );
       int Ul = SendMessage( HWTextFPORT, EM_GETLINECOUNT, 0, 0 );
       SendMessage( HWTextFPORT, EM_LINESCROLL, 0, Ul );



       //sprintf( TexT2, "COM%i", (int)PortAV[i] );
       //SendMessage( HWCOMPort, CB_ADDSTRING, 0, (LPARAM)TexT2 );
       //SendMessage( HWCOMPort, CB_SETCURSEL, Cur2set, 0 );
       //Cur2set++;

       SendMessage( HWCOMPort, CB_SETCURSEL, PortAV[i]-1, 0 );

    ELSIF ResAV==255 THEN
       sprintf( CTAVPort, MsgNDisp, PortAV[i] );
       strcat( CAVPort, CTAVPort );

       Text2Edit( CAVEDITPort, CAVPort );
       SetWindowText( HWTextFPORT, CAVEDITPort );
       int Ul = SendMessage( HWTextFPORT, EM_GETLINECOUNT, 0, 0 );
       SendMessage( HWTextFPORT, EM_LINESCROLL, 0, Ul );


       //sprintf( TexT2, "COM%i", (int)PortAV[i] );
       //SendMessage( HWCOMPort, CB_ADDSTRING, 0, (LPARAM)TexT2 );
       //Cur2set++;

    ELSIF ResAV==2 THEN
       sprintf( CTAVPort, MsgDisp, PortAV[i] );
       strcat( CAVPort, CTAVPort );

       Text2Edit( CAVEDITPort, CAVPort );
       SetWindowText( HWTextFPORT, CAVEDITPort );

       int Ul = SendMessage( HWTextFPORT , EM_GETLINECOUNT, 0 , 0 );
       SendMessage( HWTextFPORT , EM_LINESCROLL, 0 , Ul );


       //sprintf( TexT2, "COM%i", (int)PortAV[i] );
       //SendMessage( HWCOMPort, CB_ADDSTRING, 0, (LPARAM)TexT2 );
       //Cur2set++;
    ENDIF;


    //int PtrStop = 0;
    //PtrStop++;


ENDLOOP;

char EndConsult[256];
LoadString( INSTANCIA_GLOBAL, ID_AVPORT_END_CONSULTA, EndConsult, 255 );
sprintf( CTAVPort, EndConsult );
strcat( CAVPort, CTAVPort );



Text2Edit( CAVEDITPort, CAVPort );
SetWindowText( HWTextFPORT, CAVEDITPort );
int Ul = SendMessage( HWTextFPORT, EM_GETLINECOUNT, 0, 0 );
SendMessage( HWTextFPORT, EM_LINESCROLL, 0, Ul );
// msgbox( CAVPort, MsgTitt, MB_OK | MB_ICONASTERISK );


InAVPorts = FALSE;
return TRUE;














return TRUE;
}
