#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct channels
{
    int colors[3];                /*color array red, green, blue*/
    channels(int r, int g, int b) /* constructor */
    {
        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
    }
};

class ppmImage
{

public:
    ppmImage();
    ppmImage(string ppm_file_name);
    ppmImage(int dimension1, int dimension2);
    int read(string name);
    int save(string name);
    void print_dimension();
    friend ppmImage operator+(const ppmImage &image1, const ppmImage &image2);
    friend ppmImage operator-(const ppmImage &image1, const ppmImage &image2);
    friend ostream &operator<<(ostream &term, ppmImage &obj);
    int &operator()(int rowIndex, int colIndex, int color);
    int change_channels(int choice);
    void singleColor(int choice);

private:
    string file_name;
    int x, y; //dimensions
    vector<vector<channels>> image_data;
    string header1;
    int max_color_value;
};

/* STANDALONE FUNCTION PROTOTYPES */
int read_ppm(const string source_ppm_file_name, ppmImage &destination_object);
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
int test_print(const string filename_image1);
int write_ppm(const string destination_ppm_file_name, ppmImage &source_object);
int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage &source, int color_choice);

/*CONSTRUCTORS */
ppmImage::ppmImage() /*DEFAULT CONSTRUCTOR*/
{
}
ppmImage::ppmImage(string ppm_file_name) : file_name(ppm_file_name) /*Create object with given filen name.*/
{
}
ppmImage::ppmImage(int dimension1, int dimension2)
{
    x = dimension1;
    y = dimension2;
    file_name = "new_file";
    header1 = "P3";
    max_color_value = 255;

    for (int i = 0; i < x; i++)
    {
        vector<channels> v1;

        for (int j = 0; j < y; j++)
            v1.push_back(channels(255, 255, 255)); /*vector push back operation*/

        image_data.push_back(v1);
    }
}

/*It reads data from file and at the same time checks the ppm image file format.*/
int ppmImage::read(string name)
{
    /* FILE OPERATIONS */
    ifstream myfile;
    myfile.open(name);
    myfile >> header1;
    myfile >> x >> y >> max_color_value;
    if (header1 != "P3" || max_color_value != 255) /*checks the header is valid*/
        return 0;

    int tempColor[3];

    for (int i = 0; i < x; i++)
    {
        vector<channels> v1;

        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < 3; k++)
                myfile >> tempColor[k];

            if (tempColor[0] < 0 || tempColor[1] < 0 || tempColor[2] < 0) /*checks the invalid image data*/
                return 0;

            for (int k = 0; k < 3; k++) /*checks upper bound of color's value, if is more than 255 ,it will assign 255*/
                if (tempColor[k] > 255)
                    tempColor[k] = 255;

            v1.push_back(channels(tempColor[0], tempColor[1], tempColor[2])); /*vector push back operation*/
        }
        image_data.push_back(v1);
    }
    myfile.close();
    return 1;
}
/*Writes the ppm image data to file.*/
int ppmImage::save(string name)
{
    ofstream MyFile(name);
    MyFile << header1 << endl;
    MyFile << x << " " << y << endl;
    MyFile << max_color_value << endl;

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
            MyFile << image_data[i][j].colors[0] << " " << image_data[i][j].colors[1] << " " << image_data[i][j].colors[2] << " "; /*writes the image data by one by*/
        MyFile << endl;
    }
    MyFile.close();
    return 1;
}
void ppmImage::print_dimension()
{
    cout << x << " " << y;
}
/*A friend function. Operator overloading, sum of the pixels of  the objects */
ppmImage operator+(const ppmImage &image1, const ppmImage &image2)
{

    ppmImage sumObject(image1.x, image1.y);           /*creates an object with first objects dimensions*/
    if (image1.x == image2.x && image1.y == image2.y) // if sizes are equal.
    {
        for (int i = 0; i < image1.x; i++)
            for (int j = 0; j < image1.y; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    sumObject.image_data[i][j].colors[k] = image1.image_data[i][j].colors[k] + image2.image_data[i][j].colors[k];
                    if (sumObject.image_data[i][j].colors[k] > 255) /*checks if sum value bigger than 255, then assings 255. */
                        sumObject.image_data[i][j].colors[k] = 255;
                }
            }
        return sumObject;
    }
    for (int i = 0; i < image1.x; i++)
        for (int j = 0; j < image1.y; j++)
            for (int k = 0; k < 3; k++)
                sumObject.image_data[i][j].colors[k] = 0; /*if objects to be added are not same size, then assings 0 to pixels. */

    return sumObject; /*if size is not equal returns an object has first objects dimensions and 0 0 0 channels.*/
}

