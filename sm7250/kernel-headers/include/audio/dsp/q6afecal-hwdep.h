/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2014, 2018, The Linux Foundation. All rights reserved.
 */
#ifndef __Q6AFECAL_HWDEP_H__
#define __Q6AFECAL_HWDEP_H__
#include <sound/msmcal-hwdep.h>

enum q6afe_cal_states {
	Q6AFECAL_UNINITIALISED,
	Q6AFECAL_INITIALISED,
	Q6AFECAL_RECEIVED
};

struct afe_fw_info {
	struct firmware_cal *fw[Q6AFE_MAX_CAL];
	DECLARE_BITMAP(cal_bit, Q6AFE_MAX_CAL);
	/* for calibration tracking */
	unsigned long q6afecal_state[Q6AFE_MAX_CAL];
	struct mutex lock;
};

struct firmware_cal {
	u8 *data;
	size_t size;
};

#if IS_ENABLED(CONFIG_AFE_HWDEP)
int q6afe_cal_create_hwdep(void *fw, int node, void *card);
struct firmware_cal *q6afecal_get_fw_cal(struct afe_fw_info *fw_data,
					enum q6afe_cal_type type);
#else /* CONFIG_AFE_HWDEP */
static __inline__ int q6afe_cal_create_hwdep(void *fw, int node, void *card)
{
	return 0;
}

static __inline__ struct firmware_cal *q6afecal_get_fw_cal(
					struct afe_fw_info *fw_data,
					enum q6afe_cal_type type)
{
	return NULL;
}
#endif /* CONFIG_AFE_HWDEP */
#endif /* __Q6AFECAL_HWDEP_H__ */
