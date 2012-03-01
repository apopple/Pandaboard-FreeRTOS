#include <linux/init.h>
#include <linux/module.h>
#include <linux/remoteproc.h>

MODULE_LICENSE("Dual DSD/GPL");

static int rproc_init(void) {
  void *my_rproc;

  printk(KERN_ALERT "Booting processor\n");

  /* let's power on and boot the image processing unit */
  my_rproc = rproc_get_by_name("ipu_c0");
  if (!my_rproc) {
    /*
     * something went wrong. handle it and leave.
     */
    printk(KERN_ALERT "Something went wrong\n");
  }

  /*
   * the 'ipu' remote processor is now powered on, and we have a
   * valid handle.... let it work !
   */

  return 0;
}

static void rproc_exit(void) {
  /* We should stop the remote processor on unload */
}

module_init(rproc_init);
module_exit(rproc_exit);
