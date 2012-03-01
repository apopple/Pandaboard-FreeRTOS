#include <stdint.h>

/* Not static so it can be used as the entry point */
void ResetISR(void);
static void NmiISR(void);
static void FaultISR(void);
static void DefaultISR(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler( void );

extern int main(void);

#define STACK_SIZE 64
static unsigned long Stack[STACK_SIZE];

/* ---------------------------------------------------------
   These definitions come from <linux/remoteproc.h> and
   may change as the remote processor interface is updated.
   Make sure they match the ones used by your current kernel
   source.
   ---------------------------------------------------------
*/
typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t u8;

struct fw_resource {
	u32 type;
	u32 id;
	u64 da;
	u64 pa;
	u32 len;
	u32 flags;
	u8 reserved[16];
	u8 name[48];
} __packed;

enum fw_resource_type {
	RSC_CARVEOUT	= 0,
	RSC_DEVMEM	= 1,
	RSC_TRACE	= 2,
	RSC_VRING	= 3,
	RSC_VIRTIO_DEV	= 4,
	RSC_VIRTIO_CFG	= 5,
};

/* --------------------------------------------------------- */

#define RESERVED {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

/* Describe the resources required by this firmware image.  Currently
   we simply map 1M of pyhsical memory from PA 0xb0000000 to the device
   address 0x0 to hold our text/data sections.  We also map a 1M block
   containing the GPIO1 perihperal registers (PA 0x4a300000) to a device
   address 0xfff00000 so we can flash a LED. */
__attribute__ ((section(".resource_table")))
struct fw_resource resources[] = {
  { RSC_CARVEOUT, 0, 0, 0xb0000000, 0x100000, 0x0, RESERVED, "text" },
  { RSC_DEVMEM, 1, 0xfff00000, 0x4a300000, 0x100000, 0x0, RESERVED, "gpio1" },
};

__attribute__ ((section(".resource_size")))
uint32_t resourcesLen = sizeof(resources)/sizeof(*resources);

__attribute__ ((section(".isr_vector")))
void (* const Vectors[])(void) =
{
  (void (*)(void))((unsigned long) Stack + sizeof(Stack)),  // Initial stack pointer
  ResetISR,  // Reset
  NmiISR,    // Nmi
  FaultISR,  // Hard fault
  DefaultISR,  // MPU fault
  DefaultISR,  // Bus fault
  DefaultISR,  // Usage fault
  0,
  0,
  0,
  0,
  vPortSVCHandler,  // SVCall handler
  DefaultISR,  //Debug
  0,
  xPortPendSVHandler,  // PendSV
  xPortSysTickHandler,  // SysTick
 
  /* Vendor Handlers */
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
  DefaultISR,
};

void ResetISR(void)
{
  main();
}

static void NmiISR(void)
{
  while(1) {}
}

static void FaultISR(void)
{
  while(1) {}
}

static void DefaultISR(void)
{
  while(1) {}
}
