#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/nonfree/nonfree.hpp"  
#include "opencv2/nonfree/features2d.hpp"  
#include <iostream>  
#include<fstream>
#include<iomanip>
#include <stdio.h>  
#include <stdlib.h>  
#include<string>

using namespace cv;
using namespace std;

int main()
{
	initModule_nonfree(); //��ʼ��ģ�飬ʹ��SIFT��SURFʱ�õ� 
	Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");//����SIFT��������� 
	Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create("SIFT");//������������������ 
	Ptr<DescriptorMatcher> descriptor_matcher = DescriptorMatcher::create("BruteForce");//��������ƥ���� 
	if (detector.empty() || descriptor_extractor.empty())
		cout << "fail to create detector!";

	ifstream in("C:\\Users\\Administrator\\Desktop\\����\\datasets\\caltech\\101_ObjectCategories\\anchor.txt");
	string s;
	string ss, s1;
	int len;
	int flag;

	Mat descriptors1;
	vector<KeyPoint> keypoints1;
	Mat img1;
	//����ͼ�� 
	while (getline(in, s)) {
		ss = "C:\\Users\\Administrator\\Desktop\\����\\datasets\\caltech\\101_ObjectCategories\\anchor\\" + s;
		//file_path = ss;
		img1 = imread(ss);
		//�������� 
		double t = (double)getTickCount();//��ǰ�δ��� 
		detector->detect(img1, keypoints1); //���img1�е�SIFT�����㣬�洢��keypoints1�� 

		cout << "ͼ��1���������:" << keypoints1.size() << endl;

		//����������������������Ӿ��󣬼������������� 
		descriptor_extractor->compute(img1, keypoints1, descriptors1);

		t = ((double)getTickCount() - t) / getTickFrequency();
		cout << "SIFT�㷨��ʱ��" << t << "��" << endl;


		cout << "ͼ��1�������������С��" << descriptors1.size()
			<< "����������������" << descriptors1.rows << "��ά����" << descriptors1.cols << endl;

		len = s.length();
		s1 = s.substr(0, len - 4);
		//std::ofstream fout("C:\\VOC2010\\" + s1 + ".txt");
		std::ofstream fout("C:\\VOC2010\\sift.txt",ios::app);
		if (!fout.is_open())
		{
			cout << "���ļ�ʧ��" << endl;
		}

		// �������Ƿ�Ϊ�� 
		if (descriptors1.empty())
		{
			cout << "����Ϊ��" << endl;
			return 0;
		}
		fout << "0 ";
		flag = 1;
		for (int r = 0; r < descriptors1.rows; r++)
		{
			for (int c = 0; c < descriptors1.cols; c++)
			{
				float data = descriptors1.at<float >(r, c);  //��ȡ���ݣ�at<type> - type �Ǿ���Ԫ�صľ������ݸ�ʽ 
				if (data != 0)
					fout << (flag++) << ":" << data << " ";   //ÿ�������ÿո���� 
				else
					flag++;
			}
			
		}
		fout << endl;  //���� 
		fout.close();
		
	}//while
	in.close();
	return 0;

}
