BOOL GET_FILE_BACK_UP( char* FileIn=NULL ){

IF InConnect || Connected THEN
   return FALSE;
ENDIF;


IF FileIn==NULL THEN
   IF OpenFileAs( Text2F_BU, 1 )==0 THEN
      return FALSE;
   ENDIF;
ELSE
   strcpy( Text2F_BU, FileIn );
ENDIF;

char* TextTemp = (char*)malloc( 512 );
GetFileTitleA( (char*)&Text2F_BU[0], (char*)&TextTemp[0], 256 );
Pltrs[0].Text2ShowF( (char*)&TextTemp[0] );
Pltrs[1].Text2ShowF( (char*)&TextTemp[0] );
free( TextTemp );


BYTE BuffBU[1024];
DWORD written = 0;
HANDLE HFile = CreateFile( Text2F_BU, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );//FILE_ATTRIBUTE_HIDDEN
DWORD LastError = GetLastError();
IF LastError!=0 THEN
	CloseHandle( HFile );
	//msgbox( "BOOL GET_BACK_UP( void )\nIF LastError!=0 THEN" );
	return FALSE;
ENDIF;
////////////////
ReadFile( HFile, &BuffBU[0], 8, &written, NULL);
IF written!=8 THEN
    CloseHandle( HFile );
	return FALSE;
ENDIF;
////////////////
IF BuffBU[0]!='B' || BuffBU[1]!='U' ||
   BuffBU[2]!=0   || BuffBU[3]!='O' ||
   BuffBU[4]!='R' || BuffBU[5]!=1   ||
   BuffBU[6]!=2   || BuffBU[7]!=3        THEN

    CloseHandle( HFile );
	return FALSE;
ENDIF;
////////////////
double FsRB[4];
ReadFile( HFile, &FsRB[0], sizeof(double), &written, NULL);
IF written!=sizeof(double) THEN
    CloseHandle( HFile );
	return FALSE;
ENDIF;
FsReal = FsRB[0];



ReadFile( HFile, &BuffBU[0], 1024, &written, NULL);
IF written!=1024 THEN
    CloseHandle( HFile );
    //msgbox( "BOOL GET_BACK_UP( void )\nIF written!=48 THEN" );
	return FALSE;
ENDIF;



DTime = MAKEWORD( BuffBU[0], BuffBU[1] );
Fs    = MAKEWORD( BuffBU[2], BuffBU[3] );


GStyle = BuffBU[4];
ActGStyle = BuffBU[5];


OnTop = BuffBU[6];
LineWidth = BuffBU[7];

ComPort = BuffBU[8];
EnAllDCursor = BuffBU[9];

EnDataCursor[0] = BuffBU[10];
EnDataCursor[1] = BuffBU[11];
EnDataCursor[2] = BuffBU[12];
EnDataCursor[3] = BuffBU[13];

CurTs = BuffBU[14];


InvGrid = BuffBU[15];
SetTransparent = BuffBU[16];



LineColors[0].rgbRed = BuffBU[17];
LineColors[0].rgbGreen = BuffBU[18];
LineColors[0].rgbBlue = BuffBU[19];


LineColors[1].rgbRed = BuffBU[20];
LineColors[1].rgbGreen = BuffBU[21];
LineColors[1].rgbBlue = BuffBU[22];



LineColors[2].rgbRed = BuffBU[23];
LineColors[2].rgbGreen = BuffBU[24];
LineColors[2].rgbBlue = BuffBU[25];


LineColors[3].rgbRed = BuffBU[26];
LineColors[3].rgbGreen = BuffBU[27];
LineColors[3].rgbBlue = BuffBU[28];


DivGraph = (BOOL)BuffBU[29];



memcpy( (void*)&Volt_In_Out[0], &BuffBU[30], 4*sizeof(double) );
Max_Volt = 0;
FOR int i=0; i<4; i++ LOOP
    Max_Volt = max( Max_Volt, Volt_In_Out[i] );
ENDLOOP;
Max_Volt = ceil( Max_Volt );
BuffBU[62] = 0;









DWORD WriNB = 0;

WriNB = (int)((MaxBuffs+32)*sizeof(short));
WriNB = (int)((DTime*FsReal + 1)*sizeof(short));

ReadFile( HFile, (PVOID)&BuffData[0].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 0", " Error ", 16 );
	return FALSE;
ENDIF;
//*/
ReadFile( HFile, (PVOID)&BuffData[1].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 1", " Error ", 16 );
	return FALSE;
ENDIF;
//*/
ReadFile( HFile, (PVOID)&BuffData[2].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 2", " Error ", 16 );
	return FALSE;
ENDIF;
//*/
ReadFile( HFile, (PVOID)&BuffData[3].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 3", " Error ", 16 );
	return FALSE;
ENDIF;
//msgbox( Text2 );
CloseHandle( HFile );
Pltrs[0].SetVisible( FALSE );
Pltrs[1].SetVisible( FALSE );

/*
Pltrs[0].SetGridStyle( GStyle );
Pltrs[0].ActGridStyle( ActGStyle );
Pltrs[0].InvGridStyle( InvGrid );
//*/



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


SendMessage( HWCOMPort, CB_SETCURSEL, ComPort-1, 0 );
SendMessage( HWTs, CB_SETCURSEL, CurTs, CurTs );

char TextoBU[256];
sprintf( TextoBU, "%i", DTime );
SetWindowText( HWTime, TextoBU );


FOR int i=0; i<4; i++ LOOP
    //EnDataCursor[i] = TRUE;
    ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
    ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
    CheckMenuItem( MENUGLOBAL, ID_DATA_CURSOR0+i, 8*int(EnDataCursor[i]) );
ENDLOOP;

IF OnTop THEN
   SetWindowPos( VENTANA_PADRE, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
ENDIF;


Pltrs[0].SetMaxYLim( Max_Volt );
Pltrs[1].SetMaxYLim( Max_Volt );

Pltrs[0].SetGridStyle( GStyle );
Pltrs[1].SetGridStyle( GStyle );

Pltrs[0].InvGridStyle( InvGrid );
Pltrs[1].InvGridStyle( InvGrid );
Pltrs[0].ActGridStyle( ActGStyle );
Pltrs[1].ActGridStyle( ActGStyle );

Pltrs[0].SetDoubleBuff( FALSE );
Pltrs[1].SetDoubleBuff( FALSE );
maximizar( VENTANA_PADRE );
Pltrs[0].SetDoubleBuff( TRUE );
Pltrs[1].SetDoubleBuff( TRUE );


Pltrs[0].SetVisible( TRUE );
IF PltrNDiv!=0 THEN
   Pltrs[1].SetVisible( TRUE );
ENDIF;





FShowInVista = (BOOL)BuffBU[64];
Divisor = MAKEWORD( BuffBU[65], BuffBU[66] );








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
    SendMessage( HWDataCur[i], BM_SETCHECK, (WPARAM)(EnDataCursor[i]), 0 );
ENDLOOP;

maximizar( VENTANA_PADRE );

IF OnTop THEN
   SetWindowPos( VENTANA_PADRE, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
ELSE
   SetWindowPos( VENTANA_PADRE, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
ENDIF;

return TRUE;
}
