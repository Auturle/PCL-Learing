#pragma once
#ifndef TESTEXAMPLE_H

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/bilateral.h>
#include <pcl/visualization/cloud_viewer.h>

typedef pcl::PointXYZI PointT;	//exmaple1 use

int user_data;	//	example2 use

//example1

int example1(int argc, char*argv[])
{
	std::string incloudfile = argv[1];
	std::string outcloudfile = argv[2];
	float sigma_s = atof(argv[3]);
	float sigma_r = atof(argv[4]);

	// 读入点云文件
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile(incloudfile.c_str(), *cloud);

	pcl::PointCloud<PointT>outcloud;

	// 建立kdtree
	pcl::KdTreeFLANN<PointT>::Ptr tree(new pcl::KdTreeFLANN<PointT>);

	pcl::BilateralFilter<PointT> bf;
	bf.setInputCloud(cloud);
	//bf.setSearchMethod(tree);
	bf.setHalfSize(sigma_s);
	bf.setStdDev(sigma_r);
	bf.filter(outcloud);

	// 保存滤波输出点云文件
	pcl::io::savePCDFile(outcloudfile.c_str(), outcloud);
	return (0);
}


//example2

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
	viewer.setBackgroundColor(1.0, 0.5, 1.0);
	pcl::PointXYZ o;
	o.x = 1.0;
	o.y = 0;
	o.z = 0;
	viewer.addSphere(o, 0.25, "sphere", 0);
	std::cout << "i only run once" << std::endl;

}

void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
	static unsigned count = 0;
	std::stringstream ss;
	ss << "Once per viewer loop: " << count++;
	viewer.removeShape("text", 0);
	viewer.addText(ss.str(), 200, 300, "text", 0);

	//FIXME: possible race condition here:
	user_data++;
}

void example2()
{
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
	pcl::io::loadPCDFile("my_point_cloud.pcd", *cloud);

	pcl::visualization::CloudViewer viewer("Cloud Viewer");



	//blocks until the cloud is actually rendered
	viewer.showCloud(cloud);

	//use the following functions to get access to the underlying more advanced/powerful
	//PCLVisualizer

	//This will only get called once
	viewer.runOnVisualizationThreadOnce(viewerOneOff);

	//This will get called once per visualization iteration
	viewer.runOnVisualizationThread(viewerPsycho);
	while (!viewer.wasStopped())
	{
		//you can also do cool processing here
		//FIXME: Note that this is running in a separate thread from viewerPsycho
		//and you should guard against race conditions yourself...
		user_data++;
	}

}

//example3
int ioTest(int argc, char **argv)
{
	//创建一个PointCloud<pcl::PointXYZ> boost共享指针并进行实例化
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

	//打开文件
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("test_pcd.pcd", *cloud) == -1)
	{
	PCL:ERROR("could'n open file test_pcd.pcd\n");
		return -1;
	}

	std::cout << "loaded" << endl;
	std::cout << cloud->width * cloud->height << "data points from test_pcd.pcd" << endl;
	std::cout << "with the following fields:" << endl;
	for (size_t i = 0; i < cloud->points.size(); i++)
	{
		std::cout << cloud->points[i].x << "	" << cloud->points[i].y << "	" << cloud->points[i].z << endl;
	}
	return 0;
}


#endif // !TESTEXAMPLE_H

