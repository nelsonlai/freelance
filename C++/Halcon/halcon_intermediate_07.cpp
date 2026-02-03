/*
 * Halcon Intermediate Program 7: Image Registration and Alignment
 * 
 * This program demonstrates:
 * - Image registration using correlation
 * - Feature-based image alignment
 * - Multi-image stitching
 * - Image warping and transformation
 * 
 * Prerequisites: 
 * - Halcon license file
 * 
 * Compilation: g++ -o halcon_intermediate_07 halcon_intermediate_07.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Intermediate Program 7: Image Registration and Alignment ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create reference image
        HImage reference;
        reference.GenImageConst("byte", 300, 300);
        
        HImage ref_pattern;
        ref_pattern.GenImageConst("byte", 300, 300);
        ref_pattern.PaintRegion(HRectangle2(0, 0, 0, 300, 300), 100);
        
        // Add features to reference image
        ref_pattern.PaintRegion(HCircle(150, 150, 40), 200);
        ref_pattern.PaintRegion(HRectangle2(100, 100, 0, 50, 30), 180);
        ref_pattern.PaintRegion(HCircle(200, 200, 25), 160);
        
        reference = ref_pattern;
        
        // Create target image (shifted and slightly different)
        HImage target;
        target.GenImageConst("byte", 300, 300);
        
        HImage target_pattern;
        target_pattern.GenImageConst("byte", 300, 300);
        target_pattern.PaintRegion(HRectangle2(0, 0, 0, 300, 300), 100);
        
        // Add similar features but shifted
        target_pattern.PaintRegion(HCircle(160, 160, 40), 200);
        target_pattern.PaintRegion(HRectangle2(110, 110, 0, 50, 30), 180);
        target_pattern.PaintRegion(HCircle(210, 210, 25), 160);
        
        target = target_pattern;
        
        window.DispImage(reference);
        cout << "Reference image displayed" << endl;
        cin.get();
        
        window.ClearWindow();
        window.DispImage(target);
        cout << "Target image displayed" << endl;
        cin.get();
        
        // Image registration using correlation
        cout << "Performing image registration..." << endl;
        
        HTuple row, col, score;
        reference.BestMatch(target, 0.7, &row, &col, &score);
        
        cout << "Registration result:" << endl;
        cout << "Offset: (" << row[0].D() << ", " << col[0].D() << ")" << endl;
        cout << "Correlation score: " << score[0].D() << endl;
        
        // Apply registration
        HImage registered;
        HTuple hom_mat2d;
        hom_mat2d.HomMat2dIdentity();
        hom_mat2d.HomMat2dTranslate(hom_mat2d, -row[0].D(), -col[0].D());
        
        registered.AffineTransImage(target, hom_mat2d, "constant", "false");
        
        window.ClearWindow();
        window.DispImage(registered);
        cout << "Registered image displayed" << endl;
        cin.get();
        
        // Feature-based alignment
        cout << "Performing feature-based alignment..." << endl;
        
        // Extract features using corner detection
        HImage corners_ref, corners_target;
        corners_ref.HarrisResponse(reference, 3, 0.04, 0.0);
        corners_target.HarrisResponse(target, 3, 0.04, 0.0);
        
        // Find corresponding points
        HTuple points_ref_row, points_ref_col, points_target_row, points_target_col;
        try 
        {
            corners_ref.PointsHarris(3, 0.04, 0.0, 10, &points_ref_row, &points_ref_col);
            corners_target.PointsHarris(3, 0.04, 0.0, 10, &points_target_row, &points_target_col);
            
            cout << "Found " << points_ref_row.Length() << " reference points" << endl;
            cout << "Found " << points_target_row.Length() << " target points" << endl;
            
            // Display feature points
            window.ClearWindow();
            window.DispImage(reference);
            window.SetColor("red");
            for (int i = 0; i < points_ref_row.Length(); i++) 
            {
                window.DispCross(points_ref_row[i].D(), points_ref_col[i].D(), 5, 0);
            }
            cout << "Reference feature points displayed" << endl;
            cin.get();
            
            window.ClearWindow();
            window.DispImage(target);
            window.SetColor("green");
            for (int i = 0; i < points_target_row.Length(); i++) 
            {
                window.DispCross(points_target_row[i].D(), points_target_col[i].D(), 5, 0);
            }
            cout << "Target feature points displayed" << endl;
            cin.get();
        }
        catch (HException& e)
        {
            cout << "Feature detection failed: " << e.ErrorMessage() << endl;
        }
        
        // Image stitching demonstration
        cout << "Demonstrating image stitching..." << endl;
        
        // Create two overlapping images
        HImage image1, image2;
        image1.GenImageConst("byte", 200, 200);
        image2.GenImageConst("byte", 200, 200);
        
        HImage pattern1, pattern2;
        pattern1.GenImageConst("byte", 200, 200);
        pattern2.GenImageConst("byte", 200, 200);
        
        // Image 1
        pattern1.PaintRegion(HRectangle2(0, 0, 0, 200, 200), 50);
        pattern1.PaintRegion(HCircle(100, 100, 30), 200);
        pattern1.PaintRegion(HRectangle2(50, 50, 0, 40, 40), 150);
        
        // Image 2 (overlapping)
        pattern2.PaintRegion(HRectangle2(0, 0, 0, 200, 200), 50);
        pattern2.PaintRegion(HCircle(120, 120, 30), 200);
        pattern2.PaintRegion(HRectangle2(70, 70, 0, 40, 40), 150);
        
        image1 = pattern1;
        image2 = pattern2;
        
        window.ClearWindow();
        window.DispImage(image1);
        cout << "Image 1 displayed" << endl;
        cin.get();
        
        window.ClearWindow();
        window.DispImage(image2);
        cout << "Image 2 displayed" << endl;
        cin.get();
        
        // Simple stitching by overlapping
        HImage stitched;
        stitched.GenImageConst("byte", 300, 200);
        
        // Place image1
        HTuple hom_mat1;
        hom_mat1.HomMat2dIdentity();
        hom_mat1.HomMat2dTranslate(hom_mat1, 0, 0);
        
        HImage temp1;
        temp1.AffineTransImage(image1, hom_mat1, "constant", "false");
        
        // Place image2 with overlap
        HTuple hom_mat2;
        hom_mat2.HomMat2dIdentity();
        hom_mat2.HomMat2dTranslate(hom_mat2, 100, 0);
        
        HImage temp2;
        temp2.AffineTransImage(image2, hom_mat2, "constant", "false");
        
        // Blend images
        stitched.AddImage(temp1, temp2, &stitched);
        
        window.ClearWindow();
        window.DispImage(stitched);
        cout << "Stitched image displayed" << endl;
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
