BOOL CALLBACK Dlg_About(HWND hDlg, UINT  message, WPARAM wParam, LPARAM lParam){
static HBITMAP HBitmapDLG;
static HWND HWBmp;
static HFONT SHFont;
MESSAGES
WHEN( WM_LBUTTONDOWN )
    SetFocus( HWBmp );
WHEN( WM_CTLCOLORSTATIC )
    //SetFocus( hwnd );
    static HBRUSH Dpincel;
    DeleteObject( Dpincel );
    Dpincel = CreateSolidBrush( RGB( 255, 255, 255 ) );
    SetTextColor( (HDC)wParam, RGB( 0, 0, 0) );
    SetBkColor( (HDC)wParam, RGB( 255, 255, 255) );
    return (LRESULT)Dpincel;

WHEN( WM_PAINT )
    //SetFocus( hwnd );
    PAINTSTRUCT         ps;
    HDC HDc = BeginPaint( hDlg, &ps );
    RECT re;
    re.top = 0;
    re.left = 0;
    re.bottom = 1000;
    re.right = 1000;
    static HBRUSH HBs;
    DeleteObject( HBs );
    HBs = CreateSolidBrush( (COLORREF)0 );
    FillRect( HDc, &re, HBs );
    EndPaint( hDlg, &ps );

WHEN( WM_COMMAND )
    //SetFocus( hwnd );
    IF wParam==2 THEN
       //sprintf( TextoGlobal, "%i", wParam );
       //msgbox( TextoGlobal );
       DeleteObject( SHFont );
       DeleteObject( HBitmapDLG );
       EndDialog( hDlg, TRUE );
    ENDIF;

WHEN( WM_DESTROY )
    DeleteObject( HBitmapDLG );
    DeleteObject( SHFont );
    EndDialog( hDlg, TRUE );
WHEN( WM_CLOSE )
    DeleteObject( HBitmapDLG );
    DeleteObject( SHFont );
    EndDialog( hDlg, TRUE );
WHEN( WM_INITDIALOG )
    char Text2About[2048];
    char Text2AboutHV[2048];
    LoadString( INSTANCIA_GLOBAL, ID_STRING_ABOUT, Text2About, 2047 );
    Text2Edit( Text2AboutHV, Text2About );
    HWND HWEdit;


    SHFont = CreateFont( 18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                         OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                         DEFAULT_PITCH | FF_ROMAN, "Times New Roman" );

    #define WXCorry 59
    #define HYCorry 44

    #define HYEdit 50

    HWEdit = GetDlgItem( hDlg, 100 );
    SendMessage( HWEdit, WM_SETFONT, (WPARAM)SHFont, MAKELPARAM(TRUE, 0) );
    SetWindowText( HWEdit, Text2AboutHV );
    MoveWindow( HWEdit, 1, 368/2+2+HYCorry, 480/2 + 1 + WXCorry, 145 + 49 + HYEdit, TRUE );
    int CXSC = GetSystemMetrics( SM_CXSCREEN );
    int CYSC = GetSystemMetrics( SM_CYSCREEN );
    int WWC = 488/2 + 5 + WXCorry;
    int HHC = 600/2 + 60 + 50 + HYCorry + HYEdit;
    CXSC = (WWC+CXSCREEN)/2 - WWC;
    CYSC = (HHC+CYSCREEN)/2 - HHC;
    MoveWindow( hDlg, CXSC, CYSC, WWC, HHC, TRUE  );

    HWBmp = CreateWindowEx( 0, "STATIC", NULL,
                            WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP,
				            1, 1, 486/2, 363/2, hDlg, NULL, INSTANCIA_GLOBAL, NULL );
    HBitmapDLG = LoadBitmap( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_ABOUT_IMAGE) );
    SendMessage( HWBmp, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HBitmapDLG );
    SetFocus( HWBmp );


DEFAULT
     return FALSE;
ENDMESSAGES
return FALSE;
}
////////////////////////////////////////////////////////////////////////////////
BOOL ABOUT( void ){
HWND HWFather = VENTANA_PADRE;
IF InVista THEN
   EnableWindow( VENTANA_PADRE, FALSE );
   HWFather = HWInVista;
ENDIF;
DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoAbout), HWFather, Dlg_About );
EnableWindow( VENTANA_PADRE, TRUE );
return TRUE;
}
