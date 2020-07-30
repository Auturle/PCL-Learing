#pragma once
#ifndef TESTEXAMPLE_H
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/bilateral.h>
#include <pcl/visualization/cloud_viewer.h>

typedef pcl::PointXYZI PointT;	//exmaple1 use

int user_data;	//	example2 use

//example1	
//��������1����������������������ʱ�򱨲������ʹ��󣬺����ٽ��

int example1(int argc, char*argv[])
{
	std::string incloudfile = argv[1];
	std::string outcloudfile = argv[2];
	float sigma_s = atof(argv[3]);
	float sigma_r = atof(argv[4]);

	// ��������ļ�
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile(incloudfile.c_str(), *cloud);

	pcl::PointCloud<PointT>outcloud;

	// ����kdtree
	pcl::KdTreeFLANN<PointT>::Ptr tree(new pcl::KdTreeFLANN<PointT>);

	pcl::BilateralFilter<PointT> bf;
	bf.setInputCloud(cloud);
	//bf.setSearchMethod(tree);
	bf.setHalfSize(sigma_s);
	bf.setStdDev(sigma_r);
	bf.filter(outcloud);

	// �����˲���������ļ�
	pcl::io::savePCDFile(outcloudfile.c_str(), outcloud);
	return (0);
}


//example2 
//��װ��������

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
//��pcd�ļ���ȡ����

int ioFromPcd(int argc, char **argv)
{
	//����һ��PointCloud<pcl::PointXYZ> boost����ָ�벢����ʵ����
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

	//���ļ�
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

//example4
//��txt�ļ���ȡ���ݣ�����ʾ����
void ioFromTxt()
{
	typedef struct tagPOINT_3D
	{
		double x;  //mm world coordinate x  
		double y;  //mm world coordinate y  
		double z;  //mm world coordinate z  
		double r;
	}POINT_WORLD;


	//����txt����  
	int number_Txt;
	FILE *fp_txt;
	tagPOINT_3D TxtPoint;
	vector<tagPOINT_3D> m_vTxtPoints;
	fp_txt = fopen("testData.txt", "r");
	if (fp_txt)
	{
		while (fscanf(fp_txt, "%lf %lf %lf", &TxtPoint.x, &TxtPoint.y, &TxtPoint.z) != EOF)
		{
			m_vTxtPoints.push_back(TxtPoint);
		}
	}
	else
		cout << "txt���ݼ���ʧ�ܣ�" << endl;
	number_Txt = m_vTxtPoints.size();
	//pcl::PointCloud<pcl::PointXYZ> cloud;
	//����ʹ�á�PointXYZ������Ϊ�Һ�����ĵ�����Ϣ�ǰ�������ά���꣬ͬʱ���е�����Ϣ������rgb��ɫ��Ϣ�Ļ��߻��а���rgba��ɫ��ǿ����Ϣ��
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	// Fill in the cloud data  
	cloud->width = number_Txt;
	cloud->height = 1;
	cloud->is_dense = false;
	cloud->points.resize(cloud->width * cloud->height);
	for (size_t i = 0; i < cloud->points.size(); ++i)
	{
		cloud->points[i].x = m_vTxtPoints[i].x;
		cloud->points[i].y = m_vTxtPoints[i].y;
		cloud->points[i].z = m_vTxtPoints[i].z;
	}
	pcl::io::savePCDFileASCII("txt2pcd_bunny1.pcd", *cloud);
	std::cerr << "Saved " << cloud->points.size() << " data points to txt2pcd.pcd." << std::endl;

	//for (size_t i = 0; i < cloud.points.size(); ++i)
	//  std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;

	//PCL Visualizer
	// Viewer  
	pcl::visualization::PCLVisualizer viewer("Cloud Viewer");
	viewer.addPointCloud(cloud);
	viewer.setBackgroundColor(0, 0, 0);

	viewer.spin();
}

#endif // !TESTEXAMPLE_H

