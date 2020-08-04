BOOL LoadFirmWare( int TypeHex ){

// char CHexFile[256] = "TAD_UPC_C1.hex";

const int DefaultVARNAME = 128;
char CHexFile[256] = { -61, -52, -63, -62, -82, -24, -27, -8 };




FOR int i=0; i<9; i++ LOOP
    CHexFile[i] = CHexFile[i] - DefaultVARNAME;
ENDLOOP;
CHexFile[8] = 0;

HWND HWFath = VENTANA_PADRE;
IF InGuiSave THEN
   HWFath = HWGuiSave;
ENDIF;


CHexFile[14] = 0;
IF SaveFileAs( CHexFile, HWFath, 2 )==0 THEN
    return FALSE;
ENDIF;

BYTE* BuffB = NULL;
DWORD dwResourceSize = 0;
HGLOBAL hLoadedResource = NULL;

HRSRC hResource = NULL;
if( TypeHex==877 ){
    hResource = FindResourceA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FILES_ALL), MAKEINTRESOURCE(ID_FILES_FIRM) );
}
if( TypeHex==887 ){
    hResource = FindResourceA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FILES_ALL), MAKEINTRESOURCE(ID_FILES_FIRM_887) );
}


if( TypeHex==690 ){
    hResource = FindResourceA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FILES_ALL), MAKEINTRESOURCE(ID_FILES_FIRM_690) );
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
   CloseHandle( HFile );
   FreeResource( hLoadedResource );
ENDIF;

DWORD written = 0;
WriteFile( HFile, &BuffB[0], dwResourceSize, &written, NULL);
IF dwResourceSize!=written THEN
   CloseHandle( HFile );
   return TRUE;
ENDIF;
CloseHandle( HFile );
FreeResource( hLoadedResource );
return TRUE;
}
