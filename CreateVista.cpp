int XVist = 0;
int YVist = 0;
int WVist = 0;
int HVist = 0;
HICON HIconVista;
//
int CreateVista( HWND HWnd ){
HWInVista = HWnd;
HIconVista = LoadIcon( INSTANCIA_GLOBAL, MAKEINTRESOURCE(10) );

SendMessage( HWnd, WM_SETICON, ICON_SMALL, (LPARAM)HIconVista );
SendMessage( HWnd, WM_SETICON, ICON_BIG, (LPARAM)HIconVista );




SendMessage( GetDlgItem( HWInVista, ID_GRID_ON ), BM_SETCHECK, (WPARAM)(ActGStyle), 0 );
SendMessage( GetDlgItem( HWInVista, ID_DIV_GRAPH ), BM_SETCHECK, (WPARAM)(DivGraph), 0 );
SendMessage( GetDlgItem( HWInVista, ID_INVERTIDO ), BM_SETCHECK, (WPARAM)(InvGrid), 0 );

FOR int i=0; i<4; i++ LOOP
    SendMessage( GetDlgItem( HWInVista, ID_DATA_CURSOR0 + i ), BM_SETCHECK, (WPARAM)(EnDataCursor[i]), 0 );
ENDLOOP;




CheckRadioButton( HWInVista, ID_GRID_STYLE0, ID_GRID_STYLE3, GStyle + ID_GRID_STYLE0 );
CheckRadioButton( HWInVista, ID_LINE_WIDTH1, ID_LINE_WIDTH4, LineWidth + ID_LINE_WIDTH1 - 1 );
    


/*
HWGrillaOn = CreateWindowEx( 0, "EDIT", " ", WS_CHILD | WS_VISIBLE | WS_BORDER,
                             2, 2,
                             48, 27, HWnd, (HMENU)ID_SET_TIME, INSTANCIA_GLOBAL, NULL );
//*/



//SetWindowText( hDlg, WTitleSV );
/*
HFONT SAHFont = CreateFont( 38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                            DEFAULT_PITCH | FF_ROMAN, "Times New Roman" );
//*/
//HWND HWndEdit_ = GetDlgItem( HWnd, 256 );
//SendMessage( HWndEdit_, WM_SETFONT, (WPARAM)SAHFont, MAKELPARAM(TRUE, 0) );


//sprintf( WTitleSV, "%g", VaG2DLG );
//SetWindowText( HWndEdit_, WTitleSV );
//ShowWindow( HWnd, 1 );


int CXSC = GetSystemMetrics( SM_CXSCREEN );
int CYSC = GetSystemMetrics( SM_CYSCREEN );
int WWC = 280;
int HHC = 340;

CXSC = (WWC+CXSCREEN)/2 - WWC;
CYSC = (HHC+CYSCREEN)/2 - HHC;
IF WVist==0 && HVist==0 THEN
   WVist = WWC;
   HVist = HHC;
   MoveWindow( HWnd, CXSC, CYSC, WWC, HHC, TRUE  );
ELSE
   int XVistT = 0;
   int YVistT = 0;
   
   IF XVist<20 THEN
      XVist = 20;
   ENDIF;
   IF YVist<20 THEN
      YVist = 20;
   ENDIF;
   
   int XVistM = XVist - 100;
   int YVistM = YVist - 100;
   
   WHILE( XVistT!=XVist || YVistT!=YVist )
       IF XVistT!=XVist THEN
          XVistM++;
       ENDIF;
       IF YVistT!=YVist THEN
          YVistM++;
       ENDIF;
       
       MoveWindow( HWnd, XVistM, YVistM, WWC, HHC, TRUE  );
       WindowPos( HWnd, &XVistT, &YVistT );
   ENDLOOP;
ENDIF;
InvalidateRect( HWnd, NULL, TRUE );
return 0;
}
