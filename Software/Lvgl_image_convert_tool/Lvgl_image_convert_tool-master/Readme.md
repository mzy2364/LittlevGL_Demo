2019-11-20：

增加了对转换操作结果的验证，避免了转换图片时界面卡死的问题

添加了原php环境下的内存限制设置参数

对于转换提示的问题：

1.在转换图片时，提示转换成功，但找不到转换后的文件

    原因：图片分辨率过大，修改php环境内存限制参数
		
  	解决办法：修改转换工具根目录下php.ini配置文件 
```php
memory_limit = _xxx_M	//	_xxx_ 根据实际使用修改该值，图片分辨率越大，需要设置的值就越大
```

2.在转换图片时，提示转换失败
		
    原因1：图片分辨率过大，转换时间太长（这么大的图片……），超时了
    原因2：图片资源编码问题，测试发现截屏保存的图片不能直接转换，否则转换失败，先使用图片编辑工具打开，然后另存就可以了
  
 目前发现以上问题

2019-11-16:

## 界面如下
设置输出文件类型，c测试没问题，bin格式没用到，如果有用到的朋友欢迎反馈

![设置输出文件类型](https://whycan.cn/files/members/1913/1573874174(1).png)

转换方式跟官方网页一样

![设置图片转换方式](https://whycan.cn/files/members/1913/1573812405(1)_20191116-1119.png)

lv_img_dsc_t，为生成的c文件下该图片资源的名字


2019-11-15：

## 说明

软件为基于LVGL离线版图片转换封装的小工具，避免了常使用界面工具的朋友操作控制台指令的不便利

运行环境为windows

修改了原官方离线版php文件接口，便于保存到指定目录

避免计算机没有php环境，在工具所在目录配置了一个php小环境（人懒，php不懂瞎裁）



## 初衷

手头项目用到lvgl做界面设计，前期在lvgl官网做图片转换，感觉挺好 但界面嘛，美观度重口难调，所以这周把界面元素重设计了一遍， 然后昨天在官网做转换时，下载n次失败……所以就有了这个基于官方离线版封装的转换工具，有问题可以通过软件界面的qq和邮箱联系我

## 后续

如果后面有时间或者用到的话，加一个批量转换的。。。这个先用吧