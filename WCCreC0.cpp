BOOL WCCreC0( HWND HWnd ){
// WCCreC1
char Texto1[256];
HWSel_All_In = CreateWindowEx( 0, "BUTTON", "CANAL UNO",
                            WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                            BS_FLAT | BS_MULTILINE | BS_CENTER,
                            XPosButSend1,
                            6,
                            WRiLine, HPosEditSend1, 
                            HWnd, (HMENU)ID_SH_IN, NULL, NULL );
SetToolTipW( HWSel_All_In, ID_SHOW_HIDE_ALL_IN );
SendMessage( HWSel_All_In, BM_SETCHECK, (WPARAM)(TRUE), 0 );
SendMessage( HWSel_All_In, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) ); 
//
int IXPosWin = WinFuncs.GetWinXPos( HWSel_All_In );
int IYPosWin = WinFuncs.GetWinYPos( HWSel_All_In );

int IWidWin = WinFuncs.GetWinWidth( HWSel_All_In );
int IHeiWin = WinFuncs.GetWinHeight( HWSel_All_In );


HWSel_Chann0_Out = CreateWindowEx( 0, "BUTTON", "SALIDA",
                                  WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                                  BS_FLAT | BS_MULTILINE,
                                  XPosButSend1,
                                  HPosEditSend1 + 13,
                                  65, HPosButSend1,
                                  HWnd, (HMENU)ID_SH_C0_OUT, NULL, NULL );
SetToolTipW( HWSel_Chann0_Out, ID_SHOW_HIDE_OUT_0 );
SendMessage( HWSel_Chann0_Out, BM_SETCHECK, (WPARAM)(TRUE), 0 );
SendMessage( HWSel_Chann0_Out, WM_SETFONT, (WPARAM)HFontButts, MAKELPARAM(TRUE, 0) );








sprintf( Texto1, "%g", B_Val );
HWB_ValB = CreateWindowEx( 0, "BUTTON", "Enviar", WS_CHILD | WS_VISIBLE | WS_BORDER,
                           XPosButSend1,
                           HPosEditSend1 + HPosButSend1 + 15,
                           60, HPosEditSend1, HWnd, (HMENU)ID_SET_BVAL, INSTANCIA_GLOBAL, NULL );
SetToolTipW( HWB_ValB, ID_TOOLTIP_BVALB );
// ShowWindow( HWB_ValB, 0 );





HWCB_SQ_Wave0 = CreateWindowEx( 0, "COMBOBOX", NULL,
                                WS_CHILD | WS_VISIBLE | WS_BORDER  | CBS_DROPDOWNLIST |
                                WS_TABSTOP | WS_VSCROLL,
                                XPosButSend1+40,
                                HPosEditSend1 + HPosButSend1 + 42,
                                WPosButSend1, 120, HWnd, (HMENU)ID_SEL_WV_OUT0, INSTANCIA_GLOBAL, NULL );
SetToolTipW( HWCB_SQ_Wave0, ID_TOOLTIP_TYPE_B );
SendMessage( HWCB_SQ_Wave0, CB_ADDSTRING, 0, (LPARAM)"Escalón" );
SendMessage( HWCB_SQ_Wave0, CB_ADDSTRING, 0, (LPARAM)"Cuadrada" );
SendMessage( HWCB_SQ_Wave0, CB_ADDSTRING, 0, (LPARAM)"Senoidal" );
SendMessage( HWCB_SQ_Wave0, CB_ADDSTRING, 0, (LPARAM)"Triangular" );
SendMessage( HWCB_SQ_Wave0, CB_SETCURSEL, 0, 0 );





IYPosWin = WinFuncs.GetWinYPos( HWSel_Chann0_Out );
HWSel_Color_Chann0_Out = CreateWindowEx( 0, "BUTTON", NULL,
                                         WS_CHILD  | WS_VISIBLE | WS_BORDER |
                                         BS_BITMAP,
                                         XPosButSend1 + 122,
                                         IYPosWin,
                                         65, 20,
                                         HWnd, (HMENU)ID_COLOR_C0_OUT, NULL, NULL );
SendMessage( HWSel_Color_Chann0_Out, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HB_CButt_C[1] );
SetToolTipW( HWSel_Color_Chann0_Out, ID_TOOLTIP_COLOR_OUT0 );



IXPosWin = WinFuncs.GetWinXPos( HWSel_Color_Chann0_Out );
IYPosWin = WinFuncs.GetWinYPos( HWB_ValB );
sprintf( Texto1, "%g", B_Val );
HWB_Val = CreateWindowEx( 0, "EDIT", Texto1, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                         XPosButSend1 + 75 + 1 + 30,
                         IYPosWin,
                         WPosEditSend1,
                         HPosButSend1 - 1,
                         HWnd, (HMENU)ID_E_BVAL, INSTANCIA_GLOBAL, NULL );
