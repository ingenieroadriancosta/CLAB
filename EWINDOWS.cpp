BOOL EWINDOWS( BOOL aFlag ){

EnableWindow( HWSel_All_In, aFlag );
EnableWindow( HWSel_Chann0_In, aFlag );
EnableWindow( HWSel_Chann1_In, aFlag );



EnableWindow( HWSel_All_Out, aFlag );
EnableWindow( HWSel_Chann0_Out, aFlag );
EnableWindow( HWSel_Chann1_Out, aFlag );

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
BOOL InShowHide;
////////////////////////////////////////////////////////////////////////////////
BOOL PROC_CHANN( int Cursel ){
IF InShowHide THEN
   return FALSE;
ENDIF;
InShowHide = TRUE;
EWINDOWS( FALSE );
Cursel = Cursel - ID_SH_C0_IN;


IF Permission THEN
   BuffData[Cursel].Show = !BuffData[Cursel].Show;
ELSE
   BuffData[0].Show = (BOOL)(SendMessage( HWSel_Chann0_In, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);
   BuffData[2].Show = (BOOL)(SendMessage( HWSel_Chann1_In, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);
   BuffData[1].Show = (BOOL)(SendMessage( HWSel_Chann0_Out, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);
   BuffData[3].Show = (BOOL)(SendMessage( HWSel_Chann1_Out, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);
ENDIF;




IF Connected THEN
   SetPlot = TRUE;
ELSE
   PLOT_PROC();
ENDIF;

SendMessage( HWSel_Chann0_In, BM_SETCHECK, (WPARAM)(BuffData[0].Show), 0 );
SendMessage( HWSel_Chann1_In, BM_SETCHECK, (WPARAM)(BuffData[2].Show), 0 );
SendMessage( HWSel_Chann0_Out, BM_SETCHECK, (WPARAM)(BuffData[1].Show), 0 );
SendMessage( HWSel_Chann1_Out, BM_SETCHECK, (WPARAM)(BuffData[3].Show), 0 );




SendMessage( HWSel_All_In, BM_SETCHECK, (WPARAM)(BuffData[0].Show && BuffData[1].Show), 0 );


SendMessage( HWSel_All_Out, BM_SETCHECK, (WPARAM)(BuffData[2].Show && BuffData[3].Show), 0 );



InShowHide = FALSE;
EWINDOWS( TRUE );



IF !Connected THEN
   FOR int i=0; i<4; i++ LOOP
       ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
       ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
   ENDLOOP;
ENDIF;
        


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
BOOL PROC_ALL_CHANN( HWND HWActW, DWORD LwParam ){
IF InShowHide THEN
   return FALSE;
ENDIF;
InShowHide = TRUE;
EWINDOWS( FALSE );

IF HWActW==HWSel_All_In || LwParam==ID_SH_IN THEN
   BuffData[0].Show = ( BuffData[0].Show && BuffData[1].Show );
   BuffData[0].Show = !BuffData[0].Show;
   //BuffData[0].Show = (BOOL)(SendMessage( HWSel_All_In, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);
   BuffData[1].Show = BuffData[0].Show;
   SendMessage( HWSel_Chann0_In, BM_SETCHECK, (WPARAM)(BuffData[0].Show), 0 );
   SendMessage( HWSel_Chann0_Out, BM_SETCHECK, (WPARAM)(BuffData[0].Show), 0 );
   
   SendMessage( HWSel_All_In, BM_SETCHECK, (WPARAM)(BuffData[0].Show && BuffData[1].Show), 0 );
   
   
ELSE
   
   BuffData[2].Show = ( BuffData[2].Show && BuffData[3].Show );
   BuffData[2].Show = !BuffData[2].Show;
   
   //BuffData[2].Show = (BOOL)(SendMessage( HWSel_All_Out, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);
   BuffData[3].Show = BuffData[2].Show;
   SendMessage( HWSel_Chann1_In, BM_SETCHECK, (WPARAM)(BuffData[2].Show), 0 );
   SendMessage( HWSel_Chann1_Out, BM_SETCHECK, (WPARAM)(BuffData[2].Show), 0 );
   
   SendMessage( HWSel_All_Out, BM_SETCHECK, (WPARAM)(BuffData[2].Show && BuffData[3].Show), 0 );
   
ENDIF;



        
IF Connected THEN
   SetPlot = TRUE;
ELSE
   PLOT_PROC();
ENDIF;



IF !Connected THEN
   FOR int i=0; i<4; i++ LOOP
       ShowWindow( HWCursor[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
       ShowWindow( HWCursorInfo[i], 1&(int)(BuffData[i].Show && EnDataCursor[i]) );
   ENDLOOP;
ENDIF;
        

InShowHide = FALSE;
EWINDOWS( TRUE );
return TRUE;
}
