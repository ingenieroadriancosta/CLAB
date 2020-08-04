#define ISleepV 150
BOOL INZOOM_IN = FALSE;
BOOL BN_NOTY_ZIN = FALSE;
BOOL ZOOM_IN( void ){

IF INZOOM_IN || BN_NOTY_ZIN==FALSE THEN
   return FALSE;
ENDIF;
INZOOM_IN = TRUE;
//
// msgbox();
WHILE( BN_NOTY_ZIN )
    IF ISDOWNKEY( VK_LBUTTON ) THEN
       WHEEL_PROC( -7864320 );
       Sleep( ISleepV );
    ELSE
       //Sleep( 500 );
       SendMessage( HWCFrame, WM_LBUTTONDOWN, 0, 0 );
    ENDIF;
ENDLOOP;


// SendMessage( HWPanel, WM_LBUTTONDOWN, 0, 0 );
//SendMessage( HWCFrame, WM_LBUTTONDOWN, 0, 0 );
// SetFocus( HWTs );


INZOOM_IN = FALSE;
return TRUE;
}
