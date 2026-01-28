#include <drivers/acpi.h>
#include <memory/hhdm.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <libk/string.h>

static bool useXSDT = false;
static struct RSDT *currentRSDT = NULL;
static struct XSDT *currentXSDT = NULL;

static bool checksum_RSDP(uint8_t *byte_array, size_t size) {
    uint32_t sum = 0;
    for(size_t i = 0; i < size; i++) {
        sum += byte_array[i];
    }
    return (sum & 0xFF) == 0;
}

// Returns true if the rdsp is initialized correctly
// Side effect: Sets the useXSDT global variable to the correct value
bool acpi_set_correct_RSDT(void *rsdp_addr)
{
    struct RSDPDescriptorV2 *rsdp = rsdp_addr;
    if(!rsdp)
    {
        return false;
    }

    // Verify the signature
    if(strncmp(rsdp->Signature, RSDP_SIGNATURE, 8) != 0)
    {
        return false;
    }

    useXSDT = rsdp->Revision == 2;
    if(useXSDT)
        currentXSDT = (struct XSDT *) hhdm_physToVirt((void *)rsdp->XSDTAddress);
    else
        currentRSDT = (struct RSDT *) hhdm_physToVirt((void *)(uint64_t)rsdp->RsdtAddress);

    return checksum_RSDP((uint8_t *)rsdp, useXSDT ? sizeof(struct RSDPDescriptorV2) :
                                                    sizeof(struct RSDPDescriptorV1));
}

// Returns true if the RSDP revision in 2
bool acpi_isXSDT(void)
{
    return useXSDT;
}

// Returns the local table
void *acpi_getCurrent_RSDT(void)
{
    return useXSDT ? (void *)currentXSDT : (void *)currentRSDT; 
}

// Trova una tabella specifica (es. "APIC")
void *acpi_find_table(const char *signature)
{
    size_t numEntries = useXSDT ? (currentXSDT->sdtHeader.Length - sizeof(currentXSDT->sdtHeader)) / 
                                    sizeof(currentXSDT->sdtAddresses[0]) :
                                  (currentRSDT->sdtHeader.Length - sizeof(currentRSDT->sdtHeader)) / 
                                    sizeof(currentRSDT->sdtAddresses[0]) ;
    
    for(size_t i = 0; i < numEntries; i++)
    {
        uint64_t physAddr = (useXSDT ? currentXSDT->sdtAddresses[i] : 
            (uint64_t)currentRSDT->sdtAddresses[i]);
        
        struct ACPISDTHeader *currentTable = hhdm_physToVirt((void *)physAddr);

        if(strncmp(currentTable->Signature, signature, 4) == 0)
        {
            return (void *)currentTable;
        }
    }

    return NULL;
}