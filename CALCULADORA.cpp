BOOL InCalc = FALSE;
BOOL ResetCalc = FALSE;
BOOL CALCULADORA( void ){
IF InCalc THEN
   ResetCalc = TRUE;
   return FALSE;
ENDIF;



InCalc = TRUE;
WHILE(!GLOBALQUIT_GLOBAL)
    IF env==NULL THEN
       //EnableWindow( VENTANA_PADRE, FALSE);
       MainJVM();
       // env->CallStaticVoidMethod( cls, mid, NULL);
       //EnableWindow( VENTANA_PADRE, TRUE);
    ELSE
       env->CallStaticVoidMethod( cls, mid2, 0);
    ENDIF;
    ResetCalc = FALSE;
    WHILE(!ResetCalc)
        Sleep(100);
    ENDLOOP;
ENDLOOP;




return TRUE;
}
