BOOL    LOADS( void ){
/////
HCursorG = LoadCursor( NULL, IDC_ARROW );
// HCursorG = LoadCursorA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_PIC_CURSOR) );
LCursors();
/////


FOR int i=0; i<8; i++ LOOP
    ZeroMemory( &DevTad[i][0], 127 );
    LoadString( INSTANCIA_GLOBAL, ID_STRING_TAD_DEV + i, &DevTad[i][0], 127 );
ENDLOOP;
// LoadString( INSTANCIA_GLOBAL, ID_STRING_TAD_DEV_690, DevTadNew, 127 );




Connected = FALSE;


CXSCREEN = GetSystemMetrics( SM_CXSCREEN );
CYSCREEN = GetSystemMetrics( SM_CYSCREEN );

CXFULLSCREEN = GetSystemMetrics( SM_CXFULLSCREEN );
CYFULLSCREEN = GetSystemMetrics( SM_CYFULLSCREEN );

CYMENU = GetSystemMetrics( SM_CYMENU );
//sprintf( TextoGlobal, "%i", CYMENU );
//msgbox( TextoGlobal );


char LoadText0[256];
char LoadText1[256];
LoadString( INSTANCIA_GLOBAL, ID_WCLASS, szClassName, 255);
LoadString( INSTANCIA_GLOBAL, ID_WTITLE, WTitle, 255);

LoadString( INSTANCIA_GLOBAL, ID_DATACURSOR_CLASS, ClassDataCursor, 255);
LoadString( INSTANCIA_GLOBAL, ID_DATACURSOR_INFO_CLASS, ClassDataCursorInfo, 255);
LoadString( INSTANCIA_GLOBAL, ID_PANEL_CLASS, ClassPanel, 255);


LoadString( INSTANCIA_GLOBAL, ID_STRING_Creado_Por,   CreadoPor, 31 );
LoadString( INSTANCIA_GLOBAL, ID_STRING_Adrian_Costa, AdrianCosta, 15 );




HB_Fondo = loadResImage( ID_PIC_FONDO,
                        MAKEINTRESOURCE(ID_PIC_JPG) );

IF !HB_Fondo THEN
    LoadString( INSTANCIA_GLOBAL, ID_LERROR0, LoadText0, 255);
    LoadString( INSTANCIA_GLOBAL, ID_TMSG_ERROR, LoadText1, 255);
    msgbox( LoadText0, LoadText1, MB_ICONERROR );
    exit( -1 );
ENDIF;

GetObject( HB_Fondo, sizeof(BITMAP), (LPSTR)&B_Fondo );




HB_FondoPanel = loadResImage( ID_PIC_FONDO_P,
                              MAKEINTRESOURCE(ID_PIC_JPG) );
GetObject( HB_FondoPanel, sizeof(BITMAP), (LPSTR)&B_FondoPanel );


int WMax = B_FondoPanel.bmWidth;
int HMax = B_FondoPanel.bmHeight;
RGBQUAD* RgbQ = (RGBQUAD*)malloc( 4 * WMax * HMax + 1024 );
GetBitmapBits( HB_FondoPanel, 4*WMax*HMax, &RgbQ[0] );


#define CDefa 254
#define CDefaFon 0.93
FOR int y=0; y<HMax; y++ LOOP
    FOR int x=0; x<WMax; x++ LOOP
        int ToIndex = x + WMax*y;
        /*
        IF RgbQ[ToIndex].rgbRed>CDefa &&
                      RgbQ[ToIndex].rgbGreen>CDefa &&
                             RgbQ[ToIndex].rgbBlue>CDefa THEN
          //*/
           RgbQ[ToIndex].rgbRed = (BYTE)( CDefaFon * RgbQ[ToIndex].rgbRed );
           RgbQ[ToIndex].rgbGreen = (BYTE)( CDefaFon * RgbQ[ToIndex].rgbGreen );
           RgbQ[ToIndex].rgbBlue = (BYTE)( CDefaFon * RgbQ[ToIndex].rgbBlue );
        // ENDIF;
    ENDLOOP;
ENDLOOP;
SetBitmapBits( HB_FondoPanel, 4*WMax*HMax, &RgbQ[0] );
free( RgbQ );



return TRUE;
}
