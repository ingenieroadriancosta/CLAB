BOOL InClearAll = FALSE;

BOOL CLEAR_ALL( void ){
IF InClearAll THEN
   return FALSE;
ENDIF;
InClearAll = TRUE;

memset( (void*)&BuffData[0].USData[0], 0, MaxBuffs*sizeof(short) );
memset( (void*)&BuffData[1].USData[0], 0, MaxBuffs*sizeof(short) );
memset( (void*)&BuffData[2].USData[0], 0, MaxBuffs*sizeof(short) );
memset( (void*)&BuffData[3].USData[0], 0, MaxBuffs*sizeof(short) );

PosBuff[0] = 0;
PosBuff[1] = (DTime*Fs)/4;
PosBuff[2] = (2*DTime*Fs)/4;
PosBuff[3] = (3*DTime*Fs);

InClearAll = FALSE;
return TRUE;

FOR int IC=0; IC<4; IC++ LOOP
    FOR int i=0; i<MaxBuffs; i++ LOOP
        //BuffData[IC].USData[i] = (BYTE)0;
    ENDLOOP;
ENDLOOP;

PLOT_PROC();

InClearAll = FALSE;
return TRUE;
}
