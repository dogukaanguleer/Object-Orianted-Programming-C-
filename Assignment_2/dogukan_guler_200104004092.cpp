#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class ppmImage
{

public:
    ppmImage();
    ppmImage(string ppm_file_name);
    ppmImage(int dimension1, int dimension2);

    int save(string name); 
    int read(string name);
    int change_channels(int choice);
    void change_pixel(int index, int choice);
    vector<int> getImageData();
    void singleColor(vector<int> sourceImageData, int choice);
    void print_dimension(string name);
    int pixel_information(int firstIndex, int secondIndex, string color);

private:
    string file_name;
    int x, y;    //dimensions
    vector<int> image_data;
    string header1;    //P3 
    int max_color_value;    //255
};

//================================================================
//                  ppmImage::ppmImage
// Default constructor initializes dimensions,file name, and header
//================================================================
ppmImage::ppmImage()
{
    x = 4;
    y = 4;
    file_name = "new_file";
    header1 = "P3";
    max_color_value = 255;
}

//================================================================
//                  ppmImage::ppmImage
// This constructor initializes file name and dimensions.
//================================================================
ppmImage::ppmImage(string ppm_file_name)
{
    file_name = ppm_file_name;
    x = 4;
    y = 4;
}

//================================================================
//                  ppmImage::ppmImage
// This constructor initializes all the private data.
//================================================================
ppmImage::ppmImage(int dimension1, int dimension2)
{
    x = dimension1;
    y = dimension2;
    file_name = "new_file";
    header1 = "P3";
    max_color_value = 255;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            for (int k = 0; k < 3; k++)
                image_data.push_back(255); /*ASSINGS WHITE VALUES.*/
}

//===========================================================
//                  ppmImage::save
// Writes the ppm image data to file.
//===========================================================
int ppmImage::save(string name)
{
    ofstream MyFile(name);
    /*write the header part to file.*/
    MyFile << header1 << endl;
    MyFile << x << " " << y << endl;
    MyFile << max_color_value << endl;

    int index = 0;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < 3; k++) /*for 3 pixels*/
            {
                MyFile << image_data[index] << " "; /*writes the image data by one by*/
                index++;
            }
        }
        MyFile << endl;
    }
    MyFile.close();
    return 1;
}

//===========================================================
//                  ppmImage::read
//It reads data from file and checks the ppm image file format.
//===========================================================
int ppmImage::read(string name)
{
    //FILE OPERATIONS
    ifstream myfile;
    myfile.open(name);
    myfile >> header1;
    myfile >> x >> y >> max_color_value;
    if (header1 != "P3" || max_color_value != 255) /*checks the header is valid*/
        return 0;

    int index = 0, temp;

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            for (int k = 0; k < 3; k++)
            {
                if (myfile.peek() != EOF) /* checks end of files, then if data is not enough for dimension return 0*/
                {
                    myfile >> temp;
                    if (temp < 0) /*checks the invalid image data*/
                        return 0;
                    if (temp > 255) /*checks upper bound of color's value, if is more than 255 ,it will assign 255*/
                        temp = 255;
                }
                else
                {
                    myfile.close(); /*if data is not enough, close the file and exit*/
                    return 0;
                }
                image_data.push_back(temp); /*vector push back operation*/
                index++;
            }

    myfile.close();
    return 1;
}
//====================================================
//        ppmImage::print_dimension
// prints the dimension, a member function.
//====================================================
void ppmImage::print_dimension(string name)
{
    cout << x << " " << y;
}

//====================================================
//        ppmImage::pixel_information
// takes 2 indices and color, return color value of index.
//====================================================
int ppmImage::pixel_information(int firstIndex, int secondIndex, string color)
{
    int index = 0, color_choice = 3, returnValue = 0;

    /*according the given color, it determines the pixel*/
    if (color == "red")
        color_choice = 0;
    else if (color == "green")
        color_choice = 1;
    else if (color == "blue")
        color_choice = 2;

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            for (int k = 0; k < 3; k++)
            {
                if (firstIndex == i + 1 && secondIndex == j + 1 && k == color_choice) //checks all index to find given index
                    returnValue = image_data[index];
                index++;
            }

    return returnValue;
}
//=============================================
//         ppmImage::change_channels
//Changes the channels according the choice.
//==============================================
int ppmImage::change_channels(int choice)
{
    int index = 0;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            for (int k = 0; k < 3; k++)
            {
                if (k == 0)                      /*first index color of channel*/
                    change_pixel(index, choice); /*call another function to execute index operations.*/
                index++;
            }

    return 1;
}
//=============================================
//         ppmImage::change_pixel
//Changes the color values according the choice.
//==============================================
void ppmImage::change_pixel(int index, int choice)
{
    int temp;
    if (choice == 3) // if choice is 3 increase index
        index++;
    if (choice == 1 || choice == 3) //for 1 swaps red and green, for 3 swaps green and blue
    {
        temp = image_data[index];
        image_data[index] = image_data[index + 1];
        image_data[index + 1] = temp;
    }
    if (choice == 2) //swaps red and blue
    {
        temp = image_data[index];
        image_data[index] = image_data[index + 2];
        image_data[index + 2] = temp;
    }
}
//==================================================
//         ppmImage::getImageData
//To access private data return the image_data vector
//==================================================
vector<int> ppmImage::getImageData()
{
    return image_data;
}

