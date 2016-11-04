#include"opencv2/highgui/highgui.hpp" 
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

class HistogramND {
private:
	Mat image;//Դͼ��
	int hisSize[1], hisWidth, hisHeight;//ֱ��ͼ�Ĵ�С,��Ⱥ͸߶�
	float range[2];//ֱ��ͼȡֵ��Χ
	const float *ranges;
	Mat channelsRGB[3];//�����BGRͨ��
	MatND outputRGB[3];//���ֱ��ͼ����
public:
	HistogramND() {
		hisSize[0] = 256; //��ɫ�ռ仮�ֵ�����
		hisWidth = 400;
		hisHeight = 400;
		range[0] = 0.0;
		range[1] = 255.0;
		ranges = &range[0];
	}

	//����ͼƬ
	bool importImage(String path) {
		image = imread(path);
		if (!image.data)
			return false;
		return true;
	}

	//����ͨ��
	void splitChannels() {
		split(image, channelsRGB);
	}

	//����ֱ��ͼ
	void getHistogram(int count) {
		calcHist(&channelsRGB[0], 1, 0, Mat(), outputRGB[0], 1, hisSize, &ranges);
		calcHist(&channelsRGB[1], 1, 0, Mat(), outputRGB[1], 1, hisSize, &ranges);
		calcHist(&channelsRGB[2], 1, 0, Mat(), outputRGB[2], 1, hisSize, &ranges);

		//�������bin��ֵ
		//std::ofstream fout("C:\\VOC2010\\color.txt", ios::app);
		std::ofstream fout("C:\\Caltech\\sift_color.txt", ios::app);
		for (int i = 0; i < hisSize[0]; ++i) {
			fout << (count++) << ":" << outputRGB[0].at< float>(i) << " ";
			fout << (count++) << ":" << outputRGB[1].at< float>(i) << " ";
			fout << (count++) << ":" << outputRGB[2].at<float>(i) << " ";
		} //for
		fout << endl;
		fout.close();
	}
};

int main()
{
	initModule_nonfree(); //��ʼ��ģ�飬ʹ��SIFT��SURFʱ�õ�
	Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");//����SIFT���������
	Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create("SIFT");//������������������
	Ptr<DescriptorMatcher> descriptor_matcher = DescriptorMatcher::create("BruteForce");//��������ƥ����
	if (detector.empty() || descriptor_extractor.empty())
		cout << "fail to create detector!";

	ifstream in_out("C:\\Users\\Administrator\\Desktop\\����\\datasets\\caltech\\101.txt");
	
	string s, path;
	string  s1;
	string out,s_out;
	int len;
	int flag;

	Mat descriptors1;
	vector<KeyPoint> keypoints1;
	Mat img1;
	HistogramND hist;
	//����ͼ��
	int sum = -1;
	ifstream in;
	double t;
	ofstream fout;
	while (getline(in_out,s_out)) {
		 in.open("C:\\Users\\Administrator\\Desktop\\����\\datasets\\caltech\\" + s_out+".txt");
		sum++;
		while (getline(in, s)) {
			path = "C:\\Users\\Administrator\\Desktop\\����\\datasets\\caltech\\101_ObjectCategories\\" + s_out +"\\" + s;
			//file_path = ss;
			img1 = imread(path);
			//��������
			//t = (double)getTickCount();//��ǰ�δ���
			detector->detect(img1, keypoints1); //���img1�е�SIFT�����㣬�洢��keypoints1��

			cout << "ͼ�����������:" << keypoints1.size() << endl;

			//����������������������Ӿ��󣬼�������������
			descriptor_extractor->compute(img1, keypoints1, descriptors1);


			/*t = ((double)getTickCount() - t) / getTickFrequency();
			cout << "SIFT�㷨��ʱ��" << t << "��" << endl;
			cout << "ͼ��1�������������С��" << descriptors1.size()
				<< "����������������" << descriptors1.rows << "��ά����" << descriptors1.cols << endl;

			len = s.length();
			s1 = s.substr(0, len - 4);*/
			//std::ofstream fout("C:\\VOC2010\\" + s1 + ".txt");
			fout.open("C:\\Caltech\\sift_color.txt", ios::app);
			if (!fout.is_open())
			{
				cout << "���ļ�ʧ��" << endl;
			}

			// �������Ƿ�Ϊ��
			/*if (descriptors1.empty())
			{
				cout << "����Ϊ��" << endl;
				return 0;
			}*/
			fout << sum<<" ";
			cout << "sum:" << sum << endl;
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
			fout.close();

			if (!hist.importImage(path)) {
				cout << "Import Error!" << endl;
				return -1;
			}
			hist.splitChannels();
			hist.getHistogram(flag);
			//hist.displayHisttogram();
			waitKey(0);


		} //while
		in.close();
	}
	
	return 0;

}