ppmImage operator-(const ppmImage &image1, const ppmImage &image2)
{
    ppmImage sumObject(image1.x, image1.y); /*creates an object with first objects dimensions*/

    if (image1.x == image2.x && image1.y == image2.y) // if sizes are equal.
    {
        for (int i = 0; i < image1.x; i++)
            for (int j = 0; j < image1.y; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    sumObject.image_data[i][j].colors[k] = image1.image_data[i][j].colors[k] - image2.image_data[i][j].colors[k]; /*assings the substraction of channels to new object channels*/
                    if (sumObject.image_data[i][j].colors[k] < 0)                                                                 /*checks if substraction result mines value, then assings 0. */
                        sumObject.image_data[i][j].colors[k] = 0;
                }
            }
        return sumObject;
    }
    for (int i = 0; i < image1.x; i++)
        for (int j = 0; j < image1.y; j++)
            for (int k = 0; k < 3; k++)
                sumObject.image_data[i][j].colors[k] = 0; /*if objects to be substract are not same size, then assings 0 to pixels. */

    return sumObject;
}

ostream &operator<<(ostream &term, ppmImage &obj)
{
    /*prints the headerpart first */
    cout << obj.header1 << endl;
    cout << obj.x << " " << obj.y << endl;
    cout << obj.max_color_value << endl;
    for (int i = 0; i < obj.x; i++)
    {
        for (int j = 0; j < obj.y; j++)
            cout << obj.image_data[i][j].colors[0] << " " << obj.image_data[i][j].colors[1] << " " << obj.image_data[i][j].colors[2] << " ";
        cout << endl;
    }
    return term; /*for another cout operation. For example, cout<<obj1<<endl;*/
}

int &ppmImage::operator()(int rowIndex, int colIndex, int color)
{
    if (color == 1)
        return image_data[rowIndex][colIndex].colors[0];
    if (color == 2)
        return image_data[rowIndex][colIndex].colors[1];

    return image_data[rowIndex][colIndex].colors[2];
}

/*Changes the channels according the choice.*/
int ppmImage::change_channels(int choice)
{
    if (choice != 1 && choice != 2 && choice != 3) /* if choice is not 1 or 2 or 3,nothing changes and return1 */
        return 1;
    int a = 0, b = 1; /*color indices intially swap red and green channels. */
    if (choice == 2)  /*changes indices to swap red and blue channels.*/
        b = 2;
    if (choice == 3) /*changes indices to swap green and blue channels.*/
    {
        a = 1;
        b = 2;
    }
    int temp;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
        {
            temp = (*this)(i, j, a + 1);
            (*this)(i, j, a + 1) = (*this)(i, j, b + 1);
            (*this)(i, j, b + 1) = temp;
        }
    return 1;
}
void ppmImage::singleColor(int choice)
{
    if (choice != 1 && choice != 2 && choice != 3) /* if choice is not 1 or 2 or 3,nothing changes and return1 */
        return;
    int a = 0, b = 1; /* color indices intially blue is preserved.*/
    if (choice == 1)  /*change indices to preserve red channels */
    {
        a = 1;
        b = 2;
    }
    if (choice == 2) /*change indices to preserve green channels*/
        b = 2;

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
        {
            (*this)(i, j, a + 1) = 0;
            (*this)(i, j, b + 1) = 0;
        }
}

