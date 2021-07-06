# simplest_h264_analyzer
20210705
1、学习yinwenjie第五章：H.264码流结构 “实践：从码流中读取NAL Unit的方法”和“实践：从码流中读取NAL Unit的方法”，新建demo FindNALContent工程；
2、学习yinwenjie第六章：NAL Unit解析“H.264码流分析器SimpleH264Analyzer工程创建”，新建了simplest_h264_analyzer工程框架；


20210706
1、学习yinwenjie第六章：NAL Unit解析，第三节："SimpleH264Analyzer解析码流为NAL Unit"；
2、学习yinwenjie第六章：NAL Unit解析，第四节："SimpleH264Analyzer中实现对NAL Unit分析"；
3、更新代码，对NALU的头信息进行解析，主要是nal_unit_type语法元素；
4、更新代码，去除"防止竞争校验字节0x03"，简称"去壳操作"，完成ebsp -> rbsp的操作；
5、对spec进行了一点注释；
6、demo文件夹里的"FindNALContent"工程的注释；
