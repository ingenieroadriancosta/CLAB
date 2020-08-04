BOOL MP_EP( void ){
////////////////// C1

IF PermissionAJC THEN
   BUndock.setLocation( 1, 1 );
   BUndock.setSize( 24, 24 );
   BUndock.setFather( Pltrs[0].GetHandleCon(), ID_SET_MAXIM_WIN );
   BUndock.setBMPResource( ID_PIC_UNDOCK );
   BUndock.setVisible( TRUE );
ENDIF;





BtnMp[0].setLocation( 150, 2 );
BtnMp[0].setSize( 38, 23 );
BtnMp[0].setVisible( TRUE );
BtnMp[0].setFather( Pltrs[0].GetHandleCon(), ID_SET_MP1 );
BtnMp[0].setText( "Mp1" );
//
Mp[0].setLocation( BtnMp[0].getX() + BtnMp[0].getWidth() + 1, BtnMp[0].getY() );
Mp[0].setSize( 84, 22 );
Mp[0].setVisible( TRUE );
Mp[0].setFather( Pltrs[0].GetHandleCon() );
////
BtnEp[0].setLocation( Mp[0].getX() + Mp[0].getWidth() + 16, 2 );
BtnEp[0].setSize( BtnMp[0].getWidth(), BtnMp[0].getHeight() );
BtnEp[0].setVisible( TRUE );
BtnEp[0].setFather( Pltrs[0].GetHandleCon(), ID_SET_EPP1 );
BtnEp[0].setText( "Ep1" );
//
Ep[0].setLocation( BtnEp[0].getX() + BtnEp[0].getWidth() + 1, BtnEp[0].getY() );
Ep[0].setSize( Mp[0].getWidth(), Mp[0].getY() );
Ep[0].setVisible( TRUE );
Ep[0].setFather( Pltrs[0].GetHandleCon() );
//////////////////////
//////////////////////
//////////////////////
//////////////////////
//////////////////////
//////////////////////
//////////////////////
////////////////// C2
BtnMp[1].setLocation( Ep[0].getX() + Ep[0].getWidth() + 80, 2 );
BtnMp[1].setSize( BtnMp[0].getWidth(), BtnMp[0].getHeight() );
BtnMp[1].setVisible( TRUE );
BtnMp[1].setFather( Pltrs[0].GetHandleCon(), ID_SET_MP2 );
BtnMp[1].setText( "Mp2" );
//
Mp[1].setLocation(  BtnMp[1].getX() + BtnMp[1].getWidth() + 1, BtnMp[1].getY() );
Mp[1].setSize( Mp[0].getWidth(), 22 );
Mp[1].setVisible( TRUE );
Mp[1].setFather( Pltrs[0].GetHandleCon() );
////
BtnEp[1].setLocation( Mp[1].getX() + Mp[1].getWidth() + 16, 2 );
BtnEp[1].setSize( BtnMp[1].getWidth(), BtnMp[1].getHeight() );
BtnEp[1].setVisible( TRUE );
BtnEp[1].setFather( Pltrs[0].GetHandleCon(), ID_SET_EPP2 );
BtnEp[1].setText( "Ep2" );
//
Ep[1].setLocation( BtnEp[1].getX() + BtnEp[1].getWidth() + 1, BtnEp[1].getY() );
Ep[1].setSize( Mp[1].getWidth(), Mp[1].getHeight() );
Ep[1].setVisible( TRUE );
Ep[1].setFather( Pltrs[0].GetHandleCon() );



BCopy.setLocation( XBOpen, 5 );
BCopy.setSize( 32, 32 );
BCopy.setVisible( TRUE );
BCopy.setFather( Pltrs[0].GetHandleCon(), ID_COPY2CLIPBOARD );
BCopy.setText( ID_STRING_COPY );
BCopy.setJPGResource( ID_PIC_COPY );
BCopy.setVisible( TRUE );




IF DivGraph THEN
   SetParent( BtnMp[1].GetHandle(), Pltrs[1].GetHandleCon() );
   SetParent( Mp[1].GetHandle(), Pltrs[1].GetHandleCon() );
   SetParent( BtnEp[1].GetHandle(), Pltrs[1].GetHandleCon() );
   SetParent( Ep[1].GetHandle(), Pltrs[1].GetHandleCon() );
////////////
   BtnMp[1].setLocation( BtnMp[0].getX(), BtnMp[0].getY() );
   Mp[1].setLocation( Mp[0].getX(), Mp[0].getY() );
   BtnEp[1].setLocation( BtnEp[0].getX(), BtnEp[0].getY() );
   Ep[1].setLocation( Ep[0].getX(), Ep[0].getY() );
ENDIF;
return TRUE;
}
