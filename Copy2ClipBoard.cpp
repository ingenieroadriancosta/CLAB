int Copy2ClipBoard( char* Texto=NULL ){
size_t len = strlen( Texto );
HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
memcpy( GlobalLock(hMem), Texto, len );
GlobalUnlock(hMem);
OpenClipboard(0);
EmptyClipboard();
SetClipboardData(CF_TEXT, hMem);
CloseClipboard();
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
DWORD WINAPI ThreadCoping( LPVOID );
////////////////////////////////////////////////////////////////////////////////
BOOL FinishCopyDLG = FALSE;
HWND HWnd_DLG_CPY, Hprogress_CPY, HWnd_TextCpy;
////////////////////////////////////////////////////////////////////////////////
BOOL COPY_DATA( void ){
	HWND HWFath = VENTANA_PADRE;
    EnableWindow( HWInVista, TRUE );
    IF InVista THEN
       //EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;

    IF Pltrs[0].isDockF() THEN
       HWFath = Pltrs[0].GetHandleCon();
    ENDIF;

    IF DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoPreCpy), HWFath, CopyDLG )==IDCANCEL THEN
       EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( HWInVista, TRUE );
       return FALSE;
    ENDIF;
    EnableWindow( VENTANA_PADRE, TRUE );

    IF Divisor!=255 && Divisor!=1023 THEN
       Divisor = 255;
    ENDIF;


    char Text2Save[1024];
	char TextTemp[2*1024];
	tic
	FinishCopyDLG = FALSE;
	DWORD IdThGlobal = 0;
	CreateThread( NULL, 0, ThreadCoping, NULL, 0, &IdThGlobal );
	SendMessage( Hprogress_CPY , PBM_SETPOS , (WPARAM)20 , 0 );

	double Values[8];
	double LTime = 0;
	char* CBDataT = (char*)malloc( 20 * MBs );
	int ActInd = 0;
	int MXBFF = (int)(DTime*FsReal);
	FOR int i=0; i<MXBFF; i++ LOOP

		Values[0] = (double)(Volt_In_Out[0]*BuffData[0].USData[i]);
		Values[0] = Values[0]/1023;

		Values[1] = (double)(Volt_In_Out[1]*BuffData[1].USData[i]);
		Values[1] = Values[1]/Divisor;



		Values[2] = (double)(Volt_In_Out[2]*BuffData[2].USData[i]);
		Values[2] = Values[2]/1023;

		Values[3] = (double)(Volt_In_Out[3]*BuffData[3].USData[i]);
		Values[3] = Values[3]/Divisor;



		IF i%8192==0 THEN
			LTime = (double)i;
			LTime = 100*LTime;
			LTime = LTime/MXBFF;
			sprintf( Text2Save, "%5.2f%%\t\t%5.3f Seg.", LTime, toc );
			SetWindowText( HWnd_TextCpy, Text2Save );
			SendMessage( Hprogress_CPY , PBM_SETPOS , (WPARAM)LTime , 0 );
		ENDIF;
		LTime = (double)i;
		LTime = LTime/FsReal;


		sprintf( Text2Save, "%f", LTime );
        FOR int i=0;i<4; i++ LOOP
	        IF CHannSaveCPY[i]==TRUE THEN
               sprintf( TextTemp, "\t%g", Values[i] );
               strcat( Text2Save, TextTemp );
            ENDIF;
        ENDLOOP;
        strcat( (char*)&Text2Save[0], "\n" );
		FOR int Ind=0; (Ind<2048)&&Text2Save[Ind]!=0; Ind++ LOOP
			IF Text2Save[Ind]==46 THEN
				Text2Save[Ind] = 46;
			ENDIF;
			CBDataT[ActInd] = Text2Save[Ind];
			ActInd++;
		ENDLOOP;





	ENDLOOP;
	Copy2ClipBoard( CBDataT );
	free( CBDataT );


	// sprintf( Text2Save, "%i\n%5.3f", NBytes, 0 );

	sprintf( Text2Save, "100%%\t\t%5.3f Seg.", toc );
	SetWindowText( HWnd_TextCpy, Text2Save );
	SendMessage( Hprogress_CPY , PBM_SETPOS , (WPARAM)100, 0 );

	SendMessage( HWnd_DLG_CPY, WM_CLOSE, 0, 0 );
	SendMessage( HWnd_DLG_CPY, WM_DESTROY, 0, 0 );

	FinishCopyDLG = TRUE;

	HWFath = VENTANA_PADRE;
    IF InVista THEN
       //EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;
    EnableWindow( VENTANA_PADRE, TRUE );









return TRUE;
}


////////////////////////////////////////////////////////////////////////////////

//BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
BOOL CALLBACK Dlg_Proc_CPY(HWND hDlg, UINT  msg, WPARAM wParam, LPARAM lParam){
	HWnd_DLG_CPY = hDlg;

	IF FinishCopyDLG THEN
		EndDialog( hDlg, TRUE );
	ENDIF;
	IF msg==WM_INITDIALOG THEN
		CXSCREEN = GetSystemMetrics( SM_CXSCREEN );
		CYSCREEN = GetSystemMetrics( SM_CYSCREEN );


		int beforeW = 300;
		int beforeH = 88;



		beforeX = (beforeW+CXSCREEN)/2 - beforeW;
		beforeY = (beforeH+CYSCREEN)/2 - beforeH;
		MoveWindow( hDlg, beforeX, beforeY, beforeW, beforeH, true );


		HWnd_TextCpy = CreateWindowEx( 0, "STATIC", " ", WS_CHILD | WS_VISIBLE,
									1, 1, 300, 20, hDlg, NULL, INSTANCIA_GLOBAL, NULL );

		#define PBS_SMOOTH2	3
		Hprogress_CPY = CreateWindowEx( WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_TOOLWINDOW,
										PROGRESS_CLASS ,
										(LPSTR)NULL,
										WS_CHILD | WS_VISIBLE | PBS_SMOOTH2,
										0,
										21,
										300 ,
										40 ,
										hDlg,
										NULL,
										INSTANCIA_GLOBAL,
										NULL);
		SendMessage( Hprogress_CPY , PBM_SETRANGE, 0 , MAKELPARAM(0,100) );
		SendMessage( Hprogress_CPY , PBM_SETPOS , (WPARAM)0 , 0 );
		SendMessage( Hprogress_CPY , PBM_SETBKCOLOR , 0 ,  RGB( 200 , 200 , 200 ) );
		SendMessage( Hprogress_CPY , PBM_SETBARCOLOR , 0 , RGB( 0 , 128 , 255 ) );


		ShowWindow( hDlg, 1 );
		InvalidateRect( hDlg, NULL, TRUE );

	ENDIF;

	IF msg==WM_CLOSE || msg==WM_DESTROY THEN
		EndDialog( hDlg, TRUE );
	ENDIF;

return FALSE;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadCoping( LPVOID pv=NULL ){
	HWND HWFath = VENTANA_PADRE;
    EnableWindow( HWInVista, TRUE );
    IF InVista THEN
       //EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;
    DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoSaving), HWFath, Dlg_Proc_CPY );
    EnableWindow( VENTANA_PADRE, TRUE );
	return 0;
}
////////////////////////////////////////////////////////////////////////////////

