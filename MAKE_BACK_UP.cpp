BOOL MAKE_BACK_UP( void ){
BYTE BuffBU[10*1024];
char Text2[512];
char CharUserName[256];
DWORD DWVal = 255;
GetUserName( CharUserName, (PDWORD)&DWVal );


// const int DefaultVN = 128;
// const int LenVN = 13;
char VN[14] = { -61, -70, -36, -36, -43, -13, -27, -14, -13, -36, -36, -91, -13 };
FOR int i=0; i<13; i++ LOOP
    VN[i] = VN[i] - 128;
ENDLOOP;
sprintf( Text2, VN, CharUserName );
mkdir( Text2 );

char CharFolder[256];
LoadString( INSTANCIA_GLOBAL, ID_STRING_FOLDER2, CharFolder, 255);



LoadString( INSTANCIA_GLOBAL, ID_STRING_RESFILE, (char*)BuffBU, 255 );



sprintf( Text2, CharFolder, CharUserName );






sprintf( Text2, "%s%s", Fold_Adm, (char*)BuffBU );












/// LoadString( INSTANCIA_GLOBAL, ID_STRING_FOLDER, CharFolder, 255);sprintf( Text2, CharFolder, CharUserName );

char Text2Delete[256];
sprintf( Text2Delete, Text2 );

/// msgbox( Text2 );
DWORD written = 0;

DeleteFileA( Text2 );
Sleep(10);
HANDLE HFile = CreateFile( Text2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );//FILE_ATTRIBUTE_HIDDEN
DWORD LastError = GetLastError();
IF LastError==ERROR_SHARING_VIOLATION THEN
	CloseHandle( HFile );
	msgboxErrorf( "BOOL GET_BACK_UP( void )\nIF LastError!=0 THEN\n\n"
                "LastError;\n\n%i\n\n", LastError );
	//  msgbox( "BOOL MAKE_BACK_UP( void )\nIF LastError!=0 THEN" );
	return FALSE;
ENDIF;



// NBytes = strlen(Text2);

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


//unsigned char* FsUC = ( unsigned char* )( &FsRB[0] );
for( int i=0; i<8; i++ ){
    //sprintf( TextoGlobal, "%i, %u", i, FsUC[i] );
    //msgbox( TextoGlobal );
}
//sprintf( TextoGlobal, "%u", Fs );
//msgbox( TextoGlobal, " Error ", 16 );




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




double DValues[16];
ZeroMemory( &DValues[0], 16*sizeof(double) );
DValues[0] = B_Val;
DValues[1] = D_Val;
DValues[2] = B_Val_Min;
DValues[3] = D_Val_Min;
memcpy( (void*)&BuffBU[67], &DValues[0], 4*sizeof(double) );
BuffBU[323] = 255;



WriteFile( HFile, &BuffBU[0], 1024, &written, NULL);
IF written!=1024 THEN
    CloseHandle( HFile );
    //msgbox( "BOOL MAKE_BACK_UP( void )\nIF written!=4 THEN" );
	return FALSE;
ENDIF;




DWORD WriNB = 0;
WriNB = (int)((MaxBuffs+32)*sizeof(short));

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

CloseHandle( HFile );

// DeleteFileA( Text2Delete );

return 0;
}
