/*
C_STATIC.
*/
typedef struct TagStatic{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[1024];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    void setText( char* Text ){
        sprintf( W_Text, "%s", Text );
        SetWindowTextA( HWnd_Owner, W_Text );
    }
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setFather( HWND WFather ){
        W_Text[0] = 0;
        HWnd_Father = WFather;
        //DestroyWindow( HWnd_Owner );
        HWnd_Owner = CreateWindowEx( 0, "STATIC", "STATIC", WS_CHILD, X_Pos, Y_Pos, Width, Height,
                                     WFather, NULL, INSTANCIA_GLOBAL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        setVisible( IsVisible );
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }
}Static;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_BUTTON.
*/
typedef struct TagButton{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    DWORD              ID_Item;
    char               W_Text[1024];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    DWORD GetIdItem( void ){return ID_Item;}
    //////

    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    void setText( const char* Text ){
        sprintf( W_Text, "%s", Text );
        SetWindowTextA( HWnd_Owner, W_Text );
        SetToolTip();
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        W_Text[0] = 0;
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        ID_Item = Identifier;
        HWnd_Owner = CreateWindowEx( 0, "BUTTON", "",
                                    WS_CHILD | WS_BORDER |
                                    BS_MULTILINE,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
        SetToolTip();
    }
    //////
    BOOL SetToolTip( void ){
        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_Text[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}Button;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_CHECKBOX.
*/
typedef struct TagCheckBox{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[1024];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    void setText( char* Text ){
        sprintf( W_Text, "%s", Text );
        SetWindowTextA( HWnd_Owner, W_Text );
        SetToolTip();
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        W_Text[0] = 0;
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        HWnd_Owner = CreateWindowEx( 0, WC_BUTTONA, "BUTTON",
                                     WS_CHILD | BS_AUTOCHECKBOX | BS_FLAT | BS_MULTILINE,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    BOOL SetToolTip( void ){
        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_Text[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    BOOL isSelected(){
        return (SendMessage( HWnd_Owner, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);
    }
    //////
    void setSelected( BOOL aFlag ){
        SendMessage( HWnd_Owner, BM_SETCHECK, (WPARAM)(aFlag), 0 );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}CheckBox;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_TOGGLEBUTTON.
*/
typedef struct TagToggleButton{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[1024];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    void setText( LPSTR Text ){
        sprintf( W_Text, "%s", Text );
        SetWindowTextA( HWnd_Owner, W_Text );
        SetToolTip();
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        W_Text[0] = 0;
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        HWnd_Owner = CreateWindowEx( 0, WC_BUTTONA, "",
                                     BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_CHILD | WS_TABSTOP |
                                     BS_MULTILINE,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetToolTip();
    }
    //////
    BOOL SetToolTip( void ){
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_Text[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    BOOL isSelected(){return (SendMessage( HWnd_Owner, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);}
    //////
    void setSelected( BOOL aFlag ){
        SendMessage( HWnd_Owner, BM_SETCHECK, (WPARAM)(aFlag), 0 );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}ToggleButton;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_COMBOBOX.
*/
typedef class TagComboBox{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[1024];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    void AddString( char* Text ){
        IF HWnd_Owner THEN
           SendMessage( HWnd_Owner , CB_ADDSTRING, 0, (LPARAM)Text );
           SendMessage( HWnd_Owner, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)Text );
        ENDIF;
    }
    //////
    void ResetContent( void ){
        SendMessage( HWnd_Owner, CB_RESETCONTENT, 0, 0 );
    }
    //////
    void setSelectedIndex(int anIndex){
        IF HWnd_Owner THEN
           SendMessage( HWnd_Owner, CB_SETCURSEL, (WPARAM)anIndex, 0 );
        ENDIF;
    }
    //////
    int getSelectedIndex( void ){
        return (SendMessage( HWnd_Owner, CB_GETCURSEL, (WPARAM)0, 0 ));
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setText( UINT UText ){
        LoadStringA( GetModuleHandle(0), UText, W_Text, 1024  );
        SetToolTip();
    }
    //////
    void setText( LPSTR Text ){
        sprintf( W_Text, "%s", Text );
        SetToolTip();
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        W_Text[0] = 0;
        HWnd_Owner = CreateWindowEx( 0, "COMBOBOX", W_Text,
                                     CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_TABSTOP,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetToolTip();
    }
    //////
    BOOL SetToolTip( void ){
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_Text[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}ComboBox;




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_COMBOBOX.
*/
typedef class TagComboBoxIcon{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[256];
    char               W_ToolTip[256];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    void AddString( char* Text ){
        IF HWnd_Owner THEN
           SendMessage( HWnd_Owner , CB_ADDSTRING, 0, (LPARAM)Text );
           SendMessage( HWnd_Owner, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)Text );
        ENDIF;
    }
    //////
    void ResetContent( void ){
        SendMessage( HWnd_Owner, CB_RESETCONTENT, 0, 0 );
    }
    //////
    void setSelectedIndex(int anIndex){
        IF HWnd_Owner THEN
           SendMessage( HWnd_Owner, CB_SETCURSEL, (WPARAM)anIndex, 0 );
        ENDIF;
    }
    //////
    int getSelectedIndex( void ){
        return (SendMessage( HWnd_Owner, CB_GETCURSEL, (WPARAM)0, 0 ));
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        W_Text[0] = 0;
        HWnd_Owner = CreateWindowEx( 0, "COMBOBOX", "",
                                     CBS_OWNERDRAWFIXED |
                                     CBS_DROPDOWNLIST | CBS_SORT |
                                     WS_VSCROLL |
                                     WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetToolTip();
    }
    //////
    void setToolTip( UINT UText ){
        LoadStringA( GetModuleHandle(0), UText, W_ToolTip, 256 );
        SetToolTip();
    }
    //////
    void setToolTip( LPSTR Text ){
        sprintf( W_ToolTip, "%s", Text );
        SetToolTip();
    }
    //////
    //////
    BOOL SetToolTip( void ){
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_ToolTip[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}ComboBoxIcon;























/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_STATICBMP.
*/
typedef class TagStaticBMP{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[1024];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setFather( HWND WFather ){
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        W_Text[0] = 0;
        HWnd_Owner = CreateWindowEx( 0, WC_STATICA, NULL,
                                     WS_CHILD | WS_BORDER |
                                     //SS_TYPEMASK |
                                     WS_CLIPCHILDREN |
                                     SS_BITMAP,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, NULL, INSTANCIA_GLOBAL, NULL );
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }
}StaticBMP;









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_TAB.
*/
typedef struct TagTab{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[1024];
    TCITEM             tie;
public:
       //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    //////
    BOOL InsertItem( int Index, char* Title ){
        tie.mask = TCIF_TEXT;
        tie.pszText = &Title[0];
        return (TabCtrl_InsertItem( HWnd_Owner, Index, &tie)==-1);
    }

    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setFather( HWND WFather ){
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        W_Text[0] = 0;
        HWnd_Owner = CreateWindowEx( 0, WC_TABCONTROL, NULL,
                                     WS_CHILD,// | TCS_BUTTONS,  "SysTabControl32"
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, NULL, INSTANCIA_GLOBAL, NULL );
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }
}Tab;












/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*trackbar
C_EDIT_NUM.
*/
typedef struct TagEditNum{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    HFONT              HFontC;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[256];
    char               W_ToolTip[256];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    void getText( char* Text ){
        GetWindowTextA( HWnd_Owner, W_Text, 1024 );
    }
    //////
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    int getValue( void ){
        GetWindowTextA( HWnd_Owner, W_Text, 1024 );
        if( W_Text[0]==0 )
            return -1;
        return atoi(W_Text);
    }
    //////
    void setText( char* Text ){
        sprintf( W_Text, "%s", Text );
        SetWindowTextA( HWnd_Owner, W_Text );
    }
    //////
    void setValue( unsigned int Value ){
        sprintf( W_Text, "%u", Value );
        SetWindowTextA( HWnd_Owner, W_Text );
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    BOOL setFont( int nHeight, int fnWeight=FW_BOLD, LPSTR FontName=NULL ){
        DeleteObject( HFontC );
        HFontC = CreateFont( nHeight, 0, 0, 0, fnWeight, FALSE, FALSE, FALSE,
                            DEFAULT_CHARSET, OUT_TT_PRECIS,
                            CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                            DEFAULT_PITCH | FF_ROMAN, FontName );
        SendMessage( HWnd_Owner, WM_SETFONT, (WPARAM)HFontC, MAKELPARAM(TRUE, 0) );
        return TRUE;
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        W_Text[0] = 0;
        HWnd_Owner = CreateWindowEx( 0, "EDIT", W_Text,
                                     ES_LEFT | WS_CHILD | WS_BORDER | ES_NUMBER,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
    DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetToolTip();
    }
    //////
    //////
    void setToolTip( UINT UText ){
        LoadStringA( GetModuleHandle(0), UText, W_ToolTip, 256 );
        SetToolTip();
    }
    //////
    void setToolTip( LPSTR Text ){
        sprintf( W_ToolTip, "%s", Text );
        SetToolTip();
    }
    //////
    BOOL SetToolTip( void ){
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_ToolTip[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}EditNum;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*trackbar
C_EDIT_NUM_DOUBLE.
*/
typedef class TagEditNum_Double{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    HFONT              HFontC;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[256];
    char               W_ToolTip[256];
public:
     ~TagEditNum_Double(){
        DeleteObject( HFontC );
     }
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    void getText( char* Text ){
        GetWindowTextA( HWnd_Owner, &W_Text[0], 1024 );
    }
    //////
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    double getValue( void ){
        GetWindowTextA( HWnd_Owner, W_Text, 1024 );
        if( W_Text[0]==0 )
            return -1;
        return atof(W_Text);
    }
    //////
    void setText( char* Text ){
        sprintf( W_Text, "%s", Text );
        SetWindowTextA( HWnd_Owner, W_Text );
    }
    //////
    void setValue( double Value ){
        sprintf( W_Text, "%5.3f", Value );
        SetWindowTextA( HWnd_Owner, W_Text );
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    BOOL setFont( int nHeight, int fnWeight=FW_BOLD, LPSTR FontName=NULL ){
        DeleteObject( HFontC );
        HFontC = CreateFont( nHeight, 0, 0, 0, 300, FALSE, FALSE, FALSE,
                            DEFAULT_CHARSET, OUT_TT_PRECIS,
                            CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                            DEFAULT_PITCH | FF_ROMAN, FontName );
        SendMessage( HWnd_Owner, WM_SETFONT, (WPARAM)HFontC, MAKELPARAM(TRUE, 0) );
        return TRUE;
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        W_Text[0] = 0;
        HWnd_Owner = CreateWindowEx( 0, "EDIT", NULL,
                                     ES_LEFT | WS_CHILD | WS_BORDER,// | ES_NOHIDESEL,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetToolTip();
    }
    //////
    //////
    void setToolTip( UINT UText ){
        LoadStringA( GetModuleHandle(0), UText, W_ToolTip, 256 );
        SetToolTip();
    }
    //////
    void setToolTip( LPSTR Text ){
        sprintf( W_ToolTip, "%s", Text );
        SetToolTip();
    }
    //////
    BOOL SetToolTip( void ){
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_ToolTip[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}EditNum_Double;









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_BUTTON_BMP.
*/
typedef class TagBMPButton{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[256];
    HBITMAP            HBMP;
    HICON              H_ICON;
public:
    ~TagBMPButton(){
        DeleteObject(HBMP);
        DeleteObject(H_ICON);
    }
    HWND GetHandle( void ){return HWnd_Owner;}
    //////

    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    void setText( LPCSTR Text ){
        sprintf( W_Text, "%s", Text );
        SetWindowTextA( HWnd_Owner, W_Text );
        SetToolTip();
    }
    //////
    void setText( UINT UText ){
        LoadStringA( GetModuleHandle(0), UText, W_Text, 256 );
        SetWindowTextA( HWnd_Owner, W_Text );
        SetToolTip();
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        SetToolTip();
    }
    //////
    void setFather( HWND WFather, int Identifier, UINT AddStyle=0 ){
        W_Text[0] = 0;
        IsVisible = false;
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        HWnd_Owner = CreateWindowEx( 0, "BUTTON", NULL,
                                     WS_CHILD | WS_BORDER | BS_BITMAP | AddStyle,
                                     X_Pos, Y_Pos,
                                     Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        SetToolTip();
    }
    //////
    BOOL SetToolTip( void ){
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_Text[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }

    //////
    void setJPGResource( int J_Resource ){
        DeleteObject( HBMP );
        HBMP = loadResImage( J_Resource, MAKEINTRESOURCE(32) );
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMP );
    }
    //////
    void setBMPResource( char* C_Resource ){
        DeleteObject( HBMP );
        HBMP = LoadBitmap( GetModuleHandle(0), C_Resource );
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMP );
    }
    //////
    //////
    void setICONResource( char* C_Resource ){
        DeleteObject( H_ICON );
        H_ICON = LoadIconA( GetModuleHandle(0), C_Resource );
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)H_ICON );
    }
    //////
    void setBMPResource( UINT UC_Resource ){
        DeleteObject( HBMP );
        HBMP = LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(UC_Resource) );
        if( HBMP==NULL ){
            const int JPG = 5;
            HBMP = loadResImage( JPG, MAKEINTRESOURCE(UC_Resource) );
        }
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMP );
    }
    //////
    void setBMP( HBITMAP HBitmap ){
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBitmap );
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }

}BMPButton;

















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
C_BUTTON_BMP.
*/
typedef struct TagBMPButton_Toggle{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               HWnd_ToolTip;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;

    HBITMAP            HBMP;
    TOOLINFO           TInfo;
public:
    char               W_Text[256];
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    int getWidth( void ){return Width;}
    //////
    int getHeight( void ){return Height;}
    //////
    //////
    int getX( void ){return X_Pos;}
    //////
    int getY( void ){return Y_Pos;}
    //////
    void setText( int IText ){
        LoadString( GetModuleHandle(NULL), IText, W_Text, 255);
        SetToolTip();
    }
    //////
    void setText( char* Text ){
        sprintf( W_Text, "%s", Text );
        //SetWindowTextA( HWnd_Owner, W_Text );
        SetToolTip();
    }
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setFather( HWND WFather, int Identifier ){
        HWnd_Father = WFather;
        DestroyWindow( HWnd_Owner );
        HWnd_Owner = CreateWindowEx( 0, "BUTTON", NULL, WS_CHILD | BS_BITMAP |
                                     BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_CENTER,
                                     X_Pos, Y_Pos, Width, Height,
                                     WFather, (HMENU)Identifier, NULL, NULL );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, HWnd_Owner, NULL, NULL, NULL );

        SetWindowTextA( HWnd_Owner, W_Text );
        ShowWindow( HWnd_Owner, (int)IsVisible );
        SetToolTip();
    }

    //////
    BOOL SetToolTip( void ){
        RECT Rect;
        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = HWnd_Owner;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_Text[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    BOOL isSelected(){return (SendMessage( HWnd_Owner, BM_GETCHECK, (WPARAM)0, 0 )==BST_CHECKED);}
    //////
    void setSelected( BOOL aFlag ){
        SendMessage( HWnd_Owner, BM_SETCHECK, (WPARAM)(aFlag), 0 );
    }
    //////
    void setBMPResource( char* C_Resource ){
        DeleteObject( HBMP );
        HBMP = LoadBitmap( INSTANCIA_GLOBAL, C_Resource );
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMP );
    }
    //////
    //////
    void setBMPResourceUI( UINT UC_Resource ){
        DeleteObject( HBMP );
        HBMP = LoadBitmap( GetModuleHandle(0), MAKEINTRESOURCE(UC_Resource) );
        if( HBMP==NULL ){
            const int JPG = 5;
            HBMP = loadResImage( JPG, MAKEINTRESOURCE(UC_Resource) );
        }
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMP );
    }
    //////
    void setJPGResource( int J_Resource ){
        DeleteObject( HBMP );
        HBMP = loadResImage( J_Resource, MAKEINTRESOURCE(32) );
        SendMessage( HWnd_Owner, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBMP );
    }
    //////
    void setEnabled( BOOL enabled ){EnableWindow( HWnd_Owner, enabled );}
    //////
}BMPButton_Toggle;


















typedef struct TagStaticStatus{
private:
    HWND               HWnd_Owner;
    HWND               HWnd_Father;
    HWND               StatusBar;
    HWND               HWnd_ToolTip;
    TOOLINFO           TInfo;
    RECT               Rect;
    int                X_Pos;
    int                Y_Pos;
    int                Width;
    int                Height;
    BOOL               IsVisible;
    char               W_Text[1024];
    char               W_ToolTip[512];
public:
    //////
    HWND GetHandle( void ){return HWnd_Owner;}
    //////
    //////
    //////
    int getX( void ){
        return X_Pos;
    }
    //////
    int getY( void ){
        return Y_Pos;
    }
    //////
    //////
    void setText( const char* Text ){
        sprintf( W_Text, "%s", Text );
        SendMessage( StatusBar, SB_SETTEXT, 0,(LPARAM)W_Text );
        //SetWindowTextA( HWnd_Owner, W_Text );
    }
    //////
    int getWidth( void ){
        return Width;
    }
    //////
    int getHeight( void ){
        return Height;
    }
    //////
    //////
    void setLocation( int x, int y ){
        X_Pos = x;
        Y_Pos = y;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
    }
    //////
    void setSize( int width, int height){
        Width  = width;
        Height = height;
        MoveWindow( HWnd_Owner, X_Pos, Y_Pos, Width, Height, true );
        int iStatusWidths[2]= { Width, -1 };
        SendMessage( StatusBar, SB_SETPARTS, 1, (LPARAM)iStatusWidths);
    }
    //////
    void setFather( HWND WFather ){
        W_Text[0] = 0;
        HWnd_Father = WFather;
        //DestroyWindow( HWnd_Owner );
        HWnd_Owner = CreateWindowEx( 0, "STATIC", "STATIC", WS_CHILD, X_Pos, Y_Pos, Width, 22,
                                     WFather, NULL, INSTANCIA_GLOBAL, NULL );
        SetWindowTextA( HWnd_Owner, W_Text );


        StatusBar = CreateWindowEx( 0L, STATUSCLASSNAME, NULL, WS_CHILD | WS_BORDER| WS_VISIBLE,
                                            0, 0, 0, 0, HWnd_Owner, NULL, INSTANCIA_GLOBAL, NULL);
        int iStatusWidths[2]= { Width, -1 };
        SendMessage( StatusBar, SB_SETPARTS, 1, (LPARAM)iStatusWidths);
        SendMessage( StatusBar, SB_SETTEXT, 0,(LPARAM)W_Text );


        DestroyWindow( HWnd_ToolTip );
        HWnd_ToolTip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                       WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                                       0, 0, 0, 0, StatusBar, NULL, NULL, NULL );
        SetWindowPos( HWnd_ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);


        setVisible( IsVisible );
    }
    //////
    //////
    void setToolTip( UINT UText ){
        LoadStringA( GetModuleHandle(0), UText, W_ToolTip, 512 );
        SetToolTip();
    }
    //////
    BOOL SetToolTip( void ){

        GetClientRect ( HWnd_Owner, &Rect );
        TInfo.cbSize = sizeof(TOOLINFO);
        TInfo.uFlags = TTF_SUBCLASS;
        TInfo.hwnd = StatusBar;
        TInfo.hinst = NULL;
        TInfo.uId = 0;
        TInfo.lpszText = &W_ToolTip[0];
        TInfo.rect.left = Rect.left;
        TInfo.rect.top = Rect.top;
        TInfo.rect.right = Rect.right;
        TInfo.rect.bottom = Rect.bottom;
        SendMessage( HWnd_ToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &TInfo );
        return true;
    }
    //////
    void setVisible( BOOL aFlag ){
        IsVisible = aFlag;
        ShowWindow( HWnd_Owner, (int)IsVisible );
    }
    //////
    BOOL isVisible( void ){
        return IsVisible;
    }
    //////
    void setEnabled( BOOL enabled ){
        EnableWindow( HWnd_Owner, enabled );
    }
}StaticStatus;
