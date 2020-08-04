BOOL SHALLL( BOOL );
char Text2SBMP[256];
BOOL Replace;
BOOL SAVE_BMP( void ){

HWND HWFath = VENTANA_PADRE;
IF InGuiSave THEN
   HWFath = HWGuiSave;
ENDIF;
IF SaveFileAs( Text2SBMP, HWFath, 5 )==0 THEN
    return FALSE;
ENDIF;
ShowWindow( VENTANA_PADRE, 3 );
Sleep( 50 );
Replace = FALSE;
////////////
SHALLL( FALSE );
////////////
BOOL DivAct = DivGraph;
IF DivAct THEN
   Replace = TRUE;
   SendMessage( VENTANA_PADRE, WM_COMMAND, ID_DIV_GRAPH, 0 );
   Sleep( 100 );
   while( Replace==TRUE ){Sleep( 100 );}
   Sleep( 1000 );
ENDIF;
///
int WPicOr = Pltrs[0].GetConWidth() - 1;
int HPicOr = Pltrs[0].GetConHeight() - 1;
//sprintf( TextoGlobal, "%i\n%i", WPicOr, HPicOr );
//msgbox( TextoGlobal );
/////////
HBITMAP HBitmpT = CreateCompatibleBitmap( GetDC( 0 ), WPicOr, HPicOr );
HDC HDc = GetDC( Pltrs[0].GetHandleCon() );
HDC THDC = CreateCompatibleDC( HDc );
SetBkMode( HDc, TRANSPARENT );
SelectObject( THDC, HBitmpT );
SetStretchBltMode( THDC, COLORONCOLOR );
BitBlt( THDC, 0, 0, WPicOr, HPicOr, HDc, 0, 0, SRCCOPY );
ReleaseDC( Pltrs[0].GetHandleCon(), HDc );
DeleteDC( THDC );
/////////
RGBQUAD*   RgbQB = (RGBQUAD*)malloc( 4*WPicOr*HPicOr + MBs );
BYTE* RgbTB = (BYTE*)malloc( 4*WPicOr*HPicOr + MBs );
ZeroMemory( &RgbQB[0], 4*WPicOr*HPicOr + MBs - 1 );
ZeroMemory( &RgbTB[0], 4*WPicOr*HPicOr + MBs - 1 );
GetBitmapBits( HBitmpT, 4*WPicOr*HPicOr, &RgbQB[0] );
DeleteObject( HBitmpT );
/////////
DWORD written;
HANDLE HFile = CreateFile( Text2SBMP ,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
BITMAPFILEHEADER bfh;
bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
bfh.bfReserved1 = 0;
bfh.bfReserved2 = 0;
bfh.bfSize = sizeof(BITMAPFILEHEADER);
bfh.bfType = 0x4d42;
WriteFile( HFile, &bfh, sizeof(bfh), &written, NULL);
// Fill out an info form
BITMAPINFOHEADER bih;
bih.biBitCount = 24;
bih.biClrImportant = 0;
bih.biClrUsed = 0;
bih.biCompression = BI_RGB;
bih.biHeight = HPicOr;
bih.biPlanes = 1;
bih.biSize = sizeof(bih);
bih.biSizeImage = 3*WPicOr*HPicOr;
bih.biWidth = WPicOr;
bih.biXPelsPerMeter = 2400;
bih.biYPelsPerMeter = 2400;
WriteFile( HFile, &bih, sizeof(bih), &written, NULL);
////
DWORD index;
index = 0;
int from_index;
from_index = 0;
FOR int y=0; y<HPicOr; y++ LOOP
    FOR int x=0; x<WPicOr; x++ LOOP
        from_index = x + (HPicOr - y - 1)*WPicOr;
        RgbTB[index] = RgbQB[from_index].rgbBlue;
        index++;
        RgbTB[index] = RgbQB[from_index].rgbGreen;
        index++;
        RgbTB[index] = RgbQB[from_index].rgbRed;
        index++;
        IF x==(WPicOr-1) THEN
           while( index%4!=0 )
               index++;
        ENDIF;
    ENDLOOP;
ENDLOOP;
///
WriteFile( HFile, &RgbTB[0], index, &written, NULL);
IF written!=index THEN
   // msgbox( "Error,\n   written!=index   ", "Error.", 16 );
ENDIF;
CloseHandle( HFile );
///
free( RgbQB );
free( RgbTB );


ShellExecute( NULL, "open", Text2SBMP, NULL, NULL, 3 );
SHALLL( TRUE );
IF DivAct THEN
   SendMessage( VENTANA_PADRE, WM_COMMAND, ID_DIV_GRAPH, 0 );
ENDIF;
return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL SHALLL( BOOL BSH ){
    BUndock.setVisible( BSH );
    BCopy.setVisible( BSH );
    Pltrs[0].SetTextVisible( BSH );
    Pltrs[0].SetBText2Show( BSH );
    FOR int i=0; i<2; i++ LOOP
        BtnMp[i].setVisible( BSH );
        BtnEp[i].setVisible( BSH );
        Mp[i].setVisible( BSH );
        Ep[i].setVisible( BSH );
    ENDLOOP;
return TRUE;
}
