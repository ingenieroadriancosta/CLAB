BOOL WCCreC1( HWND HWnd ){


char Texto1[256];
int IXPosWin = WinFuncs.GetWinXPos( HWSel_All_In );
int IYPosWin = WinFuncs.GetWinYPos( HWSel_All_In );

int IWidWin = WinFuncs.GetWinWidth( HWSel_All_In );
int IHeiWin = WinFuncs.GetWinHeight( HWSel_All_In );

HWSel_All_Out = CreateWindowEx( 0, "BUTTON", "CANAL DOS",
                            WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                            BS_FLAT | BS_MULTILINE | BS_CENTER,
                            IXPosWin + Dist_1_2 + 1,
                            IYPosWin - 1,
                            IWidWin + 2, IHeiWin + 2,
                            HWnd, (HMENU)ID_SH_OUT, NULL, NULL );
SetToolTipW( HWSel_All_Out, ID_SHOW_HIDE_ALL_OUT );
SendMessage( HWSel_All_Out, BM_SETCHECK, (WPARAM)(TRUE), 0 );
// SendMessage( HWSel_All_Out, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );
HFONT HFONT_TEMP = (HFONT)SendMessage( HWSel_All_In, WM_GETFONT, 0, 0 );
SendMessage( HWSel_All_Out, WM_SETFONT, (WPARAM)HFONT_TEMP, MAKELPARAM(TRUE, 0) );
//
IXPosWin = WinFuncs.GetWinXPos( HWSel_Chann0_Out );
IYPosWin = WinFuncs.GetWinYPos( HWSel_Chann0_Out );

IWidWin = WinFuncs.GetWinWidth( HWSel_Chann0_Out );
IHeiWin = WinFuncs.GetWinHeight( HWSel_Chann0_Out );
HWSel_Chann1_Out = CreateWindowEx( 0, "BUTTON", "SALIDA",
                                  WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                                  BS_FLAT | BS_MULTILINE,
                                  IXPosWin + Dist_1_2 + 1,
                                  IYPosWin - 1,
                                  IWidWin + 2, IHeiWin + 2,
                                  HWnd, (HMENU)ID_SH_C1_OUT, NULL, NULL );
SetToolTipW( HWSel_Chann1_Out, ID_SHOW_HIDE_OUT_1 );
SendMessage( HWSel_Chann1_Out, BM_SETCHECK, (WPARAM)(TRUE), 0 );
// SendMessage( HWSel_Chann1_Out, WM_SETFONT, (WPARAM)HFontButts, MAKELPARAM(TRUE, 0) );
HFONT_TEMP = (HFONT)SendMessage( HWSel_Chann0_Out, WM_GETFONT, 0, 0 );
SendMessage( HWSel_Chann1_Out, WM_SETFONT, (WPARAM)HFONT_TEMP, MAKELPARAM(TRUE, 0) );


//
IXPosWin = WinFuncs.GetWinXPos( HWB_ValB );
IYPosWin = WinFuncs.GetWinYPos( HWB_ValB );

IWidWin = WinFuncs.GetWinWidth( HWB_ValB );
IHeiWin = WinFuncs.GetWinHeight( HWB_ValB );
sprintf( Texto1, "%g", B_Val );
HWD_ValB = CreateWindowEx( 0, "BUTTON", "Enviar", WS_CHILD | WS_VISIBLE | WS_BORDER,
                           IXPosWin + Dist_1_2 + 1,
                           IYPosWin - 1,
                           IWidWin+2, IHeiWin+2,
                           HWnd, (HMENU)ID_SET_DVAL, INSTANCIA_GLOBAL, NULL );
SetToolTipW( HWD_ValB, ID_TOOLTIP_DVALB );
//
IXPosWin = WinFuncs.GetWinXPos( HWCB_SQ_Wave0 );
IYPosWin = WinFuncs.GetWinYPos( HWCB_SQ_Wave0 );

IWidWin = WinFuncs.GetWinWidth( HWCB_SQ_Wave0 );
IHeiWin = WinFuncs.GetWinHeight( HWCB_SQ_Wave0 );
HWCB_SQ_Wave1 = CreateWindowEx( 0, "COMBOBOX", NULL,
                                WS_CHILD | WS_VISIBLE | WS_BORDER  | CBS_DROPDOWNLIST |
                                WS_TABSTOP | WS_VSCROLL,
                                IXPosWin + Dist_1_2 + 1,
                                IYPosWin,
                                IWidWin, 120,
                                HWnd, (HMENU)ID_SEL_WV_OUT1, INSTANCIA_GLOBAL, NULL );
SetToolTipW( HWCB_SQ_Wave1, ID_TOOLTIP_TYPE_D );
SendMessage( HWCB_SQ_Wave1, CB_ADDSTRING, 0, (LPARAM)"Escalón" );
SendMessage( HWCB_SQ_Wave1, CB_ADDSTRING, 0, (LPARAM)"Cuadrada" );
SendMessage( HWCB_SQ_Wave1, CB_ADDSTRING, 0, (LPARAM)"Senoidal" );
SendMessage( HWCB_SQ_Wave1, CB_ADDSTRING, 0, (LPARAM)"Triangular" );
SendMessage( HWCB_SQ_Wave1, CB_SETCURSEL, 0, 0 );
//

IXPosWin = WinFuncs.GetWinXPos( HWSel_Color_Chann0_Out );
IYPosWin = WinFuncs.GetWinYPos( HWSel_Color_Chann0_Out );

IWidWin = WinFuncs.GetWinWidth( HWSel_Color_Chann0_Out );
IHeiWin = WinFuncs.GetWinHeight( HWSel_Color_Chann0_Out );
HWSel_Color_Chann1_Out = CreateWindowEx( 0, "BUTTON", NULL,
                                         WS_CHILD  | WS_VISIBLE | WS_BORDER |
                                         BS_BITMAP,
                                         IXPosWin + Dist_1_2 + 1,
                                         IYPosWin-1,
                                         IWidWin + 2, IHeiWin + 2,
                                         HWnd, (HMENU)ID_COLOR_C1_OUT, NULL, NULL );
SendMessage( HWSel_Color_Chann1_Out, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HB_CButt_C[3] );
SetToolTipW( HWSel_Color_Chann1_Out, ID_TOOLTIP_COLOR_OUT1 );
//
IXPosWin = WinFuncs.GetWinXPos( HWB_Val );
IYPosWin = WinFuncs.GetWinYPos( HWB_Val );
IWidWin = WinFuncs.GetWinWidth( HWB_Val );
IHeiWin = WinFuncs.GetWinHeight( HWB_Val );
sprintf( Texto1, "%g", D_Val );
HWD_Val = CreateWindowEx( 0, "EDIT", Texto1, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                         IXPosWin + Dist_1_2 + 1,
                         IYPosWin,
                         IWidWin, IHeiWin,
                         HWnd, (HMENU)ID_E_DVAL, INSTANCIA_GLOBAL, NULL );
SendMessage( HWD_Val, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );
SetToolTipW( HWD_Val, ID_TOOLTIP_DVAL );
//////
IXPosWin = WinFuncs.GetWinXPos( HWB_Val_Min );
IYPosWin = WinFuncs.GetWinYPos( HWB_Val_Min );
IWidWin = WinFuncs.GetWinWidth( HWB_Val_Min );
IHeiWin = WinFuncs.GetWinHeight( HWB_Val_Min );
sprintf( Texto1, "%g", D_Val_Min );
HWD_Val_Min = CreateWindowEx( 0, "EDIT", Texto1, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                              IXPosWin + Dist_1_2 + 1,
                              IYPosWin,
                              IWidWin, IHeiWin,
                              HWnd, (HMENU)ID_E_DVAL_MIN, INSTANCIA_GLOBAL, NULL );
SendMessage( HWD_Val_Min, WM_SETFONT, (WPARAM)HFontComm, MAKELPARAM(TRUE, 0) );
SetToolTipW( HWD_Val_Min, ID_TOOLTIP_DVAL_MIN );
//
SendMessage( HWFs_Out1, CB_SETCURSEL, 0, 0 );
EnableWindow( HWFs_Out1, FALSE );





//
IXPosWin = WinFuncs.GetWinXPos( HWFs_Out0 );
IYPosWin = WinFuncs.GetWinYPos( HWFs_Out0 );
IWidWin = WinFuncs.GetWinWidth( HWFs_Out0 );
IHeiWin = WinFuncs.GetWinHeight( HWFs_Out0 );
HWFs_Out1 = CreateWindowEx( 0, "COMBOBOX", NULL,
                            WS_CHILD | WS_VISIBLE | WS_BORDER  | CBS_DROPDOWNLIST |
                            WS_TABSTOP | WS_VSCROLL,
                            IXPosWin + Dist_1_2 + 1,
                            IYPosWin,
                            IWidWin, 364,
                            HWnd, (HMENU)ID_SET_FS_OUT1, INSTANCIA_GLOBAL, NULL );
//SendMessage( HWFs_Out0, WM_SETFONT, (WPARAM)HFontFsSq, MAKELPARAM(TRUE, 0) );
SetToolTipW( HWFs_Out1, ID_TOOLTIP_SQWAVE1_FS );
//
IXPosWin = WinFuncs.GetWinXPos( HWSel_Chann0_In );
IYPosWin = WinFuncs.GetWinYPos( HWSel_Chann0_In );
IWidWin = WinFuncs.GetWinWidth( HWSel_Chann0_In );
IHeiWin = WinFuncs.GetWinHeight( HWSel_Chann0_In );
HWSel_Chann1_In = CreateWindowEx( 0, "BUTTON", "ENTRADA",
                                  WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE | WS_BORDER |
                                  BS_FLAT | BS_MULTILINE,
                                  IXPosWin + Dist_1_2 + 1,
                                  IYPosWin - 1,
                                  IWidWin + 2, IHeiWin + 2,
                                  HWnd, (HMENU)ID_SH_C1_IN, NULL, NULL );
SetToolTipW( HWSel_Chann1_In, ID_SHOW_HIDE_IN_1 );
SendMessage( HWSel_Chann1_In, BM_SETCHECK, (WPARAM)(TRUE), 0 );
SendMessage( HWSel_Chann1_In, WM_SETFONT, (WPARAM)HFontButts, MAKELPARAM(TRUE, 0) );
//
HWND HWHand = Input1Status.GetHandle();
IXPosWin = WinFuncs.GetWinXPos( HWHand );
IYPosWin = WinFuncs.GetWinYPos( HWHand );
IWidWin = WinFuncs.GetWinWidth( HWHand );
IHeiWin = WinFuncs.GetWinHeight( HWHand );
Input2Status.setLocation( IXPosWin + Dist_1_2 + 1, IYPosWin );
Input2Status.setSize( IWidWin, IHeiWin );
Input2Status.setFather( HWnd );
sprintf( Texto1, "In2: %5.5g V", 0.0 );
Input2Status.setText( Texto1 );
Input2Status.setVisible( TRUE );
SendMessage( Input2Status.GetHandle(), WM_SETFONT, (WPARAM)HFontButts, MAKELPARAM(TRUE, 0) );

//
IXPosWin = WinFuncs.GetWinXPos( HWSel_Color_Chann0_In );
IYPosWin = WinFuncs.GetWinYPos( HWSel_Color_Chann0_In );
IWidWin = WinFuncs.GetWinWidth( HWSel_Color_Chann0_In );
IHeiWin = WinFuncs.GetWinHeight( HWSel_Color_Chann0_In );
HWSel_Color_Chann1_In = CreateWindowEx( 0, "BUTTON", NULL,
                                         WS_CHILD  | WS_VISIBLE | WS_BORDER |
                                         BS_BITMAP,
                                         IXPosWin + Dist_1_2 + 1,
                                         IYPosWin - 1,
                                         IWidWin + 2, IHeiWin + 2,
                                         HWnd, (HMENU)ID_COLOR_C1_IN, NULL, NULL );
SendMessage( HWSel_Color_Chann1_In, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HB_CButt_C[2] );
SetToolTipW( HWSel_Color_Chann1_In, ID_TOOLTIP_COLOR_IN1 );











/*/
int xxx = WinFuncs.GetWinXPos( HWSel_Color_Chann1_In );
int yyy = WinFuncs.GetWinYPos( HWSel_Color_Chann1_In );
int www = WinFuncs.GetWinWidth( HWSel_Color_Chann1_In );
int hhh = WinFuncs.GetWinHeight( HWSel_Color_Chann1_In );
sprintf( TextoGlobal,
         "C0:\n"
         "X  %i\n"
         "Y  %i\n"
         "W  %i\n"
         "H  %i\n\n"
         
         "X  %i\n"
         "Y  %i\n"
         "W  %i\n"
         "H  %i\n\n",
         IXPosWin,
         IYPosWin,
         IWidWin,
         IHeiWin,
         xxx,
         yyy,
         www,
         hhh
          );
msgbox( TextoGlobal );
//*/

//
EnableWindow( HWD_Val_Min, SetSQWave1!=0 );
return TRUE;
}
