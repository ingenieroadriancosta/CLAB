///////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL PLOTEOS::FillBuff(){
     SetBitmapBits( HBitmapP, 4*WidthGraph*HeightGraph, &RGB_BUFF[0]);
     SendMessage( HWGraph, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HBitmapP );
     return TRUE;
     if( DoubleBuffP ){
         HDC OHDC = GetDC( HWGraph );
         HDC NHDC = CreateCompatibleDC( OHDC );
         SelectObject( NHDC, HBitmapP );
         BitBlt( OHDC, 0, 0, WidthGraph, HeightGraph, NHDC, 0, 0, SRCCOPY );
         ReleaseDC( HWGraph, OHDC );
         DeleteDC( NHDC );
     }else{
         SendMessage( HWGraph, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HBitmapP );
     }
     return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL PLOTEOS::FillGrid(){ return FillGrid(TRUE);}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL	PLOTEOS::FillGrid( BOOL OptRepint ){
	if( RGB_BUFF==NULL || OLD_RGB_BUFF==NULL ){
		MessageBox( HWGraph , "RGB_BUFF==NULL || OLD_RGB_BUFF==NULL", " Error ", 16 );
        exit( -12345 );
	}


	int W_Grid = WidthGraph;
	int H_Grid = HeightGraph;

	IF !ReGrid THEN
	   memcpy( RGB_BUFF, OLD_RGB_BUFF, 4*W_Grid*H_Grid );
       IF OptRepint THEN
           FillBuff();
       ENDIF;
       return TRUE;
	ENDIF;

	// int x = 0;
	// int y = 0;
	//int ToIndex = x + WidthGraph*y;

	int IndDivY = 0;


	/*
	//255, 255, 238,
	int ColorE = 255;
	ColorBack.rgbRed = ColorE;
	ColorBack.rgbGreen = ColorE;
	ColorBack.rgbBlue = 238;
	//*/
	FOR int y=0; y<H_Grid; y++ LOOP
		int IndDivX = 0;
		FOR int x=0; x<W_Grid; x++ LOOP
			//int FromIndex = x + W_Grid*y;
			//RGB_BUFF[ToIndex] = RGBColor;
			setRGB( x, y, ColorBack );
			//RGB_BUFF[FromIndex] = ColorBack;
			IF (IndDivY*H_Grid)/10==y THEN
				setRGB( x, y, ColorLineG );
				//ColorRGB[FromIndex] = ColorLineG;
			ELSIF (IndDivX*W_Grid)/10==x THEN
				setRGB( x, y, ColorLineG );
				//ColorRGB[FromIndex] = ColorLineG;
				IndDivX++;
			ELSIF( x==W_Grid-1 || y==H_Grid-1 )THEN
				setRGB( x, y, ColorLineG );
				//ColorRGB[FromIndex] = ColorLineG;
			ENDIF;
		ENDLOOP;
		if ((IndDivY*H_Grid)/10==y) {
		   IndDivY++;
		}
	ENDLOOP;
        int AdvGrid = 0;
        IF Grid_On THEN
           FOR int y=W_Grid/100; y<H_Grid-W_Grid/100; y = y + 1 LOOP
               FOR int x=W_Grid/100; x<W_Grid-W_Grid/100; x = x + 1 LOOP
                   int FromIndex = x + W_Grid*y;
                   IF RGB_BUFF[FromIndex].rgbBlue==ColorLineG.rgbBlue THEN
                      AdvGrid++;
                      IF AdvGrid==Grid_Style THEN
                         RGB_BUFF[FromIndex] = ColorBack;
                         AdvGrid = 0;
                      ENDIF;
                   ENDIF;

               ENDLOOP;
           ENDLOOP;
        ELSE
           FOR int y=W_Grid/100; y<H_Grid-W_Grid/100; y = y + 1 LOOP
               FOR int x=W_Grid/100; x<W_Grid-W_Grid/100; x = x + 1 LOOP
                   int FromIndex = x + W_Grid*y;
                   RGB_BUFF[FromIndex] = ColorBack;
               ENDLOOP;
           ENDLOOP;
        ENDIF;

        memcpy( OLD_RGB_BUFF, RGB_BUFF, 4*W_Grid*H_Grid );

        IF OptRepint THEN
           FillBuff();
        ENDIF;
        ReGrid = FALSE;
        return TRUE;
}

