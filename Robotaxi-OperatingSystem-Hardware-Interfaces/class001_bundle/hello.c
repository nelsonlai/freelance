#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
static char *who = "world";
module_param(who, charp, 0644);
MODULE_PARM_DESC(who, "Name to greet");
static int __init hello_init(void){
    pr_info("hello: init, hello %s\n", who);
    return 0;
}
static void __exit hello_exit(void){
    pr_info("hello: exit, goodbye %s\n", who);
}
module_init(hello_init);
module_exit(hello_exit);
