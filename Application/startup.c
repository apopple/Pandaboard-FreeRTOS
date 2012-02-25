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
