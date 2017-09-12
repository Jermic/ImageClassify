# ImageClassify

# 这是我的本科毕设的相关代码。
# 本科毕设的题目是：基于Spark的海量图片分类算法研究与实现(Research and Implementation of Massive Image Classification Algorithm Based on Spark)

# 主要分为以下两个过程实现：
## 1.提取图片特征
### 1.1 提取图片的颜色直方图特征(color histogram)
    这部分的代码实现在color-all文件夹中。是借助opencv实现的。编程语言为C++。
### 1.2 提取图片的SIFT特征
    这部分的代码实现在sift-all文件夹中。是借助opencv实现的。编程语言为C++。
### 1.3 feature fusion
    此部分用于将提取的特征进行融合。其具体实现在color-sift-all文件夹中。也是用C++实现的。
### 1.4 BOF
    此部分用于生成图片的BOF特征。此部分的实现是基于并行计算框架Spark实现的。编程语言为scala。
    生成BOF的过程中，首先需要用K-means聚类算法对提取的图片特征进行聚类，通过聚类得到视觉词汇，视觉词汇的组合即视觉词典。
    然后用得到的视觉词典来表示每一幅图片，至此，图片的BOF特征生成完成。
    具体实现在bof1文件夹和bof2文件夹中。bof1文件用于得到视觉词典，bof2文件通过使用bof1得到的视觉词典，来生成每一幅图片的BOF特征。   
## 2.图片分类 
    图片分类算法都是基于Spark的并行实现。编程语言为scala。
### 2.1 二分类
    本设计二分类是用SVM分类器实现的，利用SVM的SVMWithSGD来训练SVM分类器的模型，并用测试集来检验分类的效果。本设计二分类实现了基于颜色直方图的分类，基于图片局部SIFT特征的分类，以及多特征融合的分类。
### 2.2 多分类
    当分类所用的数据的规模很大时，SVM分类器的计算复杂度就会很高，运行时间相当长。而LR分类器具有计算代价不高，易于理解和实现的优点。因此，本设计多分类用一对其余方法实现，对每个二分类器利用Logistic回归分类器实现。
    
## 3.实验结果
<p align=center><img src="https://github.com/Lily520/ImageClassify/raw/master/img/img1.png" width="80%" height="80%" alt = "图1" align=center/></p>
<p align=center><img src="https://github.com/Lily520/ImageClassify/raw/master/img/img2.png" width="80%" height="80%" alt = "图2" align=center/></p>
<p align=center><img src="https://github.com/Lily520/ImageClassify/raw/master/img/img3.png" width="80%" height="80%" alt = "图3" align=center/></p>
<p align=center><img src="https://github.com/Lily520/ImageClassify/raw/master/img/img4.png" width="80%" height="80%" alt = "图4" align=center/></p>
<p align=center><img src="https://github.com/Lily520/ImageClassify/raw/master/img/img5.png" width="80%" height="80%" alt = "图5" align=center/></p>
