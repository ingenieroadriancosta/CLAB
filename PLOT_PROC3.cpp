BOOL PLOT_PROC3( void ){
	int  ConstDiv = PltrNDiv + 1;
	int  MaxConstDiv = PltrNDiv + 1;
	//sprintf( TextoGlobal, "ConstDiv, %i\nMaxConstDiv, %i\n", ConstDiv, MaxConstDiv );
	//msgbox( TextoGlobal );
	const int MaxTop = (int)(DTime*FsReal);
	int WFrames = MaxTop;

	FOR int Line=0; Line<MaxConstDiv; Line++ LOOP
        Pltrs[Line].FillGrid( FALSE );

		IF Connected THEN
			Pltrs[Line].SetMaxXLim( (double)(EndFrames/FsReal) );
			WFrames = MaxTop;
			EndFrames = DiffIE;
			Pltrs[Line].SetMaxXLim( (double)(DTime) );
			Pltrs[Line].SetMinXLim( 0 );
		ELSE
			EndFrames = InitFrames + DiffIE;
			IF EndFrames>=MaxTop THEN
				EndFrames = MaxTop;
				InitFrames = EndFrames - DiffIE;
			ENDIF;
			IF InitFrames<0 THEN
				InitFrames = 0;
			ENDIF;

			Pltrs[Line].SetMaxXLim( (double)(EndFrames/FsReal) );
			Pltrs[Line].SetMinXLim( (double)(InitFrames/FsReal) );
			WFrames = EndFrames - InitFrames;

		ENDIF;
    ENDLOOP;





	// Divisor = 1023;
    IF Divisor!=255 && Divisor!=1023 THEN
       Divisor = 255;
    ENDIF;




	int         W_Grid = Pltrs[0].GetGraphWidth()-1;
	int         H_Grid = Pltrs[0].GetGraphHeight()-1;

	int         x;
	int         y;
	int         Nx;
	int         Ny;

	int DivScale = 1023;
	double VoltScale = 0;

	int EndFr = EndFrames - 1;
	FOR int Line=0; Line<4; Line++ LOOP
		IF !BuffData[Line].Show THEN
            goto ENDLINE_PLOT_3;
		ENDIF;



		IF PltrNDiv<1 THEN
			ConstDiv = 0;
		ELSE
			ConstDiv = (3 - PltrNDiv);
			ConstDiv = Line/ConstDiv;
		ENDIF;


		VoltScale = Volt_In_Out[Line]/Max_Volt;


		IF Line%2==0 THEN
            DivScale = 1023;
		ELSE
            DivScale = Divisor;
		ENDIF;



        FOR int Index=InitFrames; Index<EndFrames; Index++ LOOP


			x = (Index-InitFrames)*W_Grid;
			x = x/WFrames;
			y = H_Grid - (int)((VoltScale*H_Grid*BuffData[Line].USData[Index])/DivScale);

			/*
			Pltrs.setRGB( x-2, y-2, LineColors[Line] );
			Pltrs.setRGB( x-1, y-2, LineColors[Line] );
			Pltrs.setRGB( x, y-2, LineColors[Line] );
			Pltrs.setRGB( x+1, y-2, LineColors[Line] );
			Pltrs.setRGB( x+2, y-2, LineColors[Line] );

			Pltrs.setRGB( x-2, y-1, LineColors[Line] );
			Pltrs.setRGB( x-1, y-1, LineColors[Line] );
			Pltrs.setRGB( x, y-1, LineColors[Line] );
			Pltrs.setRGB( x+1, y-1, LineColors[Line] );
			Pltrs.setRGB( x+2, y-1, LineColors[Line] );


			Pltrs.setRGB( x-2, y, LineColors[Line] );
			Pltrs.setRGB( x-1, y, LineColors[Line] );
			Pltrs.setRGB( x, y, LineColors[Line] );
			Pltrs.setRGB( x+1, y, LineColors[Line] );
			Pltrs.setRGB( x+2, y, LineColors[Line] );


			Pltrs.setRGB( x-2, y+1, LineColors[Line] );
			Pltrs.setRGB( x-1, y+1, LineColors[Line] );
			Pltrs.setRGB( x, y+1, LineColors[Line] );
			Pltrs.setRGB( x+1, y+1, LineColors[Line] );
			Pltrs.setRGB( x+2, y+1, LineColors[Line] );

			Pltrs.setRGB( x-2, y+2, LineColors[Line] );
			Pltrs.setRGB( x-1, y+2, LineColors[Line] );
			Pltrs.setRGB( x, y+2, LineColors[Line] );
			Pltrs.setRGB( x+1, y+2, LineColors[Line] );
			Pltrs.setRGB( x+2, y+2, LineColors[Line] );
			//*/

			Pltrs[ConstDiv].setRGB( x, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+1, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+2, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+3, y, LineColors[Line] );

			Pltrs[ConstDiv].setRGB( x, y+1, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+1, y+1, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+2, y+1, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+3, y+1, LineColors[Line] );

			Pltrs[ConstDiv].setRGB( x, y+2, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+1, y+2, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+2, y+2, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+3, y+2, LineColors[Line] );



			Pltrs[ConstDiv].setRGB( x, y+3, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+1, y+3, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+2, y+3, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+3, y+3, LineColors[Line] );
			//*/


			Nx = (Index-InitFrames+1)*W_Grid;
			Nx = Nx/WFrames;
			Ny = H_Grid - (int)((VoltScale*H_Grid*BuffData[Line].USData[Index+1])/DivScale);

			//
			WHILE( x!=Nx )
				x++;

				IF DiffIE<200 THEN
					for( int y1=0; y1<2; y1++ ){
		                 for( int x1=0; x1<2; x1++ ){
		                      Pltrs[ConstDiv].setRGB( x+x1, y+y1, LineColors[Line] );
                         }
                    }
				ELSE
					//Pltrs.setRGB( x, y, LineColors[Line] );

			Pltrs[ConstDiv].setRGB( x, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+1, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+2, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+3, y, LineColors[Line] );
				ENDIF;
			ENDWHILE;
			//


			IF Index==EndFr THEN
			   goto ENDY_PLOT_3;
			ENDIF;


			//
			WHILE( y>Ny )
				y--;
				IF y>=H_Grid || y<0 THEN
					goto ENDY_PLOT_3;
				ENDIF;

				IF DiffIE<200 THEN
					for( int y1=0; y1<LineWidth; y1++ ){
		                 for( int x1=0; x1<LineWidth; x1++ ){
		                      Pltrs[ConstDiv].setRGB( x+x1, y+y1, LineColors[Line] );
                         }
                    }
				ELSE
					//Pltrs.setRGB( x, y, LineColors[Line] );


			Pltrs[ConstDiv].setRGB( x, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+1, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+2, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+3, y, LineColors[Line] );
				ENDIF;

			ENDWHILE;
			//
			//
			WHILE( y!=Ny )
				y++;
				IF y>=H_Grid || y<0 THEN
					goto ENDY_PLOT_3;
				ENDIF;


				IF DiffIE<200 THEN
					for( int y1=0; y1<2; y1++ ){
		                 for( int x1=0; x1<2; x1++ ){
		                      Pltrs[ConstDiv].setRGB( x+x1, y+y1, LineColors[Line] );
                         }
                    }
				ELSE
					//Pltrs.setRGB( x, y, LineColors[Line] );


			Pltrs[ConstDiv].setRGB( x, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+1, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+2, y, LineColors[Line] );
			Pltrs[ConstDiv].setRGB( x+3, y, LineColors[Line] );

				ENDIF;

			ENDWHILE;
			ENDY_PLOT_3:
			y = 0;
		ENDLOOP;
		ENDLINE_PLOT_3:
		/*
        IF !Connected THEN
		   Pltrs[0].FillBuff();
		   Pltrs[1].FillBuff();
		ENDIF;
		//*/
        y = 0;
        IF Connected THEN
           Sleep( 1 );
        ENDIF;
	ENDLOOP;
	//

	FOR int Line=0; Line<MaxConstDiv; Line++ LOOP
        Pltrs[Line].FillBuff();
    ENDLOOP;
	return TRUE;
}