int main(int argc, char **argv)
{
    if (argc >= 3 && argc <= 5)
    {
        string choice = argv[1];

        for (int i = 0; i < choice.length(); i++) /*Check each character of string parameter*/
            if (isdigit(choice[i]) == false)      /*if parameter is not digit, it gives a error message */
                return 0;

        if (choice == "1" && argc == 5)
        {
            test_addition(argv[2], argv[3], argv[4]);
        }
        else if (choice == "2" && argc == 5)
        {
            test_subtraction(argv[2], argv[3], argv[4]);
        }
        else if (choice == "3" && argc > 3) // optional file name 2 is necesseray, so it checks.
        {
            ppmImage destination_object(argv[2]);
            if (read_ppm(argv[2], destination_object))
            {
                swap_channels(destination_object, 2); /*calls the function to swap red and blue channels */
                write_ppm(argv[3], destination_object);
            }
        }
        else if (choice == "4" && argc > 3) // optional file_name_2 is necesseray, so it checks.
        {
            ppmImage destination_object(argv[2]);
            if (read_ppm(argv[2], destination_object))
            {
                swap_channels(destination_object, 3); /*calls the function to swap green and blue channels */
                write_ppm(argv[3], destination_object);
            }
        }
        else if (choice == "5" && argc > 3) // optional file_name_2 is necesseray ,so it checks.
        {
            ppmImage destination_object(argv[2]);
            if (read_ppm(argv[2], destination_object))
            {
                ppmImage newObj = single_color(destination_object, 1);
                write_ppm(argv[3], newObj);
            }
        }
        else if (choice == "6" && argc > 3) // optional file_name_2 is necesseray ,so it checks.
        {
            ppmImage destination_object(argv[2]);
            if (read_ppm(argv[2], destination_object))
            {
                ppmImage newObj = single_color(destination_object, 2);
                write_ppm(argv[3], newObj);
            }
        }
        else if (choice == "7" && argc > 3) // optional file_name_2 is necesseray ,so it checks.
        {
            ppmImage destination_object(argv[2]);
            if (read_ppm(argv[2], destination_object))
            {
                ppmImage newObj = single_color(destination_object, 3);
                write_ppm(argv[3], newObj);
            }
        }
    }
    return 0;
}

//=======================================STANDLONE FUNCTIONS===============================================================

int read_ppm(const string source_ppm_file_name, ppmImage &destination_object)
{
    return destination_object.read(source_ppm_file_name); /*calls member read function and returns member read functions returns value.*/
}

int write_ppm(const string destination_ppm_file_name, ppmImage &source_object)
{
    return source_object.save(destination_ppm_file_name); /*calls member save function and returns member save functions returns value.*/
}

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage image1(filename_image1), image2(filename_image2); /*creates new objects with file name.*/

    if (!read_ppm(filename_image1, image1) || !read_ppm(filename_image2, image2)) /*if one of the reading operation is not successfull,then returns 0*/
        return 0;

    ppmImage newObject = image1 + image2; /*Operator overloading.*/

    return write_ppm(filename_image3, newObject); /* if reading is successful, then returns write operation's status*/
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage image1(filename_image1), image2(filename_image2);
    if (!read_ppm(filename_image1, image1) || !read_ppm(filename_image2, image2)) /*if one of the reading operation is not successfull,then returns 0*/
        return 0;

    ppmImage newObject = image1 - image2;         /*Operator overloading.*/
    return write_ppm(filename_image3, newObject); /* if reading is successful, then returns write operation's status*/
}

int test_print(const string filename_image1)
{
    ppmImage image1(filename_image1);
    if (!read_ppm(filename_image1, image1)) /*if reading operation is not successfull,then returns 0*/
        return 0;
    cout << image1;
    return 1;
}

int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice)
{
    return image_object_to_be_modified.change_channels(swap_choice); /*calls member change_channels function and returns member change_channels functions returns value.*/
}

ppmImage single_color(const ppmImage &source, int color_choice)
{
    ppmImage copy = source; /*creates a new object and copies source object to copy object.*/
    copy.singleColor(color_choice);

    return copy;
}