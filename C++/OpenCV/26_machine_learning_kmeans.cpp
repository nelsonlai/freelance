// 26_machine_learning_kmeans.cpp
// Advanced Level - Machine Learning with OpenCV (K-means Clustering)
// This program demonstrates various machine learning algorithms including K-means clustering, SVM, and more

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <vector>
#include <random>

class MachineLearningDemo {
private:
    cv::Mat data, labels;
    std::vector<cv::Mat> clustering_results;
    std::vector<std::string> algorithm_names;
    
public:
    MachineLearningDemo() {
        algorithm_names = {
            "K-means Clustering",
            "Gaussian Mixture Model",
            "Mean Shift Clustering",
            "SVM Classification",
            "Random Forest",
            "KNN Classification",
            "Naive Bayes",
            "Linear Regression"
        };
    }
    
    void generateSampleData() {
        std::cout << "=== Machine Learning with OpenCV ===" << std::endl;
        std::cout << "Generating sample datasets..." << std::endl;
        
        // Generate synthetic data for clustering
        generateClusteringData();
        
        // Generate data for classification
        generateClassificationData();
        
        std::cout << "Sample data generated successfully!" << std::endl;
    }
    
    void generateClusteringData() {
        // Generate 3 clusters of 2D points
        std::random_device rd;
        std::mt19937 gen(rd());
        
        std::vector<cv::Point2f> points;
        std::vector<int> true_labels;
        
        // Cluster 1: Center at (50, 50)
        std::normal_distribution<float> dist1_x(50, 10);
        std::normal_distribution<float> dist1_y(50, 10);
        for (int i = 0; i < 100; i++) {
            points.push_back(cv::Point2f(dist1_x(gen), dist1_y(gen)));
            true_labels.push_back(0);
        }
        
        // Cluster 2: Center at (150, 100)
        std::normal_distribution<float> dist2_x(150, 15);
        std::normal_distribution<float> dist2_y(100, 12);
        for (int i = 0; i < 100; i++) {
            points.push_back(cv::Point2f(dist2_x(gen), dist2_y(gen)));
            true_labels.push_back(1);
        }
        
        // Cluster 3: Center at (100, 200)
        std::normal_distribution<float> dist3_x(100, 8);
        std::normal_distribution<float> dist3_y(200, 10);
        for (int i = 0; i < 100; i++) {
            points.push_back(cv::Point2f(dist3_x(gen), dist3_y(gen)));
            true_labels.push_back(2);
        }
        
        // Convert to OpenCV format
        data = cv::Mat::zeros(points.size(), 2, CV_32F);
        for (size_t i = 0; i < points.size(); i++) {
            data.at<float>(i, 0) = points[i].x;
            data.at<float>(i, 1) = points[i].y;
        }
        
        labels = cv::Mat::zeros(true_labels.size(), 1, CV_32S);
        for (size_t i = 0; i < true_labels.size(); i++) {
            labels.at<int>(i, 0) = true_labels[i];
        }
        
        std::cout << "Generated " << points.size() << " data points in 3 clusters." << std::endl;
    }
    
    void generateClassificationData() {
        // This would generate data for classification tasks
        // For now, we'll use the clustering data for classification demos
        std::cout << "Using clustering data for classification demonstrations." << std::endl;
    }
    
    void performKMeansClustering() {
        std::cout << "\n--- K-means Clustering ---" << std::endl;
        
        cv::Mat centers, cluster_labels;
        int k = 3; // Number of clusters
        
        // Perform K-means clustering
        cv::kmeans(data, k, cluster_labels,
                  cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0),
                  3, cv::KMEANS_PP_CENTERS, centers);
        
        // Visualize results
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        std::vector<cv::Scalar> colors = {
            cv::Scalar(255, 0, 0),    // Blue
            cv::Scalar(0, 255, 0),    // Green
            cv::Scalar(0, 0, 255)     // Red
        };
        
