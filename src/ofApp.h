#pragma once

#include "ofMain.h"
#include <string>

typedef struct{
    ofImage image;
    ofColor color;
}ImageList;

const int PIXEL = 10;
class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofColor getColor(ofImage image);
    void imageSetup();
    ofImage binarySearch(vector<ImageList> & list, ofColor request);
    void quickSort(vector<ImageList> & list, int begin, int end);
    void imageAllocation(vector<ImageList> & list, ofImage mainImg, vector<ofImage> & order);
    ofImage* imageTrimming(string name);
    vector<ImageList> imageList;
    vector<ofImage> drawOrder;
    ofImage mainImage, saveImage;
    int wLength, hLength;
};
