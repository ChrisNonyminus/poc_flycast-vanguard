// serialize.cpp : save states
#include "types.h"
#include "hw/aica/dsp.h"
#include "hw/aica/aica.h"
#include "hw/aica/sgc_if.h"
#include "hw/arm7/arm7.h"
#include "hw/holly/sb.h"
#include "hw/flashrom/flashrom.h"
#include "hw/gdrom/gdromv3.h"
#include "hw/maple/maple_cfg.h"
#include "hw/pvr/Renderer_if.h"
#include "hw/sh4/sh4_sched.h"
#include "hw/sh4/sh4_mmr.h"
#include "hw/sh4/modules/mmu.h"
#include "reios/gdrom_hle.h"
#include "hw/sh4/dyna/blockmanager.h"
#include "hw/naomi/naomi_cart.h"
#include "hw/sh4/sh4_cache.h"
#include "hw/bba/bba.h"

extern "C" void DYNACALL TAWriteSQ(u32 address,u8* sqb);

//./core/hw/arm7/arm_mem.cpp
extern bool aica_interr;
extern u32 aica_reg_L;
extern bool e68k_out;
extern u32 e68k_reg_L;
extern u32 e68k_reg_M;

//./core/hw/arm7/arm7.cpp
alignas(8) extern reg_pair arm_Reg[RN_ARM_REG_COUNT];
extern bool armIrqEnable;
extern bool armFiqEnable;
extern int armMode;
extern bool Arm7Enabled;

//./core/hw/aica/dsp.o
alignas(4096) extern dsp_t dsp;

extern AicaTimer timers[3];

//./core/hw/aica/aica_if.o
extern VArray2 aica_ram;
extern u32 VREG;//video reg =P
extern u32 ARMRST;//arm reset reg
extern u32 rtc_EN;
extern int dma_sched_id;
extern u32 RealTimeClock;

//./core/hw/aica/aica_mem.o
extern u8 aica_reg[0x8000];

//./core/hw/aica/sgc_if.o
struct ChannelEx;
#define AicaChannel ChannelEx

//special handling
#define Chans AicaChannel::Chans
#define CDDA_SIZE  (2352/2)
extern s16 cdda_sector[CDDA_SIZE];
extern u32 cdda_index;

//./core/hw/holly/sb.o
extern u32 SB_ISTNRM;
extern u32 SB_FFST_rc;
extern u32 SB_FFST;

//./core/hw/holly/sb_mem.o
extern MemChip *sys_rom;
extern MemChip *sys_nvmem;

//./core/hw/gdrom/gdromv3.o
extern int gdrom_schid;
extern signed int sns_asc;
extern signed int sns_ascq;
extern signed int sns_key;
extern packet_cmd_t packet_cmd;
extern u32 set_mode_offset;
extern read_params_t read_params ;
extern packet_cmd_t packet_cmd;
//Buffer for sector reads [dma]
extern read_buff_t read_buff ;
//pio buffer
extern pio_buff_t pio_buff ;
extern u32 set_mode_offset;
extern ata_cmd_t ata_cmd ;
extern cdda_t cdda ;
extern gd_states gd_state;
extern DiscType gd_disk_type;
extern u32 data_write_mode;
//Registers
extern u32 DriveSel;
extern GD_ErrRegT Error;
extern GD_InterruptReasonT IntReason;
extern GD_FeaturesT Features;
extern GD_SecCountT SecCount;
extern GD_SecNumbT SecNumber;
extern GD_StatusT GDStatus;
extern ByteCount_t ByteCount ;

//./core/hw/maple/maple_devs.o
extern u8 EEPROM[0x100];
extern bool EEPROM_loaded;

//./core/hw/maple/maple_if.o
extern int maple_schid;
extern bool maple_ddt_pending_reset;

//./core/hw/modem/modem.cpp
extern int modem_sched;

//./core/hw/pvr/Renderer_if.o
extern bool pend_rend;
extern u32 fb_w_cur;

//./core/hw/pvr/pvr_mem.o
extern u32 YUV_tempdata[512/4];//512 bytes
extern u32 YUV_dest;
extern u32 YUV_blockcount;
extern u32 YUV_x_curr;
extern u32 YUV_y_curr;
extern u32 YUV_x_size;
extern u32 YUV_y_size;

//./core/hw/pvr/pvr_regs.o
extern bool fog_needs_update;
extern u8 pvr_regs[pvr_RegSize];

//./core/hw/pvr/spg.o
extern u32 in_vblank;
extern u32 clc_pvr_scanline;
extern int render_end_schid;
extern int vblank_schid;
extern bool maple_int_pending;

//./core/hw/pvr/ta.o
extern u8 ta_fsm[2049];	//[2048] stores the current state
extern u32 ta_fsm_cl;

//./core/hw/pvr/ta_vtx.o
extern bool pal_needs_update;

//./core/rend/TexCache.o
extern VArray2 vram;

//./core/hw/sh4/sh4_mmr.o
extern std::array<u8, OnChipRAM_SIZE> OnChipRAM;

//./core/hw/sh4/sh4_mem.o
extern VArray2 mem_b;

