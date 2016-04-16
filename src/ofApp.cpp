#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofToggleFullscreen();
    mainImage.load("1320ec21.gif");
    imageSetup(); //素材のロード、トリミング、色解析、並べ替え
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    mainImage.draw(mainImage.getWidth(), 0, mainImage.getWidth(), mainImage.getHeight());
    for(int i=0; i<drawOrder.size(); i++){
        drawOrder[i].draw(PIXEL*(i%wLength), PIXEL*(i/hLength), PIXEL, PIXEL);
    }
    fbo.end();
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
        //        ofImage m;
        //        m.load("newimg/"+fileNamebuffer[i].getFileName());
        //        l.image = m;
        l.color = getColor(l.image); //色種6
        imageList.push_back(l);
        
        usleep(10);
    }
    
    //色データの並び替え
    quickSort(imageList, 0, imageList.size()-1);
    
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
    float size = 500;
    if(w > h){
        img.draw(0, size/1.87, w*size/h, size);
    }
    else{
        img.draw(0, size/1.87, size, h*size/w);
    }
    
    saveImage.grabScreen(0, 0, size, size);
    saveImage.save("newimg/"+name);
    
    return &saveImage;
    
}
//--------------------------------------------------------------
ofColor ofApp::getColor(ofImage image){
    ofPixels pixels;
    pixels = image.getPixels(); //画像をpixelにする
    int skip = 20;
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
    ofColor hsb = ofColor(c.getHueAngle(), c.getSaturation(), c.getBrightness());
    hsb.r = ofMap(c.getHueAngle(), 0, 360, 0, 255);
    return hsb;
}
//--------------------------------------------------------------
void ofApp::quickSort(vector<ImageList> & list, int begin, int end){
    int pivot = list[ (begin+end)/2 ].color.r;
    ofColor temp;
    int i = begin, j = end;
    
    while (1) {
        while (list[i].color.r < pivot) { ++i; };
        while (list[j].color.r > pivot) { --j; };
        if(i >= j)break;
        
        //入れ替え
        temp = list[i].color;
        list[i].color = list[j].color;
        list[j].color = temp;
        i++;
        j--;
    }
    
    //pivotの左側をsort
    if(begin < i-1){ quickSort(list, begin, i-1); };
    if(j+1 < end){ quickSort(list, j+1, end); };
    
}
//--------------------------------------------------------------
ofImage ofApp::binarySearch(vector<ImageList> & list, ofColor request){
    int head = 0;
    int tail = list.size();
    vector<ofImage>img;
    
    while( head <= tail ) {
        int center =( head + tail )/2;
        ofColor centerVal = list[center].color;
        
        if( abs(centerVal.r - request.r) < 5 ) {
            img.push_back(list[center].image);
        }else if( abs(centerVal.r - request.r) < 10 ) {
            img.push_back(list[center].image);
        }else{
            img.push_back(list[(int)ofRandom(list.size())].image);
        }
        if( centerVal.r < request.r ) {
            head = center + 1;
        }else {
            tail = center - 1;
        }
    }
    
    int n = ofRandom(img.size());
    return img[n];
}
//--------------------------------------------------------------
void ofApp::imageAllocation(vector<ImageList> & list, ofImage mainImg, vector<ofImage> & order){
    
    wLength = 0; hLength = 0;
    
    ofPixels pixels;
    pixels = mainImg.getPixels();
    int skip = PIXEL;
    for(int y=0; y<mainImg.getHeight(); y+=skip){
        for(int x=0; x<mainImg.getWidth(); x+=skip){
            ofColor c = pixels.getColor(x, y);
            c.set(c.getHueAngle(), c.getSaturation(), c.getBrightness());
            c.r = ofMap(c.getHueAngle(), 0, 360, 0, 255);
            ofImage img;
            img = binarySearch(list, c);
            order.push_back(img);
            
            if(y == 0)wLength++;
        }
        
        hLength++;
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofScale(1.5, 1.5);
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
