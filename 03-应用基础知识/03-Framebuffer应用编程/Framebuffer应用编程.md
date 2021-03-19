1. LCD操作原理
- 在Linux系统中通过Framebuffer驱动程序来控制LCD。Frame是帧的意思，buffer是缓冲的意思，这意味着Framebuffer就是一块内存，里面保存着一帧图像。Framebuffer中保存着一帧图像的每一个像素颜色值，假设LCD的分辨率是1024x768，每一个像素的颜色用32位来表示，那么Framebuffer的大小就是：1024x768x32/8=3145728字节。
- LCD操作原理
    - ① 驱动程序设置好LCD控制器：
        根据LCD的参数设置LCD控制器的时序、信号极性；
        根据LCD分辨率、BPP分配Framebuffer。
    - ② APP使用ioctl获得LCD分辨率、BPP
    - ③ APP通过mmap映射Framebuffer，在Framebuffer中写入数据
![Alt]((https://img-blog.csdnimg.cn/20210319191920490.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hcGxlTGVhZl85,size_16,color_FFFFFF,t_70)
- 假设需要设置LCD中坐标(x,y)处像素的颜色，首要要找到这个像素对应的内存，然后根据它的BPP值设置颜色。假设fb_base是APP执行mmap后得到的Framebuffer地址，如下图所示：
![Alt](https://img-blog.csdnimg.cn/20210319192217606.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hcGxlTGVhZl85,size_16,color_FFFFFF,t_70)
- 可以用以下公式算出(x,y)坐标处像素对应的Framebuffer地址：
    ```
    (x，y)像素起始地址=fb_base+(xres*bpp/8)*y + x*bpp/8
    ```
- 像素的颜色是用RGB三原色(红、绿、蓝)来表示的，在不同的BPP格式中，用不同的位来分别表示R、G、B。
    - 对于32BPP，一般只设置其中的低24位，高8位表示透明度，一般的LCD都不支持。
    - 对于24BPP，硬件上为了方便处理，在Framebuffer中也是用32位来表示，效果跟32BPP是一样的。
    - 对于16BPP，常用的是RGB565；很少的场合会用到RGB555，这可以通过ioctl读取驱动程序中的RGB位偏移来确定使用哪一种格式。
    ![Alt](https://img-blog.csdnimg.cn/20210319192502315.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hcGxlTGVhZl85,size_16,color_FFFFFF,t_70)
## 注释：
- bpp:bits per pixel(每个像素用多少位来表示它的颜色)
- xres:X轴方向的分辨率(分辨率指显示器所能显示的像素有多少)

