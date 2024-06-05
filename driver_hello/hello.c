#include <linux/module.h>
#include <linux/kernel.h>

static char *nome = "ARTHUR";
module_param(nome, charp, 0644);
MODULE_PARM_DESC(nome, "Recipient of the hello message");

static int hello_init(void){
printk(KERN_ALERT "Hello %s\n", nome);
return(0);
}
static void hello_exit(void){
printk(KERN_ALERT "Goodbye, cruel world\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author name <author@email.com>");
MODULE_DESCRIPTION("Test kernel module");
MODULE_VERSION("1.0");
