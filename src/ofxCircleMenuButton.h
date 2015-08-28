//
//  ofxCircleMenuButton.h
//  ofxCircleMenuButtonExample
//
//  Created by ISHII 2bit on 2015/08/28.
//
//

#ifndef ofxCircleMenuButtonExample_ofxCircleMenuButton_h
#define ofxCircleMenuButtonExample_ofxCircleMenuButton_h

#include "ofMain.h"

class ofxCircleMenuButtonListener {
public:
    virtual void hovered(int buttonID) {}
    virtual void buttonClicked(int buttonID) {}
};

class ofxCircleMenuButton {
    ofxCircleMenuButtonListener *listener;
    bool bEnabled;
    ofPoint center;
    vector<string> menuItems;
    int innerRadius, outerRadius;
    vector<ofPath> pathes;
    float scale;
public:
    void setup() {
        listener = NULL;
        bEnabled = false;
        scale = 0.0f;
        
        innerRadius = 80;
        outerRadius = 240;
        
        enableMouseControl();
    }
    
    void enableMouseControl() {
        ofAddListener(ofEvents().update, this, &ofxCircleMenuButton::update);
        ofAddListener(ofEvents().mousePressed, this, &ofxCircleMenuButton::mousePressed);
        ofAddListener(ofEvents().mouseReleased, this, &ofxCircleMenuButton::mouseReleased);
    }
    
    void disableMouseControl() {
        ofRemoveListener(ofEvents().mousePressed, this, &ofxCircleMenuButton::mousePressed);
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxCircleMenuButton::mouseReleased);
    }
    
    void setMenuItems(const vector<string> &menuItems) {
        this->menuItems = menuItems;
        createPath();
    }
    
    void addMenuItem(const string &menuItem) {
        menuItems.push_back(menuItem);
        createPath();
    }
    
    void createPath() {
        pathes.clear();
        for(int i = menuItems.size() - 1; 0 <= i; i--) {
            ofPath path;
            float fromRad = i * 2 * M_PI / menuItems.size(),
                  toRad   = (i + 1) * 2 * M_PI / menuItems.size();
            path.setFilled(true);
            path.setCircleResolution(40);
            path.setStrokeColor(ofColor(255, 255, 255));
            path.setStrokeWidth(1);
            path.setFillColor(ofColor(255, 255, 255, 64));
            path.moveTo(ofPoint(innerRadius * cos(fromRad),
                                innerRadius * sin(fromRad)));
            path.arc(0, 0,
                     innerRadius, innerRadius,
                     fromRad / M_PI * 180.0f, toRad / M_PI * 180.0f);
            path.moveTo(ofPoint(innerRadius * cos(toRad),
                                innerRadius * sin(toRad)));
            path.lineTo(ofPoint(outerRadius * cos(toRad),
                                outerRadius * sin(toRad)));
            path.arcNegative(0, 0,
                             outerRadius, outerRadius,
                             toRad / M_PI * 180.0f, fromRad / M_PI * 180.0f);
            path.lineTo(ofPoint(innerRadius * cos(fromRad),
                                innerRadius * sin(fromRad)));
            pathes.push_back(path);
        }
    }
    
    
    void setRadius(int inner, int outer) {
        innerRadius = inner;
        outerRadius = outer;
    }
    
    void setListener(ofxCircleMenuButtonListener *listener) {
        this->listener = listener;
    }
    
    void update(ofEventArgs &arg) {
        scale = ofLerp(scale, bEnabled, bEnabled ? 0.12f : 0.15f);
        if(scale < 0.01f) scale = 0.0f;
        if(!bEnabled) return;
        
        int index = hitTest();
        if(listener != NULL && index != -1) listener->hovered(index);
    }
    
    void draw() {
        if(scale == 0.0f) {
            return;
        }
        int index = hitTest();
        
        ofPushMatrix();
        ofEnableAlphaBlending();
        ofEnableSmoothing();
        ofTranslate(center);
        
        for(int i = 0; i < pathes.size(); i++) {
            ofPushMatrix();
            ofScale(pow(scale, 2 * i + 1), pow(scale, 2 * i + 1));
            ofPath &path = pathes[i];
            path.setFilled(index == i);
            path.draw(0, 0);
            float rad = 2.0f * M_PI * (i + 0.5f) / pathes.size();
            ofSetColor(255, 255, 255);
            const string &str = menuItems[pathes.size() - 1 - i];
            ofPoint p = (outerRadius - innerRadius) * ofPoint(cos(rad), sin(rad)) - ofPoint(8 * str.length() / 2, -12);
            ofDrawBitmapString(str, p);
            ofPopMatrix();
        }
        
        ofPopMatrix();
    }
    
    void mousePressed(ofMouseEventArgs &mouse) {
        if(mouse.button != OF_MOUSE_BUTTON_RIGHT) {
            return;
        }
        scale = 0.0f;
        center.x = mouse.x;
        center.y = mouse.y;
        bEnabled = true;
    }
    void mouseReleased(ofMouseEventArgs &mouse) {
        if(!bEnabled || mouse.button != OF_MOUSE_BUTTON_LEFT) return;
        click(mouse.x, mouse.y);
    }
    
    int hitTest() {
        int x = ofGetMouseX(), y = ofGetMouseY();
        float distance = center.distance(ofPoint(x, y));
        if(innerRadius <= distance && distance <= outerRadius) {
            double angle = -atan2(y - center.y, x - center.x);
            if(angle < 0) angle += 2 * M_PI;
            return angle / (2 * M_PI / menuItems.size());
        } else {
            return -1;
        }
    }
    
    void click(int x, int y) {
        int index = hitTest();
        bEnabled = false;
        if(listener != NULL) {
            listener->buttonClicked(index);
        }
    }
};

#endif
