#include <linux/module.h>   /* Define module_init(), module_exit() */
#include <linux/fs.h>       /* Define alloc_chrdev_region(), register_chrdev_region() */

#define DRIVER_AUTHOR "phonglt9 linuxfromscratch@gmail.com"
#define DRIVER_DESC   "Hello world kernel module"
#define DRIVER_VERS   "1.0"

struct m_foo_dev {
    dev_t dev_num;
} mdev;

/* Constructor */
static int  __init chdev_init(void)
{
    /* 1.0 Dynamic allocating device number (cat /proc/devices) */
    if (alloc_chrdev_region(&mdev.dev_num, 0, 1, "m_cdev") < 0) {
	    pr_err("Failed to alloc chrdev region\n");
	    return -1;
    }

    // dev_t dev = MKDEV(173, 0);
    // register_chrdev_region(&mdev.dev_num, 1, "m-cdev")

    pr_info("Major = %d Minor = %d\n", MAJOR(mdev.dev_num), MINOR(mdev.dev_num));

    pr_info("Hello world kernel module\n");
    return 0;
}

/* Destructor */
static void  __exit chdev_exit(void)
{
    unregister_chrdev_region(mdev.dev_num, 1);              /* 1.0 */
    pr_info("Goodbye\n");
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
MODULE_VERSION(DRIVER_VERS);