//By Cannian
//2017-4-17 by Ql.Liu
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "readBMP.h"
//读取BMP的库
#include "autofocus.h"
//自动对焦的库
#include <iostream>

int main(void){
	Image image;
	Image *imagepointer = &image;
	int ROI_x, ROI_y, ROI_width, ROI_height;//设定ROI
	char filename[10][10] = { "1.bmp",
		"2.bmp",
		"3.bmp",
		"4.bmp",
		"5.bmp",
		"6.bmp",
		"7.bmp",
		"8.bmp",
		"9.bmp",
		"10.bmp"
        };
	struct roidefine ez;
	if (ImageLoad(filename[0], imagepointer)){
		int **greyimage = (int **)malloc(imagepointer->sizeY*sizeof(int *));
		struct roidefine ro;
                // 暂时找"haqu"为对焦区域(1006,375),(1128,513)
		ro.roi_x = 1006;
		ro.roi_y = 375;
                // 要找准对焦区域，200会误判，300程序无响应
		ro.roi_height = 122;
		ro.roi_width = 138;
		int b = get_region_contrast(imagepointer->greydata, ro);
		unsigned char *z = (imagepointer->data);
		//ez = get_roi_region(imagepointer->greydata);
		ez = ro;
		printf("%d %d\n", ez.roi_x,ez.roi_y);
	}
	//载入图像并自动选择对焦区域

	int frame_loc=0;
	for (frame_loc = 0; frame_loc <10; ++frame_loc){
		if (ImageLoad(filename[frame_loc], imagepointer)){
			int **greyimage = (int **)malloc(imagepointer->sizeY*sizeof(int *));
			struct roidefine ro;
			int b = get_region_contrast(imagepointer->greydata, ez);
			unsigned char *z = (imagepointer->data);
			printf("%s %d\n", filename[frame_loc],b);
		}
	}
	//根据上面选择的对焦区域进行对焦值计算
	
        sleep(1);
	return 0;
}
