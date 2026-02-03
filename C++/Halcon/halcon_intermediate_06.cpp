/*
 * Halcon Intermediate Program 6: OCR and Text Recognition
 * 
 * This program demonstrates:
 * - Optical Character Recognition (OCR)
 * - Text detection and segmentation
 * - Character recognition using different methods
 * - Text validation and filtering
 * 
 * Prerequisites: 
 * - Halcon license file
 * - OCR training data
 * 
 * Compilation: g++ -o halcon_intermediate_06 halcon_intermediate_06.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Intermediate Program 6: OCR and Text Recognition ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create an image with text
        HImage text_image;
        text_image.GenImageConst("byte", 400, 200);
        
        // Create text regions
        HImage pattern;
        pattern.GenImageConst("byte", 400, 200);
        pattern.PaintRegion(HRectangle2(0, 0, 0, 200, 400), 50);
        
        // Simulate text characters as rectangular regions
        // "HELLO" simulation
        pattern.PaintRegion(HRectangle2(50, 50, 0, 20, 15), 200);  // H
        pattern.PaintRegion(HRectangle2(50, 80, 0, 20, 15), 200);  // E
        pattern.PaintRegion(HRectangle2(50, 110, 0, 20, 15), 200); // L
        pattern.PaintRegion(HRectangle2(50, 140, 0, 20, 15), 200); // L
        pattern.PaintRegion(HRectangle2(50, 170, 0, 20, 15), 200); // O
        
        // "12345" simulation
        pattern.PaintRegion(HRectangle2(100, 50, 0, 20, 15), 200);  // 1
        pattern.PaintRegion(HRectangle2(100, 80, 0, 20, 15), 200);  // 2
        pattern.PaintRegion(HRectangle2(100, 110, 0, 20, 15), 200); // 3
        pattern.PaintRegion(HRectangle2(100, 140, 0, 20, 15), 200); // 4
        pattern.PaintRegion(HRectangle2(100, 170, 0, 20, 15), 200); // 5
        
        text_image = pattern;
        
        window.DispImage(text_image);
        cout << "Text image displayed" << endl;
        cin.get();
        
        // Create OCR classifier
        HTuple ocr_handle;
        CreateOcrClassKnn(HTuple("default"), HTuple("default"), &ocr_handle);
        
        cout << "OCR classifier created" << endl;
        
        // Segment text regions
        HRegionArray text_regions;
        text_regions.CharThreshold(text_image, HTuple("light"), HTuple("dark"), 
                                  HTuple("min_contrast"), HTuple(10), &text_regions);
        
        HTuple num_regions;
        num_regions = text_regions.CountObj();
        cout << "Found " << num_regions[0].I() << " text regions" << endl;
        
        window.ClearWindow();
        window.DispImage(text_image);
        window.SetColor("red");
        window.DispRegion(text_regions);
        cout << "Text regions displayed" << endl;
        cin.get();
        
        // Sort regions by position
        HRegionArray sorted_regions;
        sorted_regions.SortRegion(text_regions, "first_point", "true", "row");
        
        // Recognize characters
        cout << "Recognizing characters..." << endl;
        
        HTuple recognized_text;
        HTuple confidence;
        
        for (int i = 1; i <= num_regions[0].I(); i++) 
        {
            HRegion char_region;
            char_region.SelectObj(sorted_regions, i);
            
            HTuple char_text, char_confidence;
            try 
            {
                DoOcrSingleClassKnn(char_region, text_image, ocr_handle, 
                                   HTuple("default"), &char_text, &char_confidence);
                
                recognized_text.Append(char_text);
                confidence.Append(char_confidence);
                
                cout << "Character " << i << ": '" << char_text[0].S() 
                     << "' (confidence: " << char_confidence[0].D() << ")" << endl;
            }
            catch (HException& e)
            {
                cout << "Character " << i << ": recognition failed" << endl;
                recognized_text.Append(HTuple("?"));
                confidence.Append(HTuple(0.0));
            }
        }
        
        // Display recognition results
        cout << "Recognition results:" << endl;
        string full_text = "";
        for (int i = 0; i < recognized_text.Length(); i++) 
        {
            full_text += recognized_text[i].S();
        }
        cout << "Full text: '" << full_text << "'" << endl;
        
        // Filter results by confidence
        cout << "Filtering by confidence..." << endl;
        HTuple filtered_text;
        for (int i = 0; i < confidence.Length(); i++) 
        {
            if (confidence[i].D() > 0.5) 
            {
                filtered_text.Append(recognized_text[i]);
                cout << "High confidence: '" << recognized_text[i].S() << "'" << endl;
            }
        }
        
        // Demonstrate text validation
        cout << "Validating text patterns..." << endl;
        
        // Check for numeric pattern
        bool is_numeric = true;
        for (int i = 0; i < recognized_text.Length(); i++) 
        {
            string char_str = recognized_text[i].S();
            if (char_str.length() == 1 && 
                (char_str[0] < '0' || char_str[0] > '9')) 
            {
                is_numeric = false;
                break;
            }
        }
        
        if (is_numeric) 
        {
            cout << "Text appears to be numeric" << endl;
        }
        else 
        {
            cout << "Text appears to be alphanumeric" << endl;
        }
        
        // Clean up
        ClearOcrClassKnn(ocr_handle);
        
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
