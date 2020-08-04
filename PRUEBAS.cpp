BOOL InPrb = FALSE;
////////////////////////////////////////////////////////////////////////////////
BOOL PRUEBAS( void ){
IF InPrb THEN
   return FALSE;
ENDIF;
InPrb= TRUE;
//sprintf( TextoGlobal, "%u", Divisor );
//msgbox( TextoGlobal );
/*
IF PltrNDiv==0 THEN
   HWND HWndP = Pltrs[0].GetHandleCon();
   // Pltrs[0].isDockF();
   IF Pltrs[0].Dock() THEN
      SendMessage( HWndP, WM_LBUTTONDBLCLK, 12345, 12345 );
   ELSE
      IF Wmaximized THEN
         maximizar( VENTANA_PADRE );
         maximizar( VENTANA_PADRE );
      ELSE
         ShowWindow( VENTANA_PADRE, 1 );
         Sleep( 100 );
         ShowWindow( VENTANA_PADRE, 3 );
      ENDIF;
   ENDIF;
   Pltrs[0].Inval();
ENDIF;
//*/
InPrb= FALSE;
return TRUE;
}
