/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include <app_version.h>

#include <prometheus/pm_exposer.h>
#include <prometheus/pm_collector.h>
#include <prometheus/pm_counter.h>
#include <prometheus/pm_gauge.h>
#include <prometheus/pm_histogram.h>
#include <prometheus/pm_summary.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#define PORT         8080
#define METRICS_PATH "/metrics"

int main(void)
{

	printk("Zephyr Example Application %s\n", APP_VERSION_STRING);

	// Create a mock collector with different types of metrics
	pm_collector_t *collector = pm_collector_create();

	pm_label_t labels[] = {{"label1", "value1"}, {"label2", "value2"}};
	pm_counter_t *counter = pm_counter_create("test_counter", "Test counter", labels, 2);
	pm_counter_inc(counter);

	pm_collector_register_metric(collector, (pm_metric_t *)counter);

	// TO DO: Add more metrics to the collector and test them

	pm_exposer_start(PORT, METRICS_PATH, collector);

	return 0;
}

