 // SPDX-License-Identifier: GPL-2.0

#include <linux/mm.h>

void init_helper(bool enable);

extern int boost_mode __read_mostly;
#ifdef CONFIG_ARCH_SDM845
extern int fps_mode __read_mostly;
extern int set_fps __read_mostly;
#endif
extern int set_pid_boost __read_mostly;
extern bool limited __read_mostly;

extern int oprofile __read_mostly;
extern bool boost_storage __read_mostly;
// Old display
#ifdef CONFIG_ARCH_SM8150
extern bool use_old_mdsi_pan __read_mostly;
#endif

extern int gamer __read_mostly;
//extern int gamer_low __read_mostly;
extern int throttle_mode __read_mostly;
extern int haptic_gain __read_mostly;
extern int haptic_gain_show __read_mostly;
extern int dynamic_charger __read_mostly;
extern int temp_batt;
extern int dc_show;
extern int temp_avg_show;
extern int oplus_panel_status;

extern bool touch_boost;
extern bool touch_boost_qos;
extern bool touch_boost_cpu;
extern bool touch_boost_mode;
