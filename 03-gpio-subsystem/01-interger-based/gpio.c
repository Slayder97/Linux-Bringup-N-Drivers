#include <linux/module.h>   /* Defines functions such as module_init/module_exit */
#include <linux/gpio.h>     /* Defines functions such as gpio_request/gpio_free */     

#define GPIO0_30            30

#define LOW                 0
#define HIGH                1

#define DRIVER_AUTHOR "phonglt15 p.linuxfromscratch@gmail.com"
#define DRIVER_DESC   "gpio subsystem"

/* Constructor */
static int __init gpio_init(void)
{
    gpio_request(GPIO0_30, "gpio0_30");
    gpio_direction_output(GPIO0_30, LOW);
    gpio_set_value(GPIO0_30, HIGH);

    pr_info("Hello! gpio status: %d!\n", gpio_get_value(GPIO0_30));
    return 0;
}

/* Destructor */
static void __exit gpio_exit(void)
{
    gpio_set_value(GPIO0_30, LOW);
    gpio_free(GPIO0_30);
    pr_info("Good bye my fen !!!\n");
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC); 
MODULE_VERSION("1.0"); 