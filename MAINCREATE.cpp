#include "IDS_CONTROL.h"
#include "WCCreate.cpp"
#include "WCCrClose.cpp"
#include "SetFonts.cpp"

int IWidWinSave = 0;
int IHeiWinSave = 0;
int MAINCREATE( HWND HWnd ){


RGBQUAD* RgbQ = (RGBQUAD*)malloc( 4*75*13 + 1024 );
FOR int i=0; i<4; i++ LOOP
    int WMax = 65;
    IF i%2==0 THEN
       WMax = 75;
    ENDIF;

    HB_CButt_C[i] = CNewBitmap( WMax, 13 );
    FOR int y=0; y<13; y++ LOOP
        FOR int x=0; x<WMax; x++ LOOP
            int ToIndex = x + WMax*y;
            RgbQ[ToIndex] = LineColors[i];
        ENDLOOP;
    ENDLOOP;
    SetBitmapBits( HB_CButt_C[i], 4*WMax*13, &RgbQ[0] );
ENDLOOP;
free( RgbQ );
///

int IXPosWin = 0;
int IYPosWin = 0;
int IWidWin = 0;
int IHeiWin = 0;

char Texto1[1024];
SetFonts();






// ID_RESET_ALL
// "&Reestablecer grafica\aCtrl + Alt + R"







BOpen.setLocation( XBOpen, 5 );
BOpen.setSize( 36, 36 );
BOpen.setVisible( TRUE );
BOpen.setFather( HWnd, ID_OPEN_F_REST );
BOpen.setText( ID_STRING_OPEN );
BOpen.setJPGResource( ID_PIC_OPEN_AS );
BOpen.setVisible( TRUE );



BSave.setLocation( BOpen.getX(), BOpen.getY() + BOpen.getHeight() + 3 );
BSave.setSize( BOpen.getWidth(), BOpen.getHeight() );
BSave.setVisible( TRUE );
BSave.setFather( HWnd, ID_SAVE_F_REST );
BSave.setText( ID_STRING_SAVE );
BSave.setJPGResource( ID_PIC_SAVE_AS );
BSave.setVisible( TRUE );


BExport.setLocation( BOpen.getX(), BOpen.getY() + BOpen.getHeight() + BSave.getHeight() + 6 );
BExport.setSize( BOpen.getWidth(), BOpen.getHeight() );
BExport.setVisible( TRUE );
BExport.setFather( HWnd, ID_SAVE_DATA );
BExport.setText( ID_STRING_EXPORT );
BExport.setBMPResource( ID_PIC_EXPORT );
BExport.setVisible( TRUE );





BSaveBMP.setLocation( BOpen.getX() + BOpen.getWidth() + 6, BOpen.getY() );
BSaveBMP.setSize( BOpen.getWidth(), BOpen.getHeight() );
BSaveBMP.setVisible( TRUE );
BSaveBMP.setFather( HWnd, ID_SAVE_BMP );
BSaveBMP.setText( ID_STRING_SAVE_BMP );
BSaveBMP.setJPGResource( ID_PIC_SAVE_BMP );
BSaveBMP.setVisible( TRUE );





BComp.setLocation( BOpen.getX() + BOpen.getWidth() + 6, BSave.getY() );
BComp.setSize( BOpen.getWidth(), BOpen.getHeight() );
BComp.setVisible( TRUE );
BComp.setFather( HWnd, ID_COMPLEMENTS );
BComp.setText( ID_STRING_COMPLEMENTS );
BComp.setJPGResource( ID_PIC_COMPLEM );
BComp.setVisible( TRUE );




BNew.setLocation( BComp.getX(), BExport.getY() );
BNew.setSize( BSave.getWidth(), BSave.getHeight() );
BNew.setVisible( TRUE );
BNew.setFather( HWnd, ID_NEW );
BNew.setText( ID_STRING_NEW );
BNew.setJPGResource( ID_PIC_NEW );
BNew.setVisible( TRUE );
//*/


// VISTA.


BVista.setLocation( BOpen.getX() + BOpen.getWidth() + 60, 7 );
BVista.setSize( 2*28 + 2, 38 );
BVista.setVisible( TRUE );
BVista.setFather( HWnd, ID_VISTA );
BVista.setText( ID_STRING_VISTA );
BVista.setJPGResource( ID_PIC_VISTA );
BVista.setVisible( TRUE );


BZoomIn.setLocation( BVista.getX(), BVista.getY() + BVista.getHeight() + 8 );
BZoomIn.setSize( 28, 28 );
BZoomIn.setVisible( TRUE );
BZoomIn.setFather( HWnd, ID_ZOOM_IN, BS_NOTIFY );
BZoomIn.setText( ID_STRING_ZOOMIN );
BZoomIn.setJPGResource( ID_PIC_ZOOMIN );
BZoomIn.setVisible( TRUE );



BZoomOut.setLocation( BZoomIn.getX() + BZoomIn.getWidth() + 2,  BZoomIn.getY() );
BZoomOut.setSize( BZoomIn.getWidth(), BZoomIn.getHeight() );
BZoomOut.setVisible( TRUE );
BZoomOut.setFather( HWnd, ID_ZOOM_OUT, BS_NOTIFY );
BZoomOut.setText( ID_STRING_ZOOMOUT );
BZoomOut.setJPGResource( ID_PIC_ZOOMOUT );
BZoomOut.setVisible( TRUE );




BAuto.setLocation( BZoomIn.getX(),  BZoomIn.getY() + BZoomIn.getHeight() + 8 );
BAuto.setSize( BZoomIn.getWidth(), BZoomIn.getHeight() );
BAuto.setVisible( TRUE );
BAuto.setFather( HWnd, ID_ZOOM_AUTO );
BAuto.setText( ID_STRING_ZOOMREST );
BAuto.setJPGResource( ID_PIC_AUTO );
BAuto.setVisible( TRUE );





BRedraw.setLocation( BZoomOut.getX(),  BAuto.getY() );
BRedraw.setSize( BAuto.getWidth(), BAuto.getHeight() );
BRedraw.setVisible( TRUE );
BRedraw.setFather( HWnd, ID_ZOOM_REDRAW );
BRedraw.setText( ID_STRING_REDRAW );
BRedraw.setJPGResource( ID_PIC_REDRAW );
BRedraw.setVisible( TRUE );








HWDataCurAll = CreateWindowEx( 0, "BUTTON", "Cursor",
                            WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                            BS_FLAT | BS_CENTER,
                            BVista.getX() + BVista.getWidth() + 8,
                            BVista.getY(),
                            70, 20,
                            HWnd, (HMENU)ID_DAT_CUR_ONO, NULL, NULL );
///////////////////////
WindowPos( HWDataCurAll, &IXPosWin, &IYPosWin );
WindowSize( HWDataCurAll, &IWidWin, &IHeiWin );
FOR int i=0; i<4; i++ LOOP
    IF (i%2)==0 THEN
       sprintf( Texto1, "Ent. %i", ((i)/2 + 1) );
    ELSE
       sprintf( Texto1, "Sal. %i", ((i)/2 + 1) );
    ENDIF;
    HWDataCur[i] = CreateWindowEx( 0, "BUTTON", Texto1,
                                   WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                                   BS_FLAT | BS_CENTER,
                                   IXPosWin - 1,
                                   IYPosWin + 22*(i+1),
                                   IWidWin + 2, IHeiWin + 2,
                                   HWnd, (HMENU)(ID_DATA_CURSOR0+i), NULL, NULL );
    /*
    IF (i%2)==0 THEN
       sprintf( Texto1, "Entrada %i", ((i)/2 + 1) );
    ELSE
       sprintf( Texto1, "Salida %i", ((i)/2 + 1) );
    ENDIF;
    HWDataCur[i] = CreateWindowEx( 0, "BUTTON", Texto1,
                                   WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                                   BS_FLAT | BS_CENTER,
                                   BVista.getX() + BVista.getWidth() + 8,
                                   BVista.getY() + 22*(i+1),
                                   IWidWin + 2, IHeiWin + 2,
                                   HWnd, (HMENU)(ID_DATA_CURSOR0+i), NULL, NULL );
    //*/
ENDLOOP;


// ID_OPEN_F_REST







BConnect.setLocation( BOpen.getX() + BOpen.getWidth() + 217, 38 );
BConnect.setSize( 82, 42 );
BConnect.setVisible( TRUE );
BConnect.setFather( HWnd, ID_CONNECT );
BConnect.setText( ID_CNNBUTTONI );
BConnect.setJPGResource( ID_BUTT_ON );

//
TimeStatus.setLocation( BConnect.getX(), BConnect.getY() + BConnect.getHeight() + 8 );
TimeStatus.setSize( BConnect.getWidth(), 22 );
TimeStatus.setFather( HWnd );
TimeStatus.setVisible( TRUE );
TimeStatus.setText( "T: 000 seg" );
//
//
HWTs = CreateWindowEx( 0, "COMBOBOX", NULL,
                       WS_CHILD | WS_VISIBLE | WS_BORDER  | CBS_DROPDOWNLIST |
                       WS_TABSTOP | WS_VSCROLL,
                       BConnect.getX() + BConnect.getWidth() + 18,
                       BConnect.getY() + 6,
                       84, 364, HWnd, (HMENU)ID_SET_FS, INSTANCIA_GLOBAL, NULL );
SendMessage( HWTs, WM_SETFONT, (WPARAM)HFontFs, MAKELPARAM(TRUE, 0) );
//

double CTime;
CTime = MaxFsReal;
CTime = 1000000/CTime;
CTime = CTime;
sprintf( Texto1, "%g us", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );
//


CTime = MaxFsReal;
CTime = 2000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );
//




