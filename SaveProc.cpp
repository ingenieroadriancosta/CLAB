BOOL SaveProc( void ){




	


HWND HWFath = VENTANA_PADRE;
IF InVista THEN
   //EnableWindow( VENTANA_PADRE, FALSE );
   //HWFath = HWInVista;
ENDIF;


/*

    EnableWindow( HWInVista, TRUE );
    IF InVista THEN
       //EnableWindow( VENTANA_PADRE, TRUE );
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;
    DialogBox( INSTANCIA_GLOBAL, MAKEINTRESOURCE(DialogoPreSave), HWFath, SaveDLG );
    EnableWindow( VENTANA_PADRE, TRUE );
    return FALSE;
//*/

IF SaveFileAs( TDataFile, HWFath )==0 THEN
    return FALSE;
ENDIF;





SAVE_DATA( TDataFile );

return TRUE;
}
