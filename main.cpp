#include <iostream>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void rgb2gray(const Mat src, Mat &result)
{
    CV_Assert(src.depth() != sizeof(uchar)); //harus 8 bit

    result = Mat::zeros(src.rows, src.cols, CV_8UC1); //buat matrik 1 chanel
    uchar data;

    if(src.channels() == 3){

        for( int i = 0; i < src.rows; ++i)
            for( int j = 0; j < src.cols; ++j )
            {
                data = (uchar)(((Mat_<Vec3b>) src)(i,j)[0] * 0.0722 + ((Mat_<Vec3b>) src)(i,j)[1] * 0.7152 + ((Mat_<Vec3b>) src)(i,j)[2] * 0.2126);

                result.at<uchar>(i,j) = data;
            }


    }else{

        result = src;
    }

}

void invariantMomentHu(const Mat src, vector<double>& result)
{
    //momen dua dimensi
    double m00=0, m10=0, m01=0;
    int x,y;

    for( int i = 0; i < src.rows; ++i){
        for( int j = 0; j < src.cols; ++j ){
            x = j + 1;
            y = i + 1;
            m00 += src.at<uchar>(i,j);
            m10 += x * src.at<uchar>(i,j);
            m01 += y * src.at<uchar>(i,j);

        }
    }

    //central moment lainnya & kemudian normalized central moments
    double xbar = m10 / m00;
    double ybar = m01 / m00;

    double m11 = 0, m20 = 0, m02 = 0, m30 = 0,
           m03 = 0, m12 = 0, m21 = 0;

    for( int i = 0; i < src.rows; ++i){
        for( int j = 0; j < src.cols; ++j ){
            x = j + 1;
            y = i + 1;
            m11 += ( x - xbar ) * ( y - ybar ) * src.at<uchar>(i,j) / pow( m00, 2 );
            m20 += pow( ( x - xbar ), 2 ) * src.at<uchar>(i,j) / pow( m00, 2 );
            m02 += pow( ( y - ybar ), 2 ) * src.at<uchar>(i,j) / pow( m00, 2 );
            m30 += pow( ( x - xbar ), 3 )  * src.at<uchar>(i,j) / pow( m00, 2.5 );
            m03 += pow( ( y - ybar ), 3 ) * src.at<uchar>(i,j) / pow( m00, 2.5 );
            m12 += ( x - xbar ) * pow( ( y - ybar ), 2 ) * src.at<uchar>(i,j) / pow( m00, 2.5 );
            m21 += pow( ( x - xbar ), 2 ) * ( y - ybar ) * src.at<uchar>(i,j) / pow( m00, 2.5 );

        }
    }

    //ketujuh nilai invariant moments
    double moment;
    //1
    moment = m20 + m02;
    result.push_back(moment);

    //2
    moment = pow( m20 + m02, 2 ) * 4 * pow( m11, 2);
    result.push_back(moment);

    //3
    moment = pow( m30 - 3 * m12, 2 ) * pow( 3 * m21 - m03, 2);
    result.push_back(moment);

    //4
    moment = pow( m30 + m12, 2 ) * pow( m21 - m03, 2);
    result.push_back(moment);

    //5
    moment = ( m30 - 3 * m12 ) * ( m30 + m12 ) * ( pow( m30 + m12, 2 ) - 3* pow( m21 + m03, 2) )
             + ( 3 * m21 - m03 ) * ( m21 + m03 ) * ( 3 * pow( m30 + m12, 2 ) - pow( m21 + m03, 2) );
    result.push_back(moment);

    //6
    moment = ( m20 - m02 )  * ( pow( m30 + m12, 2 ) - 3* pow( m21 - m03, 2) )
             + 4 * m11 * ( m30 + m12 ) * ( m21 + m03 );
    result.push_back(moment);

    //7
    moment = ( 3 * m21 - m03 )  * ( m30 + m12 )  * ( pow( m30 + m12, 2 ) - 3 * pow( m21 + m03, 2) )
             + ( 3 * m12 - m30 )  * ( m21 + m03 )  * ( 3 * pow( m30 + m12, 2 ) - pow( m21 + m03, 2) );
    result.push_back(moment);
}

void printMoments(char label[] ,const vector<double> huMoments)
{
    cout<<label<<endl<<setprecision(50);;
    for(unsigned int i = 0; i < huMoments.size(); ++i){
        cout<<i+1<<" = "<<huMoments[i]<<endl;
    }
}

int main(int /*argc*/, char /*argv*/)
{
    vector<double> huMoments;



    Mat g1 = imread("D:\\Project\\C++\\CitraDigital\\gambar1.jpg");
    rgb2gray(g1, g1);
    invariantMomentHu(g1, huMoments);
    printMoments("gambar 1 : " ,huMoments);

    namedWindow("gambar1");
    imshow("gambar1", g1);

    huMoments.clear();
    Mat g2 = imread("D:\\Project\\C++\\CitraDigital\\gambar2.jpg");
    rgb2gray(g2, g2);
    invariantMomentHu(g2, huMoments);
    printMoments("gambar 2 : " ,huMoments);

    namedWindow("gambar2");
    imshow("gambar2", g2);

    huMoments.clear();
    Mat g3 = imread("D:\\Project\\C++\\CitraDigital\\gambar3.jpg");
    rgb2gray(g3, g3);
    invariantMomentHu(g3, huMoments);
    printMoments("gambar 3 : " ,huMoments);

    namedWindow("gambar3");
    imshow("gambar3", g3);

    waitKey(0);
}

