BOOL LoadVista( void ){
int LimX = (int)(TopDTime*FsReal);
// const double VoltMax = 5;
double Time = 0;
double Gain = 0.5;
double Tao = 10.2;
double AuxD = 0;
FOR int Index=0; Index<LimX; Index++ LOOP
    Time = Index;
    Time = Time/((double)FsReal);

    AuxD = PrimerOrden( Time, Gain, Tao );

    AuxD = round(1023*AuxD);
    BuffData[0].USData[Index] = (unsigned short)AuxD;

ENDLOOP;
//*/
double R = 1;
double L = 2;
double C = 2;
double Q0 = 1;
double RL = R/(2*L);
double Wd = sqrt(1/(L*C) - RL*RL);
double ArgE = 0;

FOR int Index=0; Index<LimX; Index++ LOOP
    Time = (double)Index;
    Time = Time/(double)FsReal;
    AuxD = exp( -RL*Time );
    ArgE = cos( Wd*Time );
    AuxD = Q0*AuxD*ArgE;
    AuxD = -( AuxD - Q0);
    AuxD = round(255*AuxD/2.2);
    BuffData[1].USData[Index] = (unsigned short)(AuxD);
ENDLOOP;




double AngArg = (11.1)*2*pi/LimX;

FOR int i=0; i<LimX; i++ LOOP
    ArgE = (sin( i*AngArg ) + 1)/2;
    ArgE = round(1023*ArgE);
    BuffData[2].USData[i] = (unsigned short)(ArgE);
ENDLOOP;










R = 0.5;
L = 5;
C = 2;
Q0 = 1;
RL = R/(2*L);
Wd = sqrt(1/(L*C) - RL*RL);
ArgE = 0;

AngArg = (2*TopDTime)*2*pi/LimX;
FOR int i=0; i<LimX; i++ LOOP


    Time = (double)i;
    Time = Time/(double)FsReal;
    AuxD = exp( -RL*Time );
    ArgE = cos( Wd*Time );
    AuxD = Q0*AuxD*ArgE;
    AuxD = -( AuxD - Q0);
    AuxD = round((255*AuxD)/2);


    ArgE = abs((sin( i*AngArg ) + 1)/2);
    ArgE = round(0.1*255*ArgE);

    ArgE = (ArgE + AuxD);
    ArgE = round(ArgE);

    BuffData[3].USData[i] = (unsigned short)(ArgE);
    //BuffData[3].USData[i] = 0;
ENDLOOP;


return TRUE;
FOR int i=0; i<LimX; i++ LOOP
    BuffData[0].USData[i] = (1023*BuffData[3].USData[i])/255;
ENDLOOP;

return TRUE;
}
