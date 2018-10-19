#include"header.h"
void get_blue(const Mat& image_origin,Mat& image_blue)
{
    vector<Mat> image_channels;
    split(image_origin,image_channels);
    image_blue=image_channels[0];
}

void get_binary(const Mat& image_origin,Mat& image_binary,int thresh = 0 )
{
    if(thresh==0)
    {
        threshold(image_origin,image_binary,0,255,CV_THRESH_OTSU);
    }
    else
    {
        threshold(image_origin,image_binary,thresh,255,THRESH_BINARY);
    }
}

void get_vertical(const Mat& image_origin,Mat& image_vertical)
{
    Mat kernal_vertical=getStructuringElement(MORPH_RECT,Size(1,image_origin.rows/50));
    erode(image_origin,image_vertical,kernal_vertical,Point(-1,-1));
    dilate(image_vertical,image_vertical,kernal_vertical,Size(-1,-1));
}

void get_wided(const Mat& image_origin,Mat& image_wided)
{
    Mat kernal_wide=getStructuringElement(MORPH_RECT,Size(3,1));
    dilate(image_origin,image_wided,kernal_wide,Point(-1,-1));
}
void get_contours(const Mat& image_origin,Mat& image_canny,int threshold,vector<vector<Point> >& contours, vector<Vec4i> hierarchy)
{
    int ratio=2;
    Canny(image_origin,image_canny,threshold,threshold*ratio);
    findContours(image_canny,contours,RETR_TREE,CHAIN_APPROX_SIMPLE);
    cout<<"the number of contours is :"<<contours.size()<<endl;
}
//首先先将所有的ｃｏｎｔｏｕｒｓ从不规则转化为精度为正负３的多边形，并且要求它必须闭合；然后再求最小的边界矩形
//如果得到的ｒｅｃｔ的形状不满足要求，那么直接删除掉
void get_rects(const vector<vector<Point> >& contours,vector<Rect>& bound_rect)
{
    bound_rect.clear();//clear the old rects;
    for(int i=0 ;i<contours.size();i++)
    {
        Mat contours_poly;
        approxPolyDP(contours[i],contours_poly,3,true);
        Rect rect_temp=boundingRect(contours_poly);
        cout<<"width :"<<rect_temp.width<<"\nheight :"<<rect_temp.height<<"\nrect_temp.width/rect_temp.height :"<<double(rect_temp.width)/double(rect_temp.height)<<endl;
        if(double(rect_temp.width)/double(rect_temp.height)<0.4&&double(rect_temp.width)/double(rect_temp.height)>0.1)
        {
            bound_rect.push_back(rect_temp);
        }
    }
    cout<<"the number of rects is :"<<bound_rect.size()<<endl;
}

void get_box(const vector<Rect>& bound_rect,vector<Rect>& rect_boxes)
{
    rect_boxes.clear();
    cout<<"--61 the number of bound_rect is :"<<bound_rect.size()<<endl;
    Point p1,p2;
   for(int i=0;i<bound_rect.size();i++)
   {
       for(int j=i;j<bound_rect.size();j++)
       {
           if(is_box(bound_rect[i],bound_rect[j]))
           {
               
               p1=Point(bound_rect[i].x,bound_rect[i].y);
               p2=Point(bound_rect[j].x,bound_rect[j].y+bound_rect[j].height);
               Rect rect_temp(p1,p2);
               rect_boxes.push_back(rect_temp);
           }
           cout<<"--69 is box or not :"<<is_box(bound_rect[i],bound_rect[j])<<endl;
       }
   } 
}

void draw_rects(const vector<Rect>& bound_rect,const Size& size_image, Mat& image_rects)
{
    image_rects = Mat::zeros( size_image, CV_8UC3 );
    Scalar color=Scalar(100,160,20);
    for(int i=0;i<bound_rect.size();i++)
    {
        rectangle( image_rects, bound_rect[i].tl(), bound_rect[i].br(), color, 2 );
    }
    
}

void draw_box(const vector<Rect>& rect_boxes,const Size& size_image,Mat& image_box)
{
    cout<<"the number of boxes is :"<<rect_boxes.size()<<endl;
    Scalar color=Scalar(0,0,200);
    //image_box=Mat::zeros(size_image,CV_8UC3);
    for(int i=0;i<rect_boxes.size();i++)
    {
        rectangle(image_box,rect_boxes[i],color,2);
    }
}

bool is_box(const Rect& rect_1,const Rect& rect_2)
{
    cout<< "( (rect_1.height - rect_2.height) < (rect_1.height/4) )"<<( (rect_1.height - rect_2.height) < (rect_1.height/4) )<<endl ;

    cout<<"rect_1.height"<<rect_1.height<<endl;;
    if( (abs(rect_1.height-rect_2.height) < (rect_1.height/2) ) && abs(rect_1.x-rect_2.x) > rect_1.height && abs(rect_1.x-rect_2.x) < rect_1.height*3.5 && abs(rect_1.y-rect_2.y) < (rect_1.height*0.4) )
    {
        return true;
    }
    else{
        return false;
    }
}

void delete_simrects(const vector<Rect>& bound_rect,vector<Rect>& diff_rect)
{
    for(int i)
}