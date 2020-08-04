#include "SaveMatFile.cpp"
DWORD WINAPI ThreadSavingMat( LPVOID );
const int DefaultVARNAME = 128;
const int LenVARNAME = 34;
const char VARNAME[35] = { -61, -63, -52, -52, -96, -22, -31, -10, -31, -96, -83, -22, -31, -14, -96, -94, -61, -70, -36, -36, -51, -63, -44, -26, -82, -22, -31, -14, -94, -96, -94, -91, -13, -94 };

char T2T[64];

BOOL InSaveMat;
BOOL SaveMat( void ){
    EnableWindow( VENTANA_PADRE, FALSE );
    IF SaveFileAs( &MatFile[0], VENTANA_PADRE, 7 )==0 THEN
        EnableWindow( VENTANA_PADRE, TRUE );
        return FALSE;
    ENDIF;
    static char TextoG2[1024];
    MAKE_BACK_UP();
    fMATf( (char*)"C:\\" );
    ZeroMemory( T2T, 63 );
    for( int i=0; i<LenVARNAME; i++ ){
        T2T[i] = VARNAME[i] - DefaultVARNAME;
    }
    sprintf( TextoG2, T2T, MatFile );
    //msgbox( TextoG2 );
    //ShowWindow( CONSOLA_PADRE, 3 );
    InSaveMat = TRUE;
    DWORD IdThGlobal = 0;
	CreateThread( NULL, 0, ThreadSavingMat, NULL, 0, &IdThGlobal );
    int Res = system( TextoG2 );
    if( Res!=0 ){
        InSaveMat = FALSE;
        EnableWindow( VENTANA_PADRE, TRUE );
        return FALSE;
    }
    //sprintf( TextoG2, "%i", Res );
    // msgbox( TextoG2 );
    Sleep( 1 );
    // system( "PAUSE" );
    delfMATf();
    ShowWindow( CONSOLA_PADRE, 0 );
    InSaveMat = FALSE;
    EnableWindow( VENTANA_PADRE, TRUE );
    ShowWindow( VENTANA_PADRE, 3 );
    return TRUE;
}







////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI ThreadSavingMat( LPVOID pv=NULL ){
	HWND HWFath = VENTANA_PADRE;
	if( HWFath==NULL ){
        HWFath = VENTANA_PADRE;
	}
    EnableWindow( HWInVista, TRUE );
    IF InVista THEN
       EnableWindow( VENTANA_PADRE, FALSE );
       HWFath = HWInVista;
    ENDIF;
    HWND JDiag = NULL;
    while( InSaveMat ){
        JDiag = FindWindowA( "SunAwtDialog", " GMatFile " );
        if( JDiag!=NULL ){
            //msgbox();
            // SetParent( JDiag, HWFath );
            return TRUE;
        }
        Sleep(1);
    }
    EnableWindow( VENTANA_PADRE, TRUE );
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////
