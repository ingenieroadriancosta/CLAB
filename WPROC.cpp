DWORD WINAPI ThreadPltrDock( LPVOID );
////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadMaxW( LPVOID pv=NULL ){
while( InMaxWin )Sleep(10);
InMaxWin = TRUE;

FOR int i=0; i<PltrNDiv; i++ LOOP
    Pltrs[i].SetDoubleBuff( FALSE );
ENDLOOP;
Pltrs[0].SetVisible( FALSE );
Pltrs[1].SetVisible( FALSE );
//ShowWindow( VENTANA_PADRE, 0 );
maximizar( VENTANA_PADRE );
//ShowWindow( VENTANA_PADRE, 0 );
InvalidateRect( VENTANA_PADRE, NULL, TRUE );

int  WPloters = WWidth-2;
int  HPloters = (HHeigth - 3 - VHCFrame);



IF Pltrs[0].TrySetSizeCon( WPloters, HPloters ) THEN
   
   IF PltrNDiv==0 THEN
      Pltrs[0].SetSizeCon( WPloters, HPloters );
   ELSE
      Pltrs[0].SetSizeCon( WPloters, HPloters/2 - 4 );
      Pltrs[1].SetSizeCon( WPloters, HPloters/2 - 4 );
      Pltrs[1].SetLocationCon( 1, HPloters/2 + 2 + VHCFrame + 4 );
   ENDIF;
   
   IF Connected THEN
      SetPlot = TRUE;
      SetPlotRes = TRUE;
   ELSE
       FOR int i=0; i<2*PltrNDiv; i++ LOOP
           Pltrs[i].FillGrid();
       ENDLOOP;
      PLOT_PROC();
      //Pltrs.Inval();
   ENDIF;
ENDIF;


IF !Connected THEN
   FOR int i=0; i<4; i++ LOOP
       ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
       ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
   ENDLOOP;
ENDIF;


