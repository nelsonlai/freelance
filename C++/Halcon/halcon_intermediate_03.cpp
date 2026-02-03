/*
 * Halcon Intermediate Program 3: Template Matching and Object Detection
 * 
 * This program demonstrates:
 * - Template matching using normalized cross correlation
 * - Shape-based template matching
 * - Multi-scale template matching
 * - Robust template matching with rotation and scale
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_intermediate_03 halcon_intermediate_03.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Intermediate Program 3: Template Matching and Object Detection ===" << endl;
        
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
            // Create a test image with multiple objects
            cout << "No image file found, creating a test image with multiple objects..." << endl;
            image.GenImageConst("byte", 500, 500);
            
            // Create background
            HImage pattern;
            pattern.GenImageConst("byte", 500, 500);
            pattern.PaintRegion(HRectangle2(0, 0, 0, 500, 500), 100);
            
            // Create multiple objects (rectangles and circles)
            // Object 1 - Rectangle
            pattern.PaintRegion(HRectangle2(100, 100, 0, 80, 60), 200);
            
            // Object 2 - Circle
            pattern.PaintRegion(HCircle(200, 300, 40), 180);
            
            // Object 3 - Rectangle (rotated)
            pattern.PaintRegion(HRectangle2(300, 150, 45, 70, 50), 190);
            
            // Object 4 - Circle (different size)
            pattern.PaintRegion(HCircle(400, 400, 30), 170);
            
            // Add some noise
            HImage noise;
            noise.GenImageConst("byte", 500, 500);
            noise.AddNoiseWhiteContourXld(noise, 0.03);  // 3% noise
            pattern.AddImage(pattern, noise, &pattern);
            
            image = pattern;
        }
        
        // Display original image
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // 1. Create templates from the image
        cout << "Creating templates for matching..." << endl;
        
        // Extract template 1 (rectangle)
        HImage template1;
        template1.CropRectangle1(image, 100, 100, 180, 160);
        cout << "Created template 1 (rectangle)" << endl;
        
        // Extract template 2 (circle)
        HImage template2;
        template2.CropRectangle1(image, 160, 260, 240, 340);
        cout << "Created template 2 (circle)" << endl;
        
        // Display templates
        window.ClearWindow();
        window.DispImage(template1);
        cout << "Template 1 displayed" << endl;
        cin.get();
        
        window.ClearWindow();
        window.DispImage(template2);
        cout << "Template 2 displayed" << endl;
        cin.get();
        
        // 2. Normalized Cross Correlation (NCC) matching
        cout << "Performing NCC template matching..." << endl;
        
        HTuple row1, col1, score1;
        template1.BestMatchNcc(image, 0.7, 0, &row1, &col1, &score1);
        
        cout << "NCC matching results:" << endl;
        cout << "Template 1 - Best match at (" << row1[0].D() << ", " << col1[0].D() 
             << ") with score " << score1[0].D() << endl;
        
        // Display NCC result
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("red");
        window.DispCross(row1[0].D(), col1[0].D(), 20, 0);
        cout << "NCC match displayed (red cross)" << endl;
        cin.get();
        
        // 3. Multi-scale template matching
        cout << "Performing multi-scale template matching..." << endl;
        
        HTuple scales;
        scales = HTuple(0.8, 1.0, 1.2);  // Different scales
        
        HTuple best_row, best_col, best_scale, best_score;
        best_score = HTuple(0.0);
        
        for (int i = 0; i < scales.Length(); i++) 
        {
            // Scale the template
            HImage scaled_template;
            scaled_template.ZoomImageFactor(template1, scales[i].D(), scales[i].D(), "constant");
            
            // Match scaled template
            HTuple row, col, score;
            try 
            {
                scaled_template.BestMatchNcc(image, 0.6, 0, &row, &col, &score);
                
                if (score[0].D() > best_score[0].D()) 
                {
                    best_row = row;
                    best_col = col;
                    best_scale = scales[i];
                    best_score = score;
                }
                
                cout << "Scale " << scales[i].D() << ": match at (" << row[0].D() << ", " 
                     << col[0].D() << ") with score " << score[0].D() << endl;
            }
            catch (HException& e)
            {
                cout << "No match found for scale " << scales[i].D() << endl;
            }
        }
        
        cout << "Best multi-scale match: scale=" << best_scale[0].D() 
             << ", position=(" << best_row[0].D() << ", " << best_col[0].D() 
             << "), score=" << best_score[0].D() << endl;
        
        // Display multi-scale result
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("green");
        window.DispCross(best_row[0].D(), best_col[0].D(), 25, 0);
        cout << "Multi-scale match displayed (green cross)" << endl;
        cin.get();
        
        // 4. Shape-based template matching
        cout << "Performing shape-based template matching..." << endl;
        
        // Create shape model from template
        HTuple model_id;
        template1.CreateShapeModel(HTuple("auto"), HTuple(-0.39), HTuple(0.79), 
                                  HTuple("auto"), HTuple("auto"), HTuple("use_polarity"), 
                                  HTuple("auto"), HTuple("auto"), &model_id);
        
        // Find matches
        HTuple match_row, match_col, match_angle, match_score;
        template1.FindShapeModel(image, model_id, HTuple(-0.39), HTuple(0.79), 
                                0.7, 1, 0.5, HTuple("least_squares"), 
                                HTuple(0), HTuple(0.9), &match_row, &match_col, 
                                &match_angle, &match_score);
        
        cout << "Shape-based matching found " << match_row.Length() << " matches" << endl;
        
        // Display shape-based matches
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("blue");
        for (int i = 0; i < match_row.Length(); i++) 
        {
            window.DispCross(match_row[i].D(), match_col[i].D(), 15, 0);
            cout << "Match " << i+1 << ": (" << match_row[i].D() << ", " 
                 << match_col[i].D() << "), angle=" << match_angle[i].D() 
                 << ", score=" << match_score[i].D() << endl;
        }
        cout << "Shape-based matches displayed (blue crosses)" << endl;
        cin.get();
        
        // 5. Robust template matching with rotation
        cout << "Performing robust template matching with rotation..." << endl;
        
        // Create a more robust model with rotation tolerance
        HTuple robust_model_id;
        template2.CreateShapeModel(HTuple("auto"), HTuple(-1.57), HTuple(1.57), 
                                  HTuple("auto"), HTuple("auto"), HTuple("use_polarity"), 
                                  HTuple("auto"), HTuple("auto"), &robust_model_id);
        
        // Find matches with rotation
        HTuple robust_row, robust_col, robust_angle, robust_score;
        template2.FindShapeModel(image, robust_model_id, HTuple(-1.57), HTuple(1.57), 
                                0.6, 1, 0.5, HTuple("least_squares"), 
                                HTuple(0), HTuple(0.8), &robust_row, &robust_col, 
                                &robust_angle, &robust_score);
        
        cout << "Robust matching found " << robust_row.Length() << " matches" << endl;
        
        // Display robust matches
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("yellow");
        for (int i = 0; i < robust_row.Length(); i++) 
        {
            window.DispCross(robust_row[i].D(), robust_col[i].D(), 20, 0);
            cout << "Robust match " << i+1 << ": (" << robust_row[i].D() << ", " 
                 << robust_col[i].D() << "), angle=" << robust_angle[i].D() 
                 << ", score=" << robust_score[i].D() << endl;
        }
        cout << "Robust matches displayed (yellow crosses)" << endl;
        cin.get();
        
        // 6. Template matching with subpixel accuracy
        cout << "Performing subpixel template matching..." << endl;
        
        HTuple subpixel_row, subpixel_col, subpixel_score;
        template1.BestMatchNcc(image, 0.5, 0, &subpixel_row, &subpixel_col, &subpixel_score);
        
        cout << "Subpixel match: (" << subpixel_row[0].D() << ", " 
             << subpixel_col[0].D() << ") with score " << subpixel_score[0].D() << endl;
        
        // Display subpixel result
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("cyan");
        window.DispCross(subpixel_row[0].D(), subpixel_col[0].D(), 30, 0);
        cout << "Subpixel match displayed (cyan cross)" << endl;
        cin.get();
        
        // Clean up models
        ClearShapeModel(model_id);
        ClearShapeModel(robust_model_id);
        
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
