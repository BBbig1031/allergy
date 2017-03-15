#include "ofApp.h"
#include "ofxJSON.h"
using namespace ofxCv;


ofxJSONElement json;
#define MAX_ACT 14
#define ONE_HRS  3600
#define SIX_HRS 21600


ofTrueTypeFont title;
int uv;

//--------------------------------------------------------------


void ofApp::setup(){
        ofSetVerticalSync(true);
        ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    
        cam.initGrabber(320, 240);
    
        tracker.setup();
    
    
    ofRegisterURLNotification(this);
    cout<< "starting\n";
    
    ofEnableAlphaBlending();
    ofBackground(0);
    
    for(int i=0; i< NBALLS; i++){
        
        int size = (i+1) * ofRandom(0.05); // defining the size of each ball based on its place in the array
        int randomX = ofRandom( 0, ofGetWidth() ); //generate a random value bigger than 0 and smaller than our application screen width
        int randomY = ofRandom( 0, ofGetHeight() ); //generate a random value bigger than 0 and smaller than our application screen height
        
        myBall[i].setup(randomX, randomY, size);
    }
    player.load("sound/light.wav");
    playerslow.load("sound/slow.mp3");
    playerslow.setVolume(0.6f);
    playerslow.play();
//    player.play();
    title.load("AkzidenzGrotesk-ExtraBoldCondAlt.otf",30);
}

//--------------------------------------------------------------

void ofApp::urlResponse(ofHttpResponse & response){
    if(response.status == 200){
        cout << response.request.name <<endl;
        cout<<response.data.getText()<<endl;
        
        if(json.parse(response.data.getText())){
            uv = json[0]["UV_VALUE"].asInt();
            
            cout<< "Set uv epoch to: " <<uv<<endl;
        }else {
            cout<<"Parsing Failed."<<endl;
            
        }
        
        //        a[0].active =false;
    }else {
        cout<<response.status<<" "<<response.error<<endl;
    }
    
}


void ofApp::update(){
    
        ofSoundUpdate();
        cam.update();
        if(cam.isFrameNew()) {
            tracker.update(toCv(cam));
            position = tracker.getPosition();
            scale = tracker.getScale();
            orientation = tracker.getOrientation();
            rotationMatrix = tracker.getRotationMatrix();
        }
    for(int i=0; i<NBALLS; i++){
        myBall[i].update();
        
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
        ofSetColor(255);
        cam.draw(0, 0);
        ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    
    int fontFade = 0;  // alpha for title font
    if (ofGetFrameNum() <= 30){
        fontFade = ofMap(ofGetFrameNum(), 0,  120, 0, 255, true); // going up
    } else {
        fontFade = ofMap(ofGetFrameNum(), 120,  240, 255, 0, true);// going down
        if (ofGetMousePressed()== true && uv >= 0 && uv < 1){
            for(int i=0; i<100; i++){
                myBall[i].draw();
            }
        }else if (ofGetMousePressed()== true && uv >= 1){
            for(int i=0; i<NBALLS; i++){
                myBall[i].draw();
            }
            
        }
        ofSetColor(255,255,255, fontFade);
        title.drawString("PHOTODERMATITIS", (ofGetWidth()/2-130), ofGetHeight()-50);
        ofSetColor(255);
    }
    
        if(tracker.getFound()) {
            ofSetLineWidth(1);
            tracker.draw();
    
            ofSetupScreenOrtho(640, 480, -1000, 1000);
            ofTranslate(640 / 2, 480 / 2);
    
            ofPushMatrix();
            ofScale(5,5,5);
            tracker.getObjectMesh().drawWireframe();
            ofPopMatrix();
    
            applyMatrix(rotationMatrix);
            ofScale(5,5,5);
            tracker.getObjectMesh().drawWireframe();
        }
    
    
 
    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//        if(key == 'r') {
//            
//        }
    
    if (key == ' ')
        string url = "https://iaspub.epa.gov/enviro/efservice/getEnvirofactsUVHOURLY/ZIP/10009/JSON";
    
    ofLoadURLAsync("https://iaspub.epa.gov/enviro/efservice/getEnvirofactsUVHOURLY/ZIP/10009/JSON", "async_req");
   
    
    
    cout<<"Current epoch uv is: " <<uv<<endl;
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
    mouseX = x;
    mouseY =y;
    
    if (mouseX <= 630 &&  mouseX>= 390 && mouseY <= 500 &&  mouseY>= 300 ){
    
    player.play();
    
    
    }
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