//./core/hw/sh4/sh4_interrupts.o
alignas(64) extern u16 InterruptEnvId[32];
alignas(64) extern u32 InterruptBit[32];
alignas(64) extern u32 InterruptLevelBit[16];
extern u32 interrupt_vpend; // Vector of pending interrupts
extern u32 interrupt_vmask; // Vector of masked interrupts             (-1 inhibits all interrupts)
extern u32 decoded_srimask; // Vector of interrupts allowed by SR.IMSK (-1 inhibits all interrupts)

//./core/hw/sh4/sh4_core_regs.o
extern Sh4RCB* p_sh4rcb;

//./core/hw/sh4/sh4_sched.o
extern u64 sh4_sched_ffb;
extern std::vector<sched_list> sch_list;

//./core/hw/sh4/interpr/sh4_interpreter.o
extern int aica_schid;
extern int rtc_schid;

//./core/hw/sh4/modules/serial.o
extern SCIF_SCFSR2_type SCIF_SCFSR2;
extern SCIF_SCSCR2_type SCIF_SCSCR2;

//./core/hw/sh4/modules/bsc.o
extern BSC_PDTRA_type BSC_PDTRA;

//./core/hw/sh4/modules/tmu.o
extern u32 tmu_shift[3];
extern u32 tmu_mask[3];
extern u64 tmu_mask64[3];
extern u32 old_mode[3];
extern int tmu_sched[3];
extern u32 tmu_ch_base[3];
extern u64 tmu_ch_base64[3];

//./core/hw/sh4/modules/ccn.o
extern u32 CCN_QACR_TR[2];

//./core/hw/sh4/modules/mmu.o
extern TLB_Entry UTLB[64];
extern TLB_Entry ITLB[4];
extern u32 sq_remap[64];
static u32 ITLB_LRU_USE[64];

//./core/imgread/common.o
extern u32 NullDriveDiscType;
extern u8 q_subchannel[96];

//./core/hw/naomi/naomi.o
extern u32 GSerialBuffer;
extern u32 BSerialBuffer;
extern int GBufPos;
extern int BBufPos;
extern int GState;
extern int BState;
extern int GOldClk;
extern int BOldClk;
extern int BControl;
extern int BCmd;
extern int BLastCmd;
extern int GControl;
extern int GCmd;
extern int GLastCmd;
extern int SerStep;
extern int SerStep2;
extern unsigned char BSerial[];
extern unsigned char GSerial[];
extern u32 reg_dimm_command;
extern u32 reg_dimm_offsetl;
extern u32 reg_dimm_parameterl;
extern u32 reg_dimm_parameterh;
extern u32 reg_dimm_status;

bool rc_serialize(const void *src, unsigned int src_size, void **dest, unsigned int *total_size)
{
	if ( *dest != NULL )
	{
		memcpy(*dest, src, src_size) ;
		*dest = ((unsigned char*)*dest) + src_size ;
	}

	*total_size += src_size ;
	return true ;
}

bool rc_unserialize(void *src, unsigned int src_size, void **dest, unsigned int *total_size)
{
	if ( *dest != NULL )
	{
		memcpy(src, *dest, src_size) ;
		*dest = ((unsigned char*)*dest) + src_size ;
	}

	*total_size += src_size ;
	return true ;
}

template<typename T>
bool register_serialize(const T& regs,void **data, unsigned int *total_size )
{
	for (const auto& reg : regs)
		REICAST_S(reg.data32);

	return true;
}

template<typename T>
bool register_unserialize(T& regs,void **data, unsigned int *total_size, serialize_version_enum version)
{
	u32 dummy = 0;

	for (auto& reg : regs)
	{
		if (version < V5)
			REICAST_US(dummy); // regs.data[i].flags
		if (!(reg.flags & REG_RF))
			REICAST_US(reg.data32);
		else
			REICAST_US(dummy);
	}
	return true;
}

