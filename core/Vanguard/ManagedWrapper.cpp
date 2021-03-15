#include "ManagedWrapper.h"
#include "../core/hw/sh4/sh4_mem.h"
#include "emulator.h"
#include <Vanguard/VanguardClient.h>
#include <string>
unsigned char ManagedWrapper::peekbyte(long long addr)
{
	return ReadMem8(static_cast<u32>(addr));
}

void ManagedWrapper::pokebyte(long long addr, unsigned char val)
{
	WriteMem8(static_cast<u32>(addr), val);
}

void ManagedWrapper::savesavestate()
{
	dc_savestate();
	dc_resume();
	
}
int ManagedWrapper::GetMemSize()
{
	return /*RAM_SIZE*/0x04000000;
}
int ManagedWrapper::GetVRAMSize()
{
	return /*VRAM_SIZE*/0x01000000;
}
void ManagedWrapper::loadsavestate()
{
	dc_loadstate();
	dc_resume();
}
void ManagedWrapper::RelayToFlycastLog(std::string string)
{
	ERROR_LOG(COMMON, string.c_str());
}
std::string ManagedWrapper::getstatepath()
{
	std::string state_file = settings.imgread.ImagePath;
	size_t lastindex = state_file.find_last_of('/');
#ifdef _WIN32
	size_t lastindex2 = state_file.find_last_of('\\');
	if (lastindex == std::string::npos)
		lastindex = lastindex2;
	else if (lastindex2 != std::string::npos)
		lastindex = std::max(lastindex, lastindex2);
#endif
	if (lastindex != std::string::npos)
		state_file = state_file.substr(lastindex + 1);
	lastindex = state_file.find_last_of('.');
	if (lastindex != std::string::npos)
		state_file = state_file.substr(0, lastindex);
	state_file = state_file + "savestate.state";
	return get_writable_data_path(state_file);
}
