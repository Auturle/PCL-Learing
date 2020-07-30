# PCL-Learing
 something record the learing-history at PCL
 
 the first time to create a repository and do something which looks just so so.
<<<<<<< HEAD

1.pcl1.8.1在VS2017中编译遇到“pop_t 找不到标识符”问题的解决办法:
 点击报错会进入dist.h的文件
 根据https://github.com/mariusmuja/flann/issues/386
 他们说要将将503行的typedef unsigned long long pop_t; 移出if end;
 我将503行的typedef unsigned long long pop_t; 移动至475行，报错消失
 
 2.VTK编译出现no override found for 'vtkPolyDataMapper'
	这种问题是因为没有用cmake，而是直接用控制台结合VTK的库函数进行开发的。
	下面是其中一个解决方式：
	#include "vtkAutoInit.h" 
	VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
	VTK_MODULE_INIT(vtkInteractionStyle);

