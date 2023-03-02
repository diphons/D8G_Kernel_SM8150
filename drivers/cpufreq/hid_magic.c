/*
 * Copyright (C) 2021 LibXZR <xzr467706992@163.com>.
 */

#include <linux/cpufreq.h>
#include <linux/moduleparam.h>
#include <misc/d8g_helper.h>

#define FREQ_LIMIT_LP 0
#ifdef CONFIG_ARCH_SDM845
#define FREQ_LIMIT_PERF 2092800
#else
#define FREQ_LIMIT_PERF 1862400
#define FREQ_LIMIT_PRIME 2073600
#endif

#ifdef CONFIG_OXYGEN_OS
static bool msg = false;
#else
static bool msg = true;
#endif
module_param(msg, bool, 0644);

bool limit_user __read_mostly;
//const int poolsize_value __read_mostly = 128;

static inline void limit_max(struct cpufreq_policy *policy,
			unsigned int freq)
{
	if (!freq)
		return;

	if (policy->max > freq)
		policy->max = freq;
}

void restrict_frequency(struct cpufreq_policy *policy)
{
//	*(int*)&poolsize_value = poolsize_set * 8;

//	if (poolsize_value < 128) {
//		*(int*)&poolsize_value = 128;
//	}
	if (!msg) {
		limit_user = false;
	} else {
		limit_user = true;
	}

	init_helper(limit_user);

	if (!limit_user)
		return;

	if (cpumask_test_cpu(policy->cpu, cpu_lp_mask))
		limit_max(policy, FREQ_LIMIT_LP);
#ifdef CONFIG_ARCH_SDM845
	else
		limit_max(policy, FREQ_LIMIT_PERF);
#else
	else if (cpumask_test_cpu(policy->cpu, cpu_perf_mask))
		limit_max(policy, FREQ_LIMIT_PERF);
	else
		limit_max(policy, FREQ_LIMIT_PRIME);
#endif
}

void set_frequency_limit(bool enable) {
	int ret;

	//if (enable)
	//	do_freq = 1;
		msg = enable;
	//else
	//	do_freq = 0;

	ret = cpufreq_policy_reset_limit();
	if (ret)
		pr_err("Unable to reset policy limits\n");
}
