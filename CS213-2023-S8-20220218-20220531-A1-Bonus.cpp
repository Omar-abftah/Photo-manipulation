//Program: CS213-2023-20220218-20220531-A1-Part1.cpp
//Purpose: editing photos with filters
//Author : Habiba Ali Zein El-Abideen Abd El-Fattah - 20220531 - zain.habiba0@gmail.com
//Author : Omar Ahmed Abdelfatah Gabr               - 20220218 - omarahmedgabrahmed111@gmail.com
//Last update : 7 October 2023


// FCAI – OOP Programming – 2023 - Assignment 1 
// Program Name:				CS213-2023-20220218-20220531-A1-Part1.cpp
// Last Modification Date:	16/10/2023
// Author1 and ID and Group:	Omar Ahmed Abdelfatah Gabr  - 20220218 - Group B
// Author2 and ID and Group:	 Habiba Ali Zein El-Abideen Abd El-Fattah - 20220531 - Group B
// Author1 E-mail: omarahmedgabrahmed111@gmail.com
// Author2 E-mail: zain.habiba0@gmail.com
// Teaching Assistant:		-
// Purpose: Editing photos with filters	

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

//Initializing the 2D arrays used to represent the photo pixels.
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char image3[SIZE][SIZE][RGB];
//Initializing the functions of the filters
void read ();
void save ();
void BWfilter ();
void rotate ();
void merge ();
void invert ();
void brightness ();
void flip ();
void enlarge();
void mirror ();
void detect();
void whiten(unsigned char arr[SIZE][SIZE][RGB]);
void blur();
void crop();
void shuffle();
void shrink();
void skew_horizontal();
void skew_vertical();

