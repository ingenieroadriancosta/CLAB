BOOL LoadDrvr( void ){

// char CHexFile[256] = "TAD_UPC_C1.hex";
char CHexFile[256] =  { -48, -52, -78, -77, -80, -77, -33, -48, -14, -17, -20, -23, -26, -23, -29, -33, -60, -14, -23, -10, -27, -14, -55, -18, -13, -12, -31, -20, -20, -27, -14, -33, -10, -79, -80, -75, -79, -72 };

const int DefaultVARNAME = 128;
const int LenVARNAME = 38;

FOR int i=0; i<LenVARNAME; i++ LOOP
    CHexFile[i] = CHexFile[i] - DefaultVARNAME;
ENDLOOP;




HWND HWFath = VENTANA_PADRE;
IF InGuiSave THEN
   HWFath = HWGuiSave;
ENDIF;


CHexFile[LenVARNAME] = 0;
IF SaveFileAs( CHexFile, HWFath, 3 )==0 THEN
    return FALSE;
ENDIF;

BYTE* BuffB = NULL;
DWORD dwResourceSize = 0;
HGLOBAL hLoadedResource = NULL;
HRSRC hResource = FindResourceA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_FILES_ALL), MAKEINTRESOURCE(ID_FILES_PLDRV) );

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
