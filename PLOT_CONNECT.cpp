HANDLE H_CONNECT;
DWORD IdThPlt = 0;
HANDLE H_Plt_Cnn;
BOOL ExePlot;
//////------------>
DWORD WINAPI PLOT_CONNECT( LPVOID pv=NULL ){
/*
// ExitThread( IdThPlt );
Pltrs[0].SetDoubleBuff( TRUE );
Pltrs[1].SetDoubleBuff( TRUE );
PLOT_PROC();
SetPlot = FALSE;
return 0;
//*/

ExePlot = FALSE;

TimeStatus.setVisible( TRUE );
Input1Status.setVisible( TRUE );
Input2Status.setVisible( TRUE );



PLOT_PROC();
WHILE( ( Connected ) && !GLOBALQUIT_GLOBAL )

    IF SetPlotRes THEN
       SetPlotRes = FALSE;
       FOR int i=0; i<2*PltrNDiv; i++ LOOP
           Pltrs[i].FillGrid();
           Pltrs[i].SetDoubleBuff( TRUE );
       ENDLOOP;

       Pltrs[0].SetVisible( TRUE );
       IF PltrNDiv!=0 THEN
          Pltrs[1].SetVisible( TRUE );
       ENDLOOP;

    ELSIF SetPlot THEN
       Pltrs[0].SetDoubleBuff( TRUE );
       Pltrs[1].SetDoubleBuff( TRUE );
       //Pltrs[0].SetDoubleBuff( FALSE );
       //Pltrs[1].SetDoubleBuff( FALSE );
       PLOT_PROC();
       SetPlot = FALSE;
       ExePlot = FALSE;
    ENDIF;
    Sleep( 10 );
ENDWHILE;

/*
TimeStatus.setVisible( FALSE );
Input1Status.setVisible( FALSE );
Input2Status.setVisible( FALSE );
//*/
return 0;
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

DWORD WINAPI SEG_CONNECT( LPVOID pv=NULL ){
int Cnt2Seg = 0;
int Cnt2SegPlt = 0;
TimeStatus.setVisible( TRUE );
Input1Status.setVisible( TRUE );
Input2Status.setVisible( TRUE );
char TextoT[256];
double EndTocP = 0;
TimeStatus.setText( "T: 000 seg" );
WHILE( Connected && !GLOBALQUIT_GLOBAL )
    EndTocP = tocCNN();
    IF EndTocP>0.05 THEN
       Cnt2SegPlt++;
       IF Cnt2SegPlt>0 && SetPlot && !ExePlot  THEN
          ExePlot = TRUE;
          Cnt2SegPlt = 0;
       ENDIF;


       Cnt2Seg++;

       IF Cnt2Seg%4==0 THEN
          sprintf( TextoT, "In1: %5.5g V", A0_Val );
          Input1Status.setText( TextoT );

          //sprintf( TextoT, "%i", MBAvailable );
          sprintf( TextoT, "In2: %5.5g V", A1_Val );
          Input2Status.setText( TextoT );
       ENDIF;


       IF Cnt2Seg>=8 THEN
          Cnt2Seg = (int)floor(DiffIE/FsReal);
          IF Cnt2Seg<10 THEN
             sprintf( TextoT, "T: 00%i seg", Cnt2Seg );
          ELSIF Cnt2Seg<100 THEN
             sprintf( TextoT, "T: 0%i seg", Cnt2Seg );
          ELSE
             sprintf( TextoT, "T: %i seg", Cnt2Seg );
          ENDIF;
          TimeStatus.setText( TextoT );
          Cnt2Seg = 0;
       ENDIF;


       ticCNN();
    ENDIF;
    Sleep( 10 );
ENDWHILE;
/*
TimeStatus.setVisible( FALSE );
Input1Status.setVisible( FALSE );
Input2Status.setVisible( FALSE );
// ExitThread( IdThPlt );
// TerminateThread
//*/
return 0;
}
