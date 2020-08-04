//
BOOL VistaPut( void ){
IF HWInVista THEN
   SendMessage( GetDlgItem( HWInVista, ID_GRID_ON ), BM_SETCHECK, (WPARAM)(ActGStyle), 0 );
   SendMessage( GetDlgItem( HWInVista, ID_DIV_GRAPH ), BM_SETCHECK, (WPARAM)(DivGraph), 0 );
   SendMessage( GetDlgItem( HWInVista, ID_INVERTIDO ), BM_SETCHECK, (WPARAM)(InvGrid), 0 );

   CheckRadioButton( HWInVista, ID_GRID_STYLE0, ID_GRID_STYLE3, GStyle + ID_GRID_STYLE0 );
   CheckRadioButton( HWInVista, ID_LINE_WIDTH1, ID_LINE_WIDTH4, LineWidth + ID_LINE_WIDTH1 - 1 );

   FOR int i=0; i<4; i++ LOOP
       SendMessage( GetDlgItem( HWInVista, ID_DATA_CURSOR0 + i ), BM_SETCHECK, (WPARAM)(EnDataCursor[i]), 0 );
   ENDLOOP;
ENDIF;



SendMessage( HWDataCurAll, BM_SETCHECK, (WPARAM)(EnAllDCursor), 0 );
FOR int i=0; i<4; i++ LOOP
    SendMessage( HWDataCur[i], BM_SETCHECK, (WPARAM)(EnDataCursor[i]), 0 );
ENDLOOP;



return TRUE;
}
//
DWORD WINAPI ThreadCommands( LPVOID pv=NULL ){
HWND hwnd;WPARAM wParam;WPARAM lParam;
wParam = wParamC;
lParam = lParamC;
hwnd = HWThread;

static BOOL InProcVolt;



CASE LOWORD( wParam ) IS
    WHEN( ID_PRUEBAS )
        IF Permission && PermissionAJC THEN
           PRUEBAS();
        ENDIF;
        ///

    WHEN( ID_SAVE_MAT )
        IF Permission || PermissionAJC THEN
           SaveMat();
        ENDIF;
        ///
    WHEN( ID_COPY2CLIPBOARD )
        IF Permission || PermissionAJC THEN
           COPY_DATA();
        ENDIF;
        ///



    WHEN( ID_SET_GAIN )
        IF Permission THEN
           SetGain();
        ENDIF;
        ///

    WHEN( ID_SET_MAXIM_WIN )
        IF Permission THEN
           SetMaxim();
        ENDIF;
        ///





    WHEN( 12345 )
        IF lParam!=12345 THEN
           break;
        ENDIF;
        //msgbox();
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
        ///
//////////////////////////////////////////////////////////////////// E p -- M p.
    WHEN( ID_WLAB )
        ShellExecuteA( NULL, "open", URL_ADRIAN, NULL, NULL, 3 );
    WHEN( ID_SET_EP11 )
        S_EP1122[0] = 1;
        CursorVProc( 0 );
    WHEN( ID_SET_EP12 )
        S_EP1122[0] = 3;
        CursorVProc( 0 );
////
    WHEN( ID_SET_EP21 )
        S_EP1122[1] = 1;
        CursorVProc( 2 );
    WHEN( ID_SET_EP22 )
        S_EP1122[1] = 3;
        CursorVProc( 2 );
//////////////////////////////////////////////////////////////////// E p -- M p.




    WHEN( ID_SET_MP1 )
        USMpActual[0] = BuffData[0].USData[PosBuff[0]];
        CursorVProc( 0 );
        ///
    WHEN( ID_SET_MP2 )
        USMpActual[1] = BuffData[2].USData[PosBuff[2]];
        CursorVProc( 2 );




    WHEN( ID_E_PWM1_BUTT )
        SetPwm();



    WHEN( ID_ZOOM_REDRAW )
        Pltrs[0].Redraw();
        Pltrs[1].Redraw();
        ///

    WHEN( ID_GET_FREQ )
        // GetFreq();




    WHEN( ID_SAVE_BMP )
        SAVE_BMP();
        ///


    WHEN( ID_VISTA )
        IF InVista THEN
           BVista.setSelected( TRUE );

           ShowWindow( HWInVista, SW_SHOWMINIMIZED );
           Sleep( 100 );
           ShowWindow( HWInVista, SW_NORMAL );
           InvalidateRect( HWInVista, NULL, TRUE );
           break;
        ELSE
           InVista = TRUE;
           DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoVista), VENTANA_PADRE, DLG_VISTA );
           InVista = FALSE;
        ENDIF;
    WHEN( ID_ZOOM_IN )
        IF HIWORD(wParam)==BN_KILLFOCUS THEN
           BN_NOTY_ZIN = FALSE;
        ELSIF HIWORD(wParam)==BN_SETFOCUS && BN_NOTY_ZIN==FALSE THEN
           BN_NOTY_ZIN = TRUE;
           ZOOM_IN();
        ENDIF;

    WHEN( ID_ZOOM_OUT )

        IF HIWORD(wParam)==BN_KILLFOCUS THEN
           BN_NOTY_ZOUT = FALSE;
        ELSIF HIWORD(wParam)==BN_SETFOCUS && BN_NOTY_ZOUT==FALSE THEN
           BN_NOTY_ZOUT = TRUE;
           ZOOM_OUT();
        ENDIF;


    WHEN( ID_BUTT_CLOSE )
        SendMessage( VENTANA_PADRE, WM_CLOSE, 0, 0 );
    WHEN( ID_BUTT_RES_MAX )
        SendMessage( VENTANA_PADRE, WM_LBUTTONDBLCLK, 0, 0 );
    WHEN( ID_BUTT_MIN )
        ShowWindow( VENTANA_PADRE, SW_SHOWMINIMIZED );




    WHEN( ID_CALL_CALCULADORA )
        CALCULADORA();



    WHEN( ID_SEL_WV_OUT0 )
        IF InProcVolt THEN
           break;
        ENDIF;
        InProcVolt =  TRUE;
        SET_SQWAVE( 0 );
        InProcVolt = FALSE;

    WHEN( ID_SEL_WV_OUT1 )
        IF InProcVolt THEN
           break;
        ENDIF;
        InProcVolt =  TRUE;
        SET_SQWAVE( 1 );
        InProcVolt = FALSE;

    WHEN( ID_SET_FS_OUT0 )
        IF InProcVolt THEN
           break;
        ENDIF;
        InProcVolt =  TRUE;
        SET_SQWAVE( 2 );
        InProcVolt = FALSE;

    WHEN( ID_SET_FS_OUT1 )
        IF InProcVolt THEN
           break;
        ENDIF;
        InProcVolt =  TRUE;
        SET_SQWAVE( 3 );
        InProcVolt = FALSE;



    WHEN( ID_FILES_SCHTAD_NEW_887 )
        LoadSch_New( 887 );
    WHEN( ID_FILES_SCHTAD_NEW )
        LoadSch_New( 877 );


    WHEN( ID_FILES_SCH_690 )
        LoadSch_New( 690 );

    WHEN( ID_FILES_SCHTAD )
        LoadSch();
    WHEN( ID_FILES_PLDRV )
        LoadDrvr();

    WHEN( ID_FILES_FIRM )
        LoadFirmWare( 877 );
    WHEN( ID_FILES_FIRM_887 )
        LoadFirmWare( 887 );


    WHEN( ID_FILES_FIRM_690 )
        LoadFirmWare( 690 );







    WHEN( ID_OPEN_WORK_DIR )
        ShellExecuteA( NULL, "open", Fold_Adm, NULL, NULL, 3 );
        /// msgbox( Fold_Adm );


    WHEN( ID_ABOUT )
        ABOUT();
    WHEN( ID_OPEN_F_REST )
        GET_FILE_BACK_UP();

    WHEN( ID_SAVE_F_REST )
        MAKE_FILE_BACK_UP();
        int ii=0;
        ii++;



    WHEN( ID_CLEAR_ALL )
        IF !Connected THEN
           char CCAll[256];
           LoadString( INSTANCIA_GLOBAL, ID_ADV_DIALOG_CLEAR_ALL, CCAll, 255 );
           //int Res = msgbox( CCAll, " Advertencia ", MB_OK | MB_ICONWARNING );
           //sprintf( CCAll, "%i", Res );
           //msgbox( CCAll );
           IF msgbox( CCAll, " Advertencia ", MB_OKCANCEL | MB_ICONWARNING )==IDOK THEN
              LoadString( INSTANCIA_GLOBAL, ID_DIALOG_CLEAR_ALL, CCAll, 255 );
              IF msgbox( CCAll, " ¿ ? ", MB_ICONQUESTION | MB_YESNO )==IDYES THEN
                 CLEAR_ALL();
                 InitFrames = 0;
                 DiffIE = (int)(DTime*FsReal);
                 EndFrames = DiffIE;


                 PosBuff[0] = 0;
                 PosBuff[1] = DiffIE/4;
                 PosBuff[2] = (2*DiffIE)/4;
                 PosBuff[3] = (3*DiffIE);


                 PLOT_PROC();


                 Pltrs[0].Text2ShowF( "" );
                 Pltrs[1].Text2ShowF( "" );

                 SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );

              ENDIF;
           ENDIF;
        ENDIF;
    WHEN( ID_RESET_ALL )
        IF !Connected && !InClearAll THEN
           InClearAll = TRUE;

           //Max_Volt = 5;

           Pltrs[0].SetMaxYLim( Max_Volt );
           Pltrs[1].SetMaxYLim( Max_Volt );
           Pltrs[0].Inval();
           Pltrs[1].Inval();

           FOR int i=0; i<4; i++ LOOP
               //Volt_In_Out[i] = 5;
           ENDLOOP;

           InitFrames = 0;
           DiffIE = (int)(DTime*FsReal);
           EndFrames = DiffIE;

           PosBuff[0] = 0;
           PosBuff[1] = DiffIE/4;
           PosBuff[2] = (2*DiffIE)/4;
           PosBuff[3] = (3*DiffIE);

           PLOT_PROC();
           SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );
           InClearAll = FALSE;
        ENDIF;



    WHEN( ID_SAVE_DATA )
        SaveProc();

    WHEN( ID_CONNECT )
        IF InConnect  THEN
            Connected = FALSE;
            BConnect.setSelected( FALSE );
        ELSIF !InConnect && !Connected THEN
            BConnect.setJPGResource( ID_BUTT_OFF );
            BConnect.setText( ID_CNNBUTTONE );
            Connected = TRUE;
            DWORD IdTh = 0;
            H_CONNECT = CreateThread( NULL, 0, CONNECT, NULL, 0, &IdTh );
            SetPriorityClass( H_CONNECT, REALTIME_PRIORITY_CLASS );
        ENDIF;
        //*/



    WHEN( ID_SET_TIME )
        static BOOL InSetTime;
        IF InSetTime THEN
           break;
        ENDIF;
        InSetTime = TRUE;
        char Text2D[256];
        LSetTime:

        GetWindowText( HWTime, Text2D, 255 );
        DTime = atoi( Text2D );
        IF DTime>TopDTime THEN
           DTime = TopDTime;
           sprintf( Text2D, "%i", DTime );
           SetWindowText( HWTime, Text2D );
           SendMessage( HWTime, EM_SETSEL, 0, 3 );
        ELSIF DTime<0 THEN
           DTime = 1;
           sprintf( Text2D, "%i", DTime );
           SetWindowText( HWTime, Text2D );
        ENDIF;



        DiffIE = (int)(DTime*FsReal);
        InitFrames = 0;
        NFramesReaded = (int)(DTime*FsReal);
        EndFrames = DiffIE;
        PosBuff[0] = 0;
        PosBuff[1] = DiffIE/4;
        PosBuff[2] = (2*DiffIE)/4;
        PosBuff[3] = (3*DiffIE);


        Pltrs[0].SetMaxXLim( (double)DTime );
        Pltrs[1].SetMaxXLim( (double)DTime );
        PLOT_PROC();

        GetWindowText( HWTime, Text2D, 255 );
        IF DTime!=atoi( Text2D ) THEN
            /*
            char Text23[1024];
            sprintf( Text23, "%i", CntPlt );
            CntPlt++;
            SetWindowText( VENTANA_PADRE, Text23 );
            //*/
            goto LSetTime;
        ENDIF;
        //sprintf( TextoGlobal, "Text2D, %s\n\nDTime, %g\n", Text2D, DTime );
        //msgbox( TextoGlobal );
        InSetTime = FALSE;





    WHEN( ID_SET_FS )
        static BOOL InSFS;
        IF InSFS THEN
           break;
        ENDIF;
        InSFS = TRUE;
        int TCurTs = 0;
        ReCurTs:
        TCurTs = (int)SendMessage( HWTs, CB_GETCURSEL, 0, 0 );
        CurTs = TCurTs;



        IF CurTs>2 THEN
           TopDTime = 999;
        ELSE
           TopDTime = 300;
        ENDIF;



        FsReal = MaxFsReal/CurFs[CurTs];
        Fs = Cur2Send[CurTs];

        /*
        sprintf( TextoGlobal, "%g\n%f\n CurTs, %i \n__%u\n", FsReal, CurFs[CurTs], CurTs,
                              Cur2Send[CurTs] );
        msgbox( TextoGlobal );
        //*/

        InitFrames = 0;
        DiffIE = (int)(DTime*FsReal);
        EndFrames = DiffIE;

        PosBuff[0] = 0;
        PosBuff[1] = DiffIE/4;
        PosBuff[2] = (2*DiffIE)/4;
        PosBuff[3] = (3*DiffIE);


        DiffIE = (int)(DTime*FsReal);
        InitFrames = 0;
        NFramesReaded = (int)(DTime*FsReal);
        PLOT_PROC();

        TCurTs = (int)SendMessage( HWTs, CB_GETCURSEL, 0, 0 );
        IF CurTs!=TCurTs THEN
           goto ReCurTs;
        ENDIF;

        //sprintf( TextoGlobal, "CurTs, %i\nFs, %i\n", CurTs, Fs );
        //msgbox( TextoGlobal );
        InSFS = FALSE;
    WHEN( ID_AVPORTS )
        //CreateThread( NULL, 0, ThreadAVP, (VOID*)(TRUE), 0, &IdThAvPort );
        AVPORTS( TRUE );
    WHEN( ID_GRID_ON )
        static BOOL InRej;
        IF InRej THEN
           break;
        ENDIF;
        InRej = TRUE;

        // GetMenuState(HMENU,UINT,UINT);
        ActGStyle = GetMenuState( MENUGLOBAL, ID_GRID_ON, MF_BYCOMMAND )==MF_CHECKED;
        ActGStyle = !ActGStyle;
        Pltrs[0].ActGridStyle( ActGStyle );
        Pltrs[1].ActGridStyle( ActGStyle );
        CheckMenuItem( MENUGLOBAL, ID_GRID_ON , 8*int(ActGStyle) );

        IF Connected THEN
           SetPlot = TRUE;
        ELSE
           PLOT_PROC();
        ENDIF;

        VistaPut();

        InRej = FALSE;
        // ActGStyle
        break;
    }case ID_GRID_STYLE0:
    case ID_GRID_STYLE1:
    case ID_GRID_STYLE2:
    case ID_GRID_STYLE3:{
        static BOOL InRejS;
        IF InRejS THEN
           break;
        ENDIF;
        InRejS = TRUE;
        ActGStyle = TRUE;

        Pltrs[0].ActGridStyle( ActGStyle );
        Pltrs[1].ActGridStyle( ActGStyle );
        CheckMenuItem( MENUGLOBAL, ID_GRID_ON , 8*int(ActGStyle) );

        GStyle = LOWORD( wParam ) - ID_GRID_STYLE0;
        CheckMenuRadioItem( MENUGLOBAL, ID_GRID_STYLE0, ID_GRID_STYLE3, LOWORD( wParam ), MF_BYCOMMAND);
        Pltrs[0].SetGridStyle( GStyle );
        Pltrs[1].SetGridStyle( GStyle );




        IF Connected THEN
           SetPlot = TRUE;
        ELSE
           PLOT_PROC();
        ENDIF;

        VistaPut();


        InRejS = FALSE;

        break;
    }case ID_LINE_WIDTH1:
    case ID_LINE_WIDTH2:
    case ID_LINE_WIDTH3:
    case ID_LINE_WIDTH4:{
        static BOOL BInLineW;
        IF BInLineW THEN
           break;
        ENDIF;
        BInLineW = TRUE;
        CheckMenuRadioItem( MENUGLOBAL, ID_LINE_WIDTH1, ID_LINE_WIDTH4, LOWORD( wParam ), MF_BYCOMMAND);
        LineWidth = 1 + LOWORD( wParam ) - ID_LINE_WIDTH1;



        IF Connected THEN
           SetPlot = TRUE;
        ELSE
           PLOT_PROC();
        ENDIF;

        VistaPut();

        BInLineW = FALSE;


    WHEN( ID_INVERTIDO )
        static BOOL InInvRej;
        IF InInvRej THEN
           break;
        ENDIF;
        InInvRej = TRUE;
        InvGrid = !InvGrid;
        Pltrs[0].InvGridStyle( InvGrid );
        Pltrs[1].InvGridStyle( InvGrid );
        CheckMenuItem( MENUGLOBAL, ID_INVERTIDO, 8*int(Pltrs[0].IsGridInv()) );


        IF Connected THEN
           SetPlot = TRUE;
        ELSE
           PLOT_PROC();
        ENDIF;

        VistaPut();
        InInvRej = FALSE;

    WHEN( ID_ON_TOP )
        OnTop = !OnTop;
        IF OnTop THEN
           SetWindowPos( VENTANA_PADRE, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
        ELSE
           SetWindowPos( VENTANA_PADRE, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
        ENDIF;
        CheckMenuItem( MENUGLOBAL, ID_ON_TOP, 8*int(OnTop) );







    WHEN( ID_SET_PVAL )
        IF InProcVolt THEN
           break;
        ENDIF;
        InProcVolt = TRUE;
        BConnect.setEnabled( FALSE );
        B_Val = AB_Val_Proc( HWB_Val, Volt_In_Out[1] );
        B_Val_Min = AB_Val_Proc( HWB_Val_Min, Volt_In_Out[1] );
        IF Connected THEN
           SetVolt( B_Val, B_Val_Min );
        ELSIF OpenSerialProc()==1 THEN
           SetVolt( B_Val, B_Val_Min );
           HSerial.Close();
        ENDIF;
        //
        D_Val = AB_Val_Proc( HWD_Val, Volt_In_Out[3] );
        D_Val_Min = AB_Val_Proc( HWD_Val_Min, Volt_In_Out[3] );
        IF Connected THEN
           SetVolt( D_Val, D_Val_Min, FALSE );
        ELSIF OpenSerialProc()==1 THEN
           SetVolt( D_Val, D_Val_Min, FALSE );
           HSerial.Close();
        ENDIF;
        BConnect.setEnabled( TRUE );
        InProcVolt = FALSE;



    WHEN( ID_SET_BVAL )
        IF InProcVolt THEN
           break;
        ENDIF;
        InProcVolt = TRUE;
        BConnect.setEnabled( FALSE );
        B_Val = AB_Val_Proc( HWB_Val, Volt_In_Out[1] );
        B_Val_Min = AB_Val_Proc( HWB_Val_Min, Volt_In_Out[1] );
        IF Connected THEN
           //SendVoltA = TRUE;
           SetVolt( B_Val, B_Val_Min );
        ELSIF OpenSerialProc()==1 THEN
           SetVolt( B_Val, B_Val_Min );
           HSerial.Close();
        ENDIF;
        BConnect.setEnabled( TRUE );
        InProcVolt = FALSE;

    WHEN( ID_SET_DVAL )
        IF InProcVolt THEN
           break;
        ENDIF;
        InProcVolt = TRUE;
        BConnect.setEnabled( FALSE );
        D_Val = AB_Val_Proc( HWD_Val, Volt_In_Out[3] );
        D_Val_Min = AB_Val_Proc( HWD_Val_Min, Volt_In_Out[3] );
        IF Connected THEN
           //SendVoltB = TRUE;
           SetVolt( D_Val, D_Val_Min, FALSE );
        ELSIF OpenSerialProc()==1 THEN
           SetVolt( D_Val, D_Val_Min, FALSE );
           HSerial.Close();
        ENDIF;
        BConnect.setEnabled( TRUE );
        InProcVolt = FALSE;


    ///////// InOuts;
    //-->
    WHEN( ID_SH_IN )
        PROC_ALL_CHANN( (HWND)(lParam), ID_SH_IN );
    WHEN( ID_SH_OUT )
        PROC_ALL_CHANN( (HWND)(lParam), ID_SH_OUT );

    WHEN( ID_SH_C0_IN )
        PROC_CHANN( ID_SH_C0_IN );
    WHEN( ID_SH_C1_IN )
        PROC_CHANN( ID_SH_C1_IN );
    WHEN( ID_SH_C0_OUT )
        PROC_CHANN( ID_SH_C0_OUT );
    WHEN( ID_SH_C1_OUT )
        PROC_CHANN( ID_SH_C1_OUT );


    ///////// Colors;
    //-->
    WHEN( ID_COLOR_C0_IN )
        IF ChosseRGBColor( LineColors[0] ) THEN
           LineColors[0] = ColorSel;
           SetColChann( 0 );
           //InvalidateRect( HWSel_Chann0_In, NULL, TRUE );
           IF Connected THEN
              SetPlot = TRUE;
           ELSE
              PLOT_PROC();
           ENDIF;
        ENDIF;
    WHEN( ID_COLOR_C1_IN )
        IF ChosseRGBColor( LineColors[2] ) THEN
           LineColors[2] = ColorSel;
           SetColChann( 2 );
           //InvalidateRect( HWSel_Chann1_In, NULL, TRUE );
           IF Connected THEN
              SetPlot = TRUE;
           ELSE
              PLOT_PROC();
           ENDIF;
        ENDIF;
    //--->
    WHEN( ID_COLOR_C0_OUT )
        IF ChosseRGBColor( LineColors[1] ) THEN
           LineColors[1] = ColorSel;
           SetColChann( 1 );
           //InvalidateRect( HWSel_Chann0_Out, NULL, TRUE );
           IF Connected THEN
              SetPlot = TRUE;
           ELSE
              PLOT_PROC();
           ENDIF;
        ENDIF;
    WHEN( ID_COLOR_C1_OUT )
        IF ChosseRGBColor( LineColors[3] ) THEN
           LineColors[3] = ColorSel;
           SetColChann( 3 );
           //InvalidateRect( HWSel_Chann1_Out, NULL, TRUE );
           IF Connected THEN
              SetPlot = TRUE;
           ELSE
              PLOT_PROC();
           ENDIF;
        ENDIF;
        break;

    }case ID_DATA_CURSOR0:
    case ID_DATA_CURSOR1:
    case ID_DATA_CURSOR2:
    case ID_DATA_CURSOR3:{

        static BOOL InDataC03;
        IF InDataC03 THEN
           break;
        ENDIF;
        InDataC03 = TRUE;

        int IDCur = LOWORD( wParam ) - ID_DATA_CURSOR0;
        EnDataCursor[IDCur] = !EnDataCursor[IDCur];
        CheckMenuItem( MENUGLOBAL, LOWORD( wParam ), 8*int(EnDataCursor[IDCur]) );
        SetFocus( HWCursor[IDCur] );
        IF !Connected THEN
           FOR int i=0; i<4; i++ LOOP
               ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
               ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
               SendMessage( HWDataCur[i], BM_SETCHECK, (WPARAM)(EnDataCursor[i]), 0 );
           ENDLOOP;
           EnAllDCursor = EnDataCursor[0] && EnDataCursor[1] &&
                          EnDataCursor[2] && EnDataCursor[3];
           CheckMenuItem( MENUGLOBAL, ID_DAT_CUR_ONO, 8*int(EnAllDCursor) );
        ENDIF;

        VistaPut();
        InDataC03 = FALSE;

    WHEN( ID_DAT_CUR_ONO )
        EnAllDCursor = !EnAllDCursor;
        CheckMenuItem( MENUGLOBAL, LOWORD( wParam ), 8*int(EnAllDCursor) );

        FOR int i=0; i<4; i++ LOOP
            EnDataCursor[i] = EnAllDCursor;
            CheckMenuItem( MENUGLOBAL, ID_DATA_CURSOR0+i, 8*int(EnAllDCursor) );
            IF !Connected THEN
               ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
               ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
            ENDIF;
        ENDLOOP;

        VistaPut();


    WHEN( ID_ACT_TRANSP )
        SetTransparent = !SetTransparent;
        CheckMenuItem( MENUGLOBAL, ID_ACT_TRANSP, 8*int(SetTransparent) );


        IF SetTransparent THEN
           SetWindowLongA( VENTANA_PADRE, GWL_EXSTYLE, WS_EX_LAYERED );
        ELSE
           SetWindowLongA( VENTANA_PADRE, GWL_EXSTYLE, 0 );
        ENDIF;


    WHEN( ID_DIV_GRAPH )
        IF Pltrs[0].isDockF() THEN
           break;
        ENDIF;
        static BOOL InDivG;
        IF InDivG THEN
           break;
        ENDIF;
        InDivG = TRUE;

        Pltrs[0].SetVisible( FALSE );
        Pltrs[1].SetVisible( FALSE );

        DivGraph = !DivGraph;

        IF DivGraph THEN
           SetParent( BtnMp[1].GetHandle(), Pltrs[1].GetHandleCon() );
           SetParent( Mp[1].GetHandle(), Pltrs[1].GetHandleCon() );
           SetParent( BtnEp[1].GetHandle(), Pltrs[1].GetHandleCon() );
           SetParent( Ep[1].GetHandle(), Pltrs[1].GetHandleCon() );


           BtnMp[1].setLocation( BtnMp[0].getX(), BtnMp[0].getY() );
           Mp[1].setLocation( Mp[0].getX(), Mp[0].getY() );
           BtnEp[1].setLocation( BtnEp[0].getX(), BtnEp[0].getY() );
           Ep[1].setLocation( Ep[0].getX(), Ep[0].getY() );


        ELSE
           SetParent( BtnMp[1].GetHandle(), Pltrs[0].GetHandleCon() );
           SetParent( Mp[1].GetHandle(), Pltrs[0].GetHandleCon() );
           SetParent( BtnEp[1].GetHandle(), Pltrs[0].GetHandleCon() );
           SetParent( Ep[1].GetHandle(), Pltrs[0].GetHandleCon() );


           BtnMp[1].setLocation( Ep[0].getX() + Ep[0].getWidth() + 80, 2 );
           Mp[1].setLocation(  BtnMp[1].getX() + BtnMp[1].getWidth() + 1, BtnMp[1].getY() );
           BtnEp[1].setLocation( Mp[1].getX() + Mp[1].getWidth() + 16, 2 );
           Ep[1].setLocation( BtnEp[1].getX() + BtnEp[1].getWidth() + 1, BtnEp[1].getY() );

        ENDIF;


        PltrNDiv = 1&((int)DivGraph);
        CheckMenuItem( MENUGLOBAL, ID_DIV_GRAPH, 8*int(DivGraph) );


        FOR int i=0; i<4; i++ LOOP
            int ConstDiv;
    		IF PltrNDiv<1 THEN
    			ConstDiv = 0;
    		ELSE
    			ConstDiv = (3 - PltrNDiv);
    			ConstDiv = i/ConstDiv;
    		ENDIF;


            SetParent( HWCursorInfo[i], Pltrs[ConstDiv].GetHandleGraph() );
            SetParent( HWCursor[i], Pltrs[ConstDiv].GetHandleGraph() );
	    ENDLOOP;



        int  WPloters = WWidth-2;
        int  HPloters = (HHeigth - 3 - VHCFrame);



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

           Pltrs[0].SetVisible( TRUE );

           IF PltrNDiv==0 THEN
              Pltrs[1].SetVisible( FALSE );
           ELSE
              Pltrs[1].SetVisible( TRUE );
           ENDIF;
           //Pltrs.Inval();
        ENDIF;

        VistaPut();

        InDivG = FALSE;
        Replace = FALSE;





    WHEN( ID_AMP_0 )
        SET_AMPS( ID_AMP_0 );
    WHEN( ID_AMP_1 )
        SET_AMPS( ID_AMP_1 );
    WHEN( ID_AMP_2 )
        SET_AMPS( ID_AMP_2 );
    WHEN( ID_AMP_3 )
        SET_AMPS( ID_AMP_3 );


    WHEN( ID_SALIR )
        PostMessage( hwnd, WM_CLOSE, 0, 0 );
    DEFAULT
        break;
ENDCASE;
return 0;
}
