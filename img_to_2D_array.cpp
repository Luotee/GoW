#include "img_to_2D_array.h"

/*
void img2array();
void showimg(string windowname, const Mat &img, int x, int y);
uint_fast8_t knn(uint_fast8_t b, uint_fast8_t g, uint_fast8_t r);
*/
void OpencvHp::show_answer(uint_fast8_t x, uint_fast8_t y, int direction)
{
    //讀取圖片
    Mat img = imread(".\\screen.bmp");
    if ( img.empty() ) 
    { 
        cout << "Error loading the image" << endl;
        exit(0);
    }
    //因windows scaling，將圖片縮小
    resize(img, img, Size(img.cols/RESIZE_SCALING, img.rows/RESIZE_SCALING));
    namedWindow("Answer", WINDOW_NORMAL);
    resizeWindow("Answer", img.cols, img.rows);
	moveWindow("Answer", 0, 0);
    
    double x1, y1, x2, y2;
    x1 = CHESSBOARD_X + x*GRID_SIZE + 0.5*GRID_SIZE;
    y1 = CHESSBOARD_Y + y*GRID_SIZE + 0.5*GRID_SIZE;
    if(direction)
    {
        x2 = CHESSBOARD_X + x*GRID_SIZE + 0.5*GRID_SIZE;
        y2 = CHESSBOARD_Y + (y+1)*GRID_SIZE + 0.5*GRID_SIZE;
    }
    else
    {
        x2 = CHESSBOARD_X + (x+1)*GRID_SIZE + 0.5*GRID_SIZE;
        y2 = CHESSBOARD_Y + y*GRID_SIZE + 0.5*GRID_SIZE;
    }
    

    arrowedLine(img, Point(x1,y1), Point(x2,y2), Scalar(0,0,255), 5, 8, 0,  0.1);
    imshow("Answer", img);

    Point3_<int> mouseInputs;
    setMouseCallback("Answer", CallBackFunc, &mouseInputs);
    //waitKey();
    while(1)
    {
        //if press ESC then break the loop
        int k = waitKey(1);
        if(k==27) break;
        if(mouseInputs.z==EVENT_MOUSEWHEEL) break;
    }
}

void OpencvHp::img2array(uint_fast8_t chessboard[8][8])
{
    //讀取圖片
    Mat img = imread(".\\screen.bmp");

    if ( img.empty() ) 
    { 
        cout << "Error loading the image" << endl;
        exit(0);
    }

    //因windows scaling，將圖片縮小
    resize(img, img, Size(img.cols/RESIZE_SCALING, img.rows/RESIZE_SCALING));
    //namedWindow("image", WINDOW_NORMAL);
    //resizeWindow("image", img.cols, img.rows);
	//moveWindow("image", 0, 0);
    //imshow("image", img);

    //標示棋盤
    line(//top line
        img, 
        Point2f(CHESSBOARD_X, CHESSBOARD_Y),
        Point2f((CHESSBOARD_X+8*GRID_SIZE), CHESSBOARD_Y), 
        Scalar(0,255,0), 1
    );
    line(//left line
        img, 
        Point2f(CHESSBOARD_X, CHESSBOARD_Y), 
        Point2f(CHESSBOARD_X, (CHESSBOARD_Y+8*GRID_SIZE)), 
        Scalar(0,255,0), 1
    );
    line(//bottom line
        img, 
        Point2f(CHESSBOARD_X, (CHESSBOARD_Y+8*GRID_SIZE)), 
        Point2f((CHESSBOARD_X+8*GRID_SIZE), (CHESSBOARD_Y+8*GRID_SIZE)), 
        Scalar(0,255,0), 1
    );
    line(//right line
        img, 
        Point2f((CHESSBOARD_X+8*GRID_SIZE), CHESSBOARD_Y), 
        Point2f((CHESSBOARD_X+8*GRID_SIZE), (CHESSBOARD_Y+8*GRID_SIZE)), 
        Scalar(0,255,0), 1
    );
    int i, j;
    float x, y;
    char *text;
    
    uint_fast8_t g, b, r;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            x=GRID_SIZE/2+CHESSBOARD_X+j*GRID_SIZE;
            y=GRID_SIZE/2+CHESSBOARD_Y+i*GRID_SIZE;
            
            b = img.at<Vec3b>(Point(x,y))[0];
            g = img.at<Vec3b>(Point(x,y))[1];
            r = img.at<Vec3b>(Point(x,y))[2];

            chessboard[j][i] = knn(b,g,r);

            switch(chessboard[j][i])
            {
                case '0' : rectangle(img, Point2f(x-GRID_SIZE/5, y-GRID_SIZE/5), Point(x+GRID_SIZE/5,y+GRID_SIZE/5), Scalar(255,255,255), 3); break;
                case '1' : circle(img, Point2f(x, y), circle_radius, Scalar(239,207,74), circle_thickness); break; //blue
                case '2' : circle(img, Point2f(x, y), circle_radius, Scalar(71,192,115), circle_thickness); break; //Green
                case '3' : circle(img, Point2f(x, y), circle_radius, Scalar(57,77,239), circle_thickness); break; //red
                case '4' : circle(img, Point2f(x, y), circle_radius, Scalar(123,227,255), circle_thickness); break; //yellow
                case '5' : circle(img, Point2f(x, y), circle_radius, Scalar(214,35,165), circle_thickness); break; //purple
                case '6' : circle(img, Point2f(x, y), circle_radius, Scalar(30,17,35), circle_thickness); break; //brown
                case '7' : rectangle(img, Point2f(x-GRID_SIZE/5, y-GRID_SIZE/5), Point(x+GRID_SIZE/5,y+GRID_SIZE/5), Scalar(150,150,255), 3); break;
                default : putText(img, "?", Point2f(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, LINE_AA);
            }
        }
    }

    //print the "initial" chessboard
    printf("===first identify===\n");
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%c ",chessboard[j][i]);
        }
        putchar(10);
    }

    namedWindow("mark", WINDOW_NORMAL);
    resizeWindow("mark", img.cols, img.rows);
    imshow("mark", img);

    Point3_<int> mouseInputs;
    setMouseCallback("mark", CallBackFunc, &mouseInputs);

    //waitKey();
    bool keyup=true;
    bool keyup2=true;
    while(1)
    {
        //if press ESC then break the loop
        int k = waitKey(1);
        if(k==27) break;

        if(mouseInputs.z==EVENT_LBUTTONDOWN && keyup)
        {
            keyup = false;
            user_modify_board(mouseInputs.x, mouseInputs.y, chessboard, img);
        }
        else if(mouseInputs.z!=EVENT_LBUTTONDOWN) keyup = true;

        if(mouseInputs.z==EVENT_LBUTTONDBLCLK && keyup2)
        {
            keyup2 = false;
            user_modify_board(mouseInputs.x, mouseInputs.y, chessboard, img);
        }
        else if(mouseInputs.z!=EVENT_LBUTTONDBLCLK) keyup2 = true;
        
        if(mouseInputs.z==EVENT_MOUSEWHEEL) break;
    }
    //print the "final" chessboard
    printf("===user modify===\n");
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%c ",chessboard[j][i]);
        }
        putchar(10);
    }
    destroyAllWindows();
}

