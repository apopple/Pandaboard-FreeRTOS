/* A program to ready one of the Cortex-M3 cores for execution */
/* Assumes the program for the Cortex-M3 has been loaded into 0x83000000 */

/* Defines the pysical address where the program for the Cortex-M3 is loaded */
#define M3_LOAD_ADDRESS 0x84000000

int *CM_MPU_M3_CLKSTCTRL = (int *) 0x4a008900;
int *CM_MPU_M3_MPU_M3_CLKCTRL = (int *) 0x4a008920;
int *RM_MPU_M3_RSTCTRL = (int *) 0x4a306910;
int *MMU_CNTL = (int *) 0x55082044;
int *MMU_TTB = (int *) 0x5508204c;

int __attribute__ ((aligned(0x4000))) TTB[4096];

void setup_l2mmu()
{
  int i;

  /* Brings the L2 MMU out of reset and sets up virtual addresses */
  *CM_MPU_M3_MPU_M3_CLKCTRL = 0x01;
  *CM_MPU_M3_CLKSTCTRL = 0x02;
  *RM_MPU_M3_RSTCTRL &= ~0x4;

  /* Initialise address translation table */
  /* Every address will be mapped to M3_LOAD_ADDRESS */
  for( i = 0; i < 4096; i++ )
  {
    TTB[i] = (M3_LOAD_ADDRESS & 0xfff00000) | 0x00c02;
  }

  /* Set the last entry to point to the GPIO1 peripheral to flash a light */
  /* ie. Virtual address of GPIO1_DATAOUT is 0xfff1013c */
  TTB[4095] = 0x4a300c02;

  /* Set the base address */
  *MMU_TTB = (int) &TTB[0];

  /* Enable MMU */
  *MMU_CNTL = 0x6;
}

void start_m3()
{
  /* Release Cortex-M3 from reset */
  *RM_MPU_M3_RSTCTRL &= ~1;
}

int main()
{
  setup_l2mmu();
  start_m3();
  while(1);
}
