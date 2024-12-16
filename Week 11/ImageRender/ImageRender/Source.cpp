#include <iostream> // This is used to print things on screen / streams
#include <fstream> // This is used to read from / write to files
#include <string> // To use strings
using namespace std;

int flipX(string filename) {
    ifstream img_file; // `ifstream` by default reads a file;
    img_file.open(filename, ios::in);
    int i = 0; // This is a line counter
    string line; // This will keep each line of the file
    while (img_file >> line) {
        // Parse the contents of the file!
    }
}

int main() {
    // Image width and height in pixels
    int image_width = 256;
    int image_height = 256;

    // Render the image (into a file, eventually)
    string ppm_contents = "P3\n" + to_string(image_width) + ' ' + to_string(image_height) + "\n255\n";
    /* Format:

    ```ppm
    P3
    <width> <height>
    <max colors>
    ```

    In the above, width and height are the image width and height in pixels and <max colors> is the
    maximum value for our RGB values within each pixel.
    */

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            // RGB values as floats numbers in [0,1]
            double r = 0.0;
            double g = double(i) / (image_height - 1); // `-1` since i <- {0,1,...,255}
            double b = double(j) / (image_width - 1);
            /*
            * Rescaling to 255 * 255:
            * Assume you have an image with dimensions 1080 * 1080.
            * Then, i, j might range in {0,1,...,1079}.
            * To rescale them to an integer in {0,1,...,255} we can work as follows:
            *   1. Divide i by 1079, so i / 1079 is a float in [0,1]
            *   2. Multiply by 255, so int(i / 1079 * 255) is an int in {0,...,255}
            */

            // Integer RGB values, in {0,1,...,255}
            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            /*
            * Old version:
            * 
            * ```cpp
            * int ir = int(255 * r); // This might not always work as expected;
            * int ig = int(255 * g); // This might not always work as expected;
            * int ib = int(255 * b); // This might not always work as expected;
            * ```
            * 
            * In the above, the only case a pixel gets 255 in some colour is if
            * `r` or `g` or `b` is exactly `1.0`. For all other values in {0,1,...,254}
            * we have more than one values of `r`, `g`, `b` where they might appear.
            * For example, for `r == 0.0`, then `ir == int(255 * 0) == 0`.
            * However, also for `r == 0.0038`, then `ir == int(255 * 0.0038) == 0`.
            */

            ppm_contents += to_string(ir) + ' ' + to_string(ig) + ' ' + to_string(ib) + '\n';
        }
    }

    // Write the image string into a file
    // string CWD = "C:\\Users\\MC\\Documents\\Courses\\Virtual Environment Development\\Week 10\\source";
    // string CWD = filesystem::();
    ofstream img_file; // Declare a file stream variable
    img_file.open("sample_001.ppm", ios::out); // Open a file stream, i.e., open a file
    img_file << ppm_contents; // Write contents to the file
    img_file.close(); // Close the file
    /*
    `fstream` offers access to both `ofstream` (output) and `ifstream` (input).
    When we declare a stream as `ofstream` we can write to that file by default (`ios::out`)
    When we declare a stream as `ifstream` we can write to that file by default (`ios::in`)
    */
    return 0;
}