//msgbox();
//ShowWindow( VENTANA_PADRE, 3 );
IF OnTop THEN
   SetWindowPos( VENTANA_PADRE, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
ELSE
   SetWindowPos( VENTANA_PADRE, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
ENDIF;

IF !Connected THEN
   FOR int i=0; i<2*PltrNDiv; i++ LOOP
       Pltrs[i].SetDoubleBuff( TRUE );
   ENDLOOP;
   
   Pltrs[0].SetVisible( TRUE );
   IF PltrNDiv!=0 THEN
      Pltrs[1].SetVisible( TRUE );
   ENDLOOP;
ENDIF;
SetPlotRes = TRUE;



ShowWindow( HWClose, (int)Wmaximized );
ShowWindow( HWResMax, (int)Wmaximized );
ShowWindow( HWMin, (int)Wmaximized );

/*
ShowWindow( HWClose, (int)TRUE );
ShowWindow( HWResMax, (int)TRUE );
ShowWindow( HWMin, (int)TRUE );
//*/

InvalidateRect( VENTANA_PADRE, NULL, TRUE );
InMaxWin = FALSE;
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
WPROC


//  printf( "[ %i, %i, %i ]\n", message, wParam, lParam );
MESSAGES
WHEN( WM_DEVICECHANGE )
     return DefWindowProc (hwnd, message, wParam, lParam);
     //FUNC_USB( wParam );
WHEN( WM_COMMAND )
     IF LOWORD(wParam)==0 || !AllOk THEN
        return 0;
        
     //ELSIF LOWORD(wParam)==ID_CALL_CALCULADORA THEN
        //CALCULADORA();
        // return 0;
     ELSIF LOWORD(wParam)==ID_COMPLEMENTS THEN
        
        int CursorPos_x = 0;
        int CursorPos_y = 0;
        CursorPos( (int*)&CursorPos_x , (int*)&CursorPos_y );
        HMENU MENUPOP = LoadMenu( INSTANCIA_GLOBAL, MAKEINTRESOURCE(WMenuPop_FCOMP) );
        HMENU popMenu = GetSubMenu( MENUPOP, 0 );
        TrackPopupMenu( popMenu, 0, CursorPos_x, CursorPos_y, 0, VENTANA_PADRE, NULL );
        break;
        
        
        
     ELSIF LOWORD(wParam)==ID_SET_EPP1 THEN
        int CursorPos_x = 0;
        int CursorPos_y = 0;
        CursorPos( (int*)&CursorPos_x , (int*)&CursorPos_y );
        HMENU MENUPOP = LoadMenu( INSTANCIA_GLOBAL, MAKEINTRESOURCE(WMenuPop_EPSEL1) );
        HMENU popMenu = GetSubMenu( MENUPOP, 0 );
        
        CheckMenuItem( popMenu, ID_SET_EP11, 8*int( S_EP1122[0]==1 ) );
        CheckMenuItem( popMenu, ID_SET_EP12, 8*int( S_EP1122[0]==3 ) );
        TrackPopupMenu( popMenu, 0, CursorPos_x, CursorPos_y, 0, VENTANA_PADRE, NULL );
        break;
     ELSIF LOWORD(wParam)==ID_SET_EPP2 THEN
        int CursorPos_x = 0;
        int CursorPos_y = 0;
        CursorPos( (int*)&CursorPos_x , (int*)&CursorPos_y );
        HMENU MENUPOP = LoadMenu( INSTANCIA_GLOBAL, MAKEINTRESOURCE(WMenuPop_EPSEL2) );
        HMENU popMenu = GetSubMenu( MENUPOP, 0 );
        CheckMenuItem( popMenu, ID_SET_EP21, 8*int( S_EP1122[1]==1 ) );
        CheckMenuItem( popMenu, ID_SET_EP22, 8*int( S_EP1122[1]==3 ) );
        TrackPopupMenu( popMenu, 0, CursorPos_x, CursorPos_y, 0, VENTANA_PADRE, NULL );
        break;
        
        
        
        
     ELSIF LOWORD(wParam)==ID_OPEN_F_LOOP THEN
        IF HIBYTE(lParam)<255 THEN
           FileIn1G[(int)HIBYTE(lParam)] = (char)LOBYTE(lParam);
        ENDIF;
        //msgbox( FileIn1G );
        break;
     ELSIF LOWORD(wParam)==ID_OPEN_F_REST_N THEN
        static BOOL InPrcss;
        IF InPrcss THEN
           break;
        ENDIF;
        InPrcss = TRUE;
        IF FileIn1G[0]=='"' THEN
           char* FileIn1 = (char*)malloc( 1024 );
           strcpy( FileIn1, FileIn1G );
           IF Valid_File( FileIn1G, FileIn1 )==TRUE THEN
              free( FileIn1 );
              
              ShowWindow( VENTANA_PADRE, SW_MINIMIZE );
              Sleep( 100 );
              ShowWindow( VENTANA_PADRE, 3 );
              IF GET_FILE_BACK_UP( &FileIn1G[0] ) THEN
                 ShowWindow( VENTANA_PADRE, 1 );
                 Sleep( 100 );
                 ShowWindow( VENTANA_PADRE, 3 );
                 InPrcss = FALSE;
                 return 1;
              ELSE
                 InPrcss = FALSE;
                 return 0;
              ENDIF;
           ELSE
              free( FileIn1 );
              InPrcss = FALSE;
              return 0;
           ENDIF;
        ELSE
           InPrcss = FALSE;
           return 0;
        ENDIF;
        break;
        
     ELSIF LOWORD(wParam)==ID_TAB THEN
        break;
        //SendMessage( HWTime, WM_SETFOCUS, 0, 0 );
     ELSIF LOWORD(wParam)==ID_E_PWM1 THEN
        IF HIWORD(wParam)==EN_KILLFOCUS THEN
           BPwm1 = ValPwm( HWPwm1 );
        ENDIF;
     ELSIF LOWORD(wParam)==ID_E_PWM2 THEN
        IF HIWORD(wParam)==EN_KILLFOCUS THEN
           BPwm2 = ValPwm( HWPwm2 );
        ENDIF;
        //SendMessage( HWTime, WM_SETFOCUS, 0, 0 );
     ELSIF LOWORD(wParam)==ID_E_BVAL THEN
        IF HIWORD(wParam)==EN_KILLFOCUS THEN
           B_Val = AB_Val_Proc( HWB_Val, Volt_In_Out[1] );
        ENDIF;
     ELSIF LOWORD(wParam)==ID_E_DVAL THEN
        IF HIWORD(wParam)==EN_KILLFOCUS THEN
           D_Val = AB_Val_Proc( HWD_Val, Volt_In_Out[3] );
        ENDIF;
     ELSIF LOWORD(wParam)==ID_E_BVAL_MIN THEN
        IF HIWORD(wParam)==EN_KILLFOCUS THEN
           B_Val_Min = AB_Val_Proc( HWB_Val_Min, Volt_In_Out[1] );
        ENDIF;
     ELSIF LOWORD(wParam)==ID_E_DVAL_MIN THEN
        IF HIWORD(wParam)==EN_KILLFOCUS THEN
           D_Val_Min = AB_Val_Proc( HWD_Val_Min, Volt_In_Out[3] );
        ENDIF;
     ELSIF (LOWORD(wParam)>=256 && LOWORD(wParam)<=356) && ( HIWORD(wParam)!=CBN_SELENDOK && lParam!=12345 ) THEN
        return 0;
     ELSIF (LOWORD(wParam)>=512 && LOWORD(wParam)<=612) && (HIWORD(wParam)==EN_KILLFOCUS) THEN
        char Text2D[256];
        GetWindowText( HWTime, Text2D, 255 );
        IF atoi( Text2D )<=0 THEN
           DTime = 1;
           sprintf( Text2D, "%i", DTime );
           SetWindowText( HWTime, Text2D );
        ELSIF atoi( Text2D )>TopDTime THEN
           DTime = TopDTime;
           sprintf( Text2D, "%i", DTime );
           SetWindowText( HWTime, Text2D );
        ENDIF;
        return 0;
     ELSIF (LOWORD(wParam)>=512 && LOWORD(wParam)<=612) && (HIWORD(wParam)!=EN_CHANGE ) THEN
        return 0;
        /*
     ELSIF LOWORD(wParam)==ID_CONNECT THEN
        IF InConnect  THEN
            Connected = FALSE;
            BConnect.setSelected( FALSE );
        ELSIF !InConnect && !Connected THEN
            BConnect.setJPGResource( ID_BUTT_OFF );
            BConnect.setText( ID_CNNBUTTONE );
            Connected = TRUE;
            DWORD IdTh = 0;
            H_CONNECT = CreateThread( NULL, 0, CONNECT, NULL, 0, &IdTh );
            Sleep( 1 );
            SetPriorityClass( H_CONNECT, REALTIME_PRIORITY_CLASS );
            
            H_Plt_Cnn = CreateThread( NULL, 0, PLOT_CONNECT, NULL, 0, &IdThPlt );
            
            //SetPriorityClass( H_CONNECT, THREAD_PRIORITY_TIME_CRITICAL );
            //SetPriorityClass( H_CONNECT,HIGH_PRIORITY_CLASS);
        ENDIF;
        return 0;
        //*/
     ELSE
        wParamC = wParam;
        lParamC = lParam;
        HWThread = hwnd;
        DWORD IdTh = 0;
        CreateThread( NULL, 0, ThreadCommands, NULL, 0, &IdTh );
        return 0;
     ENDIF;
     
     
     
WHEN( WM_RBUTTONDOWN )
     // SetFocus( hwnd );
     int CursorPos_x = 0;
     int CursorPos_y = 0;
     
     HMENU MENUPOP = LoadMenu( INSTANCIA_GLOBAL, MAKEINTRESOURCE(WMenuPop) );
     
     
     
     CheckMenuItem( MENUPOP, ID_GRID_ON , 8*int(ActGStyle) );
     CheckMenuRadioItem( MENUPOP, ID_GRID_STYLE0, ID_GRID_STYLE3, Pltrs[0].GetGridStyle()+ID_GRID_STYLE0, MF_BYCOMMAND);
     
     CheckMenuItem( MENUPOP, ID_ON_TOP, 8*int(OnTop) );
     CheckMenuItem( MENUPOP, ID_INVERTIDO, 8*int(Pltrs[0].IsGridInv()) );
     CheckMenuRadioItem( MENUPOP, ID_LINE_WIDTH1, ID_LINE_WIDTH4, LineWidth+ID_LINE_WIDTH1-1, MF_BYCOMMAND);
     
     
     CheckMenuItem( MENUPOP, ID_ACT_TRANSP, 8*int(SetTransparent) );
     CheckMenuItem( MENUPOP, ID_DIV_GRAPH, 8*int(DivGraph) );
     
     FOR int i=0; i<4; i++ LOOP
         CheckMenuItem( MENUPOP, ID_DATA_CURSOR0+i, 8*int(EnDataCursor[i]) );
     ENDLOOP;
     CheckMenuItem( MENUPOP, ID_DAT_CUR_ONO, 8*int(EnAllDCursor) );
     
     
     IF Connected THEN
        EnableMenuItem( MENUPOP, ID_OPEN_F_REST, MF_DISABLED | MF_BYCOMMAND );
     ELSE
        EnableMenuItem( MENUPOP, ID_OPEN_F_REST, MF_ENABLED );
     ENDIF;
     
     HMENU popMenu = GetSubMenu( MENUPOP , 0 );
     CursorPos( (int*)&CursorPos_x , (int*)&CursorPos_y );
     TrackPopupMenu( popMenu, 0, CursorPos_x, CursorPos_y, 0, VENTANA_PADRE, NULL );
     break;
WHEN( WM_LBUTTONDBLCLK )
     DWORD IdTh = 0;
     CreateThread( NULL, 0, ThreadMaxW, NULL, 0, &IdTh );
     //ShowWindow( VENTANA_PADRE, 3 );
     break;
WHEN( WM_PAINT )
    PAINTSTRUCT         ps;
    HDC HDc = BeginPaint( hwnd, &ps );
    SetBkMode( HDc, TRANSPARENT);
    
    HDC THDC = CreateCompatibleDC( HDc );
    SelectObject( THDC, HB_Fondo );
    SetStretchBltMode( HDc, COLORONCOLOR );

    IF Wmaximized THEN
        StretchBlt( HDc, 0, 0, CXSCREEN, CYSCREEN,
                    THDC, 0, 0, B_Fondo.bmWidth, B_Fondo.bmHeight,
                    SRCCOPY );
    ELSE
        StretchBlt( HDc, 0, 0, 
                    //WWidth, HHeigth,
                    CXFULLSCREEN, CYFULLSCREEN,
                    THDC, 0, 0, B_Fondo.bmWidth, B_Fondo.bmHeight,
                    SRCCOPY );
    ENDIF;
    DeleteDC( THDC );
    
    EndPaint( hwnd, &ps);
    
    // CYMENU
    
WHEN( WM_ENTERSIZEMOVE )
    IF hwnd==VENTANA_PADRE && SetTransparent THEN
       SetLayeredWindowAttributes( VENTANA_PADRE, 0, 64, LWA_ALPHA );
    ENDIF;
WHEN( WM_EXITSIZEMOVE )
    IF hwnd==VENTANA_PADRE THEN
       SetLayeredWindowAttributes( VENTANA_PADRE, 0, VALPHA_MAIN, LWA_ALPHA );
       
       
       int  WPloters = WWidth-2;
       int  HPloters = HHeigth - 3 - VHCFrame;
       BOOL ReAll;
       IF PltrNDiv==0 THEN
          ReAll = Pltrs[0].TrySetSizeCon( WPloters, HPloters );
       ELSE
          ReAll = Pltrs[0].TrySetSizeCon( WPloters, HPloters/2 - 4 );
       ENDIF;
       IF ReAll THEN
          
          
             IF Permission THEN
                
                BCopy.setLocation( WPloters - 35, 1 );
                
             ENDIF;
             
          IF PltrNDiv==0 THEN
             Pltrs[0].SetSizeCon( WPloters, HPloters );
          ELSE
             Pltrs[0].SetSizeCon( WPloters, HPloters/2 - 4 );
             Pltrs[1].SetSizeCon( WPloters, HPloters/2 - 4 );
             Pltrs[1].SetLocationCon( 1, HPloters/2 + 2 + VHCFrame + 4 );
          ENDIF;
          
          
          IF Connected THEN
             SetPlot = TRUE;
          ELSE
             Pltrs[0].SetDoubleBuff( FALSE );
             Pltrs[0].FillGrid();
             IF PltrNDiv!=0 THEN
                Pltrs[1].SetDoubleBuff( FALSE );
                Pltrs[1].FillGrid();
             ENDIF;
             PLOT_PROC();
             Pltrs[0].Inval();
             Pltrs[0].SetDoubleBuff( TRUE );
             Pltrs[1].SetDoubleBuff( TRUE );
             IF PltrNDiv!=0 THEN
                Pltrs[1].Inval();
                Pltrs[1].SetDoubleBuff( TRUE );
             ENDIF;
          ENDIF;
       ENDIF;
    ENDIF;
    
WHEN( WM_SYSCOMMAND )
    IF hwnd==VENTANA_PADRE THEN
       IF wParam==SC_RESTORE || wParam==SC_MAXIMIZE THEN
          ActSize = TRUE;
       ENDIF;
    ENDIF;
    return DefWindowProc (hwnd, message, wParam, lParam);
    
WHEN( WM_NCLBUTTONDBLCLK )
    SetFocus( hwnd );
    IF hwnd==VENTANA_PADRE && 
                           (int)wParam!=HTMENU       &&
                           (int)wParam!=HTZOOM       &&
                           (int)wParam!=HTTOPLEFT    &&
                           
                           (int)wParam!=HTTOPRIGHT   &&
                           (int)wParam!=HTRIGHT      &&
                           (int)wParam!=HTLEFT       &&
                           (int)wParam!=HTBOTTOMLEFT &&
                           (int)wParam!=HTBOTTOMRIGHT     THEN
       ActSize = TRUE;
       IF IsMaxed THEN
          ShowWindow( VENTANA_PADRE, 1 );
       ELSE
          ShowWindow( VENTANA_PADRE, 3 );
       ENDIF;
       break;
    ENDIF;
    return DefWindowProc (hwnd, message, wParam, lParam);
WHEN( WM_SIZE )
    IF wParam==SIZE_MINIMIZED THEN
       IsMinimized = TRUE;
       break;
    ELSIF IsMinimized THEN
       IsMinimized = FALSE;
       break;
    ENDIF;
    
    
    CXSCREEN = GetSystemMetrics( SM_CXSCREEN );
    CYSCREEN = GetSystemMetrics( SM_CYSCREEN );
    
    CXFULLSCREEN = GetSystemMetrics( SM_CXFULLSCREEN );
    CYFULLSCREEN = GetSystemMetrics( SM_CYFULLSCREEN );
    
    IF hwnd==VENTANA_PADRE THEN
       WFather = LOWORD(lParam);
       HFather = HIWORD(lParam);
       
       IF WFather<1220 THEN
          IF VHCFrame!=HCFrameBig THEN
             VHCFrame = HCFrameBig;
             Pltrs[0].SetLocationCon( 1, VHCFrame + 2 );
             SetWindowLong( HWPanel, GWL_STYLE, WS_CHILD | WS_BORDER | WS_HSCROLL );
             
             
             Sinfo.cbSize = sizeof(SCROLLINFO);
             Sinfo.fMask = SIF_ALL;
             Sinfo.nMin = 0;
             Sinfo.nMax = 20;
             Sinfo.nPage = 1;
             //Sinfo.nPos = 0;
             //Sinfo.nTrackPos = 1;
             
             //SetScrollInfo( HWPanel, SB_VERT, &Sinfo, TRUE);
             SetScrollInfo( HWPanel, SB_HORZ, &Sinfo, TRUE);

             ShowWindow( HWPanel, 1 );
          ENDIF;
       ELSE
          IF VHCFrame!=HCFrame THEN
             VHCFrame = HCFrame;
             Pltrs[0].SetLocationCon( 1, VHCFrame + 2 );
             SetWindowLong( HWPanel, GWL_STYLE, WS_CHILD | WS_BORDER );
             ShowWindow( HWPanel, 1 );
          ENDIF;
       ENDIF;
       
          
       
       
       MoveWindow( HWPanel, 1, 1, WFather-2, VHCFrame, TRUE );
       MoveWindow( HWCFrame, 1, 1, WFather - 6, HCFrame - 4, TRUE );
       SetScrollPos( HWPanel, SB_HORZ, 0, TRUE);
       
       
       WWidth  = LOWORD(lParam);
       HHeigth = HIWORD(lParam);
       
       
       IF wParam==SIZE_MAXIMIZED THEN
          IsMaxed = TRUE;
       ELSE
          IsMaxed = FALSE;
       ENDIF;
       
       IF wParam==SIZE_MAXIMIZED || ActSize THEN
          
          
          ActSize = FALSE;
          
          
          int  WPloters = WWidth-2;
          int  HPloters = HHeigth - 3 - VHCFrame;
          
          IF Pltrs[0].TrySetSizeCon( WPloters, HPloters ) || Pltrs[0].isDockF() THEN
             
             IF Permission THEN
                
                BCopy.setLocation( WPloters - 35, 1 );
                
             ENDIF;
             
             IF PltrNDiv==0 THEN
                Pltrs[0].SetSizeCon( WPloters, HPloters );
             ELSE
                Pltrs[0].SetSizeCon( WPloters, HPloters/2 - 4 );
                Pltrs[1].SetSizeCon( WPloters, HPloters/2 - 4 );
                Pltrs[1].SetLocationCon( 1, HPloters/2 + 2 + VHCFrame + 4 );
             ENDIF;
             
             IF Connected THEN
                SetPlot = TRUE;
             ELSE
                Pltrs[0].SetDoubleBuff( FALSE );
                Pltrs[0].FillGrid();
                
                IF PltrNDiv!=0 THEN
                   Pltrs[1].SetDoubleBuff( FALSE );
                   Pltrs[1].FillGrid();
                ENDIF;
                PLOT_PROC();
                Pltrs[0].Inval();
                Pltrs[0].SetDoubleBuff( TRUE );
                
                IF PltrNDiv!=0 THEN
                   Pltrs[0].Inval();
                   Pltrs[0].SetDoubleBuff( TRUE );
                ENDIF;
             ENDIF;
          ENDIF;
       ENDIF;
    ENDIF;
WHEN( WM_CREATE )
     break;
     IF VENTANA_PADRE!=NULL THEN
        return MAINCREATE( hwnd );
     ENDIF;
     
     
     
     
WHEN( WM_MOUSEWHEEL )
     IF Connected THEN
        break;
     ENDIF;
     //
     IF lParam!=12345 THEN
        return 0;
     ENDIF;
     return WHEEL_PROC( wParam );
WHEN( WM_LBUTTONDOWN )
     
     
     IF HWInVista THEN
        //SetLayeredWindowAttributes( HWInVista, 0, VALPHA_VISTA, LWA_ALPHA );
     ENDIF;
     
     
     IF wParam!=12345 THEN
        SetFocus( hwnd );
     ENDIF;
     IF Connected THEN
        break;
     ENDIF;
     //
     LastXPos = LOWORD(lParam);
     IF !MActivate && wParam==12345 THEN
        MActivate = TRUE;
        SetFocus( Pltrs[0].GetHandleCon() );
        DWORD IDTH = 0;
        MActivate = TRUE;
        CreateThread( NULL, 0, ExitActivate, NULL, 0, &IDTH );
     ENDIF;
     break;
WHEN( WM_LBUTTONUP )
	 MActivate = FALSE;
	 CActivate = FALSE;
	 break;
WHEN( WM_MOUSEMOVE )
     
     IF Connected THEN
        break;
     ENDIF;
     
     
     
     //
     IF !MActivate || wParam!=12345 || CActivate || !ISDOWNKEY( VK_LBUTTON ) THEN
        MActivate = FALSE;
        return 0;
     ENDIF;
     //
     int xPos = LOWORD(lParam);
     DiffIE = EndFrames - InitFrames;
     IF DiffIE<2 THEN
        DiffIE = 2;
     ENDIF;
     
     const int MaxTop = (int)(DTime*FsReal);
     IF DiffIE>=MaxTop THEN
        DiffIE = MaxTop;
        break;
     ENDIF;
     
     IF DiffIE<10 THEN
        DiffIE = 10;
     ENDIF;
     
     int DivMMove = 30;
     IF DiffIE<30 THEN
        DivMMove = DiffIE;
     ENDIF;
     
     IF ISDOWNKEY( VK_CONTROL ) THEN
        DivMMove = 5;
     ENDIF;
     
     
     IF xPos>(LastXPos+10) THEN
        InitFrames = InitFrames - DiffIE/DivMMove;
     ELSIF xPos<(LastXPos-10) THEN
        InitFrames = InitFrames + DiffIE/DivMMove;
     ELSE
        break;
     ENDIF;
     LastXPos = xPos;
     IF InitFrames<0 THEN
        InitFrames = 0;
     ENDIF;
     
     IF InitFrames==0 THEN
        EndFrames  = InitFrames + DiffIE;
     ELSE
        EndFrames  = InitFrames + DiffIE;
     ENDIF;
     
     IF InitFrames==EndFrames THEN
        EndFrames  = InitFrames + 1;
     ENDIF;
     PLOT_PROC();
     //DWORD IDP = 0;
     //CreateThread( NULL, 0, Process, NULL, 0, &IDP );
     return 0;
     
     
WHEN( WM_GETMINMAXINFO )
     MINMAXINFO*      mmiStruct = (MINMAXINFO*)lParam;
     POINT            ptPoint;
     ptPoint.x = 790;
     ptPoint.y = 500;
     
     // UPC
     ptPoint.x = 810;
     ptPoint.y = 550;
     // UPC
     
     
     mmiStruct->ptMinTrackSize = ptPoint;
     ptPoint.x = GetSystemMetrics(SM_CXMAXIMIZED);
     ptPoint.y = GetSystemMetrics(SM_CYMAXIMIZED);
     mmiStruct->ptMaxTrackSize = ptPoint;
     return 0;
WHEN( WM_CLOSE )
     IF Connected || InConnect THEN
        char CClose[256];
        LoadString( INSTANCIA_GLOBAL, ID_ADV_DIALOG_CLOSE_ALL, CClose, 255 );
        msgbox( CClose, " Info ", MB_ICONASTERISK | MB_OK );
        return 0;
     ENDIF;
     FShowInVista = InVista;
     PostQuit = TRUE;
     Connected = FALSE;
     Sleep( 100 );
     HSerial.Close();
     
     SendMessage( HW_Cal, WM_CLOSE, 0, 0 );
     SendMessage( HW_Cal, WM_DESTROY, 0, 0 );
     
     IF SetTransparent THEN
        VALPHA_MAIN = 255;
        WHILE( VALPHA_MAIN>0 )
            VALPHA_MAIN = VALPHA_MAIN - 1;
            SetLayeredWindowAttributes( VENTANA_PADRE, 0, VALPHA_MAIN, LWA_ALPHA);
            UpdateWindow( VENTANA_PADRE );
            IF VALPHA_MAIN%2==0 THEN
               Sleep( 10 );
            ENDIF;
        ENDWHILE;
     ENDIF;
     MAKE_BACK_UP();
     Sleep( 100 );
     return DefWindowProc (hwnd, message, wParam, lParam);
     
     
WHEN( WM_DESTROY )
     PostQuit = TRUE;
     DeleteObject( HFontFs );
     DeleteObject( HFont );
     DeleteObject( HFont_S );
     
     DeleteObject( HFontPaintP );
     
     
     
     DeleteObject( HFontComm );
     DeleteObject( HB_Fondo );
     
     DeleteObject( HB_FondoPanel );
     
     
     
     
     
     DeleteObject( HFontFsSq );
     
     
     Connected = FALSE;
     Sleep( 100 );
     HSerial.Close();
     
     GLOBALQUIT_GLOBAL = true;
     Sleep( 100 );
     FOR int IC=0; IC<4; IC++ LOOP
         BuffData[IC].~TagBuffers();
         DeleteObject( HB_CButt_C[IC] );
     ENDLOOP;
     
     FOR int i=0; i<4; i++ LOOP
         DeleteObject( WCHbrsh[i] );
     ENDLOOP;
     
     DeleteObject( HCursorG );
     PostQuitMessage (0);
     break;
     
DEFAULT
     //static int III;
     //printf( " %i - %i \n", message, III );
     //III++;
     return DefWindowProc (hwnd, message, wParam, lParam);
ENDMESSAGES
ENDWPROC
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
DWORD WINAPI ThreadPltrDock( LPVOID pv=NULL ){


return 0;
}
