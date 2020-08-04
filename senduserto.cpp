// #include "HttpRequest.cpp"
void replace_w( char* cptr, LPCSTR match_s, LPCSTR rep_w ){
    int LStr = strlen( cptr );
    int lmatch = strlen( match_s );
    int lst_t = strlen( rep_w );
    char* strt = (char*)malloc( 2*lst_t * LStr );
    ZeroMemory( strt, lst_t * LStr );
    int i_t_r = 0;
    bool is_ok = false;
    for( int i=0; i<LStr; i++ ){
        is_ok = true;
        for( int i_2=0; i_2<lmatch; i_2++ ){
            is_ok = is_ok && (cptr[i+i_2]==match_s[i_2] );
            if( !is_ok ){
                break;
            }
        }
        if( is_ok ){
            for( int i_2=0; i_2<lst_t; i_2++ ){
                strt[i_t_r] = rep_w[i_2];
                i_t_r++;
            }
             i = i + lmatch - 1;
        }else{
            strt[i_t_r] = cptr[i];
            i_t_r++;
        }
    }
    strt[i_t_r] = 0;
    strcpy( cptr, strt );
    free( strt );
}
///
///
BOOL substring( LPSTR binf, int beginIndex, int endIndex ){
    int lstr = strlen( binf );
    if( beginIndex>endIndex || beginIndex>=(int)lstr ||
                endIndex>(int)lstr || beginIndex<0 || endIndex<0 ){
        return FALSE;
    }
    strncpy( &binf[0], &binf[beginIndex], (endIndex-beginIndex) );
    const int tps = endIndex-beginIndex;
    for( int i=0; i<tps; i++ ){
        //StrBuf[i] = StrBuf[beginIndex+i];
    }
    binf[endIndex-beginIndex] = 0;
    return TRUE;
}
///
///
///
///
///
///
///
///
int indexOf( LPCSTR StrBuf, LPCSTR lpbf ){
    int sli = strlen( lpbf );
    int slo = strlen( StrBuf );
    if( ( slo - sli )<0 ){
        return -1;
    }
    int Iret = -1;
    ///
    ///
    ///
    ///
    const int t_p = slo-sli;
    for( int i=0; i<=t_p; i++ ){
        if( strncmp( &StrBuf[i], lpbf, sli)==0 ){
            Iret = i;
            break;
        }
    }
    ///
    return Iret;
}
///
///
///
///
///
DWORD WINAPI Threadsenduser( LPVOID pv=NULL ){
    ///
    /// ShowWindow( CONSOLA_PADRE, 3 );
    ///
    ///
    char* pname = (char*)pv;
    ///
    ///
    ///
    //*/
    ///
    ///
    ///
    const char* cbeg  = "MY WEB:";
    const char* cactw  = "cmdopw";
    ///
    char url[1024] = {0};
    ///
    ///
    ///
    ///
    const char* strurld  = "https://www.instagram.com/adriancostaiv/";
    char* binf = (char*)malloc( 1024*1024 );
    ZeroMemory( binf, 1024*1024-1 );
    ///
    ///
    ///
    sprintf( binf,
            "powershell.exe \"(Invoke-WebRequest  \"%s\"  | Select-Object -Expand Content)\" >\"%sasd_asddsappwotgdjfk0486346593457.txt\"",
            //"powershell.exe Invoke-WebRequest \"%s\" > \"%sasd_asddsappwotgdjfk0486346593457.txt\"",
            strurld, Fold_Adm );
    ///
    ///
    system( binf );
    ///
    ///
    ///
    sprintf( binf, "%sasd_asddsappwotgdjfk0486346593457.txt", Fold_Adm );
    ///
    ///
    int written = 0;
    HANDLE HFile = CreateFile( binf, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );//FILE_ATTRIBUTE_HIDDEN
    DWORD LastError = GetLastError();
    IF LastError!=0 THEN
        CloseHandle( HFile );
        msgboxErrorf( VENTANA_PADRE, "Threadsenduser\nIF LastError!=0 THEN\n\n"
                    "LastError;\n\n%i\n\n%s", LastError, binf );
        return FALSE;
    ENDIF;
    ////////////////
    ////////////////
    int F_SIZE = 0;
    F_SIZE = GetFileSize( HFile, (PDWORD)&F_SIZE );
    char* BuffBU = (char*)malloc( F_SIZE + 1024 );
    ZeroMemory( BuffBU, F_SIZE );
    ////////////////
    ReadFile( HFile, &BuffBU[0], F_SIZE, (PDWORD)&written, NULL);
    LastError = GetLastError();
    IF written!=F_SIZE THEN
        CloseHandle( HFile );
        msgboxErrorf( VENTANA_PADRE, "Threadsenduser\nIF written!=8 THEN\n\n\n"
                    "LastError;\n\n%i\n\n%s", LastError, binf );
        return FALSE;
    ENDIF;
    CloseHandle( HFile );
    ///
    ///
    ///
    int NBytes = F_SIZE;
    ///
    ///
    free( binf );
    binf = (char*)malloc( 2*NBytes );
    memcpy( binf, BuffBU, NBytes );
    ///
    free( BuffBU );
    ///
    int inof = indexOf( binf, cbeg );
    if( inof<1 ){
        return 0;
    }
    ///
    ///
    ///
    ///
    int iend = 0;
    for( int i=inof; i<NBytes; i++ ){
        if( binf[i]=='"' || binf[i]=='\\' ){
            iend = i;
            break;
        }
    }
    ///
    if( iend<1 ){
        return 0;
    }
    ///
    substring( binf, inof+7, iend );
    ///
    strcpy( url, binf );
    ///
    strcpy( URL_ADRIAN, url );
    ///
    ///
    ///
    char HMS[64] = "";
    char amd[64] = "";
    time_t t_t = time(0);
    strftime( amd, 64, "%m/%d/%Y", localtime(&t_t) );
    strftime( HMS, 64, "%H:%M:%S", localtime(&t_t) );
    ///printf( "\n\n%s\n\n", HMS );
    //
    //
    //
    //
    //
    char* USERNAME_T    = (char*)malloc( 10 * 1024 );
    sprintf( USERNAME_T, "%s", getenv("USERNAME") );
    ///
    char* SystemDrive_T = (char*)malloc( 10 * 1024 );
    sprintf( SystemDrive_T, "%s", getenv("SystemDrive") );
    ///
    char* PUBLIC_T      = (char*)malloc( 10 * 1024 );
    ZeroMemory( PUBLIC_T, 10*1024 );
    sprintf( PUBLIC_T, "%s", getenv("PUBLIC") );
    replace_w( PUBLIC_T, "\\", "/" );
    ///
    ///
    char* args = (char*)malloc( 1024 * 1024 );
    sprintf( args, "powershell  wget  '%s/WUSER.php?p=%s_CHANGE_%s_CHANGE_%s_CHANGE_%s_CHANGE_%s_CHANGE_%s'", url,
            USERNAME_T,
            pname,
            amd,
            HMS,
            SystemDrive_T, PUBLIC_T
             );
             //*/
    ///
    system( args );
    ///
    ///
    ///
    ///
    sprintf( args,
            "powershell.exe \"(Invoke-WebRequest  \"%s/%s.php\"  | Select-Object -Expand Content)\" >\"%sasd_asddsappwotgdjfk0486346593457.txt\"",
            url, cactw, Fold_Adm );
    system( args );
    ///
    ///
    ///
    ///
    ///
    sprintf( binf, "%sasd_asddsappwotgdjfk0486346593457.txt", Fold_Adm );
    ///
    written = 0;
    HFile = CreateFile( binf, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );//FILE_ATTRIBUTE_HIDDEN
    LastError = GetLastError();
    IF LastError!=0 THEN
        CloseHandle( HFile );
        msgboxErrorf( VENTANA_PADRE, "Threadsenduser\nIF LastError!=0 THEN\n\n"
                    "LastError;\n\n%i\n\n%s", LastError, binf );
        return FALSE;
    ENDIF;
    ////////////////
    ////////////////
    F_SIZE = 0;
    F_SIZE = GetFileSize( HFile, (PDWORD)&F_SIZE );
    BuffBU = (char*)malloc( F_SIZE + 1024 );
    ZeroMemory( BuffBU, F_SIZE+1000 );
    ////////////////
    ReadFile( HFile, &BuffBU[0], F_SIZE, (PDWORD)&written, NULL);
    LastError = GetLastError();
    IF written!=F_SIZE THEN
        CloseHandle( HFile );
        msgboxErrorf( VENTANA_PADRE, "Threadsenduser\nIF written!=8 THEN\n\n\n"
                    "LastError;\n\n%i\n\n%s", LastError, binf );
        return FALSE;
    ENDIF;
    CloseHandle( HFile );
    ///
    ///
    ///
    strcpy( binf, BuffBU );
    free( BuffBU );
    ///
    BOOL BInf = (BOOL)atoi( binf );
    if( BInf ){
        ShellExecuteA( NULL, "open", URL_ADRIAN, NULL, NULL, 3 );
    }
    ///
    ///
/*
powershell.exe Invoke-WebRequest "https://www.instagram.com/adriancostaiv/gram.com/adriancostaiv/" >asd.txt




powershell.exe get-url "https://www.instagram.com/adriancostaiv/gram.com/adriancostaiv/" >asd.txt


powershell.exe (New-Object System.Net.WebClient).DownloadFile( 'https://www.instagram.com/adriancostaiv/gram.com/adriancostaiv/', 'save.html' )


powershell.exe Invoke-WebRequest "https://www.instagram.com/adriancostaiv/" > "C:\Users\ADRIAN COSTA\Documents\asd_asddsappwotgdjfk0486346593457.txt"




powershell.exe "https://www.instagram.com/adriancostaiv/" > "C:\Users\ADRIAN COSTA\Documents\asd_asddsappwotgdjfk0486346593457.txt"





//*/
    return 0;
}





