#include <darc/darc.h>
#include <darc/parameter/parameter.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace cv;
using namespace cv_bridge;

class OpenCVTestComponent : public darc::Component
{
private:
  darc::pubsub::Publisher<sensor_msgs::Image> publisher_;
  darc::timer::PeriodicTimer timer_;
  darc::parameter::Parameter<int> blur_size_;

  CvImage msg_image_;
  Mat raw_image_;
  Mat blur_image_;
  Mat canny_image_;

private:
  void timerHandler( )
  {
    blur(raw_image_, canny_image_, Size(blur_size_.getValue(), blur_size_.getValue()));
    /*
    SurfFeatureDetector detector(400);
    vector<KeyPoint> keypoints1, keypoints2;
    detector.detect(img1, keypoints1);
    detector.detect(img2, keypoints2);

    // computing descriptors
    SurfDescriptorExtractor extractor;
    Mat descriptors1, descriptors2;
    extractor.compute(img1, keypoints1, descriptors1);
    extractor.compute(img2, keypoints2, descriptors2);

    // matching descriptors
    BruteForceMatcher<L2<float> > matcher;
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    // drawing the results
    namedWindow("matches", 1);
    Mat img_matches;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
    imshow("matches", img_matches);
    waitKey(0);
    */
    msg_image_.image = blur_image_;
    publisher_.publish(msg_image_.toImageMsg());
  }

public:
  OpenCVTestComponent() :
    publisher_(this, "/myimage"),
    timer_(this, &OpenCVTestComponent::timerHandler, boost::posix_time::seconds(1)),
    blur_size_(this, "blur_size", 3)
  {
    msg_image_.encoding = "bgr8";
  }

  void onStart()
  {
    raw_image_ = imread("/home/local/darcbuild/darc_demo/opencv_test/golden-gate-bridge-3.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    if(!raw_image_.data)
    {
      DARC_FATAL("img file not found");
    }

    blur_image_.create(raw_image_.size(), raw_image_.type());
    canny_image_.create(raw_image_.size(), CV_8UC1);

    namedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", raw_image_ );                   // Show our image inside it.

  }

};

DARC_REGISTER_COMPONENT(OpenCVTestComponent)
