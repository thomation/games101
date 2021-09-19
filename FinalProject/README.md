# GAMES101 大作业 BSSRDF
## 代码结构
* 使用作业6的框架，单模型，点光源，蒙特卡洛方法，omp并行
* BSSRDF渲染在Scene::computeSubsurfaceScattering实现
* * 首先Sample po周围的一个点pi
* * 如果sample成功，且该点能被光照到，计算次表面S
* * 否则计算, 按照作业6的Phone模型计算
* 次表面公式代码封装在S函数中
* 使用Normalized Diffusion计算reflectance profile，代码在Rd函数中
* 使用投射采样法采样点pi
* * 首先确定一个圆球最大半径Rm，然后在[0,Rm]中采样一个r
* * 在po点所在切平面上，以po为圆心，r为半径的圆弧上采样一个点p, 将p投射到模型表面，获取po点
* * 实现了两个重要性采样方式来计算po点的pdf
* * * 通过预计算CDF，实现Inverse Sampling。代码在samplePointPreCompute
* * * Normalized Diffusion拆分成有解析解两项，实现MIS。代码在samplePointMis
## 辅助工具
* material.xlsx 计算材质的ld
* cdf.py 预计算Normalized Diffusion的cdf的逆, 需要安装scipy库
## 报告 
* report.pptx
* 视频地址：
## 参考文献
* https://graphics.stanford.edu/papers/bssrdf/bssrdf.pdf
* https://graphics.pixar.com/library/ApproxBSSRDF/paper.pdf
* http://library.imageworks.com/pdfs/imageworks-library-BSSRDF-sampling.pdf
* https://zhuanlan.zhihu.com/p/21247702
* http://shihchinw.github.io/2015/10/bssrdf-importance-sampling-of-normalized-diffusion.html
* https://gao-duan.github.io/blogs/bssrdf/index.html
* https://blog.csdn.net/Dark_Scope/article/details/70992266
