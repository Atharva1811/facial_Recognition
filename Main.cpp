#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    CascadeClassifier faceCascade;
    faceCascade.load("path/to/haarcascade_frontalface_default.xml");

    VideoCapture capture(0); // Open the default camera (change if needed)

    if (!capture.isOpened()) {
        cout << "Error: Could not open camera." << endl;
        return -1;
    }

    while (true) {
        Mat frame;
        capture >> frame;

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        vector<Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        for (const Rect& faceRect : faces) {
            // Draw a rectangle around the detected face
            rectangle(frame, faceRect, Scalar(0, 255, 0), 2);

            // Save the detected face to a file (you can customize the filename)
            string filename = "registered_faces/face_" + to_string(time(nullptr)) + ".jpg";
            imwrite(filename, frame(faceRect));
        }

        imshow("Face Detection", frame);

        char key = waitKey(10);
        if (key == 27) // Press ESC to exit
            break;
    }

    capture.release();
    destroyAllWindows();

    return 0;
}
