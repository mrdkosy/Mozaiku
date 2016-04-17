#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofToggleFullscreen();
    mainImage.load("1320ec21.24bit.jpg");
    imageSetup(); //素材のロード、トリミング、色解析、並べ替え
}
//--------------------------------------------------------------
void ofApp::imageSetup(){
    
    ofDirectory dir;
    dir.open("img");
    dir.listDir();
    vector<ofFile> fileNamebuffer = dir.getFiles(); //データのロード
    for(int i=0; i<fileNamebuffer.size(); i++){
        
        ImageList l;
        l.image = *imageTrimming(fileNamebuffer[i].getFileName()); //画像のトリミング
        l.color = getColor(l.image); //色種6
        imageList.push_back(l);
        
        usleep(50);
    }
    
    //探索
    imageAllocation(imageList, mainImage, drawOrder);
}
//--------------------------------------------------------------
ofImage* ofApp::imageTrimming(string name){
    
    ofImage img;
    img.load("img/"+name);
    float w = img.getWidth();
    float h = img.getHeight();
    
    img.mirror(true, false);
    float size = 180;
    if(w > h){
        img.draw(0, size/.305, w*size/h, size);
        //        img.draw(0, 0, w*size/h, size);
    }
    else{
        img.draw(0, size/.305, w*size/h, size);
        //        img.draw(0, 0, size, h*size/w);
    }
    
    saveImage.grabScreen(0, 0, size, size);
    saveImage.save("newimg/"+name);
    
    return &saveImage;
    
}
//--------------------------------------------------------------
ofColor ofApp::getColor(ofImage image){ //素材画像の色取得
    ofPixels pixels;
    pixels = image.getPixels(); //画像をpixelにする
    int skip = 10;
    ofVec3f averageColor = ofVec3f(0,0,0);
    int count = 0;
    for(int x=0; x<image.getWidth(); x+=skip){
        for(int y=0; y<image.getHeight(); y+=skip){
            ofColor color = pixels.getColor(x, y);
            ofVec3f vec = ofVec3f(color.r, color.g, color.b);
            averageColor += vec;
            count ++;
        }
    }
    averageColor /= ofVec3f(count);
    ofColor c = ofColor(averageColor.x, averageColor.y, averageColor.z);
    return c;
}
//--------------------------------------------------------------
void ofApp::imageAllocation(vector<ImageList> & list, ofImage mainImg, vector<ofImage> & order){
    
    wLength = 0; hLength = 0;
    
    ofPixels pixels;
    pixels = mainImg.getPixels();
    int skip = PIXEL;
    for(int y=0; y<mainImg.getHeight(); y+=skip){
        for(int x=0; x<mainImg.getWidth(); x+=skip){
            
            //------------------
            ofColor c;
            int skip = 2;
            ofVec3f average = ofVec3f(0);
            int count = 0;
            for(int h=0; h<PIXEL; h+=skip){
                for(int w=0; w<PIXEL; w+=skip){
                    c = pixels.getColor(x+w, y+h);
                    average += ofVec3f(c.r, c.g, c.b);
                    count ++;
                }
            }
            average /= count;
            //------------------
            
            ofImage img;
            img = min(list, ofColor(average.x, average.y, average.z));
            order.push_back(img);
            if(y == 0) wLength++;
        }
        hLength++;
    }
}
//--------------------------------------------------------------
ofImage ofApp::min(vector<ImageList> & list, ofColor request){
    
    int range = 5;
    ofImage img;
    int min = 1000;
    
    for( auto i: list ){
        //        int n = abs(i.color.r - request.r) + abs(i.color.g - request.g) + abs(i.color.g - request.g);
        int n = abs(i.color.getHue() - request.getHue()) + abs(i.color.getSaturation() - request.getSaturation()) +
        abs(i.color.getBrightness()- request.getBrightness());
        if ( n < min){
            img = i.image;
            min = n;
        }
    }
    int n = ofRandom(range);
    return img;
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofScale(1.5, 1.5);
    mainImage.draw(mainImage.getWidth(), 0, mainImage.getWidth(), mainImage.getHeight());
    ofScale(1, 1.25);
    for(int i=0; i<drawOrder.size(); i++){
        drawOrder[i].draw(PIXEL*(i%(wLength)), PIXEL*(i/hLength), PIXEL, PIXEL);
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
}
//--------------------------------------------------------------
void ofApp::update(){}
void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
