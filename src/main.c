/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/settings/settings.h>

#include <errno.h>
#include <zephyr/sys/printk.h>

int beta_handle_set(const char *name, size_t len, settings_read_cb read_cb,
		  void *cb_arg)
{
	return 0;
}

int beta_handle_commit(void)
{
	return 0;
}

int beta_handle_export(int (*cb)(const char *name,
			       const void *value, size_t val_len))
{
	return 0;
}

int beta_handle_get(const char *name, char *val, int val_len_max)
{
	return 0;
}

/* static subtree handler */
SETTINGS_STATIC_HANDLER_DEFINE(beta, "beta", beta_handle_get,
			       beta_handle_set, beta_handle_commit,
			       beta_handle_export);

static uint32_t val;

void main(void)
{
	int i, rc;
	uint32_t time;

	rc = settings_subsys_init();
	if (rc) {
		printk("settings subsys initialization: fail (err %d)\n", rc);
		return;
	}

	settings_load();

	printk("\n*** Settings usage example ***\n\n");

	time = k_uptime_get_32();
	printk("start time %d\n", time);


	for (i = 0; i < 6; i++) {
		printk("\n##############\n");
		printk("# iteration %d", i);
		printk("\n##############\n");

		for (int j = 0; j < 24; j++) {
			char name[10];

			snprintf(name, 10, "beta/%d", j);

			rc = settings_save_one(name, val++, sizeof(val));
			if (rc) {
				printk("error save name:%s\n", name);
				continue;
			}
		}

		for (int j = 23; j >= 0; j--) {
			char name[10];

			snprintf(name, 10, "beta/%d", j);

			rc = settings_save_one(name, val++, sizeof(val));
			if (rc) {
				printk("error save name:%s\n", name);
				continue;
			}
		}
	}

	printk("end time %d (%d)\n", k_uptime_get_32(), k_uptime_get_32() - time);

	printk("\n*** THE END  ***\n");
}
