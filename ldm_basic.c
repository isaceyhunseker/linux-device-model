/*
 * Basic Structure in Linux Device
 *
 * This Program creates and registers basic dummy bus, driver and device 
 * according to Linux Device Model.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/platform_device.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/phy_fixed.h>
#include <linux/export.h>
#include <linux/ethtool.h>
#include <linux/workqueue.h>
#include <linux/module.h>
#include <linux/if_bridge.h>

#include "ldm_basic.h"

void ldm_basic_device_release(struct device *dev)
{
	printk(KERN_DEBUG "[EXP] ldm_basic_device release\n");
}

// Match devices to drivers.  Just do a simple name test.
static int ldm_basic_match(struct device *dev, struct device_driver *driver)
{
	return !strncmp(dev_name(dev), driver->name, strlen(driver->name));
}

// Respond to udev events.
static int ldm_basic_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	add_uevent_var(env, "DEV_NAME=%s", dev_name(dev));
	return 0;
}

static struct bus_type ldm_basic_bus_type = 
{
	.name		= "ldm_basic_bus",
	.match		= ldm_basic_match,
	.uevent		= ldm_basic_uevent,
};

static struct ldm_basic_driver ldm_basic_drv = 
{
	.module = THIS_MODULE,
    	.driver = {
		.name = "ldm_basic_driver",
		.bus	= &ldm_basic_bus_type,
    },
};

static struct ldm_basic_device ldm_basic_dev = 
{
	.dev = {
		.driver = &ldm_basic_drv.driver,
		.init_name   = "ldm_basic_device",
		.bus = &ldm_basic_bus_type,
		.release = ldm_basic_device_release,
	}, 
	.name ="ldm_basic_device",
};

static int ldm_basic_device_register(struct ldm_basic_device *dev)
{
	pr_info ("[EXP] init ldm_basic_device_register, line %d\n",__LINE__);
	dev_set_name(&dev->dev, dev->name);
	return device_register(&dev->dev);
	pr_info ("[EXP] exit ldm_basic_device_register, line %d\n",__LINE__);
}

static void ldm_basic_device_unregister(struct ldm_basic_device *dev)
{
	pr_info ("[EXP] device_unregister init, line %d\n",__LINE__);
	device_unregister(&dev->dev);
	pr_info ("[EXP] device_unregister exit %d\n",__LINE__);
}

int ldm_basic_driver_register(struct ldm_basic_driver *drv)
{
	int retval;
	
	pr_info ("[EXP] init ldm_basic_driver_register, line %d\n",__LINE__);
	retval = driver_register(&drv->driver);

	if (retval) {
		pr_err("%s: Error %d in registering driver\n", drv->driver.name, retval);
		return retval;
	}

	pr_info ("[EXP] exit ldm_basic_driver_register, line %d\n",__LINE__);
	return 0;
}

void ldm_basic_driver_unregister(struct ldm_basic_driver *drv)
{
	driver_unregister(&drv->driver);
}

static int __init ldm_basic_init(void)
{
	int ret;

	printk(KERN_ALERT "[EXP] INIT_BEGIN, line %d\n",__LINE__);
	pr_info ("[EXP] init ldm_basic_bus_register, line %d\n",__LINE__);
	ret = bus_register(&ldm_basic_bus_type);

	if (ret) 
	{
		printk(KERN_ERR "Unable to register the bus, failure was %d\n",ret);
		return ret;
	}
	pr_info ("[EXP] exit ldm_basic_bus_register, line %d\n",__LINE__);

	ldm_basic_driver_register(&ldm_basic_drv);
	ldm_basic_device_register(&ldm_basic_dev);

	printk(KERN_ALERT "[EXP] BUS, DRIVER AND DEVICE INITIALIZED, line %d\n",__LINE__);
	return 0;
}

module_init(ldm_basic_init);

static void __exit ldm_basic_exit(void)
{   
	printk(KERN_ALERT "[EXP] EXIT, line %d\n",__LINE__);
	ldm_basic_device_unregister(&ldm_basic_dev);
	ldm_basic_driver_unregister(&ldm_basic_drv);
	bus_unregister(&ldm_basic_bus_type);
	printk(KERN_ALERT "[EXP] UNREGISTIRATION COMPLETED, line %d\n",__LINE__);
}
module_exit(ldm_basic_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Isa Ceyhun Seker");
MODULE_DESCRIPTION("Basic Structure - LDM");
