#ifndef __CELLCOUNTER_H__
#define __CELLCOUNTER_H__

#include <opencv2/core/core.hpp>
#include <vector>

class CellCounter
{
public:
    void Run(const cv::Mat &img, int radius_start, int radius_end, int lower, int upper, int keep_cell_size, float circle_threshold);
    std::vector <cv::Point2f> &GetResults();

private:
    void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
    std::vector < std::vector <cv::Point2i> > Split(std::vector <cv::Point2i> &blob, int clusters, cv::Mat &labels, cv::Mat &centres);
	cv::Point2f Avg(const std::vector <cv::Point2i> &data);
	float Circleness(std::vector <cv::Point2i> &data);

private:
    std::vector <cv::Point2f> m_centroids;
};

#endif
