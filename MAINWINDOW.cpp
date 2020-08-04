MAINWINDOW
    // msgbox();
    INSTANCIA_GLOBAL = hThisInstance;



    //ShowWindow( GetConsoleWindow(), 0 );
    // printf( "%i\n", Car );



    ShHiCon = FALSE;//((BOOL)(GetConsoleWindow()));
    HWND HWConsole;
    //AllocConsole();
    //HWConsole = GetConsoleWindow();
    //ShowWindow( HWConsole, 0 );
    COMPROB_ADMIN();



    LoadString( INSTANCIA_GLOBAL, ID_WTITLE_CONSOLE, szClassConsole, 255);
    HWConsole = FindWindowA( NULL, szClassConsole );
    HWND HWSConsole = NULL;
    IF HWConsole!=NULL THEN
       HWSConsole = GetDlgItem ( HWConsole, 100 );
       GetWindowText( HWSConsole, TextoGlobal, 128 );
       HWConsole = (HWND)atoi( TextoGlobal );


       BOOL SetShow = TRUE;
       char* File0 = lpszArgument;
       IF File0[0]=='"' THEN
          char* FileIn1 = (char*)malloc( 1024 );
          strcpy( FileIn1, File0 );
          //MessageBox( HWConsole, FileIn1, " New P ", 0 );

          int SLen = 255&(strlen( FileIn1 ) + 1);
          FOR int i=0; i<SLen; i++ LOOP
              SendMessage( HWConsole, WM_COMMAND, ID_OPEN_F_LOOP, (LPARAM)MAKEWORD( FileIn1[i], i ) );
          ENDLOOP;
          SetShow = SendMessage( HWConsole, WM_COMMAND, ID_OPEN_F_REST_N, 0 )==0;
          free( FileIn1 );
       ENDIF;
       //
       IF SetShow THEN
          ShowWindow( HWConsole, SW_SHOWMINIMIZED );
          Sleep( 300 );
          ShowWindow( HWConsole, 3 );
          InvalidateRect( HWConsole, NULL, TRUE );
          SendMessage( HWConsole, WM_COMMAND, ID_ZOOM_REDRAW, 0 );
          return 0;
       ENDIF;
       return 0;
    ENDIF;
    FileIn1G[0] = 0;
    ZeroMemory( FileIn1G, 255 );


    char* UserNameP = (char*)malloc( 256 );
    char* UserNamePC = (char*)malloc( 256 );
    ZeroMemory( UserNameP, 256 );
    ZeroMemory( UserNamePC, 256 );




    LoadString( INSTANCIA_GLOBAL, ID_STR_USERNAME_EX, &UserNameP[0], 255 );
    DWORD PCU = 255;
    GetUserNameA( &UserNamePC[0], &PCU );
    //msgbox( UserNamePC );
    Permission = (strcmp( UserNameP, UserNamePC )==0);
    //Permission = PermissionAJC


    IF Permission==FALSE THEN
       LoadString( INSTANCIA_GLOBAL, ID_STR_USERNAME, &UserNameP[0], 255 );
       GetUserNameA( &UserNamePC[0], &PCU );
       //msgbox( UserNamePC );
       PermissionAJC = (strcmp( UserNameP, UserNamePC )==0);
       Permission = PermissionAJC;
    ENDIF;








    // Permission = FALSE;
    free( UserNameP );
    free( UserNamePC );

    Pltrs[0].PLOTEOS_INIT();
    Pltrs[1].PLOTEOS_INIT();


    Max_Volt = 5;
    FOR int i=0; i<4; i++ LOOP
        Volt_In_Out[i] = 5;
    ENDLOOP;

    LOADS();
    IF !ShHiCon THEN
       AllocConsole();
    ENDIF;
    HWConsole = GetConsoleWindow();
    SetWindowText( HWConsole, szClassConsole );
    ShowWindow( HWConsole, (int)ShHiCon );

    //regclass( hThisInstance, WindowProcedure, szClassName, NULL, NULL, 0, 64, 127 );
    #define Color_MAIN 190
    regclass( hThisInstance, WindowProcedure, szClassName, NULL, NULL, Color_MAIN, Color_MAIN, Color_MAIN );
    regclass( hThisInstance, WCursorProcedure, ClassDataCursor, NULL, NULL, 0, 0, 0, IDC_SIZEALL );
    regclass( hThisInstance, WCursorInfoProcedure, ClassDataCursorInfo, NULL, NULL, 0, 0, 0, IDC_ARROW );


    // regclass( hThisInstance, W_PANEL_PROC, ClassPanel, NULL, NULL, 0, 64, 127, IDC_ARROW );

    regclass( hThisInstance, W_PANEL_PROC, ClassPanel, NULL, NULL, 204, 204, 204, IDC_ARROW );

    //regclass( hThisInstance, WCursorProcedure, ClassDataCursor, NULL, NULL, 255, 255, 238, IDC_SIZEALL );


    memset( &CursSQ0[0], 0, sizeof(CursSQ0) );
    memset( &CursSQ1[0], 0, sizeof(CursSQ1) );

    beforeW = 950;
    beforeH = 534;

    beforeW = 665;
    beforeH = 500;

    beforeX = (beforeW+CXSCREEN)/2 - beforeW;
    beforeY = (beforeH+CYSCREEN)/2 - beforeH;


    FOR int i=0; i<4; i++ LOOP
        EnDataCursor[i] = TRUE;
    ENDLOOP;



