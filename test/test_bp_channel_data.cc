#include "bitplanes/core/internal/bitplanes_channel_data.h"
#include "bitplanes/core/homography.h"
#include "bitplanes/utils/timer.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <fstream>

int main()
{
  cv::Mat I = cv::imread("/home/halismai/lena.png", cv::IMREAD_GRAYSCALE);
  cv::Rect roi(80, 50, 320, 240);

  bp::BitPlanesChannelData<bp::Homography> cdata;

  cdata.set(I, roi);

  auto t_ms = bp::TimeCode(10, [&]() { cdata.set(I,roi); });
  printf("time %0.2f ms\n", t_ms);

  cv::Mat I1;
  I(roi).copyTo(I1);

  typename bp::BitPlanesChannelData<bp::Homography>::Pixels residuals;
  cdata.computeResiduals(I1, residuals);
  /*
  {
    std::ofstream ofs("E");
    ofs << residuals;
    ofs.close();
  }
  */

  printf("ERROR: %f\n", residuals.template lpNorm<Eigen::Infinity>());
  printf("ERROR: %f\n", residuals.norm());

  return 0;

  t_ms = bp::TimeCode(100, [&]() { cdata.computeResiduals(I1, residuals); });
  printf("time %0.2f ms\n", t_ms);

  return 0;
}

