HWND HWFathPORT;
HWND HWTextFPORT;
BOOL InAVPorts;
int ValNPorts = 0;
DWORD IdThAvPort = 0;
char CAVEDITPort[10*1024];
//
BOOL CALLBACK DlgFindAVP( HWND, UINT, WPARAM, LPARAM );
BOOL AVPORTSNEW( void );
////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadDlgFindAVP( LPVOID pv=NULL ){

HWND HWFath = VENTANA_PADRE;
IF HWInVista THEN
   EnableWindow( VENTANA_PADRE, FALSE );
   HWFath = HWInVista;
ENDIF;
DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FIND_PORTS), HWFath, DlgFindAVP );
EnableWindow( VENTANA_PADRE, TRUE );
// msgbox();
return 0;
}
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////  AVP -- GENERAL -------------------------------->
BOOL AVPORTS( BOOL ShowMsg  ){

IF InAVPorts THEN
   return FALSE;
ENDIF;
InAVPorts = TRUE;

AVPORTSNEW();return FALSE;



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
IF ShowMsg THEN
   DWORD IdTh = 0;
   CreateThread( NULL, 0, ThreadDlgFindAVP, NULL, 0, &IdTh );
   Sleep( 500 );
ENDIF;

FOR int i=1; i<256; i++ LOOP
    sprintf( CTAVPort, "COM%i", i );
    //SetWindowText( HWFathPORT, CTAVPort );
    int ResAV = IsPortAvailable( CTAVPort, TRUE );
    IF ResAV==1 THEN
       sprintf( CTAVPort, MsgTADDisp, i, DevPass );
       strcat( CAVPort, CTAVPort );

       Text2Edit( CAVEDITPort, CAVPort );
       SetWindowText( HWTextFPORT, CAVEDITPort );
       int Ul = SendMessage( HWTextFPORT, EM_GETLINECOUNT, 0, 0 );
       SendMessage( HWTextFPORT, EM_LINESCROLL, 0, Ul );

       SendMessage( HWCOMPort, CB_SETCURSEL, i-1, 0 );

    ELSIF ResAV==255 THEN
       sprintf( CTAVPort, MsgNDisp, i );
       strcat( CAVPort, CTAVPort );

       Text2Edit( CAVEDITPort, CAVPort );
       SetWindowText( HWTextFPORT, CAVEDITPort );
       int Ul = SendMessage( HWTextFPORT, EM_GETLINECOUNT, 0, 0 );
       SendMessage( HWTextFPORT, EM_LINESCROLL, 0, Ul );

    ELSIF ResAV==2 THEN
       sprintf( CTAVPort, MsgDisp, i );
       strcat( CAVPort, CTAVPort );

       Text2Edit( CAVEDITPort, CAVPort );
       SetWindowText( HWTextFPORT, CAVEDITPort );

       int Ul = SendMessage( HWTextFPORT , EM_GETLINECOUNT, 0 , 0 );
       SendMessage( HWTextFPORT , EM_LINESCROLL, 0 , Ul );

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
}
////////////////////////////////////////////////////////////////////////////////
//
/*
DWORD WINAPI ThreadAVP( LPVOID pv=NULL ){
BOOL AvInp = (BOOL)pv;
AVPORTS( AvInp );
return 0;
}
//*/
//
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
BOOL CALLBACK DlgFindAVP( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam){
CASE( msg ) IS
     WHEN( WM_CLOSE )
          IF !InAVPorts THEN
             EndDialog(hDlg, FALSE);
             /*
          ELSE
             break;
             char TextDlg[256];
             LoadString( INSTANCIA_GLOBAL, ID_AVPORT_DIALOG_CLOSE_WIN, TextDlg, 255 );
             IF MessageBox( hDlg, TextDlg, " ", MB_ICONQUESTION | MB_YESNO )==IDYES THEN
                EndDialog(hDlg, FALSE);
                InAVPorts = FALSE;
                EnableWindow( VENTANA_PADRE, TRUE );
                ExitThread( IdThAvPort );
             ENDIF;
             //*/
          ENDIF;
     WHEN( WM_PAINT )
          // return FALSE;
          PAINTSTRUCT         ps;
          HDC HDc = BeginPaint( hDlg, &ps );
          /*
          HDC THDC = CreateCompatibleDC( HDc );
          SelectObject( THDC, HB_Fondo );
          SetStretchBltMode( HDc, COLORONCOLOR );
          RECT re;
          GetWindowRect( hDlg, &re );
          StretchBlt( HDc, 0, 0, re.right, re.bottom, THDC, 0, 0, B_Fondo.bmWidth, B_Fondo.bmHeight, SRCCOPY );
          DeleteDC( THDC );
          //*/
          //
          SetBkMode( HDc, TRANSPARENT );
          int IXPosWin = WinFuncs.GetWinXPos( HWCOMPort );
          int IYPosWin = WinFuncs.GetWinYPos( HWCOMPort );

          // int IWidWin = WinFuncs.GetWinWidth( HWCOMPort );
          // int IHeiWin = WinFuncs.GetWinHeight( HWCOMPort );
          SetTextAlign( HDc, TA_LEFT );
          TextOut( HDc, IXPosWin - 140, IYPosWin + 3, "Puerto seleccionado:", 20 );
          //
          EndPaint( hDlg, &ps);
     WHEN( WM_INITDIALOG )
          char MsgTitt[256];
          int WD = 360;
          int HD = 300 + 10*ValNPorts;

          CreateWindowEx( 0, "BUTTON", "Aceptar",
                          WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                          2, 2,
                          98, 26, hDlg, (HMENU)IDOK, INSTANCIA_GLOBAL, NULL );

          HWCOMPort = CreateWindowEx( 0, "COMBOBOX", NULL,
                                      WS_CHILD | WS_VISIBLE | WS_BORDER  | CBS_DROPDOWNLIST |
                                      WS_TABSTOP | WS_VSCROLL,
                                      WD-9 - 98, 1,
                                      98, 364, hDlg, NULL, INSTANCIA_GLOBAL, NULL );
          //SendMessage( HWCOMPort, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );
          FOR int i=1; i<256; i++ LOOP
              sprintf( MsgTitt, "COM%i", i );
              SendMessage( HWCOMPort, CB_ADDSTRING, 0, (LPARAM)MsgTitt );
          ENDLOOP;
          SendMessage( HWCOMPort, CB_SETCURSEL, ComPort-1, 0 );
          SetToolTipW( HWCOMPort, ID_TOOLTIP_CPORT );


          HWFathPORT = hDlg;
          HWTextFPORT = CreateWindowEx( 0, "EDIT", "", ES_LEFT | ES_MULTILINE | ES_WANTRETURN |
                                        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP |
                                        WS_HSCROLL | WS_VSCROLL | ES_READONLY | ES_NOHIDESEL,
                                        2, 30, WD-9, HD-32 - 27, hDlg, (HMENU)NULL, INSTANCIA_GLOBAL, NULL);
          int XPosD = 0;
          int YPosD = 0;
          XPosD = (WD+CXSCREEN)/2 - WD;
          YPosD = (HD+CYSCREEN)/2 - HD;



          MoveWindow( hDlg, XPosD, YPosD, WD, HD, TRUE );


          LoadString( INSTANCIA_GLOBAL, ID_SER_DISPOTITTLE, MsgTitt, 255 );
          SetWindowText( hDlg, MsgTitt );
          SetIcon( 10 ,hDlg );
          return TRUE;
     WHEN( WM_CTLCOLORSTATIC )
          static HBRUSH Dpincel;
          DeleteObject( Dpincel );
          Dpincel = CreateSolidBrush( RGB( 255, 255, 255 ) );

          SetTextColor( (HDC)wParam, RGB( 0, 0, 0) );
          SetBkColor( (HDC)wParam, RGB( 255, 255, 255) );
          return (LRESULT)Dpincel;
     WHEN( WM_COMMAND )
          IF LOWORD(wParam)==IDOK && InAVPorts  THEN
             MessageBox( hDlg, "Buscando...", " Info ", 0 );
          ELSIF LOWORD(wParam)==IDOK && !InAVPorts  THEN
             ComPort = (int)SendMessage( HWCOMPort, CB_GETCURSEL, 0, 0 ) + 1;
             EndDialog(hDlg, FALSE);
             return TRUE;
          ENDIF;
          return FALSE;
     DEFAULT
          return FALSE;
ENDCASE;
return FALSE;
}
