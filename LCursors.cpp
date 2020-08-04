BOOL LCursors( void ){

SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );

HICON HIcon = LoadIconA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_PIC_CURSORI) );
ICONINFO IINFO_I;



GetIconInfo( HIcon, &IINFO_I );

// GetIconInfo( HCursor, &IINFO );
HCurHand = CreateIconIndirect( &IINFO_I );
DeleteObject( HIcon );


HIcon = LoadIconA( INSTANCIA_GLOBAL, MAKEINTRESOURCE(ID_PIC_CURSORDI) );
GetIconInfo( HIcon, &IINFO_I );

// GetIconInfo( HCursor, &IINFO );
HCurDHand = CreateIconIndirect( &IINFO_I );
DeleteObject( HIcon );
SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCurHand );


SetClassLongA( Pltrs[0].GetHandleCon(), GCL_HCURSOR, (LONG)HCursorG );

return TRUE;
}
