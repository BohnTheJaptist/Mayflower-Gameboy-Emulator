#pragma once
#include "Cartridge.h"
#include "MemoryBankController.h"
#include "GBTypes.h"

class MBC1 :
	public MemoryBankController
{
private:
	mbc_mode m_Mode = MBC_MODE_ROM;
	bool m_RamEnabled = false;
	bool m_BootRomEnabled = true;
	byte *m_CartridgeROM = nullptr;
	byte *m_CartridgeRAM = nullptr;
	cart_attrs m_CartAttrs;
	byte m_RamBank = 0;
	byte m_RomBank = 1;

	void SwitchRomBank(byte BankNumber);

public:
	byte GetRomBankNumber();
	void SetRomBankNumber(byte BankNumber);
	void SetRamBankNumber(byte BankNumber);
	void SetRamEnabled(bool Enabled);
	void SetRamBuffer(byte *RamBuffer, int Size);
	byte GetRamBankNumber();
	byte ReadMemory8(word Address);
	void WriteMemory8(word Address, byte Value);
	MBC1(cart_attrs CartAttrs, byte *CartridgeROM);
	void Destroy();
};