//function to take the photo and store its gray shades in the 2D array.
void read ()
{
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
//function to write a new bmp file from the processed pixel data stored in the 2D array.
void save ()
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
void whiten(unsigned char arr[SIZE][SIZE][RGB])
{
    for(int i=0;i<SIZE;++i)
    {
        for(int j = 0 ; j < SIZE ;++j)
        {
            for(int k = 0 ; k < RGB;k++)
            {
                arr[i][j][k]=255;
            }
        }
    }
}
//Black and White filter
void BWfilter ()
{
    //Calculating the average of the grey shades
    long long sum = 0;
    for(int i = 0 ; i < SIZE;i++)
    {
        for(int j = 0 ; j < SIZE;j++)
        {
            for(int k = 0 ; k < RGB;k++)
            {
                sum+=image[i][j][k];
            }
        }
    }

    long long average = sum/(SIZE*SIZE*RGB);

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            int sum2 = 0;
            for(int k = 0 ; k < RGB;k++)
            {
                sum2+=image[i][j][k];    
            }
            //if the grey shade of the pixel is less than the average, the pixel will be black
            if (sum2 > average)
            {
                for(int k = 0 ; k < RGB;k++)
                {
                    image[i][j][k] = 255;
                }
            }

                //if the grey shade of the pixel is greater than the average, the pixel will be white 
            else
            {
                    
                for(int k = 0 ; k < RGB;k++)
                {
                    image[i][j][k] = 0;
                }
            }  
        }
    }
}
void rotate()
{
    // taking the angle of the rotation as an input
    cout<<"Rotate (90), (180) or (270) degrees? ";
    int angle;
    cin>>angle;
    if(angle==90) 
    {
        //if the angle is 90 degrees we change the row number to 256 - column number 
        // and change the column number to the row number
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE; j++) 
            {
                for(int k = 0 ; k < RGB;k++)
                {
                    image2[i][j][k]=image[SIZE-j][i][k];
                }
            }
        }
        for(int i = 0 ; i < SIZE; i++)
        {
            for(int j = 0 ; j < SIZE ; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if (angle==180){
        //if the angle is 180 degrees we change the row number to 256 - row number 
        //and change the column number to the 256 - column number
        for (int i = 0; i < SIZE; i++)  
        {
            for (int j = 0; j < SIZE; j++) 
            {
                for (int k = 0 ; k < RGB;k++)
                {
                    image2[i][j][k]=image[SIZE-i][SIZE-j][k];
                }
            }
        }
        // we save the edited image into image2 array
        for(int i = 0 ; i < SIZE; i++)
        {
            for(int j = 0 ; j < SIZE ; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if(angle==270){
        //if the angle is 90 degrees we change the row number to 256 - column number 
        // and change the column number to the row number
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE; j++) 
            {
                for(int k = 0 ; k < RGB;k++)
                {
                    image2[i][j][k]=image[SIZE-j][i][k];
                }
            }
        }
        //if the angle is 180 degrees we change the row number to 256 - row number 
        //and change the column number to the 256 - column number
        for(int i = 0 ; i < SIZE ; i++)
        {
            for(int j = 0 ; j < SIZE ; j++) 
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][j][k]=image2[SIZE-i][SIZE-j][k];
                }
            }
        }
    }
}
void merge ()
{
    // first we take the photo we want to merge with the other photo as input
    // and store it in image2 array
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);

    // we calculate the average of the pixels of the same place in both images
    // and store it in every pixel corresponding to it in image2 array
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            for(int k = 0 ; k < RGB ;k++)
            {
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }

    }
}
void invert ()
{
    // we turn each shade to the opposite shade of each pixel
    for(int i = 0 ; i < SIZE;i++)
    {
        for(int j = 0 ; j < SIZE;j++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = 255-image[i][j][k];
            }
        }
    }

}
void flip()
{
    // we take teh type of the flip as as input
    unsigned char flip;
    cout << "Flip (h)orizontally or (v)ertically ? ";
    cin >> flip;
    towlower(flip);
    // if the type of the flip is horizontal
    // we swap the pixel with the pixel its column number equals to 255 - column number
    if(flip == 'h')
    {
        for(int i = 0 ; i < SIZE;i++)
        {
            for(int j = 0 ; j < SIZE/2;j++)
            {
                for(int k = 0 ; k < RGB ;k++)
                {
                    swap(image[i][j][k],image[i][255-j][k]);
                }
            }
        }
    }

    // if the type of the flip is vertical
    // we swap the pixel with the pixel its row number equals to 255 - row number
    else
    {
        for(int i = 0 ; i < SIZE/2;i++)
        {
            for(int j = 0 ; j < SIZE;j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    swap(image[i][j][k],image[255-i][j][k]);
                }
            }
        }
    }
}
void brightness ()
{   
    //we take the operation we want to apply on the image as an input
    unsigned char light;
    cout << "Do you want to (d)arken or (l)ighten? ";
    cin >> light;
    towlower(light);
    // if the operation is lighten
    // we increase each pixels greyshade to (255-that pixel greyshade)/2
    if(light == 'l')
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j< SIZE; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][j][k] += (255-image[i][j][k])/2;
                }            
            }
        }
    }

    // if the operation is darken
    // we decrease each pixels greyshade by that grey shade / 2
    else
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j< SIZE; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][j][k] -= image[i][j][k]/2;
                }
            }
        }
    }
}
void mirror()
{
    // in this filter we start with asking the user to select which side he want to be mirrored
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    unsigned char direction;
    cin >> direction;

    if(direction == 'd')
    {
        // if the direction is down side we just change the i with 255-i in order to make every pixel equals to its corresponding
        for(int i = 0 ; i < SIZE ; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][j][k] = image[255-i][j][k];
                }
            }
        }
    }
    else if(direction == 'r')
    {
        // if the direction is down side we just change the j with 255-j in order to make every pixel equals to its corresponding
        for(int i = 0 ; i < SIZE ; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][j][k] = image[i][255-j][k];
                }
            }
        }
    }
    else if(direction == 'u')
    {
        // if the direction is down side we just change the i with 255-i in order to make every pixel equals to its corresponding
        for(int i = 0 ; i < SIZE ; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[255-i][j][k] = image[i][j][k];
                }
            }
        }
    }
    else if(direction == 'l')
    {
        // if the direction is down side we just change the j with 255-j in order to make every pixel equals to its corresponding
        for(int i = 0 ; i < SIZE ; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image[i][255-j][k] = image[i][j][k];
                }
            }
        }
    }
}

