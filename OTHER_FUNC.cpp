/*
#include <sys/stat.h>

BOOL IsFile( char* NFile ){
    struct stat st;
    stat( NFile, &st );
    return S_ISREG(st.st_mode);
}
//

BOOL IsDir( char* NFile ){
    struct stat st;
    stat( NFile, &st );
    return S_ISDIR(st.st_mode);
}

//*/











class Tag_WinFuncs{
public:
////////
	static int GetWinXPos( HWND HWnd ){
		int x = 0;
		int y = 0;
        POINT pos;
        POINT posF;
        memset( &pos, 0, sizeof(POINT) );
        memset( &posF, 0, sizeof(POINT) );
        ClientToScreen( HWnd, &pos);
        HWND hwndP = GetParent( HWnd );
        if( hwndP==NULL ){
            x = pos.x;
            y = pos.y;
            y = y;
        }else{
            ClientToScreen( hwndP, &posF );
            x = pos.x - posF.x;
            y = pos.y - posF.y;
        }
		return x;
	}
////////
	static int GetWinYPos( HWND HWnd ){
		int x = 0;
		int y = 0;
        POINT pos;
        POINT posF;
        memset( &pos, 0, sizeof(POINT) );
        memset( &posF, 0, sizeof(POINT) );
        ClientToScreen( HWnd, &pos);
        HWND hwndP = GetParent( HWnd );
        if( hwndP==NULL ){
            x = pos.x;
            y = pos.y;
            x = x;
        }else{
            ClientToScreen( hwndP, &posF );
            x = pos.x - posF.x;
            y = pos.y - posF.y;
        }
		return y;
	}
////////
	static int GetWinWidth( HWND HWnd ){
		RECT re;
		memset( &re, 0, sizeof(RECT) );
		GetClientRect( HWnd, &re );
		return re.right;
	}
////////
	static int GetWinHeight( HWND HWnd ){
		RECT re;
		memset( &re, 0, sizeof(RECT) );
		GetClientRect( HWnd, &re );
		return re.bottom;
	}
////////
};
Tag_WinFuncs WinFuncs;
