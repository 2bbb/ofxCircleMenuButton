#include "ofMain.h"
#include "ofxCircleMenuButton.h"

class ofApp : public ofBaseApp, public ofxCircleMenuButtonListener {
    ofxCircleMenuButton menu;
public:
    virtual void buttonClicked(int buttonID) {
        ofLogNotice() << "clciked: " << buttonID;
    }
    
    virtual void hovered(int buttonID) {
        ofLogNotice() << "hovered: " << buttonID;
    }
    
    void setup() {
        menu.setup();
        vector<string> menuItems;
        menuItems.push_back("scene 1");
        menuItems.push_back("scene 2");
        menuItems.push_back("scene 3");
        menuItems.push_back("scene 4");
        menuItems.push_back("scene 5");
        menuItems.push_back("scene 6");
        menuItems.push_back("scene 7");
        menu.setMenuItems(menuItems);
        menu.setListener(this);
    }
    void update() {
        
    }
    void draw() {
        ofBackground(0);
        menu.draw();
        ofSetColor(255, 0, 0);
        ofCircle(mouseX, mouseY, 20);
    }
    
    void keyPressed(int key) {
        
    }
    void keyReleased(int key) {
        
    }
    void mouseMoved(int x, int y ) {
        
    }
    void mouseDragged(int x, int y, int button) {
        
    }
    void mousePressed(int x, int y, int button) {
        
    }
    void mouseReleased(int x, int y, int button) {
        
    }
    void windowResized(int w, int h) {
        
    }
    void dragEvent(ofDragInfo dragInfo) {
        
    }
    void gotMessage(ofMessage msg) {
        
    }
    
};

int main( ){
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp);
}
