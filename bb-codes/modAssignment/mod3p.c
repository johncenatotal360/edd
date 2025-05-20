#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>


#define SIZE (10)

static int myint=100;

static int myArray[SIZE] = {0};
static int count = 0;
int myint_callback = 200;

static int __init my_mod_init(void)
{
	pr_info("ADDED\n");
	return 0;
}

static void __exit my_mod_exit(void)
{
	pr_info("UNLOADED\n");
	return ;
}



int print_change(const char *val, const struct kernel_param *kp){
	if (param_set_int(val, kp) != 0){
		pr_warn("Value can't be set\n");
		return -1;
	}
	pr_info("New value = %d\n", myint_callback);
	return 0;
}

const struct kernel_param_ops ops =
{
	.set = &print_change,
	.get = &param_get_int,
};

module_param_cb(myint_callback, &ops, &myint_callback, S_IWUSR | S_IRUGO);

module_param(myint, int, S_IRUGO | S_IWUSR);
module_param_array(myArray, int, &count, S_IRUGO | S_IWUSR);

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("Module with param support!");

