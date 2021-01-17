#include <opencv2/opencv.hpp>
#include <cstdio>
#include <algorithm>
#include <cmath>

#include "CellCounter.h"
#include "Defines.h"

#ifdef _WIN32
	#define isinf(x) (!_finite(x))
#endif

using namespace std;

void CellCounter::Run(const cv::Mat &img, const cv::Mat &mask, int radius_start, int radius_end, int lower, int upper, int keep_cell_size, float circle_threshold)
{
    cv::Mat grey;

    cv::cvtColor(img, grey, cv::COLOR_BGR2GRAY);

    int min_size = (int)(M_PI*radius_start*radius_start + 0.5f);
	min_size = max(1, min_size);

	bool enable_circle_check = true;

	if(circle_threshold > 5.0f) {
		enable_circle_check = false;
	}

    //printf("MIN SIZE: %d\n", min_size);

    m_centroids.clear();

    cv::Mat binary = cv::Mat::zeros(grey.size(), CV_8U);
    cv::Mat binary2;

    // Build the binary thresholded image
    for(int y=0; y < grey.rows; y++) {
        for(int x=0; x < grey.cols; x++) {
            if(mask.at<uchar>(y,x) == 0) {
                continue;
            }

            int v = grey.at<uchar>(y,x);

            if(v >= lower && v <= upper) {
                binary.at<uchar>(y,x) = 1;
            }
        }
    }

    //char str[512];
    //sprintf(str, "threshold-%d.png", t);
    //cv::imwrite(str, binary);

    // Connect blobs
    //cv::dilate(binary, binary2, cv::Mat());
    //cv::erode(binary2, binary2, cv::Mat());

    binary2 = binary;

    // Remove small blobs
    //cv::erode(binary2, binary2, cv::Mat());
    //cv::dilate(binary2, binary2, cv::Mat());
    //cv::imwrite("binary2.png", binary2);

    vector < vector<cv::Point2i> > blobs;

    FindBlobs(binary2, blobs);

    // Analyse each blob
    for(size_t b=0; b < blobs.size(); b++) {
		vector <cv::Point2i> &blob = blobs[b];

		if(keep_cell_size == 0 && (int)blob.size() < min_size) {
            continue;
        }

        // Estimate how many cells make up this blob
        int clusters = 0;

        for(int i=radius_end; i >= radius_start; i--) {
            float area = (float)(M_PI*i*i);

            int n = (int)(blob.size() / area + 0.5f);

            if(n > 0) {
                clusters = n;
                break;
            }
        }

		if((int)blob.size() <= keep_cell_size) {
			cv::Point2f avg = Avg(blob); // cv::mean doesn't work as I expected
			m_centroids.push_back(avg);
		}
		else if(clusters == 0) {
            continue;
        }
        else if(clusters == 1) {
			bool good = false;

			if(enable_circle_check) {
				if(Circleness(blob) < circle_threshold) {
					good = true;
				}
			}
			else {
				good = true;
			}

			if(good) {
				cv::Point2f avg = Avg(blob); // cv::mean doesn't work as I expected
				m_centroids.push_back(avg);
			}
        }
        else {
            cv::Mat labels, centres;

			// 3 splitting attempts
			for(int i=0; i < 3; i++) {
				vector <cv::Point2f> tenative_centroids;

                //printf("Splitting: %d %d\n", blob.size(), clusters);
				vector < vector<cv::Point2i> > split_blobs = Split(blob, clusters, labels, centres);

				for(size_t j=0; j < split_blobs.size(); j++) {
					if(split_blobs.size() == 0) {
						continue;
					}

					if((int)split_blobs[j].size() <= keep_cell_size) {
						tenative_centroids.push_back(cv::Point2f(centres.at<float>(j,0), centres.at<float>(j,1)));
					}
					else if(enable_circle_check) {
						if(Circleness(split_blobs[j]) > circle_threshold) {
							continue;
						}
					}
					else {
						tenative_centroids.push_back(cv::Point2f(centres.at<float>(j,0), centres.at<float>(j,1)));
					}
				}

				// Found at least one good cell, good enough lets get out!
				if(tenative_centroids.size()) {
					m_centroids.insert(m_centroids.end(), tenative_centroids.begin(), tenative_centroids.end());
					break;
				}

				clusters--;

				if(clusters == 0) {
					break;
				}
			}
        }
    }
}

cv::Point2f CellCounter::Avg(const vector <cv::Point2i> &data)
{
	cv::Point2i ret(0,0);

	for(size_t i=0; i < data.size(); i++) {
		ret += data[i];
	}

	return cv::Point2f((float)ret.x / data.size(), (float)ret.y / data.size());
}

float CellCounter::Circleness(std::vector <cv::Point2i> &data)
{
	cv::Mat _samples(data.size(), 2, CV_32S, &data[0]);
	cv::Mat samples;

	_samples.convertTo(samples, CV_32F);

	cv::PCA pca(samples, cv::Mat(), cv::PCA::DATA_AS_ROW, 0);

	float ratio = sqrt(pca.eigenvalues.at<float>(0)) / sqrt(pca.eigenvalues.at<float>(1));

	if(isinf(ratio)) {
		return FLT_MAX;
	}

	return ratio;
}

vector < vector <cv::Point2i> > CellCounter::Split(std::vector <cv::Point2i> &blob, int clusters, cv::Mat &labels, cv::Mat &centres)
{
    // Use K-Means to split the blob
    cv::Mat samples;
    cv::TermCriteria termcrit = cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 1000, 0.1);

    cv::Mat _samples(blob.size(), 2, CV_32S, &blob[0]);
    _samples.convertTo(samples, CV_32F);

    cv::kmeans(samples, clusters, labels, termcrit, 1, cv::KMEANS_RANDOM_CENTERS, centres);

	vector < vector <cv::Point2i> > ret;

    for(int c=0; c < clusters; c++) {
        vector <cv::Point2i> sub_blob;

        for(int j=0; j < labels.rows; j++) {
            if(labels.at<int>(j,0) == c) {
                sub_blob.push_back(blob[j]);
            }
        }

		ret.push_back(sub_blob);
    }

	return ret;
}

void CellCounter::FindBlobs(const cv::Mat &binary, vector < vector<cv::Point2i> > &blobs)
{
    blobs.clear();

    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground

    cv::Mat label_image;
    binary.convertTo(label_image, CV_32FC1); // weird it doesn't support CV_32S!

    int label_count = 2; // starts at 2 because 0,1 are used already

    for(int y=0; y < binary.rows; y++) {
        for(int x=0; x < binary.cols; x++) {
            if((int)label_image.at<float>(y,x) != 1) {
                continue;
            }

            cv::Rect rect;
            cv::floodFill(label_image, cv::Point(x,y), cv::Scalar(label_count), &rect, cv::Scalar(0), cv::Scalar(0), 4);

            vector <cv::Point2i> blob;

            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if((int)label_image.at<float>(i,j) != label_count) {
                        continue;
                    }

                    blob.push_back(cv::Point2i(j,i));
                }
            }

            blobs.push_back(blob);

            label_count++;
        }
    }
}

std::vector <cv::Point2f> &CellCounter::GetResults()
{
    return m_centroids;
}