CTime = MaxFsReal;
CTime = 4000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );
//




CTime = MaxFsReal;
CTime = 10000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );
//




CTime = MaxFsReal;
CTime = 20000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );
//





CTime = MaxFsReal;
CTime = 40000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );




CTime = MaxFsReal;
CTime = 100000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );




CTime = MaxFsReal;
CTime = 200000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );




CTime = MaxFsReal;
CTime = 400000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );





CTime = MaxFsReal;
CTime = 1000000/CTime;
CTime = CTime;
sprintf( Texto1, "%g ms", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );





CTime = MaxFsReal;
CTime = 2000/CTime;
CTime = CTime;
sprintf( Texto1, "%g Seg", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );




CTime = MaxFsReal;
CTime = 4000/CTime;
CTime = CTime;
sprintf( Texto1, "%g Seg", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );




CTime = MaxFsReal;
CTime = 10000/CTime;
CTime = CTime;
sprintf( Texto1, "%g Seg", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );




CTime = MaxFsReal;
CTime = 20000/CTime;
CTime = CTime;
sprintf( Texto1, "%g Seg", CTime );
SendMessage( HWTs, CB_ADDSTRING, 0, (LPARAM)Texto1 );

//
SendMessage( HWTs, CB_SETCURSEL, CurTs, CurTs );
SetToolTipW( HWTs, ID_TOOLTIP_TS );










