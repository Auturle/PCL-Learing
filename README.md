# PCL-Learing
 something record the learing-history at PCL
 
 the first time to create a repository and do something which looks just so so.
<<<<<<< HEAD
 
 1.PCL 1.8.1在VS2017中编译遇到pop_t找不到标识符的问题的解决办法
	点击报错会进入dist.h的文件,
	根据https://github.com/mariusmuja/flann/issues/386,
	将将503行的typedef unsigned long long pop_t; 移出if end;
	我将503行的typedef unsigned long long pop_t; 移动至475行，报错消失.
=======

1.pcl1.8.1在VS2017中编译遇到“pop_t 找不到标识符”问题的解决办法:
 点击报错会进入dist.h的文件
 根据https://github.com/mariusmuja/flann/issues/386
 他们说要将将503行的typedef unsigned long long pop_t; 移出if end;
 我将503行的typedef unsigned long long pop_t; 移动至475行，报错消失
>>>>>>> 6bd5e25066f656be02b027043cbaf333f1f3eefc
