char WTitleSV[256];
int OrdN;
double VaG2DLG = 0;
BOOL CALLBACK Dlg_SetAmps(HWND hDlg, UINT  message, WPARAM wParam, LPARAM lParam){
static HFONT SAHFont;
static HWND HWndEdit;
MESSAGES
WHEN( WM_COMMAND )
    IF LOWORD(wParam)==2 THEN
       DeleteObject( SAHFont );
       EndDialog( hDlg, IDCANCEL );
    ELSIF LOWORD(wParam)==IDOK THEN
       char DValChar[256];
       double DVal2 = 0;
       GetWindowText( HWndEdit, DValChar, 255 );
       DVal2 = atof( DValChar );
       IF DVal2<0.00000001 THEN
          msgbox( "Valor invalido.", " Error ", 16 );
          break;
       ENDIF;
       
       Volt_In_Out[OrdN] = DVal2;
       
       
       DeleteObject( SAHFont );
       EndDialog( hDlg, IDOK );
    ENDIF;
WHEN( WM_DESTROY )
    DeleteObject( SAHFont );
    EndDialog( hDlg, IDCANCEL );
WHEN( WM_CLOSE )
    DeleteObject( SAHFont );
    EndDialog( hDlg, IDCANCEL );
WHEN( WM_INITDIALOG )
    SetWindowText( hDlg, WTitleSV );
    SAHFont = CreateFont( 38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                         OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                         DEFAULT_PITCH | FF_ROMAN, "Times New Roman" );
    HWndEdit = GetDlgItem( hDlg, 256 );
    SendMessage( HWndEdit, WM_SETFONT, (WPARAM)SAHFont, MAKELPARAM(TRUE, 0) );
    
    
    sprintf( WTitleSV, "%g", VaG2DLG );
    SetWindowText( HWndEdit, WTitleSV );
    
    int CXSC = GetSystemMetrics( SM_CXSCREEN );
    int CYSC = GetSystemMetrics( SM_CYSCREEN );
    int WWC = 220;
    int HHC = 86;
    CXSC = (WWC+CXSCREEN)/2 - WWC;
    CYSC = (HHC+CYSCREEN)/2 - HHC;
    
    MoveWindow( hDlg, CXSC, CYSC, WWC, HHC, TRUE  );
	//*/
DEFAULT
     return FALSE;
ENDMESSAGES
return FALSE;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL SET_AMPS( BYTE BAmpOrd ){
OrdN = BAmpOrd - ID_AMP_0;
int Order12 = 0;
char Tex2WT[512];
CASE( BAmpOrd )IS
	WHEN(ID_AMP_0)
		LoadString( INSTANCIA_GLOBAL, ID_STRING_TITLE_SV_IN, Tex2WT, 255 );
		Order12 = 1;
        VaG2DLG = Volt_In_Out[0];
	WHEN(ID_AMP_1)
		LoadString( INSTANCIA_GLOBAL, ID_STRING_TITLE_SV_OUT, Tex2WT, 255 );
		Order12 = 1;
        VaG2DLG = Volt_In_Out[1];
	WHEN(ID_AMP_2)
		LoadString( INSTANCIA_GLOBAL, ID_STRING_TITLE_SV_IN, Tex2WT, 255 );
		Order12 = 2;
        VaG2DLG = Volt_In_Out[2];
	WHEN(ID_AMP_3)
		LoadString( INSTANCIA_GLOBAL, ID_STRING_TITLE_SV_OUT, Tex2WT, 255 );
		Order12 = 2;
        VaG2DLG = Volt_In_Out[3];
	DEFAULT
		return FALSE;
ENDCASE;


HWND HWFath = VENTANA_PADRE;
EnableWindow( VENTANA_PADRE, FALSE );
IF InVista THEN
   HWFath = HWInVista;
ENDIF;

sprintf( WTitleSV, Tex2WT, Order12 );
IF DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoAmp), HWFath, Dlg_SetAmps )==IDOK THEN
   Max_Volt = 0;
   FOR int i=0; i<4; i++ LOOP
       Max_Volt = max( Max_Volt, Volt_In_Out[i] );
   ENDLOOP;
   Max_Volt = ceil( Max_Volt );
   
   Pltrs[0].SetMaxYLim( Max_Volt );
   Pltrs[1].SetMaxYLim( Max_Volt );
   Pltrs[0].Inval();
   Pltrs[1].Inval();
   
   
   
   PLOT_PROC();
   
ENDIF;
EnableWindow( VENTANA_PADRE, TRUE );



//  4.5308











return TRUE;
}



