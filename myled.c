#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda & Soma Mitsuike");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;

static volatile u32 *gpio_base = NULL;

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos){
	char c;
	int i, p=100, b=400, t=500;

void ton(void) {gpio_base[7] = 1 << 25; msleep(p); gpio_base[10] = 1 << 25; msleep(p);}
void tuu(void) {gpio_base[7] = 1 << 25; msleep(b); gpio_base[10] = 1 << 25; msleep(p);}

	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;
	switch(c){
		case 'a':ton();tuu();		 msleep(t);break;
		case 'b':tuu();ton();ton();ton();msleep(t);break;
		case 'c':tuu();ton();tuu();ton();msleep(t);break;
		case 'd':tuu();ton();ton();	 msleep(t);break;
		case 'e':ton();			 msleep(t);break;
		case 'f':ton();ton();tuu();ton();msleep(t);break;
		case 'g':tuu();tuu();ton();	 msleep(t);break;
		case 'h':ton();ton();ton();ton();msleep(t);break;
		case 'i':ton();ton();		 msleep(t);break;
		case 'j':ton();tuu();tuu();tuu();msleep(t);break;
		case 'k':tuu();ton();tuu();	 msleep(t);break;
		case 'l':ton();tuu();ton();ton();msleep(t);break;
		case 'm':tuu();tuu();		 msleep(t);break;
		case 'n':tuu();ton();		 msleep(t);break;
		case 'o':tuu();tuu();tuu();      msleep(t);break;
		case 'p':ton();tuu();tuu();ton();msleep(t);break;
		case 'q':tuu();tuu();ton();tuu();msleep(t);break;
		case 'r':ton();tuu();ton();      msleep(t);break;
		case 's':ton();ton();ton();      msleep(t);break;
		case 't':tuu();                  msleep(t);break;
		case 'u':ton();ton();tuu();      msleep(t);break;
		case 'v':ton();ton();ton();tuu();msleep(t);break;
		case 'w':ton();tuu();tuu();      msleep(t);break;
		case 'x':tuu();ton();ton();tuu();msleep(t);break;
		case 'y':tuu();ton();tuu();tuu();msleep(t);break;
		case 'z':tuu();tuu();ton();ton();msleep(t);break;
		case '\n':                                 break;
		default:
			for(i=0; i<20; i++){
				ton();
			}
			break;
	}
	return 1;

}
static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write
};

static int __init init_mod(void){
	int retval;
	gpio_base = ioremap_nocache(0xfe200000, 0xA0); 

	const u32 led = 25;
	const u32 index = led/10;
	const u32 shift = (led%10)*3;
	const u32 mask = ~(0x7 << shift);
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
	
	retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));
	
	cdev_init(&cdv, &led_fops);
	cdv.owner = THIS_MODULE;
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}
	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
																return 0;
}
static void __exit cleanup_mod(void){
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
	iounmap(gpio_base);
}

module_init(init_mod);
module_exit(cleanup_mod);
