#include "../../include/YSystem/YMachineInfo.h"

using namespace YLR;
using namespace YSystem;

std::string * YMachineInfo::getCpuID()
{
	std::string * CPUID = NULL;
    unsigned long s1,s2;
    char vendor_id[]="------------";
    char sel;
    sel='1';

    std::string VernderID;
    std::string MyCpuID,CPUID1,CPUID2;
    switch(sel)
    {
    case '1':
        __asm{
            xor eax,eax      //eax=0:取Vendor信息
            cpuid    //取cpu id指令，可在Ring3级使用
            mov dword ptr vendor_id,ebx
            mov dword ptr vendor_id[+4],edx
            mov dword ptr vendor_id[+8],ecx
        }

		VernderID = std::string(vendor_id);
        __asm{
            mov eax,01h   //eax=1:取CPU序列号
            xor edx,edx
            cpuid
            mov s1,edx
            mov s2,eax
        }

		char buffer[20];
		memset(buffer,0,20);
		sprintf_s(buffer,"%08X%08X",s1,s2);
		CPUID1 = std::string(buffer);
        __asm{
            mov eax,03h
            xor ecx,ecx
            xor edx,edx
            cpuid
            mov s1,edx
            mov s2,ecx
        }

		memset(buffer,0,20);
		sprintf_s(buffer,"%08X%08X",s1,s2);
		CPUID2 = std::string(buffer);
        break;
    case '2':
        {
            __asm{
                mov ecx,119h
                rdmsr
                or eax,00200000h
                wrmsr
            }
        }

        CPUID = NULL;
        break;
    }

    MyCpuID = CPUID1+CPUID2;

    CPUID = new std::string(MyCpuID);

	return CPUID;
}

void YMachineInfo::freeText(std::string * s)
{
	delete s;
}