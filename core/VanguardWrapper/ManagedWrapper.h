#include <string>
class ManagedWrapper
{
public:
	static unsigned char peekbyte(long long addr);
	static void pokebyte(long long addr, unsigned char val);
	static void savesavestate(std::string path);
	static int GetMemSize();
	static int GetVRAMSize();
	static int GetARAMSize();
	static int GetBIOSSize();
	static void loadsavestate(std::string path);
	static void RelayToFlycastLog(std::string string);
	static std::string getstatepath();
	static std::string setstatepath(std::string path);
};