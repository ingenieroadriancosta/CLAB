BOOL Gain = 0;
////// ----->
BOOL SetGain( void ){
BYTE  Msg2TAD[MaxNBTx+1];
Msg2TAD[0] = '{';
Msg2TAD[1] = 151;
Msg2TAD[2] = (BYTE)Gain;
Msg2TAD[MaxNBTx-1] = '}';
// INGFQ
IF Connected THEN
   FOR int i=0; i<MaxNBTx; i++ LOOP
       HSerial.SendByte( Msg2TAD[i] );
       Sleep( 1 );
   ENDLOOP;
ELSIF OpenSerialProc()==1 THEN
   FOR int i=0; i<MaxNBTx; i++ LOOP
       HSerial.SendByte( Msg2TAD[i] );
       Sleep( 1 );
   ENDLOOP;
   HSerial.Close();
ENDIF;


sprintf( TextoGlobal, "Gain, %u", (BYTE)Gain );
msgbox( TextoGlobal );
Gain = !Gain;
return TRUE;
}
