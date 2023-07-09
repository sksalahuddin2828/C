#include <opencv2/opencv.hpp>

int main() {
    // Create a tracker object
    CvTracker* tracker = cvCreateTrackerByName("KCF");

    // Open the video capture
    CvCapture* cap = cvCaptureFromCAM(0);
    if (!cap) {
        printf("Failed to open video capture.\n");
        return -1;
    }

    // Read the first frame from the video
    IplImage* frame = cvQueryFrame(cap);
    if (!frame) {
        printf("Failed to read frame.\n");
        return -1;
    }

    // Select the region of interest (ROI) for tracking
    CvRect2D32f bbox = cvSelectROI("Tracking", frame, 0);

    // Initialize the tracker with the selected ROI
    cvStartTrack(tracker, frame, &bbox);

    // Main loop for video processing
    while (1) {
        // Read a frame from the video
        frame = cvQueryFrame(cap);
        if (!frame) {
            printf("Failed to read frame.\n");
            break;
        }

        // Update the tracker with the current frame
        int success = cvUpdateTrack(tracker, frame, &bbox);

        // If tracking is successful, draw the bounding box
        if (success) {
            cvRectangle(frame, cvPoint(bbox.x, bbox.y), cvPoint(bbox.x + bbox.width, bbox.y + bbox.height),
                        CV_RGB(255, 0, 255), 3, 8, 0);
            cvPutText(frame, "Tracking", cvPoint(bbox.x, bbox.y - 10), &font, CV_RGB(0, 255, 0));
        } else {
            cvPutText(frame, "Lost", cvPoint(100, 75), &font, CV_RGB(0, 0, 255));
        }

        // Display the frame
        cvShowImage("Tracking", frame);

        // Exit the loop if 'q' is pressed
        if (cvWaitKey(1) == 'q') {
            break;
        }
    }

    // Release the video capture and close windows
    cvReleaseCapture(&cap);
    cvDestroyAllWindows();

    return 0;
}
