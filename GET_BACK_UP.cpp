BOOL GET_BACK_UP( void ){
// return FALSE;
BYTE BuffBU[10*1024];
char Text2[512];
char CharUserName[256];
DWORD DWVal = 255;
GetUserName( CharUserName, (PDWORD)&DWVal );
char CharFolder[256];
LoadString( INSTANCIA_GLOBAL, ID_STRING_FOLDER2, CharFolder, 255);
LoadString( INSTANCIA_GLOBAL, ID_STRING_RESFILE, (char*)BuffBU, 255 );

sprintf( Text2, CharFolder, CharUserName );



sprintf( Text2, "%s%s", Fold_Adm, (char*)BuffBU );







/// LoadString( INSTANCIA_GLOBAL, ID_STRING_FOLDER, CharFolder, 255);
/// sprintf( Text2, CharFolder, CharUserName );

// int NBytes = 0;
DWORD written = 0;
HANDLE HFile = CreateFile( Text2, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );//FILE_ATTRIBUTE_HIDDEN
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


double DValues[16];
ZeroMemory( &DValues[0], 16*sizeof(double) );
memcpy( (void*)&DValues[0], &BuffBU[67], 4*sizeof(double) );
B_Val = DValues[0];
D_Val = DValues[1];
B_Val_Min = DValues[2];
D_Val_Min = DValues[3];



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


Pltrs[0].SetMaxYLim( Max_Volt );
Pltrs[1].SetMaxYLim( Max_Volt );





FShowInVista = (BOOL)BuffBU[64];



Divisor = MAKEWORD( BuffBU[65], BuffBU[66] );




int WriNB = 0;
WriNB = (int)((MaxBuffs+32)*sizeof(short));

ReadFile( HFile, (PVOID)&BuffData[0].USData[0], WriNB, &written, NULL);
IF (int)written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 0", " Error ", 16 );
	return FALSE;
ENDIF;
//*/
ReadFile( HFile, (PVOID)&BuffData[1].USData[0], WriNB, &written, NULL);
IF (int)written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 1", " Error ", 16 );
	return FALSE;
ENDIF;
//*/
ReadFile( HFile, (PVOID)&BuffData[2].USData[0], WriNB, &written, NULL);
IF (int)written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 2", " Error ", 16 );
	return FALSE;
ENDIF;
//*/
ReadFile( HFile, (PVOID)&BuffData[3].USData[0], WriNB, &written, NULL);
IF (int)written!=WriNB THEN
    CloseHandle( HFile );
    //msgbox( "Chann 3", " Error ", 16 );
	return FALSE;
ENDIF;






IF OnTop THEN
   SetWindowPos( VENTANA_PADRE, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
ELSE
   SetWindowPos( VENTANA_PADRE, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
ENDIF;



//msgbox( Text2 );
CloseHandle( HFile );
return TRUE;
}
