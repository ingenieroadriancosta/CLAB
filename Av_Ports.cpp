#define MLenAVP 256
BYTE PortAV[MLenAVP];
char ValuePorts[MLenAVP][MLenAVP];
char NamePorts[MLenAVP][MLenAVP];
//
int Av_Ports( void ){
	memset( PortAV, 0, MLenAVP );
	memset( &ValuePorts[0][0], 0, MLenAVP*MLenAVP );
	memset( &NamePorts[0][0], 0, MLenAVP*MLenAVP );

	FOR int i=0; i<MLenAVP; i++ LOOP
		ValuePorts[i][0] = 0;
		NamePorts[i][0] = 0;
	ENDLOOP;
	//const char DirReg[32] = "HARDWARE\\DEVICEMAP\\SERIALCOMM";

	const int DefaultDirReg = 128;
    const int LenDirReg = 29;
    char DirReg[64] = { -56, -63, -46, -60, -41, -63, -46, -59, -36, -60, -59,
                        -42, -55, -61, -59, -51, -63, -48, -36, -45, -59, -46,
                        -55, -63, -52, -61, -49, -51, -51 };
    FOR int i=0; i<LenDirReg; i++ LOOP
        DirReg[i] = DirReg[i] - DefaultDirReg;
    ENDLOOP;




	// \Device\ProlificSerial2
	HKEY  hKey = NULL;
	char lpValueName[MLenAVP];
	char lpPortName[MLenAVP];
	DWORD DW = 0;
	DWORD cbValueName = sizeof(lpValueName);
	DWORD cbPortName = sizeof(lpPortName);
	DWORD dwError = 0;

	IF (dwError=RegOpenKeyEx( HKEY_LOCAL_MACHINE, DirReg, 0, KEY_READ, &hKey )) THEN
		return -2;
	ENDIF;

	char TNum[MLenAVP];
	int Num = 0;
	int NAv = 0;
	FOR int i=0; i<MLenAVP; i++ LOOP

		cbValueName = sizeof(lpValueName);
		cbPortName = sizeof(lpPortName);

		memset( lpValueName, 0, cbValueName );
		memset( lpPortName, 0, cbPortName );

		dwError = RegEnumValueA( hKey, i, lpValueName, &cbValueName, NULL, &DW, (LPBYTE)lpPortName, &cbPortName );
		IF dwError==ERROR_NO_MORE_ITEMS THEN
			break;
		ELSIF DW==REG_SZ THEN
			int SLen = strlen( lpPortName );
			FOR int n=0; n<SLen; n++ LOOP
				TNum[n] = lpPortName[3+n];
			ENDLOOP;

			Num = atoi( TNum );
			PortAV[NAv] = (BYTE)Num;
			SLen = strlen( lpValueName );
			memcpy( &ValuePorts[NAv][0], lpValueName, SLen );

			SLen = strlen( lpPortName );
			memcpy( &NamePorts[NAv][0], lpPortName, SLen );
			/*
			//lpValueName[ SLen - 1 ] = 0;
			//sprintf( TextoGlobal, "F\n\n%i\n\nPortName:%s\n\nValueName:%s\n\nDW\n%i", i, lpPortName, lpValueName, DW );
			IF strcmp( "\\Device\\ProlificSerial", lpValueName )==0 THEN
				msgbox( TextoGlobal );
			ENDIF;
			//*/
			NAv++;
		ENDIF;
	ENDLOOP;
	RegCloseKey(hKey);


	/*
	TextoGlobal[0] = 0;
	FOR int i=0; i<256; i++ LOOP
		IF ValuePorts[i][0]!=0 THEN
			sprintf( lpValueName, "[%s\t%s]\n", ValuePorts[i], NamePorts[i] );
			strcat( TextoGlobal, lpValueName );
		ENDIF;
	ENDLOOP;
	sprintf( lpValueName, "\nNPorts:\n%i\n", NAv );
	strcat( TextoGlobal, lpValueName );
	msgbox( TextoGlobal );
	//*/
	return NAv;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL ValidPort( const char* TIn ){
const int DefaultProlificSerial = 128;
const int LenProlificSerial = 22;
char ProlificSerial[23] = { -36, -60, -27, -10, -23, -29, -27, -36, -48, -14,
                            -17, -20, -23, -26, -23, -29, -45, -27, -14, -23,
                            -31, -20 };


FOR int i=0; i<LenProlificSerial; i++ LOOP
    ProlificSerial[i] = ProlificSerial[i] - DefaultProlificSerial;
ENDLOOP;





// msgbox( ProlificSerial );




int SLen = strlen( TIn );
char Ch2[SLen+1];
memcpy( Ch2, TIn, SLen );
Ch2[ SLen - 1 ] = 0;
IF strcmp( ProlificSerial, Ch2 )==0 THEN
	return TRUE;
ENDIF;







/////
const int DefaultVSerial = 128;
const int LenVSerial = 15;
char VSerial[16] = { -36, -60, -27, -10, -23, -29, -27, -36, -42, -45, -27, -14, -23, -31, -20 };
FOR int i=0; i<LenVSerial; i++ LOOP
    VSerial[i] = VSerial[i] - DefaultVSerial;
ENDLOOP;


int SLenV = strlen( TIn );
char Ch2V[SLen+1];
memcpy( Ch2V, TIn, SLenV );
Ch2[ SLen - 2 ] = 0;
IF strcmp( VSerial, Ch2 )==0 THEN
	return TRUE;
ENDIF;
/////
















return FALSE;
}
