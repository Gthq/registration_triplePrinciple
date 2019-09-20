#pragma once

#include "typeDef.h"
#include <utility>����//pair��ͷ�ļ�
#include "recognition.h"

static enum VFH_method{VFH, CVFH};

extern "C"
{
	bool compareScore(std::pair<float, int> pair1, std::pair<float, int> pair2);
	//��ȡ�ļ���
	bool computePairNum(std::pair<double, std::string> pair1, 
		std::pair<double, std::string> pair2);
	void sort_filelists(std::vector<std::string>& filists);//�ļ�������
	void getFiles(std::string path, std::string ext, std::vector<std::string>& files);

	//������
	void computeMean(PointCloudPtr pointInput, Eigen::Vector3f &mean);
	//�����ļ���ȥ����
	void remove_Mean(PointCloudPtr point, Eigen::Vector3f& mean);
	//��ȥ���ĵ�Э������󲢹�һ��
	void computeCovarianceMatrixNormalized(PointCloudPtr pointInput,
		Eigen::Vector3f& centroid,
		Eigen::Matrix3f& covariance);
	//��һ��
	void normalizePoints(PointCloudPtr pointCloud, Eigen::Vector3f& mean,
		float global_scale);
	//����ֱ���
	float computeResolution(PointCloudPtr cloud);

	//������ȥ��NAN��
	void removeNANfromNormal(FeatureCloud &cloud);
	//FPFHȥ��NAN��
	void removeNANfromFPFH(FPFH_features::Ptr feature_descriptor,
		FPFH_features::Ptr nanremoved,
		FeatureCloud& cloud);
	//SHOTȥ��NAN��
	void removeNANfromSHOT(SHOT_features::Ptr feature_descriptor,
		SHOT_features::Ptr nanremoved,
		FeatureCloud& cloud);
	//�����˲�
	void VoxelGrid_Filter(PointCloudPtr input,
		PointCloudPtr output,
		float leafsize = 1.0);
	//����ͳ��ѧ�˲�
	void StatisticalOutlierRemoval_Filter(PointCloudPtr input,
		PointCloudPtr output,
		int K = 30,
		float stddevMulThresh = 1.0);
	//�����˲�
	void Uniform_Filter(PointCloudPtr input,
		PointCloudPtr output,
		float uniform_Radius = 1.0);
	//ֱͨ�˲�
	void PassThrough_Filter(PointCloudPtr input,
		PointCloudPtr output,
		std::string axis,
		float upBound,
		float downBound,
		bool negative);

	//����������
	void computeSurfaceNormals(FeatureCloud& cloud,
		int K = 50,
		float radius = 0,
		int numofthreads = 4);

	//��������������
	void construct_PointNormal(FeatureCloud& targetCloud,
		FeatureCloud& sourceCloud);

	//SHOT����
	void computeFeatures_SHOT(FeatureCloud &cloud, 
		float R);
	//FPFH����
	void computeFeatures_FPFH(FeatureCloud &cloud,
		float R);
	//�ֲ��ο�����ϵLRF
	void computeFeatures_LRF(FeatureCloud &cloud,
		float rf_radius = 5.0);
	//VFHȫ������������
	void computeFeatures_VFH(FeatureCloud &cloud, VFH_method method);

	void keyPoints_NARF(const PointCloudPtr cloud_src,
		const PointCloudPtr keyPoints_NARF,
		float angular_resolution ,
		float support_size );

	//Harris�ؼ���
	void keyPoints_HARRIS(PointCloudPtr cloud_src,
		 PointCloudPtr keyPoints_Harris,
		float radius = 0.03f,
		float threshold = 0.05f);

	//kdTree���������(PointT)
	void getNearestIndices(const PointCloudPtr cloudIn,
		const PointCloudPtr cloudQuery,
		PointCloudPtr cloudResult,
		pcl::PointIndices::Ptr indicesPtr);

	//kdTree���������(SHOT)
	void getNearestIndices_SHOT(const SHOT_features::Ptr cloudIn,
		const SHOT_features::Ptr cloudQuery,
		pcl::CorrespondencesPtr corrPtr);

	//��Ӧ��Թ���
	void correspondence_estimation(std::string kernel_descriptors,
		FPFH_features::Ptr source_cloud,
		FPFH_features::Ptr target_cloud,
		pcl::Correspondences &all_corres);

	//��Ӧ����޳��� �� �� �� Ӧ ��
	void correspondences_rejection(FeatureCloud &source_cloud,
		FeatureCloud &target_cloud,
		pcl::Correspondences &correspondences,
		pcl::Correspondences &inliers,
		int MaximumIterations, float Inlierthreshold);
	//��Ӧ����޳��� �Զ���Լ����
	// tupleScale	  0.95	// Similarity measure used for tuples of feature points.
	// tuple_max_cnt_   1000	// Maximum tuple numbers.
	void advancedMatching(PointCloudPtr target, PointCloudPtr source, 
		pcl::Correspondences &correspondences,
		pcl::Correspondences &inliers,
		float tupleScale,
		int tuple_max_cnt_);
	//��ȡ��ȥ�������ĵ���
	void extractIndicesPoints(PointCloudPtr pointInput,
		PointCloudPtr pointOutput,
		pcl::PointIndices::Ptr inliers,
		bool extractNegative);

	// ����RANSAC����״��ȡ
	bool SACSegmentation_model(PointCloudPtr pointInput,
							pcl::ModelCoefficients::Ptr coefficients,
							pcl::PointIndices::Ptr inliers,
							pcl::SacModel modeltype = pcl::SACMODEL_PLANE,
							int maxIteration = 100,
							float distancethreshold = 1.0);
	//����SAC�Ĵ�ֱƽ���⡢��ȡ��ɾ��
	bool SACSegmentation_plane(PointCloudPtr pointInput,
		pcl::ModelCoefficients::Ptr coefficients,
		pcl::PointIndices::Ptr inliers,
		int maxIteration = 100,
		float distancethreshold = 1.0
		);
	// ��С��Χ��
	void OrientedBoundingBox(PointCloudPtr pointInput,
		Eigen::Vector3f &whd,
		Eigen::Vector3f &bboxT,
		Eigen::Quaternionf &bboxQ,
		float scalar,
		PointT& pcX, PointT& pcY, PointT& pcZ, PointT& initialoriginalPoint);

	//����ŷ�Ͼ���ľ���
	void EuclideanClusterExtraction(PointCloudPtr pointInput,
		std::vector<PointCloudPtr>& cloudListOutput,
		float clusterTolerance = 0.02,
		int minClusterSize = 100,
		int maxClusterSize = 1000);
	//�������������ľ���
	void RegionGrowingClusterExtraction(PointCloudPtr pointInput,
		std::vector<PointCloudPtr>& cloudListOutput,
		SurfaceNormals::Ptr normalInput,
		int minClusterSize,
		int maxClusterSize,
		int numofNeighbour = 30,
		float smoothThreshold = 3.0 / 180.0 * M_PI,
		float curvatureThreshold = 1.0);

	/*****��׼***/
	//SAC-IA
	void SAC_IA_Transform(FeatureCloud &source_cloud, 
		FeatureCloud &target_cloud,
		float minsampleDistance,
		int numofSample,
		int correspondenceRandomness,
		Eigen::Matrix4f& final_transformation);
	//ICP
	float iterative_closest_points(std::string solver,
		bool flag_reciprocal, bool flag_ransac,
		FeatureCloud &source_cloud, FeatureCloud &target_cloud,
		float transEps, float corresDist, float EuclFitEps, float outlThresh,int maxIteration,
		Eigen::Matrix4f &final_transformation);

	//SVD�任
	void SVD_Transform(PointCloudPtr target,
					PointCloudPtr source,
					Eigen::Matrix4f &transformation_SVD,
					int numOfIteration,
					 float threshold);
	//FGR�任
	void FGR_Transform(PointCloudPtr target,
		PointCloudPtr source,
		Eigen::Matrix4f &transformation_SVD,
		int numOfIteration,
		float threshold);
	//SACPrerejective�任
	void SAC_Transform(PointCloudNormal::Ptr target,
		PointCloudNormal::Ptr source,
		FPFH_features::Ptr fpfh_tgt,
		FPFH_features::Ptr fpfh_src,
		int maxIteration,
		float maxCorrDist,
		float inlierFration,
		Eigen::Matrix4f& final_transformation);


	//����ת������
	bool RotationTranslationCompute(FeatureCloud& cloudtarget,
		FeatureCloud& cloudsource,
		Eigen::Matrix4f &tranResult);

	//����Hough3DGrouping�ľ���ʶ�����׼
	void Hough3DGrouping_recognize(PointCloudPtr modelPointInput,
		PointCloudPtr scenePointInput,
		pcl::CorrespondencesPtr model_scene_corrs,
		pcl::PointCloud<LRFType>::Ptr modelRF,
		pcl::PointCloud<LRFType>::Ptr sceneRF,
		std::vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f>> & rototranslation,
		std::vector<pcl::Correspondences>& clustered_corr,
		float BinSize = 2.0,
		float cg_thresh_ = 5.0,
		float rf_radius = 5.0,
		bool interpolation = true,
		bool distanceWeight = false);

	//���ڼ���һ���Ծ���
	void GeometricConsistencyGrouping(float GCsize,
		float GCthreshold,
		PointCloudPtr modelPointInput,
		PointCloudPtr scenePointInput,
		pcl::CorrespondencesPtr model_scene_corrs,
		std::vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f>> & rototranslation,
		std::vector<pcl::Correspondences>& clustered_corr);

	//��ʾ���ƶ�Ӧ���
	void showPointCloudCorrespondences(std::string viewerName,
		PointCloudPtr cloudTarget_,
		PointCloudPtr cloudSource_,
		pcl::Correspondences &corr_, int showThreshold = 1);
	
}