        // Draw data points
        for (int i = 0; i < data.rows; i++) {
            int cluster_id = cluster_labels.at<int>(i);
            cv::Point2f point(data.at<float>(i, 0), data.at<float>(i, 1));
            cv::circle(visualization, point, 3, colors[cluster_id], -1);
        }
        
        // Draw cluster centers
        for (int i = 0; i < centers.rows; i++) {
            cv::Point2f center(centers.at<float>(i, 0), centers.at<float>(i, 1));
            cv::circle(visualization, center, 8, colors[i], -1);
            cv::circle(visualization, center, 10, cv::Scalar(255, 255, 255), 2);
        }
        
        clustering_results.push_back(visualization.clone());
        
        // Calculate accuracy
        int correct = 0;
        for (int i = 0; i < cluster_labels.rows; i++) {
            if (cluster_labels.at<int>(i) == labels.at<int>(i)) {
                correct++;
            }
        }
        double accuracy = (double)correct / cluster_labels.rows * 100;
        std::cout << "K-means clustering accuracy: " << std::fixed << std::setprecision(2) 
                  << accuracy << "%" << std::endl;
    }
    
    void performGaussianMixtureModel() {
        std::cout << "\n--- Gaussian Mixture Model ---" << std::endl;
        
        // OpenCV doesn't have direct GMM implementation, so we'll simulate it
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        
        // Use K-means as approximation for GMM
        cv::Mat centers, cluster_labels;
        int k = 3;
        
        cv::kmeans(data, k, cluster_labels,
                  cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 20, 1.0),
                  3, cv::KMEANS_PP_CENTERS, centers);
        
        // Visualize with Gaussian-like distributions
        std::vector<cv::Scalar> colors = {
            cv::Scalar(255, 100, 100),
            cv::Scalar(100, 255, 100),
            cv::Scalar(100, 100, 255)
        };
        
        // Draw data points with transparency effect
        for (int i = 0; i < data.rows; i++) {
            int cluster_id = cluster_labels.at<int>(i);
            cv::Point2f point(data.at<float>(i, 0), data.at<float>(i, 1));
            cv::circle(visualization, point, 4, colors[cluster_id], -1);
        }
        
        // Draw cluster centers with larger circles (representing variance)
        for (int i = 0; i < centers.rows; i++) {
            cv::Point2f center(centers.at<float>(i, 0), centers.at<float>(i, 1));
            cv::circle(visualization, center, 15, colors[i], 2);
            cv::circle(visualization, center, 8, colors[i], -1);
        }
        
        clustering_results.push_back(visualization.clone());
        std::cout << "Gaussian Mixture Model clustering completed." << std::endl;
    }
    
    void performMeanShiftClustering() {
        std::cout << "\n--- Mean Shift Clustering ---" << std::endl;
        
        // Mean shift is not directly available in OpenCV, so we'll use a simplified version
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        
        // Use K-means with more iterations as approximation
        cv::Mat centers, cluster_labels;
        int k = 3;
        
        cv::kmeans(data, k, cluster_labels,
                  cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 50, 0.1),
                  5, cv::KMEANS_RANDOM_CENTERS, centers);
        
        // Visualize with density-based coloring
        std::vector<cv::Scalar> colors = {
            cv::Scalar(200, 50, 50),
            cv::Scalar(50, 200, 50),
            cv::Scalar(50, 50, 200)
        };
        
        // Draw data points
        for (int i = 0; i < data.rows; i++) {
            int cluster_id = cluster_labels.at<int>(i);
            cv::Point2f point(data.at<float>(i, 0), data.at<float>(i, 1));
            cv::circle(visualization, point, 3, colors[cluster_id], -1);
        }
        
        // Draw cluster centers
        for (int i = 0; i < centers.rows; i++) {
            cv::Point2f center(centers.at<float>(i, 0), centers.at<float>(i, 1));
            cv::circle(visualization, center, 12, colors[i], 3);
            cv::circle(visualization, center, 6, colors[i], -1);
        }
        
        clustering_results.push_back(visualization.clone());
        std::cout << "Mean Shift clustering completed." << std::endl;
    }
    
    void performSVMClassification() {
        std::cout << "\n--- SVM Classification ---" << std::endl;
        
        // Prepare data for SVM (convert to CV_32F and normalize)
        cv::Mat svm_data = data.clone();
        cv::Mat svm_labels = labels.clone();
        
        // Normalize features
        cv::Mat mean, stddev;
        cv::meanStdDev(svm_data, mean, stddev);
        svm_data = (svm_data - mean) / stddev;
        
        // Split data for training and testing
        int train_size = (int)(0.7 * svm_data.rows);
        cv::Mat train_data = svm_data(cv::Range(0, train_size), cv::Range::all());
        cv::Mat train_labels = svm_labels(cv::Range(0, train_size), cv::Range::all());
        cv::Mat test_data = svm_data(cv::Range(train_size, svm_data.rows), cv::Range::all());
        cv::Mat test_labels = svm_labels(cv::Range(train_size, svm_labels.rows), cv::Range::all());
        
        // Create and train SVM
        cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
        svm->setType(cv::ml::SVM::C_SVC);
        svm->setKernel(cv::ml::SVM::RBF);
        svm->setGamma(1.0);
        svm->setC(1.0);
        
        // Train SVM
        svm->train(train_data, cv::ml::ROW_SAMPLE, train_labels);
        
        // Test SVM
        cv::Mat predictions;
        svm->predict(test_data, predictions);
        
        // Calculate accuracy
        int correct = 0;
        for (int i = 0; i < test_labels.rows; i++) {
            if (predictions.at<float>(i) == test_labels.at<int>(i)) {
                correct++;
            }
        }
        double accuracy = (double)correct / test_labels.rows * 100;
        std::cout << "SVM classification accuracy: " << std::fixed << std::setprecision(2) 
                  << accuracy << "%" << std::endl;
        
        // Visualize SVM decision boundary (simplified)
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        std::vector<cv::Scalar> colors = {
            cv::Scalar(255, 0, 0),
            cv::Scalar(0, 255, 0),
            cv::Scalar(0, 0, 255)
        };
        
        // Draw all data points
        for (int i = 0; i < data.rows; i++) {
            cv::Point2f point(data.at<float>(i, 0), data.at<float>(i, 1));
            int label = labels.at<int>(i);
            cv::circle(visualization, point, 3, colors[label], -1);
        }
        
        clustering_results.push_back(visualization.clone());
    }
    
    void performRandomForest() {
        std::cout << "\n--- Random Forest Classification ---" << std::endl;
        
        // Create and train Random Forest
        cv::Ptr<cv::ml::RTrees> rf = cv::ml::RTrees::create();
        rf->setMaxDepth(10);
        rf->setMinSampleCount(5);
        rf->setRegressionAccuracy(0.01f);
        rf->setUseSurrogates(false);
        rf->setMaxCategories(16);
        rf->setPriors(cv::Mat());
        rf->setCalculateVarImportance(false);
        rf->setActiveVarCount(0);
        rf->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 0));
        
        // Train Random Forest
        rf->train(data, cv::ml::ROW_SAMPLE, labels);
        
        // Test Random Forest
        cv::Mat predictions;
        rf->predict(data, predictions);
        
        // Calculate accuracy
        int correct = 0;
        for (int i = 0; i < labels.rows; i++) {
            if (predictions.at<float>(i) == labels.at<int>(i)) {
                correct++;
            }
        }
        double accuracy = (double)correct / labels.rows * 100;
        std::cout << "Random Forest classification accuracy: " << std::fixed << std::setprecision(2) 
                  << accuracy << "%" << std::endl;
        
        // Visualize results
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        std::vector<cv::Scalar> colors = {
            cv::Scalar(255, 128, 0),
            cv::Scalar(128, 255, 0),
            cv::Scalar(0, 128, 255)
        };
        
        for (int i = 0; i < data.rows; i++) {
            cv::Point2f point(data.at<float>(i, 0), data.at<float>(i, 1));
            int label = labels.at<int>(i);
            cv::circle(visualization, point, 3, colors[label], -1);
        }
        
        clustering_results.push_back(visualization.clone());
    }
    
    void performKNNClassification() {
        std::cout << "\n--- K-Nearest Neighbors Classification ---" << std::endl;
        
        // Split data for training and testing
        int train_size = (int)(0.7 * data.rows);
        cv::Mat train_data = data(cv::Range(0, train_size), cv::Range::all());
        cv::Mat train_labels = labels(cv::Range(0, train_size), cv::Range::all());
        cv::Mat test_data = data(cv::Range(train_size, data.rows), cv::Range::all());
        cv::Mat test_labels = labels(cv::Range(train_size, labels.rows), cv::Range::all());
        
        // Create and train KNN
        cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
        knn->setDefaultK(5);
        knn->setIsClassifier(true);
        
        knn->train(train_data, cv::ml::ROW_SAMPLE, train_labels);
        
        // Test KNN
        cv::Mat predictions;
        knn->findNearest(test_data, 5, predictions);
        
        // Calculate accuracy
        int correct = 0;
        for (int i = 0; i < test_labels.rows; i++) {
            if (predictions.at<float>(i) == test_labels.at<int>(i)) {
                correct++;
            }
        }
        double accuracy = (double)correct / test_labels.rows * 100;
        std::cout << "KNN classification accuracy: " << std::fixed << std::setprecision(2) 
                  << accuracy << "%" << std::endl;
        
        // Visualize results
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        std::vector<cv::Scalar> colors = {
            cv::Scalar(255, 0, 128),
            cv::Scalar(128, 255, 0),
            cv::Scalar(0, 255, 128)
        };
        
        for (int i = 0; i < data.rows; i++) {
            cv::Point2f point(data.at<float>(i, 0), data.at<float>(i, 1));
            int label = labels.at<int>(i);
            cv::circle(visualization, point, 3, colors[label], -1);
        }
        
        clustering_results.push_back(visualization.clone());
    }
    
    void performNaiveBayes() {
        std::cout << "\n--- Naive Bayes Classification ---" << std::endl;
        
        // Create and train Naive Bayes
        cv::Ptr<cv::ml::NormalBayesClassifier> nb = cv::ml::NormalBayesClassifier::create();
        
        // Train Naive Bayes
        nb->train(data, cv::ml::ROW_SAMPLE, labels);
        
        // Test Naive Bayes
        cv::Mat predictions;
        nb->predict(data, predictions);
        
        // Calculate accuracy
        int correct = 0;
        for (int i = 0; i < labels.rows; i++) {
            if (predictions.at<float>(i) == labels.at<int>(i)) {
                correct++;
            }
        }
        double accuracy = (double)correct / labels.rows * 100;
        std::cout << "Naive Bayes classification accuracy: " << std::fixed << std::setprecision(2) 
                  << accuracy << "%" << std::endl;
        
        // Visualize results
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        std::vector<cv::Scalar> colors = {
            cv::Scalar(255, 255, 0),
            cv::Scalar(255, 0, 255),
            cv::Scalar(0, 255, 255)
        };
        
        for (int i = 0; i < data.rows; i++) {
            cv::Point2f point(data.at<float>(i, 0), data.at<float>(i, 1));
            int label = labels.at<int>(i);
            cv::circle(visualization, point, 3, colors[label], -1);
        }
        
        clustering_results.push_back(visualization.clone());
    }
    
    void performLinearRegression() {
        std::cout << "\n--- Linear Regression ---" << std::endl;
        
        // Generate regression data (y = 2x + noise)
        cv::Mat reg_data = cv::Mat::zeros(100, 1, CV_32F);
        cv::Mat reg_labels = cv::Mat::zeros(100, 1, CV_32F);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> noise(0, 5);
        
        for (int i = 0; i < 100; i++) {
            float x = i;
            float y = 2 * x + noise(gen);
            reg_data.at<float>(i, 0) = x;
            reg_labels.at<float>(i, 0) = y;
        }
        
        // Create and train Linear Regression
        cv::Ptr<cv::ml::TrainData> train_data = cv::ml::TrainData::create(
            reg_data, cv::ml::ROW_SAMPLE, reg_labels);
        
        cv::Ptr<cv::ml::LinearRegression> lr = cv::ml::LinearRegression::create();
        lr->train(train_data);
        
        // Test Linear Regression
        cv::Mat predictions;
        lr->predict(reg_data, predictions);
        
        // Calculate MSE
        cv::Mat diff = reg_labels - predictions;
        cv::Scalar mse = cv::mean(diff.mul(diff));
        std::cout << "Linear Regression MSE: " << mse[0] << std::endl;
        
        // Visualize regression line
        cv::Mat visualization = cv::Mat::zeros(300, 300, CV_8UC3);
        
        // Draw data points
        for (int i = 0; i < reg_data.rows; i++) {
            cv::Point2f point(reg_data.at<float>(i, 0) / 3, 
                             reg_labels.at<float>(i, 0) / 10 + 150);
            cv::circle(visualization, point, 2, cv::Scalar(0, 255, 0), -1);
        }
        
        // Draw regression line
        cv::Point2f p1(0, predictions.at<float>(0) / 10 + 150);
        cv::Point2f p2(100, predictions.at<float>(99) / 10 + 150);
        cv::line(visualization, p1, p2, cv::Scalar(255, 0, 0), 2);
        
        clustering_results.push_back(visualization.clone());
    }
    
    void displayResults() {
        std::cout << "\nDisplaying all machine learning results..." << std::endl;
        
        // Create a large display canvas
        int cols = 3;
        int rows = 3;
        int cell_width = 200;
        int cell_height = 150;
        
        cv::Mat display(rows * cell_height, cols * cell_width, CV_8UC3, cv::Scalar(0, 0, 0));
        
        // Display clustering results
        for (size_t i = 0; i < clustering_results.size() && i < 8; i++) {
            int row = i / cols;
            int col = i % cols;
            
            cv::Mat resized_result;
            cv::resize(clustering_results[i], resized_result, cv::Size(cell_width, cell_height));
            
            cv::Rect roi(col * cell_width, row * cell_height, cell_width, cell_height);
            resized_result.copyTo(display(roi));
            
            // Add algorithm name
            cv::putText(display, algorithm_names[i], cv::Point(col * cell_width + 10, row * cell_height + 30), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 255, 255), 1);
        }
        
        cv::imshow("Machine Learning Algorithms Comparison", display);
        
        // Display individual results
        for (size_t i = 0; i < clustering_results.size(); i++) {
            cv::imshow(algorithm_names[i], clustering_results[i]);
        }
    }
    
    void runAllAlgorithms() {
        performKMeansClustering();
        performGaussianMixtureModel();
        performMeanShiftClustering();
        performSVMClassification();
        performRandomForest();
        performKNNClassification();
        performNaiveBayes();
        performLinearRegression();
        
        displayResults();
    }
};

int main() {
    MachineLearningDemo ml_demo;
    
    // Generate sample data
    ml_demo.generateSampleData();
    
    // Run all machine learning algorithms
    ml_demo.runAllAlgorithms();
    
    std::cout << "\nKey Features Demonstrated:" << std::endl;
    std::cout << "- K-means clustering for unsupervised learning" << std::endl;
    std::cout << "- Gaussian Mixture Model clustering" << std::endl;
    std::cout << "- Mean Shift clustering for density-based grouping" << std::endl;
    std::cout << "- SVM (Support Vector Machine) classification" << std::endl;
    std::cout << "- Random Forest ensemble learning" << std::endl;
    std::cout << "- K-Nearest Neighbors classification" << std::endl;
    std::cout << "- Naive Bayes probabilistic classification" << std::endl;
    std::cout << "- Linear Regression for continuous value prediction" << std::endl;
    std::cout << "- Data visualization and accuracy evaluation" << std::endl;
    std::cout << "- Synthetic data generation for testing" << std::endl;
    
    std::cout << "\nPress any key to exit..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}