//==================================================
//         ppmImage::singleColor
//channel will single color, according the choice
//==================================================
void ppmImage::singleColor(vector<int> sourceImageData, int choice)
{

    int index = 0;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            for (int k = 0; k < 3; k++)
            {
                if ((choice == 1 && k == 0) || (choice == 2 && k == 1) || choice == 3 && k == 2) /*assigns the desired color to the new image data vector*/
                    image_data.push_back(sourceImageData[index]);
                else
                    image_data.push_back(0);
                index++;
            }
}

//==========================TEST FUNCTIONS====================================
int read_ppm(const string source_ppm_file_name, ppmImage &destination_object)
{
    return destination_object.read(source_ppm_file_name); /*calls member read function and returns member read functions returns value.*/
}

int write_ppm(const string destination_ppm_file_name, ppmImage &source_object)
{
    return source_object.save(destination_ppm_file_name); /*calls member save function and returns member save functions returns value.*/
}

int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice)
{
    return image_object_to_be_modified.change_channels(swap_choice); /*calls member change_channels function and returns member change_channels functions returns value.*/
}

ppmImage single_color(ppmImage &source, int color_choice)
{
    
    ppmImage single_object; /*creates a new object has 4x4 dimeonsion to assing single color's value*/
    single_object.singleColor(source.getImageData(), color_choice);
    return single_object; /*returns a object*/
}
//============================================================================

int main(int argc, char **argv)
{

    if (argc == 3) /* checks the argument number */
    {
        string control = argv[1];
        for (int i = 0; i < control.length(); i++) /*Check each character of string parameter*/
            if (isdigit(control[i]) == false)      /*if parameter is not digit, it gives a error message */
                return 0;

        int choice = stoi(argv[1]); /*assing the first argument to integer value*/
        ppmImage destination_object(argv[2]);

        if (choice == 1)
        {
            if (read_ppm(argv[2], destination_object)) /*if reading is succesfull and all of the data is valid.*/
            {
                write_ppm("o1.ppm", destination_object); /*calls the write_ppm function to write the same data to o1.ppm file*/
            }
        }
        else if (choice == 2)
        {
            if (read_ppm(argv[2], destination_object)) /*if reading is succesfull and all of the data is valid.*/
            {
                swap_channels(destination_object, 1); /*calls the function to swap red and green channels */

                write_ppm("o2.ppm", destination_object); /*calls the write_ppm function to write new image data to o2.ppm file*/
            }
        }
        else if (choice == 3)
        {
            if (read_ppm(argv[2], destination_object)) /*if reading is succesfull and all of the data is valid.*/
            {
                swap_channels(destination_object, 2); /*calls the function to swap red and blue channels */

                write_ppm("o3.ppm", destination_object); /*calls the write_ppm function to write new image data to o3.ppm file*/
            }
        }
        else if (choice == 4)
        {
            if (read_ppm(argv[2], destination_object)) /*if reading is succesfull and all of the data is valid.*/
            {
                swap_channels(destination_object, 3); /*calls the function to swap green and blue channels */

                write_ppm("o4.ppm", destination_object); /*calls the write_ppm function to write new image data o4.ppm file*/
            }
        }
        else if (choice == 5)
        {
            if (read_ppm(argv[2], destination_object)) /*if reading is succesfull and all of the data is valid.*/
            {
                /* creates a default 4x4 object*/
                ppmImage newObject = single_color(destination_object, 1); /*calls the single_color function and assings the return value to newObject*/

                write_ppm("o5.ppm", newObject); /*calls the write_ppm function to write new image data to o5.ppm file*/
            }
        }
        else if (choice == 6)
        {
            if (read_ppm(argv[2], destination_object)) /*if reading is succesfull and all of the data is valid.*/
            {
                /* creates a default 4x4 object*/
                ppmImage newObject = single_color(destination_object, 2); /*calls the single_color function and assings the return value to newObject*/

                write_ppm("o6.ppm", newObject); /*calls the write_ppm function to write new image data to o6.ppm file*/
            }
        }
        else if (choice == 7)
        {
            if (read_ppm(argv[2], destination_object)) /*if reading is succesfull and all of the data is valid.*/
            {
                /* creates a default 4x4 object*/
                ppmImage newObject = single_color(destination_object, 3); /*calls the single_color function and assings the return value to newObject*/

                write_ppm("o7.ppm", newObject); /*calls the write_ppm function to write new image data to o7.ppm file*/
            }
        }
    }
    return 0;
}
