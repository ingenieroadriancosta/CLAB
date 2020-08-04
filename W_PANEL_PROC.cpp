//
#include "PAINT_PROC.cpp"
//
LRESULT CALLBACK W_PANEL_PROC (HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam ){
static BOOL MovePanel;
// static BOOL ReMove;
MESSAGES
WHEN( WM_KEYDOWN )
     return DefWindowProc (hwnd, message, wParam, lParam);
     /*
     IF wParam==VK_TAB THEN
        // msgbox();
        int I = 0;
        HWND HWFoc = GetFocus();
        FOR int i=0; i<128; i++ LOOP
            IF HWFoc==HW_FOCO[i] THEN
               IFocus = i;
               break;
            ENDIF;
        ENDLOOP;

        IFocus = 127&(IFocus + 1 );
        SetFocus( HW_FOCO[IFocus] );
     ENDIF;
     //*/

     //FUNC_USB( wParam );



WHEN( WM_COMMAND )
     SendMessage( VENTANA_PADRE, message, wParam, lParam );
WHEN( WM_LBUTTONDBLCLK )
     SendMessage( VENTANA_PADRE, WM_LBUTTONDBLCLK, 0, 0 );
     //MoveWindow( HWCFrame, 1, 1, WPan - 2, HCFrame - 4, TRUE );
//WHEN( WM_KEYDOWN )
    //SetFocus( HWFs_Out0 );
    //VK_RETURN



WHEN( WM_PAINT )
    IF hwnd==HWCFrame THEN
       PAINT_PROC( hwnd );
    ELSE
       return DefWindowProc (hwnd, message, wParam, lParam);
    ENDIF;
WHEN( WM_CTLCOLORSTATIC )
    IF  HWTime==(HWND)lParam THEN
        IF !pincel THEN
            pincel = CreateSolidBrush( RGB( 255, 255, 255 ) );
        ENDIF;
        SetTextColor( (HDC)wParam, RGB( 0, 0, 0) );
        SetBkColor( (HDC)wParam, RGB( 255, 255, 255) );
        return (LRESULT)pincel;
        /*
        IF !pincel THEN
            pincel = CreateSolidBrush( RGB( 0, 64, 127 ) );
        ENDIF;
        SetTextColor( (HDC)wParam, RGB(0,0,255));
        SetBkColor( (HDC)wParam, RGB(0,255,0));
        return (LRESULT)pincel;
        //*/

    ELSIF HWSel_Chann0_In==(HWND)lParam THEN
        //return DefWindowProc( hwnd, message, wParam, lParam );

        static HBRUSH PI0;
        DeleteObject( PI0 );
        /*
        PI0 = CreateSolidBrush( RGB( LineColors[0].rgbRed,
                                LineColors[0].rgbGreen,
                                LineColors[0].rgbBlue ) );

        SetTextColor( (HDC)wParam,
                      RGB( ~LineColors[0].rgbRed,
                      ~LineColors[0].rgbGreen,
                      ~LineColors[0].rgbBlue ) );
        SetBkColor( (HDC)wParam,
                    RGB( LineColors[0].rgbRed,
                    LineColors[0].rgbGreen,
                    LineColors[0].rgbBlue ) );
        //*/

        DeleteObject( PI0 );
        PI0 = CreateSolidBrush( RGB( 250,
                                     250,
                                     250 ) );
        SetTextColor( (HDC)wParam,
                      RGB( 0,
                           0,
                           0 ) );
        SetBkColor( (HDC)wParam, RGB( 250,
                                      250,
                                      250 ) );

        return (LRESULT)PI0;

    ELSIF HWSel_Chann1_In==(HWND)lParam THEN
        static HBRUSH PI1;
        DeleteObject( PI1 );
        /*
        PI1 = CreateSolidBrush( RGB( LineColors[2].rgbRed,
                                LineColors[2].rgbGreen,
                                LineColors[2].rgbBlue ) );

        SetTextColor( (HDC)wParam,
                      RGB( ~LineColors[2].rgbRed,
                      ~LineColors[2].rgbGreen,
                      ~LineColors[2].rgbBlue ) );
        SetBkColor( (HDC)wParam,
                    RGB( LineColors[2].rgbRed,
                    LineColors[2].rgbGreen,
                    LineColors[2].rgbBlue ) );
        //*/
        PI1 = CreateSolidBrush( RGB( 250,
                                     250,
                                     250 ) );
        SetTextColor( (HDC)wParam,
                      RGB( 0,
                           0,
                           0 ) );
        SetBkColor( (HDC)wParam, RGB( 250,
                                      250,
                                      250 ) );
        return (LRESULT)PI1;

    ELSIF HWSel_Chann0_Out==(HWND)lParam THEN
        static HBRUSH PO0;
        DeleteObject( PO0 );
        /*
        PO0 = CreateSolidBrush( RGB( LineColors[1].rgbRed,
                                LineColors[1].rgbGreen,
                                LineColors[1].rgbBlue ) );

        SetTextColor( (HDC)wParam,
                      RGB( ~LineColors[1].rgbRed,
                      ~LineColors[1].rgbGreen,
                      ~LineColors[1].rgbBlue ) );
        SetBkColor( (HDC)wParam,
                    RGB( LineColors[1].rgbRed,
                    LineColors[1].rgbGreen,
                    LineColors[1].rgbBlue ) );
        //*/

        PO0 = CreateSolidBrush( RGB( 250,
                                     250,
                                     250 ) );
        SetTextColor( (HDC)wParam,
                      RGB( 0,
                           0,
                           0 ) );
        SetBkColor( (HDC)wParam, RGB( 250,
                                      250,
                                      250 ) );
        return (LRESULT)PO0;

    ELSIF HWSel_Chann1_Out==(HWND)lParam THEN
        static HBRUSH PO1;
        DeleteObject( PO1 );
        /*
        PO1 = CreateSolidBrush( RGB( LineColors[3].rgbRed,
                                LineColors[3].rgbGreen,
                                LineColors[3].rgbBlue ) );

        SetTextColor( (HDC)wParam,
                      RGB( ~LineColors[3].rgbRed,
                      ~LineColors[3].rgbGreen,
                      ~LineColors[3].rgbBlue ) );
        SetBkColor( (HDC)wParam,
                    RGB( LineColors[3].rgbRed,
                    LineColors[3].rgbGreen,
                    LineColors[3].rgbBlue ) );
        //*/

        DeleteObject( PO1 );
        PO1 = CreateSolidBrush( RGB( 250,
                                     250,
                                     250 ) );
        SetTextColor( (HDC)wParam,
                      RGB( 0,
                           0,
                           0 ) );
        SetBkColor( (HDC)wParam, RGB( 250,
                                      250,
                                      250 ) );

        return (LRESULT)PO1;

    ELSIF  HWSel_All_In==(HWND)lParam ||
           HWSel_Chann0_Out==(HWND)lParam ||
           HWSel_Chann1_Out==(HWND)lParam ||
           HWSel_All_Out==(HWND)lParam  THEN
        IF !pincel THEN
            pincel = CreateSolidBrush( RGB( 255, 255, 255 ) );
        ENDIF;
        SetTextColor( (HDC)wParam, RGB( 0, 0, 0) );
        SetBkColor( (HDC)wParam, RGB( 255, 255, 255) );
        return (LRESULT)pincel;
    ELSE
        IF !pincel THEN
            pincel = CreateSolidBrush( RGB( 255, 255, 255 ) );
        ENDIF;
        SetTextColor( (HDC)wParam, RGB( 0, 0, 0) );
        SetBkColor( (HDC)wParam, RGB( 255, 255, 255) );
        return (LRESULT)pincel;
        return DefWindowProc( hwnd, message, wParam, lParam );
    ENDIF;



WHEN( WM_NCLBUTTONDBLCLK )
     MoveWindow( HWCFrame, 1, 1, WPan - 2, HCFrame - 4, TRUE );

WHEN( WM_LBUTTONUP )
	 MovePanel++;
	 MovePanel = FALSE;
WHEN( WM_CREATE )
     IF HWPanel!=NULL THEN
        return MAINCREATE( hwnd );
     ENDIF;
     return DefWindowProc (hwnd, message, wParam, lParam);


WHEN( WM_LBUTTONDOWN )
	 SetFocus( hwnd );
	 // SetFocus( BOpen.GetHandle() );
	 //SetFocus( HWTs );

WHEN( WM_MOUSEWHEEL )
     // msgbox();
     IF VHCFrame!=HCFrameBig THEN
        return DefWindowProc( hwnd, message, wParam, lParam );
     ENDIF;


      Sinfo.cbSize = sizeof(Sinfo);
      Sinfo.fMask  = SIF_ALL;
      GetScrollInfo( HWPanel, SB_HORZ, &Sinfo );

     short rueda = HIWORD(wParam);
     rueda /= WHEEL_DELTA;
     IF rueda>=0 THEN
        Sinfo.nPos--;
     ELSE
        Sinfo.nPos++;
     ENDIF;


     IF Sinfo.nPos<0 THEN
        Sinfo.nPos = 0;
     ELSIF Sinfo.nPos>=20 THEN
        Sinfo.nPos = Sinfo.nMax;
     ENDIF;
     Sinfo.fMask = SIF_POS;
     int CXFUL = GetSystemMetrics( SM_CXSCREEN );// SM_CXSCREEN   SM_CXFULLSCREEN
     //int NeWW = ((WPan - 2)*Sinfo.nPos)/Sinfo.nMax;
     double NeWWD = (double)(CXFUL - 2 - WPan);
     NeWWD = NeWWD * Sinfo.nPos;
     NeWWD = NeWWD/((double)Sinfo.nMax);
     NeWWD = round( NeWWD );
     int NeWW = (int)NeWWD;


     MoveWindow( HWCFrame, 1 - NeWW, 1, WPan + NeWW - 2, HCFrame - 4, TRUE );
     SetScrollInfo( HWPanel, SB_HORZ, &Sinfo, TRUE );
     return 0;

DEFAULT
     return DefWindowProc (hwnd, message, wParam, lParam);
ENDMESSAGES
return 0;
}
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
LRESULT CALLBACK W_PANEL_PROC_P( HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam ){
MESSAGES
WHEN( WM_LBUTTONDOWN )
	 SetFocus( hwnd );
WHEN( WM_LBUTTONDBLCLK )
     SendMessage( VENTANA_PADRE, WM_LBUTTONDBLCLK, 0, 0 );
     //MoveWindow( HWCFrame, 1, 1, WPan - 2, HCFrame - 4, TRUE );
     //  MoveWindow( HWPanel, 1, 1, WFather-2, VHCFrame, TRUE );
WHEN( WM_SIZE )
    WPan = LOWORD(lParam);
    HPan = HIWORD(lParam);

    IF Wmaximized  THEN
       //MoveWindow( HWCFrame, 1, 1, WPan - 2, VHCFrame - 4, TRUE );
       #define DefBXPos 53
       #define DefBYPos 1
       MoveWindow( HWClose,  WPan - DefBXPos,           DefBYPos, 48, 20, TRUE );
       MoveWindow( HWResMax, WPan - DefBXPos - 28,      DefBYPos, 28, 20, TRUE );
       MoveWindow( HWMin,    WPan - DefBXPos - 28 - 29, DefBYPos, 29, 20, TRUE );
    ENDIF;
    //
    //
    int WWin = LOWORD(lParam);
    int HWin = HIWORD(lParam);
    IF WWin>1260 THEN
       MoveWindow( HWLogoUPC,  WWin - 72, HWin - 72, 66, 66, TRUE );
    ENDIF;



WHEN( WM_PAINT )
    return DefWindowProc( hwnd, message, wParam, lParam);
    PAINTSTRUCT         ps;
    HDC HDc = BeginPaint( hwnd, &ps );
    SetBkMode( HDc, TRANSPARENT );
    RECT re;
    GetWindowRect( hwnd, &re );
    re.top = 0;
    re.left = 0;
    re.bottom = HPan + 1;
    re.right = WPan + 1;


    #define DPar 1.3
    static HBRUSH HbrS;
    IF !HbrS THEN
       HbrS = CreateSolidBrush( RGB( 0, (int)(DPar*64), (int)(DPar*127) ) );
    ENDIF;
    FillRect( HDc, &re, HbrS );
    // TextOut( HDc, 1, 1, "Hola", 4 );
    EndPaint( hwnd, &ps );
    //return DefWindowProc( hwnd, message, wParam, lParam );

WHEN( WM_VSCROLL )
	 break;
     msgbox();

WHEN( WM_HSCROLL )
     IF hwnd!=HWPanel THEN
        return DefWindowProc( hwnd, message, wParam, lParam );
     ENDIF;
     // TEXTHANDLER * handler = ((TEXTHANDLER *)GetProp(hWnd, "TEXTHANDLER"));
     // GetPropW
      // If user is trying to scroll outside
      // of scroll range, we don't have to
      // invalidate window
      // BOOL needInvalidation = TRUE;


      Sinfo.cbSize = sizeof(Sinfo);
      Sinfo.fMask  = SIF_ALL;
      GetScrollInfo( hwnd, SB_HORZ, &Sinfo );

      CASE( LOWORD(wParam) )IS
          WHEN( SB_LINELEFT )
              Sinfo.nPos -= 1;
              IF Sinfo.nPos < 0 THEN
                 Sinfo.nPos = 0;
                 //needInvalidation = FALSE;
              ENDIF;
          WHEN( SB_LINERIGHT )
              Sinfo.nPos += 1;
              IF Sinfo.nPos > Sinfo.nMax THEN
                 Sinfo.nPos = Sinfo.nMax;
                 //needInvalidation = FALSE;
              ENDIF;
          WHEN( SB_THUMBTRACK )
              Sinfo.nPos = Sinfo.nTrackPos;
          DEFAULT
              int i123 = 0;
              i123++;
      ENDCASE;

      Sinfo.fMask = SIF_POS;


      int CXFUL = GetSystemMetrics( SM_CXFULLSCREEN );
      //int NeWW = ((WPan - 2)*Sinfo.nPos)/Sinfo.nMax;
      double NeWWD = (double)(CXFUL - 2 - WPan);
      NeWWD = NeWWD * Sinfo.nPos;
      NeWWD = NeWWD/((double)Sinfo.nMax);
      NeWWD = round( NeWWD );
      int NeWW = (int)NeWWD;


      MoveWindow( HWCFrame, 1 - NeWW, 1, WPan + NeWW - 2, HCFrame - 4, TRUE );
      SetScrollInfo( hwnd, SB_HORZ, &Sinfo, TRUE );
      return 0;


      IF (WPan + NeWW - 2)>=1220 THEN
         Sinfo.nPos = Sinfo.nMax;
         SetScrollInfo( hwnd, SB_HORZ, &Sinfo, TRUE );

         MoveWindow( HWCFrame, 1 - CXFUL + WPan, 1, CXFUL, HCFrame - 4, TRUE );
      ELSE
         SetScrollInfo( hwnd, SB_HORZ, &Sinfo, TRUE );
         MoveWindow( HWCFrame, 1 - NeWW, 1, WPan + NeWW - 2, HCFrame - 4, TRUE );
      ENDIF;
      //sprintf( TextoGlobal, "%i", WPan );
      //SetWindowText( VENTANA_PADRE, TextoGlobal );
      // Set new text renderer parameters
      ///handler->renderer->xPos = si.nPos;

      // if ( needInvalidation ) InvalidateRect( hwnd, NULL, FALSE);
      return 0;
DEFAULT
     return DefWindowProc( hwnd, message, wParam, lParam );
ENDMESSAGES
return 0;
}
