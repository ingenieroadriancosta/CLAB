#include <wininet.h>

int HttpFileSizeS( LPCSTR lpsURL ){
    DWORD FSize = 1024;
    char* StrRes = (char*)malloc( FSize );
    HINTERNET hInternet, hFile;
    hInternet = InternetOpen( "", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL){
        printf( "InternetOpen failed\n" );
        return -1;
    }
    hFile = InternetOpenUrl( hInternet, lpsURL, NULL, 0L, 0, 0 );
    if (hFile == NULL){
        InternetCloseHandle( hInternet );
        printf( "InternetOpenUrl failed\n" );
        return -1;
    }
    ZeroMemory( StrRes, FSize );
    HttpQueryInfo( hFile, HTTP_QUERY_RAW_HEADERS_CRLF, (LPVOID)StrRes, &FSize, NULL );
    InternetCloseHandle( hInternet );
    InternetCloseHandle( hFile );
    ///
    ///
    if( strncmp( StrRes, "HTTP/1.1 404 Not Found", strlen("HTTP/1.1 404 Not Found") )==0 ){
        return -2;
    }
    ///
    /// printf( "%s\n\n\n", StrRes );system( "pause" );
    ///
    ///
    const char* cntnt = "Content-Length: ";
    const int sle = strlen( StrRes );
    const int sli = strlen( cntnt );
    const int slT = sle - sli;
    if( slT<0 ){
        return -1;
    }
    int ires = -1;
    int ires_n = -1;
    for( int i=0; i<slT; i++ ){
        if( strncmp( &StrRes[i], cntnt, sli )==0 ){
            ires = i;
            break;
        }
    }
    ///
    if( ires<0 ){
        return -1;
    }
    ///
    ires = ires + sli;
    for( int i=ires; i<sle; i++ ){
        if( StrRes[i]=='\n' || StrRes[i]=='\r' ){
            ires_n = i;
            break;
        }
    }
    ///
    ///
    if( ires<0 || (ires_n-ires)<=0 ){
        return - 1;
    }
    strncpy( &StrRes[0], &StrRes[ires], (ires_n-ires) );
    StrRes[ires_n-ires] = 0;
    int I2Ret =atoi( StrRes );
    free( StrRes );
    return I2Ret;
}

int HttpRequest( LPCSTR lpsURL, char* ptr2retcs ){
    HINTERNET hInternet, hFile;
    char buf[2] = {0};
    DWORD bytes_read = 0;
    BOOL finished = TRUE;
    hInternet = InternetOpen( "", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
    if( hInternet == NULL ){
        printf( "InternetOpen failed\n" );
        return 0;
    }
    hFile = InternetOpenUrl( hInternet, lpsURL, NULL, 0L, 0, 0 );
    if( hFile == NULL ){
        InternetCloseHandle( hInternet );
        return 0;
    }
    int n_t_m = 0;
    while( finished ){
        if( InternetReadFile( hFile, buf, 1, &bytes_read) ) {
            if (bytes_read > 0) {
                ptr2retcs[n_t_m] = buf[0];
                n_t_m++;
            }
            else {
                finished = FALSE;
            }
        }
        else {
            finished = FALSE;
        }
    }
    InternetCloseHandle( hInternet );
    InternetCloseHandle( hFile );
    return n_t_m;
}
