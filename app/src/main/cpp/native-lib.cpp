#include <jni.h>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

extern "C"
{
void JNICALL Java_ch_hepia_iti_opencvnativeandroidstudio_MainActivity_processPanorama(
        JNIEnv * env, jclass clazz, jlongArray imageAddressArray, jlong outputAddress) {

    Stitcher::Mode mode = Stitcher::PANORAMA;

    // Get the length of the long array
    jsize a_len = env->GetArrayLength(imageAddressArray);
    // Convert the jlongArray to an array of jlong
    jlong *imgAddressArr = env->GetLongArrayElements(imageAddressArray,0);
    // Create a vector to store all the image
    vector< Mat > imgVec;
    for(int k=0;k<a_len;k++)
    {
        // Get the image
        Mat & curimage=*(Mat*)imgAddressArr[k];
        Mat newimage;
        // Convert to a 3 channel Mat to use with Stitcher module
        cvtColor(curimage, newimage, CV_BGRA2RGB);
        // Reduce the resolution for fast computation
        float scale = 1000.0f / curimage.rows;
        resize(newimage, newimage, Size(scale * curimage.rows, scale *
                                                               curimage.cols));
        imgVec.push_back(newimage);
    }
    Mat & result = *(Mat*) outputAddress;
    Stitcher stitcher = Stitcher::createDefault();
    stitcher.stitch(imgVec, result);
    // Release the jlong array
    env->ReleaseLongArrayElements(imageAddressArray, imgAddressArr ,0);

    /* Mat &mGr = *(Mat *) matAddrGray;
    for (int k = 0; k < nbrElem; k++) {
        int i = rand() % mGr.cols;
        int j = rand() % mGr.rows;
        mGr.at<uchar>(j, i) = 255;
    }
     */

}
}
