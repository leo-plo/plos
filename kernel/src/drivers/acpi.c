#include <common/logging.h>
#include <cpu.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <drivers/acpi.h>
#include <memory/hhdm.h>
#include <libk/string.h>

extern struct limine_rsdp_request rsdp_request;

static bool useXSDT = false;
static struct RSDT *rsdt = NULL;
static struct XSDT *xsdt = NULL;

static bool validate_checksum(uint8_t *byte_array, size_t size) {
    uint32_t sum = 0;
    for(size_t i = 0; i < size; i++) {
        sum += byte_array[i];
    }
    return (sum & 0xFF) == 0;
}

/**
 * @brief Initialize the ACPI
 * Verifys the tables and checksums
 * @note sets useXSDT and rsdt/xsdt global variables
 */
void acpi_init()
{
    struct RSDPDescriptorV2 *rsdp = rsdp_request.response->address;

    // Verify the signature
    if(strncmp(rsdp->Signature, RSDP_SIGNATURE, 8) != 0)
    {
        log_line(LOG_ERROR, "%s: The RSDP signature is invalid", __FUNCTION__);
        hcf();
    }

    // Validate the v1 checksum
    if(!validate_checksum((uint8_t *) rsdp, sizeof(struct RSDPDescriptorV1)))
    {
        log_line(LOG_ERROR, "%s: The RSDPV1 checksum is invalid", __FUNCTION__);
        hcf();
    }

    // Check if we can use XSDT
    if(rsdp->Revision >= 2 && rsdp->XSDTAddress != 0)
    {
        // Validate the v2 checksum
        if(!validate_checksum((uint8_t *) rsdp, sizeof(struct RSDPDescriptorV2)))
        {
            log_line(LOG_ERROR, "%s: The RSDPV2 checksum is invalid", __FUNCTION__);
            hcf();
        }

        useXSDT = true;
        xsdt = hhdm_physToVirt((void *) rsdp->XSDTAddress);
        log_line(LOG_SUCCESS, "%s: xsdt pointer obtained", __FUNCTION__);
    }
    else 
    {
        useXSDT = false;
        rsdt = hhdm_physToVirt((void *)(uint64_t)rsdp->RSDTAddress);
        log_line(LOG_SUCCESS, "%s: rsdt pointer obtained", __FUNCTION__);
        
    }
}

/**
 * @brief Find a specific sdt table (es. "MADT")
 * 
 * @param signature The 4 bytes signature of the table we want to search for 
 * @return void* A pointer to the table header if found, NULL otherwise
 */
void *acpi_find_table(const char *signature)
{
    if(!rsdt || !xsdt) return NULL;

    // Calculate the number of entries
    size_t numEntries;
    if(useXSDT)
        numEntries = (xsdt->sdtHeader.Length - sizeof(struct ACPISDTHeader)) / 8;
    else 
        numEntries = (rsdt->sdtHeader.Length - sizeof(struct ACPISDTHeader)) / 4;

    // Iterate all the tables
    for(size_t i = 0; i < numEntries; i++)
    {
        uint64_t physAddr = (useXSDT ? xsdt->sdtAddresses[i] : (uint64_t)rsdt->sdtAddresses[i]);
        struct ACPISDTHeader *currentTable = hhdm_physToVirt((void *)physAddr);

        // Check for signature match
        if(strncmp(currentTable->Signature, signature, 4) == 0)
        {
            return (void *)currentTable;
        }
    }

    return NULL;
}