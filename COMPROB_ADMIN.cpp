char Fold_Adm[1024] = {0};
BOOL COMPROB_ADMIN( void ){
    BOOL ErrE = FALSE;
    char CHexFile[1024] = { 0 };
    sprintf( CHexFile, "C:\\Users\\%s\\Documents\\error.dll", getenv("USERNAME") );
    DeleteFileA( CHexFile );
    Sleep(50);
    HANDLE HFile = CreateFile( CHexFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD LastError = GetLastError();
    if( LastError==ERROR_SHARING_VIOLATION || (LastError!=0 && LastError!=183) ){
        ErrE = TRUE;
    }
    CloseHandle( HFile );
    Sleep(1);
    DeleteFileA( CHexFile );
    Sleep(1);
    if( !ErrE ){
        sprintf( Fold_Adm, "C:\\Users\\%s\\Documents\\", getenv("USERNAME") );
        return TRUE;
    }
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///
    Fold_Adm[0] = ' ';
    Fold_Adm[1] = 0;
    ///
    ///
    char TUSERS[256] = "C:\\Users";
    int NFold = EnumFiles_IF( TUSERS, NULL );
    char** FNamesPtr = (char**)malloc( NFold * sizeof(int) + 16 );
    for( int i=0; i<NFold; i++ ){
        FNamesPtr[i] = (char*)malloc( 1024 );
    }
    EnumFiles_IF( TUSERS, FNamesPtr );
    for( int i=0; i<NFold; i++ ){
        sprintf( CHexFile, "C:\\Users\\%s\\Documents\\", FNamesPtr[i] );
        mkdir( CHexFile );
        sprintf( CHexFile, "C:\\Users\\%s\\Documents\\error.dll", FNamesPtr[i] );
        DeleteFile( CHexFile );
        Sleep( 1 );
        HFile = CreateFile( CHexFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        LastError = GetLastError();
        if( LastError==ERROR_SHARING_VIOLATION || (LastError!=0 && LastError!=183) ){
            CloseHandle( HFile );
            continue;
        }
        CloseHandle( HFile );
        Sleep(1);
        DeleteFileA( CHexFile );
        Sleep(1);
        sprintf( Fold_Adm, "C:\\Users\\%s\\Documents\\", FNamesPtr[i] );
        ErrE = FALSE;
        /// msgbox( FNamesPtr[i] );
        break;
    }
    ///
    for( int i=0; i<NFold; i++ ){
        free( FNamesPtr[i] );
    }
    free( FNamesPtr );
    ///
    ///
    ///
    ///
    ///
    ///
    ///
    ///
    ///
    if( ErrE ){
        msgboxErrorf( "Ejecute el software como administrador.\n\nError: %i"
                "\nerror dll\nerrorfollow dll\n", LastError );
        exit( 0 );
    }
    ///
    return TRUE;
}
