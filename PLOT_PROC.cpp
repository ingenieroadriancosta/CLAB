#include "PLOT_PROC0.cpp"

#include "PLOT_PROC1.cpp"

#include "PLOT_PROC2.cpp"

#include "PLOT_PROC3.cpp"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
BOOL PLOT_PROC( void ){
	tic
    IF LineWidth==1 THEN
		PLOT_PROC0();
	ELSIF LineWidth==2 THEN
		PLOT_PROC1();
	ELSIF LineWidth==3 THEN
		PLOT_PROC2();//0.57
	ELSIF LineWidth==4 THEN
		PLOT_PROC3();//0.96
    ENDIF;


    IF !Connected THEN
       FOR int i=0; i<4; i++ LOOP
           IF BuffData[i].Show THEN
              ShowWindow( HWCursor[i], 0 );
              CursorVProc( i );
              ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
              ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
              InvalidateRect( HWCursor[i], NULL, TRUE );
              InvalidateRect( HWCursorInfo[i], NULL, TRUE );
              InvalidateRect( HWCursorText[i], NULL, TRUE );
           ENDIF;
       ENDLOOP;
    ENDIF;



    return TRUE;


	IF !Connected THEN
    	EndToc = toc;
    	char TextoT[1024];
    	sprintf( TextoT, "PLOT_PROC%i:\n\nEndToc, %5.3f", LineWidth-1, EndToc );
    	//SetWindowText( HWCInfo, TextoT );
	ENDIF;
    return TRUE;



    tic
    Pltrs[0].FillGrid( FALSE );


	const int MaxTop = (int)(DTime*FsReal);
	int WFrames = 0;
	//  NFramesReaded = (int)(DTime*FsReal);
	IF Connected THEN
	   Pltrs[0].SetMaxXLim( (double)(EndFrames/FsReal) );
	   WFrames = MaxTop;
	   EndFrames = DiffIE;
	   Pltrs[0].SetMaxXLim( (double)(DTime) );
       Pltrs[0].SetMinXLim( 0 );
    ELSE
       EndFrames = InitFrames + DiffIE;
       IF EndFrames>=MaxTop THEN
          EndFrames = MaxTop;
          InitFrames = EndFrames - DiffIE;
       ENDIF;
       IF InitFrames<0 THEN
          InitFrames = 0;
       ENDIF;

       Pltrs[0].SetMaxXLim( (double)(EndFrames/FsReal) );
       Pltrs[0].SetMinXLim( (double)(InitFrames/FsReal) );
       WFrames = EndFrames - InitFrames;

    ENDIF;




    int         W_Grid = Pltrs[0].GetGraphWidth()-1;
	int         H_Grid = Pltrs[0].GetGraphHeight()-1;

	int         x  = 0;
	int         y  = 0;
	int         Nx = 0;
	int         Ny = 0;



    FOR int Line=0; Line<4; Line++ LOOP
	FOR int Index=InitFrames; Index<EndFrames; Index++ LOOP


        x = (Index-InitFrames)*W_Grid;
		x = x/WFrames;

		y = H_Grid - (H_Grid*BuffData[Line].USData[Index])/65535;


		//Pltrs.setRGB( x, y, InitLineStyle[Line] );
		for( int y1=0; y1<LineWidth; y1++ ){
		     for( int x1=0; x1<LineWidth; x1++ ){
		          Pltrs[0].setRGB( x+x1, y+y1, InitLineStyle[Line] );
             }
        }




		Nx = (Index-InitFrames+1)*W_Grid;
		Nx = Nx/WFrames;
		Ny = H_Grid - (H_Grid*BuffData[Line].USData[Index+1])/65535;


		//
		WHILE( x!=Nx )
			x++;
			Pltrs[0].setRGB( x, y, InitLineStyle[Line] );
		ENDWHILE;


        WHILE( y>Ny )
					y--;
					IF y<0 THEN
						goto ENDY;
					ENDIF;
					Pltrs[0].setRGB( x, y, InitLineStyle[Line] );
				ENDWHILE;



				WHILE( y!=Ny )
					y++;
					IF y>=H_Grid THEN
						goto ENDY;
					ENDIF;
					Pltrs[0].setRGB( x, y, InitLineStyle[Line] );
				ENDWHILE;



		ENDY:
		y = 0;
	ENDLOOP;
	    // ENDLINE:
        y = 0;
	ENDLOOP;
	//
	Pltrs[0].FillBuff();


	EndToc = toc;
    char TextoT[1024];
    sprintf( TextoT, "PLOT_PROC:\n\nEndToc, %f", EndToc );
    //SetWindowText( HWCInfo, TextoT );

    return TRUE;
}
