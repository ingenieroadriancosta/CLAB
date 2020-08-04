LRESULT PLOTEOS::WProcCon( HWND hwnd, UINT  message, WPARAM wParam, LPARAM lParam ){
MESSAGES
    WHEN( WM_COMMAND )
		FMess( message, wParam, lParam );
    WHEN( WM_LBUTTONDBLCLK )
        IF IsDocked THEN
           IF wParam!=12345 || lParam!=12345 THEN
              break;
           ENDIF;
           IsDockedPermis = TRUE;
           IF IsDockedMaxed && lParam!=12345 THEN
              ShowWindow( HWContainer, 1 );
              IsDockedMaxed = FALSE;
           ELSE
              ShowWindow( HWContainer, 3 );
              IsDockedMaxed = TRUE;
           ENDIF;
           SetSizeConP();
           IsDockedPermis = FALSE;
           FMess( WM_COMMAND, 12345, 12345 );
        ELSE
           FMess( message, wParam, lParam );
        ENDIF;
	WHEN( WM_LBUTTONDOWN )
		SetFocus( hwnd );
        FMess( message, 12345, lParam );
	WHEN( WM_RBUTTONDOWN )
		//SetFocus( hwnd );
        FMess( message, 12345, lParam );
    WHEN( WM_MOUSEWHEEL )
        FMess( WM_MOUSEWHEEL, wParam, 12345 );


    WHEN( WM_SIZE )
		IF IsDocked THEN
           xPosCon = 0;
           yPosCon = 0;
           WidthGraph = 0;
           HeightGraph = 0;

           WidthCon = GetSystemMetrics( SM_CXSCREEN );
		   HeightCon = GetSystemMetrics( SM_CYSCREEN );
		   WidthGraph = WidthCon - xPosGraph - 5 - 25;
           HeightGraph = HeightCon - yPosGraph - 30;
        ENDIF;
        // FMess( message, wParam, lParam );
        // msgbox();


    WHEN( WM_KEYDOWN )
        FMess( WM_KEYDOWN, wParam, lParam );
	WHEN( WM_MOUSEMOVE )
		char TText[256];
		int XMPos = LOWORD(lParam) - xPosGraph;
		int YMPos = HIWORD(lParam) - yPosGraph - 1;
		YMPos = HeightGraph - YMPos - 1;
		if( XMPos<0 || XMPos>=WidthGraph ){
			break;
		}
		//
		if( YMPos<0 || YMPos>=HeightGraph ){
			break;
		}
		//
		double DiffIEX = MaxXLim - MinXLim;
		double DXL = (XMPos);
		DXL = DXL/(WidthGraph-1);
		DXL = (MinXLim + DXL*DiffIEX );





		double DYL = (MaxYLim*YMPos);
		DYL = DYL/(HeightGraph-1);



		//sprintf( TText, "X:%5.3f - %g - %g\nY:%5.5f", DXL, MaxXLim, MinXLim, DYL );
		sprintf( TText, "X:%5.3f\nY:%5.5f", DXL, DYL );
		SetWindowText( HWSText, TText );

		FMess( message, 12345, lParam );

WHEN( WM_PAINT )
    //
    //return DefWindowProc (hwnd, message, wParam, lParam);

    PAINTSTRUCT         ps;
    HDC HDc = BeginPaint( hwnd, &ps );
    SetBkMode( HDc, TRANSPARENT);
	SetTextAlign( HDc, TA_CENTER );



	IF Text2Show!=NULL && BText2Show THEN
	   IF Permission THEN
	      TextOut( HDc, WidthCon/2, HeightCon - 24, Text2Show, strlen(Text2Show) );
       ELSE
	      TextOut( HDc, WidthCon/2, 8, Text2Show, strlen(Text2Show) );
	   ENDIF;
    ENDIF;
    TextOut( HDc, WidthCon - 180, 2, CreadoPor, strlen(CreadoPor) );
    SetTextColor( HDc, (COLORREF)(0x00FF0000) );
    TextOut( HDc, WidthCon - 180, 2+16, AdrianCosta, strlen(AdrianCosta) );
    SetTextColor( HDc, (COLORREF)(0x00000000) );
	/*
	RECT re;
    re.bottom = WidthCon;
    re.left = 0;
    re.right = xPosGraph;
    re.top = 0;
	FillRect( HDc, &re, CreateSolidBrush( RGB( RgbColor , RgbColor , RgbColor ) )  );
	//*/
	char TTex[256];
	double Val2P = MaxYLim;
	Val2P = round(10*Val2P);
	Val2P = Val2P/10;
	sprintf( TTex, "%g", Val2P );
	TextOut( HDc, xPosGraph/2, yPosGraph-6, TTex, strlen(TTex) );
	for( int i=1; i<6; i++ ){
		Val2P = ((5-i)*MaxYLim)/5;
		Val2P = round(10*Val2P);
		Val2P = Val2P/10;

        sprintf( TTex, "%g", Val2P );
		TextOut( HDc, xPosGraph/2, yPosGraph-8 + (i*HeightGraph)/5, TTex, strlen(TTex) );
	}
	sprintf( TTex, "%g", MaxXLim );
	TextOut( HDc, xPosGraph + WidthGraph, yPosGraph + HeightGraph + 5, TTex, strlen(TTex) );

	sprintf( TTex, "%g", MinXLim );
	TextOut( HDc, xPosGraph, yPosGraph + HeightGraph + 5, TTex, strlen(TTex) );
	//*/
    EndPaint( hwnd, &ps);

WHEN( WM_CLOSE )
    return 0;

DEFAULT
     return DefWindowProc (hwnd, message, wParam, lParam);
ENDMESSAGES
return 0;
}

// floricienta 2005 cap 47 3/5