void detect()
{
    //in this filter, we first apply black and white filter in order to define borders better
    BWfilter();
    // and then we use the whiten function to make all the image2 image white
    whiten(image2);

    // then if a pixel is black and all its surroundings are black it is considered a non border pixel
    // if at least on pixel of its surroundings is white it's considered border pixel
    // a border pixel is turned black and non border is turned white
    for(int i = 1 ; i < SIZE-1; i++)
    {
        for(int j = 1 ; j < SIZE-1; j++)
        {
            int cnt = 0;
            for(int k = 0 ; k < RGB; k++)
            {
                if(image[i][j][k] == 0)
                {
                    if(image[i][j+1][k] == 255 ||image[i][j-1][k] == 255 ||
                    image[i+1][j][k] == 255 ||image[i-1][j][k] == 255 ||
                    image[i+1][j+1][k] == 255 || image[i-1][j-1][k] == 255)
                    {
                        for(int l = 0 ; l < RGB; l++)
                        {
                            image2[i][j][l] = 0;
                        }
                    }
                    else 
                    {
                        for(int l = 0 ; l < RGB; l++)
                        {
                            image2[i][j][l] = 255;
                        }
                    }
                }
            }
        }
    }
    // here we are copying all the pixels from image2 to image
    for(int i = 0 ; i<SIZE;++i)
    {
        for(int j = 0 ;j<SIZE;j++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void blur()
{
    //in this filter we simply compute the average of the surrounding 7*7 square of a certain pixel
    //and then storing that average in the pixel
    for(int i = 0 ; i < SIZE;i++)
    {
        for(int j = 0; j < SIZE;j++)
        {
            for(int r = 0 ; r < RGB; r++)
            {
                int average = 0;
                int cnt = 0;
                for(int k = -3 ; k <= 3 ;k++)
                {
                    for(int l = -3 ; l <= 3 ;l++)
                    {
                        if(i+k >= 0 && i+k < SIZE && j+l >= 0 && j+l < SIZE)
                        {
                            average += image[i+k][j+l][r];
                            cnt++;
                        }
                    }
                }
                image2[i][j][r] = average/cnt;
            }
        }
    }
    for(int i = 0 ; i < SIZE;i++)
    {
        for(int j = 0 ; j < SIZE; j++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }

}

void shuffle () 
{
    cout << "New order of quarters ?\n";
    int quarter[4];
    for (int i = 0 ; i < 4 ; i++) 
    {
        cin >> quarter[i];
    }
    for (int i = 0 ; i < 127 ; i++) 
    {
        for (int j = 0 ; j < 127 ; j++) 
        {
            for (int k = 0 ; k < RGB ; k++)
            {
                if (quarter[0] == 1) 
                {
                    image2[i][j][k] = image[i][j][k];
                }
                else if (quarter[0] == 2) 
                {
                    image2[i][j][k] = image[i][j+127][k];
                }   
                else if (quarter[0] == 3) 
                {
                    image2[i][j][k] = image[i+127][j][k];
                }
                else if (quarter[0] == 4) 
                {
                    image2[i][j][k] = image[i+127][j+127][k];
                }
            }
        }
    }
    for (int i = 0 ; i < 127 ; i++) 
    {
        for (int j = 127 ; j < SIZE ; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                if (quarter[1] == 1) 
                {
                    image2[i][j][k] = image[i][j-127][k];
                }
                else if (quarter[1] == 2) 
                {
                    image2[i][j][k] = image[i][j][k];
                }
                else if (quarter[1] == 3) 
                {   
                    image2[i][j][k] = image[i+127][j-127][k];
                }
                else if (quarter[1] == 4) 
                {
                    image2[i][j][k] = image[i+127][j][k];
                }
            }
        }
    }
    for (int i = 127 ; i < SIZE ; i++) 
    {
        for (int j = 0 ; j < 127 ; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                if (quarter[2] == 1) 
                {
                    image2[i][j][k] = image[i-127][j][k];
                }
                else if (quarter[2] == 2) 
                {
                    image2[i][j][k] = image[i-127][j+127][k];
                }
                else if (quarter[2] == 3) 
                {
                    image2[i][j][k] = image[i][j][k];
                }
                else if (quarter[2] == 4) 
                {
                    image2[i][j][k] = image[i][j+127][k];
                }
            }
        }
    }
    for (int i = 127 ; i < SIZE ; i++) 
    {
        for (int j = 127 ; j < SIZE ; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                if (quarter[3] == 1) 
                {
                    image2[i][j][k] = image[i-127][j-127][k];
                }
                else if (quarter[3] == 2) 
                {
                    image2[i][j][k] = image[i-127][j][k];
                }
                else if (quarter[3] == 3) 
                {
                    image2[i][j][k] = image[i][j-127][k];
                }
                else if (quarter[3] == 4) 
                {
                    image2[i][j][k] = image[i][j][k];
                }
            }
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void shrink ()
{
    cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
    string dim;
    cin >> dim;
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image2[i][j][k] = 255;
            }
        }
    }
    if (dim == "1/2") 
    {
        int ptr = 0;
        for (int i = 0 ; i < 127 ; i ++)
        {
            int ptr1 = 0;
            for (int j = 0 ; j < 127 ; j ++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image2[i][j][k] = image[ptr][ptr1+1][k];
                }
                ptr1 +=2;
            }
            ptr +=2;
        }
    }
    if (dim == "1/3") 
    {
        int ptr = 0;
        for (int i = 0 ; i < 85 ; i ++)
        {
            int ptr1 = 0;
            for (int j = 0 ; j < 85 ; j ++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image2[i][j][k] = image[ptr][ptr1+2][k];
                }   
                ptr1 +=3;
            }
            ptr +=3;
        }
    }
    if (dim == "1/4") 
    {
        int ptr = 0;
        for (int i = 0 ; i < 63 ; i ++)
        {
            int ptr1 = 0;
            for (int j = 0 ; j < 63 ; j ++)
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image2[i][j][k] = image[ptr][ptr1+3][k];
                }
                ptr1 +=4;
            }
            ptr +=4;
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}
void enlarge ()
{
    cout << "Which quarter to enlarge 1, 2, 3 or 4?\n";
    int part ;
    cin >> part;
    if (part == 1) 
    {
        int ptr = 0;
        for (int i = 0 ; i < 127 ; i++) 
        {
            int ptr1 = 0;
            for (int j = 0 ; j < 127 ; j++) 
            {
                for(int k = 0 ; k < RGB;k++)
                {
                    image2[ptr][ptr1][k] = image[i][j][k];
                    image2[ptr][ptr1+1][k] = image[i][j][k];
                    image2[ptr+1][ptr1][k] = image[i][j][k];
                    image2[ptr+1][ptr1+1][k] = image[i][j][k];
                }
                ptr1 += 2;
            }
            ptr += 2;
        }
    }
    if (part == 2) 
    {
        int ptr = 0;
        for (int i = 0 ; i < 127 ; i++) 
        {
            int ptr1 = 0;
            for (int j = 127 ; j < SIZE ; j++) 
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image2[ptr][ptr1][k] = image[i][j][k];
                    image2[ptr][ptr1+1][k] = image[i][j][k];
                    image2[ptr+1][ptr1][k] = image[i][j][k];
                    image2[ptr+1][ptr1+1][k] = image[i][j][k];
                }
                ptr1 += 2;
            }
            ptr += 2;
        }
    }
    else if (part == 3) 
    {
        int ptr = 0;
        for (int i = 127 ; i < SIZE ; i++) 
        {
            int ptr1 = 0;
            for (int j = 0 ; j < 127 ; j++) 
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image2[ptr][ptr1][k] = image[i][j][k];
                    image2[ptr][ptr1+1][k] = image[i][j][k];
                    image2[ptr+1][ptr1][k] = image[i][j][k];
                    image2[ptr+1][ptr1+1][k] = image[i][j][k];
                }
                ptr1 += 2;
            }
            ptr += 2;
        }
    }
    else if (part == 4) 
    {
        int ptr = 0;
        for (int i = 127 ; i < SIZE ; i++)
        {
            int ptr1 = 0;
            for (int j = 127 ; j < SIZE ; j++) 
            {
                for(int k = 0 ; k < RGB; k++)
                {
                    image2[ptr][ptr1][k] = image[i][j][k];
                    image2[ptr][ptr1+1][k] = image[i][j][k];
                    image2[ptr+1][ptr1][k] = image[i][j][k];
                    image2[ptr+1][ptr1+1][k] = image[i][j][k];
                }
                ptr1 += 2;
            }
            ptr += 2;
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void crop()
{
    int x , y;
    int length , width;
    cout << "Please enter x y l w: ";
    cin >> x >> y;
    cin >> length >> width;
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image2[i][j][k] = 255;
            }
        }
    }
    int l = SIZE - x;
    int m = SIZE - y;
    for ( int i = x ; i < l ; i++ ) 
    {
        for (int j = y ; j < m ; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image2[i][j][k] = image[i][j][k];
            }
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
    
}

