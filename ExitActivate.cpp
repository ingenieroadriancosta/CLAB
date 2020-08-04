DWORD WINAPI ExitActivate( LPVOID pv=NULL ){

const int MaxTop = (int)(DTime*FsReal);
IF DiffIE!=MaxTop THEN
   SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCurDHand );
ENDIF;

Pltrs[0].SetDoubleBuff( TRUE );
Pltrs[1].SetDoubleBuff( TRUE );

WHILE( ISDOWNKEY( VK_LBUTTON ) && MActivate && !CActivate )
     Sleep( 100 );
ENDLOOP;

IF DiffIE!=MaxTop THEN
   SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCurHand );
ELSE
   SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );
ENDIF;
MActivate = FALSE;
//msgbox();
return 0;
}
