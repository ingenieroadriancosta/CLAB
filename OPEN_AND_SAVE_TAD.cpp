//char FileNameAux[256] = "__CSV.csv";


inline bool OpenFileAs( char *FileName, int Type=0, int DirOption=1 ){
char FileNameAux[256];
sprintf( FileNameAux, "%s", FileName );
OPENFILENAME  openFileDialogfunction = {0};
ZeroMemory(&openFileDialogfunction, sizeof(openFileDialogfunction));
openFileDialogfunction.lStructSize= sizeof(openFileDialogfunction);
openFileDialogfunction.hwndOwner = VENTANA_PADRE;

EnableWindow( HWInVista, FALSE );

openFileDialogfunction.nFilterIndex=3;

char OTitle[256];
LoadString( INSTANCIA_GLOBAL, ID_OPENTITTLE, OTitle, 255);
openFileDialogfunction.lpstrTitle=OTitle;


openFileDialogfunction.hInstance = INSTANCIA_GLOBAL;
//  openFileDialogfunction.lpstrInitialDir = BeforeDir;


IF Type==0 THEN
   openFileDialogfunction.lpstrFilter = "CSV Files (*.csv*)\0*.csv\0\0";
ELSIF Type==1 THEN
   openFileDialogfunction.lpstrFilter = "TC1 Files (*.tc1*)\0*.tc1\0\0";
ENDIF;



//"BMP Files (*.bmp*)\0*.bmp\0JPG Files (*.jpg*)\0*.jpg\0All Files(*.*)\0*.*\0\0";
openFileDialogfunction.lpstrFile = FileNameAux;
openFileDialogfunction.nMaxFile = MAX_PATH;
openFileDialogfunction.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ;
openFileDialogfunction.lpstrDefExt = "";
if( !GetOpenFileName(&openFileDialogfunction) ){
   EnableWindow( HWInVista, TRUE );
   return false;
}
EnableWindow( HWInVista, TRUE );
sprintf( FileName, "%s", FileNameAux );
return true;
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
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int SaveFileAs( char *FileName, HWND HWnd_F, int Type=0 ){
    char FileNameAux[256];
    sprintf( FileNameAux, "%s", FileName );
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = HWnd_F;
    ofn.nFilterIndex = 0;
    ofn.hInstance = INSTANCIA_GLOBAL;
    char STitle[256];
    LoadString( INSTANCIA_GLOBAL, ID_SAVETITTLE, STitle, 255);
    ofn.lpstrTitle = STitle;

    ofn.lpstrInitialDir= NULL;


    IF Type==0 THEN
       ofn.lpstrFilter = "CSV Files (*.csv*)\0*.csv\0\0";
       ofn.lpstrDefExt = ".csv";
    ELSIF Type==1 THEN
       ofn.lpstrFilter = "TC1 Files (*.tc1*)\0*.tc1\0\0";
       ofn.lpstrDefExt = ".tc1";
    ELSIF Type==2 THEN
       ofn.lpstrFilter = "HEX Files (*.hex*)\0*.hex\0\0";
       ofn.lpstrDefExt = ".hex";
    ELSIF Type==3 THEN
       ofn.lpstrFilter = "EXE Files (*.exe*)\0*.exe\0\0";
       ofn.lpstrDefExt = ".exe";
    ELSIF Type==4 THEN
       ofn.lpstrFilter = "DOCX Files (*.docx*)\0*.docx\0\0";
       ofn.lpstrDefExt = ".docx";
    ELSIF Type==5 THEN
       ofn.lpstrFilter = "BMP Files (*.bmp*)\0*.bmp\0\0";
       ofn.lpstrDefExt = ".bmp";
    ELSIF Type==6 THEN
       ofn.lpstrFilter = "PDF Files (*.pdf*)\0*.pdf\0\0";
       ofn.lpstrDefExt = ".pdf";
    ELSIF Type==7 THEN
       ofn.lpstrFilter = "MAT Files (*.mat*)\0*.mat\0\0";
       ofn.lpstrDefExt = ".mat";
    ENDIF;



    ofn.lpstrFile = (LPSTR)&FileNameAux[0];
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT ;

    EnableWindow( HWInVista, FALSE );

    if( !GetSaveFileNameA(&ofn) ){ EnableWindow( HWInVista, TRUE ); return 0; }
    sprintf( FileName, "%s", FileNameAux );
    EnableWindow( HWInVista, TRUE );
return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI ThreadColor( LPVOID pv=NULL ){
LONG OLCLK = clock();
LONG LCLK = clock();
LONG TOC_C = LCLK - OLCLK;

HWND HWFath = VENTANA_PADRE;
IF HWInVista THEN
   HWFath = HWInVista;
ENDIF;
HWND HWCOLOR = FindWindow( NULL, "COLOR" );
BOOL ISWFATH = (GetParent( HWCOLOR )==HWFath);
WHILE( ISWFATH==FALSE && TOC_C<2000 )
    HWCOLOR = FindWindow( NULL, "Color" );
    ISWFATH = (GetParent( HWCOLOR )==HWFath);
    LCLK = clock();
    TOC_C = LCLK - OLCLK;
ENDLOOP;
OLCLK = clock();
LCLK = clock();
TOC_C = LCLK - OLCLK;
ISWFATH = IsWindowVisible( HWCOLOR );
WHILE( ISWFATH==FALSE && TOC_C<2000 )
    ISWFATH = IsWindowVisible( HWCOLOR );
    LCLK = clock();
    TOC_C = LCLK - OLCLK;
ENDLOOP;


//Sleep( 100 );
int WCOL = 0;
int HCOL = 0;
WindowSize( HWCOLOR, &WCOL, &HCOL );


int CXSC = GetSystemMetrics( SM_CXSCREEN );
int CYSC = GetSystemMetrics( SM_CYSCREEN );

CXSC = (WCOL+CXSC)/2 - WCOL;
CYSC = (HCOL+CYSC)/2 - HCOL;
MoveWindow( HWCOLOR, CXSC, CYSC, WCOL + 8, HCOL + 32, TRUE  );

// MessageBox( HWCOLOR, " Ok ", " ThreadColor ", 0 );
return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RGBQUAD ColorSel;
COLORREF CREF[32];
char TexCC[256];
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL ChosseRGBColor( RGBQUAD RGBINIT ){

CHOOSECOLORA ColCh;
ZeroMemory ( &ColCh, sizeof (ColCh) );
ColCh.lStructSize = sizeof(CHOOSECOLOR);


HWND HWFath = VENTANA_PADRE;
IF HWInVista THEN
   EnableWindow( VENTANA_PADRE, FALSE );
   HWFath = HWInVista;
ENDIF;
ColCh.hwndOwner = HWFath;



ColCh.lpCustColors = (LPDWORD) TexCC;
ColCh.rgbResult = RGB( RGBINIT.rgbRed, RGBINIT.rgbGreen, RGBINIT.rgbBlue );
ColCh.Flags = CC_FULLOPEN | CC_RGBINIT;
FOR int i=0; i<8; i++ LOOP
    CREF[i] = RGB( InitLineStyle[i].rgbRed , InitLineStyle[i].rgbGreen, InitLineStyle[i].rgbBlue );
ENDLOOP;
ColCh.lpCustColors = (COLORREF*)(&CREF[0]);



DWORD IdTh = 0;
CreateThread( NULL, 0, ThreadColor, NULL, 0, &IdTh );

IF ChooseColor(&ColCh)==TRUE THEN
   ColorSel.rgbRed   = GetRValue(ColCh.rgbResult);
   ColorSel.rgbGreen = GetGValue(ColCh.rgbResult);
   ColorSel.rgbBlue  = GetBValue(ColCh.rgbResult);
   EnableWindow( VENTANA_PADRE, TRUE );
   return TRUE;
ENDIF;
EnableWindow( VENTANA_PADRE, TRUE );
return FALSE;
}
//*/
