LRESULT CALLBACK WCursorProcedure (HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam){
MESSAGES
WHEN( WM_LBUTTONUP )
	 CActivate = FALSE;
WHEN( WM_LBUTTONDOWN )
     IF Connected THEN
        break;
     ENDIF;
     IF !CActivate THEN
        CActivate = TRUE;
        FOR int i=0; i<4; i++ LOOP
            IF hwnd==HWCursor[i] || hwnd==HWCursorInfo[i] THEN
               SetFocus( HWCursor[i] );
               DWORD IDTH = 0;
               CreateThread( NULL, 0, CursorActivate, (PVOID)i, 0, &IDTH );
               break;
            ELSIF i==3 THEN
               CActivate = FALSE;
            ENDIF;
        ENDLOOP;
     ENDIF;


WHEN( WM_KEYDOWN )
    IF (int)wParam==VK_RIGHT &&
       (int)wParam==VK_LEFT &&
       (int)wParam==VK_UP &&
       (int)wParam==VK_DOWN  THEN
       return 0;
    ENDIF;


    FOR int i=0; i<4; i++ LOOP
        IF hwnd==HWCursor[i] || hwnd==HWCursorInfo[i] THEN
           // int VoltDiv;
           // double VoltC;
           // double SegC;

           IF (int)wParam==VK_RIGHT || (int)wParam==VK_DOWN THEN
              IF ISDOWNKEY( VK_CONTROL ) && ISDOWNKEY( VK_LSHIFT ) THEN
                 PosBuff[i] = PosBuff[i] + (int)(FsReal);
              ELSIF ISDOWNKEY( VK_CONTROL ) THEN
                 PosBuff[i] = PosBuff[i] + 20;
              ELSE
                 PosBuff[i]++;
              ENDIF;
           ELSIF (int)wParam==VK_LEFT || (int)wParam==VK_UP THEN
              IF ISDOWNKEY( VK_CONTROL ) && ISDOWNKEY( VK_LSHIFT ) THEN
                 PosBuff[i] = PosBuff[i] - (int)(FsReal);
              ELSIF ISDOWNKEY( VK_CONTROL ) THEN
                 PosBuff[i] = PosBuff[i] - 20;
              ELSE
                 PosBuff[i]--;
              ENDIF;
           ENDIF;
           CursorVProc( i );
           break;
        ENDIF;
    ENDLOOP;

WHEN( WM_PAINT )
    PAINTSTRUCT         ps;
    HDC HDc = BeginPaint( hwnd, &ps );
    SetBkMode( HDc, TRANSPARENT);



    FOR int i=0; i<4; i++ LOOP
        IF hwnd==HWCursor[i] || hwnd==HWCursorInfo[i] THEN
           RGBQUAD RgbQ = Pltrs[0].GetBkg();
           DeleteObject( WCHbrsh[i] );
           WCHbrsh[i] = CreateSolidBrush( RGB( ~RgbQ.rgbRed, ~RgbQ.rgbGreen, ~RgbQ.rgbBlue ) );
           FillRect( HDc, &WCRre, WCHbrsh[i] );//WCHbrsh[i] );   // COLOR_WINDOWTEXT
           break;
        //ELSIF  THEN
           //FillRect( HDc, &WCRre, WCHbrsh[i] );
           //break;
        ENDIF;
    ENDLOOP;
    EndPaint( hwnd, &ps);


















DEFAULT
     return DefWindowProc (hwnd, message, wParam, lParam);
ENDMESSAGES
return 0;
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
LRESULT CALLBACK WCursorInfoProcedure( HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam){
MESSAGES

WHEN( WM_RBUTTONDOWN )
     // SetFocus( hwnd );
    FOR int i=0; i<4; i++ LOOP
        IF hwnd==HWCursorInfo[i] THEN
            int CursorPos_x = 0;
            int CursorPos_y = 0;
            CursorPos( (int*)&CursorPos_x , (int*)&CursorPos_y );
            HMENU MENUPOP = LoadMenu( INSTANCIA_GLOBAL, MAKEINTRESOURCE(WMenuPop_DataC0+i) );

            CheckMenuItem( MENUPOP, ID_DATA_CURSOR0+i, 8*int(EnDataCursor[i]) );
            CheckMenuItem( MENUPOP, ID_DAT_CUR_ONO, 8*int(EnAllDCursor) );



            // CheckMenuItem( MENUGLOBAL, ID_DIV_GRAPH, 8*int(DivGraph) );

            HMENU popMenu = GetSubMenu( MENUPOP , 0 );
            TrackPopupMenu( popMenu, 0, CursorPos_x, CursorPos_y, 0, VENTANA_PADRE, NULL );
        ENDIF;
    ENDLOOP;
     break;
WHEN( WM_PAINT )
    PAINTSTRUCT         ps;
    HDC HDc = BeginPaint( hwnd, &ps );
    SetBkMode( HDc, TRANSPARENT);
    RECT Re;
    GetWindowRect( hwnd, &Re );
    FillRect( HDc, &Re, WCHbrsh[0] );
    EndPaint( hwnd, &ps);

WHEN( WM_CTLCOLORSTATIC )
    static HBRUSH Pincel;
    IF !Pincel THEN
        Pincel = CreateSolidBrush( RGB( 255, 255, 255 ) );
    ENDIF;
    SetTextColor( (HDC)wParam, RGB( 0, 0, 0) );
    SetBkColor( (HDC)wParam, RGB( 255, 255, 255) );
    return (LRESULT)Pincel;
DEFAULT
     return DefWindowProc (hwnd, message, wParam, lParam);
ENDMESSAGES
return 0;
}








