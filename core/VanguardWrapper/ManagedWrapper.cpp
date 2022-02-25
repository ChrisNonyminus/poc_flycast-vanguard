#include "ManagedWrapper.h"
#include "../../core/hw/sh4/sh4_mem.h"
#include "../../core/hw/mem/_vmem.h"
#include "../../core/emulator.h"
#include "../Vanguard/VanguardClient.h"
#include <string>
#include "../types.h"
#include "../stdclass.h"
#include <oslib/oslib.h>
unsigned char ManagedWrapper::peekbyte(long long addr)
{
	return _vmem_readt<u8, u8>(static_cast<u32>(addr));
}

void ManagedWrapper::pokebyte(long long addr, unsigned char val)
{
	_vmem_writet<u8>(static_cast<u32>(addr), val);
}

void ManagedWrapper::savesavestate()
{
	dc_savestate();
	EventManager::event(Event::Resume);
	
}
int ManagedWrapper::GetMemSize()
{
	return RAM_SIZE;
}
int ManagedWrapper::GetVRAMSize()
{
	return VRAM_SIZE;
}
int ManagedWrapper::GetARAMSize()
{
	return ARAM_SIZE;
}
int ManagedWrapper::GetBIOSSize()
{
	return BIOS_SIZE;
}
void ManagedWrapper::loadsavestate()
{
	dc_loadstate();
	EventManager::event(Event::Resume);
}
void ManagedWrapper::RelayToFlycastLog(std::string string)
{
	//ERROR_LOG(COMMON, string.c_str());
	INFO_LOG(COMMON, string.c_str());
}
std::string ManagedWrapper::getstatepath()
{
	std::string state_file = hostfs::getSavestatePath(0, true);
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
	state_file = state_file;
	return get_writable_data_path(state_file);
}
