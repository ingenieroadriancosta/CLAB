BOOL INZOOM_OUT = FALSE;
BOOL BN_NOTY_ZOUT = FALSE;
BOOL ZOOM_OUT( void ){
IF INZOOM_OUT || BN_NOTY_ZOUT==FALSE THEN
   return FALSE;
ENDIF;
INZOOM_OUT = TRUE;
//
// msgbox();




// VK_TAB
WHILE( BN_NOTY_ZOUT )
    IF ISDOWNKEY( VK_LBUTTON ) THEN
       WHEEL_PROC( 7864320 );
       Sleep( ISleepV );
    ELSE
       //Sleep( 500 );
       SendMessage( HWCFrame, WM_LBUTTONDOWN, 0, 0 );
    ENDIF;
ENDLOOP;




INZOOM_OUT = FALSE;
return TRUE;
}
