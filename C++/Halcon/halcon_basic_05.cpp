/*
 * Halcon Beginner Program 5: Basic Geometric Operations
 * 
 * This program demonstrates:
 * - Image rotation and scaling
 * - Translation and affine transformations
 * - Image cropping and region of interest (ROI)
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_basic_05 halcon_basic_05.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Beginner Program 5: Basic Geometric Operations ===" << endl;
        
        // Create a window for displaying images
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Load an image
        HImage image;
        try 
        {
            image.ReadImage("test_image.jpg");
            cout << "Successfully loaded image: test_image.jpg" << endl;
        }
        catch (HException& e)
        {
            // Create a test pattern with geometric shapes
            cout << "No image file found, creating a test pattern with geometric shapes..." << endl;
            image.GenImageConst("byte", 400, 400);
            
            // Create a pattern with rectangles and circles
            HImage pattern;
            pattern.GenImageConst("byte", 400, 400);
            
            // Draw some shapes
            HTuple row1, col1, row2, col2;
            row1 = HTuple(50); col1 = HTuple(50); row2 = HTuple(150); col2 = HTuple(150);
            pattern.PaintRegion(HRectangle2(row1, col1, 0, row2-row1, col2-col1), 200);
            
            row1 = HTuple(200); col1 = HTuple(200); row2 = HTuple(300); col2 = HTuple(300);
            pattern.PaintRegion(HRectangle2(row1, col1, 0, row2-row1, col2-col1), 150);
            
            image = pattern;
        }
        
        // Get original image dimensions
        HTuple width, height;
        image.GetImageSize(&width, &height);
        cout << "Original image dimensions: " << width[0].I() << " x " << height[0].I() << " pixels" << endl;
        
        // Display original image
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // 1. Image rotation
        cout << "Applying image rotation..." << endl;
        HImage rotated;
        rotated.RotateImage(image, 45, "constant");  // Rotate 45 degrees
        cout << "Applied 45-degree rotation" << endl;
        
        window.ClearWindow();
        window.DispImage(rotated);
        cout << "Rotated image displayed" << endl;
        cin.get();
        
        // 2. Image scaling
        cout << "Applying image scaling..." << endl;
        HImage scaled;
        scaled.ZoomImageFactor(image, 0.5, 0.5, "constant");  // Scale to 50%
        cout << "Applied scaling (50%)" << endl;
        
        window.ClearWindow();
        window.DispImage(scaled);
        cout << "Scaled image displayed" << endl;
        cin.get();
        
        // 3. Image translation
        cout << "Applying image translation..." << endl;
        HImage translated;
        translated.MoveImage(image, 50, 50);  // Move by 50 pixels in x and y
        cout << "Applied translation (50, 50)" << endl;
        
        window.ClearWindow();
        window.DispImage(translated);
        cout << "Translated image displayed" << endl;
        cin.get();
        
        // 4. Affine transformation
        cout << "Applying affine transformation..." << endl;
        HImage affine_transformed;
        
        // Create a homogeneous transformation matrix
        HTuple hom_mat2d;
        hom_mat2d.HomMat2dIdentity();
        hom_mat2d.HomMat2dRotate(hom_mat2d, 30, 200, 200);  // Rotate 30 degrees around center
        hom_mat2d.HomMat2dTranslate(hom_mat2d, 30, 20);      // Translate
        
        affine_transformed.AffineTransImage(image, hom_mat2d, "constant", "false");
        cout << "Applied affine transformation (rotation + translation)" << endl;
        
        window.ClearWindow();
        window.DispImage(affine_transformed);
        cout << "Affine transformed image displayed" << endl;
        cin.get();
        
        // 5. Image cropping (Region of Interest)
        cout << "Applying image cropping..." << endl;
        HImage cropped;
        
        // Define a rectangular region of interest
        HTuple row1, col1, row2, col2;
        row1 = HTuple(width[0].I()/4);     // Start at 1/4 of width
        col1 = HTuple(height[0].I()/4);    // Start at 1/4 of height
        row2 = HTuple(3*width[0].I()/4);  // End at 3/4 of width
        col2 = HTuple(3*height[0].I()/4); // End at 3/4 of height
        
        cropped.CropRectangle1(image, row1, col1, row2, col2);
        cout << "Applied cropping (center 50% of image)" << endl;
        
        window.ClearWindow();
        window.DispImage(cropped);
        cout << "Cropped image displayed" << endl;
        cin.get();
        
        // 6. Image mirroring
        cout << "Applying image mirroring..." << endl;
        HImage mirrored_h, mirrored_v;
        
        // Horizontal mirroring
        mirrored_h.MirrorImage(image, "horizontal");
        cout << "Applied horizontal mirroring" << endl;
        
        window.ClearWindow();
        window.DispImage(mirrored_h);
        cout << "Horizontally mirrored image displayed" << endl;
        cin.get();
        
        // Vertical mirroring
        mirrored_v.MirrorImage(image, "vertical");
        cout << "Applied vertical mirroring" << endl;
        
        window.ClearWindow();
        window.DispImage(mirrored_v);
        cout << "Vertically mirrored image displayed" << endl;
        cin.get();
        
        // Clear the window
        window.ClearWindow();
        
        cout << "Program completed successfully!" << endl;
    }
    catch (HException& e)
    {
        cout << "Halcon Error: " << e.ErrorMessage() << endl;
        return -1;
    }
    catch (exception& e)
    {
        cout << "Standard Error: " << e.what() << endl;
        return -1;
    }
    
    return 0;
}