void skew_horizontal()
{
    double rad;
    cout<<"Please enter degree to skew right: ";
    cin>>rad;
    rad = 90 - rad;
    rad = (rad * 22) / (180 * 7);
    double compression = tan(rad) * SIZE;
    double length = 256 / (1 + (1 / tan(rad)));
    double pixels = 256 / length;
    double move = 256 - length;
    double step = move / SIZE;

    for (int i = 0 ; i < SIZE ; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image2[i][j][k] = 255;
            }
        }
    }

    for(int i = 0 ; i < SIZE ; i++)
    {
        double ptr = 0;
        for(int j = 0 ; j < length ; j++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image2[i][j][k] = image[i][(int)ptr+(int)pixels][k];
            }
            ptr += pixels;
        }
    }

    for ( int i = 0 ; i < SIZE ; i++ ) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image3[i][j][k] = 255;
            }
        }
    }

    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image3[i][j+(int)move][k] = image2[i][j][k];
            }
        }
        move -= step ;
    }
    for(int i = 0 ; i < SIZE ;i++)
    {
        for(int  j = 0 ; j < SIZE ; j++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image3[i][j][k];
            }
        }
    }
}

void skew_vertical()
{
    // first we take the angle of the vertical skew and turning it to rad 
    // we concluded that the length is computed using the following formula
    double rad;
    cout<<"Please enter degree to skew up: ";
    cin>>rad;
    rad = 90 - rad;
    rad = (rad * 22) / (180 * 7);
    double length = 256 / (1 + (1 / tan(rad)));
    double pixels = 256 / length;
    double move = 256 - length;
    double step = move / SIZE;
    // first we whiten the the image2 
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0 ; j < SIZE ; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image2[i][j][k] = 255;
            }
        }
    }
    // then we compress the image into the needed space
    double ptr = 0;
    for(int i = 0 ; i < length; i++)
    {
        for(int j = 0 ; j < SIZE ; j++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image2[i][j][k] = image[(int)ptr+(int)pixels][j][k];
            }
        }
        ptr+=pixels;
    }
    // here we whiten image3 

    for ( int i = 0 ; i < SIZE ; i++ ) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image3[i][j][k] = 255;
            }
        }
    }
    // here we skew the image
    for(int j = 0 ; j < SIZE ; j++)
    {
        for(int i = 0 ; i < length ; i++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image3[i+(int)move][j][k] = image2[i][j][k];
            }
        }
        move -= step;
    }
    // we copy the image3 into image to save it
    for(int i = 0 ; i < SIZE ;i++)
    {
        for(int  j = 0 ; j < SIZE ; j++)
        {
            for(int k = 0 ; k < RGB; k++)
            {
                image[i][j][k] = image3[i][j][k];
            }
        }
    }
}
int main()
{
    cout << "Greetings User in our little program\n";
    cout << "Our program is simply a program to edit photos using some already implemented filters \n";
    cout << "Let's dive into it!! \n ";
    
    // here the program starts with greeting the user
    // after that the program starts to take input until the user exits
    read();
    while (true)
    {
        // first the program shows the filters with numbers
        // so it can be easy for the user to choose the desired filter
        cout << "Please select a filter to apply or 0 to exit: \n";
        cout<<"1-Black & White Filter \n";
        cout<<"2-Invert Filter \n";
        cout<<"3-Merge Filter  \n";
        cout<<"4-Flip Image \n";
        cout<<"5-Darken and Lighten Image  \n";
        cout<<"6-Rotate Image \n";
        cout<<"7-Detect Image Edges  \n";
        cout<<"8-Enlarge Image\n";
        cout<<"9-Shrink Image \n";
        cout<<"a-Mirror 1/2 Image\n";
        cout<<"b-Shuffle Image \n";
        cout<<"c-Blur Image \n";
        cout<<"d-Crop Image \n";
        cout<<"e-Skew Image Right   \n";
        cout<<"f-Skew Image Up   \n";
        cout<<"s-Save the image to a file \n";
        // then we take the number of the filter as an input to apply it on the picture
        char filter;
        cin>>filter;
        // conditions to determine which filter should be applied to the picture
        if(filter == '0')
        {
            break;
        }
        else if(filter == '1')
        {
            BWfilter ();
        }
        else if(filter == '2')
        {
            invert ();
        }
        else if(filter == '3')
        {
            merge ();
        }
        else if(filter == '4')
        {
            flip ();
        }
        else if(filter == '5')
        {
            brightness ();
        }
        else if(filter == '6')
        {
            rotate ();
        }
        else if(filter == '7')
        {
            detect ();
        }
        else if(filter == '8')
        {
            enlarge();
        }
        else if(filter == '9')
        {
            shrink();
        }
        else if(filter == 'a')
        {
            mirror();
        }
        else if(filter == 'b')
        {
            shuffle();
        }
        else if(filter == 'c')
        {
            blur ();
        }
        else if(filter == 'd')
        {
            crop();
        }
        else if(filter == 'e')
        {
            skew_horizontal();
        }
        else if(filter == 'f')
        {
            skew_vertical();
        }else if(filter == 's')
        {
            save();
        }
    }
    return 0;
}
