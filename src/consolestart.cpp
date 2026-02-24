#include <iostream>
#include <string>
#include "boot.hpp"

std::string getcommand() {
	std::string getstring = "";
	std::getline(std::cin >> std::ws, getstring);
	return getstring;
}

void listdir() {
	std::cout << "        Directory: /mnt/\n\n";
	std::cout << " Mode     LastWriteTime       Name\n";
	std::cout << " ----     -------------       ----\n";
	std::cout << "-a----  3/24/1998 6:28 PM  NINKill.forum\n";
	std::cout << "-a----  1/14/1998 3:04 AM    help.txt   \n";
}

void help() {
	std::cout << "(c)Nuebine incorperated Network\n";
	std::cout << "Thank you for using the Nuebine incorperated Network operating system.\n";
	std::cout << "We hope you enjoy your stay!\n";
	std::cout << R"(To open the operating system write : "exc-nin")" << '\n';
	std::cout << "You are right now in the live environment, you can't do much right now exept start the forum,\nbut heres some commands you can try:";
	std::cout << "\nhelp: displays the help screen.\nexit: exits the live environment.\nls & dir: lists the directory you're in.\n";
	std::cout << "cls & clear: clears the console\ncat [filename]: reads file to you.\n";
}

int readcommand(std::string command) {
	if (command == "exc-nin") {
		return 1;
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
	else if (command == " cat NINKill.forum") {
		std::string randombinary = R"(
קְ׀”8*צ¸‚vjbL>2ˆ
צלאײ־ֶ¼´
× ‚tjbXH>|l\Fעה־ֲ |jX°
(NZSHGetKnownFolderPathSHELL32.dllGetStdHandletBeep%GetConsoleMod
e?SetConsoleMode+GetConsoleScreenBuf
ferInfoKERNEL32.dllCoTaskMemFreeole32.dllm??0_Lockit@std@@QEAA@H@Z¥??1_Lockit@std@@QEAA@XZ&?uncaught_exception@std@@YA_NXZ–?_Xlength_error@std@@YAXPEBD@Zֽ?good@ios_base@std@@QEBA_NXZo?flags@ios_base@std@@QEBAHXZF?width@ios_base@std@@QEBA_JXZE?width@ios_base@std@@QEAA_J_J@Zז?sputc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHD@Zי?sputn@?$basic_streambuf@DU?$
char_traits@D@std@@
@std@@QEAA_JPEBD_J@Zֽ?setstate@?$basic_ios@DU
?$char_traits@D@std@@@std@@QEAAXH_N@Z?tie@?$basic_ios@DU?$char_traits@D@std@@@std@@QEBAPEAV?$basic_ostream@DU?$char_traits@D@std@@@2@XZ?rdbuf@?$basic_ios@DU?$char_traits@D@std@@@std@@QEBAPEAV?$basic_streambuf@DU?$char_traits@D@std@@@2@XZi?fill@?$basic_ios@DU?$char_tr
aits@D@std@@@std@@QEBADXZL?_Osfx@?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAXXZp?flush@?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAAEAV12@XZ¼?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A—?_Xout_of_range@std@@YAXPEBD@Z?_Getgloballocale@locale@std@@CAPEAV_Locimp@12@XZ?is@?$ctype@D@std@@QEBA_NFD@Z¾?_Getcat@?$ctype@D@std@@SA_KPEAPEBVfacet@locale@2@PEBV42@@Zֻ?getloc@ios_base@std@@QEBA?AVlocale@2@XZ?sbumpc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHXZ׳?sgetc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHXZא?snextc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEAAHXZ<?widen@?$basic_ios@DU?$char_tra
its@
D@std
@@@std@@QEBADD@Z!?_Ipfx@?$basic_istream@DU?$char_traits@D@std@@@std@@QEAA_N_N@Z??5?$basic_istream@DU?$char_traits@D@std@@@std@@QEAAAEAV01@P6AAEAV01@AEAV01@@Z@Zצ?_Id_cnt@id@locale@std@@0HA׳?id@?$ctype@D@std@@2V0locale@2@A«?cin@std@@3V?$basic_istream@DU?$char_traits@D@std@@@1@A˜_Query_perf_counter™_Query_perf_frequency/??0?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAA@XZ‏?swap@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAXAEAV12@@Z‰??1?$basic_streambuf@DU?$char_traits@D@std@@@std@@UEAA@XZU?eback@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEBAPEADXZ־?gptr@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEBAPEADXZF?pbase@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEBAPEADXZO?pptr@?$basic_streambuf@DU?$char_traits@D
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
m@DU?$char_traits@D@std@@@std@@QEAAAEAV12@D@Z??0?$basic_iostream@DU?$char_traits@D@std@@@std@@QEAA@PEAV?$basic_streambuf@DU?$char_traits@D@std@@@1@@Zץ?swap@?$basic_iostream@DU?$char_traits@D@std@@@std@@IEAAXAEAV12@@Z€??1?$basic_iostream@DU?$char_traits@D@std@@@std@@UEAA@XZ‏?imbue@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MEAAXAEBVlocale@2@@Z?sync@?$bas
ic_streambuf@DU?$char_traits@D@std@@@std@@MEAAHXZ½?setbuf@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MEAAPEAV12@PEAD_J@ZN?xsputn@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MEAA_JPEBD_J@ZK?xsgetn@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MEAA_JPEAD_J@Z#?ufl
ow@?$basic_streambuf@DU?$char_
traits@D@std@@@std@@MEAAHX
Z?showmanyc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MEAA_JXZ‡?_Unlock@?$basic_streambuf@DU?$char_traits@D@std@@@std@@UEAAXXZ0?_Lock@?$basic_streambuf@DU?$char_traits@D@std@@@std@@UEAAXXZ??6?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAAEAV01@H@Z??6?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAAEAV01@_K@Z“?_Xbad_alloc@std@@YAXXZ{?_Syserror_map@std@@YAPEBDH@Z?_Winerror_map@std@@YAHH@Z׀?_Getcvt@_Locinfo@std@@QEBA?AU_Cvtvec@@XZ?_W_Getdays@_Locinfo@std@@QEBAPEBGXZ‹?_W_Getmonths@_Locinfo@std@@QEBAPEBGXZ¥?always_noconv@codecvt_base@std@@QEBA_NXZ?in@?$codecvt@DDU_Mbstatet@@@std@@QEBAHAEAU_Mbstatet@@PEBD1AEAPEBDPEAD3AEAPEAD@Z;?out@
?$c
odecvt@D
DU_Mbstatet@@@std@@QEBAHAEAU_Mbstatet@@PEBD1AEAPEBDPEAD3AEAPEAD@Z/?unshift@?$codecvt@DDU_Mbstatet@@@std@@QEBAHAEAU_Mbstatet@@PEAD1AEAPEAD@Z¹?_Getcat@?$codecvt@DDU_Mbstatet@@@std@@SA_KPEAPEBVfacet@locale@2@PEBV42@@Z8??Bios_base@std@@QEBA_NXZָ?getloc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@QEBA?AVlocale@2@XZם?_Gndec@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAPEADXZנ?_Gninc@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAPEADXZך?_Gnavail@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEBA_JXZI?pbump@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAXH@ZO?_Pnavail@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEBA_JXZ‎?_Init@?$basic_streambuf@DU?$char_traits@D@std@@@std@@IEAAXXZ?_Init@?$basic_s
treambuf@DU?$char_traits@D@std@@@std@@IEAAXPEAPEAD0PEAH001@Z%??0?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAA@PEAV?$basic_streambuf@DU?$char_traits@D@std@@@1@_N@Z†??1?
$basic_ostream@DU?$char_traits@D@std@@@s
td@@UEAA@XZ␦??0?$basic_istream@DU?$char_tr
aits@D@std@@@std@@QEAA@PEAV?$basic_streambuf@DU?$char_traits@D@std@@@1@_N@Zƒ??1?$basic_istream@DU?$char_traits@D@std@@@std@@UEAA@XZµ?_Fiopen@std@@YAPEAU_iobuf@@PEB_WHH@Zׁ?id@?$codecvt@DDU_Mbsta
tet@@@std@@2V0locale@2@AMSVCP140D.dll<me
mcpy=memmove!__std_exception_copy"__std_e
xception_destroy_CxxThrowException__CxxFrameHandler4;memcmp>memset␦GetSystemTi
meAsFileTimeInitializeSListHe
ad|HeapAlloc€HeapFreeהGetP
rocessHeapVirtualQueryװFreeLibrary@@}@g@g@g
‚@€0
)";
		std::cout << randombinary;
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
	else {
		std::cout << "\033[31m" << "'" << command << "' is not recognized as a valid command.\n" << "Please check your spelling and try again.\n" << "\033[0m";
	}
	return 0;
}

void consolefirst() {
	std::cout << "\033[32m";
	std::cout << "\033[?25h";
	std::cout << "Welcome to NINKILLos!\nWrite \'help\' for more info\n";
	while (true) {
		std::cout << "\033[32m";
		std::cout << "\033[?25h";
		std::cout << "[root@ninkill-live]# " << std::flush;
		std::string command = getcommand();
		int z = readcommand(command);
		if (z == 1) {
			break;
		}
	}
}

void console() {
	std::cout << "\033[32m";
	std::cout << "\033[?25h";
	while (true) {
		std::cout << "\033[32m";
		std::cout << "\033[?25h";
		std::cout << "[root@ninkill-live]# " << std::flush;
		std::string command = getcommand();
		int z = readcommand(command);
		if (z == 1) {
			break;
		}
	}
}