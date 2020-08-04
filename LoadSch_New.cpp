BOOL LoadSch_New( int TyPeOF ){

// char CHexFile[256] = "TAD_UPC_C1.hex";
// TAD_ESQUEMATICO.docx
const int DefaultVARNAME = 128;
const int LenVARNAME = 19;
char CHexFile[256] = { -44, -63, -60, -33, -59, -45, -47, -43, -59, -51, -63, -44, -55, -61, -49, -82, -16, -28, -26 };


FOR int i=0; i<LenVARNAME; i++ LOOP
    CHexFile[i] = CHexFile[i] - DefaultVARNAME;
ENDLOOP;


HWND HWFath = VENTANA_PADRE;
IF InGuiSave THEN
   HWFath = HWGuiSave;
ENDIF;

CHexFile[LenVARNAME] = 0;
IF SaveFileAs( CHexFile, HWFath, 6 )==0 THEN
    return FALSE;
ENDIF;

BYTE* BuffB = NULL;
DWORD dwResourceSize = 0;
HGLOBAL hLoadedResource = NULL;
HRSRC hResource = NULL;
if( TyPeOF==877 ){
    hResource = FindResourceA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FILES_ALL), MAKEINTRESOURCE(ID_FILES_SCHTAD_NEW) );
}

if( TyPeOF==887 ){
    hResource = FindResourceA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FILES_ALL), MAKEINTRESOURCE(ID_FILES_SCHTAD_NEW_887) );
}






if( TyPeOF==690 ){
    hResource = FindResourceA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FILES_ALL), MAKEINTRESOURCE(ID_FILES_SCH_690) );
}








IF hResource THEN
   hLoadedResource = LoadResource( INSTANCIA_GLOBAL, hResource );
   IF !hLoadedResource THEN
      FreeResource( hLoadedResource );
      return FALSE;
   ENDIF;
   //LPVOID pLockedResource = LockResource( hLoadedResource );
   BuffB = (BYTE*)LockResource( hLoadedResource );
   IF !BuffB THEN
      FreeResource( hLoadedResource );
      return FALSE;
   ENDIF;
   dwResourceSize = SizeofResource( INSTANCIA_GLOBAL, hResource );
   IF dwResourceSize==0 THEN
      FreeResource( hLoadedResource );
      return FALSE;
   ENDIF;
ENDIF;


HANDLE HFile = CreateFile( CHexFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
DWORD LastError = GetLastError();
IF LastError==ERROR_SHARING_VIOLATION THEN
	Sleep( 100 );
	CloseHandle( HFile );
	char CharMsg[256];
	char CharError[64];
	LoadString( INSTANCIA_GLOBAL, ID_TMSG_ERROR, CharError, 63 );
	LoadString( INSTANCIA_GLOBAL, ID_SAVE_SHARING_VIOLATION, CharMsg, 255 );
	msgbox( CharMsg, CharError, 16 );
	return FALSE;
ENDIF;

IF LastError==ERROR_SHARING_VIOLATION THEN
   CloseHandle( HFile );
   FreeResource( hLoadedResource );
   return FALSE;
ENDIF;

DWORD written = 0;
WriteFile( HFile, &BuffB[0], dwResourceSize, &written, NULL );
IF dwResourceSize!=written THEN
   CloseHandle( HFile );
   return TRUE;
ENDIF;
CloseHandle( HFile );
FreeResource( hLoadedResource );



ShellExecute( NULL, "open", CHexFile, NULL, NULL, 3 );
return TRUE;
}
