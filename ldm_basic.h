/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __LDM_BASIC_H
#define __LDM_BASIC_H

struct ldm_basic_device {
	char *name;
	struct ldm_basic_driver *ldm_basic_drv;
	struct resource		resource;
	unsigned int		irq;
	unsigned int		id;
	struct device dev;
};

struct ldm_basic_driver {
	struct module *module;
	struct device_driver driver;
};

#define to_ldm_basic_device(_dev) container_of(_dev, struct ldm_basic_device, dev)
#define to_ldm_basic_driver(_drv) container_of(_drv, struct ldm_basic_driver, driver)

#endif /* __LDM_BASIC_H */
