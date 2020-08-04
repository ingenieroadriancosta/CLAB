double AB_Val_Proc( HWND HWnd, double DMaxVal ){

double DVal_F = 0;
char DVText[64];
GetWindowText( HWnd, DVText, 63 );



IF DVText[0]==0 THEN
   DVText[0] = '0';
   DVText[1] = 0;
ENDIF;
int StrL = strlen( DVText );
BOOL BadStr = FALSE;
FOR int i=0; i<StrL; i++ LOOP
    BadStr = ( DVText[i]<48 || DVText[i]>57 );
    
    IF BadStr THEN
       BadStr = (DVText[i]!=46);
    ENDIF;
    
    IF BadStr THEN
       break;
    ENDIF;
ENDLOOP;
IF BadStr THEN
   DVText[0] = 48;
   DVText[1] = 0;
   SetWindowText( HWnd, DVText );
   DVal_F = 0;
ELSE
   DVal_F = atof( DVText );
   SetWindowText( HWnd, DVText );
ENDIF;


IF DVal_F>DMaxVal THEN
   sprintf( DVText, "%g", DMaxVal );
   DVal_F = atof( DVText );
   SetWindowText( HWnd, DVText );
   DVal_F = DMaxVal;
ELSIF DVal_F<0 THEN
   DVText[0] = 48;
   DVText[1] = 0;
   SetWindowText( HWnd, DVText );
   DVal_F = 0;
ENDIF;

#define ValDiv 10
BYTE BValT = (BYTE)(round( (255*DVal_F)/DMaxVal ) );
DVal_F = (double)BValT;
DVal_F = (DMaxVal*DVal_F)/255;
DVal_F = round(ValDiv*DVal_F);
DVal_F = DVal_F/ValDiv;
sprintf( DVText, "%g", DVal_F );
SetWindowText( HWnd, DVText );

//GetWindowText( HWnd, DVText, 63 );
//double Atof = atof( DVText );
//sprintf( DVText, "%g", Atof );
//SetWindowText( HWnd, DVText );

sprintf( DVText, "%g", DVal_F );
//msgbox( DVText );

return DVal_F;
}
