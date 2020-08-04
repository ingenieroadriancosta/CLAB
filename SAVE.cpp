#include "SaveDLG.cpp"
DWORD WINAPI ThreadSaving( LPVOID );
HWND HWnd_DLG, Hprogress_SAVE, HWnd_Text;
BOOL FinishSaveDLG = FALSE;
BOOL SAVE_DATA( char* TFile ){
	HWND HWFath = VENTANA_PADRE;
    EnableWindow( HWInVista, TRUE );
    IF InVista THEN
       //EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;
    IF DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoPreSave), HWFath, SaveDLG )==IDCANCEL THEN
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
	FinishSaveDLG = FALSE;

	char CharError[64];
	char CharMsg[1024];
	LoadString( INSTANCIA_GLOBAL, ID_TMSG_ERROR, CharError, 63 );

	DWORD IdThGlobal = 0;
	CreateThread( NULL, 0, ThreadSaving, NULL, 0, &IdThGlobal );
	SendMessage( Hprogress_SAVE , PBM_SETPOS , (WPARAM)20 , 0 );




	double Values[8];
	double LTime = 0;
	DWORD NBytes = 0;
	DWORD written = 0;
	DeleteFileA( TFile );
	HANDLE HFile = CreateFile( TFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD LastError = GetLastError();
	IF LastError==ERROR_SHARING_VIOLATION THEN
		Sleep( 100 );
		FinishSaveDLG = TRUE;
		SendMessage( HWnd_DLG, WM_CLOSE, 0, 0 );
		SendMessage( HWnd_DLG, WM_DESTROY, 0, 0 );

		LoadString( INSTANCIA_GLOBAL, ID_SAVE_SHARING_VIOLATION, CharMsg, 255 );

		msgbox( CharMsg, CharError, 16 );
		return FALSE;
	ENDIF;



	IF !HFile THEN
		Sleep( 100 );
		FinishSaveDLG = TRUE;
		SendMessage( HWnd_DLG, WM_CLOSE, 0, 0 );
		SendMessage( HWnd_DLG, WM_DESTROY, 0, 0 );

		LoadString( INSTANCIA_GLOBAL, ID_SAVE_NO_HFILE, CharMsg, 255 );
		msgbox( CharMsg, CharError, 16 );
	ENDIF;



	LoadString( INSTANCIA_GLOBAL, ID_SAVE_HEAD_MSG, TextTemp, 1023 );
	sprintf( Text2Save, TextTemp,
             FsReal, DTime,
             Volt_In_Out[0],
             Volt_In_Out[1],
             Volt_In_Out[2],
             Volt_In_Out[3]
              );
    // msgbox( Text2Save );
	NBytes = strlen(Text2Save);
	WriteFile( HFile, &Text2Save[0], NBytes, &written, NULL);
	IF written!=NBytes THEN
		FinishSaveDLG = TRUE;
		CloseHandle( HFile );
		LoadString( INSTANCIA_GLOBAL, ID_SAVE_ERROR_WR, CharMsg, 255 );
		msgbox( CharMsg, CharError, 16 );

		FinishSaveDLG = TRUE;
		return FALSE;
	ENDIF;



	Text2Save[0] = 0;
	LoadString( INSTANCIA_GLOBAL, ID_SAVE_HEAD_CHANN_INIT, Text2Save, 1023 );
	LoadString( INSTANCIA_GLOBAL, ID_SAVE_HEAD_CHANN_TIME, Text2Save, 1023 );


	FOR int i=0;i<4; i++ LOOP
	    IF CHannSave[i]==TRUE THEN
           LoadString( INSTANCIA_GLOBAL, ID_SAVE_HEAD_CHANN_0+i, TextTemp, 1023 );
           strcat( (char*)&Text2Save[0], TextTemp );
	    ENDIF;
	ENDLOOP;
	strcat( (char*)&Text2Save[0], "\n" );



	NBytes = strlen(Text2Save);
	WriteFile( HFile, &Text2Save[0], NBytes, &written, NULL);
	IF NBytes!=written THEN
		FinishSaveDLG = TRUE;
		LoadString( INSTANCIA_GLOBAL, ID_SAVE_ERROR_WR, CharMsg, 255 );
		msgbox( CharMsg, CharError, 16 );
		return FALSE;
	ENDIF;


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
			SetWindowText( HWnd_Text, Text2Save );
			SendMessage( Hprogress_SAVE , PBM_SETPOS , (WPARAM)LTime , 0 );
		ENDIF;
		LTime = (double)i;
		LTime = LTime/FsReal;


		sprintf( Text2Save, "%f", LTime );
        FOR int i=0;i<4; i++ LOOP
	        IF CHannSave[i]==TRUE THEN
               sprintf( TextTemp, ";%g", Values[i] );
               strcat( Text2Save, TextTemp );
            ENDIF;
        ENDLOOP;
        strcat( (char*)&Text2Save[0], "\n" );
        /*
		sprintf( Text2Save,
				//        LTime O1    I1    O2    I2    O3    I3    O4    I4
				"%f;%g;%g;%g;%g;\n",
				LTime,
				Values[0],
				Values[1],
				Values[2],
				Values[3]
		);
		//*/


		NBytes = 0;
		FOR int Ind=0; (Ind<2048)&&Text2Save[Ind]!=0; Ind++ LOOP
			IF Text2Save[Ind]==46 THEN
				Text2Save[Ind] = 44;
			ENDIF;
			NBytes = Ind + 1;
		ENDLOOP;
        // msgbox( Text2Save );
		// exit( 0 );
		WriteFile( HFile, &Text2Save[0], NBytes, &written, NULL);

		IF NBytes!=written THEN
			FinishSaveDLG = TRUE;
			LoadString( INSTANCIA_GLOBAL, ID_SAVE_ERROR_WR, CharMsg, 255 );
			msgbox( CharMsg, CharError, 16 );
			break;
		ENDIF;

	ENDLOOP;
	sprintf( Text2Save, "%u\n%5.3f", (unsigned int)NBytes, 0.0 );
	CloseHandle( HFile );
	FinishSaveDLG = TRUE;
	SendMessage( HWnd_DLG, WM_CLOSE, 0, 0 );
	SendMessage( HWnd_DLG, WM_DESTROY, 0, 0 );
	sprintf( Text2Save, "100%%\t\t%5.3f Seg.", toc );
	SetWindowText( HWnd_Text, Text2Save );
	SendMessage( Hprogress_SAVE , PBM_SETPOS , (WPARAM)100, 0 );

	LoadString( INSTANCIA_GLOBAL, ID_SAVE_WANT_OPEN_FILE, CharMsg, 255 );
	sprintf( Text2Save, CharMsg, TFile );


	HWFath = VENTANA_PADRE;
    IF InVista THEN
       //EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;

	IF MessageBox( HWFath, Text2Save, " ¿ ? ", MB_ICONQUESTION | MB_YESNO )==IDYES THEN
		ShellExecute( NULL, "open", TFile, NULL, NULL, 3 );
	ENDIF;
    EnableWindow( VENTANA_PADRE, TRUE );









return TRUE;
}