bool dc_serialize(void **data, unsigned int *total_size)
{
	int i = 0;

	serialize_version_enum version = VCUR_FLYCAST;

	*total_size = 0 ;

	//dc not initialized yet
	if ( p_sh4rcb == NULL )
		return false ;

	REICAST_S(version) ;
	REICAST_S(aica_interr) ;
	REICAST_S(aica_reg_L) ;
	REICAST_S(e68k_out) ;
	REICAST_S(e68k_reg_L) ;
	REICAST_S(e68k_reg_M) ;

	REICAST_SA(arm_Reg,RN_ARM_REG_COUNT);
	REICAST_S(armIrqEnable);
	REICAST_S(armFiqEnable);
	REICAST_S(armMode);
	REICAST_S(Arm7Enabled);

	REICAST_S(dsp);	// FIXME could save 32KB

	for ( i = 0 ; i < 3 ; i++)
	{
		REICAST_S(timers[i].c_step);
		REICAST_S(timers[i].m_step);
	}

	REICAST_SA(aica_ram.data,aica_ram.size) ;
	REICAST_S(VREG);
	REICAST_S(ARMRST);
	REICAST_S(rtc_EN);
	REICAST_S(RealTimeClock);

	REICAST_SA(aica_reg,0x8000);

	channel_serialize(data, total_size) ;

	REICAST_SA(cdda_sector,CDDA_SIZE);
	REICAST_S(cdda_index);

	register_serialize(sb_regs, data, total_size) ;
	REICAST_S(SB_ISTNRM);
	REICAST_S(SB_FFST_rc);
	REICAST_S(SB_FFST);


	sys_rom->Serialize(data, total_size);
	sys_nvmem->Serialize(data, total_size);

	REICAST_S(GD_HardwareInfo);


	REICAST_S(sns_asc);
	REICAST_S(sns_ascq);
	REICAST_S(sns_key);

	REICAST_S(packet_cmd);
	REICAST_S(set_mode_offset);
	REICAST_S(read_params);
	REICAST_S(packet_cmd);
	REICAST_S(pio_buff);
	REICAST_S(set_mode_offset);
	REICAST_S(ata_cmd);
	REICAST_S(cdda);
	REICAST_S(gd_state);
	REICAST_S(gd_disk_type);
	REICAST_S(data_write_mode);
	REICAST_S(DriveSel);
	REICAST_S(Error);

	REICAST_S(IntReason);
	REICAST_S(Features);
	REICAST_S(SecCount);
	REICAST_S(SecNumber);
	REICAST_S(GDStatus);
	REICAST_S(ByteCount);


	REICAST_SA(EEPROM,0x100);
	REICAST_S(EEPROM_loaded);


	REICAST_S(maple_ddt_pending_reset);

	mcfg_SerializeDevices(data, total_size);

	REICAST_SA(YUV_tempdata,512/4);
	REICAST_S(YUV_dest);
	REICAST_S(YUV_blockcount);
	REICAST_S(YUV_x_curr);
	REICAST_S(YUV_y_curr);
	REICAST_S(YUV_x_size);
	REICAST_S(YUV_y_size);

	REICAST_SA(pvr_regs,pvr_RegSize);

	REICAST_S(in_vblank);
	REICAST_S(clc_pvr_scanline);
	REICAST_S(maple_int_pending);
	REICAST_S(fb_w_cur);

	REICAST_S(ta_fsm[2048]);
	REICAST_S(ta_fsm_cl);

	SerializeTAContext(data, total_size);

	REICAST_SA(vram.data, vram.size);

	REICAST_SA(OnChipRAM.data(), OnChipRAM_SIZE);

	register_serialize(CCN, data, total_size) ;
	register_serialize(UBC, data, total_size) ;
	register_serialize(BSC, data, total_size) ;
	register_serialize(DMAC, data, total_size) ;
	register_serialize(CPG, data, total_size) ;
	register_serialize(RTC, data, total_size) ;
	register_serialize(INTC, data, total_size) ;
	register_serialize(TMU, data, total_size) ;
	register_serialize(SCI, data, total_size) ;
	register_serialize(SCIF, data, total_size) ;
	icache.Serialize(data, total_size);
	ocache.Serialize(data, total_size);

	REICAST_SA(mem_b.data, mem_b.size);

	REICAST_SA(InterruptEnvId,32);
	REICAST_SA(InterruptBit,32);
	REICAST_SA(InterruptLevelBit,16);
	REICAST_S(interrupt_vpend);
	REICAST_S(interrupt_vmask);
	REICAST_S(decoded_srimask);


	//default to nommu_full
	i = 3 ;
	if ( do_sqw_nommu == &do_sqw_nommu_area_3)
		i = 0 ;
	else if (do_sqw_nommu == &do_sqw_nommu_area_3_nonvmem)
		i = 1 ;
	else if (do_sqw_nommu==(sqw_fp*)&TAWriteSQ)
		i = 2 ;
	else if (do_sqw_nommu==&do_sqw_nommu_full)
		i = 3 ;

	REICAST_S(i) ;

	REICAST_SA((*p_sh4rcb).sq_buffer,64/8);

	REICAST_S((*p_sh4rcb).cntx);

	REICAST_S(sh4_sched_ffb);

	REICAST_S(sch_list[aica_schid].tag) ;
	REICAST_S(sch_list[aica_schid].start) ;
	REICAST_S(sch_list[aica_schid].end) ;

	REICAST_S(sch_list[rtc_schid].tag) ;
	REICAST_S(sch_list[rtc_schid].start) ;
	REICAST_S(sch_list[rtc_schid].end) ;

	REICAST_S(sch_list[gdrom_schid].tag) ;
	REICAST_S(sch_list[gdrom_schid].start) ;
	REICAST_S(sch_list[gdrom_schid].end) ;

	REICAST_S(sch_list[maple_schid].tag) ;
	REICAST_S(sch_list[maple_schid].start) ;
	REICAST_S(sch_list[maple_schid].end) ;

	REICAST_S(sch_list[dma_sched_id].tag) ;
	REICAST_S(sch_list[dma_sched_id].start) ;
	REICAST_S(sch_list[dma_sched_id].end) ;

	for (int i = 0; i < 3; i++)
	{
		REICAST_S(sch_list[tmu_sched[i]].tag) ;
		REICAST_S(sch_list[tmu_sched[i]].start) ;
		REICAST_S(sch_list[tmu_sched[i]].end) ;
	}

	REICAST_S(sch_list[render_end_schid].tag) ;
	REICAST_S(sch_list[render_end_schid].start) ;
	REICAST_S(sch_list[render_end_schid].end) ;

	REICAST_S(sch_list[vblank_schid].tag) ;
	REICAST_S(sch_list[vblank_schid].start) ;
	REICAST_S(sch_list[vblank_schid].end) ;

	REICAST_S(settings.network.EmulateBBA);
	if (settings.network.EmulateBBA)
	{
		bba_Serialize(data, total_size);
	}
	else
	{
		REICAST_S(sch_list[modem_sched].tag);
		REICAST_S(sch_list[modem_sched].start);
		REICAST_S(sch_list[modem_sched].end);
	}

	REICAST_S(SCIF_SCFSR2);
	REICAST_S(SCIF_SCSCR2);
	REICAST_S(BSC_PDTRA);

	REICAST_SA(tmu_shift,3);
	REICAST_SA(tmu_mask,3);
	REICAST_SA(tmu_mask64,3);
	REICAST_SA(old_mode,3);
	REICAST_SA(tmu_ch_base,3);
	REICAST_SA(tmu_ch_base64,3);

	REICAST_SA(CCN_QACR_TR,2);

	REICAST_S(UTLB);
	REICAST_S(ITLB);
	REICAST_S(sq_remap);
	REICAST_S(ITLB_LRU_USE);

	REICAST_S(NullDriveDiscType);
	REICAST_SA(q_subchannel,96);

	REICAST_S(GSerialBuffer);
	REICAST_S(BSerialBuffer);
	REICAST_S(GBufPos);
	REICAST_S(BBufPos);
	REICAST_S(GState);
	REICAST_S(BState);
	REICAST_S(GOldClk);
	REICAST_S(BOldClk);
	REICAST_S(BControl);
	REICAST_S(BCmd);
	REICAST_S(BLastCmd);
	REICAST_S(GControl);
	REICAST_S(GCmd);
	REICAST_S(GLastCmd);
	REICAST_S(SerStep);
	REICAST_S(SerStep2);
	REICAST_SA(BSerial,69);
	REICAST_SA(GSerial,69);
	REICAST_S(reg_dimm_command);
	REICAST_S(reg_dimm_offsetl);
	REICAST_S(reg_dimm_parameterl);
	REICAST_S(reg_dimm_parameterh);
	REICAST_S(reg_dimm_status);

	REICAST_S(settings.dreamcast.broadcast);
	REICAST_S(settings.dreamcast.cable);
	REICAST_S(settings.dreamcast.region);

	if (CurrentCartridge != NULL)
	   CurrentCartridge->Serialize(data, total_size);
	
	gd_hle_state.Serialize(data, total_size);

	DEBUG_LOG(SAVESTATE, "Saved %d bytes", *total_size);

	return true ;
}

