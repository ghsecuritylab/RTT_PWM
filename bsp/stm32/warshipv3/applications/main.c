/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PB5 */
#define LED0_PIN    GET_PIN(B, 5)
/* defined the LED0 pin: PE5 */
#define LED1_PIN    GET_PIN(E, 5)

#define PWM_DEV_NAME            "pwm3"  /* PWM???? */
#define PWM_DEV_CHANNEL         1       /* PWM?? */
#define THREAD_PRIORITY         15      /* ????? */
#define THREAD_STACK_SIZE       512     /* ????? */
#define THREAD_TIMESLICE        5       /* ??????? */
static rt_thread_t tid1 = RT_NULL;      /* ???? */
struct rt_device_pwm *pwm_dev;          /* PWM???? */
static rt_uint32_t period = 1300000000;     /* ???0.5ms,?????ns */
static rt_uint32_t pulse = 1300000000;           /* PWM?????????? */

/* ?? pwm_entry ????? */
static void pwm_entry(void *parameter)
{
    rt_uint32_t count = 0;

    while (1)
    {
        rt_thread_mdelay(5000);
        /* step 2??? PWM ???????,??????? */
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
			pulse-=50000000;
			if(pulse < 500) pulse=1300000000;
//			rt_kprintf("pwm pulse is %d \n", pulse);
			
    }
    /* step 3??????????,???? PWM ????? */
    rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
}

int main(void)
{
    /* step 1.1??? PWM ?? */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* step 1.2??? PWM ?????????? */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    /* step 1.3??? PWM ??????? */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    /* ????,??? pwm_thread ,??? pwm_entry*/
    tid1 = rt_thread_create("pwm_thread",
                             pwm_entry,
                             RT_NULL,
                             THREAD_STACK_SIZE,
                             THREAD_PRIORITY,
                             THREAD_TIMESLICE);

    /* ?????????,?????? */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    return RT_EOK;
}


