char Text2F_BU[256];
/////////////////////////
BOOL MAKE_FILE_BACK_UP( void ){

HWND HWFath = VENTANA_PADRE;
IF InGuiSave THEN
   HWFath = HWGuiSave;
ENDIF;

IF SaveFileAs( Text2F_BU, HWFath, 1 )==0 THEN
    return FALSE;
ENDIF;


DeleteFileA( Text2F_BU );
BYTE BuffBU[10*1024];
//  msgbox( Text2 );
// int NBytes = 0;
DWORD written = 0;
HANDLE HFile = CreateFile( Text2F_BU, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );//FILE_ATTRIBUTE_HIDDEN
DWORD LastError = GetLastError();

IF LastError==ERROR_SHARING_VIOLATION THEN
    // msgbox( "BOOL MAKE_BACK_UP( void )\nIF LastError!=0 THEN" );
	CloseHandle( HFile );
	return FALSE;
ENDIF;
IF LastError!=0 THEN
    sprintf( TextoGlobal, "Last Error = %i", (int)LastError );
    msgbox( TextoGlobal, " Error ", 16 );
    return FALSE;
ENDIF;



BuffBU[0] = 'B';
BuffBU[1] = 'U';
BuffBU[2] = 0;
BuffBU[3] = 'O';
BuffBU[4] = 'R';
BuffBU[5] = 1;
BuffBU[6] = 2;
BuffBU[7] = 3;


WriteFile( HFile, &BuffBU[0], 8, &written, NULL);
IF written!=8 THEN
    CloseHandle( HFile );
    msgbox( "BOOL MAKE_BACK_UP( void )\nIF written!=4 THEN" );
	return FALSE;
ENDIF;

//msgbox( Text2 );
// #include <dirent.h>



double FsRB[4];
FsRB[0] = FsReal;
WriteFile( HFile, &FsRB[0], sizeof(double), &written, NULL);
IF written!=sizeof(double) THEN
    CloseHandle( HFile );
    msgbox( "BOOL MAKE_BACK_UP( void )\nIF written!=4 THEN" );
	return FALSE;
ENDIF;





BuffBU[0] = LOBYTE( DTime );
BuffBU[1] = HIBYTE( DTime );

BuffBU[2] = LOBYTE( Fs );
BuffBU[3] = HIBYTE( Fs );

BuffBU[4] = GStyle;
BuffBU[5] = (BYTE)ActGStyle;


BuffBU[6] = (BYTE)OnTop;
BuffBU[7] = (BYTE)LineWidth;

BuffBU[8] = (BYTE)ComPort;
BuffBU[9] = (BYTE)EnAllDCursor;

BuffBU[10] = (BYTE)EnDataCursor[0];
BuffBU[11] = (BYTE)EnDataCursor[1];
BuffBU[12] = (BYTE)EnDataCursor[2];
BuffBU[13] = (BYTE)EnDataCursor[3];


BuffBU[14] = (BYTE)CurTs;

BuffBU[15] = (BYTE)InvGrid;
BuffBU[16] = (BYTE)SetTransparent;



BuffBU[17] = LineColors[0].rgbRed ;
BuffBU[18] = LineColors[0].rgbGreen;
BuffBU[19] = LineColors[0].rgbBlue;


BuffBU[20] = LineColors[1].rgbRed ;
BuffBU[21] = LineColors[1].rgbGreen;
BuffBU[22] = LineColors[1].rgbBlue;



BuffBU[23] = LineColors[2].rgbRed ;
BuffBU[24] = LineColors[2].rgbGreen;
BuffBU[25] = LineColors[2].rgbBlue;


BuffBU[26] = LineColors[3].rgbRed ;
BuffBU[27] = LineColors[3].rgbGreen;
BuffBU[28] = LineColors[3].rgbBlue;



BuffBU[29] = (BYTE)DivGraph;



// 30 - 61
memcpy( (void*)&BuffBU[30], &Volt_In_Out[0], 4*sizeof(double) );




BuffBU[64] = (BYTE)FShowInVista;
BuffBU[65] = LOBYTE( Divisor );
BuffBU[66] = HIBYTE( Divisor );




WriteFile( HFile, &BuffBU[0], 1024, &written, NULL);
IF written!=1024 THEN
    CloseHandle( HFile );
    msgbox( "BOOL MAKE_BACK_UP( void )\nIF written!=4 THEN" );
	return FALSE;
ENDIF;




DWORD WriNB = 0;
WriNB = (int)((MaxBuffs+32)*sizeof(short));
WriNB = (int)((DTime*FsReal + 1)*sizeof(short));

//*/
WriteFile( HFile, &BuffData[0].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
	return FALSE;
ENDIF;
//*/
WriteFile( HFile, &BuffData[1].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
	return FALSE;
ENDIF;
//*/
WriteFile( HFile, &BuffData[2].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
	return FALSE;
ENDIF;
//*/
WriteFile( HFile, &BuffData[3].USData[0], WriNB, &written, NULL);
IF written!=WriNB THEN
    CloseHandle( HFile );
	return FALSE;
ENDIF;


//sprintf( TextoGlobal, "%i\n%i", WriNB, LBuff );
//msgbox( TextoGlobal );
//free( Buff );
//  msgbox( "BOOL MAKE_BACK_UP( void )\n" );




//sprintf( TextoGlobal, "%i", sizeof(double) );
//msgbox( TextoGlobal );
CloseHandle( HFile );
return TRUE;
}