void OpencvHp::showimg(string windowname, const Mat &img, int x, int y)
{
	namedWindow(windowname, WINDOW_NORMAL);
	imshow(windowname, img);
	resizeWindow(windowname, 480, 270);
	moveWindow(windowname, x, y);
}

uint_fast8_t OpencvHp::knn(uint_fast8_t b, uint_fast8_t g, uint_fast8_t r)
{
    //                       頭   藍   綠    紅   黃   紫   棕  爆頭 
    uint_fast8_t b_arr[8]={ 187, 239,  55,  52, 130, 160,  66, 160};
    uint_fast8_t g_arr[8]={ 195, 100, 183,  50, 223,  14,  69, 176};
    uint_fast8_t r_arr[8]={ 202,  74,  78, 217, 251,  78, 107, 225};
    int i;
    uint_fast8_t min_target;
    double min_distance = 1000.0;
    double distance;
    double x=1/3.0;

    for(i=0;i<8;i++)
    {
        distance = pow(
            (
                (b-b_arr[i])*(b-b_arr[i])+
                (g-g_arr[i])*(g-g_arr[i])+
                (r-r_arr[i])*(r-r_arr[i])
            ),
            x
        );
        
        if(distance < min_distance)
        {
            min_distance = distance;
            min_target = i+'0';
        }
    }
    return min_target;
}

void OpencvHp::CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    Point3_<int> *mouseInputs = (Point3_<int>*)userdata;
    mouseInputs->x= x;
    mouseInputs->y = y;
    mouseInputs->z = event;
    //printf("test event: %d\n",event);
}

void OpencvHp::user_modify_board(int mouse_x, int mouse_y, uint_fast8_t chessboard[8][8], const Mat &img)
{
    int board_x, board_y;
    board_x =  floor( (mouse_x-CHESSBOARD_X) / GRID_SIZE );
    board_y =  floor( (mouse_y-CHESSBOARD_Y) / GRID_SIZE );
    //printf("param = %g\n",CHESSBOARD_X);
    //printf("clickon: %d %d, %d %d\n",board_x,board_y,(mouse_x-(int)CHESSBOARD_X), (mouse_y-(int)CHESSBOARD_Y)); //for debug
    if(board_x<0||board_x>7||board_y<0||board_y>7) {}
    else
    {
        if(chessboard[board_x][board_y]=='7') chessboard[board_x][board_y]='0';
        else chessboard[board_x][board_y]=chessboard[board_x][board_y]+1;
        float re_x=GRID_SIZE/2+CHESSBOARD_X+board_x*GRID_SIZE;
        float re_y=GRID_SIZE/2+CHESSBOARD_Y+board_y*GRID_SIZE;
        switch(chessboard[board_x][board_y])
        {
            case '0' : rectangle(img, Point2f(re_x-GRID_SIZE/5, re_y-GRID_SIZE/5), Point(re_x+GRID_SIZE/5,re_y+GRID_SIZE/5), Scalar(255,255,255), 3); break;
            case '1' : circle(img, Point2f(re_x, re_y), circle_radius, Scalar(239,207,74), circle_thickness); break; //blue
            case '2' : circle(img, Point2f(re_x, re_y), circle_radius, Scalar(71,192,115), circle_thickness); break; //Green
            case '3' : circle(img, Point2f(re_x, re_y), circle_radius, Scalar(57,77,239), circle_thickness); break; //red
            case '4' : circle(img, Point2f(re_x, re_y), circle_radius, Scalar(123,227,255), circle_thickness); break; //yellow
            case '5' : circle(img, Point2f(re_x, re_y), circle_radius, Scalar(214,35,165), circle_thickness); break; //purple
            case '6' : circle(img, Point2f(re_x, re_y), circle_radius, Scalar(30,17,35), circle_thickness); break; //brown
            case '7' : rectangle(img, Point2f(re_x-GRID_SIZE/5, re_y-GRID_SIZE/5), Point(re_x+GRID_SIZE/5,re_y+GRID_SIZE/5), Scalar(150,150,255), 3); break;
            default : putText(img, "?", Point2f(re_x, re_y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, LINE_AA);
        }
        imshow("mark", img);
    }
}