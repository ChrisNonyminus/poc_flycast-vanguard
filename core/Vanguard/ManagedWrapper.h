#include <string>
class ManagedWrapper
{
public:
	static unsigned char peekbyte(long long addr);
	static void pokebyte(long long addr, unsigned char val);
	static void savesavestate();
	static int GetMemSize();
	static int GetVRAMSize();
	static void loadsavestate();
	static void RelayToFlycastLog(std::string string);
	static std::string getstatepath();
};