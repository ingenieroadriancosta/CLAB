#include "VarsVista.cpp"
#include "CreateVista.cpp"
#include "PintVistaP.cpp"
BOOL CALLBACK DLG_VISTA( HWND hDlg, UINT  message, WPARAM wParam, LPARAM lParam ){
//
IF PostQuit THEN
   EndDialog( hDlg, IDOK );
   return FALSE;
ENDIF;
//
IF message==WM_MOUSEMOVE THEN
   SetLayeredWindowAttributes( hDlg, 0, 255, LWA_ALPHA );
   return FALSE;
ENDIF;
//
MESSAGES
WHEN( WM_COMMAND )
    SetLayeredWindowAttributes( hDlg, 0, 255, LWA_ALPHA );
    IF LOWORD(wParam)==2 THEN
       BVista.setSelected( FALSE );
       DeleteObject( HIconVista );
       WindowPos( hDlg, &XVist, &YVist );
       InVista = FALSE;
       HWInVista = NULL;
       EndDialog( hDlg, IDOK );
    ELSIF LOWORD(wParam)!=0 THEN
       
       IF LOWORD(wParam)>=ID_GRID_STYLE0 && LOWORD(wParam)<=ID_GRID_STYLE3 THEN
          SendMessage( GetDlgItem( hDlg, ID_GRID_ON ), BM_SETCHECK, (WPARAM)(TRUE), 0 );
       ENDIF;
       
       SendMessage( VENTANA_PADRE, message, wParam, lParam );
       //EndDialog( hDlg, IDOK );
    ENDIF;
    
WHEN( WM_INITDIALOG )
    HWInVista = hDlg;
    BVista.setSelected( TRUE );
    InVista = TRUE;
    CreateVista( hDlg );
    EnableWindow( VENTANA_PADRE, TRUE );
    SetLayeredWindowAttributes( hDlg, 0, 255, LWA_ALPHA );
WHEN( WM_ENTERSIZEMOVE )
    SetLayeredWindowAttributes( hDlg, 0, VALPHA_VISTA, LWA_ALPHA );
WHEN( WM_EXITSIZEMOVE )
    SetLayeredWindowAttributes( hDlg, 0, 255, LWA_ALPHA );
WHEN( WM_NCMOUSEMOVE )
    SetLayeredWindowAttributes( hDlg, 0, 255, LWA_ALPHA );
WHEN( WM_SETFOCUS )
    //SetLayeredWindowAttributes( hDlg, 0, 100, LWA_ALPHA );
WHEN( WM_PAINT )
    PintVistaP( hDlg );
WHEN( WM_CLOSE )
    BVista.setSelected( FALSE );
    DeleteObject( HIconVista );
    WindowPos( hDlg, &XVist, &YVist );
    InVista = FALSE;
    HWInVista = NULL;
    EndDialog( hDlg, IDCANCEL );
WHEN( WM_DESTROY )
    BVista.setSelected( FALSE );
    InVista = FALSE;
    HWInVista = NULL;
    EndDialog( hDlg, IDCANCEL );
DEFAULT
     return FALSE;
ENDMESSAGES
return FALSE;
}
