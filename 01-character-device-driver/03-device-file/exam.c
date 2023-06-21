#include <linux/module.h>   /* Define module_init(), module_exit() */
#include <linux/fs.h>       /* Define alloc_chrdev_region(), register_chrdev_region() */
#include <linux/device.h>   /* Define device_create(), class_create() */

#define DRIVER_AUTHOR "phonglt9 linuxfromscratch@gmail.com"
#define DRIVER_DESC   "Hello world kernel module"
#define DRIVER_VERS   "1.0"

struct m_foo_dev {
    dev_t dev_num;
    struct class *m_class;
} mdev;

/* Constructor */
static int  __init chdev_init(void)
{
    /* 1.0 Dynamic allocating device number (cat /proc/devices) */
    if (alloc_chrdev_region(&mdev.dev_num, 0, 1, "m_cdev") < 0) {
	    pr_err("Failed to alloc chrdev region\n");
	    return -1;
    }

    /* 1.1 Static allocating device number (cat /proc/devices) */
    // dev_t dev = MKDEV(173, 0);
    // register_chrdev_region(&mdev.dev_num, 1, "m-cdev")

    pr_info("Major = %d Minor = %d\n", MAJOR(mdev.dev_num), MINOR(mdev.dev_num));

    /* 2.0 Creating struct class */
    if ((mdev.m_class = class_create(THIS_MODULE, "m_class")) == NULL) {
        pr_err("Cannot create the struct class for my device\n");
        goto rm_device_numb;
    }

    /* 3.0 Creating device*/
    if ((device_create(mdev.m_class, NULL, mdev.dev_num, NULL, "m_device")) == NULL) {
        pr_err("Cannot create my device\n");
        goto rm_class;
    }

    pr_info("Hello world kernel module\n");
    return 0;

rm_class:
    class_destroy(mdev.m_class);
rm_device_numb:
    unregister_chrdev_region(mdev.dev_num, 1);
    return -1;
}

/* Destructor */
static void  __exit chdev_exit(void)
{
    device_destroy(mdev.m_class, mdev.dev_num);             /* 3.0 */
    class_destroy(mdev.m_class);                            /* 2.0 */
    unregister_chrdev_region(mdev.dev_num, 1);              /* 1.0 */
    pr_info("Goodbye\n");
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);  
MODULE_VERSION(DRIVER_VERS);