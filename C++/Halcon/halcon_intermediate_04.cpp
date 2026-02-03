/*
 * Halcon Intermediate Program 4: Blob Analysis and Feature Extraction
 * 
 * This program demonstrates:
 * - Blob detection and analysis
 * - Feature extraction from regions
 * - Object classification based on features
 * - Contour analysis
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_intermediate_04 halcon_intermediate_04.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Intermediate Program 4: Blob Analysis and Feature Extraction ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        HImage image;
        try 
        {
            image.ReadImage("test_image.jpg");
            cout << "Loaded image: test_image.jpg" << endl;
        }
        catch (HException& e)
        {
            cout << "Creating test pattern..." << endl;
            image.GenImageConst("byte", 400, 400);
            
            HImage pattern;
            pattern.GenImageConst("byte", 400, 400);
            pattern.PaintRegion(HRectangle2(0, 0, 0, 400, 400), 50);
            
            // Create different shaped blobs
            pattern.PaintRegion(HCircle(100, 100, 40), 200);
            pattern.PaintRegion(HRectangle2(200, 200, 0, 80, 60), 180);
            pattern.PaintRegion(HCircle(300, 150, 30), 190);
            pattern.PaintRegion(HRectangle2(150, 300, 45, 70, 50), 170);
            
            image = pattern;
        }
        
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // Threshold and find blobs
        HRegionArray blobs;
        blobs.BinaryThreshold(image, "max_separability", "light", &blobs);
        
        HTuple num_blobs;
        num_blobs = blobs.CountObj();
        cout << "Found " << num_blobs[0].I() << " blobs" << endl;
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("red");
        window.DispRegion(blobs);
        cout << "Blobs displayed" << endl;
        cin.get();
        
        // Extract features for each blob
        cout << "Extracting features..." << endl;
        
        for (int i = 1; i <= num_blobs[0].I(); i++) 
        {
            HRegion blob;
            blob.SelectObj(blobs, i);
            
            HTuple area, row_center, col_center;
            blob.AreaCenter(&area, &row_center, &col_center);
            
            HTuple circularity, compactness;
            blob.Circularity(&circularity);
            blob.Compactness(&compactness);
            
            HTuple orientation, major_axis, minor_axis;
            blob.OrientationRegion(&orientation);
            blob.EllipticAxis(blob, &major_axis, &minor_axis);
            
            cout << "Blob " << i << ":" << endl;
            cout << "  Area: " << area[0].I() << endl;
            cout << "  Center: (" << row_center[0].D() << ", " << col_center[0].D() << ")" << endl;
            cout << "  Circularity: " << circularity[0].D() << endl;
            cout << "  Compactness: " << compactness[0].D() << endl;
            cout << "  Orientation: " << orientation[0].D() << " rad" << endl;
            cout << "  Major axis: " << major_axis[0].D() << endl;
            cout << "  Minor axis: " << minor_axis[0].D() << endl;
        }
        
        // Classify blobs based on features
        cout << "Classifying blobs..." << endl;
        
        HRegionArray circles, rectangles;
        
        for (int i = 1; i <= num_blobs[0].I(); i++) 
        {
            HRegion blob;
            blob.SelectObj(blobs, i);
            
            HTuple circularity;
            blob.Circularity(&circularity);
            
            if (circularity[0].D() > 0.8) 
            {
                circles.Append(blob);
                cout << "Blob " << i << " classified as circle" << endl;
            }
            else 
            {
                rectangles.Append(blob);
                cout << "Blob " << i << " classified as rectangle" << endl;
            }
        }
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("green");
        window.DispRegion(circles);
        window.SetColor("blue");
        window.DispRegion(rectangles);
        cout << "Classification: green=circles, blue=rectangles" << endl;
        cin.get();
        
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
