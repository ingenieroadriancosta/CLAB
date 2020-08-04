BOOL SetColChann( int Ind ){

HWND HWColors[4];
HWColors[0] = HWSel_Color_Chann0_In;
HWColors[1] = HWSel_Color_Chann0_Out;
HWColors[2] = HWSel_Color_Chann1_In;
HWColors[3] = HWSel_Color_Chann1_Out;


RGBQUAD* RgbQ = (RGBQUAD*)malloc( 4*75*13 + 1024 );
int WMax = 75;
IF Ind%2==0 THEN
   WMax = 75;
ENDIF;
    
FOR int y=0; y<13; y++ LOOP
    FOR int x=0; x<WMax; x++ LOOP
        int ToIndex = x + WMax*y;
        RgbQ[ToIndex] = LineColors[Ind];
    ENDLOOP;
ENDLOOP;
SetBitmapBits( HB_CButt_C[Ind], 4*WMax*13, &RgbQ[0] );
free( RgbQ );
SendMessage( HWColors[Ind], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)HB_CButt_C[Ind] );
return TRUE;
}
