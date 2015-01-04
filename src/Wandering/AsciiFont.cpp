#include "AsciiFont.h"
#include <iostream>

int AsciiFont::_symbolLengths[AsciiFont::_count];
int AsciiFont::_prefixLength[AsciiFont::_count + 1];
std::string AsciiFont::_data[AsciiFont::_textHeight];
std::string AsciiFont::_dala[112];

void AsciiFont::Initialize() {
	_symbolLengths[' ' - _asciiMin] = 2;
	_symbolLengths['!' - _asciiMin] = 3;
	_symbolLengths['"' - _asciiMin] = 5;
	_symbolLengths['#' - _asciiMin] = 10;
	_symbolLengths['$' - _asciiMin] = 5;
	_symbolLengths['%' - _asciiMin] = 7;
	_symbolLengths['&' - _asciiMin] = 8;
	_symbolLengths['\'' - _asciiMin] = 3;
	_symbolLengths['(' - _asciiMin] = 4;
	_symbolLengths[')' - _asciiMin] = 4;
	_symbolLengths['*' - _asciiMin] = 9;
	_symbolLengths['+' - _asciiMin] = 7;
	_symbolLengths[',' - _asciiMin] = 3;
	_symbolLengths['-' - _asciiMin] = 8;
	_symbolLengths['.' - _asciiMin] = 3;
	_symbolLengths['/' - _asciiMin] = 7;

	_symbolLengths['0' - _asciiMin] = 7;
	_symbolLengths['1' - _asciiMin] = 4;
	_symbolLengths['2' - _asciiMin] = 6;
	_symbolLengths['3' - _asciiMin] = 7;
	_symbolLengths['4' - _asciiMin] = 8;
	_symbolLengths['5' - _asciiMin] = 7;
	_symbolLengths['6' - _asciiMin] = 7;
	_symbolLengths['7' - _asciiMin] = 8;
	_symbolLengths['8' - _asciiMin] = 7;
	_symbolLengths['9' - _asciiMin] = 7;

	_symbolLengths[':' - _asciiMin] = 3;
	_symbolLengths[';' - _asciiMin] = 3;
	_symbolLengths['<' - _asciiMin] = 5;
	_symbolLengths['=' - _asciiMin] = 8;
	_symbolLengths['>' - _asciiMin] = 5;
	_symbolLengths['?' - _asciiMin] = 6;
	_symbolLengths['@' - _asciiMin] = 9;

	_symbolLengths['A' - _asciiMin] = 10;
	_symbolLengths['B' - _asciiMin] = 7;
	_symbolLengths['C' - _asciiMin] = 8;
	_symbolLengths['D' - _asciiMin] = 8;
	_symbolLengths['E' - _asciiMin] = 8;
	_symbolLengths['F' - _asciiMin] = 8;
	_symbolLengths['G' - _asciiMin] = 8;
	_symbolLengths['H' - _asciiMin] = 8;
	_symbolLengths['I' - _asciiMin] = 7;
	_symbolLengths['J' - _asciiMin] = 8;
	_symbolLengths['K' - _asciiMin] = 6;
	_symbolLengths['L' - _asciiMin] = 8;
	_symbolLengths['M' - _asciiMin] = 8;
	_symbolLengths['N' - _asciiMin] = 7;
	_symbolLengths['O' - _asciiMin] = 8;
	_symbolLengths['P' - _asciiMin] = 8;
	_symbolLengths['Q' - _asciiMin] = 8;
	_symbolLengths['R' - _asciiMin] = 8;
	_symbolLengths['S' - _asciiMin] = 8;
	_symbolLengths['T' - _asciiMin] = 9;
	_symbolLengths['U' - _asciiMin] = 8;
	_symbolLengths['V' - _asciiMin] = 10;
	_symbolLengths['W' - _asciiMin] = 14;
	_symbolLengths['X' - _asciiMin] = 7;
	_symbolLengths['Y' - _asciiMin] = 9;
	_symbolLengths['Z' - _asciiMin] = 7;

	_symbolLengths['[' - _asciiMin] = 5;
	_symbolLengths['\\' - _asciiMin] = 7;
	_symbolLengths[']' - _asciiMin] = 5;
	_symbolLengths['^' - _asciiMin] = 4;
	_symbolLengths['_' - _asciiMin] = 8;
	_symbolLengths['`' - _asciiMin] = 3;

	_symbolLengths['a' - _asciiMin] = 7;
	_symbolLengths['b' - _asciiMin] = 7;
	_symbolLengths['c' - _asciiMin] = 6;
	_symbolLengths['d' - _asciiMin] = 7;
	_symbolLengths['e' - _asciiMin] = 6;
	_symbolLengths['f' - _asciiMin] = 5;
	_symbolLengths['g' - _asciiMin] = 7;
	_symbolLengths['h' - _asciiMin] = 7;
	_symbolLengths['i' - _asciiMin] = 3;
	_symbolLengths['j' - _asciiMin] = 5;
	_symbolLengths['k' - _asciiMin] = 6;
	_symbolLengths['l' - _asciiMin] = 3;
	_symbolLengths['m' - _asciiMin] = 11;
	_symbolLengths['n' - _asciiMin] = 7;
	_symbolLengths['o' - _asciiMin] = 7;
	_symbolLengths['p' - _asciiMin] = 7;
	_symbolLengths['q' - _asciiMin] = 7;
	_symbolLengths['r' - _asciiMin] = 6;
	_symbolLengths['s' - _asciiMin] = 5;
	_symbolLengths['t' - _asciiMin] = 5;
	_symbolLengths['u' - _asciiMin] = 7;
	_symbolLengths['v' - _asciiMin] = 7;
	_symbolLengths['w' - _asciiMin] = 10;
	_symbolLengths['x' - _asciiMin] = 6;
	_symbolLengths['y' - _asciiMin] = 7;
	_symbolLengths['z' - _asciiMin] = 5;

	_symbolLengths['{' - _asciiMin] = 5;
	_symbolLengths['|' - _asciiMin] = 3;
	_symbolLengths['}' - _asciiMin] = 5;
	_symbolLengths['~' - _asciiMin] = 5;

	int d = 0;
	_prefixLength[0] = 0;
	for (int i = 0; i < _count; i++) {
		_prefixLength[i + 1] = _prefixLength[i] + _symbolLengths[i];
	}

	_data[0] = "   _  _ _    _  _     _   _   __         _   ____      _                              __";
	_data[1] = "  | |( | ) _| || |_  | | (_) / /  ___   ( ) / /\\ \\  /\\| |/\\    _                     / /";
	_data[2] = "  | | V V |_  __  _|/ __)   / /  ( _ )  |/ | |  | | \\ ` ' /  _| |_     ______       / / ";
	_data[3] = "  | |      _| || |_ \\__ \\  / /   / _ \\/\\   | |  | ||_     _||_   _|   |______|     / /  ";
	_data[4] = "  |_|     |_  __  _|(   / / / _ | (_>  <   | |  | | / , . \\   |_|   _          _  / /   ";
	_data[5] = "  (_)       |_||_|   |_| /_/ (_) \\___/\\/    \\_\\/_/  \\/|_|\\/        ( )        (_)/_/    ";
	_data[6] = "                                                                   |/                   ";
	_data[7] = "                                                                                        ";

	_data[0] += "  ___   __  ___   ____   _  _    _____    __   ______   ___    ___  ";
	_data[1] += " / _ \\ /_ ||__ \\ |___ \\ | || |  | ____|  / /  |____  | / _ \\  / _ \\ ";
	_data[2] += "| | | | | |   ) |  __) || || |_ | |__   / /_      / / | (_) || (_) |";
	_data[3] += "| | | | | |  / /  |__ < |__   _||___ \\ | '_ \\    / /   > _ <  \\__, |";
	_data[4] += "| |_| | | | / /_  ___) |   | |   ___) || (_) |  / /   | (_) |   / / ";
	_data[5] += " \\___/  |_||____||____/    |_|  |____/  \\___/  /_/     \\___/   /_/  ";
	_data[6] += "                                                                    ";
	_data[7] += "                                                                    ";

	_data[0] += "         __        __    ___     ____  ";
	_data[1] += " _  _   / / ______ \\ \\  |__ \\   / __ \\ ";
	_data[2] += "(_)(_) / / |______| \\ \\    ) | / / _` |";
	_data[3] += "      < <   ______   > >  / / | | (_| |";
	_data[4] += " _  _  \\ \\ |______| / /  |_|   \\ \\__,_|";
	_data[5] += "(_)( )  \\_\\        /_/   (_)    \\____/ ";
	_data[6] += "   |/                                  ";
	_data[7] += "                                       ";

	_dala[d++] = "                          ,.--.."; _dala[d++] = "                       ,:'.   .,'V:.::..  ."; _dala[d++] = "                     ,::.,..  . . 'VI:I'.,:-.,."; _dala[d++] = "                    :I:I:.. .   .    MHMHIHI:MHHI:I:,.:."; _dala[d++] = "                   :I:I:.. .   .    MHMHIHI:MHHI:I:,.:."; _dala[d++] = "                   A:I::. ...  .   .MMHHIIHIHI:IHHII:.:,"; _dala[d++] = "                  .M:I::... ..   . AMMMMMHI::IHII::II.::."; _dala[d++] = "                  IMA'::.:.. .    .MMMMMHHII:IMHIHIA:::',"; _dala[d++] = "                  ,MV.:.:.. .     AMMMMHMHI:I:HIHHIIIA;."; _dala[d++] = "                   P.:.:.. .  .  .MMMMMMMHHIIMHHHIIHIIH."; _dala[d++] = "                   :..:.. . .    AMMMMMMMHHI:AMIVHI:HIII:"; _dala[d++] = "                  ,:. :.. .  .    MMMMMMMMMH:IHHI:HHI:HIIH."; _dala[d++] = "                  :..:...  .    .MMMHP:'',,,:HHIH:HHH:HIII"; _dala[d++] = "                 ;.:..:.. .     AMH:'. , , ,,':HII:HHH:HII:"; _dala[d++] = "                 ::..:.. . .   .H:,.. .     ,'.:VA:I:H::HI:"; _dala[d++] = "                ;.:.:... ..    A:.,...     .   ,:HA:IHI::I:"; _dala[d++] = "               ,::..:. . .    .M::. .    .      ,:HA:HH:II:."; _dala[d++] = "               ;.::... ..     AML;,,,       .    .:VHI:HI:I:;"; _dala[d++] = "              ,:.:.:. . .    .H. 'PA,           .:IHH:HHII::."; _dala[d++] = "             ,:.::... ..     A:I:::';, .   .  ,ILIIIH:HI:I:I;"; _dala[d++] = "            ,;:.:.:.. . .   .H:TP'VB,)..   .,;T;,,::I:HI:I:::"; _dala[d++] = "           ,::.:.:.. . .    AI:.':IAAT:.  .(,:BB,);V::IH:I:I;"; _dala[d++] = "         ,::.:.:.. . .    .H:. , . . ..  .':;AITP;I:IIH:I::;,"; _dala[d++] = "        ,::.::.:. . . .   A::.   . ..:.  .  . ..:AI:IHII:I::;."; _dala[d++] = "         ;:.::.:.. .  .   AM:I:.   ..:.   .: . .::HIIIHIIHII::."; _dala[d++] = "        ,:::.:.:..  .    .MM:I:..  .:,    .:.  .::HHIIIHIHII::;"; _dala[d++] = "       ,::.:..:.. .   .  AMM:I:.  . .,'-'',,. ..::HIHI:HI:III:"; _dala[d++] = "       ;:.::..:.. . .   AMMM::. . ,,,, ,..   ,.::IMHIHIHIIHI::;"; _dala[d++] = "      ,:::.:..:. .   .  MMMM:I:.  ,:::;;;::;, .::AMHIHIHHIHHI:'"; _dala[d++] = "      ;::.:.:.. . .   .:VMMV:A:. .  ,:;,,.'  .::AMMMIHIHHIHHII"; _dala[d++] = "     ;::.:.:.. ..  .  .::VM:IHA:. .,,   , . ..:AMMMMHIHHHIHHII:"; _dala[d++] = "     ;:::.:.. .  .. . .::P::IHHAA.. .   .. .:AMMMMMMMIIHHIHHI::"; _dala[d++] = "     ;::.:.. .  . .  ..:.:VIHHHIHHA::,,,,,:AMMMMMMMMMHIIHHHHII;"; _dala[d++] = "     ;.::.. .    . .  ..:.;VHHIHI:IHIHHIHI:MMMMMMMMMMHIHHIHHII:"; _dala[d++] = "     ::.:.. .     ..  ...:.::VHI:IIVIHIHII:MMMMMMMMMMMIHHIHHII:,"; _dala[d++] = "     ;:..:. .    ..  . ..:.::::VAII:IIIIII:MMMMMMMMMMMIHHIIHIIHI"; _dala[d++] = "     ,;:.. .        . .. ..:...:.VII::III:.VMMMMMMMMMHIHHHIHI::I,"; _dala[d++] = "      ;:. . .    , . .. ... . .::.::V::II:..VMMMMMMMMHIHHHIHI::I;"; _dala[d++] = "      ;:.. . .     . .. ..:..  .::...:VIITPL:VMMMMMMMVIHHHIH:. :;"; _dala[d++] = "      ;:. .  .    . .. ... .   ..:.:.. .:IIIA:.MMMMMVI:HIHIH:. .:"; _dala[d++] = "      I:. . .   . .. . .. . . . . ..:.. ..::IIA.VMMMVIHIIHIV:. .,"; _dala[d++] = "      I:..    . . .. .... .  .   . .. ... .:.:IA:.VMVIMHIHIH:..:"; _dala[d++] = "      I.. .  .  . ..... .       .  . .. . .. .:IIAV:HIMHHIHII:.;"; _dala[d++] = "      :. ..   . . .:.. .          .  .. ... ..::.:CVI:MHHIHHI..."; _dala[d++] = "      :..  . . .. ..:.               . . ... .:.:::VHA.VIHHMI:.."; _dala[d++] = "      :. .. .  . ..:..        . .     . .  ..  .. ...:VIIHIHI: ."; _dala[d++] = "      ,:.. .  . .::. .       .::,.      .    .  . .  ...V:IHII.."; _dala[d++] = "       ;:.. .. .:I:.        ..:T'::.     .  . .  .  . .  .VIIH:."; _dala[d++] = "       ;:.:.. .:I:..        .::V:::.         . . . .  .    VIII.."; _dala[d++] = "       ;:.. ..::::. .        ..::. .      .  . .. . .  .    VIII."; _dala[d++] = "       I:.:.. .:I:.           ..:.,        . . .. :. .  .    'VI:."; _dala[d++] = "       I::......::.  .                    . .. .:.:.:. .       'I:"; _dala[d++] = "       II::.. ..::. .       .    .     . .. .. .::::.. .      .:."; _dala[d++] = "       II::.:. ..::. .  . .   .    .     .:. . .:I:::. .       .::HD"; _dala[d++] = "       ,I:::.. .: . .. ..  .. . .    .  .::. . .:I:. .         .:V:"; _dala[d++] = "        I:. .. .  . . ... ..  .. . .    .. ..  ..::.             .:."; _dala[d++] = "        I:.. .. .  ..:.. .. .. ..  . .      .   .                . :"; _dala[d++] = "        ;:.... . ..:::I:.. ..:.. ... .::. . ... . ..              .I."; _dala[d++] = "        ::.:....::.::I:III:I::::I:II:I::.. .:.. . .:. .     .  . .AI:"; _dala[d++] = "        ,::.:...:..::::::III::II::::::.. ...::. .  .::. . .. .  .AMMI."; _dala[d++] = "          :::.:.:. ..::::III:II:I:::.:. .. ..::.. ..  ..::,.  ..::HMMI:"; _dala[d++] = "         ,:::.:.. ...::I:::I:I:::.:.. :. . ..::.. . . . .,PTIHI:IIHHI:."; _dala[d++] = "          ::I::.:...:::II:I::.:....:.:. . ...::. .  . .  .AI:IHI,,:,  ,."; _dala[d++] = "          ,:::.:... ..I::I::.:....:. .: .. ...::. .  .   III:II:.  ,"; _dala[d++] = "           ,I:::..:...:.::I::.:..:. .: .. . ..:... .  .  III.I,"; _dala[d++] = "            VI:::.::.::...:II::...:...:. . . .:::. . .   :,,"; _dala[d++] = "            ,HI:I::.::.::..:II::.:..:.... . .:.:I:.. .   :"; _dala[d++] = "             VI:I:I::.::.:...:I:::I:::.... ..:.:I::...   :"; _dala[d++] = "             ,II:I::II:I:::.:.:I:III:I:... ....::::... .  :"; _dala[d++] = "              VII::I::I::.::..:.::II::.:.. . .:.::::. .   ."; _dala[d++] = "               VI:.:..::II:::..:..::.... .   ..::I::...  . ."; _dala[d++] = "               ,I::.. ..::II::..:.::.... . ...::I:::.   .  ."; _dala[d++] = "                V::.:.. .:I:II::.:..::.. .. ...:::I::..  . . ."; _dala[d++] = "                I:::.:....::III:::.:..:.:.. .:.:II:::. .  . . ."; _dala[d++] = "                I::.:::...:::II::.:.:.:... ...:II::.. . . . .  ."; _dala[d++] = "                I::..:...:.:::.:.:.:.:..:.. .:II:. .. .    . .   ."; _dala[d++] = "               .::.:.:....:.:::.:.:.:.:.: . .:I:... . . . . .  .  ."; _dala[d++] = "               :.:.:...:.:.:::.::.:.::.... .:::.. .. .  . .  . ."; _dala[d++] = "              .:. ..:.:.:::.:..::.::.:.. . .::.. .. . . .  . . .   :"; _dala[d++] = "             .:. .:....::..:.:.:.:.:... .. .NI:.. . .. . . .  . .  :."; _dala[d++] = "            .:. . . ..:.:.::.::.::.::.::.. . :.:.. .. .. . . . . . .)O"; _dala[d++] = "           .:.. ... .. ..:.::.::.:::.:..:.. . ..:.. .. .. . .. . . ,()"; _dala[d++] = "           ::.:. ...:.. ..:..::..::.:.:.:.:. .:.:... .. .. .:.. ..0OO."; _dala[d++] = "          /:::.:...:.:..:..:..::.::.::.:..:..:.:..:.... ..:.:..:.()',"; _dala[d++] = "        (0):::.::...:..:..:...::::I:.:I:.:.:.::.::..:.:...:..::O0O... ."; _dala[d++] = "         : ::.:..:.:..:.:..:.:I:.::I:::I::.:I::.I:.::..:.:.::.:/0O/.. ."; _dala[d++] = "        .:: ::I:.:..::.::.::.::I:::I::.:I::.::I::.:::.::.I::( ):.:..  ."; _dala[d++] = "        '.:: ::I:.:..::.::.::.::I:::I::.:I::.::I::.:::.::.:I::( ):.:.. ."; _dala[d++] = "        ::I:::,(,,)OO::.:.::.::III:::III::III::I:::::.:I:'V0O:., .   ."; _dala[d++] = "       .:::I::I::-:000::..:::.::::III:I::I::II::I:::IIII( ),) .    . . ."; _dala[d++] = "       .:.::I::II:I(,)(  )00):.::.::II:I:II:I:I:::III0OO'.M:M.   . . ."; _dala[d++] = "       .. .:.::.:I:I:IIHHI000 ,)OO:II:O:II:III::OO(')00//XXVM . .. . . ."; _dala[d++] = "       . .. ..:.::.::II:II:III,(0O0'')!0:III:(0OO)..AMV AXXXXI .. .. . ."; _dala[d++] = "       . :.. . .::I:IIIHHII:IHIHH(0),,0OOO( )M00AMMHMM,,XXXXXX.. . .  ."; _dala[d++] = "      .:.:.:.. . ..:IHHHII::::.,.MMIIIMMXIMMMMMMMMMMV AXXXV:MI. .. .  ."; _dala[d++] = "      ::.:.:.:.:.. . ,,., .. ..:.MMIII:MMIMMMMMMMMMMMM, .X::M.MI.. . . ."; _dala[d++] = "     .::.::..::.:.:.:. .  .. .::AMMXXXIAMHMMIHMMMMMMV ...::M.MM ... . .."; _dala[d++] = "     ::.::.::.::.::.:.:.. . .:::MMXXXXI:.:VMMHMPMHVMI ..:I:H-,',,.:. . ."; _dala[d++] = "    ::.::..:.:.:..:.:.::.:. . .:MMXXX:IXX:MMMMMLMMAM, ..I:M.  :  ,:.. ."; _dala[d++] = "   .::.:..:...:...::.:.::I::...IMM:XXX:XX:LMMMMMI:MV  ..I:V   .   :... ."; _dala[d++] = "   :.:.:..:.:.:..:..:::II:II:'..M'.VMXX:XXMMMMMMMI.I ...IVI   .  .::. .."; _dala[d++] = "  :.:.:.:.:.:.::...:.::IHI, - . .'VIMHX:XIIMMV/IMLMI ...HV     .  ::.. ."; _dala[d++] = " .::.:.:.:.:..:.. ..::IHI:-.  . .  ',IX:XXIVMI XMMV I...HI    .   :::..."; _dala[d++] = ".::.:.:.:.:.:.. ...:.:IHHHI:., .    .XXX:XX.MMAXMHA I..AMI    .    ::..."; _dala[d++] = "::.::.::.:.:.... .:.:IHHIHI'. ..    :XXX:XX:MHHIMMMAI,AHHI     .  :::..."; _dala[d++] = ":::.:.:.:.:.:.. .:.::IHHHHI:  ..   ,:XXX:XX:MV''.I,V:,:HHI.    .   :::.."; _dala[d++] = "::.::.:.:..:.. ...::IIHHHHI:   .   :.XXX:XXXI:.,.    '-VH:    .    ::.:."; _dala[d++] = ":::.::..:..:.. ..:.:IHHHHHI,   .    ::XX:XXXI:.A. .  'VHH      .   :::.."; _dala[d++] = "::.::.::.:... ...:::IIHHHIH   ..    :IAX:XXXIHHH:  .  .:MI    .   .:::.."; _dala[d++] = ":::.::.:..... ..:.::IIHHIHH   .     ::XX:IXXIHHV .     'V. . . .  :I:::."; _dala[d++] = ":.::.:.:... ...:.::IIIHHHIH    .    I:XX:XXVHMMI .      I.. .:. . .I::.:"; _dala[d++] = "::.:::.:.... ..:.::IIIHIHHH.  .     :'XX:XXXVIVI  . .   ::..:. .   CLOHE";
	_data[0] += "           ____    _____  _____   ______  ______   _____  _    _  _____       _  _  __ _       __  __  _   _   ____   _____    ____   _____    _____  _______  _    _ __      ____          ____   ____     __ ______";
	_data[1] += "    /\\    |  _ \\  / ____||  __ \\ |  ____||  ____| / ____|| |  | ||_   _|     | || |/ /| |     |  \\/  || \\ | | / __ \\ |  __ \\  / __ \\ |  __ \\  / ____||__   __|| |  | |\\ \\    / /\\ \\        / /\\ \\ / /\\ \\   / /|___  /";
	_data[2] += "   /  \\   | |_) || |     | |  | || |__   | |__   | |  __ | |__| |  | |       | || ' / | |     | \\  / ||  \\| || |  | || |__) || |  | || |__) || (___     | |   | |  | | \\ \\  / /  \\ \\  /\\  / /  \\ V /  \\ \\_/ /    / / ";
	_data[3] += "  / /\\ \\  |  _ < | |     | |  | ||  __|  |  __|  | | |_ ||  __  |  | |   _   | ||  <  | |     | |\\/| || . ` || |  | ||  ___/ | |  | ||  _  /  \\___ \\    | |   | |  | |  \\ \\/ /    \\ \\/  \\/ /    > <    \\   /    / /  ";
	_data[4] += " / ____ \\ | |_) || |____ | |__| || |____ | |     | |__| || |  | | _| |_ | |__| || . \\ | |____ | |  | || |\\  || |__| || |     | |__| || | \\ \\  ____) |   | |   | |__| |   \\  /      \\  /\\  /    / . \\    | |    / /__ ";
	_data[5] += "/_/    \\_\\|____/  \\_____||_____/ |______||_|      \\_____||_|  |_||_____| \\____/ |_|\\_\\|______||_|  |_||_| \\_| \\____/ |_|      \\___\\_\\|_|  \\_\\|_____/    |_|    \\____/     \\/        \\/  \\/    /_/ \\_\\   |_|   /_____|";
	_data[6] += "                                                                                                                                                                                                                     ";
	_data[7] += "                                                                                                                                                                                                                     ";

	_data[0] += " ___ __      ___  /\\          _ ";
	_data[1] += "|  _|\\ \\    |_  ||/\\|        ( )";
	_data[2] += "| |   \\ \\     | |             \\|";
	_data[3] += "| |    \\ \\    | |               ";
	_data[4] += "| |     \\ \\   | |               ";
	_data[5] += "| |_     \\_\\ _| |               ";
	_data[6] += "|___|       |___|     ______    ";
	_data[7] += "                     |______|   ";

	_data[0] += "        _                _         __         _      _    _  _     _                                                    _                                             ";
	_data[1] += "       | |              | |       / _|       | |    (_)  (_)| |   | |                                                  | |                                            ";
	_data[2] += "  __ _ | |__    ___   __| |  ___ | |_   __ _ | |__   _    _ | | __| | _ __ ___   _ __    ___   _ __    __ _  _ __  ___ | |_  _   _ __   ____      ____  __ _   _  ____";
	_data[3] += " / _` || '_ \\  / __| / _` | / _ \\|  _| / _` || '_ \\ | |  | || |/ /| || '_ ` _ \\ | '_ \\  / _ \\ | '_ \\  / _` || '__|/ __|| __|| | | |\\ \\ / /\\ \\ /\\ / /\\ \\/ /| | | ||_  /";
	_data[4] += "| (_| || |_) || (__ | (_| ||  __/| |  | (_| || | | || |  | ||   < | || | | | | || | | || (_) || |_) || (_| || |   \\__ \\| |_ | |_| | \\ V /  \\ V  V /  >  < | |_| | / / ";
	_data[5] += " \\__,_||_.__/  \\___| \\__,_| \\___||_|   \\__, ||_| |_||_|  | ||_|\\_\\|_||_| |_| |_||_| |_| \\___/ | .__/  \\__, ||_|   |___/ \\__| \\__,_|  \\_/    \\_/\\_/  /_/\\_\\ \\__, |/___|";
	_data[6] += "                                        __/ |           _/ |                                  | |        | |                                                __/ |     ";
	_data[7] += "                                       |___/           |__/                                   |_|        |_|                                               |___/      ";

	_data[0] += "   __ _ __    /\\/|";
	_data[1] += "  / /| |\\ \\  |/\\/ ";
	_data[2] += " | | | | | |      ";
	_data[3] += "/ /  | |  \\ \\     ";
	_data[4] += "\\ \\  | |  / /     ";
	_data[5] += " | | | | | |      ";
	_data[6] += "  \\_\\| |/_/       ";
	_data[7] += "     |_|          ";

	for (int i = 0; i < _textHeight; i++)
		if (_data[i].length() != _prefixLength[_count]) {
			int x = _data[i].length();
			int y = _prefixLength[_count];
			std::string str = _data[i];
			throw 1;
		}
}

void AsciiFont::MeasureText(const std::string& text, int& outAsciiWidth, int& outAsciiHeight) {
	outAsciiWidth = 0;
	outAsciiHeight = _textHeight;

	for (int i = 0; i < text.length(); i++) {
		outAsciiWidth += _symbolLengths[text[i] - _asciiMin];
	}
}

std::string* AsciiFont::GetData() { return _dala; }

std::string AsciiFont::ConvertText(const std::string& text) {
	int wid, hei;
	MeasureText(text, wid, hei);

	char* arr = new char[wid * hei];

	for (int i = 0, j = 0; i < text.length(); i++) {
		int sWid = _symbolLengths[text[i] - _asciiMin],
			pLen = _prefixLength[text[i] - _asciiMin];
		for (int x = 0; x < sWid; x++) {
			for (int y = 0; y < _textHeight; y++) {
				arr[y * wid + j + x] = _data[y][pLen + x];
			}
		}
		j += sWid;
	}

	std::string str = std::string(arr, wid * hei);
	delete[] arr;
	return str;
}