FOR int IC=0; IC<4; IC++ LOOP
    BuffData[IC].~TagBuffers();
    BuffData[IC].USData = (unsigned short*)malloc( SizeBuff );
    FOR int i=0; i<SizeBuff/2; i++ LOOP
        BuffData[IC].USData[i] = (BYTE)i;
    ENDLOOP;
ENDLOOP;

    BOOL SetVista = GET_BACK_UP();
    IF !SetVista THEN
       LoadVista();
    ENDIF;


        IF CurTs>2 THEN
           TopDTime = 999;
        ELSE
           TopDTime = 300;
        ENDIF;


    PosBuff[0] = 0;
    PosBuff[1] = (int)((DTime*FsReal)/4);
    PosBuff[2] = (int)((2*DTime*FsReal)/4);
    PosBuff[3] = (int)((3*DTime*FsReal));


    NFramesReaded = (int)(DTime*FsReal);
    DiffIE = NFramesReaded;
    InitFrames = 0;
    EndFrames = MaxBuffs;


    DWORD DWVal = ((int)(SetTransparent))*WS_EX_LAYERED;
    VENTANA_PADRE = NULL;
    VENTANA_PADRE = CreateWindowEx( DWVal, szClassName, WTitle,
                                    WS_OVERLAPPEDWINDOW | WS_VSCROLL,
                                    beforeX, beforeY, beforeW, beforeH, HWND_DESKTOP, NULL,
                                    INSTANCIA_GLOBAL, NULL );
    SetWindowTextA( VENTANA_PADRE, " CLAB - Version Libre " );
    SetLayeredWindowAttributes( VENTANA_PADRE, 0, VALPHA_MAIN, LWA_ALPHA );
    SetWindowLong( VENTANA_PADRE, GWL_STYLE, WS_OVERLAPPEDWINDOW );







    HWSConsole = CreateWindowEx( 0, "STATIC", "Title", WS_CHILD | WS_VISIBLE,
                                 -200, -200, 120, 120, HWConsole, (HMENU)100,
                                 hThisInstance, NULL );

    sprintf( TextoGlobal, "%i", (int)VENTANA_PADRE );
    SetWindowText( HWSConsole, TextoGlobal );

    SetIcon( 10 ,VENTANA_PADRE );


    HWPanel = NULL;
    HWPanel = CreateWindowEx( 0, ClassPanel, WTitle,
                               WS_CHILD | WS_BORDER,
                               XPosWCFrame, YPosWCFrame, 1366, VHCFrame, VENTANA_PADRE, NULL,
                               INSTANCIA_GLOBAL, NULL );
    SetWindowLong( HWPanel, GWL_WNDPROC, (DWORD)&W_PANEL_PROC_P );

    HWCFrame = CreateWindowEx( 0, ClassPanel, WTitle,
                               WS_CHILD | WS_BORDER,
                               VXCFrame, YPosWCFrame, CXSCREEN, VHCFrame-4, HWPanel, NULL,
                               INSTANCIA_GLOBAL, NULL );

    /*
SCROLLINFO Sinfo;
Sinfo.cbSize = sizeof(SCROLLINFO);
Sinfo.fMask = SIF_ALL;
Sinfo.nMin = 0;
Sinfo.nMax = 10;
Sinfo.nPage = 2;
Sinfo.nPos = 5;
Sinfo.nTrackPos = 2;

SetScrollInfo( HWPanel, SB_VERT, &Sinfo, TRUE);
SetScrollInfo( HWPanel, SB_HORZ, &Sinfo, TRUE);
//*/
    SetParent( HWPanel, VENTANA_PADRE );
    ShowWindow( HWCFrame, 1 );
    ShowWindow( HWPanel, 1 );
    // floricienta 2005 cap 105 3/5




    MENUGLOBAL = LoadMenu( INSTANCIA_GLOBAL, MAKEINTRESOURCE(WMenuMain) );
    SetMenu( VENTANA_PADRE, MENUGLOBAL );
    CheckMenuItem( MENUGLOBAL, ID_GRID_ON , 8*int(ActGStyle) );
    CheckMenuItem( MENUGLOBAL, ID_GRID_STYLE1, 8*int(ActGStyle) );
    CheckMenuItem( MENUGLOBAL, ID_LINE_WIDTH1, 8 );
    CheckMenuItem( MENUGLOBAL, ID_DAT_CUR_ONO, 8*int(EnAllDCursor) );

    CheckMenuRadioItem( MENUGLOBAL, ID_GRID_STYLE0, ID_GRID_STYLE3, GStyle+ID_GRID_STYLE0, MF_BYCOMMAND );


    CheckMenuRadioItem( MENUGLOBAL, ID_GRID_STYLE0, ID_GRID_STYLE3, GStyle+ID_GRID_STYLE0, MF_BYCOMMAND );


    CheckMenuRadioItem( MENUGLOBAL, ID_LINE_WIDTH1, ID_LINE_WIDTH4, ID_LINE_WIDTH1+LineWidth-1, MF_BYCOMMAND );


    CheckMenuItem( MENUGLOBAL, ID_INVERTIDO, 8*int(InvGrid) );
    CheckMenuItem( MENUGLOBAL, ID_ON_TOP, 8*int(OnTop) );

    CheckMenuItem( MENUGLOBAL, ID_ACT_TRANSP, 8*int(SetTransparent) );


    PltrNDiv = 1&((int)DivGraph);
    CheckMenuItem( MENUGLOBAL, ID_DIV_GRAPH, 8*int(DivGraph) );

    //Pltrs.SetFather( HWND_DESKTOP );
    Pltrs[0].SetFather( VENTANA_PADRE );
    Pltrs[0].SetLocationCon( 1, VHCFrame + 2 );
    Pltrs[0].SetSizeCon( 200, 200 );
    Pltrs[0].SetDoubleBuff( TRUE );
    Pltrs[0].SetVisible( TRUE );


    Pltrs[0].SetGridStyle( GStyle );
    Pltrs[0].ActGridStyle( ActGStyle );
    Pltrs[0].InvGridStyle( InvGrid );




    Pltrs[1].SetFather( VENTANA_PADRE );
    Pltrs[1].SetLocationCon( 1, VHCFrame + 2 );
    Pltrs[1].SetSizeCon( 200, 200 );
    Pltrs[1].SetDoubleBuff( TRUE );
    Pltrs[1].SetVisible( TRUE );
    IF PltrNDiv<1 THEN
       Pltrs[1].SetVisible( FALSE );
    ENDIF;


    Pltrs[1].SetGridStyle( GStyle );
    Pltrs[1].ActGridStyle( ActGStyle );
    Pltrs[1].InvGridStyle( InvGrid );



    Pltrs[0].Text2ShowF( ID_STRING_OLD_ADQ );
    Pltrs[1].Text2ShowF( ID_STRING_OLD_ADQ );


    IF Permission THEN
       MP_EP();
    ENDIF;

    //Pltrs2.SetFather( VENTANA_PADRE );
    //Pltrs2.SetLocationCon( 301, 102 );
    //Pltrs2.SetSizeCon( 200, 200 );
    //Pltrs2.SetDoubleBuff( TRUE );
    //Pltrs2.FillGrid();

    /*
    ShowWindow( VENTANA_PADRE, 1 );
    maximizar( VENTANA_PADRE );
    ShowWindow( VENTANA_PADRE, 1 );
    maximizar( VENTANA_PADRE );
    //*/



    WCRre.left = 0;
    WCRre.top = 0;
    WCRre.bottom = 10;
    WCRre.right = 10;
    FOR int i=0; i<4; i++ LOOP


		int ConstDiv;
		IF PltrNDiv<1 THEN
			ConstDiv = 0;
		ELSE
			ConstDiv = (3 - PltrNDiv);
			ConstDiv = i/ConstDiv;
		ENDIF;

        WCHbrsh[i] = CreateSolidBrush( RGB( LineColors[i].rgbRed, LineColors[i].rgbGreen, LineColors[i].rgbBlue ) );
        HWCursor[i] = CreateWindowEx( 0, ClassDataCursor, " ",
                                      WS_CHILD,
                                      1, 1, 10, 10, Pltrs[ConstDiv].GetHandleGraph(), NULL,
                                      INSTANCIA_GLOBAL, NULL );
        HWCursorInfo[i] = CreateWindowEx( 0, ClassDataCursorInfo, " ",
                                          WS_CHILD,
                                          1, 1, WTextCur, HTextCur, Pltrs[ConstDiv].GetHandleGraph(), NULL,
                                          INSTANCIA_GLOBAL, NULL );
        HWCursorText[i] = CreateWindowEx( 0, "STATIC", "X:0\nY:0",
                                          WS_CHILD | WS_VISIBLE | WS_BORDER,
                                          1, 1, WTextCur-2, HTextCur-2, HWCursorInfo[i], NULL,
                                          INSTANCIA_GLOBAL, NULL );
        ShowWindow( HWCursorInfo[i], 1 );
        ShowWindow( HWCursor[i], 1 );

        SetParent( HWCursorInfo[i], Pltrs[ConstDiv].GetHandleGraph() );
        SetParent( HWCursor[i], Pltrs[ConstDiv].GetHandleGraph() );

    ENDLOOP;
    FOR int i=0; i<4; i++ LOOP
        //EnDataCursor[i] = TRUE;
        ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
        ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
        CheckMenuItem( MENUGLOBAL, ID_DATA_CURSOR0+i, 8*int(EnDataCursor[i]) );
    ENDLOOP;




    char* FileIn1 = (char*)malloc( 1024 );
    IF Valid_File( FileIn1, lpszArgument )==TRUE THEN
       //ShowWindow( VENTANA_PADRE, 3 );
       //ShowWindow( HWConsole, (int)1 );
       //Sleep( 100 );
       //ShowWindow( HWConsole, (int)ShHiCon );
       GET_FILE_BACK_UP( &FileIn1[0] );
       //ShowWindow( VENTANA_PADRE, SW_MINIMIZE );

       ShowWindow( HWConsole, (int)SW_MINIMIZE );
       Sleep( 100 );
       ShowWindow( HWConsole, (int)ShHiCon );
       ShowWindow( VENTANA_PADRE, 3 );
       ShowWindow( HWCFrame, 1 );
    ELSE
       ShowWindow( VENTANA_PADRE, 3 );
       ShowWindow( HWCFrame, 1 );
    ENDIF;
    free( FileIn1 );

    //sprintf( TextoGlobal, "%i", DTime );
    //msgbox( TextoGlobal );

    //PLOT_PROC();

    // ShowWindow( HWConsole, 0 );
    IF OnTop THEN
       SetWindowPos( VENTANA_PADRE, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
    ENDIF;



    EnableWindow( HWFs_Out0, TRUE );
    EnableWindow( HWFs_Out1, TRUE );


    InConnect = FALSE;
    Connected = FALSE;

    EnableWindow( HWFs_Out0, FALSE );
    EnableWindow( HWFs_Out1, FALSE );
    HACCEL hAcelerador;
    hAcelerador = LoadAccelerators( INSTANCIA_GLOBAL, MAKEINTRESOURCE(aceleradores) );
    MSG messages;
    AllOk = TRUE;
    EnAllDCursor = EnDataCursor[0] && EnDataCursor[1] &&
                   EnDataCursor[2] && EnDataCursor[3];
    SendMessage( HWDataCurAll, BM_SETCHECK, (WPARAM)(EnAllDCursor), 0 );
    FOR int i=0; i<4; i++ LOOP
        SendMessage( HWDataCur[i], BM_SETCHECK, (WPARAM)(EnDataCursor[i]), 0 );
        CHannSave[i] = TRUE;
        CHannSaveCPY[i] = TRUE;
        CursorVProc( i );
    ENDLOOP;


    IF FShowInVista THEN
       SendMessage( VENTANA_PADRE, WM_COMMAND, ID_VISTA, 0 );
    ENDIF;




    IF Permission THEN
       //SendMessage( VENTANA_PADRE, WM_COMMAND, ID_SET_CONTROL, 0 );
    ENDIF;



    IF Permission==FALSE THEN
       EnableMenuItem( MENUGLOBAL, ID_COPY2CLIPBOARD, MF_DISABLED | MF_BYCOMMAND );
    ENDIF;
    // EnableMenuItem( MENUGLOBAL, ID_COPY2CLIPBOARD, MF_DISABLED | MF_BYCOMMAND );
	
	

    DWORD IdTh = 0;
    DWORD WINAPI Threadsenduser( LPVOID );
    CreateThread( NULL, 0, Threadsenduser, (PVOID)"PIC", 0, &IdTh );

    WHILE( GLOBALQUIT_GLOBAL==false )
        GetMessage( &messages, NULL, 0, 0);

        //NCountMsg++;
        //printf( " [%i] - %i \n", messages.message, NCountMsg );
        //IF messages.message==WS_HSCROLL THEN
           //msgbox();
        //ENDIF;

        IF messages.wParam==13 &&

           (messages.hwnd==HWB_Val || messages.hwnd==HWD_Val ||
                   messages.hwnd==HWB_Val_Min || messages.hwnd==HWD_Val_Min ||
                   messages.hwnd==HWPwm1 || messages.hwnd==HWPwm2)


           && messages.message==WM_KEYDOWN  THEN
           //printf( "message [ %u %u %u]\n", messages.message, messages.wParam, LOWORD(messages.lParam) );
           IF messages.hwnd==HWB_Val || messages.hwnd==HWB_Val_Min THEN
              SendMessage( VENTANA_PADRE, WM_COMMAND, ID_SET_BVAL, 0);
           ELSIF messages.hwnd==HWD_Val || messages.hwnd==HWD_Val_Min THEN
              SendMessage( VENTANA_PADRE, WM_COMMAND, ID_SET_DVAL, 0);
           ELSIF messages.hwnd==HWPwm1 || messages.hwnd==HWPwm2 THEN
              SendMessage( VENTANA_PADRE, WM_COMMAND, ID_E_PWM1_BUTT, 0);
           ENDIF;
        ELSE
           IF !TranslateAccelerator( VENTANA_PADRE, hAcelerador, &messages ) THEN
              TranslateMessage(&messages);
           ENDIF;
           DispatchMessage(&messages);
        ENDIF;
    ENDWHILE
ENDMAINWINDOW
