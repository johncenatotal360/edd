/* Automatic device node creation - has a bug - resolve it! */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>

#define MY_CLASS_NAME	"cdac_cls"
#define MY_DEV_NAME	"cdac_dev"
#define NUM_DEVS	(5)

dev_t dev = 0;
static struct class *dev_class;
static struct device *cdevice[NUM_DEVS];

static int __init my_mod_init(void)
{
	int ans,i, major, minor;
	char dev_string[10]={0};

	pr_info("Hello world from mod33!\n");
	ans = alloc_chrdev_region(&dev, 0, NUM_DEVS, MY_DEV_NAME);
	if (ans<0)
	{
		pr_err("Error in major:minor allotment!\n");
		return -1;
	}
	pr_info("major:minor range of %d devices %d:%d allotted!\n", NUM_DEVS, MAJOR(dev),MINOR(dev));

	dev_class = class_create(THIS_MODULE, MY_CLASS_NAME); // why THIS?
	if (IS_ERR(dev_class))
	{
		pr_err("Could not create device class %s\n", MY_CLASS_NAME);
		goto r_class; // goto is fine for kernel
		/*goto instead of return cuz you gotta unregister the major and minor 
		why not alloc kernel space at the end?
		in that way maybe static allocation is good?
		 "without goto code be horribly complicated tho"
		 "Unlearn some c programming to know kernel"*/

		// "Every line is dangerous in kernel anyway" 
	}

	major = MAJOR(dev);
	for (i=0;i<NUM_DEVS;i++)
	{
		minor = i;
		dev = MKDEV(major, minor);
		sprintf(dev_string, "%s%d", MY_DEV_NAME, i); // sprintf???::
		cdevice[i] = device_create(dev_class, NULL, dev, NULL, dev_string);
		if (IS_ERR(cdevice[i]))
		{
			pr_err("Could not create device %s\n", dev_string);
			goto r_device;
		}
	}
	pr_info("%d devices %s under class %s created with success\n", 
			i, MY_DEV_NAME, MY_CLASS_NAME);
	return 0;

r_device: // stack in action aka Error Ladder
	i--;
	for (;i>=0; i--){
		dev = MKDEV(major, i);
		device_destroy(dev_class, dev);
	}
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev, NUM_DEVS);
	return -1;
}

static void __exit my_mod_exit(void)
{
	int major, i;
	pr_info("Goodbye world from mod33!\n");
	major = MAJOR(dev);
	for (i=0;i<NUM_DEVS;i++)
	{
		// make dev
		dev = MKDEV(major, i);
		// if device exists
		device_destroy(dev_class, dev);
		// destroy device

	}	
	dev = MKDEV(major, 0);
	class_destroy(dev_class);
	unregister_chrdev_region(dev, NUM_DEVS);
	pr_info("major:minor numbers freed up...\n");
	return;
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Device node creation module!");