////////////////////////////////////////////////////////////////////////////////

//BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
BOOL CALLBACK Dlg_Proc_PRUEBAS(HWND hDlg, UINT  msg, WPARAM wParam, LPARAM lParam){
	HWnd_DLG = hDlg;

	IF FinishSaveDLG THEN
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


		HWnd_Text = CreateWindowEx( 0, "STATIC", " ", WS_CHILD | WS_VISIBLE,
									1, 1, 300, 20, hDlg, NULL, INSTANCIA_GLOBAL, NULL );

		#define PBS_SMOOTH2	3
		Hprogress_SAVE = CreateWindowEx( WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_TOOLWINDOW,
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
		SendMessage( Hprogress_SAVE , PBM_SETRANGE, 0 , MAKELPARAM(0,100) );
		SendMessage( Hprogress_SAVE , PBM_SETPOS , (WPARAM)0 , 0 );
		SendMessage( Hprogress_SAVE , PBM_SETBKCOLOR , 0 ,  RGB( 200 , 200 , 200 ) );
		SendMessage( Hprogress_SAVE , PBM_SETBARCOLOR , 0 , RGB( 0 , 128 , 255 ) );


		ShowWindow( hDlg, 1 );
		InvalidateRect( hDlg, NULL, TRUE );

	ENDIF;

	IF msg==WM_CLOSE || msg==WM_DESTROY THEN
		EndDialog( hDlg, TRUE );
	ENDIF;

return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadSaving( LPVOID pv=NULL ){
	HWND HWFath = VENTANA_PADRE;
    EnableWindow( HWInVista, TRUE );

    IF InVista THEN
       //EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;

    DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoSaving), HWFath, Dlg_Proc_PRUEBAS );

    EnableWindow( VENTANA_PADRE, TRUE );
	return 0;
}
