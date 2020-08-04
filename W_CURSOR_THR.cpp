DWORD WINAPI CursorActivate( LPVOID pv=NULL ){

HCURSOR HCurActual = (HCURSOR)GetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR );

int CurCW = (int)pv;


SetFocus( HWCursor[0] );


int CPosX = 0;
int CPosY = 0;
int CPosXR = 0;
int CPosYR = 0;
int WPosX = 0;
int WPosY = 0;



int BufPos = 0;
const double DWRel = floor(DiffIE);
const int    WPlot = Pltrs[0].GetGraphWidth() - 1;
const int    HPlot = Pltrs[0].GetGraphHeight() - 1;
HCURSOR HCursor = LoadCursor( NULL, IDC_SIZEALL );
SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursor );
SetClassLongA( HWCursorInfo[0], GCL_HCURSOR, (LONG)HCursor );

// char TextoT[1024];
// double XVal = 0;
// double YVal = 0;





WHILE( ISDOWNKEY( VK_LBUTTON ) && CActivate )
     Sleep( 50 );
     CursorPos( (int*)&CPosX, (int*)&CPosY );
     WindowPos( VENTANA_PADRE, (int*)&WPosX, (int*)&WPosY );

     //  CPosX = (CPosX - WPosX - 1 - 40 );

     //CPosX = (CPosX - WPosX - 1 - 40 + 39 );

     IF Pltrs[0].isDockF() THEN
        WPosX = -3;
        WPosY = -2;
     ENDIF;

     CPosX = (CPosX - WPosX - 41  );


     //CPosY = (CPosY - WPosY - 102 - 38 );
     CPosY = (CPosY - WPosY - 102 - 38 );

     IF CPosX<0 THEN
        CPosXR++;
        CPosXR = 0;
     ELSIF CPosX>WPlot THEN
        CPosXR = WPlot;
     ELSE
        CPosXR = CPosX;
     ENDIF;
     ////
     IF CPosY<0 THEN
        CPosYR++;
        CPosYR = 0;
     ELSIF CPosY>HPlot THEN
        CPosYR = HPlot;
     ELSE
        CPosYR = CPosY;
     ENDIF;

     BufPos = (int)(floor((CPosX*DWRel)/WPlot));
     IF BufPos<0 THEN
        BufPos = 0;
     ELSIF BufPos>DWRel THEN
        BufPos = (int)(DWRel);
     ENDIF;

     BufPos = BufPos + InitFrames;
     PosBuff[CurCW] = BufPos;
     CursorVProc( CurCW );
ENDLOOP;
DeleteObject( HCursor );

SetClassLongA( HWCursorInfo[0], GCL_HCURSOR, (LONG)HCursorG );
//ReleaseCapture();


// SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );
//SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCurHand );
SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCurActual );


CActivate = FALSE;
// msgbox();
return 0;
}
