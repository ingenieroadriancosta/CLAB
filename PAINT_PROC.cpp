BOOL PAINT_PROC( HWND hwnd ){
char Tex2[256];

IF HFontPaintP==NULL THEN
   HFontPaintP = CreateFont( 18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                             OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                             DEFAULT_PITCH | FF_ROMAN, "Times New Roman");
ENDIF;
static HBRUSH HBPan;
PAINTSTRUCT         ps;
HDC HDc = BeginPaint( hwnd, &ps );
SetBkMode( HDc, TRANSPARENT );
HDC THDC = CreateCompatibleDC( HDc );
SelectObject( THDC, HB_FondoPanel );
SetStretchBltMode( HDc, COLORONCOLOR );
RECT PRe;
GetWindowRect( HWCFrame, &PRe );
BOOL Acept = TRUE;
IF Wmaximized THEN
  Acept = StretchBlt( HDc, 1, 1, CXSCREEN, HCFrame,
                      THDC, 0, 0, B_FondoPanel.bmWidth, B_FondoPanel.bmHeight,
                      SRCCOPY );
ELSE
  Acept = StretchBlt( HDc, 1, 1, CXSCREEN, HCFrame,//   CXFULLSCREEN
                      THDC, 0, 0, B_FondoPanel.bmWidth, B_FondoPanel.bmHeight,
                      SRCCOPY );
ENDIF;

IF Permission THEN
   IF !Acept THEN
      msgbox( "IF !Acept THEN\nStretchBlt\nPAINT_PROC.cpp", "", 16 );
   ENDIF;
ENDIF;

DeleteDC( THDC );
//*/
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Frame.
//
//
int XPosTemp = 0;
int YPosTemp = 0;
int WPosTemp = 0;
int HPosTemp = 0;


DeleteObject( HBPan );

HBPan = CreateSolidBrush( RGB( HBValP, HBValP, HBValP ) );


/////////////////////////////////
/////////////////////////////////
// Chann 0.
WindowPos( HWSel_All_In, &XPosTemp, &YPosTemp );
WindowSize( HWSel_All_In, &WPosTemp, &HPosTemp );
//
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WRiLine + i + 2;
    PRe.top = 1 + i;
    PRe.bottom = HPosTemp + 11 + i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
// Internos.
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WRiLine + i + 2;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
//

FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + 4*WPosButSend1 + i - 120;
    PRe.top = HPosTemp + 11 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
// Chann 1.
WindowPos( HWSel_All_Out, &XPosTemp, &YPosTemp );
WindowSize( HWSel_All_Out, &WPosTemp, &HPosTemp );
////
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WRiLine + i + 2;
    PRe.top = 1 + i;
    PRe.bottom = HPosTemp + 11 + i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
// Internos.
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WRiLine + i + 2;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
//

FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + 4*WPosButSend1 + i - 120;
    PRe.top = HPosTemp + 11 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
//*/
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//HBRUSH Ppincel = CreateSolidBrush( RGB( 0, 0, 0 ) );
//SelectObject( HDc, Ppincel );
SelectObject( HDc, HFontPaintP );
SetTextColor( HDc, RGB( 0, 0, 0 ) );

SetTextAlign( HDc, TA_CENTER );


// SetTextColor( HDc, RGB( 255, 255, 255 ) );
// TextOut( HDc, 1, 1, "Iniciar/", 8 );
// TextOut( HDc, 1, 16, "Terminar", 8 );
// TextOut( HDc, 1, 31, "Adquisicion", 11 );


////
XPosTemp = BConnect.getX();
WPosTemp = BConnect.getWidth();
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WPosTemp + i + 3;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
XPosTemp = BConnect.getX() + BConnect.getWidth()/2;
TextOut( HDc, XPosTemp, 3, "Control de", 10 );
TextOut( HDc, XPosTemp, 18, "Adquisicion", 11 );





/*
WindowPos( HWCOMPort, &XPosTemp, &YPosTemp );
WindowSize( HWCOMPort, &WPosTemp, &YPosTemp );

XPosTemp = XPosTemp + WPosTemp/2;
TextOut( HDc, XPosTemp, 1, "Puerto de", 9 );
// TextOut( HDc, 100, 16, "de", 2 );
TextOut( HDc, XPosTemp, 16, "conexion", 8 ); // -->> 31
//*/




// Vista.
XPosTemp = BVista.getX();
YPosTemp = BVista.getY();
WPosTemp = BVista.getWidth();
HPosTemp = BVista.getHeight();
////
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WPosTemp + i + 3;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;




XPosTemp = BOpen.getX();
YPosTemp = BOpen.getY();
WPosTemp = BOpen.getWidth();
HPosTemp = BOpen.getHeight();
////
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WPosTemp + i + 3;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;

////
XPosTemp = BComp.getX();
YPosTemp = BComp.getY();
WPosTemp = BComp.getWidth();
HPosTemp = BComp.getHeight();
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WPosTemp + i + 3;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;






XPosTemp = BVista.getX() + BVista.getWidth() + 8 - 2;
YPosTemp = BVista.getY();
WindowSize( HWDataCurAll, &WPosTemp, &HPosTemp );
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WPosTemp + i + 9;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;









WindowPos( HWTs, &XPosTemp, &YPosTemp );
WindowSize( HWTs, &WPosTemp, &HPosTemp );
////
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WPosTemp + i + 3;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
SetTextAlign( HDc, TA_LEFT );
TextOut( HDc, XPosTemp - 3, 3, "Tiempos de:", 11 );


WindowPos( HWTs, &XPosTemp, &YPosTemp );
WindowSize( HWTs, &WPosTemp, &HPosTemp );
SetTextAlign( HDc, TA_CENTER );
XPosTemp = XPosTemp + WPosTemp/2;
TextOut( HDc, XPosTemp, YPosTemp - HPosTemp/2 - 4, "Muestreo", 8 ); // -->>31


//   de  (Seg)

WindowPos( HWTime, &XPosTemp, &YPosTemp );
WindowSize( HWTime, &WPosTemp, &HPosTemp );
XPosTemp = XPosTemp + WPosTemp/2;
//TextOut( HDc, XPosTemp, 1, "Tiempo de", 9 );
TextOut( HDc, XPosTemp, YPosTemp - HPosTemp/2 - 4, "Adquisicion", 11 );
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Canal uno.
//
SetTextAlign( HDc, TA_LEFT );
WindowPos( HWCB_SQ_Wave0, &XPosTemp, &YPosTemp );
WindowSize( HWCB_SQ_Wave0, &WPosTemp, &HPosTemp );
sprintf( Tex2, "Se%cal", 241 );
TextOut( HDc, XPosTemp - 39, YPosTemp+2, Tex2, strlen(Tex2) );

//

SetTextAlign( HDc, TA_LEFT );
WindowPos( HWFs_Out0, &XPosTemp, &YPosTemp );
WindowSize( HWCB_SQ_Wave0, &WPosTemp, &HPosTemp );
sprintf( Tex2, "Frec." );
TextOut( HDc, XPosTemp - 39, YPosTemp+2, Tex2, strlen(Tex2) );




WindowPos( HWB_Val, &XPosTemp, &YPosTemp );
WindowSize( HWB_Val, &WPosTemp, &HPosTemp );
XPosTemp = (int)( XPosTemp - 31 );
TextOut( HDc, XPosTemp, YPosTemp + 2, "Max", 3 );
//
WindowPos( HWB_Val_Min, &XPosTemp, &YPosTemp );
WindowSize( HWB_Val_Min, &WPosTemp, &HPosTemp );
XPosTemp = (int)( XPosTemp - 28 );
TextOut( HDc, XPosTemp, YPosTemp + 2, "Min", 3 );

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Canal dos.
//
WindowPos( HWCB_SQ_Wave1, &XPosTemp, &YPosTemp );
WindowSize( HWCB_SQ_Wave1, &WPosTemp, &HPosTemp );
sprintf( Tex2, "Se%cal", 241 );
TextOut( HDc, XPosTemp - 39, YPosTemp+2, Tex2, strlen(Tex2) );

//

SetTextAlign( HDc, TA_LEFT );
WindowPos( HWFs_Out1, &XPosTemp, &YPosTemp );
WindowSize( HWCB_SQ_Wave1, &WPosTemp, &HPosTemp );
sprintf( Tex2, "Frec." );
TextOut( HDc, XPosTemp - 39, YPosTemp+2, Tex2, strlen(Tex2) );




WindowPos( HWD_Val, &XPosTemp, &YPosTemp );
WindowSize( HWD_Val, &WPosTemp, &HPosTemp );
XPosTemp = (int)( XPosTemp - 31 );
TextOut( HDc, XPosTemp, YPosTemp + 2, "Max", 3 );
//
WindowPos( HWD_Val_Min, &XPosTemp, &YPosTemp );
WindowSize( HWD_Val_Min, &WPosTemp, &HPosTemp );
XPosTemp = (int)( XPosTemp - 28 );
TextOut( HDc, XPosTemp, YPosTemp + 2, "Min", 3 );

SetTextAlign( HDc, TA_CENTER );
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////------------------->PWM
////
if( IsWindowVisible(HWPwm1)==TRUE ){
SelectObject( HDc, HFontButts );
// SelectObject( HDc, HFontPaintP );
SetTextAlign( HDc, TA_CENTER );
WindowPos( HWPwmSend, &XPosTemp, &YPosTemp );
WindowSize( HWPwmSend, &WPosTemp, &HPosTemp );
FOR int i=0; i<BorderFor; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WPosTemp + i + 3;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
int XPosPwm = XPosTemp + WPosTemp/2;
TextOutW( HDc, XPosPwm, 3, L"PWM1", 4 );


WindowPos( HWPwm2, &XPosTemp, &YPosTemp );
TextOutW( HDc, XPosPwm, YPosTemp - 14, L"PWM2", 4 );
}else{
    WindowPos( HWPwmSend, &XPosTemp, &YPosTemp );
    int XPosPwm = XPosTemp + WPosTemp/2;
    TextOutW( HDc, XPosPwm+8, 3, L"Version libre", 13 );
}















////////////////////////////////////////////////////////////////////////////////
EndPaint( hwnd, &ps);
return TRUE;
}
