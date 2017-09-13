#pragma once
#include <wx/wx.h>
#include "EmulatorEngine.h"
#include "GBCPU.h"
#include "GBTypes.h"

#define RAM_BANK_SIZE         0x1FFF
#define ROM_BANK_SIZE         0x4000
#define ROM_BANK_N_ADDRESS    0x4000
#define OAM_TRANSFER_LEN      0x00A0

#define ADDR_CART_RAM         0xA000

enum BankingMode
{
	BANK_MODE_ROM = 0,
	BANK_MODE_RAM = 1
};

enum CartridgeType
{
	CART_ROM_ONLY = 0,
	CART_MBC1 = 1,
	CART_MBC1_RAM = 2,
	CART_MBC1_RAM_BAT = 3,
	CART_MBC2 = 5,
	CART_MBC2_BAT = 6,
	CART_ROM_RAM = 8,
	CART_ROM_RAM_BAT = 9,
	CART_MMM01 = 0x0B,
	CART_MMM01_RAM = 0x0C,
	CART_MMM01_RAM_BAT = 0x0D,
	CART_MBC3_TIM_BAT = 0x0F,
	CART_MBC3_TIM_RAM_BAT = 0x10,
	CART_MBC3 = 0x11,
	CART_MBC3_RAM = 0x12,
	CART_MBC3_RAM_BAT = 0x13,
	CART_MBC5 = 0x19,
	CART_MBC5_RAM = 0x1A,
	CART_MBC5_RAM_BAT = 0x1B,
	CART_MBC5_RUM = 0x1C,
	CART_MBC5_RUM_RAM = 0x1D,
	CART_MBC5_RUM_RAM_BAT = 0x1E,
	CART_MBC6 = 0x20,
	CART_MBC7_SENS_RUM_RAM_BAT = 0x22,
	CART_POCKET_CAMERA = 0xFC,
	CART_BANDAI_TAMAS = 0xFD,
	CART_HUC3 = 0xFE, 
	CART_HUC1_RAM_BAT = 0xFF
};

class GBCPU;

class GBMMU
{
private:
	GBCPU *m_CPU;
	EmulatorEngine *m_Emulator;
	unsigned char m_Memory[0x10000] = { 0 };
	byte m_CartridgeRam[0x8000] = { 0 };
	int m_CurrentRomBank = 1;
	CartridgeType m_CartType = CART_ROM_ONLY;
	byte *m_RomBin;
	bool m_BootRomEnabled = true;
	bool m_CartRamEnabled = false;
	int m_SelectedRamBank = 0;
	int m_SelectedRTCReg = 0;
	BankingMode m_BankMode = BANK_MODE_ROM;
	int m_LastLatchClockDataWritten = 0;


	void SetupMBC();


public:
	void WriteMemory8(word Address, byte value);
	void WriteMemory16(word Address, word value);
	byte ReadMemory8(word Address);
	word ReadMemory16(word Address);
	void StackPush(word value);
	word StackPop();
	void SwitchRomBank(byte BankNumber);
	void SwitchRamBankOrRTCRegister(byte BankOrRTC);
	void HandleRomRamSelectOrLatchClockData(byte value);
	void SetCPU(GBCPU *CPU);
	void ReadRomFile(wxString RomFilePath);
	void InitMemory();
	void DMATransfer();
	int GetCurrentRomBank();


	GBMMU(EmulatorEngine *Emulator);
	~GBMMU();

};

static const unsigned char BootRom[] = {
	0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F,
	0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26,
	0xFF, 0x0E, 0x11, 0x3E, 0x80, 0x32, 0xE2,
	0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77,
	0x77, 0x3E, 0xFC, 0xE0, 0x47, 0x11, 0x04,
	0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95,
	0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B, 0xFE,
	0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06,
	0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20,
	0xF9, 0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21,
	0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08,
	0x32, 0x0D, 0x20, 0xF9, 0x2E, 0x0F, 0x18,
	0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42,
	0x3E, 0x91, 0xE0, 0x40, 0x04, 0x1E, 0x02,
	0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20,
	0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
	0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE,
	0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64,
	0x20, 0x06, 0x7B, 0xE2, 0x0C, 0x3E, 0x87,
	0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15,
	0x20, 0xD2, 0x05, 0x20, 0x4F, 0x16, 0x20,
	0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB,
	0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17, 0x05,
	0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9,
	0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00,
	0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C,
	0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88,
	0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6,
	0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67,
	0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC,
	0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C,
	0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
	0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A,
	0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE,
	0x34, 0x20, 0xF5, 0x06, 0x19, 0x78, 0x86,
	0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE,
	0x3E, 0x01, 0xE0, 0x50 };