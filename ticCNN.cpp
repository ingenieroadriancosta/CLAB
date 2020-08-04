////////////////////////////////////////////////////////////////////////////////

//MTIME///////////////////////// T I M E___S E R I E S /////////////////////////
double TIME_SERIES_CTIC_CNN;//VARIABLES GLOBALES DE TIEMPO.
double TIME_SERIES_CTOC_CNN;//VARIABLES GLOBALES DE TIEMPO.
                                       //
inline void ticCNN()   //TIC -TIC-TIC -TIC-TIC -TIC-TIC -TIC-TIC -TIC-TIC -TIC-TIC " TIC "
{//INICIA LA VARIABLE DE TEIMPO GLOBAL adrianti.
     TIME_SERIES_CTIC_CNN=(double)clock();
}//END TIC.
                                       //
inline double tocCNN()  //TOC -TOC-TOC -TOC-TOC -TOC-TOC -TOC-TOC -TOC-TOC -TOC-TOC " TOC "
 {//RETORNA EL TIEMPO TRANSCURRIDO DESDE QUE SE LLAMÓ LA FUNCION TOC.
      TIME_SERIES_CTOC_CNN=(clock()-TIME_SERIES_CTIC_CNN)/1000.0;
      return(TIME_SERIES_CTOC_CNN);
 }//END TOC.



//////////////////////////////////////////////////////////////////////////////// 
