BOOL MoveCursor( int CPosX, int CPosY, int CurCW=0 ){
CurCW = 3&CurCW;
int    WPlot = Pltrs[0].GetGraphWidth() - 1;
int    HPlot = Pltrs[0].GetGraphHeight() - 1;

int    XXXP = 0;
int    YYYP = 0;

IF CPosX<WCRre.right THEN
   XXXP = 0;
ELSIF CPosX>WPlot-WCRre.right THEN
   XXXP = WPlot - WCRre.right+1;
ELSE
   XXXP = CPosX - WCRre.right/2;
ENDIF;

IF CPosY<WCRre.bottom THEN
   YYYP = 0;
ELSIF CPosY>HPlot-WCRre.bottom THEN
   YYYP = HPlot - WCRre.bottom;
ELSE
   YYYP = CPosY - WCRre.bottom/2;
ENDIF;

MoveWindow( HWCursor[CurCW], XXXP, YYYP, WCRre.right, WCRre.bottom, TRUE );

IF XXXP>WPlot/2 THEN
   XXXP = XXXP - WTextCur;
ELSE
   XXXP = XXXP + 10;
ENDIF;

IF YYYP>HPlot/2 THEN
   YYYP = YYYP - HTextCur;
ELSE
   YYYP = YYYP + 10;
ENDIF;
MoveWindow( HWCursorInfo[CurCW], XXXP, YYYP, WTextCur, HTextCur, TRUE );
return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL CursorVProc( int InBuff ){

int VoltDiv;
IF InBuff%2==0 THEN
   VoltDiv = 1023;
ELSE
   VoltDiv = 255;
ENDIF;




IF PosBuff[InBuff]>=DiffIE+InitFrames THEN
   PosBuff[InBuff] = InitFrames + DiffIE;
ELSIF PosBuff[InBuff]<InitFrames THEN
   PosBuff[InBuff] = InitFrames;
ENDIF;



double VoltC;
double SegC;

int    WPlot = Pltrs[0].GetGraphWidth() - 1;
int    HPlot = Pltrs[0].GetGraphHeight() - 1;
double DXVal = (double)(PosBuff[InBuff]);
SegC = DXVal/FsReal;

DXVal = (WPlot*(DXVal-InitFrames))/DiffIE;
int XPos = (int)(floor(DXVal));



double DYVal = (double)BuffData[InBuff].USData[PosBuff[InBuff]];
double VoltScale = 0;


VoltC = (Volt_In_Out[InBuff]*DYVal)/VoltDiv;
VoltScale = Volt_In_Out[InBuff]/Max_Volt;






DYVal = (VoltScale*HPlot*DYVal)/VoltDiv;
DYVal = HPlot - DYVal;

int YPos = (int)(floor(DYVal));

MoveCursor( XPos, YPos, InBuff );


/*
VoltC = round( 10000*VoltC );
VoltC = VoltC/10000;
//*/
VoltC = round( 10000*VoltC );
VoltC = VoltC/10000;





char TextoT[1024];
sprintf( TextoT, "X:%5.5f\nY:%g", SegC, VoltC );
SetWindowText( HWCursorText[InBuff], TextoT );



IF InBuff%2==0 THEN
   // const double P10 = 10000.0;
   int CurMp = 1&(InBuff/2);
   //
   double V2Inf = 0.00000000000000000000000000000001;
   IF BuffData[InBuff].USData[PosBuff[InBuff]]>0 THEN
      V2Inf = (double)BuffData[InBuff].USData[PosBuff[InBuff]];
   ELSE
      V2Inf = -0.00000000000000000000000000000001;
   ENDIF;
   //
   double ActV = ( (double)USMpActual[CurMp] - V2Inf );
   ActV = ActV/V2Inf;
   //ActV = ActV/( V2Inf );
   //ActV = ( Volt_In_Out[2*CurMp]*ActV )/VoltDiv;

   ActV = 100 * ActV;
   //
   sprintf( TextoT, "Mp%i: %5.2f%% ", (CurMp+1), ActV );
   Mp[CurMp].setText( TextoT );


   double DatEp = (double)BuffData[S_EP1122[CurMp]].USData[PosBuff[InBuff]];
   //DatEp = (1023 * DatEp)/255;
   DatEp = (Volt_In_Out[S_EP1122[CurMp]]*DatEp)/255;
   IF (DatEp<=0) THEN
      DatEp = 0.00000000000000000000000000000001;
   ENDIF;

   V2Inf = VoltC;
   IF (V2Inf<=0) THEN
      V2Inf = 0.00000000000000000000000000000001;
   ENDIF;
   //V2Inf = ( Volt_In_Out[2*CurMp + 1]*V2Inf )/255;
   ActV = ( DatEp - V2Inf )/DatEp;
   //ActV = ( Volt_In_Out[2*CurMp]*ActV )/VoltDiv;
   ActV = abs( 100 * ActV );
   sprintf( TextoT, "Ep%i: %5.2f%% ", (CurMp+1), ActV );
   Ep[CurMp].setText( TextoT );


ENDIF;
///
///
InvalidateRect( HWCursor[InBuff], NULL, TRUE );
InvalidateRect( HWCursorInfo[InBuff], NULL, TRUE );
InvalidateRect( HWCursorInfo[InBuff], NULL, TRUE );

return TRUE;
}
