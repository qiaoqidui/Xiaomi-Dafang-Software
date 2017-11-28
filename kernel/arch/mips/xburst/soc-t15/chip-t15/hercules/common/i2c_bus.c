#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/interrupt.h>
#include <linux/i2c/pca953x.h>
#include "board_base.h"
#include "mach/jzsnd.h"

#if (defined(CONFIG_I2C_GPIO) || defined(CONFIG_I2C0_V12_JZ))
struct i2c_board_info jz_i2c0_devs[] __initdata = {
};
#endif

#ifdef CONFIG_WM8594_CODEC_V12
static struct snd_codec_data wm8594_codec_pdata = {
		.codec_sys_clk = 1200000,
};
#endif

#ifdef CONFIG_AK4951_CODEC
static struct snd_codec_data ak4951_codec_pdata = {
		.codec_sys_clk = 1200000,
};
#endif

#if (defined(CONFIG_I2C_GPIO) || defined(CONFIG_I2C1_V12_JZ))
struct i2c_board_info jz_i2c1_devs[] __initdata = {
#ifdef CONFIG_AK4951_CODEC
	{
		I2C_BOARD_INFO("ak4951en",0x12),
		.platform_data = &ak4951_codec_pdata,
	},
#endif
};
#endif  /*I2C1*/

#if (defined(CONFIG_I2C_GPIO) || defined(CONFIG_I2C3_V12_JZ))
struct i2c_board_info jz_i2c3_devs[] __initdata = {
#ifdef CONFIG_WM8594_CODEC_V12
	{
		I2C_BOARD_INFO("wm8594",0x1a),
		.platform_data = &wm8594_codec_pdata,
	},
#endif
};
#endif  /*I2C3*/
#if	(defined(CONFIG_SOFT_I2C0_GPIO_V12_JZ) || defined(CONFIG_I2C0_V12_JZ))
int jz_i2c0_devs_size = ARRAY_SIZE(jz_i2c0_devs);
#endif

#if	(defined(CONFIG_SOFT_I2C1_GPIO_V12_JZ) || defined(CONFIG_I2C1_V12_JZ))
int jz_i2c1_devs_size = ARRAY_SIZE(jz_i2c1_devs);
#endif

#if	(defined(CONFIG_SOFT_I2C3_GPIO_V12_JZ) || defined(CONFIG_I2C3_V12_JZ))
int jz_i2c3_devs_size = ARRAY_SIZE(jz_i2c3_devs);
#endif
/*
 * define gpio i2c,if you use gpio i2c,
 * please enable gpio i2c and disable i2c controller
 */
#ifdef CONFIG_I2C_GPIO
#define DEF_GPIO_I2C(NO)						\
	static struct i2c_gpio_platform_data i2c##NO##_gpio_data = {	\
		.sda_pin	= GPIO_I2C##NO##_SDA,			\
		.scl_pin	= GPIO_I2C##NO##_SCK,			\
	};								\
	struct platform_device i2c##NO##_gpio_device = {		\
		.name	= "i2c-gpio",					\
		.id	= NO,						\
		.dev	= { .platform_data = &i2c##NO##_gpio_data,},	\
	};

#ifdef CONFIG_SOFT_I2C0_GPIO_V12_JZ
DEF_GPIO_I2C(0);
#endif
#ifdef CONFIG_SOFT_I2C1_GPIO_V12_JZ
DEF_GPIO_I2C(1);
#endif
#ifdef CONFIG_SOFT_I2C2_GPIO_V12_JZ
DEF_GPIO_I2C(2);
#endif
#ifdef CONFIG_SOFT_I2C3_GPIO_V12_JZ
DEF_GPIO_I2C(3);
#endif
#endif /*CONFIG_I2C_GPIO*/