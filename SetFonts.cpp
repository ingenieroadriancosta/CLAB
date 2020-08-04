BOOL SetFonts( void ){
//
HFontComm = CreateFont( 20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                    DEFAULT_PITCH | FF_ROMAN, "Times New Roman");




HFontButts = CreateFont( 14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                         OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                         DEFAULT_PITCH | FF_ROMAN, "Times New Roman");


HFontFs = CreateFont( 18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                    DEFAULT_PITCH | FF_ROMAN, "Times New Roman");





// 14
HFont = CreateFont( 22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                    DEFAULT_PITCH | FF_ROMAN, "Times New Roman");





HFont_S = CreateFont( HPosEditSend1-4, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                    DEFAULT_PITCH | FF_ROMAN, "Times New Roman");




HFontFsSq = CreateFont( 20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                    DEFAULT_PITCH | FF_ROMAN, "Times New Roman");

return TRUE;
}
