#include"header.h"
int main(int argc, char const *argv[])
{
    VideoCapture capture("../4.mp4");
    Mat image_origin;
    Mat image_blue;
    Mat image_binary;
    Mat image_vertical;
    Mat image_canny;
    Mat image_rects;
    Mat image_box;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Rect> rects;
    vector<Rect> rect_boxes;
    capture>>image_origin;
    while(!image_origin.empty())
    {
        get_blue(image_origin,image_blue);
        get_binary(image_blue,image_binary,150);
        get_vertical(image_binary,image_vertical);
        get_contours(image_vertical,image_canny,100, contours,hierarchy);
        get_rects(contours,rects);
        get_box(rects,rect_boxes);
        draw_rects(rects,image_blue.size(),image_rects);
        image_box=image_origin.clone();
        draw_box(rect_boxes,image_blue.size(),image_box);
        imshow("origin",image_origin);
        imshow("blue",image_blue);
        imshow("binary",image_binary);
        imshow("vertical",image_vertical);
        imshow("canny",image_canny);
        imshow("rects",image_rects);
        imshow("box",image_box);
        capture>>image_origin;
        waitKey(0);
    }
    cout<<"done3"<<endl;
    return 0;

}
