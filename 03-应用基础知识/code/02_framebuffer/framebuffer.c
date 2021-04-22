#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>

#include <sys/ioctl.h>

#include <string.h>

#include <linux/fb.h>

static int fd_fb; /* 文件描述符 */
static struct fb_var_screeninfo var; /* fb可变参数 */
static int screen_size; /* lcd屏尺寸 */
static unsigned char *fb_base; /* mmap返回lcd的初始地址 */
static unsigned int line_width;
static unsigned int pixel_width;

/**********************************************************************
 * 函数名称： lcd_put_pixel
 * 功能描述： 在LCD指定位置上输出指定颜色（描点）
 * 输入参数： x坐标，y坐标，颜色
 * 输出参数： 无
 * 返 回 值： 会
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 
 ***********************************************************************/ 

void lcd_put_pixel(int x, int y, unsigned int color)
{
    unsigned char *pen_8 = fb_base + y*line_width + x*pixel_width;
    unsigned short *pen_16;
    unsigned int *pen_32;

    unsigned int red, green, blue;

    pen_16 = (unsigned short *)pen_8;
    pen_32 = (unsigned int *)pen_8;

    /* bits_per_pixel及每个像素用多少位来表示它的颜色 */
    switch(var.bits_per_pixel)
    {
        case 8:
        {
            *pen_8 = color;
            break;
        }
        case 16:
        {
            /* bits_per_pixel格式为565时 */
            red = (color >> 16) & 0xFF;
            green = (color >> 8) & 0xFF;
            blue = (color >> 0) & 0xFF;
            color = ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
            *pen_16 = color;
            break;
        }
        case 32:
        {
            *pen_32 = color;
            break;
        }
        default:
        {
            printf("can't suport %dbpp\n", var.bits_per_pixel);
            break;
        }
    }
}

int main(int argc, char **argv)
{
    int i;

    fd_fb = open("/dev/fb0", O_RDWR);
    if (-1 == fd_fb)
    {
        printf("can't open /dev/fb0\n");
        _exit(-1);  
    }
    /* ioctol返回值成功为0，失败为一负值 */
    if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
    {
        printf("can't get var\n");
        _exit(-1);
    }

    line_width = var.xres * var.bits_per_pixel / 8;
    pixel_width = var.bits_per_pixel / 8;
    screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
    fb_base = (unsigned char *)mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
    if (fb_base == (unsigned char *)-1)
    {
        printf("can't mmap\n");
        _exit(-1);
    }

    /* 清屏，将lcd屏设为白色 */
    memset(fb_base, 0xFF, screen_size);

    /* 在lcd屏中间画红线 */
    for (i = 0; i < 100; i++)
    {
        lcd_put_pixel(var.xres / 2 + i, var.yres / 2, 0XFF0000);
    }

    /* 解除内存映射 */
    munmap(fb_base, screen_size);
    close(fd_fb);

    _exit(0);
}
