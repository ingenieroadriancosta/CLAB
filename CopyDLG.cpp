BOOL               CHannSaveCPY[4];
////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK CopyDLG( HWND hDlg, UINT  message, WPARAM wParam, LPARAM lParam ){
static HBRUSH PI0_DLG;
static char TextoCab[512];
MESSAGES
WHEN( WM_COMMAND )
    IF LOWORD(wParam)==141 THEN
       EndDialog( hDlg, IDCANCEL );
    ELSIF LOWORD(wParam)==140 THEN
       
       FOR int i=0; i<4; i++ LOOP
           CHannSaveCPY[i] = SendMessage( GetDlgItem( hDlg, 128 + i ), BM_GETCHECK, 0, 0 )==BST_CHECKED;
       ENDLOOP;
       
       EndDialog( hDlg, IDOK );
    ELSE
       char Texto1[512];
       //sprintf( Texto1, "Datos que se exportaran:\nTiempo\n" );
       strcpy( Texto1, TextoCab );
       char Texto2[512];
       FOR int i=0; i<4; i++ LOOP
           IF SendMessage( GetDlgItem( hDlg, 128 + i ), BM_GETCHECK, 0, 0 )==BST_CHECKED THEN
              GetWindowTextA( GetDlgItem( hDlg, 128 + i ), Texto2, 256 );
              strcat( Texto2, "\n" );
              strcat( Texto1, Texto2 );
           ENDIF;
       ENDLOOP;
       SetWindowText( GetDlgItem( hDlg, 10 ), Texto1 );
    ENDIF;
WHEN( WM_CTLCOLORSTATIC )
        DeleteObject( PI0_DLG );
        PI0_DLG = CreateSolidBrush( RGB( 255, 255, 255 ) );
        SetTextColor( (HDC)wParam, RGB( 0, 0, 0 ) );
        SetBkColor( (HDC)wParam, RGB( 255, 255, 255 ) );
        return (LRESULT)PI0_DLG;
WHEN( WM_INITDIALOG )
    FOR int i=0; i<4; i++ LOOP
        SendMessage( GetDlgItem( hDlg, 128 + i ), BM_SETCHECK, (WPARAM)(CHannSaveCPY[i]), 0 );
    ENDLOOP;
    
    GetWindowTextA( GetDlgItem( hDlg, 10 ), TextoCab, 256 );
    
    int CXSC = GetSystemMetrics( SM_CXSCREEN );
    int CYSC = GetSystemMetrics( SM_CYSCREEN );
    int WWC = 295;
    int HHC = 210;
    CXSC = (WWC+CXSCREEN)/2 - WWC;
    CYSC = (HHC+CYSCREEN)/2 - HHC;
    MoveWindow( hDlg, CXSC, CYSC, WWC, HHC, TRUE  );
    SendMessage( hDlg, WM_COMMAND, 255, 0 );
    SetFocus( GetDlgItem( hDlg, 140 ) );
WHEN( WM_CLOSE )
    DeleteObject( PI0_DLG );
    EndDialog( hDlg, IDCANCEL );
WHEN( WM_DESTROY )
    DeleteObject( PI0_DLG );
    EndDialog( hDlg, IDCANCEL );
DEFAULT
     return FALSE;
ENDMESSAGES
return FALSE;
}

