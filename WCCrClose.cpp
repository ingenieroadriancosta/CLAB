BOOL WCCrClose( HWND HWnd ){
// Close.
HWClose = CreateWindowEx( 0, "BUTTON",
                          NULL,
                          WS_CHILD | WS_BORDER | BS_BITMAP,
                          1, 1,
                          48, 20,
                          HWnd, (HMENU)ID_BUTT_CLOSE, NULL, NULL );
HBITMAP HBMPb = LoadBitmap( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_BUTT_CLOSE) );
SendMessage( HWClose, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMPb );
SetToolTipW( HWClose, ID_TOOLTIP_CLOSE );
// Min Tam.
HWResMax = CreateWindowEx( 0, "BUTTON", NULL,
                          WS_CHILD | WS_BORDER | BS_BITMAP,
                          1, 1,
                          20, 20,
                          HWnd, (HMENU)ID_BUTT_RES_MAX, NULL, NULL );
HBMPb = LoadBitmap( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_BUTT_RES_MAX) );
SendMessage( HWResMax, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMPb );
SetToolTipW( HWResMax, ID_TOOLTIP_RES_MAX );
// Minimizar.
HWMin = CreateWindowEx( 0, "BUTTON", NULL,
                          WS_CHILD | WS_BORDER | BS_BITMAP,
                          1, 1,
                          20, 20,
                          HWnd, (HMENU)ID_BUTT_MIN, NULL, NULL );
HBMPb = LoadBitmap( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_BUTT_MIN) );
SendMessage( HWMin, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMPb );
SetToolTipW( HWMin, ID_TOOLTIP_MIN );
return TRUE;
}
