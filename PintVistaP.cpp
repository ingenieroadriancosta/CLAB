int PintVistaP( HWND hwnd ){
return 0;
static HBRUSH HBPan;
DeleteObject( HBPan );
HBPan = CreateSolidBrush( RGB( 64, 64, 64 ) );

PAINTSTRUCT         ps;
HDC HDc = BeginPaint( hwnd, &ps );
SetBkMode( HDc, TRANSPARENT );
RECT PRe;


int XPosTemp = 0;
int YPosTemp = 0;
int WPosTemp = 0;
int HPosTemp = 0;



WindowPos( hwnd, &XPosTemp, &YPosTemp );
WindowSize( hwnd, &WPosTemp, &HPosTemp );

// Internos.
FOR int i=0; i<2; i++ LOOP
    PRe.left = 2 - i;
    PRe.right = WPosTemp - i - 1;
    PRe.top = 2 - i;
    PRe.bottom = HPosTemp - i - 1;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;






// BorderFor
FOR int i=0; i<4; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WRiLine + i + 2;
    PRe.top = 1 + i;
    PRe.bottom = HPosTemp + 11 + i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
// Internos.
FOR int i=0; i<4; i++ LOOP
    PRe.left = XPosTemp - 3 - i;
    PRe.right = XPosTemp + WRiLine + i + 2;
    PRe.top = 1 + i;
    PRe.bottom = HCFrame - 7 - i;
    FrameRect( HDc, &PRe, HBPan );
ENDLOOP;
EndPaint( hwnd, &ps);
return 0;
}
