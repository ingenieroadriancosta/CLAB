BOOL Valid_File( char* FileIn1, LPSTR lpszArgument ){
char* FileIn = lpszArgument;
IF FileIn[0]=='"' THEN
   FOR int i=0; i<255; i++ LOOP
       FileIn1[i] = FileIn[i+1];
       IF FileIn1[i]=='"' THEN
          FileIn1[i] = 0;
          break;
       ENDIF;
   ENDLOOP;
ELSE
   return FALSE;
ENDIF;
return TRUE;
}
