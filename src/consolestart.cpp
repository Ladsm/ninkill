#include <iostream>
#include <string>
#include "boot.hpp"

std::string getcommand() {
	std::string getstring = "";
	std::getline(std::cin, getstring);
	return getstring;
}

void listdir() {
	std::cout << "                 Directory: /mnt/\n\n";
	std::cout << " Mode     LastWriteTime       Name         Size   \n";
	std::cout << " ----     -------------       ----         ----   \n";
	std::cout << "-a----  3/24/1998 6:28 PM  NINKill.exc   2,865kb  \n";
	std::cout << "-a----  1/14/1998 3:04 AM    help.txt      1kb    \n";
	std::cout << "-a----  4/26/1996 8:02 PM   NINEX.exc    6,462kb  \n";
}

void help() {
	std::cout << "(c)Nuebine incorperated Network\n";
	std::cout << "Thank you for using the Nuebine incorperated Network operating system.\n";
	std::cout << "We hope you enjoy your stay!\n";
	std::cout << R"(To open the operating system's internet navagator, write : "nin-iexc")" << '\n';
	std::cout << R"(To open the operating system's forum software, write : "nin-fexc")" << '\n';
	std::cout << "You are right now in the live environment. Heres some commands you can try:";
	std::cout << "\nhelp: displays the help screen.\nexit: exits the live environment.\nls & dir: lists the directory you're in.\n";
	std::cout << "cls & clear: clears the console\ncat [filename]: reads file to you.\nlsblk: prints all storage devices\n";
}
int stateOfvdc = 0;
int readcommand(std::string command) {
	if (command == "nin-fexc") {
		return 1;
	}
	else if (command == "nin-iexc") {
		return 2;
	}
	else if (command == "ls" || command == "dir") {
		listdir();
		return 0;
	}
	else if (command == "cls" || command == "clear") {
#if defined(_WIN32)
		system("cls");
#endif
#if defined(__linux__)
		system("clear");
#endif
	}
	else if (command == "help"|| command == "cat help.txt") {
		help();
		return 0;
	}
	else if (command == "cat NINKill.exc") {
		std::string randombinary = R"(
NINKILL forum software owned by Nuebine incorperated Network
קְ׀”8*צ¸‚vjbL>2ˆ
צלאײ־ֶ¼´
× ‚tjbXH>|l\Fעה־ֲ |jX°
(NZSHGetKnownFolderPathSHELL32.dllGetStdHandletBeep%GetConsoleMod
e?SetConsoleMode+GetConsoleScreenBuf
ferInfoKERNEL32.dllCoTaskMemFreeole32.dllm??0_Lockit@std@@QEAA@H@Z¥??1_Lockit@std@@QEAA@XZ&?uncaught_exception@std@@YA_NXZ–?_Xlength_error@std@@YAXPEBD@Zֽ?good@ios_base@std@@QEBA_NXZo?flags@ios_base@std@@QEBAHXZF?width@ios_base@std@@QEBA_JXZE?wi
dth@ios_base@std@@QEAA_J_J@Zז?sputc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAH
D@Zי?sputn@?$basic_str
eambuf@DU?$
char_traits@D@std@@
@std@@QEAA_JPEBD_J@Zֽ?setstate@?$basic_ios@DU
?$char_traits@D@std@@@std@@QEAAXH_N@Z?tie@?$basic_ios@DU?$char_traits@D@std@@@std@@QEBAPEAV?$basic_ostream@DU?$char_traits@D@std@@@2@XZ?rdbuf@?$basic_ios@DU?$char_traits@D@std@@@std@@QEBAPEAV?$basic_streambuf@D
U?$char_traits@D@std@@@2@XZi?fill@?$basic_ios@
DU?$char_tr

aits@D@std@@@std@@QEBADXZL?_Osfx@?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAXXZp?flush@?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAAEAV12@XZ¼?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A—?_Xo
ut_of_range@std@@YAXPEBD@Z?_G
etgloballocale@locale@std@@CAPEAV_Locimp@12@XZ?is@?$ctype@D@std@@QEBA_NFD@Z¾?_Getcat@?$ctype@
D@std@@SA_KPEAPEBVfacet@locale@2@PEBV
42@@Zֻ?getloc@ios_base@std@@QEBA?AVlocale@2@XZ?sbumpc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHXZ׳?sgetc@
?$basic_streambuf@DU?$char_tr
aits@D@std@@@std@@QEAAHXZא?snextc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHXZ<?widen@?$basic_ios@DU?$char_tra
its@
D@std
@@@std@@QEBADD@Z!?_Ipfx@?$basic_istream@DU?$char_traits@D@std@@@std@@QEAA_N_N@Z??5?$basic_istream@DU?$char_traits@D@std@@@std@@QEAAAEAV01@P6AAEAV01@AEAV01@@Z@Zצ?_Id_cnt@id@locale@std@@0HA׳?id@?$ctype@D@std@@2V0locale
@2@A«?cin@std@@3V?$basic_istream@DU?$char_tr
aits@D@std@@@1@A˜_Query_perf_cou
nter™_Query_perf_frequency/??0?$basic_str
eambuf@DU?$char_traits@D@std@
@@std@@IEAA@XZ‏?swap@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAXAEAV12@@Z‰??1?$basic_streambuf@DU?$char_trait
s@D@std@@@std@@UEAA@XZU?e
ack@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEB
APEADXZ־?gptr@?$basic_streambuf@DU?$
char_traits@D@std@@@std@@IEBAP
EADXZF?pbase@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IE
BAPEADXZO?pptr@?$basic_streambuf@DU?$char_traits@D
@std@@@std@@IEBAPEADXZX?egptr@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEBAPEADXZs?gbump@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAXH@Zֲ?setg@?$basic_stream
buf@DU?$char_traits@D@std@@@s
td@@IEAAXPEAD00@Za?epptr@?$basic_str
eambuf@DU?$char_traits@D@std@@@std@@IEBAPEADXZַ?setp@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAXPEAD0@Zֶ?setp@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAXPEAD00@ZR?_Pninc@?$basic_streambuf@DU?$char_tr
aits@D@std@@@std@@IEAAPEADXZ}??1?$basic_ios@DU?$cha
r_traits@D@std@@@std@@UEAA@XZ
                                                                       ??0?$basic_ios@DU
?$char_traits@D@std@@@std@@IEAA@XZ
                              ??6?$basic_ostream@DU?$
char_traits@D@std@@@std@@QEAAAEAV01@P6AAEAV01@AEAV01@@Z@Zi?put@?$basic_ostrea

m@DU?$char_traits@D@std@@@std@@QEAAAEAV12@D@Z??0?$basic_iostream@DU?$char_traits@D@std@@@std@@QEAA@PEAV?$basic_streambuf@DU?$char_traits@D@std@@
@1@@Zץ?swap@?$basic_iostream@DU?$char_traits@D@std@@@std@@IE
AAXAEAV1~~~ console: mkfs.mfs /dev/vdc 2@@Z€??1?$basic_iostream@DU?$c
har_traits@D@std@@@std@@UEAA@XZ‏?
imbue@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MEAAXAEBVl
ocale@2@@Z?sync@?$bas
ic_streambuf@DU?$char_traits@D@std@@@std@@MEAAHXZ½?setbuf@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MEAAPEAV12@PEAD_J@ZN?xsputn@?$basic_streambuf@DU?$char_traits@
D@std@@@std@@MEAA_JPEBD_J@ZK
?xsgetn~~~ console: arr /dev/vdc @?$basic_streambuf@DU?$char_traits@D@std
@@@std@@MEAA_JPEAD_J@Z#?ufl
ow@?$basic_streambuf@DU?$char_
traits@D@std@@@std@@MEAAHX
Z?showmanyc@?$basic_s~~~ console: ifo /dev/vdc treambuf@DU?$char_traits@D@std@@@std@@MEAA_JXZ‡?_Unlock@?$basic_streambuf@DU?$char_traits@D@std@@@std@@UEAAXXZ0?_Lock@?$basic_streambuf@DU?$
char_traits@D@std@@@std@@UEAAXXZ
??6?$basic_ostream@DU?$char_traits@
D@std@@@std@@QEAAAEAV01@H@Z??6?$basic_ostream@DU?$char_traits@D@std@@@st
d@@QEAAAEAV01@_K@Z“?_Xbad_alloc@std@@YAXXZ{
?_Syserror_map@std@@YAPEBDH@Z?_Wi
nerror_map@std@@YAHH@Z׀?_Getcvt@_Locinfo@std@@QEBA?AU_Cvtvec@@XZ?_W_Getdays@_Locinfo@std@@QEBAPEBGXZ‹?_W_Getmonths@_Locinfo@
std@@QEBAPEBGXZ¥?always_noconv@codecvt_base@std
@@QEBA_NXZ?in@?$codecvt@DDU_Mbstatet@@@std@@QEBAHAEAU_Mbstatet@@PEBD1AEAPEBDPEAD3AEAPEAD@Z;?out@
?$c
odecvt@D
DU_Mbstatet@@@std@@QEBAHAEAU_Mbstatet@@PEBD1AEAPEBDPEAD3AEAPEAD@Z/?unshift@?$codecvt@DDU_Mbstatet@@@std@@QEBAHAEAU_Mbstatet@@PEAD1AEAPEAD@Z¹?_Getcat@?$codecv
t@DDU_Mbstatet@@@std@@SA_KPEAPEBVfacet@locale@
2@PEBV42@@Z8??Bios_base@std@
@QEBA_NXZָ?getloc@?$basic_streambuf@DU?$char_traits@D@std@@@std@
@QEBA?AVlocale@2@XZם?_Gndec@?$basic_streambuf@DU?$c
har_traits@D@std@@@std@
@IEAAPEADXZנ?_Gninc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAPEADXZך?_Gnavail@?$basic_streambuf@DU?$char_traits@D@std@@@s
td@@IEBA_JXZI?pbump@?$basic_streambuf@DU
?$char_traits@D@std@@@std@@IEAAXH@ZO?_Pnavail@?$basic_streambuf@DU?$char_traits@D@st
d@@@std@@IEBA_JXZ‎?_Init@?$basic_s
treambuf@DU?$char_traits@D@std@
@@std@@IEAAXXZ?_Init@?$basic_s
treambuf@DU?$char_traits@D@std@@@std@@IEAAXPEAPEAD0PEAH001@Z%??0?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAA@PEAV?$basic_streambuf@DU?$char_traits@D@
std@@@1@_N@Z†??1?
$basic_ostream@DU?$char_traits@D@std@@@s
td@@UEAA@XZ␦??0?$basic_istream@DU?$char_tr
aits@D@std@@@std@@QEAA@PEAV?$basic_streambuf@DU?$char_traits@D@std@@@1@_N@Zƒ??1?$basic_istream@DU?$char_traits@D@std@@@std@@UEAA@XZµ?_Fiopen@std@@YAPEAU_iobuf@@PEB_WHH@Zׁ?id
@?$codecvt@DDU_Mbsta
tet@@@std@@2V0locale@2@AMSVCP140D.dll<me
mcpy=memmove!__std_exception_copy"__std_e
xception_destroy_CxxThrowException__CxxFrameHandler4;memcmp>memset␦GetSystemTi
meAsFileTimeInitializeSListHe
ad|HeapAlloc€HeapFreeהGetP
rocessHeapVirtualQueryװFreeLibrary@@}@g@g@g
‚@€0
)";
		std::cout << randombinary << '\n';
	}
	else if (command == "cat NINEX.exc") {
		std::string randombinary = R"(
NINKILL Internet software owned by Jack Wilder Dean and Nuebine incorperated Network
License by Jack Wilder Dean:
The software is provided "As is", without warranty of any kind, express or
Implied, including but not limited to the warranties of merchantability,
Fitness for a particular purpose and noninfringement. You may not try to: data mine, reverse engineer or find out more about this software via non disclosed means.
By viewing this text here, you are infringeing on my license, you may turn back and forget about this.
This software is only owned due to a legel battle, please: visit www.jackwd.com for more info
-------------------------------------------------------------------------------------------------------------
ַ‏ טw״H‹א   ט׃H‹…א   H‹ָט ־H‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּL‰D$ˆT$H‰L$UWHלט   Hl$ H
R‏ ט״H‹…א   H‹ָט0H‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
צ‎ ט¦׳H‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּL‰D$ˆT$H‰L$UWHלט   Hl$ H
¢‎ טR׳H‹…א   H‹ָטˆֽH‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
F‎ טצײH‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלר   Hl$ H
ר ט¦ײH‹ר   טףׁH‰…ְ   H‹ר   ט®ׁH‰…ָ   L‹…ְ   H‹•ָ   H‹נ   טjײH¥״   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHל¸  Hl$ H|$ ¹6   ¸ּּּּף«H‹$״  H‹8| H3ֵH‰…€  H
h טלױַE    H‹¸  טmׂH‰E(H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָז־ H…ְ~[H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָ½־ H;E(~1H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָ“־ H+E(H‰…h  כHַ…h      H‹…h  H‰EHH‹•°  HMhטך־HMhט>ױ¶ְ…ְu‹Eƒָ‰Eיb  H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָ־ %ְ  ƒר@„ֶ   כH‹EHHָH‰EHHƒ}H ®   H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָsֽ H‰…h  H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָ@ֽ ˆ…p  ¶•p  H‹h  Vֽ ‰…t  ‹…t  ‰…x  טֺ‰…|  ‹•x  ‹|  ט־¶ְ…ְt‹Eƒָ‰Eכי<ƒ} u`H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָ¿ּ H‰…h  L‹E(H‹•¸  H‹h  ְּ H‰…p  H‹E(H9…p  t	‹Eƒָ‰Eƒ} …ֶ   כH‹EHHָH‰EHHƒ}H ®   H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָ=ּ H‰…h  H‹…°  H‹ Hc@H‹°  HָH‹ֱH‹ָ
ּ ˆ…p  ¶•p  H‹h   ּ ‰…t  ‹…t  ‰…x  טVֹ‰…|  ‹•x  ‹|  טTֽ¶ְ…ְt‹Eƒָ‰Eכי<H‹…°  H‹ Hc@H‹°  HָH‹ֱH‰…h  3ׂH‹h  ךֻ כ H‹…°  H‹ Hc@H‹°  HָH‹ֱH‰…h  E3ְ‹UH‹h  bֻ H‹…°  H‰…X  HMhטDׁH‹…X  H‹רHMאH­ט ט£ֻH‹ַH‹€  H3ֽט¾ֻH¥˜  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
Kק ט׀Hƒ½א    u3ְכAטַ¶ְ…ְtH‹א   טֺכ'H½א      rH‹א   ט״ֿכH‹א   טuֺH¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
¦צ טV׀H‹…ט   H‹H‹א   טוֺH¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
Fצ טצֿH‹…ט   H‹H‹א   טֶH¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלH  Hl$ H
טץ ט–ֿH‹…H  H‹ HְH‹H  H‰HַE    H‹•H  H‹@  טׂH‰Eטrֶ¶ְ…ְtKH‹MטֶH‰E(HַEH    כH‹EHHְH‰EHH‹…H  H‹ H9EHsH‹EHH‹M(HָH‹ֱH‹ָטH־כּH‹…H  H‹ HָH‹H  H‰H‹EH¥(  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלX  Hl$0H
פ ט‹־H‹…@  Hƒְ/H‰EH‹…@  H9Ewט4ּH‹Mט)ָH‰E(Hƒ}( uBH׃ך H‰D$(Hך H‰D$ E3ֹA¸ֲ   Hׂך ¹   קֺ ƒרuּ3ְ¹   ֽ)H‹E(Hƒְ/HƒאאH‰EH¸   HkְH‹MHH‹U(H‰¸   Hkְ‏H‹MHH÷תתתתתתתתH‰H‹EHH¥(  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּL‰D$H‰T$H‰L$UWHלר  Hl$ H|$ ¹F   ¸ּּּּף«H‹$  H‹ƒs H3ֵH‰…ָ  H
‰ף ט7ֽH‹…נ  H‰EH‹נ  ט ִH9…   vטֻH‹נ  ט¢ֵH‰E(H‹U(HMDטֻּL‹EHUDHMhט־Hƒ½   wzH‹EH‹   H‰HH‹EHַ@    H‹EHƒְL‹…   H‹•ר  H‹ָטַֶ…”   H‹EH‹   HDH•”  H‹ָט>ֳHMhטרַHMhט(ֿיױ   H‹נ  ט1ֳL‹ְ÷   H‹   טֳH‰…˜   H•˜   H‹M(טםַH‰…¸   H‹EHƒְH•¸   H‹ָטֻH‹EH‹   H‰HH‹EH‹˜   H‰H H‹¸   ט!ֳL‹…   H‹•ר  H‹ָטDֶֶ…´   H‹¸   טקֲH…   H•´  H‹ָטdֲHMhטַHMhטN־HMאHעה ט״ִH‹ָ  H3ֽטצִH¥״  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּL‰D$H‰T$H‰L$UWHלָ  Hl$ H|$ ¹:   ¸ּּּּף«H‹$ט  H‹ֳp H3ֵH‰…  H
ֹנ טwֺH‹…ְ  H‰EH‹ְ  ט@ֱH9…׀  vטֹH‹ְ  טגֲH‰E(H‹U(HMDטֺL‹EHUDHMhט\ֻHƒ½׀  wRH‹EH‹׀  H‰HH‹EHַ@    H‹EHƒְA¸   H‹•ָ  H‹ָט
ֱHMhט`ֵHMhטּי¿   H‹ְ  ט™ְL‹ְ÷   H‹׀  ט€ְH‰…˜   H•˜   H‹M(טUֵH‰…¸   H‹EHƒְH•¸   H‹ָטpָH‹EH‹׀  H‰HH‹EH‹˜   H‰H H‹…׀  HְH‰…ˆ  H‹¸   טxְH‹ˆ  L‹ֱH‹•ָ  H‹ָטFְHMhטִHMhטֻּHMאHה טVֲH‹  H3ֽטtֲH¥¨  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHל  Hl$ H
yמ ט6ָטH¿¶ְ…ְtH‹   טJֳH‹•  H‹ָטbֹכ4H‹   ט,ֳH‹׀¹   טֵH‰…ָ   H‹…ָ   H‹  H‹	H‰H¥ט   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHל  Hl$ H
ֹם ט†ַט˜¾¶ְ…ְtH‹   טCִH‹•  H‹ָטבֶכ7H‹   ט%ִH‹׀¹   טאִH‰…ָ   H‹…  H‹H‹ָ   טֶH¥ט   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּL‰L$ L‰D$H‰T$H‰L$UWHל˜  Hl$ H|$ ¹.   ¸ּּּּף«H‹$¸  H‹l H3ֵH‰…h  H
יל ט’ֶH‹  טֹH‰EH‹UHM$ט‹¾H‹…  H‰EHL‹EHHU$HMhט’ַHƒ½˜   tgH‹•˜  H‹  ט¿H‹…  H‰…˜   L‹MH‹EHL‹@H‹…¨  H‹H‹…   H‹טk¿H‹MHH‰AHַ…˜       H˜   טQִHMhטhֱHMhט˜ָHMאH¼ ט"¿H‹h  H3ֽט@¿H¥x  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
{כ ט+ֵH‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
6כ טזִטר»¶ְ…ְtH‹א   טַכ5H½ט      rH•ט   Hא   טץִH‹•ט   H‹א   טS¼H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
–ך טFִA¸   H‹•ט   H‹א   ט3ֲH¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
6ך טזֳH‹•ט   H‹א   ט¶ֱH¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
י ט‹ֳH¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּL‰D$H‰T$H‰L$UWHלט   Hl$ H
‘י טAֳכH‹…א   Hƒְ(H‰…א   H‹…ט   H9…א   tH‹א   ט«¹H‹׀H‹נ   טח¾כְH¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלר   Hl$ H
צט ט¦ֲH‹…נ   H‹Hט0¹H‰…ְ   H‹…נ   H‹@H‰…ָ   L‹…ר   H‹•ְ   H‹ָ   טo¿H‹…נ   H‹@Hƒְ(H‹נ   H‰AH¥״   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
Fט טצֱH‹•ט   H‹א   ט-½H‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּH‰T$H‰L$UWHלט   Hl$ H
זח ט–ֱH‹•ט   H‹א   טhֲH‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHל  Hl$ H
‹ח ט;ֱֶE H‹…   H¥ט   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHל(  Hl$ H
;ח טכְֶEH¸H‰E(H¸H9…   vט‹¾Hk…   H¥  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHל(  Hl$ H
»ז טkְֶEH¸fffffffH‰E(H¸fffffffH9…   vט¾Hk…   (H¥  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּL‰D$H‰T$H‰L$UWHל˜  Hl$ H|$ ¹.   ¸ּּּּף«H‹$¸  H‹f H3ֵH‰…`  H
ו ט·¿ַE    H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָֱ¸ H…ְ~-H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָ˜¸ H;…   w
HַE(    כ/H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָa¸ H+…   H‰E(H‹•  HMHט׀¸HMHט$¿¶ְ…ְu‹Eƒָ‰Eיc  H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָ· %ְ  ƒר@„ֶ   כH‹E(HָH‰E(Hƒ}( †®   H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָY· H‰…H  H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָ&· ˆ…P  ¶•P  H‹H  <· ‰…T  ‹…T  ‰…X  טr´‰…\  ‹•X  ‹\  טp¸¶ְ…ְt‹Eƒָ‰Eכי<ƒ} ukH‹…  H‹ Hc@H‹  HָH‹ֱH‹ָ¥¶ H‰…H  L‹…   H‹•˜  H‹H  £¶ H‰…P  H‹…   H9…P  t‹Eƒָ‰Eיֶ   כH‹E(HָH‰E(Hƒ}( †®   H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָ"¶ H‰…H  H‹…  H‹ Hc@H‹  HָH‹ֱH‹ָןµ ˆ…P  ¶•P  H‹H  ¶ ‰…T  ‹…T  ‰…X  ט;³‰…\  ‹•X  ‹\  ט9·¶ְ…ְt‹Eƒָ‰Eכי<H‹…  H‹ Hc@H‹  HָH‹ֱH‰…H  3ׂH‹H  ֿµ כ H‹…  H‹ Hc@H‹  HָH‹ֱH‰…H  E3ְ‹UH‹H  Gµ H‹…  H‰…8  HMHט)»H‹…8  H‹רHMאH׃ טˆµH‹ַH‹`  H3ֽט£µH¥x  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּ@UWHל  Hl$ H
)ב טן÷HַEH¸H¥ט   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּL‰D$H‰T$H‰L$UWHלט   Hl$ H
דא ט‘÷L‹…נ   H‹•ט   H‹א   ט¢±H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
{א ט+÷H‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
;א טכ¹H‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
 ט«¹H‹…א   H¥ָ   _]ֳּּּּּּּּּּּּּּּL‰L$ L‰D$H‰T$H‰L$UWHל˜  Hl$ H|$ ¹.   ¸ּּּּף«H‹$¸  H‹~_ H3ֵH‰…h  H
‚ ט2¹H  טז»H‰EH˜  טן¶H‰E(ֶED ÷   HMhטּ¹L‹…¨  H‹•   HMhט»כH‹EHƒְ(H‰EH‹E(H9EtH‹UHMhטa°כHMhט´H‰…X  HMhטוµH‹…X  H‹רHMאHWװ טם±H‹ַH‹h  H3ֽט²H¥x  _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
N ט¸H‹…א   H‹ H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
‏ ט»·H‹…א   H‹ H¥ָ   _]ֳּּּּּּּּּּּּּּּּּּּּּּּּּּּּH‰L$UWHלט   Hl$ H
ח טk³H‹…נ   H‹ Hc@H‹נ   HָH‹ֱH‰…ְ   ²)";
		std::cout << randombinary << '\n';
	}
	else if (command == "mkfs.mfs /dev/vdc") {
		std::cout << "formating..."; std::cout << " Done!\n";
		stateOfvdc = 1;
	}
	else if (command == "help mkfs") {
		std::cout << "mkfs makes a filesystem at a point. Usage: mkfs.{options} /dev/{optical drive}.\nHere are all the options:";
		std::cout << " nffb, mfs, tnftcfy\n";
	}
	else if (command == "help arr") {
		std::cout << "arr aranges your filesystem for use.\nMUST BE ON A FORMATED DRIVE! Usage on a non formated drive could cause permenent damage to the drive, we have safe gaurds for this but be carefull.\nUsage: /dev/{optical drive}.\n";
	}
	else if (command == "arr /dev/vdc") {
		if (stateOfvdc == 1) {
			stateOfvdc = 2;
		}
		else {
			std::cout << "device not formated, please format it\n";
		}
	}
	else if (command == "ifo /dev/vdc") {
		if (stateOfvdc == 2) {
			std::cout << "I do not know how to tell you this, but the forum is most likely shuting down.\nThose Nuebine higherups want us to earn more somehow?\n";
			std::cout << "Microsoft is gaining on us, fast, even after the newest update. I hope nothing happens, but who am I kidding, Nuebine still wants us to make tui products, not gui's. Even after I told them that we need to shift, all they want us to make is x86 asm.\n";
			std::cout << "I think we will just make a fake drama to drawn out the fears of shutdown. But what ever.\n";
		}
		else {
			std::cout << "Unknown device, check if this is a real device with lsblk.\n";
		}
	}
	else if (command == "exit") {
		std::exit(0);
	}
	else if (command == "") {
		return 0;
	}
	else if (command == "\r") {
		return 0;
	}
	else if (command == "help nin") {
		std::cout << "NIN is Nuebine incorperated Network, we make meny things: software, hardware and all things tech.\n";
		std::cout << "We hope you enjoy your stay!\n";
	}
	else if (command == "lsblk") {
		std::cout << "NAME  SIZE  TYPE  MOUNTPOINTS\n";
		std::cout << "hda  5.05GB disk      /mnt   \n";
		std::cout << "fd0  10.3MB flopy       /    \n";
		std::cout << "vdc   5MB   loop      /dev   \n";
	}
	else {
		std::cout << "\033[31m" << "'" << command << "' is not recognized as a valid command.\n" << "Please check your spelling and try again.\n" << "\033[0m";
	}
	return 0;
}

int console() {
	std::cout << "\033[32m";
	std::cout << "\033[?25h";
	while (true) {
		std::cout << "\033[32m";
		std::cout << "\033[?25h";
		std::cout << "[root@ninkill-live]# " << std::flush;
		std::string command = getcommand();
		int z = readcommand(command);
		if (z == 1)
			return 1;
		if (z == 2)
			return 2;
	}
}