IXPosWin = WinFuncs.GetWinXPos( HWTs );
IYPosWin = WinFuncs.GetWinYPos( HWTs );

IWidWin = WinFuncs.GetWinWidth( HWTs );
IHeiWin = WinFuncs.GetWinHeight( HWTs );



sprintf( Texto1, "%i", DTime );
HWTime = CreateWindowEx( 0, "EDIT", Texto1, WS_CHILD | WS_VISIBLE | WS_BORDER |
                         //ES_NOHIDESEL |
                         ES_CENTER |
                         ES_NUMBER,
                         IXPosWin + IWidWin/2 - 24,
                         IYPosWin + IHeiWin + 22,
                         48, 27, HWnd, (HMENU)ID_SET_TIME, INSTANCIA_GLOBAL, NULL );
SendMessage( HWTime, WM_SETFONT, (WPARAM)HFont, MAKELPARAM(TRUE, 0) );
SetToolTipW( HWTime, ID_TOOLTIP_TIME );
//*/






WCCreate( HWnd );









/*
HBITMAP HBitmapLogo;
HBitmapLogo = LoadBitmap( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_PIC_LOG_UPC) );
HWLogoUPC = CreateWindowEx( 0, WC_STATICA, NULL,
                            WS_CHILD | WS_BORDER | WS_VISIBLE |
                            SS_BITMAP,
                            1190, 24, 16, 16,
                            HWnd, NULL, INSTANCIA_GLOBAL, NULL );
SendMessage( HWLogoUPC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HBitmapLogo );
//*/






#define WPWMSEND 54
#define W_E_PWM  34
#define Y_E_PWM1 18
#define Y_E_PWM2 (Y_E_PWM1+48)
const int DefXPwm = XPosButSend1 + 2 * WRiLine + 38 + (WPWMSEND - W_E_PWM-4)/2;
HWPwmSend = CreateWindowEx( 0, "BUTTON", "Enviar",
                            WS_CHILD |
                            // WS_VISIBLE |
                            WS_BORDER | BS_MULTILINE,
                            XPosButSend1 + 2 * WRiLine + 36, 94,
                            WPWMSEND, 22,
                            HWnd, (HMENU)ID_E_PWM1_BUTT, NULL, NULL );
HWPwm1   = CreateWindowEx( 0, "EDIT", "0",
                           WS_CHILD |
                           // WS_VISIBLE |
                           WS_BORDER | ES_CENTER | ES_NUMBER,
                           DefXPwm, Y_E_PWM1,
                           W_E_PWM, 24,
                           HWnd, (HMENU)ID_E_PWM1, INSTANCIA_GLOBAL, NULL );
SendMessage( HWPwm1, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );


HWPwm2   = CreateWindowEx( 0, "EDIT", "0",
                           WS_CHILD |
                           //WS_VISIBLE |
                           WS_BORDER | ES_CENTER | ES_NUMBER,
                           DefXPwm, Y_E_PWM2,
                           W_E_PWM, 24,
                           HWnd, (HMENU)ID_E_PWM2, INSTANCIA_GLOBAL, NULL );
SendMessage( HWPwm2, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );










////////
////////
WCCrClose( HWnd );
return 0;
}