static bool dc_unserialize_libretro(void **data, unsigned int *total_size)
{
	int i = 0;

	REICAST_US(aica_interr) ;
	REICAST_US(aica_reg_L) ;
	REICAST_US(e68k_out) ;
	REICAST_US(e68k_reg_L) ;
	REICAST_US(e68k_reg_M) ;

	REICAST_USA(arm_Reg,RN_ARM_REG_COUNT);
	REICAST_US(armIrqEnable);
	REICAST_US(armFiqEnable);
	REICAST_US(armMode);
	REICAST_US(Arm7Enabled);

	REICAST_US(dsp);

	for ( i = 0 ; i < 3 ; i++)
	{
		REICAST_US(timers[i].c_step);
		REICAST_US(timers[i].m_step);
	}

	REICAST_USA(aica_ram.data,aica_ram.size) ;
	REICAST_US(VREG);
	REICAST_US(ARMRST);
	REICAST_US(rtc_EN);

	REICAST_USA(aica_reg,0x8000);

	channel_unserialize(data, total_size, VCUR_LIBRETRO);

	REICAST_USA(cdda_sector,CDDA_SIZE);
	REICAST_US(cdda_index);

	register_unserialize(sb_regs, data, total_size, VCUR_LIBRETRO) ;
	REICAST_US(SB_ISTNRM);
	REICAST_US(SB_FFST_rc);
	REICAST_US(SB_FFST);

	if (settings.platform.system == DC_PLATFORM_NAOMI || settings.platform.system == DC_PLATFORM_ATOMISWAVE)
	{
		REICAST_US(sys_nvmem->size);
		REICAST_US(sys_nvmem->mask);
		REICAST_USA(sys_nvmem->data, sys_nvmem->size);
	}
	else
	{
		REICAST_US(i);
		REICAST_US(i);
	}

	if (settings.platform.system == DC_PLATFORM_DREAMCAST)
	{
		REICAST_US(sys_nvmem->size);
		REICAST_US(sys_nvmem->mask);
		REICAST_US(static_cast<DCFlashChip*>(sys_nvmem)->state);
		REICAST_USA(sys_nvmem->data, sys_nvmem->size);
	}
	else if (settings.platform.system == DC_PLATFORM_ATOMISWAVE)
	{
		REICAST_US(sys_rom->size);
		REICAST_US(sys_rom->mask);
		REICAST_US(static_cast<DCFlashChip*>(sys_rom)->state);
		REICAST_USA(sys_rom->data, sys_rom->size);
	}
	else
	{
		REICAST_US(i);
		REICAST_US(i);
		REICAST_US(i);
	}

	REICAST_US(GD_HardwareInfo);

	REICAST_US(sns_asc);
	REICAST_US(sns_ascq);
	REICAST_US(sns_key);

	REICAST_US(packet_cmd);
	REICAST_US(set_mode_offset);
	REICAST_US(read_params);
	REICAST_US(packet_cmd);
	read_buff.cache_size = 0;
	REICAST_US(pio_buff);
	REICAST_US(set_mode_offset);
	REICAST_US(ata_cmd);
	REICAST_US(cdda);
	cdda.status = (bool)cdda.status ? cdda_t::Playing : cdda_t::NoInfo;
	REICAST_US(gd_state);
	REICAST_US(gd_disk_type);
	REICAST_US(data_write_mode);
	REICAST_US(DriveSel);
	REICAST_US(Error);
	REICAST_US(IntReason);
	REICAST_US(Features);
	REICAST_US(SecCount);
	REICAST_US(SecNumber);
	REICAST_US(GDStatus);
	REICAST_US(ByteCount);
	REICAST_US(i); 			// GDROM_TICK
	REICAST_USA(EEPROM,0x100);
	REICAST_US(EEPROM_loaded);

	REICAST_US(maple_ddt_pending_reset);
	mcfg_UnserializeDevices(data, total_size, false);

	pend_rend = false;

	REICAST_USA(YUV_tempdata,512/4);
	REICAST_US(YUV_dest);
	REICAST_US(YUV_blockcount);
	REICAST_US(YUV_x_curr);
	REICAST_US(YUV_y_curr);
	REICAST_US(YUV_x_size);
	REICAST_US(YUV_y_size);

	REICAST_USA(pvr_regs,pvr_RegSize);
	fog_needs_update = true ;

	REICAST_US(in_vblank);
	REICAST_US(clc_pvr_scanline);
	fb_w_cur = 1;

	REICAST_US(ta_fsm[2048]);
	REICAST_US(ta_fsm_cl);
	pal_needs_update = true;

	UnserializeTAContext(data, total_size, VCUR_LIBRETRO);

	REICAST_USA(vram.data, vram.size);

	REICAST_USA(OnChipRAM.data(), OnChipRAM_SIZE);

	register_unserialize(CCN, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(UBC, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(BSC, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(DMAC, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(CPG, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(RTC, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(INTC, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(TMU, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(SCI, data, total_size, VCUR_LIBRETRO) ;
	register_unserialize(SCIF, data, total_size, VCUR_LIBRETRO) ;
	icache.Reset(true);
	ocache.Reset(true);

	REICAST_USA(mem_b.data, mem_b.size);
	REICAST_USA(InterruptEnvId,32);
	REICAST_USA(InterruptBit,32);
	REICAST_USA(InterruptLevelBit,16);
	REICAST_US(interrupt_vpend);
	REICAST_US(interrupt_vmask);
	REICAST_US(decoded_srimask);

	REICAST_US(i) ;
	if ( i == 0 )
		do_sqw_nommu = &do_sqw_nommu_area_3 ;
	else if ( i == 1 )
		do_sqw_nommu = &do_sqw_nommu_area_3_nonvmem ;
	else if ( i == 2 )
		do_sqw_nommu = (sqw_fp*)&TAWriteSQ ;
	else if ( i == 3 )
		do_sqw_nommu = &do_sqw_nommu_full ;

	REICAST_USA((*p_sh4rcb).sq_buffer,64/8);

	REICAST_US((*p_sh4rcb).cntx);

	REICAST_US(sh4_sched_ffb);

	REICAST_US(sch_list[aica_schid].tag) ;
	REICAST_US(sch_list[aica_schid].start) ;
	REICAST_US(sch_list[aica_schid].end) ;

	REICAST_US(sch_list[rtc_schid].tag) ;
	REICAST_US(sch_list[rtc_schid].start) ;
	REICAST_US(sch_list[rtc_schid].end) ;

	REICAST_US(sch_list[gdrom_schid].tag) ;
	REICAST_US(sch_list[gdrom_schid].start) ;
	REICAST_US(sch_list[gdrom_schid].end) ;

	REICAST_US(sch_list[maple_schid].tag) ;
	REICAST_US(sch_list[maple_schid].start) ;
	REICAST_US(sch_list[maple_schid].end) ;

	REICAST_US(sch_list[dma_sched_id].tag) ;
	REICAST_US(sch_list[dma_sched_id].start) ;
	REICAST_US(sch_list[dma_sched_id].end) ;

	for (int i = 0; i < 3; i++)
	{
		REICAST_US(sch_list[tmu_sched[i]].tag) ;
		REICAST_US(sch_list[tmu_sched[i]].start) ;
		REICAST_US(sch_list[tmu_sched[i]].end) ;
	}

	REICAST_US(sch_list[render_end_schid].tag) ;
	REICAST_US(sch_list[render_end_schid].start) ;
	REICAST_US(sch_list[render_end_schid].end) ;

	REICAST_US(sch_list[vblank_schid].tag) ;
	REICAST_US(sch_list[vblank_schid].start) ;
	REICAST_US(sch_list[vblank_schid].end) ;

	REICAST_US(sch_list[modem_sched].tag) ;
    REICAST_US(sch_list[modem_sched].start) ;
    REICAST_US(sch_list[modem_sched].end) ;

	REICAST_US(SCIF_SCFSR2);
	REICAST_US(SCIF_SCSCR2);
	REICAST_US(BSC_PDTRA);

	REICAST_USA(tmu_shift,3);
	REICAST_USA(tmu_mask,3);
	REICAST_USA(tmu_mask64,3);
	REICAST_USA(old_mode,3);
	REICAST_USA(tmu_ch_base,3);
	REICAST_USA(tmu_ch_base64,3);

	REICAST_USA(CCN_QACR_TR,2);

	REICAST_US(UTLB);
	REICAST_US(ITLB);
	REICAST_US(sq_remap);
	REICAST_US(ITLB_LRU_USE);

	REICAST_US(NullDriveDiscType);
	REICAST_USA(q_subchannel,96);

	REICAST_US(i);	// FLASH_SIZE
	REICAST_US(i);	// BBSRAM_SIZE
	REICAST_US(i);	// BIOS_SIZE
	REICAST_US(i);	// RAM_SIZE
	REICAST_US(i);	// ARAM_SIZE
	REICAST_US(i);	// VRAM_SIZE
	REICAST_US(i);	// RAM_MASK
	REICAST_US(i);	// ARAM_MASK
	REICAST_US(i);	// VRAM_MASK

	REICAST_US(GSerialBuffer);
	REICAST_US(BSerialBuffer);
	REICAST_US(GBufPos);
	REICAST_US(BBufPos);
	REICAST_US(GState);
	REICAST_US(BState);
	REICAST_US(GOldClk);
	REICAST_US(BOldClk);
	REICAST_US(BControl);
	REICAST_US(BCmd);
	REICAST_US(BLastCmd);
	REICAST_US(GControl);
	REICAST_US(GCmd);
	REICAST_US(GLastCmd);
	REICAST_US(SerStep);
	REICAST_US(SerStep2);
	REICAST_USA(BSerial,69);
	REICAST_USA(GSerial,69);
	REICAST_US(reg_dimm_command);
	REICAST_US(reg_dimm_offsetl);
	REICAST_US(reg_dimm_parameterl);
	REICAST_US(reg_dimm_parameterh);
	REICAST_US(reg_dimm_status);
	REICAST_SKIP(1); // NaomiDataRead

	REICAST_US(settings.dreamcast.broadcast);
	REICAST_US(settings.dreamcast.cable);
	REICAST_US(settings.dreamcast.region);

	if (CurrentCartridge != NULL)
		CurrentCartridge->Unserialize(data, total_size);
	gd_hle_state.Unserialize(data, total_size);
	settings.network.EmulateBBA = false;

	DEBUG_LOG(SAVESTATE, "Loaded %d bytes (libretro compat)", *total_size);

	return true ;
}

bool dc_unserialize(void **data, unsigned int *total_size)
{
	int i = 0;

	serialize_version_enum version = V1 ;

	*total_size = 0 ;

	REICAST_US(version) ;
	if (version == VCUR_LIBRETRO)
		return dc_unserialize_libretro(data, total_size);
	if (version != V4 && version < V5)
	{
		WARN_LOG(SAVESTATE, "Save State version not supported: %d", version);
		return false;
	}
	else
	{
		DEBUG_LOG(SAVESTATE, "Loading state version %d", version);
	}
	REICAST_US(aica_interr) ;
	REICAST_US(aica_reg_L) ;
	REICAST_US(e68k_out) ;
	REICAST_US(e68k_reg_L) ;
	REICAST_US(e68k_reg_M) ;

	REICAST_USA(arm_Reg,RN_ARM_REG_COUNT);
	REICAST_US(armIrqEnable);
	REICAST_US(armFiqEnable);
	REICAST_US(armMode);
	REICAST_US(Arm7Enabled);
	if (version < 5)
		REICAST_SKIP(256 + 3);

	REICAST_US(dsp);

	for ( i = 0 ; i < 3 ; i++)
	{
		REICAST_US(timers[i].c_step);
		REICAST_US(timers[i].m_step);
	}

	REICAST_USA(aica_ram.data,aica_ram.size) ;
	REICAST_US(VREG);
	REICAST_US(ARMRST);
	REICAST_US(rtc_EN);
	if (version >= V9)
		REICAST_US(RealTimeClock);

	REICAST_USA(aica_reg,0x8000);

	if (version < V5)
	{
		REICAST_SKIP(4 * 16);
		REICAST_SKIP(4 * 256 + 768);
		REICAST_SKIP(4 * 64);
		REICAST_SKIP(4 * 64);
		REICAST_SKIP(2);
		REICAST_SKIP(2);
	}
	channel_unserialize(data, total_size, version);

	REICAST_USA(cdda_sector,CDDA_SIZE);
	REICAST_US(cdda_index);
	if (version < V5)
	{
		REICAST_SKIP(4 * 64);
		REICAST_SKIP(4);
	}

	register_unserialize(sb_regs, data, total_size, version) ;
	REICAST_US(SB_ISTNRM);
	REICAST_US(SB_FFST_rc);
	REICAST_US(SB_FFST);

	if (version < V5)
	{
		REICAST_SKIP(4);	// size
		REICAST_SKIP(4);	// mask
	}
	sys_rom->Unserialize(data, total_size);
	sys_nvmem->Unserialize(data, total_size);

	REICAST_US(GD_HardwareInfo);

	REICAST_US(sns_asc);
	REICAST_US(sns_ascq);
	REICAST_US(sns_key);

	REICAST_US(packet_cmd);
	REICAST_US(set_mode_offset);
	REICAST_US(read_params);
	REICAST_US(packet_cmd);
	// read_buff
	read_buff.cache_size = 0;
	if (version < V8)
		REICAST_SKIP(4 + 4 + 2352 * 8192);
	REICAST_US(pio_buff);
	REICAST_US(set_mode_offset);
	REICAST_US(ata_cmd);
	REICAST_US(cdda);
	if (version < V10)
		cdda.status = (bool)cdda.status ? cdda_t::Playing : cdda_t::NoInfo;
	REICAST_US(gd_state);
	REICAST_US(gd_disk_type);
	REICAST_US(data_write_mode);
	REICAST_US(DriveSel);
	REICAST_US(Error);
	REICAST_US(IntReason);
	REICAST_US(Features);
	REICAST_US(SecCount);
	REICAST_US(SecNumber);
	REICAST_US(GDStatus);
	REICAST_US(ByteCount);

	REICAST_USA(EEPROM,0x100);
	REICAST_US(EEPROM_loaded);

	REICAST_US(maple_ddt_pending_reset);

	mcfg_UnserializeDevices(data, total_size, version < 5);

	if (version < V5)
	{
		REICAST_SKIP(4);
		REICAST_SKIP(1);		// pend_rend
	}
	pend_rend = false;

	REICAST_USA(YUV_tempdata,512/4);
	REICAST_US(YUV_dest);
	REICAST_US(YUV_blockcount);
	REICAST_US(YUV_x_curr);
	REICAST_US(YUV_y_curr);
	REICAST_US(YUV_x_size);
	REICAST_US(YUV_y_size);

	REICAST_USA(pvr_regs,pvr_RegSize);
	fog_needs_update = true ;

	REICAST_US(in_vblank);
	REICAST_US(clc_pvr_scanline);
	if (version < V5)
	{
		REICAST_US(i); 			// pvr_numscanlines
		REICAST_US(i);			// prv_cur_scanline
		REICAST_US(i);			// vblk_cnt
		REICAST_US(i);			// Line_Cycles
		REICAST_US(i);			// Frame_Cycles
		REICAST_SKIP(8);		// speed_load_mspdf
		REICAST_US(i);			// mips_counter
		REICAST_SKIP(8);		// full_rps
		REICAST_US(i); 			// fskip

		REICAST_SKIP(4 * 256);
		REICAST_SKIP(2048);		// ta_fsm
	}
	if (version >= V12)
	{
		REICAST_US(maple_int_pending);
		REICAST_US(fb_w_cur);
	}
	else
		fb_w_cur = 1;
	REICAST_US(ta_fsm[2048]);
	REICAST_US(ta_fsm_cl);

	if (version < V5)
	{
		REICAST_SKIP(4);
		REICAST_SKIP(65536);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
	}
	if (version >= V11)
		UnserializeTAContext(data, total_size, version);

	REICAST_USA(vram.data, vram.size);
	pal_needs_update = true;

	REICAST_USA(OnChipRAM.data(), OnChipRAM_SIZE);

	register_unserialize(CCN, data, total_size, version) ;
	register_unserialize(UBC, data, total_size, version) ;
	register_unserialize(BSC, data, total_size, version) ;
	register_unserialize(DMAC, data, total_size, version) ;
	register_unserialize(CPG, data, total_size, version) ;
	register_unserialize(RTC, data, total_size, version) ;
	register_unserialize(INTC, data, total_size, version) ;
	register_unserialize(TMU, data, total_size, version) ;
	register_unserialize(SCI, data, total_size, version) ;
	register_unserialize(SCIF, data, total_size, version) ;
	if (version >= V9)
		icache.Unserialize(data, total_size);
	else
		icache.Reset(true);
	if (version >= V10)
		ocache.Unserialize(data, total_size);
	else
		ocache.Reset(true);

	REICAST_USA(mem_b.data, mem_b.size);

	if (version < V5)
		REICAST_SKIP(2);
	REICAST_USA(InterruptEnvId,32);
	REICAST_USA(InterruptBit,32);
	REICAST_USA(InterruptLevelBit,16);
	REICAST_US(interrupt_vpend);
	REICAST_US(interrupt_vmask);
	REICAST_US(decoded_srimask);

	REICAST_US(i) ;
	if ( i == 0 )
		do_sqw_nommu = &do_sqw_nommu_area_3 ;
	else if ( i == 1 )
		do_sqw_nommu = &do_sqw_nommu_area_3_nonvmem ;
	else if ( i == 2 )
		do_sqw_nommu = (sqw_fp*)&TAWriteSQ ;
	else if ( i == 3 )
		do_sqw_nommu = &do_sqw_nommu_full ;

	REICAST_USA((*p_sh4rcb).sq_buffer,64/8);

	REICAST_US((*p_sh4rcb).cntx);
	if (version < V5)
	{
		REICAST_SKIP(4);
		REICAST_SKIP(4);
	}

	REICAST_US(sh4_sched_ffb);
	if (version < V8)
		REICAST_US(i);		// sh4_sched_intr

	REICAST_US(sch_list[aica_schid].tag) ;
	REICAST_US(sch_list[aica_schid].start) ;
	REICAST_US(sch_list[aica_schid].end) ;

	REICAST_US(sch_list[rtc_schid].tag) ;
	REICAST_US(sch_list[rtc_schid].start) ;
	REICAST_US(sch_list[rtc_schid].end) ;

	REICAST_US(sch_list[gdrom_schid].tag) ;
	REICAST_US(sch_list[gdrom_schid].start) ;
	REICAST_US(sch_list[gdrom_schid].end) ;

	REICAST_US(sch_list[maple_schid].tag) ;
	REICAST_US(sch_list[maple_schid].start) ;
	REICAST_US(sch_list[maple_schid].end) ;

	REICAST_US(sch_list[dma_sched_id].tag) ;
	REICAST_US(sch_list[dma_sched_id].start) ;
	REICAST_US(sch_list[dma_sched_id].end) ;

	for (int i = 0; i < 3; i++)
	{
		REICAST_US(sch_list[tmu_sched[i]].tag) ;
		REICAST_US(sch_list[tmu_sched[i]].start) ;
		REICAST_US(sch_list[tmu_sched[i]].end) ;
	}

	REICAST_US(sch_list[render_end_schid].tag) ;
	REICAST_US(sch_list[render_end_schid].start) ;
	REICAST_US(sch_list[render_end_schid].end) ;

	REICAST_US(sch_list[vblank_schid].tag) ;
	REICAST_US(sch_list[vblank_schid].start) ;
	REICAST_US(sch_list[vblank_schid].end) ;

	if (version < V8)
	{
		REICAST_US(i); // sch_list[time_sync].tag
		REICAST_US(i); // sch_list[time_sync].start
		REICAST_US(i); // sch_list[time_sync].end
	}

	if (version >= V13)
		REICAST_S(settings.network.EmulateBBA);
	else
		settings.network.EmulateBBA = false;
	if (settings.network.EmulateBBA)
	{
		bba_Unserialize(data, total_size);
	}
	else
	{
		REICAST_US(sch_list[modem_sched].tag);
		REICAST_US(sch_list[modem_sched].start);
		REICAST_US(sch_list[modem_sched].end);
	}

	REICAST_US(SCIF_SCFSR2);
	if (version < V8)
	{
		bool dum_bool;
		REICAST_US(dum_bool);	// SCIF_SCFRDR2
		REICAST_US(i);			// SCIF_SCFDR2
	}
	else if (version >= V11)
		REICAST_US(SCIF_SCSCR2);
	REICAST_US(BSC_PDTRA);

	REICAST_USA(tmu_shift,3);
	REICAST_USA(tmu_mask,3);
	REICAST_USA(tmu_mask64,3);
	REICAST_USA(old_mode,3);
	REICAST_USA(tmu_ch_base,3);
	REICAST_USA(tmu_ch_base64,3);

	REICAST_USA(CCN_QACR_TR,2);

	REICAST_USA(UTLB,64);
	REICAST_USA(ITLB,4);
	if (version >= 11)
		REICAST_USA(sq_remap,64);
	REICAST_USA(ITLB_LRU_USE,64);

	REICAST_US(NullDriveDiscType);
	REICAST_USA(q_subchannel,96);

	if (version < V5)
	{
		REICAST_SKIP(4);
		REICAST_SKIP(4);
	}
	REICAST_US(GSerialBuffer);
	REICAST_US(BSerialBuffer);
	REICAST_US(GBufPos);
	REICAST_US(BBufPos);
	REICAST_US(GState);
	REICAST_US(BState);
	REICAST_US(GOldClk);
	REICAST_US(BOldClk);
	REICAST_US(BControl);
	REICAST_US(BCmd);
	REICAST_US(BLastCmd);
	REICAST_US(GControl);
	REICAST_US(GCmd);
	REICAST_US(GLastCmd);
	REICAST_US(SerStep);
	REICAST_US(SerStep2);
	REICAST_USA(BSerial,69);
	REICAST_USA(GSerial,69);
	REICAST_US(reg_dimm_command);
	REICAST_US(reg_dimm_offsetl);
	REICAST_US(reg_dimm_parameterl);
	REICAST_US(reg_dimm_parameterh);
	REICAST_US(reg_dimm_status);
	if (version < V11)
		REICAST_SKIP(1); // NaomiDataRead

	if (version < V5)
	{
		REICAST_US(i);	// idxnxx
		REICAST_SKIP(sizeof(state_t));
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(1024);

		REICAST_SKIP(8 * sh4_reg_count);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);

		REICAST_SKIP(2 * 4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
		REICAST_SKIP(4 * 4);
		REICAST_SKIP(4);
		REICAST_SKIP(4);
	}
	REICAST_US(settings.dreamcast.broadcast);
	verify(settings.dreamcast.broadcast <= 4);
	REICAST_US(settings.dreamcast.cable);
	verify(settings.dreamcast.cable <= 3);
	REICAST_US(settings.dreamcast.region);
	verify(settings.dreamcast.region <= 3);

	if (CurrentCartridge != NULL)
		CurrentCartridge->Unserialize(data, total_size);
	if (version >= V6)
		gd_hle_state.Unserialize(data, total_size);

	DEBUG_LOG(SAVESTATE, "Loaded %d bytes", *total_size);

	return true ;
}