SendMessage( HWB_Val, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );
SetToolTipW( HWB_Val, ID_TOOLTIP_BVAL );
//////

IWidWin = WinFuncs.GetWinWidth( HWB_Val );
IHeiWin = WinFuncs.GetWinHeight( HWB_Val );
sprintf( Texto1, "%g", B_Val_Min );
HWB_Val_Min = CreateWindowEx( 0, "EDIT", Texto1, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                         XPosButSend1 + 75 + 1 + IWidWin + 70,
                         IYPosWin,
                         IWidWin,
                         IHeiWin,
                         HWnd, (HMENU)ID_E_BVAL_MIN, INSTANCIA_GLOBAL, NULL );
SendMessage( HWB_Val_Min, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );
SetToolTipW( HWB_Val_Min, ID_TOOLTIP_BVAL_MIN );

// EnableWindow( HWB_Val_Min, FALSE );
SendMessage( HWFs_Out0, CB_SETCURSEL, 0, 0 );
EnableWindow( HWFs_Out0, FALSE );






IYPosWin = WinFuncs.GetWinYPos( HWCB_SQ_Wave0 );
HWFs_Out0 = CreateWindowEx( 0, "COMBOBOX", NULL,
                       WS_CHILD | WS_VISIBLE | WS_BORDER  | CBS_DROPDOWNLIST |
                       WS_TABSTOP | WS_VSCROLL,
                       XPosButSend1 + WPosButSend1 + 90,
                       IYPosWin,
                       70, 364,
                       HWnd, (HMENU)ID_SET_FS_OUT0, INSTANCIA_GLOBAL, NULL );
//SendMessage( HWFs_Out0, WM_SETFONT, (WPARAM)HFontFsSq, MAKELPARAM(TRUE, 0) );
SetToolTipW( HWFs_Out0, ID_TOOLTIP_SQWAVE0_FS );






IYPosWin = WinFuncs.GetWinYPos( HWSel_Chann0_Out );
IWidWin = WinFuncs.GetWinWidth( HWSel_Chann0_Out );
IHeiWin = WinFuncs.GetWinHeight( HWSel_Chann0_Out );
HWSel_Chann0_In = CreateWindowEx( 0, "BUTTON", "ENTRADA",
                                  WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                                  BS_FLAT | BS_MULTILINE,
                                  XPosButSend1 + 4*WPosButSend1 - 115,
                                  IYPosWin,
                                  IWidWin + 14, IHeiWin,
                                  HWnd, (HMENU)ID_SH_C0_IN, NULL, NULL );
SetToolTipW( HWSel_Chann0_In, ID_SHOW_HIDE_IN_0 );
SendMessage( HWSel_Chann0_In, BM_SETCHECK, (WPARAM)(TRUE), 0 );
SendMessage( HWSel_Chann0_In, WM_SETFONT, (WPARAM)HFontButts, MAKELPARAM(TRUE, 0) );



IXPosWin = WinFuncs.GetWinXPos( HWSel_Chann0_In );
IYPosWin = WinFuncs.GetWinYPos( HWSel_Chann0_In );
IWidWin = WinFuncs.GetWinWidth( HWSel_Chann0_In );
IHeiWin = WinFuncs.GetWinHeight( HWSel_Chann0_In );
Input1Status.setLocation( IXPosWin, IYPosWin + 6 + IHeiWin );
Input1Status.setSize( IWidWin, 18 );
Input1Status.setFather( HWnd );

sprintf( Texto1, "In1: %5.5g V", 0.0 );
Input1Status.setText( Texto1 );

Input1Status.setVisible( TRUE );
SendMessage( Input1Status.GetHandle(), WM_SETFONT, (WPARAM)HFontButts, MAKELPARAM(TRUE, 0) );



HWSel_Color_Chann0_In = CreateWindowEx( 0, "BUTTON", NULL,
                                         WS_CHILD  | WS_VISIBLE | WS_BORDER |
                                         BS_BITMAP,
                                         Input1Status.getX(),
                                         Input1Status.getY() + Input1Status.getHeight() + 10,
                                         Input1Status.getWidth(), 20,
                                         HWnd, (HMENU)ID_COLOR_C0_IN, NULL, NULL );
SendMessage( HWSel_Color_Chann0_In, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HB_CButt_C[0] );
SetToolTipW( HWSel_Color_Chann0_In, ID_TOOLTIP_COLOR_IN0 );




EnableWindow( HWB_Val_Min, SetSQWave0!=0 );
return TRUE;
}
