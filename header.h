#ifndef __HEADER_H__
#define __HEADER_H__
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void get_blue(const Mat& image_origin,Mat& image_blue);
void get_vertical(const Mat& image_origin,Mat& image_vertical);
void get_binary(const Mat& image_origin,Mat& image_binary,int thresh );
void get_wided(const Mat& origin,Mat& image_wided);
void get_contours(const Mat& image_origin,Mat& image,int threshold,vector<vector<Point> >& contours, vector<Vec4i> heriarchy);
void get_rects(const vector<vector<Point> >& contours,vector<Rect>& bound_rect);
void get_box(const vector<Rect>& bound_rect,vector<Rect>& rect_boxes);
void delete_simrects(const vector<Rect>& bound_rect,vector<Rect>& diff_rect);
bool is_box(const Rect& rect_1,const Rect& rect_2);
void draw_rects(const vector<Rect>& bound_rect,const Size& size_image, Mat& image_rects);
void draw_box(const vector<Rect>& rect_boxes,const Size& size_image,Mat& image_box);
#endif